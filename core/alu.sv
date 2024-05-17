// Copyright 2018 ETH Zurich and University of Bologna.
// Copyright and related rights are licensed under the Solderpad Hardware
// License, Version 0.51 (the "License"); you may not use this file except in
// compliance with the License.  You may obtain a copy of the License at
// http://solderpad.org/licenses/SHL-0.51. Unless required by applicable law
// or agreed to in writing, software, hardware and materials distributed under
// this License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.
//
// Author: Matthias Baer <baermatt@student.ethz.ch>
// Author: Igor Loi <igor.loi@unibo.it>
// Author: Andreas Traber <atraber@student.ethz.ch>
// Author: Lukas Mueller <lukasmue@student.ethz.ch>
// Author: Florian Zaruba <zaruabf@iis.ee.ethz.ch>
//
// Date: 19.03.2017
// Description: Ariane ALU based on RI5CY's ALU


module alu import ariane_pkg::*;(
    input  logic                     clk_i,          // Clock
    input  logic                     rst_ni,         // Asynchronous reset active low
    input  fu_data_t                 fu_data_i,
    output riscv::xlen_t             result_o,
    output logic                     alu_branch_res_o
);

    riscv::xlen_t operand_a_rev;
    logic [31:0] operand_a_rev32;
    logic [riscv::XLEN:0] operand_b_neg;
    logic [riscv::XLEN+1:0] adder_result_ext_o;
    logic        less;  // handles both signed and unsigned forms
    logic [31:0] rolw;                    // Rotate Left Word
    logic [31:0] rorw;                    // Rotate Right Word
    logic [31:0] orcbw, rev8w;
    logic [$clog2(riscv::XLEN) :0] cpop; // Count Population
    logic [$clog2(riscv::XLEN)-1 :0] lz_tz_count;              // Count Leading Zeros
    logic [4:0] lz_tz_wcount;             // Count Leading Zeros Word
    logic       lz_tz_empty, lz_tz_wempty;

    // bit reverse operand_a for left shifts and bit counting
    generate
      genvar k;
      for(k = 0; k < riscv::XLEN; k++)
        assign operand_a_rev[k] = fu_data_i.operand_a[riscv::XLEN-1-k];

      for (k = 0; k < 32; k++)
        assign operand_a_rev32[k] = fu_data_i.operand_a[31-k];
    endgenerate

    // ------
    // Adder
    // ------
    logic        adder_op_b_negate;
    logic        adder_z_flag;
    logic [riscv::XLEN:0] adder_in_a, adder_in_b;
    riscv::xlen_t adder_result;
    logic [riscv::XLEN-1:0] operand_a_bitmanip, bit_indx;

    always_comb begin
      adder_op_b_negate = 1'b0; 

      unique case (fu_data_i.operator)
        // ADDER OPS
        EQ,  NE,
        SUB, SUBW,
        ANDN, ORN, XNOR: adder_op_b_negate = 1'b1;
        default: ;
      endcase
    end

    always_comb begin
      operand_a_bitmanip = fu_data_i.operand_a;

      if (ariane_pkg::BITMANIP) begin
        unique case (fu_data_i.operator)
          SH1ADD   : operand_a_bitmanip = fu_data_i.operand_a << 1;
          SH2ADD   : operand_a_bitmanip = fu_data_i.operand_a << 2;
          SH3ADD   : operand_a_bitmanip = fu_data_i.operand_a << 3;
          SH1ADDUW : operand_a_bitmanip = fu_data_i.operand_a[31:0] << 1;
          SH2ADDUW : operand_a_bitmanip = fu_data_i.operand_a[31:0] << 2;
          SH3ADDUW : operand_a_bitmanip = fu_data_i.operand_a[31:0] << 3;
          CTZ      : operand_a_bitmanip = operand_a_rev;
          CTZW     : operand_a_bitmanip = operand_a_rev32;
          ADDUW, CPOPW, CLZW   : operand_a_bitmanip = fu_data_i.operand_a[31:0];
          default  : ;
        endcase
      end
    end

    // prepare operand a
    assign adder_in_a    = {operand_a_bitmanip, 1'b1};

    // prepare operand b
    assign operand_b_neg = {fu_data_i.operand_b, 1'b0} ^ {riscv::XLEN+1{adder_op_b_negate}};
    assign adder_in_b    =  operand_b_neg ;

    // actual adder
    assign adder_result_ext_o = $unsigned(adder_in_a) + $unsigned(adder_in_b);
    assign adder_result       = adder_result_ext_o[riscv::XLEN:1];
    assign adder_z_flag       = ~|adder_result;

    // get the right branch comparison result
    always_comb begin : branch_resolve
        // set comparison by default
        alu_branch_res_o      = 1'b1;
        case (fu_data_i.operator)
            EQ:       alu_branch_res_o = adder_z_flag;
            NE:       alu_branch_res_o = ~adder_z_flag;
            LTS, LTU: alu_branch_res_o = less;
            GES, GEU: alu_branch_res_o = ~less;
            default:  alu_branch_res_o = 1'b1;
        endcase
    end

    // ---------
    // Shifts
    // ---------

    // TODO: this can probably optimized significantly
    logic        shift_left;          // should we shift left
    logic        shift_arithmetic;

    riscv::xlen_t shift_amt;           // amount of shift, to the right
    riscv::xlen_t shift_op_a;          // input of the shifter
    logic [31:0] shift_op_a32;        // input to the 32 bit shift operation

    riscv::xlen_t shift_result;
    logic [31:0] shift_result32;

    logic [riscv::XLEN:0] shift_right_result;
    logic [32:0] shift_right_result32;

    riscv::xlen_t shift_left_result;
    logic [31:0] shift_left_result32;

    assign shift_amt = fu_data_i.operand_b;

    assign shift_left = (fu_data_i.operator == SLL) | (fu_data_i.operator == SLLW);

    assign shift_arithmetic = (fu_data_i.operator == SRA) | (fu_data_i.operator == SRAW);

    // right shifts, we let the synthesizer optimize this
    logic [riscv::XLEN:0] shift_op_a_64;
    logic [32:0] shift_op_a_32;

    // choose the bit reversed or the normal input for shift operand a
    assign shift_op_a    = shift_left ? operand_a_rev   : fu_data_i.operand_a;
    assign shift_op_a32  = shift_left ? operand_a_rev32 : fu_data_i.operand_a[31:0];

    assign shift_op_a_64 = { shift_arithmetic & shift_op_a[riscv::XLEN-1], shift_op_a};
    assign shift_op_a_32 = { shift_arithmetic & shift_op_a[31], shift_op_a32};

    assign shift_right_result     = $unsigned($signed(shift_op_a_64) >>> shift_amt[5:0]);

    assign shift_right_result32   = $unsigned($signed(shift_op_a_32) >>> shift_amt[4:0]);
    // bit reverse the shift_right_result for left shifts
    genvar j;
    generate
      for(j = 0; j < riscv::XLEN; j++)
        assign shift_left_result[j] = shift_right_result[riscv::XLEN-1-j];

      for(j = 0; j < 32; j++)
        assign shift_left_result32[j] = shift_right_result32[31-j];

    endgenerate

    assign shift_result = shift_left ? shift_left_result : shift_right_result[riscv::XLEN-1:0];
    assign shift_result32 = shift_left ? shift_left_result32 : shift_right_result32[31:0];

    // ------------
    // Comparisons
    // ------------

    always_comb begin
        logic sgn;
        sgn = 1'b0;

        if ((fu_data_i.operator == SLTS) ||
            (fu_data_i.operator == LTS)  ||
            (fu_data_i.operator == GES)  ||
            (fu_data_i.operator == MAX)  ||
            (fu_data_i.operator == MIN))
            sgn = 1'b1;

        less = ($signed({sgn & fu_data_i.operand_a[riscv::XLEN-1], fu_data_i.operand_a})  <  $signed({sgn & fu_data_i.operand_b[riscv::XLEN-1], fu_data_i.operand_b}));
    end

    if (ariane_pkg::BITMANIP) begin : gen_bitmanip
        // Count Population + Count population Word

        popcount #(
          .INPUT_WIDTH(riscv::XLEN)
        ) i_cpop_count (
          .data_i           (operand_a_bitmanip),
          .popcount_o       (cpop)
        );

        // Count Leading/Trailing Zeros
        // 64b
        lzc #(
          .WIDTH(riscv::XLEN),
          .MODE (1)
        ) i_clz_64b (
          .in_i (operand_a_bitmanip),
          .cnt_o (lz_tz_count),
          .empty_o (lz_tz_empty)
        );
        //32b
        lzc #(
          .WIDTH(32),
          .MODE (1)
        ) i_clz_32b (
          .in_i (operand_a_bitmanip[31:0]),
          .cnt_o (lz_tz_wcount),
          .empty_o (lz_tz_wempty)
        );
    end

    // -----------
    //  TURBO
    // -----------

      //PARAMs
      logic [riscv::XLEN-1:0] polar_result; 
      parameter integer Q         = 8 ; //8 bit qtf 
      parameter integer SIMD      = 4 ; 
      // parameter integer idx_size  = 4 ; // 4 bits to cover 0->7 shuffle network in 64b varation  
      // Array of vectors [ SIMD_lvl | simd_lvl-1 | simd_lvl-2 | ect..]   
      parameter integer V_LENGHT  = (Q*SIMD) ; //32b ou 64b 

      // scale /sign 
      logic [(V_LENGHT)-1:0] tb_in_A, tb_in_B, tb_in_C, r_scale, r_sign ; 
      logic [SIMD-1:0]       tb_sign ;

      // MAX
      logic [V_LENGHT-1:0]  tb_max ;

      // adds/subs
      logic [V_LENGHT-1:0]  tb_add, tb_sub;  

      // div2add div2sub
      logic [V_LENGHT-1:0]  r_divadd, r_divsub;       

      // sat63 :sb_at
      logic [V_LENGHT-1:0]  r_sat63, r_sb_sat;  

      // MAXPM 
      logic[V_LENGHT-1:0]  r_maxpm_1, r_maxpm_2, r_maxpm ; 

      // ACCUMAX
      logic[V_LENGHT-1:0]  r_max_1, r_max_2 ; 

      // accu PM, PP 
      logic[V_LENGHT-1:0]  r_accupp, r_accupm ; 

      // blendv
      logic[V_LENGHT-1:0]  r_blend; 


      // shuffle
      logic [V_LENGHT-1:0]  r_shuffle;  
      logic [V_LENGHT-1:0]  r_shuffle_data;
      logic [(4*SIMD)-1:0]  r_index; 
      logic [SIMD-1:0]      r_shfl_mask; //peut partir par opti 

      assign r_index[15:12] = fu_data_i.operand_b[24+3:24] ;  
      assign r_index[11: 8] = fu_data_i.operand_b[16+3:16] ;  
      assign r_index[ 7: 4] = fu_data_i.operand_b[8+3 : 8] ;  
      assign r_index[ 3: 0] = fu_data_i.operand_b[3   : 0] ;  

      always_comb begin : shuffle_selection
        r_shuffle_data ='b0 ; 

        case(r_index[3:0])
          4'b0000 : r_shuffle_data[7:0] = fu_data_i.operand_a[7:0]    ; 
          4'b0001 : r_shuffle_data[7:0] = fu_data_i.operand_a[15:8]   ;
          4'b0010 : r_shuffle_data[7:0] = fu_data_i.operand_a[23:16]  ;
          4'b0011 : r_shuffle_data[7:0] = fu_data_i.operand_a[31:24]  ;
          default : r_shuffle_data[7:0] = 0 ;  
        endcase 

        case( r_index[ 7: 4])
          4'b0000 : r_shuffle_data[15:8] = fu_data_i.operand_a[7:0]    ;
          4'b0001 : r_shuffle_data[15:8] = fu_data_i.operand_a[15:8]   ;
          4'b0010 : r_shuffle_data[15:8] = fu_data_i.operand_a[23:16]  ;
          4'b0011 : r_shuffle_data[15:8] = fu_data_i.operand_a[31:24]  ;
          default : r_shuffle_data[15:8] = 0 ;
        endcase 

        case(r_index[11: 8])
          4'b0000 : r_shuffle_data[23:16] = fu_data_i.operand_a[7:0]    ; 
          4'b0001 : r_shuffle_data[23:16] = fu_data_i.operand_a[15:8]   ;
          4'b0010 : r_shuffle_data[23:16] = fu_data_i.operand_a[23:16]  ;
          4'b0011 : r_shuffle_data[23:16] = fu_data_i.operand_a[31:24]  ;
          default : r_shuffle_data[23:16] = 0; 
        endcase 

        case(r_index[15:12])
          4'b0000 : r_shuffle_data[31:24] = fu_data_i.operand_a[7:0]    ;
          4'b0001 : r_shuffle_data[31:24] = fu_data_i.operand_a[15:8]   ;
          4'b0010 : r_shuffle_data[31:24] = fu_data_i.operand_a[23:16]  ;
          4'b0011 : r_shuffle_data[31:24] = fu_data_i.operand_a[31:24]  ;
          default : r_shuffle_data[31:24] ='b0 ; 
        endcase 
    end

      // cycle trought the vectors 
      generate
        for ( genvar i=0 ; i<SIMD ; i++ ) begin

          // scale 
          assign tb_sign[i]         = ($signed(fu_data_i.operand_a[ i*Q +:Q] ) >=0 )? 1 : 0 ; 			
          assign tb_in_A[ i*Q +:Q]  = (tb_sign[i]) ? fu_data_i.operand_a[i*Q +:Q] : - fu_data_i.operand_a[i*Q +:Q] ; 
          assign tb_in_B[ i*Q +:Q]  = tb_in_A[ i*Q +:Q] >> 2 ; 
          assign tb_in_C[ i*Q +:Q]  = tb_in_A[ i*Q +:Q] - tb_in_B[ i*Q +:Q] ; 
          // final 
          assign r_scale[ i*Q +:Q]  = ((tb_sign[i])? tb_in_C[ i*Q +:Q] : -tb_in_C[ i*Q +:Q]) + fu_data_i.operand_b[i*Q +:Q] ;

          // // sign : inv of _sign 
          // assign r_sign[  i*Q +:Q]  = (tb_sign[i])? 0 : 1 ; 

          // max 
          assign tb_max[i*Q +:Q]    = ( $signed(fu_data_i.operand_a[ i*Q +:Q] ) <= $signed(fu_data_i.operand_b[ i*Q +:Q]) ) ? fu_data_i.operand_b[ i*Q +:Q]: 
                                                                                                                              fu_data_i.operand_a[ i*Q +:Q];
          // add/sub
          assign tb_add[i*Q +:Q]    =  $signed(fu_data_i.operand_a[ i*Q +:Q] ) + $signed(fu_data_i.operand_b[ i*Q +:Q])  ;  
          assign tb_sub[i*Q +:Q]    =  $signed(fu_data_i.operand_a[ i*Q +:Q] ) - $signed(fu_data_i.operand_b[ i*Q +:Q])  ;  
          
          // shuffle
          assign r_shfl_mask[i]     = (fu_data_i.operand_b[i*Q +:Q]==8'h01) ? 1'b1 :1'b0; 
          
          // 4b wide is enough   
          assign r_shuffle[i*Q +:Q] = (r_shfl_mask[i]==1'b1) ? 8'h00 : r_shuffle_data[i*Q +:Q] ; 

          // divadd /sub
          assign r_divadd[i*Q +:Q]  = (tb_add[i*Q +:Q])>>1;
          assign r_divsub[i*Q +:Q]  = (tb_sub[i*Q +:Q])>>1;

          // sat63
          assign r_sat63[i*Q +:Q]   = ($signed(fu_data_i.operand_a[i*Q +:Q]) >  8'sd63)?  8'sd63 :
                                      ($signed(fu_data_i.operand_a[i*Q +:Q]) < -8'sd63)? -8'sd63 :
                                      fu_data_i.operand_a[i*Q +:Q]; 
          // sb_sat
          assign r_sb_sat[i*Q +:Q]  = $signed(r_sat63[i*Q +:Q]) - $signed(fu_data_i.operand_b[i*Q +:Q]);
          
          // maxpm
          assign r_maxpm_1[i*Q +:Q] = $signed(fu_data_i.operand_a[i*Q +:Q]) + $signed(fu_data_i.operand_b[i*Q +:Q]);
          assign r_maxpm_2[i*Q +:Q] = $signed(fu_data_i.imm[i*Q +:Q])       - $signed(fu_data_i.operand_b[i*Q +:Q]);
          assign r_maxpm[i*Q +:Q]   = $signed(r_maxpm_1[i*Q +:Q]) < $signed(r_maxpm_2[i*Q +:Q])  ? r_maxpm_2[i*Q +:Q] :r_maxpm_1[i*Q +:Q] ;

          // accu PM, MP 
          assign r_accupp[i*Q +:Q]  = $signed(r_maxpm_1[i*Q +:Q]) + $signed(fu_data_i.imm[i*Q +:Q]);  
          assign r_accupm[i*Q +:Q]  = $signed(fu_data_i.operand_a[i*Q +:Q]) + $signed(fu_data_i.operand_b[i*Q +:Q]) - $signed(fu_data_i.imm[i*Q +:Q]);  

          // blenv
          assign r_blend[i*Q +:Q]   = $signed(fu_data_i.operand_a[i*Q +:Q] &  fu_data_i.imm[i*Q +:Q] ) | 
                                      $signed(fu_data_i.operand_b[i*Q +:Q] & ~fu_data_i.imm[i*Q +:Q] ) ; 
        end 
      endgenerate
    // -----------
    // Result MUX
    // -----------
    always_comb begin
        result_o   = '0;
        unique case (fu_data_i.operator)
            // Turbo
            TB_MAX    : result_o = tb_max;
            TB_ADDS   : result_o = tb_add;
            TB_SUBS   : result_o = tb_sub;
            TB_ACCUPP : result_o = r_accupp; 
            TB_ACCUPM : result_o = r_accupm;  
            TB_SHUFFLE: result_o = r_shuffle;
            TB_DIV_ADD: result_o = r_divadd;
            TB_DIV_SUB: result_o = r_divsub;
            TB_SB_SAT : result_o = r_sb_sat;
            TB_MAXPM  : result_o =  r_maxpm;
            TB_BLEND  : result_o =  r_blend; 
            TB_SCALE  : result_o = r_scale;


            // Standard Operations
            ANDL, ANDN: result_o = fu_data_i.operand_a & operand_b_neg[riscv::XLEN:1];
            ORL, ORN  : result_o = fu_data_i.operand_a | operand_b_neg[riscv::XLEN:1];
            XORL, XNOR: result_o = fu_data_i.operand_a ^ operand_b_neg[riscv::XLEN:1];

            // Adder Operations
            ADD, SUB,
            ADDUW,
            SH1ADD, SH2ADD, SH3ADD,
            SH1ADDUW, SH2ADDUW, SH3ADDUW: result_o = adder_result;
            // Add word: Ignore the upper bits and sign extend to 64 bit
            ADDW, SUBW: result_o = {{riscv::XLEN-32{adder_result[31]}}, adder_result[31:0]};
            // Shift Operations
            SLL,
            SRL, SRA: result_o = (riscv::XLEN == 64) ? shift_result : shift_result32;
            // Shifts 32 bit
            SLLW,
            SRLW, SRAW: result_o = {{riscv::XLEN-32{shift_result32[31]}}, shift_result32[31:0]};

            // Comparison Operations
            SLTS,  SLTU: result_o = {{riscv::XLEN-1{1'b0}}, less};

            default: ; // default case to suppress unique warning
        endcase

        if (ariane_pkg::BITMANIP) begin
            // Index for Bitwise Rotation
            bit_indx = 1 << (fu_data_i.operand_b & (riscv::XLEN-1));
            orcbw = {{8{|fu_data_i.operand_a[31:24]}}, {8{|fu_data_i.operand_a[23:16]}}, {8{|fu_data_i.operand_a[15:8]}}, {8{|fu_data_i.operand_a[7:0]}}};
            rev8w = {{fu_data_i.operand_a[7:0]}, {fu_data_i.operand_a[15:8]}, {fu_data_i.operand_a[23:16]}, {fu_data_i.operand_a[31:24]}};
            // rolw, roriw, rorw
            rolw = ({{riscv::XLEN-32{1'b0}},fu_data_i.operand_a[31:0]} << fu_data_i.operand_b[4:0]) | ({{riscv::XLEN-32{1'b0}},fu_data_i.operand_a[31:0]} >> (riscv::XLEN-32-fu_data_i.operand_b[4:0]));
            rorw = ({{riscv::XLEN-32{1'b0}},fu_data_i.operand_a[31:0]} >> fu_data_i.operand_b[4:0]) | ({{riscv::XLEN-32{1'b0}},fu_data_i.operand_a[31:0]} << (riscv::XLEN-32-fu_data_i.operand_b[4:0]));
            unique case (fu_data_i.operator)
                // Left Shift 32 bit unsigned
                SLLIUW: result_o = {{riscv::XLEN-32{1'b0}}, fu_data_i.operand_a[31:0]} << fu_data_i.operand_b[5:0];
                // Integer minimum/maximum
                MAX:  result_o = less ? fu_data_i.operand_b : fu_data_i.operand_a;
                MAXU: result_o = less ? fu_data_i.operand_b : fu_data_i.operand_a;
                MIN:  result_o = ~less ? fu_data_i.operand_b : fu_data_i.operand_a;
                MINU: result_o = ~less ? fu_data_i.operand_b : fu_data_i.operand_a;

                // Single bit instructions operations
                BCLR, BCLRI: result_o = fu_data_i.operand_a & ~bit_indx;
                BEXT, BEXTI: result_o = |(fu_data_i.operand_a & bit_indx);
                BINV, BINVI: result_o = fu_data_i.operand_a ^ bit_indx;
                BSET, BSETI: result_o = fu_data_i.operand_a | bit_indx;

                // Count Leading/Trailing Zeros
                CLZ, CTZ  :  result_o = (lz_tz_empty) ? (lz_tz_count + 1) : lz_tz_count;
                CLZW, CTZW:  result_o = (lz_tz_wempty) ? 32 : lz_tz_wcount;

                // Count population
                CPOP, CPOPW: result_o = cpop;

                // Sign and Zero Extend
                SEXTB: result_o = {{riscv::XLEN-8{fu_data_i.operand_a[7]}}, fu_data_i.operand_a[7:0]};
                SEXTH: result_o = {{riscv::XLEN-16{fu_data_i.operand_a[15]}}, fu_data_i.operand_a[15:0]};
                ZEXTH: result_o = {{riscv::XLEN-16{1'b0}}, fu_data_i.operand_a[15:0]};

                // Bitwise Rotation
                ROL:          result_o = (riscv::XLEN == 64) ? ((fu_data_i.operand_a << fu_data_i.operand_b[5:0]) | (fu_data_i.operand_a >> (riscv::XLEN-fu_data_i.operand_b[5:0]))) : ((fu_data_i.operand_a << fu_data_i.operand_b[4:0]) | (fu_data_i.operand_a >> (riscv::XLEN-fu_data_i.operand_b[4:0])));
                ROLW:         result_o = {{riscv::XLEN-32{rolw[31]}}, rolw};
                ROR, RORI:    result_o = (riscv::XLEN == 64) ? ((fu_data_i.operand_a >> fu_data_i.operand_b[5:0]) | (fu_data_i.operand_a << (riscv::XLEN-fu_data_i.operand_b[5:0]))) : ((fu_data_i.operand_a >> fu_data_i.operand_b[4:0]) | (fu_data_i.operand_a << (riscv::XLEN-fu_data_i.operand_b[4:0])));
                RORW, RORIW:  result_o = {{riscv::XLEN-32{rorw[31]}}, rorw};
                ORCB:         result_o = (riscv::XLEN == 64) ? ({{8{|fu_data_i.operand_a[63:56]}}, {8{|fu_data_i.operand_a[55:48]}}, {8{|fu_data_i.operand_a[47:40]}}, {8{|fu_data_i.operand_a[39:32]}}, orcbw}) : orcbw;
                REV8:         result_o = (riscv::XLEN == 64) ? ({rev8w , {fu_data_i.operand_a[39:32]}, {fu_data_i.operand_a[47:40]}, {fu_data_i.operand_a[55:48]}, {fu_data_i.operand_a[63:56]}}) : rev8w;

                default: ; // default case to suppress unique warning
            endcase
        end
    end
endmodule

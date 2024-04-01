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
    //////////////////
    //POLAR autogen //
    //////////////////
    // Pas d'optis 

    logic [riscv::XLEN-1:0] polar_result; 
    parameter integer Q       = 8 ;

    parameter integer SIMD    = 8 ; 
    // Array of vectors [ SIMD_lvl | simd_lvl-1 | simd_lvl-2 | ect..]   
    parameter integer V_LENGHT = (Q*SIMD) ;

// 9 bits to compute overflow for SIMD values.. .
    logic [9*SIMD:0]    polar_res_aminusb, 
                        polar_res_aplusb; 

    // pl_r 
    logic [(V_LENGHT)-1:0]  func_r,
                            abs_a, 
                            abs_b,
                            func_f,
                            func_addsat,
                            func_subsat,
                            decode,
                            eval,
                            func_g;
    // sign 1 bit 
    logic [SIMD-1:0]        sign ;

    // cycle trought the vectors 
    generate

        for ( genvar i =0 ;  i<SIMD ;i++ ) begin
            
            // assign i = k*Q ; 
            // assign byte0 = dword[0 +: 8];    // Same as dword[7:0]

            // This is illegal due to the variable i, even though the width is always 8 bits
            // assign byte = dword[(i*8)+7 : i*8];  // ** Not allowed!

            // Use the indexed part select 
            // assign byte = dword[i*8 +: 8];
            
            assign func_r[i*Q +:Q] =  ($signed(fu_data_i.operand_b[7:0] ) == 8'sb1) ?8'h00: ( $signed(fu_data_i.operand_a[i*Q +:Q ]) < 8'sb0 ) ? 8'h01 : 8'h00 ; 
            
            assign decode[i*Q +:Q] =  (fu_data_i.operand_b[7:0] ==8'h00 ) ? fu_data_i.operand_a[i*Q +:Q] : 8'h00 ; 
            // we have to account for possible overflow

            assign sign[i]         =  ( ( $signed( fu_data_i.operand_a[i*Q +:Q ]  ) >= 0) ? 1'b0:1'b1)  ^ ( ( $signed(fu_data_i.operand_b[i*Q +:Q] ) >= 0 )? 1'b0:1'b1)   ;

            assign abs_a[ i*Q +:Q] = ( ( $signed( fu_data_i.operand_a[i*Q +:Q]   ) >= 0) ? fu_data_i.operand_a[i*Q +:Q]   : -fu_data_i.operand_a[i*Q +:Q] ) ;
            assign abs_b[ i*Q +:Q] = ( ( $signed( fu_data_i.operand_b[i*Q +:Q]   ) >= 0) ? fu_data_i.operand_b[i*Q +:Q]   : -fu_data_i.operand_b[i*Q +:Q] ) ;

            assign func_f[i*Q +:Q] =  ( abs_a[i*Q +:Q] > abs_b[i*Q +:Q] ) ? 
                                      (( sign[i] == 1'b0 ) ? abs_b[i*Q +:Q] : -abs_b[i*Q +:Q] ) 
                                      :  
                                      (( sign[i] == 1'b0 ) ? abs_a[i*Q +:Q] : -abs_a[i*Q +:Q] ) ; 

            // need to compare with signed 
            // synth will do the rest 
            
            // SUBSAT 
            assign polar_res_aminusb[(i*9) +:9]  = $signed( fu_data_i.operand_b[ i*Q +:Q]) - $signed( fu_data_i.operand_a[i*Q +:Q]) ;
            assign func_subsat[ i*Q +:Q] =  ($signed(polar_res_aminusb[(i*9) +:9]) >  9'sd127)?  8'sd127 : 
                                            ($signed(polar_res_aminusb[(i*9) +:9]) < -9'sd127)? -8'sd127 : 
                                            polar_res_aminusb[(i*9) +:9];
            
            // ADDSAT 
            assign polar_res_aplusb[(i*9)  +:9]  = $signed( fu_data_i.operand_a[ i*Q +:Q]) + $signed( fu_data_i.operand_b[i*Q +:Q]) ;
            assign func_addsat[ i*Q +:Q] =  ( $signed(polar_res_aplusb[(i*9) +:9])  >  9'sd127) ? 8'sd127 : 
                                            ( $signed(polar_res_aplusb[(i*9) +:9])  < -9'sd127)? -8'sd127 : 
                                            polar_res_aplusb[(i*9) +:9] ;

            

            assign eval[i*Q +:Q]   =(fu_data_i.operand_a[i*Q +:Q] ==8'd1 ) ? 8'hFF : 8'h00 ; 

            assign func_g[i*Q+:Q] =  (fu_data_i.imm[i*Q+:Q]==8'h00)?  func_addsat[ i*Q +:Q]: 
                                                                      func_subsat[ i*Q +:Q]; 

        end 
  endgenerate


  always_comb begin
    polar_result='0 ; 
    unique case (fu_data_i.operator)

      PL_R:       polar_result =  func_r; 
      PL_F:       polar_result =  func_f ;
      PL_DECODE : polar_result =  decode ; 
      PL_EVAL   : polar_result =  eval ; 
      PL_G      : polar_result =  func_g ; 

      default: polar_result='0 ; 
    endcase
  end 

    // -----------
    // Result MUX
    // -----------
    always_comb begin
        result_o   = '0;
        unique case (fu_data_i.operator)
            
            // polar  operations 
            PL_F,
            PL_R,
            PL_DECODE,
            PL_EVAL,
            PL_G : result_o = polar_result;


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
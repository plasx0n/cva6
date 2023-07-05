/**
  Copyright (c) 2012-2015 "Bordeaux INP, Bertrand LE GAL"
  [http://legal.vvv.enseirb-matmeca.fr]

  This file is part of LDPC_C_Simulator.

  LDPC_C_Simulator is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _GF64_
#define _GF64_

const int GF64_BINGF[64][6]=
{
  {0, 0, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0},
  {0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 1},
  {1, 1, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 0},
  {0, 0, 1, 1, 0, 0},
  {0, 0, 0, 1, 1, 0},
  {0, 0, 0, 0, 1, 1},
  {1, 1, 0, 0, 0, 1},
  {1, 0, 1, 0, 0, 0},
  {0, 1, 0, 1, 0, 0},
  {0, 0, 1, 0, 1, 0},
  {0, 0, 0, 1, 0, 1},
  {1, 1, 0, 0, 1, 0},
  {0, 1, 1, 0, 0, 1},
  {1, 1, 1, 1, 0, 0},
  {0, 1, 1, 1, 1, 0},
  {0, 0, 1, 1, 1, 1},
  {1, 1, 0, 1, 1, 1},
  {1, 0, 1, 0, 1, 1},
  {1, 0, 0, 1, 0, 1},
  {1, 0, 0, 0, 1, 0},
  {0, 1, 0, 0, 0, 1},
  {1, 1, 1, 0, 0, 0},
  {0, 1, 1, 1, 0, 0},
  {0, 0, 1, 1, 1, 0},
  {0, 0, 0, 1, 1, 1},
  {1, 1, 0, 0, 1, 1},
  {1, 0, 1, 0, 0, 1},
  {1, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 1, 0},
  {0, 0, 1, 0, 0, 1},
  {1, 1, 0, 1, 0, 0},
  {0, 1, 1, 0, 1, 0},
  {0, 0, 1, 1, 0, 1},
  {1, 1, 0, 1, 1, 0},
  {0, 1, 1, 0, 1, 1},
  {1, 1, 1, 1, 0, 1},
  {1, 0, 1, 1, 1, 0},
  {0, 1, 0, 1, 1, 1},
  {1, 1, 1, 0, 1, 1},
  {1, 0, 1, 1, 0, 1},
  {1, 0, 0, 1, 1, 0},
  {0, 1, 0, 0, 1, 1},
  {1, 1, 1, 0, 0, 1},
  {1, 0, 1, 1, 0, 0},
  {0, 1, 0, 1, 1, 0},
  {0, 0, 1, 0, 1, 1},
  {1, 1, 0, 1, 0, 1},
  {1, 0, 1, 0, 1, 0},
  {0, 1, 0, 1, 0, 1},
  {1, 1, 1, 0, 1, 0},
  {0, 1, 1, 1, 0, 1},
  {1, 1, 1, 1, 1, 0},
  {0, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1},
  {1, 0, 1, 1, 1, 1},
  {1, 0, 0, 1, 1, 1},
  {1, 0, 0, 0, 1, 1},
  {1, 0, 0, 0, 0, 1}
};

//
// DEST_NAT[ GF64_S2N[i] ] = SRC_SYMBOL[ i ]
//
const int GF64_S2N[64] = {
   0,  32,  16,   8,   4,   2,   1,  48,
  24,  12,   6,   3,  49,  40,  20,  10,
   5,  50,  25,  60,  30,  15,  55,  43,
  37,  34,  17,  56,  28,  14,   7,  51,
  41,  36,  18,   9,  52,  26,  13,  54,
  27,  61,  46,  23,  59,  45,  38,  19,
  57,  44,  22,  11,  53,  42,  21,  58,
  29,  62,  31,  63,  47,  39,  35,  33,
};

//
//
//
const int GF64_N2S[64] = {
  0,   6,   5,  11,   4,  16,  10,  30,
  3,  35,  15,  51,   9,  38,  29,  21,
  2,  26,  34,  47,  14,  54,  50,  43,
  8,  18,  37,  40,  28,  56,  20,  58,
  1,  63,  25,  62,  33,  24,  46,  61,
 13,  32,  53,  23,  49,  45,  42,  60,
  7,  12,  17,  31,  36,  52,  39,  22,
 27,  48,  55,  44,  19,  41,  57,  59,
};

#include "GF64_ADD.h"
#include "GF64_MUL.h"
#include "GF64_DIV.h"

#endif

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

#ifndef _GF16_
#define _GF16_

const int GF16_BINGF[16][4]=
{
  {0, 0, 0, 0},
  {1, 0, 0, 0},
  {0, 1, 0, 0},
  {0, 0, 1, 0},
  {0, 0, 0, 1},
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 1, 0, 1},
  {1, 0, 1, 0},
  {0, 1, 0, 1},
  {1, 1, 1, 0},
  {0, 1, 1, 1},
  {1, 1, 1, 1},
  {1, 0, 1, 1},
  {1, 0, 0, 1}
};

//
// DEST_NAT[ GF64_S2N[i] ] = SRC_SYMBOL[ i ]
//
const int GF16_S2N[16]=
{
   0,  8,  4,  2,  1, 12,  6,  3,
  13, 10,  5, 14,  7, 15, 11,  9
};

//
//
//
const int GF16_N2S[16]=
{
   0,  4,  3,  7,  2, 10,  6, 12,
   1, 15,  9, 14,  5,  8, 11, 13
};

#include "GF16_ADD.h"
#include "GF16_MUL.h"
#include "GF16_DIV.h"

#endif

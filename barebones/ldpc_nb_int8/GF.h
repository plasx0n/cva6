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

#ifndef _GF_DEF_
#define _GF_DEF_

#include "constantes.h"
// #include "../Constantes/encoder.h"

#if _GF_ == 16
	#include "./GF16/GF16.h"
	#define GF_BINGF				GF16_BINGF
	#define GF_S2N					GF16_S2N
	#define GF_N2S					GF16_N2S
	#define GF_ADD					GF16_ADD
	#define GF_MUL					GF16_MUL
	#define GF_MUL_simd				GF16_MUL_simd
	#define GF_MUL_natural_simd		GF16_MUL_natural_simd
	#define GF_DIV					GF16_DIV
	#define GF_DIV_simd				GF16_DIV_simd
	#define GF_DIV_natural_simd		GF16_DIV_natural_simd
	#define GF_ENC					GF16_ENC
	#define GF_PERM					GF16_PERM
#elif _GF_ == 32
	#include "./GF32/GF32.h"
	#define GF_BINGF				GF32_BINGF
	#define GF_S2N					GF32_S2N
	#define GF_N2S					GF32_N2S
	#define GF_ADD					GF32_ADD
	#define GF_MUL					GF32_MUL
	#define GF_MUL_simd				GF32_MUL_simd
	#define GF_MUL_natural_simd		GF32_MUL_natural_simd
	#define GF_DIV					GF32_DIV
	#define GF_DIV_simd				GF32_DIV_simd
	#define GF_DIV_natural_simd		GF32_DIV_natural_simd
	#define GF_ENC					GF32_ENC
	#define GF_PERM					GF32_PERM
#elif _GF_ == 64
	#include "./GF64/GF64.h"
	#define GF_BINGF				GF64_BINGF
	#define GF_S2N					GF64_S2N
	#define GF_N2S					GF64_N2S
	#define GF_ADD					GF64_ADD
	#define GF_MUL					GF64_MUL
	#define GF_MUL_simd				GF64_MUL_simd
	#define GF_MUL_natural_simd		GF64_MUL_natural_simd
	#define GF_DIV					GF64_DIV
	#define GF_DIV_simd				GF64_DIV_simd
	#define GF_DIV_natural_simd		GF64_DIV_natural_simd
	#define GF_ENC					GF64_ENC
	#define GF_PERM					GF64_PERM
#elif _GF_ == 128
	#include "./GF128/GF128.h"
	#define GF_BINGF				GF128_BINGF
	#define GF_S2N					GF128_S2N
	#define GF_N2S					GF128_N2S
	#define GF_ADD					GF128_ADD
	#define GF_MUL					GF128_MUL
	#define GF_MUL_simd				GF128_MUL_simd
	#define GF_MUL_natural_simd		GF128_MUL_natural_simd
	#define GF_DIV					GF128_DIV
	#define GF_DIV_simd				GF128_DIV_simd
	#define GF_DIV_natural_simd		GF128_DIV_natural_simd
	#define GF_ENC					GF128_ENC
	#define GF_PERM					GF128_PERM
#elif _GF_ == 256
	#include "./GF256/GF256.h"
	#define GF_BINGF				GF256_BINGF
	#define GF_S2N					GF256_S2N
	#define GF_N2S					GF256_N2S
	#define GF_ADD					GF256_ADD
	#define GF_MUL					GF256_MUL
	#define GF_MUL_simd				GF256_MUL_simd
	#define GF_MUL_natural_simd		GF256_MUL_natural_simd
	#define GF_DIV					GF256_DIV
	#define GF_DIV_simd				GF256_DIV_simd
	#define GF_DIV_natural_simd		GF256_DIV_natural_simd
	#define GF_ENC					GF256_ENC
	#define GF_PERM					GF256_PERM
#else
	#error "GF order is not managed currently"
#endif

#endif

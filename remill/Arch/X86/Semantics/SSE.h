/* Copyright 2016 Peter Goodman (peter@trailofbits.com), all rights reserved. */

#ifndef REMILL_ARCH_X86_SEMANTICS_SSE_H_
#define REMILL_ARCH_X86_SEMANTICS_SSE_H_

namespace {

// TODO(pag): Ignores distinction between quiet/signalling, and ordering.
template <typename S1, typename S2>
DEF_SEM(COMISS, S1 src1, S2 src2) {
  auto left = FExtractV32<0>(FReadV32(src1));
  auto right = FExtractV32<0>(FReadV32(src2));

  if (FCmpGt(left, right)) {
    Write(FLAG_ZF, false);
    Write(FLAG_PF, false);
    Write(FLAG_CF, false);
  } else if (FCmpLt(left, right)) {
    Write(FLAG_ZF, false);
    Write(FLAG_PF, false);
    Write(FLAG_CF, true);

  } else if (FCmpEq(left, right)) {
    Write(FLAG_ZF, true);
    Write(FLAG_PF, false);
    Write(FLAG_CF, false);

  } else {  // Unordered?
    Write(FLAG_ZF, true);
    Write(FLAG_PF, true);
    Write(FLAG_CF, true);
  }

  Write(FLAG_OF, false);
  Write(FLAG_SF, false);
  Write(FLAG_AF, false);
}


template <typename S1, typename S2>
DEF_SEM(COMISD, S1 src1, S2 src2) {
  auto left = FExtractV64<0>(FReadV64(src1));
  auto right = FExtractV64<0>(FReadV64(src2));

  if (FCmpGt(left, right)) {
    Write(FLAG_ZF, false);
    Write(FLAG_PF, false);
    Write(FLAG_CF, false);
  } else if (FCmpLt(left, right)) {
    Write(FLAG_ZF, false);
    Write(FLAG_PF, false);
    Write(FLAG_CF, true);

  } else if (FCmpEq(left, right)) {
    Write(FLAG_ZF, true);
    Write(FLAG_PF, false);
    Write(FLAG_CF, false);

  } else {  // Unordered?
    Write(FLAG_ZF, true);
    Write(FLAG_PF, true);
    Write(FLAG_CF, true);
  }

  Write(FLAG_OF, false);
  Write(FLAG_SF, false);
  Write(FLAG_AF, false);
}

}  // namespace

DEF_ISEL(COMISD_XMMsd_MEMsd) = COMISD<V128, MV64>;
DEF_ISEL(COMISD_XMMsd_XMMsd) = COMISD<V128, V128>;
DEF_ISEL(COMISS_XMMss_MEMss) = COMISS<V128, MV32>;
DEF_ISEL(COMISS_XMMss_XMMss) = COMISS<V128, V128>;

#if HAS_FEATURE_AVX
DEF_ISEL(VCOMISD_XMMq_MEMq) = COMISD<V128, MV64>;
DEF_ISEL(VCOMISD_XMMq_XMMq) = COMISD<V128, V128>;
DEF_ISEL(VCOMISS_XMMd_MEMd) = COMISS<V128, MV32>;
DEF_ISEL(VCOMISS_XMMd_XMMd) = COMISS<V128, V128>;
#endif  // HAS_FEATURE_AVX

DEF_ISEL(UCOMISD_XMMsd_MEMsd) = COMISD<V128, MV64>;
DEF_ISEL(UCOMISD_XMMsd_XMMsd) = COMISD<V128, V128>;
DEF_ISEL(UCOMISS_XMMss_MEMss) = COMISS<V128, MV32>;
DEF_ISEL(UCOMISS_XMMss_XMMss) = COMISS<V128, V128>;

#if HAS_FEATURE_AVX
DEF_ISEL(VUCOMISD_XMMdq_MEMq) = COMISD<V128, MV64>;
DEF_ISEL(VUCOMISD_XMMdq_XMMq) = COMISD<V128, V128>;
DEF_ISEL(VUCOMISS_XMMdq_MEMd) = COMISS<V128, MV32>;
DEF_ISEL(VUCOMISS_XMMdq_XMMd) = COMISS<V128, V128>;
#endif  // HAS_FEATURE_AVX


/*
88 FCOMI FCOMI_ST0_X87 X87_ALU X87 PPRO ATTRIBUTES: NOTSX
232 FCOMIP FCOMIP_ST0_X87 X87_ALU X87 PPRO ATTRIBUTES: NOTSX
1647 FUCOMI FUCOMI_ST0_X87 X87_ALU X87 PPRO ATTRIBUTES: NOTSX
1878 FUCOMIP FUCOMIP_ST0_X87 X87_ALU X87 PPRO ATTRIBUTES: NOTSX

4290 VCOMISD VCOMISD_XMMf64_XMMf64_AVX512 AVX512 AVX512EVEX AVX512F_SCALAR ATTRIBUTES: MXCSR SIMD_SCALAR
4291 VCOMISD VCOMISD_XMMf64_XMMf64_AVX512 AVX512 AVX512EVEX AVX512F_SCALAR ATTRIBUTES: MXCSR SIMD_SCALAR
4292 VCOMISD VCOMISD_XMMf64_MEMf64_AVX512 AVX512 AVX512EVEX AVX512F_SCALAR ATTRIBUTES: DISP8_SCALAR MXCSR SIMD_SCALAR
4293 VCOMISS VCOMISS_XMMf32_XMMf32_AVX512 AVX512 AVX512EVEX AVX512F_SCALAR ATTRIBUTES: MXCSR SIMD_SCALAR
4294 VCOMISS VCOMISS_XMMf32_XMMf32_AVX512 AVX512 AVX512EVEX AVX512F_SCALAR ATTRIBUTES: MXCSR SIMD_SCALAR
4295 VCOMISS VCOMISS_XMMf32_MEMf32_AVX512 AVX512 AVX512EVEX AVX512F_SCALAR ATTRIBUTES: DISP8_SCALAR MXCSR SIMD_SCALAR
5396 VUCOMISS VUCOMISS_XMMf32_XMMf32_AVX512 AVX512 AVX512EVEX AVX512F_SCALAR ATTRIBUTES: MXCSR SIMD_SCALAR
5397 VUCOMISS VUCOMISS_XMMf32_XMMf32_AVX512 AVX512 AVX512EVEX AVX512F_SCALAR ATTRIBUTES: MXCSR SIMD_SCALAR
5398 VUCOMISS VUCOMISS_XMMf32_MEMf32_AVX512 AVX512 AVX512EVEX AVX512F_SCALAR ATTRIBUTES: DISP8_SCALAR MXCSR SIMD_SCALAR
5430 VUCOMISD VUCOMISD_XMMf64_XMMf64_AVX512 AVX512 AVX512EVEX AVX512F_SCALAR ATTRIBUTES: MXCSR SIMD_SCALAR
5431 VUCOMISD VUCOMISD_XMMf64_XMMf64_AVX512 AVX512 AVX512EVEX AVX512F_SCALAR ATTRIBUTES: MXCSR SIMD_SCALAR
5432 VUCOMISD VUCOMISD_XMMf64_MEMf64_AVX512 AVX512 AVX512EVEX AVX512F_SCALAR ATTRIBUTES: DISP8_SCALAR MXCSR SIMD_SCALAR

 */

#endif  // REMILL_ARCH_X86_SEMANTICS_SSE_H_

/* Copyright 2016 Peter Goodman (peter@trailofbits.com), all rights reserved. */

/* NOTE:
 * YMM0 - YMM3 are filled will 0xFF.
 * YMM4 and on are filled with 0x0. */

TEST_BEGIN(MOVDQUv128v128_1to0, 1)
TEST_INPUTS(
    0)
    movdqu xmm4, xmm0
TEST_END

TEST_BEGIN(MOVDQUv128v128_0to1, 1)
TEST_INPUTS(
    0)
    movdqu xmm0, xmm4
TEST_END

#if HAS_FEATURE_AVX

TEST_BEGIN(VMOVDQUv128v128_1to0, 1)
TEST_INPUTS(
    0)
    vmovdqu xmm4, xmm0
TEST_END

TEST_BEGIN(VMOVDQUv128v128_0to1, 1)
TEST_INPUTS(
    0)
    vmovdqu xmm0, xmm4
TEST_END

TEST_BEGIN(VMOVDQUv256v256_1to0, 1)
TEST_INPUTS(
    0)
    vmovdqu ymm4, ymm0
TEST_END

TEST_BEGIN(VMOVDQUv256v256_0to1, 1)
TEST_INPUTS(
    0)
    vmovdqu ymm0, ymm4
TEST_END

#endif
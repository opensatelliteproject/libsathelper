/*
 * Operations.h
 *
 *  Created on: 08/01/2017
 *      Author: Lucas Teske
 */

#ifndef SRC_SIMD_OPERATIONS_H_
#define SRC_SIMD_OPERATIONS_H_

#if defined(_M_IX86) || defined(_M_X86) || defined(__i386__) || defined(__x86_64) || defined(_M_X64)
#define MEMORY_OP_X86
#if defined __GNUC__
#include <x86intrin.h>
#else
#include <immintrin.h>
#endif
#elif defined(__arm__) || defined(_M_ARM) || defined(__aarch64__)
#include <arm_neon.h> 
#define MEMORY_OP_ARM
#else
#define MEMORY_OP_GENERIC
#endif

#include <complex>

namespace SatHelper {

    class Operations {
    public:
        static void dotProduct(std::complex<float> *result, const std::complex<float> *input, const float *taps, unsigned int length);
    };

} /* namespace SatHelper */

#endif /* SRC_SIMD_OPERATIONS_H_ */

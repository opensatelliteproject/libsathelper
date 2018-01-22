/*
 * extensions.cpp
 *
 *  Created on: 16/09/2017
 *      Author: Lucas Teske
 */

#include <SatHelper/extensions.h>
#include <immintrin.h>

#define FMA3 (1 << 12)

void InitExtensions() {
    unsigned int eax, ebx, ecx, edx;
    eax = 0x01;

    __asm__ __volatile__(
                         "cpuid;"
                         : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
                         : "a"(eax)
                         );

    SatHelper::Extensions::hasFMA = ecx & FMA3;
}

namespace SatHelper {

bool Extensions::hasFMA = false;
bool Extensions::initialized = (InitExtensions(), true);

float Extensions::FMA(float a, float b, float c ) {
/*        float x = __builtin_fmaf(a, b, c); // a * b + c;
        float res[4];

        __m128 c0, c1, c2;

        res[0] = a;
        c0 = _mm_set1_ps(a);
        c1 = _mm_set1_ps(b);
        c2 = _mm_set1_ps(c);
        c0 = _mm_fmadd_ss (c0, c1, c2);
        _mm_store_ps(res, c0);
*/
        return hasFMA ? __builtin_fmaf(a, b, c) : a * b + c;
      }

} /* namespace SatHelper */

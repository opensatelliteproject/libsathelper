/*
 * extensions.h
 *
 *  Created on: 16/09/2017
 *      Author: Lucas Teske
 */

#ifndef INCLUDES_EXTENSIONS_H_
#define INCLUDES_EXTENSIONS_H_

#include <iostream>

namespace SatHelper {

    class Extensions {
    public:
      static bool hasFMA;
      static bool hasSSE;
      static bool hasSSE4;
      static bool hasAVX;
      static bool initialized;
      static inline float FMA(float a, float b, float c) {
        if (hasFMA) {
#ifdef _MSC_VER
          return fmaf(a, b, c); // Inline not supported for x64 in MSVC :(
#else
          __asm__ __volatile__( "vfmadd231ss %[a], %[b], %[c]" : [a] "+x" (a), [b] "+x" (b), [c] "+x" (c) : );
          return c;
#endif
        } else {
            return a * b + c;
        }
      }
    };

} /* namespace SatHelper */

#endif /* INCLUDES_EXTENSIONS_H_ */

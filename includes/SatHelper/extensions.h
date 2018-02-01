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
      static float FMA(float a, float b, float c);
    };

} /* namespace SatHelper */

#endif /* INCLUDES_EXTENSIONS_H_ */

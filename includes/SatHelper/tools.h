/*
 * tools.h
 *
 *  Created on: 07/11/2016
 *      Author: Lucas Teske
 */

#ifndef INCLUDES_TOOLS_H_
#define INCLUDES_TOOLS_H_

#include <sys/stat.h>
#include <complex>
#include <cmath>

// MSVC will optmize to FMA if /arch:AVX2 /GL /O2 /fp:fast
#ifndef _WIN32
#   if !defined(__FMA__) && defined(__AVX2__)
#       define __FMA__ 1
#   endif

#   if defined(FP_FAST_FMA)
#       define __FMA__ 1
#   endif
#endif

#ifdef _WIN32
#undef _WCHAR_H
#include <io.h>
#include <direct.h>
#include <time.h>
#undef __FMA__
#endif

namespace SatHelper {

    class Tools {
    public:
        inline static uint32_t swapEndianess(uint32_t num) {
            return ((num >> 24) & 0xff) | ((num << 8) & 0xff0000) | ((num >> 8) & 0xff00) | ((num << 24) & 0xff000000);
        }

        inline static uint32_t getTimestamp() {
            return (int) time(NULL);
        }

        inline static void makedir(const std::string &folder) {
            #if defined(__linux__) || defined(__APPLE__)
            mkdir(folder.c_str(), 0777);
            #else
            _mkdir(folder.c_str());
            #endif
        }

        inline static std::complex<float> phase2complex(float phase) {
            return std::complex<float>(sinf(phase), cosf(phase));
        }

        inline static float clip(float v, float max) {
            return 0.5f * (std::abs(v + max) - std::abs(v - max));
            /*
            // Old Version. See http://stackoverflow.com/questions/23474796/is-there-a-fast-fabsf-replacement-for-float-in-c
            float x1 = fabsf(v + max);
            float x2 = fabsf(v - max);
            x1 -= x2;
            return 0.5f * x1;
            */
        }
    };
}

#endif /* INCLUDES_TOOLS_H_ */

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
            mkdir(folder.c_str(), 0777);
        }

        inline static std::complex<float> phase2complex(float phase) {
            return std::complex<float>(sinf(phase), cosf(phase));
        }

        inline static float clip(float v, float max) {
            float x1 = fabsf(v + max);
            float x2 = fabsf(v - max);
            x1 -= x2;
            return 0.5 * x1;
        }
    };
}

#endif /* INCLUDES_TOOLS_H_ */

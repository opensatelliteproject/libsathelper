/*
 * filters.cpp
 *
 *  Created on: 24/12/2016
 *      Author: Lucas Teske
 *      Based on GNU Radio
 *      https://github.com/gnuradio/gnuradio/blob/master/gr-filter/lib/firdes.cc
 */

#include <dsp/filters.h>

#include <cmath>

namespace SatHelper {

    std::vector<float> RRC(double gain, double sampling_freq, double symbol_rate, double alpha, int ntaps) {
        double spb = sampling_freq / symbol_rate;
        double scale = 0;
        double x1, x2, x3, num, den;
        double xindx;

        ntaps |= 1;
        std::vector<float> taps(ntaps);

        for (int i = 0; i < ntaps; i++) {
            xindx = i - ntaps / 2;
            x1 = M_PI * xindx / spb;
            x2 = 4 * alpha * xindx / spb;
            x3 = x2 * x2 - 1;

            if (fabs(x3) >= 0.000001) {
                if (i != ntaps / 2) {
                    num = cos((1 + alpha) * x1) + sin((1 - alpha) * x1) / (4 * alpha * xindx / spb);
                } else {
                    num = cos((1 + alpha) * x1) + (1 - alpha) * M_PI / (4 * alpha);
                }
                den = x3 * M_PI;
            } else {
                if (alpha == 1) {
                    taps[i] = -1;
                    continue;
                }

                x3 = (1 - alpha) * x1;
                x2 = (1 + alpha) * x1;
                num = (sin(x2) * (1 + alpha) * M_PI - cos(x3) * ((1 - alpha) * M_PI * spb) / (4 * alpha * xindx)
                        + sin(x3) * spb * spb / (4 * alpha * xindx * xindx));
                den = -32 * M_PI * alpha * alpha * xindx / spb;
            }
            taps[i] = 4 * alpha * num / den;
            scale += taps[i];
        }

        for (int i = 0; i < ntaps; i++) {
            taps[i] = taps[i] * gain / scale;
        }

        return taps;
    }

} /* namespace SatHelper */

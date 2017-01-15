/*
 * filters.cpp
 *
 *  Created on: 24/12/2016
 *      Author: Lucas Teske
 *      Based on GNU Radio
 *      https://github.com/gnuradio/gnuradio/blob/master/gr-filter/lib/firdes.cc
 */

#define _USE_MATH_DEFINES
#include <dsp/filters.h>
#include <SatHelperException.h>
#include <cmath>

namespace SatHelper {

    double maxAttenuation(FFTWindows::WindowType type, double beta) {
        switch (type) {
            case (FFTWindows::HAMMING):
                return 53;
                break;
            case (FFTWindows::HANN):
                return 44;
                break;
            case (FFTWindows::BLACKMAN):
                return 74;
                break;
            case (FFTWindows::RECTANGULAR):
                return 21;
                break;
            case (FFTWindows::KAISER):
                return (beta / 0.1102 + 8.7);
                break;
            case (FFTWindows::BLACKMAN_HARRIS):
                return 92;
                break;
            case (FFTWindows::BARTLETT):
                return 27;
                break;
            case (FFTWindows::FLATTOP):
                return 93;
                break;
            default:
                throw SatHelperException("BUG! Unknown window type! Check code for bugs!");
        }
    }

    int computeNTaps(double sampling_freq, double transition_width, FFTWindows::WindowType window_type, double beta) {
        double a = maxAttenuation(window_type, beta);
        int ntaps = (int) (a * sampling_freq / (22.0 * transition_width));
        if ((ntaps & 1) == 0) {
            ntaps++;
        }

        return ntaps;
    }

    std::vector<float> Filters::RRC(double gain, double sampling_freq, double symbol_rate, double alpha, int ntaps) {
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
            if (taps[i] > 1) {
                taps[i] = 1;
            }
        }

        return taps;
    }

    std::vector<float> Filters::lowPass(double gain, double sampling_freq, double cutoff_freq, double transition_width, FFTWindows::WindowType window_type,
            double beta) {
        int ntaps = computeNTaps(sampling_freq, transition_width, window_type, beta);

        std::vector<float> taps(ntaps);
        std::vector<float> w = FFTWindows::MakeWindow(window_type, ntaps, beta);

        int M = (ntaps - 1) / 2;
        double fwT0 = 2 * M_PI * cutoff_freq / sampling_freq;

        for (int n = -M; n <= M; n++) {
            if (n == 0) {
                taps[n + M] = fwT0 / M_PI * w[n + M];
            } else {
                taps[n + M] = sin(n * fwT0) / (n * M_PI) * w[n + M];
            }
        }

        double fmax = taps[0 + M];
        for (int n = 1; n <= M; n++) {
            fmax += 2 * taps[n + M];
        }

        gain /= fmax;

        for (int i = 0; i < ntaps; i++) {
            taps[i] *= gain;
        }

        return taps;
    }

} /* namespace SatHelper */

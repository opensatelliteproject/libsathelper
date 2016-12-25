/*
 * fftwindows.cpp
 *
 *  Created on: 25/12/2016
 *      Author: Lucas Teske
 *      Based on GNU Radio FFT Filters
 *      https://github.com/gnuradio/gnuradio/blob/master/gr-fft/include/gnuradio/fft/window.h
 */

#include <cmath>
#include "dsp/fftwindows.h"
#include "SatHelperException.h"

namespace SatHelper {

    std::vector<float> coswindow(int ntaps, float c0, float c1, float c2) {
        std::vector<float> taps(ntaps);
        float M = static_cast<float>(ntaps - 1);

        for (int n = 0; n < ntaps; n++) {
            taps[n] = c0 - c1 * cosf((2.0f * M_PI * n) / M) + c2 * cosf((4.0f * M_PI * n) / M);
        }
        return taps;
    }

    std::vector<float> coswindow(int ntaps, float c0, float c1, float c2, float c3) {
        std::vector<float> taps(ntaps);
        float M = static_cast<float>(ntaps - 1);

        for (int n = 0; n < ntaps; n++) {
            taps[n] = c0 - c1 * cosf((2.0f * M_PI * n) / M) + c2 * cosf((4.0f * M_PI * n) / M) - c3 * cosf((6.0f * M_PI * n) / M);
        }
        return taps;
    }

    std::vector<float> coswindow(int ntaps, float c0, float c1, float c2, float c3, float c4) {
        std::vector<float> taps(ntaps);
        float M = static_cast<float>(ntaps - 1);

        for (int n = 0; n < ntaps; n++) {
            taps[n] = c0 - c1 * cosf((2.0f * M_PI * n) / M) + c2 * cosf((4.0f * M_PI * n) / M) - c3 * cosf((6.0f * M_PI * n) / M)
                    + c4 * cosf((8.0f * M_PI * n) / M);
        }
        return taps;
    }

#define IzeroEPSILON 1E-21
    double Izero(double x) {
        double sum, u, halfx, temp;
        int n;

        sum = u = n = 1;
        halfx = x / 2.0;
        do {
            temp = halfx / (double) n;
            n += 1;
            temp *= temp;
            u *= temp;
            sum += u;
        } while (u >= IzeroEPSILON * sum);
        return (sum);
    }
#undef IzeroEPSILON

    std::vector<float> FFTWindows::Rectangular(int ntaps) {
        std::vector<float> taps(ntaps);
        for (int n = 0; n < ntaps; n++) {
            taps[n] = 1;
        }
        return taps;
    }

    std::vector<float> FFTWindows::Hamming(int ntaps) {
        std::vector<float> taps(ntaps);
        float M = static_cast<float>(ntaps - 1);

        for (int n = 0; n < ntaps; n++) {
            taps[n] = 0.54 - 0.46 * cos((2 * M_PI * n) / M);
        }
        return taps;
    }

    std::vector<float> FFTWindows::Hanning(int ntaps) {
        std::vector<float> taps(ntaps);
        float M = static_cast<float>(ntaps - 1);

        for (int n = 0; n < ntaps; n++) {
            taps[n] = 0.5 - 0.5 * cos((2 * M_PI * n) / M);
        }
        return taps;
    }

    std::vector<float> FFTWindows::Blackman(int ntaps) {
        return coswindow(ntaps, 0.34401, 0.49755, 0.15844);
    }

    std::vector<float> FFTWindows::BlackmanHarris(int ntaps, int atten) {
        switch (atten) {
            case (61):
                return coswindow(ntaps, 0.42323, 0.49755, 0.07922);
            case (67):
                return coswindow(ntaps, 0.44959, 0.49364, 0.05677);
            case (74):
                return coswindow(ntaps, 0.40271, 0.49703, 0.09392, 0.00183);
            case (92):
                return coswindow(ntaps, 0.35875, 0.48829, 0.14128, 0.01168);
            default:
                throw SatHelperException("BlackmanHarris attenuation must be one of the following values: 61, 67, 74, or 92");
        }
    }

    std::vector<float> FFTWindows::FlatTop(int ntaps) {
        double scale = 4.63867;
        return coswindow(ntaps, 1.0 / scale, 1.93 / scale, 1.29 / scale, 0.388 / scale, 0.028 / scale);
    }

    std::vector<float> FFTWindows::Kaiser(int ntaps, double beta) {
        if (beta < 0) {
            throw SatHelperException("Kaiser Window beta cannot be negative.");
        }

        std::vector<float> taps(ntaps);

        double IBeta = 1.0 / Izero(beta);
        double inm1 = 1.0 / ((double) (ntaps - 1));
        double temp;

        for (int i = 0; i < ntaps; i++) {
            temp = 2 * i * inm1 - 1;
            taps[i] = Izero(beta * sqrt(1.0 - temp * temp)) * IBeta;
        }
        return taps;
    }

    std::vector<float> FFTWindows::Bartlett(int ntaps) {
        std::vector<float> taps(ntaps);
        float M = static_cast<float>(ntaps - 1);

        for (int n = 0; n < ntaps / 2; n++) {
            taps[n] = 2 * n / M;
        }

        for (int n = ntaps / 2; n < ntaps; n++) {
            taps[n] = 2 - 2 * n / M;
        }

        return taps;
    }

    std::vector<float> FFTWindows::MakeWindow(WindowType type, int ntaps, float beta) {
        switch (type) {
            case HAMMING:
                return Hamming(ntaps);
            case HANN:
                return Hanning(ntaps);
            case BLACKMAN:
                return Blackman(ntaps);
            case RECTANGULAR:
                return Rectangular(ntaps);
            case KAISER:
                return Kaiser(ntaps, beta);
            case BLACKMAN_HARRIS:
                return BlackmanHarris(ntaps);
            case BARTLETT:
                return Bartlett(ntaps);
            case FLATTOP:
                return FlatTop(ntaps);
            default:
                throw SatHelperException("BUG! There is no such window type! Please check code for bugs.");
        }
    }
} /* namespace SatHelper */

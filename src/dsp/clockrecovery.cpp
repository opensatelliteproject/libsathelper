/*
 * clockrecovery.cpp
 *
 *  Created on: 22/12/2016
 *      Author: Lucas Teske
 *      Based on GNU Radio Implementation
 */

#include "dsp/clockrecovery.h"
#include "SatHelperException.h"
#include "tools.h"
#include <cstring>
#include <iostream>
#include <cmath>

#define MIN_SAMPLE_HISTORY 8

namespace SatHelper {
    static const int FUDGE = 16;

    ClockRecovery::ClockRecovery(float omega, float gainOmega, float mu, float gainMu, float omegaRelativeLimit) :
            mu(mu), omega(omega), gainOmega(gainOmega), omegaRelativeLimit(omegaRelativeLimit), gainMu(gainMu), interp(new MMSEFirInterpolator()), p_2T(0, 0), p_1T(
                    0, 0), p_0T(0, 0), c_2T(0, 0), c_1T(0, 0), c_0T(0, 0) {

        if (omega <= 0.0) {
            throw SatHelperException("ClockRecovery Rate must be higher than 0.");
        }

        if (gainMu < 0 || gainOmega < 0) {
            throw SatHelperException("ClockRecovery Gains should be positive.");
        }

        SetOmega(omega);

        sampleHistory = MIN_SAMPLE_HISTORY;

        for (int i = 0; i < sampleHistory; i++) {
            samples.push_back(std::complex<float>(0, 0));
        }
    }

    ClockRecovery::~ClockRecovery() {
        delete interp;
    }

    std::complex<float> ClockRecovery::slicer_0deg(std::complex<float> sample) {
        float real = 0, imag = 0;

        if (sample.real() > 0) {
            real = 1;
        }

        if (sample.imag() > 0) {
            imag = 1;
        }

        return std::complex<float>(real, imag);
    }

    std::complex<float> ClockRecovery::slicer_45deg(std::complex<float> sample) {
        float real = -1, imag = -1;
        if (sample.real() > 0) {
            real = 1;
        }

        if (sample.imag() > 0) {
            imag = 1;
        }

        return std::complex<float>(real, imag);
    }

    int ClockRecovery::Work(std::complex<float> *rInput, std::complex<float> *output, int length) {

        int ii = 0; // input index
        int oo = 0; // output index
        int ni = sampleHistory + length - interp->GetNTaps() - FUDGE;  // don't use more input than this
        //
        float mm_val = 0;
        std::complex<float> u, x, y;

        if (samples.size() < (unsigned int) (sampleHistory + length)) {
            samples.resize(sampleHistory + length);
        }

        memcpy(&samples[sampleHistory], rInput, length * sizeof(std::complex<float>));

        while (oo < length && ii < ni) {
            p_2T = p_1T;
            p_1T = p_0T;
            p_0T = interp->interpolate(&samples[ii], mu);

            c_2T = c_1T;
            c_1T = c_0T;
            c_0T = slicer_0deg(p_0T);

            x = (c_0T - c_2T) * conj(p_1T);
            y = (p_0T - p_2T) * conj(c_1T);
            u = y - x;
            mm_val = u.real();
            output[oo++] = p_0T;

            mm_val = Tools::clip(mm_val, 1.0);
            omega = omega + gainOmega * mm_val;
            omega = omegaMid + Tools::clip(omega - omegaMid, omegaLim);

            mu = mu + omega + gainMu * mm_val;
            ii += (int) floor(mu);
            mu -= floor(mu);

            if (ii < 0) {
                ii = 0;
            }
        }

        sampleHistory = sampleHistory + length - ii;

        memmove(&samples[0], &samples[ii], sampleHistory * sizeof(std::complex<float>));

        return oo;
    }

} /* namespace SatHelper */

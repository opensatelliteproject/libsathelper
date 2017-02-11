/*
 * clockrecovery.cpp
 *
 *  Created on: 22/12/2016
 *      Author: Lucas Teske
 *      Based on GNU Radio Implementation
 */

#include <dsp/clockrecovery.h>
#include <exceptions/SatHelperException.h>
#include <tools.h>
#include <cstring>
#include <iostream>
#include <cmath>

#define MIN_SAMPLE_HISTORY 3

namespace SatHelper {
    static const int FUDGE = 16;

    ClockRecovery::ClockRecovery(float omega, float gainOmega, float mu, float gainMu, float omegaRelativeLimit) :
            mu(mu), omega(omega), gainOmega(gainOmega), omegaRelativeLimit(omegaRelativeLimit), gainMu(gainMu), consumed(0),
            p_2T(0, 0), p_1T(0, 0), p_0T(0, 0), c_2T(0, 0), c_1T(0, 0), c_0T(0, 0) {

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

        std::cout << "MM - Omega: " << this->omega << " Gain Omega: " << this->gainOmega << " Mu: " << this->mu << " Gain Mu: " << this->gainMu
                << " Omega Relative Limit: " << this->omegaRelativeLimit << std::endl;
    }

    ClockRecovery::~ClockRecovery() {

    }

    std::complex<float> ClockRecovery::slicer(std::complex<float> sample) {
        return std::complex<float>(sample.real() > 0 ? 1.f : 0.f, sample.imag() > 0 ? 1.f : 0.f);
    }

    int ClockRecovery::InternalWork(std::complex<float> *rInput, std::complex<float> *output, int inputLen, int outputLen) {
        int inputIndex = 0;
        int outputIndex = 0;
        int numberInput = inputLen - interp.GetNTaps() - FUDGE;
        float mm_val = 0;
        std::complex<float> u, x, y;

        while (outputIndex < outputLen && inputIndex < numberInput) {
            p_2T = p_1T;
            p_1T = p_0T;
            p_0T = interp.interpolate(&rInput[inputIndex], mu);

            c_2T = c_1T;
            c_1T = c_0T;
            c_0T = slicer(p_0T);

            x = (c_0T - c_2T) * conj(p_1T);
            y = (p_0T - p_2T) * conj(c_1T);
            u = y - x;
            mm_val = u.real();
            output[outputIndex++] = p_0T;

            mm_val = Tools::clip(mm_val, 1.0);
            omega = omega + gainOmega * mm_val;
            omega = omegaMid + Tools::clip(omega - omegaMid, omegaLim);

            mu = mu + omega + gainMu * mm_val;
            inputIndex += (int) floor(mu);
            mu -= floor(mu);

            if (inputIndex < 0) {
                inputIndex = 0;
            }
        }

        consumed = inputIndex;

        if (consumed > inputLen) {
            std::cerr << "Consumed more samples than input." << std::endl;
        }

        return outputIndex;
    }

    int ClockRecovery::Work(std::complex<float> *rInput, std::complex<float> *output, int length) {
        // Manage the history
        int totalLength = sampleHistory + length;
        if (samples.size() < (unsigned int) (totalLength)) {
            samples.resize(totalLength);
        }

        memcpy(&samples[sampleHistory], rInput, length * sizeof(std::complex<float>));

        int symbols = InternalWork(&samples[0], output, totalLength, length);

        sampleHistory = totalLength - consumed;

        if (sampleHistory < MIN_SAMPLE_HISTORY) {
            sampleHistory = MIN_SAMPLE_HISTORY;
        }

        memmove(&samples[0], &samples[totalLength - sampleHistory], (sampleHistory) * sizeof(std::complex<float>));

        return symbols;
    }

} /* namespace SatHelper */

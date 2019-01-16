/*
 * CostasLoop.cpp
 *
 *  Created on: 22/12/2016
 *      Author: Lucas Teske
 *      Based on GNU Radio Implementation
 */

#include <dsp/costasloop.h>
#include <tools.h>
#include <exceptions/SatHelperException.h>
#include <extensions.h>
#include <iostream>

namespace SatHelper {
    CostasLoop::CostasLoop(float loopBandwidth, int order, float maxRelativeFrequency, float minRelativeFrequency) : ControlLoop(loopBandwidth, maxRelativeFrequency, minRelativeFrequency), order(order), error(0) {
        switch (order) {
            case 2:
                std::cout << "BPSK Costas Loop" << std::endl;
                break;

            case 4:
                std::cout << "QPSK Costas Loop" << std::endl;
                break;

            case 8:
                std::cout << "8PSK Costas Loop" << std::endl;
                break;

            default:
                throw SatHelperException("Costas Loop order must be 2, 4 or 8.");
                break;
        }
    }
    CostasLoop::CostasLoop(float loopBandwidth, int order) : CostasLoop(loopBandwidth, order, 1.0, -1.0) {}

    CostasLoop::~CostasLoop() {

    }

    void CostasLoop::Work(std::complex<float> *input, std::complex<float> *output, float *frequencyDeviation, int length) {
        std::complex<float> nco_out;

        float n_r, n_i, o_r, o_i;
        for (int i = 0; i < length; i++) {
            // region nco_out = Tools::phase2complex(-phase);
            n_r = cosf(-phase);
            n_i = sinf(-phase);
            // endregion
            // region output[i] = input[i] * nco_out;
            o_r = Extensions::FMA(input[i].real(), n_r, -input[i].imag() * n_i);
            o_i = Extensions::FMA(input[i].real(), n_i, input[i].imag() * n_r);
            output[i].real(o_r);
            output[i].imag(o_i);
            // endregion
            // region error = (this->*PhaseDetector)(output[i]);
            if (order == 2) {
                error = PhaseDetector2(output[i]);
            } else if (order == 4) {
                error = PhaseDetector4(output[i]);
            } else if (order == 8) {
                error = PhaseDetector8(output[i]);
            }
            // endregion
            error = Tools::clip(error, 1.0);
            AdvanceLoop(error);
            PhaseWrap();
            FrequencyLimit();
            if (frequencyDeviation != NULL) {
                frequencyDeviation[i] = this->freq;
            }
        }
    }

    void CostasLoop::Work(std::complex<float> *input, std::complex<float> *output, int length) {
        this->Work(input, output, NULL, length);
    }

    void CostasLoop::Reset() {
        ControlLoop::Reset();
        error = 0;
    }

} /* namespace SatHelper */

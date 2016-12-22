/*
 * CostasLoop.cpp
 *
 *  Created on: 22/12/2016
 *      Author: Lucas Teske
 *      Based on GNU Radio Implementation
 */

#include <dsp/costasloop.h>
#include <tools.h>
#include <SatHelperException.h>

namespace SatHelper {

    CostasLoop::CostasLoop(float loop_bw, int order) :
            ControlLoop(loop_bw, 1.0, -1.0), order(order), error(0), noise(1.0), PhaseDetector(NULL) {
        switch (order) {
            case 2:
                PhaseDetector = &CostasLoop::PhaseDetector2;
                break;

            case 4:
                PhaseDetector = &CostasLoop::PhaseDetector4;
                break;

            case 8:
                PhaseDetector = &CostasLoop::PhaseDetector8;
                break;

            default:
                throw SatHelperException("Costas Loop order must be 2, 4 or 8.");
                break;
        }
    }

    CostasLoop::~CostasLoop() {

    }

    float CostasLoop::PhaseDetector2(std::complex<float> sample) const {
        return (sample.real() * sample.imag());
    }

    float CostasLoop::PhaseDetector4(std::complex<float> sample) const {
        return ((sample.real() > 0 ? 1.0 : -1.0) * sample.imag() - (sample.imag() > 0 ? 1.0 : -1.0) * sample.real());
    }

    /*
     * This technique splits the 8PSK constellation into 2 squashed
     * QPSK constellations, one when I is larger than Q and one
     * where Q is larger than I. The error is then calculated
     * proportionally to these squashed constellations by the const
     * K = sqrt(2)-1.
     * The signal magnitude must be > 1 or K will incorrectly bias
     * the error value.
     * Ref: Z. Huang, Z. Yi, M. Zhang, K. Wang, "8PSK demodulation for
     * new generation DVB-S2", IEEE Proc. Int. Conf. Communications,
     * Circuits and Systems, Vol. 2, pp. 1447 - 1450, 2004.
     */
    float CostasLoop::PhaseDetector8(std::complex<float> sample) const {
        float K = (sqrt(2.0) - 1);
        if (fabsf(sample.real()) >= fabsf(sample.imag())) {
            return ((sample.real() > 0 ? 1.0 : -1.0) * sample.imag() - (sample.imag() > 0 ? 1.0 : -1.0) * sample.real() * K);
        } else {
            return ((sample.real() > 0 ? 1.0 : -1.0) * sample.imag() * K - (sample.imag() > 0 ? 1.0 : -1.0) * sample.real());
        }
    }

    void CostasLoop::Work(std::complex<float> *input, std::complex<float> *output, int length) {
        std::complex<float> nco_out;

        for (int i = 0; i < length; i++) {
            nco_out = Tools::phase2complex(-phase);
            output[i] = input[i] * nco_out;

            error = (this->*PhaseDetector)(output[i]);
            error = Tools::clip(error, 1.0);

            AdvanceLoop(error);
            PhaseWrap();
            FrequencyLimit();
        }
    }

} /* namespace SatHelper */

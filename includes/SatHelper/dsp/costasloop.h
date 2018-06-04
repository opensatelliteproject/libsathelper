/*
 * CostasLoop.h
 *
 *  Created on: 22/12/2016
 *      Author: Lucas Teske
 *      Based on GNU Radio Implementation
 */

#ifndef INCLUDES_DSP_COSTASLOOP_H_
#define INCLUDES_DSP_COSTASLOOP_H_

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <complex>
#include <SatHelper/dsp/controlloop.h>

namespace SatHelper {

    class CostasLoop: public ControlLoop {
    private:
        int order;
        float error;

        inline float PhaseDetector2(std::complex<float> sample) const {
            return sample.real() * sample.imag();
        }

        inline float PhaseDetector4(std::complex<float> sample) const {
            return ((sample.real() > 0 ? 1.0f : -1.0f) * sample.imag() - (sample.imag() > 0 ? 1.0f : -1.0f) * sample.real());
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
        inline float PhaseDetector8(std::complex<float> sample) const {
            float K = (float)(sqrt(2.0) - 1);
            if (fabsf(sample.real()) >= fabsf(sample.imag())) {
                return ((sample.real() > 0 ? 1.0f : -1.0f) * sample.imag() - (sample.imag() > 0 ? 1.0f : -1.0f) * sample.real() * K);
            } else {
                return ((sample.real() > 0 ? 1.0f : -1.0f) * sample.imag() * K - (sample.imag() > 0 ? 1.0f : -1.0f) * sample.real());
            }
        }

    public:
        CostasLoop(float loopBandwidth, int order);
        CostasLoop(float loopBandwidth, int order, float maxRelativeFrequency, float minRelativeFrequency);
        virtual ~CostasLoop();

        inline float GetError() const {
            return error;
        }

        inline float GetFrequency() const {
            return freq;
        }

        inline float GetFrequencyHz() const {
            return freq / ( 2 * 3.141592653589793 );
        }

        void Reset();

        void Work(std::complex<float> *input, std::complex<float> *output, int length);
        void Work(std::complex<float> *input, std::complex<float> *output, float *frequencyDeviation, int length);
    };

} /* namespace SatHelper */

#endif /* INCLUDES_DSP_COSTASLOOP_H_ */

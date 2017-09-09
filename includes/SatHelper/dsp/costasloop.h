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

    class CostasLoop: ControlLoop {
    private:
        float error;

        float PhaseDetector2(std::complex<float> sample) const;
        float PhaseDetector4(std::complex<float> sample) const;
        float PhaseDetector8(std::complex<float> sample) const;

        float (CostasLoop::*PhaseDetector)(std::complex<float> sample) const;

    public:
        CostasLoop(float loopBandwidth, int order);
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

/*
 * CostasLoop.h
 *
 *  Created on: 22/12/2016
 *      Author: Lucas Teske
 */

#ifndef INCLUDES_DSP_COSTASLOOP_H_
#define INCLUDES_DSP_COSTASLOOP_H_

#include <complex>

#include "controlloop.h"

namespace SatHelper {

    class CostasLoop: ControlLoop {
    private:
        int order;
        float error, noise;

        float PhaseDetector2(std::complex<float> sample) const;
        float PhaseDetector4(std::complex<float> sample) const;
        float PhaseDetector8(std::complex<float> sample) const;

        float (CostasLoop::*PhaseDetector)(std::complex<float> sample) const;

    public:
        CostasLoop(float loop_bw, int order);
        virtual ~CostasLoop();

        inline float GetError() const {
            return error;
        }

        void Work(std::complex<float> *input, std::complex<float> *output, int length);
    };

} /* namespace SatHelper */

#endif /* INCLUDES_DSP_COSTASLOOP_H_ */

/*
 * controlloop.h
 *
 *  Created on: 22/12/2016
 *      Author: Lucas Teske
 *      Based on GNU Radio Implementation
 */

#ifndef INCLUDES_DSP_CONTROLLOOP_H_
#define INCLUDES_DSP_CONTROLLOOP_H_

#define _USE_MATH_DEFINES
#include <cmath>
#define M_TWOPI (2.0f*M_PI)

namespace SatHelper {

    class ControlLoop {
    protected:
        float phase, freq, max_freq, min_freq, damping, loop_bw, alpha, beta;

    public:
        ControlLoop(float loop_bw, float max_freq, float min_freq);
        virtual ~ControlLoop();

        void UpdateGains();
        void AdvanceLoop(float error);
        virtual void SetLoopBandwidth(float bw);
        void SetDampingFactor(float df);
        void SetAlpha(float alpha);
        void SetBeta(float beta);
        void SetFrequency(float freq);

        inline void SetPhase(float phase) {
            this->phase = phase;
            PhaseWrap();
        }

        inline void GetMaxFrequency(float freq) {
            max_freq = freq;
        }

        inline void GetMinFrequency(float freq) {
            min_freq = freq;
        }

        inline float GetLoopBandwidth() const {
            return loop_bw;
        }

        inline float GetDampingFactor() const {
            return damping;
        }

        inline float GetAlpha() const {
            return alpha;
        }

        inline float GetBeta() const {
            return beta;
        }

        inline float GetFrequency() const {
            return freq;
        }

        inline float GetPhase() const {
            return phase;
        }

        inline float GetMaxFrequency() const {
            return max_freq;
        }

        inline float GetMinFrequency() const {
            return min_freq;
        }

        inline void FrequencyLimit() {
            if (freq > max_freq) {
                freq = max_freq;
            } else if (freq < min_freq) {
                freq = min_freq;
            }
        }

        inline void PhaseWrap() {
            while (phase > M_TWOPI) {
                phase -= M_TWOPI;
            }
            while (phase < -M_TWOPI) {
                phase += M_TWOPI;
            }
        }

        // TODO: May use GNURadio tanh LUT
    };

} /* namespace SatHelper */

#endif /* INCLUDES_DSP_CONTROLLOOP_H_ */

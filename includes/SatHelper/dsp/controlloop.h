/*
 * controlloop.h
 *
 *  Created on: 22/12/2016
 *      Author: Lucas Teske
 *      Based on GNU Radio Implementation
 */

#ifndef INCLUDES_DSP_CONTROLLOOP_H_
#define INCLUDES_DSP_CONTROLLOOP_H_

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <cmath>
#define M_TWOPI (2.0f*M_PI)

namespace SatHelper {

    class ControlLoop {
    protected:
        float phase, freq, maxRelFreq, minRelFreq, dampingFactor, loopBandwidth, alpha, beta;

    public:
        ControlLoop(float loopBandwidth, float maxRelativeFrequency, float minRelativeFrequency);
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

        inline void GetRelativeMaxFrequency(float freq) {
            maxRelFreq = freq;
        }

        inline void GetRelativeMinFrequency(float freq) {
            minRelFreq = freq;
        }

        inline float GetLoopBandwidth() const {
            return loopBandwidth;
        }

        inline float GetDampingFactor() const {
            return dampingFactor;
        }

        inline float GetAlpha() const {
            return alpha;
        }

        inline float GetBeta() const {
            return beta;
        }

        inline float GetRelativeFrequency() const {
            return freq;
        }

        inline float GetPhase() const {
            return phase;
        }

        inline float GetMaxRelativeFrequency() const {
            return maxRelFreq;
        }

        inline float GetMinRelativeFrequency() const {
            return minRelFreq;
        }

        inline void FrequencyLimit() {
            if (freq > maxRelFreq) {
                freq = maxRelFreq;
            } else if (freq < minRelFreq) {
                freq = minRelFreq;
            }
        }

        inline void PhaseWrap() {
            while (phase > M_TWOPI) {
                phase -= (float)M_TWOPI;
            }
            while (phase < -M_TWOPI) {
                phase += (float)M_TWOPI;
            }
        }
    };

} /* namespace SatHelper */

#endif /* INCLUDES_DSP_CONTROLLOOP_H_ */

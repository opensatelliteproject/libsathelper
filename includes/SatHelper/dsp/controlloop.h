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
#define M_TWOPI 6.28318530717958647692f
#define M_ONE_OVER_2PI 0.15915494309189533577
#define M_MINUS_TWO_PI -6.28318530717958647692

// MSVC will optmize to FMA if /arch:AVX2 /GL /O2 /fp:fast
#ifndef _WIN32
#   if !defined(__FMA__) && defined(__AVX2__)
#       define __FMA__ 1
#   endif

#   if defined(FP_FAST_FMA)
#       define __FMA__ 1
#   endif
#endif


#ifdef _WIN32
#   undef __FMA__
#endif



#include <SatHelper/exceptions/SatHelperException.h>
#include <SatHelper/extensions.h>

namespace SatHelper {

    class ControlLoop {
    protected:
        float phase, freq, maxRelFreq, minRelFreq, dampingFactor, loopBandwidth, alpha, beta;

    public:
        ControlLoop(float loopBandwidth, float maxRelativeFrequency, float minRelativeFrequency);
        virtual ~ControlLoop();

        inline void SetLoopBandwidth(float bw) {
            if (bw < 0) {
                throw SatHelperException("Control Loop Bandwidth needs to be higher than or equal to 0.");
            }

            loopBandwidth = bw;
            UpdateGains();
        }

        inline void SetDampingFactor(float df) {
            if (df <= 0) {
                throw SatHelperException("Control Loop Bandwidth needs to be higher than 0.");
            }

            dampingFactor = df;
            UpdateGains();
        }

        inline void SetAlpha(float alpha) {
            if (alpha < 0 || alpha > 1.0) {
                throw SatHelperException("Control Loop Alpha needs to be between 0 and 1.");
            }
            this->alpha = alpha;
        }

        inline void SetBeta(float beta) {
            if (beta < 0 || beta > 1.0) {
                throw SatHelperException("Control Loop Beta needs to be between 0 and 1.");
            }

            this->beta = beta;
        }

        inline void SetFrequency(float freq) {
            if (freq > maxRelFreq) {
                this->freq = minRelFreq;
            } else if (freq < minRelFreq) {
                this->freq = maxRelFreq;
            } else {
                this->freq = freq;
            }
        }

        inline void Reset() {
            phase = 0;
            freq = 0;
            dampingFactor = sqrt(2.0f) / 2.0f;
            SetLoopBandwidth(loopBandwidth);
        }

        inline void UpdateGains() {
            float denom = (1.0f + 2.0f * dampingFactor * loopBandwidth + loopBandwidth * loopBandwidth);
            alpha = (4 * dampingFactor * loopBandwidth) / denom;
            beta = (4 * loopBandwidth * loopBandwidth) / denom;
        }

        inline void SetPhase(float phase) {
            this->phase = phase;
            PhaseWrap();
        }

        inline void AdvanceLoop(float error) {
            freq = Extensions::FMA(beta, error, freq);
            phase = phase + Extensions::FMA(alpha, error, freq);
            /*
            #if defined(__FMA__)
            freq = __builtin_fmaf(beta, error, freq);
            phase = phase + __builtin_fmaf(alpha, error, freq);
            #else
            freq = beta * error + freq;
            phase = phase + alpha * error + freq;
            #endif
            */
        }

        inline void SetRelativeMaxFrequency(float freq) {
            maxRelFreq = freq;
        }

        inline void SetRelativeMinFrequency(float freq) {
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
            if ((phase > M_TWOPI) || (phase < M_MINUS_TWO_PI)) {
                #if defined(__FMA__)
                phase = __builtin_fmaf(phase, M_ONE_OVER_2PI, -(float)((int)(phase * M_ONE_OVER_2PI)));
                #else
                phase = phase * M_ONE_OVER_2PI - (float)((int)(phase * M_ONE_OVER_2PI));
                #endif
                phase = phase * M_TWOPI;
            }
            /*
            // OLD Version
            while (phase > M_TWOPI) {
                phase -= (float)M_TWOPI;
            }
            while (phase < -M_TWOPI) {
                phase += (float)M_TWOPI;
            }
            */
        }
    };

} /* namespace SatHelper */

#endif /* INCLUDES_DSP_CONTROLLOOP_H_ */

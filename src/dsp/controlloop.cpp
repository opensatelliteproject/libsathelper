/*
 * controlloop.cpp
 *
 *  Created on: 22/12/2016
 *      Author: Lucas Teske
 */

#include <dsp/controlloop.h>
#include <cmath>
#include <SatHelperException.h>

#define M_TWOPI (2.0f*M_PI)

namespace SatHelper {

    ControlLoop::ControlLoop(float loop_bw, float max_freq, float min_freq) :
            phase(0), freq(0), max_freq(max_freq), min_freq(min_freq) {
        damping = sqrt(2.0f) / 2.0f;
        SetLoopBandwidth(loop_bw);
    }

    ControlLoop::~ControlLoop() {

    }

    void ControlLoop::UpdateGains() {
        float denom = (1.0 + 2.0 * damping * loop_bw + loop_bw * loop_bw);
        alpha = (4 * damping * loop_bw) / denom;
        beta = (4 * loop_bw * loop_bw) / denom;
    }

    void ControlLoop::AdvanceLoop(float error) {
        freq = freq + beta * error;
        phase = phase + freq + alpha * error;
    }

    void ControlLoop::SetLoopBandwidth(float bw) {
        if (bw < 0) {
            throw SatHelperException("Control Loop Bandwidth needs to be higher than or equal to 0.");
        }

        loop_bw = bw;
        UpdateGains();
    }

    void ControlLoop::SetDampingFactor(float df) {
        if (df <= 0) {
            throw SatHelperException("Control Loop Bandwidth needs to be higher than 0.");
        }

        damping = df;
        UpdateGains();
    }

    void ControlLoop::SetAlpha(float alpha) {
        if (alpha < 0 || alpha > 1.0) {
            throw SatHelperException("Control Loop Alpha needs to be between 0 and 1.");
        }
        this->alpha = alpha;
    }

    void ControlLoop::SetBeta(float beta) {
        if (beta < 0 || beta > 1.0) {
            throw SatHelperException("Control Loop Beta needs to be between 0 and 1.");
        }

        this->beta = beta;
    }

    void ControlLoop::SetFrequency(float freq) {
        if (freq > max_freq) {
            this->freq = min_freq;
        } else if (freq < min_freq) {
            this->freq = max_freq;
        } else {
            this->freq = freq;
        }
    }


} /* namespace SatHelper */

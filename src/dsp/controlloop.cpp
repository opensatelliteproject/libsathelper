/*
 * controlloop.cpp
 *
 *  Created on: 22/12/2016
 *      Author: Lucas Teske
 *      Based on GNU Radio Implementation
 */

#include <dsp/controlloop.h>
#include <cmath>
#include <exceptions/SatHelperException.h>

#define M_TWOPI (2.0f*M_PI)

namespace SatHelper {

    ControlLoop::ControlLoop(float loop_bw, float max_freq, float min_freq) :
            phase(0), freq(0), maxRelFreq(max_freq), minRelFreq(min_freq) {
        dampingFactor = sqrt(2.0f) / 2.0f;
        SetLoopBandwidth(loop_bw);
    }

    ControlLoop::~ControlLoop() {

    }

    void ControlLoop::UpdateGains() {
        float denom = (1.0 + 2.0 * dampingFactor * loopBandwidth + loopBandwidth * loopBandwidth);
        alpha = (4 * dampingFactor * loopBandwidth) / denom;
        beta = (4 * loopBandwidth * loopBandwidth) / denom;
    }

    void ControlLoop::AdvanceLoop(float error) {
        freq = freq + beta * error;
        phase = phase + freq + alpha * error;
    }

    void ControlLoop::SetLoopBandwidth(float bw) {
        if (bw < 0) {
            throw SatHelperException("Control Loop Bandwidth needs to be higher than or equal to 0.");
        }

        loopBandwidth = bw;
        UpdateGains();
    }

    void ControlLoop::SetDampingFactor(float df) {
        if (df <= 0) {
            throw SatHelperException("Control Loop Bandwidth needs to be higher than 0.");
        }

        dampingFactor = df;
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
        if (freq > maxRelFreq) {
            this->freq = minRelFreq;
        } else if (freq < minRelFreq) {
            this->freq = maxRelFreq;
        } else {
            this->freq = freq;
        }
    }


} /* namespace SatHelper */

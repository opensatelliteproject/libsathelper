/*
 * controlloop.cpp
 *
 *  Created on: 22/12/2016
 *      Author: Lucas Teske
 *      Based on GNU Radio Implementation
 */

#include <dsp/controlloop.h>
#include <cmath>

namespace SatHelper {

    ControlLoop::ControlLoop(float loop_bw, float max_freq, float min_freq) :
            phase(0), freq(0), maxRelFreq(max_freq), minRelFreq(min_freq) {
        dampingFactor = sqrt(2.0f) / 2.0f;
        SetLoopBandwidth(loop_bw);
    }

    ControlLoop::~ControlLoop() {

    }
} /* namespace SatHelper */

/*
 * filters.h
 *
 *  Created on: 24/12/2016
 *      Author: Lucas Teske
 */

#ifndef INCLUDES_DSP_FILTERS_H_
#define INCLUDES_DSP_FILTERS_H_

#include <vector>
#include "dsp/fftwindows.h"

namespace SatHelper {

    class Filters {
    public:
        static std::vector<float> RRC(double gain, double sampling_freq, double symbol_rate, double alpha, int ntaps);
        static std::vector<float> lowPass(double gain, double sampling_freq, double cutoff_freq, double transition_width, FFTWindows::WindowType window_type, double beta);
    };

} /* namespace SatHelper */

#endif /* INCLUDES_DSP_FILTERS_H_ */

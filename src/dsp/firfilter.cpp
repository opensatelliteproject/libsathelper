/*
 * firfilter.cpp
 *
 *  Created on: 25/12/2016
 *      Author: Lucas Teske
 */

#include "dsp/firfilter.h"
#include <cstring>


namespace SatHelper {

    FirFilter::FirFilter(unsigned int decimation, const std::vector<float> &taps) : decimation(decimation), kernel(taps) {
        sampleHistory = taps.size();
        for (unsigned int i=0; i<sampleHistory; i++) {
            samples.push_back(std::complex<float>(0, 0));
        }
    }

    FirFilter::~FirFilter() {

    }

    int FirFilter::Work(std::complex<float> *input, std::complex<float> *output, int length) {

        if (samples.size() < length * decimation + sampleHistory) {
            samples.resize(length * decimation + sampleHistory);
        }

        memcpy(&samples[sampleHistory], input, length * sizeof(std::complex<float>));

        if (decimation > 1) {
            kernel.FilterDecimating(&samples[0], output, length, decimation);
        } else {
            kernel.Filter(&samples[0], output, length);
        }

        memcpy(&samples[0], &input[length * decimation-sampleHistory], sampleHistory * sizeof(std::complex<float>));

        return length;
    }

} /* namespace SatHelper */

/*
 * firfilter.h
 *
 *  Created on: 25/12/2016
 *      Author: Lucas Teske
 */

#ifndef SRC_DSP_FIRFILTER_H_
#define SRC_DSP_FIRFILTER_H_

#include <complex>
#include "firkernel.h"

namespace SatHelper {

    class FirFilter {
    private:
        unsigned int decimation;
        FirKernel kernel;
        std::vector<std::complex<float>> samples;
        unsigned int sampleHistory;

    public:
        FirFilter(unsigned int decimation, const std::vector<float> &taps);
        virtual ~FirFilter();
        int Work(std::complex<float> *input, std::complex<float> *output, int length);
    };

} /* namespace SatHelper */

#endif /* SRC_DSP_FIRFILTER_H_ */

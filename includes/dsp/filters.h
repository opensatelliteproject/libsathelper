/*
 * filters.h
 *
 *  Created on: 24/12/2016
 *      Author: Lucas Teske
 */

#ifndef INCLUDES_DSP_FILTERS_H_
#define INCLUDES_DSP_FILTERS_H_

#include <vector>

namespace SatHelper {

    class Filters {
    public:
        static std::vector<float> RRC(double gain, double sampling_freq, double symbol_rate, double alpha, int ntaps);

    };

} /* namespace SatHelper */

#endif /* INCLUDES_DSP_FILTERS_H_ */

/*
 * firinterpolator.h
 *
 *  Created on: 22/12/2016
 *      Author: Lucas Teske
 *      Based on GNU Radio Implementation
 */

#ifndef SRC_DSP_FIRINTERPOLATOR_H_
#define SRC_DSP_FIRINTERPOLATOR_H_

#include <complex>
#include "firkernel.h"

namespace SatHelper {

    class MMSEFirInterpolator {
    protected:
      std::vector<FirKernel *> filters;

    public:
        MMSEFirInterpolator();
        virtual ~MMSEFirInterpolator();

        unsigned GetNTaps() const;
        unsigned GetNSteps() const;

        std::complex<float> interpolate(const std::complex<float> input[], float mu) const;
    };

} /* namespace SatHelper */

#endif /* SRC_DSP_FIRINTERPOLATOR_H_ */

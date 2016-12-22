/*
 * firkernel.h
 *
 *  Created on: 22/12/2016
 *      Author: Lucas Teske
 *      Based on GNU Radio Implementation
 */

#ifndef SRC_DSP_FIRKERNEL_H_
#define SRC_DSP_FIRKERNEL_H_

#include <vector>
#include <algorithm>
#include <complex>

namespace SatHelper {

    class FirKernel {
    protected:
        std::vector<float> taps;
        unsigned int ntaps;
        float **aligned_taps;
        std::complex<float> *output;
        int align;
        int naligned;

    public:
        FirKernel(int decimation, const std::vector<float> &taps);
        virtual ~FirKernel();

        void SetTaps(const std::vector<float> &taps);

        std::complex<float> filter(const std::complex<float> input[]);
        void Filter(std::complex<float> output[], const std::complex<float> input[], unsigned long n);
        void FilterDecimating(std::complex<float> output[], const std::complex<float> input[], unsigned long n, unsigned int decimate);

        inline void UpdateTap(float t, unsigned int index) {
            taps[index] = t;
            for (int i = 0; i < naligned; i++) {
                aligned_taps[i][i + index] = t;
            }
        }

        inline std::vector<float> GetTaps() const {
            std::vector<float> t = taps;
            std::reverse(t.begin(), t.end());
            return t;
        }

        inline unsigned int GetNTaps() const {
            return ntaps;
        }

    };

} /* namespace SatHelper */

#endif /* SRC_DSP_FIRKERNEL_H_ */

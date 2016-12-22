/*
 * firkernel.cpp
 *
 *  Created on: 22/12/2016
 *      Author: Lucas Teske
 *      Based on GNU Radio Implementation
 */

#include "dsp/firkernel.h"
#include <volk/volk.h>
#include <cstring>

namespace SatHelper {

    FirKernel::FirKernel(int decimation, const std::vector<float> &taps) {
        align = volk_get_alignment();
        naligned = std::max((size_t) 1, align / sizeof(std::complex<float>));
        aligned_taps = NULL;
        SetTaps(taps);
        output = (std::complex<float>*) volk_malloc(1 * sizeof(std::complex<float>), align);
    }

    FirKernel::~FirKernel() {
        if (aligned_taps != NULL) {
            for (int i = 0; i < naligned; i++) {
                volk_free (aligned_taps[i]);
            }
            std::free(aligned_taps);
            aligned_taps = NULL;
        }

        volk_free (output);
    }

    void FirKernel::SetTaps(const std::vector<float> &taps) {
        if (aligned_taps != NULL) {
            for (int i = 0; i < naligned; i++) {
                volk_free (aligned_taps[i]);
            }
            std::free(aligned_taps);
            aligned_taps = NULL;
        }

        ntaps = (int) taps.size();
        this->taps = taps;
        std::reverse(this->taps.begin(), this->taps.end());

        aligned_taps = (float**) malloc(naligned * sizeof(float*));
        for (int i = 0; i < naligned; i++) {
            aligned_taps[i] = (float*) volk_malloc((ntaps + naligned - 1) * sizeof(float), align);
            memset(aligned_taps[i], 0, sizeof(float) * (ntaps + naligned - 1));
            for (unsigned int j = 0; j < ntaps; j++) {
                aligned_taps[i][i + j] = taps[j];
            }
        }
    }

    std::complex<float> FirKernel::filter(const std::complex<float> input[]) {
        const std::complex<float> *ar = (std::complex<float> *) ((size_t) input & ~(align - 1));
        unsigned al = input - ar;

        volk_32fc_32f_dot_prod_32fc_a(output, ar, aligned_taps[al], (ntaps + al));
        return *output;
    }

    void FirKernel::Filter(std::complex<float> output[], const std::complex<float> input[], unsigned long n) {
        for (unsigned long i = 0; i < n; i++) {
            output[i] = filter(&input[i]);
        }
    }

    void FirKernel::FilterDecimating(std::complex<float> output[], const std::complex<float> input[], unsigned long n, unsigned int decimate) {
        unsigned long j = 0;
        for (unsigned long i = 0; i < n; i++) {
            output[i] = filter(&input[j]);
            j += decimate;
        }
    }

} /* namespace SatHelper */

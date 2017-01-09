/*
 * firkernel.cpp
 *
 *  Created on: 22/12/2016
 *      Author: Lucas Teske
 *      Based on GNU Radio Implementation
 */

#include "dsp/firkernel.h"
#include <cstring>
#include "SIMD/MemoryOp.h"
#include "SIMD/Operations.h"

namespace SatHelper {

    FirKernel::FirKernel(const std::vector<float> &taps) {
        align = MemoryOp::getAligment();
        naligned = std::max((size_t) 1, align / sizeof(std::complex<float>));
        aligned_taps = NULL;
        SetTaps(taps);
        output = (std::complex<float>*) MemoryOp::alignedAlloc(1 * sizeof(std::complex<float>), align);
    }

    FirKernel::~FirKernel() {
        if (aligned_taps != NULL) {
            for (int i = 0; i < naligned; i++) {
                MemoryOp::free(aligned_taps[i]);
            }
            std::free(aligned_taps);
            aligned_taps = NULL;
        }

        MemoryOp::free(output);
    }

    void FirKernel::SetTaps(const std::vector<float> &taps) {
        if (aligned_taps != NULL) {
            for (int i = 0; i < naligned; i++) {
                MemoryOp::free(aligned_taps[i]);
            }
            std::free(aligned_taps);
            aligned_taps = NULL;
        }

        ntaps = (int) taps.size();
        this->taps = taps;
        std::reverse(this->taps.begin(), this->taps.end());

        aligned_taps = (float**) malloc(naligned * sizeof(float*));
        for (int i = 0; i < naligned; i++) {
            aligned_taps[i] = (float*) MemoryOp::alignedAlloc((ntaps + naligned - 1) * sizeof(float), align);
            memset(aligned_taps[i], 0, sizeof(float) * (ntaps + naligned - 1));
            for (unsigned int j = 0; j < ntaps; j++) {
                aligned_taps[i][i + j] = taps[j];
            }
        }
    }

    std::complex<float> FirKernel::filter(const std::complex<float> *input) {
        const std::complex<float> *ar = (std::complex<float> *) ((size_t) input & ~(align - 1));
        unsigned al = input - ar;

        Operations::dotProduct(output, ar, aligned_taps[al], (ntaps + al));
        return *output;
    }

    void FirKernel::Filter(const std::complex<float> *input, std::complex<float> *output, unsigned long n) {
        for (unsigned long i = 0; i < n; i++) {
            output[i] = filter(&input[i]);
        }
    }

    void FirKernel::FilterDecimating(const std::complex<float> *input, std::complex<float> *output, unsigned long n, unsigned int decimate) {
        unsigned long j = 0;
        for (unsigned long i = 0; i < n; i++) {
            output[i] = filter(&input[j]);
            j += decimate;
        }
    }

} /* namespace SatHelper */

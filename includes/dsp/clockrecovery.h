/*
 * clockrecovery.h
 *
 *  Created on: 22/12/2016
 *      Author: Lucas Teske
 *      Based on GNU Radio Implementation
 */

#ifndef SRC_DSP_CLOCKRECOVERY_H_
#define SRC_DSP_CLOCKRECOVERY_H_

#include <complex>
#include "firinterpolator.h"

namespace SatHelper {

    class ClockRecovery {
    private:
        float mu, omega, gainOmega, omegaRelativeLimit, omegaMid, omegaLim, gainMu;

        std::complex<float> lastSample;
        MMSEFirInterpolator *interp;

        bool d_verbose;

        std::complex<float> p_2T, p_1T, p_0T;
        std::complex<float> c_2T, c_1T, c_0T;
        std::vector<std::complex<float>> samples;

        std::complex<float> slicer_0deg(std::complex<float> sample);
        std::complex<float> slicer_45deg(std::complex<float> sample);

    public:
        ClockRecovery(float omega, float gain_omega, float mu, float gain_mu, float omega_relative_limit);
        virtual ~ClockRecovery();

        int Work(std::complex<float> *input, std::complex<float> *output, int length);

        inline float GetMu() const {
            return mu;
        }

        inline float GetOmega() const {
            return omega;
        }

        inline float GetGainMu() const {
            return gainMu;
        }

        inline float GetGainOmega() const {
            return gainOmega;
        }

        inline void SetGainMu(float gain_mu) {
            this->gainMu = gain_mu;
        }

        inline void SetGainOmega(float gain_omega) {
            this->gainOmega = gain_omega;
        }

        inline void SetMu(float mu) {
            this->mu = mu;
        }

        inline void SetOmega(float omega) {
            this->omega = omega;
            this->omegaMid = omega;
            this->omegaLim = this->omegaRelativeLimit * omega;
        }
    };

} /* namespace SatHelper */

#endif /* SRC_DSP_CLOCKRECOVERY_H_ */

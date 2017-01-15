/*
 * agc.h
 *
 *  Created on: 24/12/2016
 *      Author: Lucas Teske
 *      Based on GNU Radio
 */

#ifndef SRC_DSP_AGC_H_
#define SRC_DSP_AGC_H_

namespace SatHelper {

    class AGC {
    protected:
        float rate;
        float reference;
        float gain;
        float maxGain;

    public:
        AGC(float rate = 1e-4, float reference = 1.0, float gain = 1.0, float maxGain = 0.0) :
                rate(rate), reference(reference), gain(gain), maxGain(maxGain) {
        }

        inline float GetRate() const {
            return rate;
        }

        inline float GetReference() const {
            return reference;
        }

        inline float GetGain() const {
            return gain;
        }

        inline float GetMaxGain() const {
            return maxGain;
        }

        inline void SetRate(float rate) {
            this->rate = rate;
        }

        inline void SetReference(float reference) {
            this->reference = reference;
        }

        inline void SetGain(float gain) {
            this->gain = gain;
        }

        inline void SetMaxGain(float max_gain) {
            this->maxGain = max_gain;
        }

        inline std::complex<float> scale(std::complex<float> input) {
            std::complex<float> output = input * gain;

            gain += this->rate * (reference - sqrt(output.real() * output.real() + output.imag() * output.imag()));
            if (maxGain > 0.0 && gain > maxGain) {
                gain = maxGain;
            }
            return output;
        }

        inline void scaleN(std::complex<float> *output, const std::complex<float> *input, unsigned n) {
            for (unsigned i = 0; i < n; i++) {
                output[i] = scale(input[i]);
            }
        }

        inline void Work(std::complex<float> *input, std::complex<float> *output, int length) {
            scaleN(output, input, length);
        }
    };

} /* namespace SatHelper */

#endif /* SRC_DSP_AGC_H_ */

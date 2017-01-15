/*
 * fftwindows.h
 *
 *  Created on: 25/12/2016
 *      Author: Lucas Teske
 *      Based on GNU Radio
 */

#ifndef SRC_DSP_FFTWINDOWS_H_
#define SRC_DSP_FFTWINDOWS_H_

#include <vector>

namespace SatHelper {

    class FFTWindows {
    public:
        enum WindowType {
            HAMMING = 0, HANN = 1, BLACKMAN = 2, RECTANGULAR = 3, KAISER = 4, BLACKMAN_HARRIS = 5, BARTLETT = 6, FLATTOP = 7
        };

        static std::vector<float> Rectangular(int ntaps);
        static std::vector<float> Hamming(int ntaps);
        static std::vector<float> Hanning(int ntaps);
        static std::vector<float> Blackman(int ntaps);
        static std::vector<float> BlackmanHarris(int ntaps, int atten = 92);
        static std::vector<float> FlatTop(int ntaps);
        static std::vector<float> Kaiser(int ntaps, double beta);
        static std::vector<float> Bartlett(int ntaps);

        static std::vector<float> MakeWindow(WindowType type, int ntaps, float beta);
    };

} /* namespace SatHelper */

#endif /* SRC_DSP_FFTWINDOWS_H_ */

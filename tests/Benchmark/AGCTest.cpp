/*
 * AGCTest.cpp
 *
 *  Created on: 15/09/2017
 *      Author: Lucas Teske
 */

#include "AGCTest.h"
#include <complex>
#include <vector>
#include <random>
#include <iostream>
#include <cmath>
#include <SatHelper/sathelper.h>


#define AGC_RATE 0.01f
#define AGC_REFERENCE 0.5f
#define AGC_GAIN 1.f
#define AGC_MAX_GAIN 4000
#define BUFFSIZE 16384

// Samples per symbol, to evaluate required BW
#define SPS 3.f

#define LRIT_SYMBOLRATE 293883
#define HRIT_SYMBOLRATE 927000
#define GRB_SYMBOLRATE 8665938

#define ITERATIONS 80


using namespace std;

namespace SatHelper {

    bool AGCTest::RunTest() {
      std::cerr << c_verbose << "Benchmark Params: " << tcendl;
      std::cerr << c_info << "    -- AGC_RATE: " << tcarg(AGC_RATE) << tcendl;
      std::cerr << c_info << "    -- AGC_REFERENCE: " << tcarg(AGC_REFERENCE) << tcendl;
      std::cerr << c_info << "    -- AGC_REFERENCE: " << tcarg(AGC_REFERENCE) << tcendl;
      std::cerr << c_info << "    -- AGC_GAIN: " << tcarg(AGC_GAIN) << tcendl;
      std::cerr << c_info << "    -- AGC_MAX_GAIN: " << tcarg(AGC_MAX_GAIN) << tcendl;
      std::cerr << c_info << "    -- ITERATIONS: " << tcarg(ITERATIONS) << tcendl;

      AGC agc(AGC_RATE, AGC_REFERENCE, AGC_GAIN, AGC_MAX_GAIN);

      std::cerr << c_verbose << "Initializing Sample Buffer" << tcendl;
      std::complex<float> *buffer0 = new std::complex<float>[BUFFSIZE];
      std::complex<float> *buffer1 = new std::complex<float>[BUFFSIZE];

      // Random Number
      random_device rd;
      default_random_engine e2(rd());
      normal_distribution<> dist(-1, 1);

      // Fill with random numbers
      for (unsigned int i=0; i < BUFFSIZE; i++) {
          buffer0[i] = complex<float>(dist(e2), dist(e2));
      }


      std::cerr << c_verbose << "Performing Benchmark" << tcendl;
      std::chrono::time_point<std::chrono::system_clock> start, end;
      float averageTime = 0;
      auto elapsed = end - start;

      for (int i = 0; i < ITERATIONS; i++) {
            start = std::chrono::system_clock::now();
            agc.Work(buffer0, buffer1, BUFFSIZE);
            end = std::chrono::system_clock::now();
            elapsed = end - start;
            averageTime += std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
      }

      averageTime /= ITERATIONS;

      float maxHritSps = 1e3 / (averageTime / (1.f * BUFFSIZE)); // In msps
      cerr << c_info << "    -- HRIT AGC Took " << tcarg(averageTime) << c_info << " ns to finish." << tcendl;
      cerr << c_info << "    -- Maximum Usable SampleRate in this settings: " << tcarg(maxHritSps) << c_info << " msps." << tcendl;

      if (maxHritSps > (LRIT_SYMBOLRATE * SPS) / 1e6) {
            cerr << c_info << c_bold << "    -- Good for LRIT     \\o/" << tcendl;
      } else {
            cerr << c_error << c_bold << "    -- No good for LRIT  :(" << tcendl;
      }

      if (maxHritSps > (HRIT_SYMBOLRATE * SPS) / 1e6) {
            cerr << c_info << c_bold << "    -- Good for HRIT     \\o/" << tcendl;
      } else {
            cerr << c_error << c_bold << "    -- No good for HRIT  :(" << tcendl;
      }

      if (maxHritSps > (GRB_SYMBOLRATE * SPS) / 1e6) {
            cerr << c_info << c_bold << "    -- Good for GRB      \\o/" << tcendl;
      } else {
            cerr << c_error << c_bold << "    -- No good for GRB   :(" << tcendl;
      }

      delete buffer0;
      delete buffer1;
      return true;
    }

} /* namespace SatHelper */

RUNTEST(AGCTest)

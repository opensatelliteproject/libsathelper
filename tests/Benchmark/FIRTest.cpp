/*
 * FIRTest.cpp
 *
 *  Created on: 05/01/2017
 *      Author: Lucas Teske
 */

#include "FIRTest.h"
#include <complex>
#include <vector>
#include <random>
#include <iostream>
#include <cmath>
#include <SatHelper/sathelper.h>

#define BUFFSIZE 16384
#define SAMPRATE 1e9
#define RRCALPHA 0.5
#define NUMTAPS 512
#define SYMBRATE 100000
// Samples per symbol, to evaluate required BW
#define SPS 3.f

#define LRIT_SYMBOLRATE 293883
#define HRIT_SYMBOLRATE 927000
#define GRB_SYMBOLRATE 8665938

#define ITERATIONS 20


using namespace std;

namespace SatHelper {

    bool FIRTest::RunTest() {
      std::cerr << c_verbose << "Benchmark Params: " << tcendl;
      std::cerr << c_info << "    -- BUFFSIZE: " << tcarg(BUFFSIZE) << tcendl;
      std::cerr << c_info << "    -- SAMPRATE: " << tcarg(SAMPRATE) << tcendl;
      std::cerr << c_info << "    -- RRCALPHA: " << tcarg(RRCALPHA) << tcendl;
      std::cerr << c_info << "    -- NUMTAPS:  " << tcarg(NUMTAPS)  << tcendl;
      std::cerr << c_info << "    -- SYMBRATE: " << tcarg(SYMBRATE) << tcendl;
      std::cerr << c_info << "    -- ITERATIONS: " << tcarg(ITERATIONS) << tcendl;

      std::cerr << c_verbose << "Initializing RRC Filter (" << tcarg(SAMPRATE) << " " << tcarg(SYMBRATE) << " " << tcarg(RRCALPHA) << " " << tcarg(NUMTAPS) << c_verbose << ")" << tcendl;
      std::vector<float> rrcTaps = Filters::RRC(1, SAMPRATE, SYMBRATE, RRCALPHA, NUMTAPS);
      FirFilter rrcFilter(1, rrcTaps);
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
            rrcFilter.Work(buffer0, buffer1, BUFFSIZE);
            end = std::chrono::system_clock::now();
            elapsed = end - start;
            averageTime += std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
      }
      auto ticksns = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
      cerr << c_info << "    -- FIR Took " << tcarg(ticksns) << c_info << " ns to finish." << tcendl;
      auto ticksus = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
      cerr << c_info << "    -- FIR Took " << tcarg(ticksus) << c_info << " us to finish." << tcendl;
      auto ticksms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
      cerr << c_info << "    -- FIR Took " << tcarg(ticksms) << c_info << " ms to finish." << tcendl;

      cerr << tcendl;

      cerr << c_verbose << "Testing LRIT/HRIT Settings (" << tcarg("alpha = 0.5, taps = 63, runs = " << ITERATIONS) << c_verbose << ")" << tcendl;

      std::vector<float> hritTaps = Filters::RRC(1, 2560000, 980000, 0.5, 63);
      FirFilter hritRRC(1, hritTaps);

      averageTime = 0;

      for (int i = 0; i < ITERATIONS; i++) {
            start = std::chrono::system_clock::now();
            hritRRC.Work(buffer0, buffer1, BUFFSIZE);
            end = std::chrono::system_clock::now();
            elapsed = end - start;
            averageTime += std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
      }

      averageTime /= ITERATIONS;

      float maxHritSps = 1e3 / (averageTime / (1.f * BUFFSIZE)); // In msps
      cerr << c_info << "    -- HRIT FIR Took " << tcarg(averageTime) << c_info << " ns to finish." << tcendl;
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

RUNTEST(FIRTest)

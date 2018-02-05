/*
 * ViterbiTest.cpp
 *
 *  Created on: 15/09/2017
 *      Author: Lucas Teske
 */

#include "ViterbiTest.h"
#include <complex>
#include <vector>
#include <random>
#include <iostream>
#include <cmath>
#include <SatHelper/sathelper.h>


#define FRAMEBYTES 2048
#define FRAMEBITS (FRAMEBYTES * 8)

// Samples per symbol, to evaluate required BW
#define SPS 3.f

#define LRIT_SYMBOLRATE 293883
#define HRIT_SYMBOLRATE 927000
#define GRB_SYMBOLRATE 8665938

#define ITERATIONS 80


using namespace std;

namespace SatHelper {

    unsigned char symbols[8 * 2 * (FRAMEBYTES + 6)];
    unsigned char bits[FRAMEBYTES];
    unsigned char output[FRAMEBYTES];

    bool ViterbiTest::RunTest() {
      std::cerr << c_verbose << "Benchmark Params: " << tcendl;
      std::cerr << c_info << "    -- FRAMEBYTES: " << tcarg(FRAMEBYTES) << tcendl;
      std::cerr << c_info << "    -- FRAMEBITS: " << tcarg(FRAMEBITS) << tcendl;
      std::cerr << c_info << "    -- ITERATIONS: " << tcarg(ITERATIONS) << tcendl;

      std::uniform_int_distribution<int> signalDist(0, 255);
      Viterbi27 viterbi(FRAMEBITS+6);

      random_device rd;
      mt19937 e2(rd());

      for (int i=0; i<FRAMEBYTES; i++) {
          bits[i] = signalDist(e2) & 0xFF;
      }


      viterbi.encode(bits, symbols);

      std::cerr << c_verbose << "Performing Benchmark" << tcendl;
      std::chrono::time_point<std::chrono::system_clock> start, end;
      float averageTime = 0;
      auto elapsed = end - start;

      for (int i = 0; i < ITERATIONS; i++) {
            start = std::chrono::system_clock::now();
            viterbi.decode(symbols, output);
            end = std::chrono::system_clock::now();
            elapsed = end - start;
            averageTime += std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
      }

      averageTime /= ITERATIONS;

      float maxHritSps = 1e3 / (averageTime / (1.f * FRAMEBITS)); // In msps
      cerr << c_info << "    -- HRIT Viterbi Took " << tcarg(averageTime) << c_info << " ns to finish." << tcendl;
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

      cerr << c_warn << c_bold << "    -- Not applicable for GRB      ._." << tcendl;

      return true;
    }

} /* namespace SatHelper */

RUNTEST(ViterbiTest)

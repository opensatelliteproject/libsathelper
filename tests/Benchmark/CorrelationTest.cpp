/*
 * CorrelationTest.cpp
 *
 *  Created on: 05/01/2017
 *      Author: Lucas Teske
 */

#include "CorrelationTest.h"
#include <complex>
#include <vector>
#include <random>
#include <iostream>
#include <cmath>
#include <cstring>
#include <SatHelper/sathelper.h>

#define TEST_SIZE 1024

using namespace std;

namespace SatHelper {

    static const uint32_t word0 = 0xDEADBEEF;
    static const uint32_t word1 = 0xAAC00FFE;
    static const uint64_t word2 = 0xAABBCCDDEEFF0055;
    static const uint32_t correlationPositionWord0 = 100;
    static const uint32_t correlationPositionWord1 = 500;
    static const uint32_t correlationPositionWord2 = 800;

    static const uint32_t correlationPosition[3] = {
        correlationPositionWord0,
        correlationPositionWord1,
        correlationPositionWord2
    };

    static const uint8_t testData[TEST_SIZE] = {
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128,   0,   0, 255,   0,   0,   0,   0, 255,   0, 255,   0, 255,
          0,   0, 255,   0,   0, 255,   0,   0,   0,   0,   0, 255,   0,   0,   0, 255,
          0,   0,   0,   0, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128,   0, 255,   0, 255,   0, 255,   0, 255,   0,   0, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,   0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0, 255, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
          0, 255,   0, 255,   0, 255,   0, 255,   0, 255,   0,   0,   0, 255,   0,   0,
          0,   0, 255, 255,   0,   0, 255, 255,   0,   0, 255,   0,   0,   0, 255,   0,
          0,   0,   0, 255,   0,   0,   0, 255,   0,   0,   0,   0,   0,   0,   0,   0,
        255, 255, 255, 255, 255, 255, 255, 255, 255,   0, 255,   0, 255,   0, 255,   0,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128
    };

    bool CorrelationTest::RunTest() {
      std::random_device rd;
      std::mt19937 e2(rd());
      std::normal_distribution<> dist(-50, 50);
      uint8_t data[TEST_SIZE];
      SatHelper::Correlator correlator[3];

      std::memcpy(data, testData, TEST_SIZE);

      correlator[0].addWord(word0);
      correlator[1].addWord(word1);
      correlator[2].addWord(word2);

      cerr << c_verbose << "Benchmark Params: " << tcendl;
      cerr << c_info << "   -- TEST_SIZE: " << c_bold << TEST_SIZE << tcendl;

      auto averageTime = 0.f;
      std::chrono::time_point<std::chrono::system_clock> start, end;
      auto elapsed = end - start;
      float elapsedTmp;
      cerr << c_verbose << "Benchmarking with plain data." << tcendl;
      for (int i=0; i<3; i++) {
          start = std::chrono::system_clock::now();
          correlator[i].correlate(data, TEST_SIZE);
          end = std::chrono::system_clock::now();
          elapsed = end - start;
          elapsedTmp = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
          averageTime += elapsedTmp;
          cerr << c_info << "   -- Run " << tcarg(i) << c_info << " took " << tcarg(elapsedTmp) << c_info << " ns to run." << tcendl;
          if (correlator[i].getHighestCorrelationPosition() != correlationPosition[i]) {
              cerr << c_error << "     -- Word " << tcarg(i) << c_error
                << " correlation in wrong position. Expected " << tcarg(correlationPosition[i]) << c_error
                << " got " << tcarg(correlator[i].getHighestCorrelationPosition()) << c_error << tcendl;
          }
          cerr << c_info << "     -- Correlation position for word " << tcarg(i) << c_info << ": " << tcarg(correlator[i].getHighestCorrelationPosition()) << c_info << " with " << tcarg(correlator[i].getHighestCorrelation()) << tcendl;
      }
      averageTime /= 3;
      cerr << c_info << "   -- Average Time: " << tcarg(averageTime) << c_info << " ns" << tcendl;

      cerr << c_verbose << "Benchmarking with gaussian noise." << tcendl;
      for (int i=0; i<TEST_SIZE; i++) {
          int32_t v = data[i];
          v += std::round(dist(e2));
          v = v > 0xFF ? 0xFF : v;
          v = v < 0 ? 0 : v;
          data[i] = v & 0xFF;
      }

      averageTime = 0.f;
      for (int i=0; i<3; i++) {
          start = std::chrono::system_clock::now();
          correlator[i].correlate(data, TEST_SIZE);
          end = std::chrono::system_clock::now();
          elapsed = end - start;
          elapsedTmp = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
          averageTime += elapsedTmp;
          cerr << c_info << "   -- Run " << tcarg(i) << c_info << " took " << tcarg(elapsedTmp) << c_info << " ns to run." << tcendl;
          if (correlator[i].getHighestCorrelationPosition() != correlationPosition[i]) {
              cerr << c_error << "     -- Word " << tcarg(i) << c_error
                << " correlation in wrong position. Expected " << tcarg(correlationPosition[i]) << c_error
                << " got " << tcarg(correlator[i].getHighestCorrelationPosition()) << c_error << tcendl;
          }
          cerr << c_info << "     -- Correlation position for word " << tcarg(i) << c_info << ": " << tcarg(correlator[i].getHighestCorrelationPosition()) << c_info << " with " << tcarg(correlator[i].getHighestCorrelation()) << tcendl;
      }

      averageTime /= 3;
      cerr << c_info << "   -- Average Time: " << tcarg(averageTime) << c_info << " ns" << tcendl;

      return true;
    }

} /* namespace SatHelper */

RUNTEST(CorrelationTest)

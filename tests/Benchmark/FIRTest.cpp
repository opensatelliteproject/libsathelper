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

using namespace std;

namespace SatHelper {

    bool FIRTest::RunTest() {
      std::cerr << "Benchmark Params: " << endl;
      std::cerr << "   BUFFSIZE: " << BUFFSIZE << endl;
      std::cerr << "   SAMPRATE: " << SAMPRATE << endl;
      std::cerr << "   RRCALPHA: " << RRCALPHA << endl;
      std::cerr << "   NUMTAPS: " << NUMTAPS << endl;
      std::cerr << "   SYMBRATE: " << SYMBRATE << endl;

      std::cerr << "Initializing RRC Filter (" << SAMPRATE << " " << SYMBRATE << " " << RRCALPHA << " " << NUMTAPS << ")" << std::endl;
      std::vector<float> rrcTaps = Filters::RRC(1, SAMPRATE, SYMBRATE, RRCALPHA, NUMTAPS);
      FirFilter rrcFilter(1, rrcTaps);
      std::cerr << "Initializing Sample Buffer" << std::endl;
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

      std::cerr << "Performing Benchmark" << std::endl;

      auto start = std::chrono::system_clock::now();
      rrcFilter.Work(buffer0, buffer1, BUFFSIZE);
      auto end = std::chrono::system_clock::now();
      auto elapsed = end - start;
      auto ticksns = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
      cerr << "FIR Took " << ticksns << " ns to finish." << endl;
      auto ticksus = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
      cerr << "FIR Took " << ticksus << " us to finish." << endl;
      auto ticksms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
      cerr << "FIR Took " << ticksms << " ms to finish." << endl;


      delete buffer0;
      return true;
    }

} /* namespace SatHelper */

RUNTEST(FIRTest)

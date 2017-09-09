/*
 * CostasLoopTest.cpp
 *
 *  Created on: 05/01/2017
 *      Author: Lucas Teske
 */

#include "CostasLoopTest.h"
#include <complex>
#include <vector>
#include <random>
#include <iostream>
#include <cmath>
#include <SatHelper/sathelper.h>

#define TESTSIZE 4096
#define PHASEOFFSET 0.707f
#define NOISELEVEL 0.02f
#define NUMTAPS 45
#define SPS 4
#define ROLLOFF 0.35f
#define LOOPBW 2 * 3.141592653589793f / 100.0f
#define TEST_AVERAGE 0.00004f


#define LRIT_SYMBOLRATE 293883
#define HRIT_SYMBOLRATE 927000
#define GRB_SYMBOLRATE 8665938
#define CALC_SPS 3.f

#define ITERATIONS 200


using namespace std;

namespace SatHelper {

    bool CostasLoopTest::RunTest() {
        random_device rd;
        mt19937 e2(rd());
        uniform_int_distribution<int> signalDist(0, 1);
        normal_distribution<> noiseDist(0, 1);
        complex<float> *testData = new complex<float>[TESTSIZE];
        complex<float> *testData2 = new complex<float>[TESTSIZE];
        float *frequencyDeviation = new float[TESTSIZE];
        CostasLoop costasLoop(LOOPBW, 2);

        cerr << c_verbose << "Benchmark Params: " << tcendl;
        cerr << c_info << "    -- TESTSIZE: " << tcarg(TESTSIZE) << tcendl;
        cerr << c_info << "    -- PHASEOFFSET: " << tcarg(PHASEOFFSET) << tcendl;
        cerr << c_info << "    -- NOISELEVEL: " << tcarg(NOISELEVEL) << tcendl;
        cerr << c_info << "    -- NUMTAPS:  " << tcarg(NUMTAPS)  << tcendl;
        cerr << c_info << "    -- SPS: " << tcarg(SPS) << tcendl;
        cerr << c_info << "    -- ROLLOFF: " << tcarg(ROLLOFF) << tcendl;
        cerr << c_info << "    -- LOOPBW: " << tcarg(LOOPBW) << tcendl;
        cerr << c_info << "    -- ITERATIONS: " << tcarg(ITERATIONS) << tcendl;

        cerr << c_verbose << "Generating Test Data " << tcendl;

        complex<float> phaseShift = exp(complex<float>(0, 1) * PHASEOFFSET);

        for (int i=0; i<TESTSIZE; i++) {
            // Create Signal
            testData[i] = phaseShift * (float) ((signalDist(e2) * 2) - 1);
            // Add Noise
            testData[i] += complex<float>(noiseDist(e2) * NOISELEVEL, noiseDist(e2) * NOISELEVEL);
        }

        vector<float> rrcTaps = Filters::RRC(1, SPS, SPS, ROLLOFF, NUMTAPS);
        FirFilter rrcFilter(1, rrcTaps);

        cerr << c_verbose << "Filtering Test Data " << tcendl;
        rrcFilter.Work(testData, testData2, TESTSIZE);


        std::cerr << c_verbose << "Performing Benchmark" << tcendl;
        std::chrono::time_point<std::chrono::system_clock> start, end;
        float averageTime = 0;
        auto elapsed = end - start;

        float highestValue = -100;
        float minimumValue = 100;
        float averageValue = 0;

        for (int c=0; c < ITERATIONS; c++) {
            costasLoop.Reset();
            start = std::chrono::system_clock::now();
            costasLoop.Work(testData2, testData, frequencyDeviation, TESTSIZE);
            end = std::chrono::system_clock::now();
            elapsed = end - start;
            averageTime += std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
            for (int i=0; i<TESTSIZE; i++) {
                float freqHz = frequencyDeviation[i] / ( 2 * 3.141592653589793f );
                averageValue += freqHz;
                highestValue = max(highestValue, freqHz);
                minimumValue = min(minimumValue, freqHz);
            }
        }

        averageValue /= TESTSIZE * ITERATIONS;
        averageTime /= ITERATIONS;

        cout << c_info << "    -- Highest Deviation: " << tcarg(highestValue) << tcendl;
        cout << c_info << "    -- Minimum Deviation: " << tcarg(minimumValue) << tcendl;
        cout << c_info << "    -- Average Deviation: " << tcarg(averageValue) << tcendl;

        if (abs(averageValue) > TEST_AVERAGE) {
            cerr << "    -- Average Value > " << TEST_AVERAGE << tcendl;
            return false;
        }

        float maxCostasSR = 1e3 / (averageTime / (1.f * TESTSIZE)); // In msps
        cerr << c_info << "    -- CostasLoop Took " << tcarg(averageTime) << c_info << " ns to finish." << tcendl;
        cerr << c_info << "    -- Maximum Usable SampleRate in this settings: " << tcarg(maxCostasSR) << c_info << " msps." << tcendl;

        if (maxCostasSR > (LRIT_SYMBOLRATE * CALC_SPS) / 1e6) {
            cerr << c_info << c_bold << "    -- Good for LRIT     \\o/" << tcendl;
        } else {
            cerr << c_error << c_bold << "    -- No good for LRIT  :(" << tcendl;
        }

        if (maxCostasSR > (HRIT_SYMBOLRATE * CALC_SPS) / 1e6) {
            cerr << c_info << c_bold << "    -- Good for HRIT     \\o/" << tcendl;
        } else {
            cerr << c_error << c_bold << "    -- No good for HRIT  :(" << tcendl;
        }

        if (maxCostasSR > (GRB_SYMBOLRATE * CALC_SPS) / 1e6) {
            cerr << c_info << c_bold << "    -- Good for GRB      \\o/" << tcendl;
        } else {
            cerr << c_error << c_bold << "    -- No good for GRB   :(" << tcendl;
        }

        delete testData;
        delete testData2;
        delete frequencyDeviation;
        return true;
    }
} /* namespace SatHelper */

RUNTEST(CostasLoopTest)

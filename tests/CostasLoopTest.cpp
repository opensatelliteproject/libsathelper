/*
 * CostasLoopTest.cpp
 *
 *  Created on: 05/01/2017
 *      Author: Lucas Teske
 */

#include "CostasLoopTest.h"

#include <iostream>
#include <random>
#include <complex>
#include <SatHelper/sathelper.h>

#define TESTSIZE 4096
#define PHASEOFFSET 0.707f
#define NOISELEVEL 0.02f
#define NUMTAPS 45
#define SPS 4
#define ROLLOFF 0.35f
#define LOOPBW 2 * 3.141592653589793f / 100.0f

#define TEST_AVERAGE 0.00004f

namespace SatHelper {
    using namespace std;
    bool CostasLoopTest::RunTest() {
        std::random_device rd;
        std::mt19937 e2(rd());
        std::uniform_int_distribution<int> signalDist(0, 1);
        std::normal_distribution<> noiseDist(0, 1);
        std::complex<float> *testData = new std::complex<float>[TESTSIZE];
        std::complex<float> *testData2 = new std::complex<float>[TESTSIZE];
        float *frequencyDeviation = new float[TESTSIZE];
        CostasLoop costasLoop(LOOPBW, 2);

        cout << "  | Generating Test Data " << endl;

        std::complex<float> phaseShift = std::exp(std::complex<float>(0, 1) * PHASEOFFSET);

        for (int i=0; i<TESTSIZE; i++) {
            // Create Signal
            testData[i] = phaseShift * (float) ((signalDist(e2) * 2) - 1);
            // Add Noise
            testData[i] += std::complex<float>(noiseDist(e2) * NOISELEVEL, noiseDist(e2) * NOISELEVEL);
        }

        std::vector<float> rrcTaps = Filters::RRC(1, SPS, SPS, ROLLOFF, NUMTAPS);
        FirFilter rrcFilter(1, rrcTaps);

        cout << "  | Filtering Test Data " << endl;
        rrcFilter.Work(testData, testData2, TESTSIZE);

        cout << "  | Running Costas Loop " << endl;
        costasLoop.Work(testData2, testData, frequencyDeviation, TESTSIZE);
        float highestValue = -100;
        float minimumValue = 100;
        float averageValue = 0;
        for (int i=0; i<TESTSIZE; i++) {
            float freqHz = frequencyDeviation[i] / ( 2 * 3.141592653589793f );
            averageValue += freqHz;
            highestValue = max(highestValue, freqHz);
            minimumValue = min(minimumValue, freqHz);
        }

        averageValue /= TESTSIZE;

        cout << "    | Highest Deviation: " << highestValue << endl;
        cout << "    | Minimum Deviation: " << minimumValue << endl;
        cout << "    | Average Deviation: " << averageValue << endl;

        if (abs(averageValue) > TEST_AVERAGE) {
            cerr << "    | Average Value > " << TEST_AVERAGE << endl;
            return false;
        }

        delete testData;
        delete testData2;
        delete frequencyDeviation;
        return true;
    }

} /* namespace SatHelper */

RUNTEST(CostasLoopTest)

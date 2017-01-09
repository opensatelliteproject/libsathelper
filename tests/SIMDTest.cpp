/*
 * SIMDTest.cpp
 *
 *  Created on: 08/01/2017
 *      Author: lucas
 */

#include "SIMDTest.h"

#include <complex>
#include <vector>
#include <random>
#include <iostream>
#include <cmath>

#include "SIMD/MemoryOp.h"
#include "SIMD/Operations.h"

using namespace std;

#define TAPS_LENGTH 64
#define EPSILON 0.0001f

namespace SatHelper {

    static bool compareFloat(float a, float b) {
        return abs(a - b) < EPSILON;
    }

    bool SIMDTest::RunTest() {
        bool result = false;
        // Memory Allocations
        const unsigned int vectorLength = TAPS_LENGTH;
        cout << "  | Testing Operations::dotProduct " << endl;
        cout << "      Alocating " << vectorLength << " taps and complex numbers." << endl;

        complex<float> *testVector = (complex<float> *)MemoryOp::alignedAlloc(sizeof(complex<float>) * vectorLength, MemoryOp::getAligment());
        float *testTaps = (float *)MemoryOp::alignedAlloc(sizeof(float) * vectorLength, MemoryOp::getAligment());
        complex<float> expectedDotProduct;
        complex<float> calculatedDotProduct;

        if (testVector == NULL || testTaps == NULL) {
            cerr << "      Cannot allocate aligned memory. " << endl;
            return false;
        }

        cout << "      Filling with random numbers" << endl;
        // Random Number
        random_device rd;
        default_random_engine e2(rd());
        normal_distribution<> dist(-1, 1);

        // Fill with random numbers
        for (unsigned int i=0; i < TAPS_LENGTH; i++) {
            testTaps[i] = dist(e2);
            testVector[i] = complex<float>(dist(e2), dist(e2));
        }

        // First Calculate without SIMD to see what's the expected value.
        cout << "      Calculating the expected value without SIMD." << endl;

        float res[2] = { 0, 0 };
        float *iPtr = (float *)testVector;
        float *tPtr = (float *)testTaps;

        for (unsigned int i = 0; i < vectorLength; i++) {
            res[0] += ((*iPtr++) * (*tPtr));
            res[1] += ((*iPtr++) * (*tPtr++));
        }

        expectedDotProduct.real(res[0]);
        expectedDotProduct.imag(res[1]);

        // Now let's use SIMD
        Operations::dotProduct(&calculatedDotProduct, testVector, testTaps, vectorLength);

        cout << "      Expected value: " << expectedDotProduct << endl;
        cout << "      Result with SIMD: " << calculatedDotProduct << endl;
        result = compareFloat(calculatedDotProduct.real(), expectedDotProduct.real()) && compareFloat(calculatedDotProduct.imag(), expectedDotProduct.imag());

        if (!result) {
            cerr << "    - SIMD and expected values doesn't match!" << endl;
        }

        // TODO: Other tests

        cout << "      Freeing memory" << endl;
        MemoryOp::free(testVector);
        MemoryOp::free(testTaps);
        cout << "      Finished test" << endl;
        return result;
    }

} /* namespace SatHelper */

#undef TEST_LENGTH

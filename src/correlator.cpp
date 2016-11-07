/*
 * correlator.cpp
 *
 *  Created on: 04/11/2016
 *      Author: Lucas Teske
 */

#include "correlator.h"
#include "WordSizeException.h"

using namespace SatHelper;

Correlator::Correlator() {

}

void Correlator::addWord(uint32_t word) {
    if (currentWordSize != 0 && currentWordSize != 32) {
        throw WordSizeException(32, currentWordSize);
    }
    VecU8 wordVec;

    for (int i = 0; i < 32; i++) {
        wordVec.push_back((word >> (32 - i - 1)) & 1 ? 0xFF : 0x00);
    }

    words.push_back(wordVec);
    correlation.push_back(0);
    position.push_back(0);
    tmpCorrelation.push_back(0);
}

void Correlator::addWord(uint64_t word) {
    if (currentWordSize != 0 && currentWordSize != 64) {
        throw WordSizeException(64, currentWordSize);
    }
    VecU8 wordVec;

    for (int i = 0; i < 64; i++) {
        wordVec.push_back((word >> (64 - i - 1) & 1) ? 0xFF : 0x00);
    }

    words.push_back(wordVec);
    correlation.push_back(0);
    position.push_back(0);
    tmpCorrelation.push_back(0);
}

void Correlator::resetCorrelation() {
    int numWords = words.size();
    for (int i = 0; i < numWords; i++) {
        correlation[i] = 0;
        position[i] = 0;
        tmpCorrelation[i] = 0;
    }
}

void Correlator::correlate(uint8_t *data, uint32_t length) {
    int wordSize = words[0].size();
    int numWords = words.size();
    int maxSearch = length - wordSize;
    resetCorrelation();

    // TODO: Use Duff's Device for numWords iteration
    for (int i = 0; i < maxSearch; i++) {
        for (int k = 0; k < wordSize; k++) {
            for (int n = 0; n < numWords; n++) {
                tmpCorrelation[n] += Correlator::hardCorrelate(data[i + k], words[n][k]);
            }
        }

        for (int n = 0; n < numWords; n++) {
            if (tmpCorrelation[n] > correlation[n]) {
                correlation[n] = tmpCorrelation[n];
                position[n] = i;
                tmpCorrelation[n] = 0;
            }
        }
    }

    uint32_t corr = 0;
    for (int n = 0; n < numWords; n++) {
        if (correlation[n] > corr) {
            wordNumber = n;
            corr = correlation[n];
        }
    }
}

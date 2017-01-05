/*
 * correlator.cpp
 *
 *  Created on: 04/11/2016
 *      Author: Lucas Teske
 */

#include "correlator.h"
#include "WordSizeException.h"
#include <memory.h>
#include <iostream>

#define USE_UNROLLING

using namespace SatHelper;

Correlator::Correlator() {
    wordNumber = 0;
    currentWordSize = 0;
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
    memset(&correlation[0], 0x00, numWords * sizeof(uint32_t));
    memset(&position[0], 0x00, numWords * sizeof(uint32_t));
    memset(&tmpCorrelation[0], 0x00, numWords * sizeof(uint32_t));
}

#ifndef USE_UNROLLING

void Correlator::correlate(uint8_t *data, uint32_t length) {
    int wordSize = words[0].size();
    int numWords = words.size();
    int maxSearch = length - wordSize;
    resetCorrelation();

    for (int i = 0; i < maxSearch; i++) {
        for (int n = 0; n < numWords; n++) {
            tmpCorrelation[n] = 0;
        }

        for (int k = 0; k < wordSize; k++) {
            for (int n = 0; n < numWords; n++) {
                tmpCorrelation[n] += (uint32_t) Correlator::hardCorrelate(data[i + k], words[n][k]);
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
#else

void Correlator::correlate(uint8_t *data, uint32_t length) {
    int wordSize = words[0].size();
    int numWords = words.size();
    int maxSearch = length - wordSize;
    resetCorrelation();

    if (numWords == 2) { // Optimization for BPSK Phase
        for (int i = 0; i < maxSearch; i++) {
            tmpCorrelation[0] = 0;
            tmpCorrelation[1] = 0;

            for (int k = 0; k < wordSize; k++) {
                tmpCorrelation[0] += softCorrelate(data[i + k], words[0][k]); //(uint32_t) Correlator::hardCorrelate(data[i + k], words[0][k]);
                tmpCorrelation[1] += softCorrelate(data[i + k], words[1][k]); //(uint32_t) Correlator::hardCorrelate(data[i + k], words[1][k]);
            }

            if (tmpCorrelation[0] > correlation[0]) {
                correlation[0] = tmpCorrelation[0];
                position[0] = i;
                tmpCorrelation[0] = 0;
            }

            if (tmpCorrelation[1] > correlation[1]) {
                correlation[1] = tmpCorrelation[1];
                position[1] = i;
                tmpCorrelation[1] = 0;
            }
        }
    } else if (numWords == 4) { // Optimization for QPSK Phase
        for (int i = 0; i < maxSearch; i++) {
            tmpCorrelation[0] = 0;
            tmpCorrelation[1] = 0;
            tmpCorrelation[2] = 0;
            tmpCorrelation[3] = 0;

            for (int k = 0; k < wordSize; k++) {
                tmpCorrelation[0] += softCorrelate(data[i + k], words[0][k]); //(uint32_t) Correlator::hardCorrelate(data[i + k], words[0][k]);
                tmpCorrelation[1] += softCorrelate(data[i + k], words[1][k]); //(uint32_t) Correlator::hardCorrelate(data[i + k], words[1][k]);
                tmpCorrelation[2] += softCorrelate(data[i + k], words[2][k]); //(uint32_t) Correlator::hardCorrelate(data[i + k], words[2][k]);
                tmpCorrelation[3] += softCorrelate(data[i + k], words[3][k]); //(uint32_t) Correlator::hardCorrelate(data[i + k], words[3][k]);
            }

            if (tmpCorrelation[0] > correlation[0]) {
                correlation[0] = tmpCorrelation[0];
                position[0] = i;
                tmpCorrelation[0] = 0;
            }

            if (tmpCorrelation[1] > correlation[1]) {
                correlation[1] = tmpCorrelation[1];
                position[1] = i;
                tmpCorrelation[1] = 0;
            }

            if (tmpCorrelation[2] > correlation[2]) {
                correlation[2] = tmpCorrelation[2];
                position[2] = i;
                tmpCorrelation[2] = 0;
            }

            if (tmpCorrelation[3] > correlation[3]) {
                correlation[3] = tmpCorrelation[3];
                position[3] = i;
                tmpCorrelation[3] = 0;
            }
        }
    } else { // Other use cases
        // Duff's Device Loop Unfolding
        int c;
        register int n;
        for (int i = 0; i < maxSearch; i++) {
            memset(&tmpCorrelation[0], 0x00, numWords * sizeof(uint32_t));
            for (int k = 0; k < wordSize; k++) {
                c = 0;
                n = (numWords + 7) / 8;
                switch (numWords % 8) {
                    case 0:
                        do {
                            tmpCorrelation[c] += (uint32_t) Correlator::hardCorrelate(data[i + k], words[c][k]);
                            c++;
                            case 7:
                            tmpCorrelation[c] += (uint32_t) Correlator::hardCorrelate(data[i + k], words[c][k]);
                            c++;
                            case 6:
                            tmpCorrelation[c] += (uint32_t) Correlator::hardCorrelate(data[i + k], words[c][k]);
                            c++;
                            case 5:
                            tmpCorrelation[c] += (uint32_t) Correlator::hardCorrelate(data[i + k], words[c][k]);
                            c++;
                            case 4:
                            tmpCorrelation[c] += (uint32_t) Correlator::hardCorrelate(data[i + k], words[c][k]);
                            c++;
                            case 3:
                            tmpCorrelation[c] += (uint32_t) Correlator::hardCorrelate(data[i + k], words[c][k]);
                            c++;
                            case 2:
                            tmpCorrelation[c] += (uint32_t) Correlator::hardCorrelate(data[i + k], words[c][k]);
                            c++;
                            case 1:
                            tmpCorrelation[c] += (uint32_t) Correlator::hardCorrelate(data[i + k], words[c][k]);
                            c++;
                        } while (--n > 0);
                }
            }

            c = 0;
            n = (numWords + 7) / 8;
            switch (numWords % 8) {
                case 0:
                    do {
                        if (tmpCorrelation[c] > correlation[c]) {
                            correlation[c] = tmpCorrelation[c];
                            position[c] = i;
                            tmpCorrelation[c] = 0;
                        }
                        c++;
                        case 7:
                        if (tmpCorrelation[c] > correlation[c]) {
                            correlation[c] = tmpCorrelation[c];
                            position[c] = i;
                            tmpCorrelation[c] = 0;
                        }
                        c++;
                        case 6:
                        if (tmpCorrelation[c] > correlation[c]) {
                            correlation[c] = tmpCorrelation[c];
                            position[c] = i;
                            tmpCorrelation[c] = 0;
                        }
                        c++;
                        case 5:
                        if (tmpCorrelation[c] > correlation[c]) {
                            correlation[c] = tmpCorrelation[c];
                            position[c] = i;
                            tmpCorrelation[c] = 0;
                        }
                        c++;
                        case 4:
                        if (tmpCorrelation[c] > correlation[c]) {
                            correlation[c] = tmpCorrelation[c];
                            position[c] = i;
                            tmpCorrelation[c] = 0;
                        }
                        c++;
                        case 3:
                        if (tmpCorrelation[c] > correlation[c]) {
                            correlation[c] = tmpCorrelation[c];
                            position[c] = i;
                            tmpCorrelation[c] = 0;
                        }
                        c++;
                        case 2:
                        if (tmpCorrelation[c] > correlation[c]) {
                            correlation[c] = tmpCorrelation[c];
                            position[c] = i;
                            tmpCorrelation[c] = 0;
                        }
                        c++;
                        case 1:
                        if (tmpCorrelation[c] > correlation[c]) {
                            correlation[c] = tmpCorrelation[c];
                            position[c] = i;
                            tmpCorrelation[c] = 0;
                        }
                        c++;
                    } while (--n > 0);
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
#endif

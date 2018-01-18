/*
 * ViterbiTest.cpp
 *
 *  Created on: 15/09/2017
 *      Author: Lucas Teske
 */

#include "ViterbiTest.h"

#include <random>
#include <iostream>
#include <sathelper.h>

#define FRAMEBYTES 2048
#define FRAMEBITS (FRAMEBYTES * 8)

namespace SatHelper {

    using namespace std;
    unsigned char symbols[8 * 2 * (FRAMEBYTES + 6)];
    unsigned char bits[FRAMEBYTES];
    unsigned char output[FRAMEBYTES];

    bool ViterbiTest::RunTest() {
        cout << "  | Generating Test Data" << endl;
        std::uniform_int_distribution<int> signalDist(0, 255);
        Viterbi27 viterbi(FRAMEBITS+6);

        random_device rd;
        mt19937 e2(rd());

        for (int i=0; i<FRAMEBYTES; i++) {
            bits[i] = signalDist(e2) & 0xFF;
        }

        viterbi.encode(bits, symbols);
        cout << "  | Trying to decode" << endl;

        viterbi.decode(symbols, output);

        int errors = 0;

        for (int i=0; i<FRAMEBYTES; i++) {
            if (output[i] != (0xFF - bits[i])) {
                errors++;
            }
        }

        if (errors > 2) { // First / Last byte can have issues due statistical nature
            cerr << "  | Error count > 2: " << errors << endl;
            return false;
        }

        return true;
    }

} /* namespace SatHelper */

RUNTEST(ViterbiTest)

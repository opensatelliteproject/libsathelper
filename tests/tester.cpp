//============================================================================
// Name        :libSatHelper Tester
// Author      : Lucas Teske
// Version     : 1.0
// Copyright   : Copyright 2016
// Description : Tester for libSatHelper - Open Satellite Project
//============================================================================

#include <cstdio>
#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <cstring>
#include "sathelper.h"
#include "tests.h"

using namespace SatHelper;
using namespace std;

int main(int argc, char **argv) {

    cout << "Starting libSatHelper Tests" << endl;

    try {
        RunTests(SIMDTest, DerandomizerTest, PacketFixerTest, CorrelationTest, ReedSolomonTest, ViterbiTest);
    } catch (TestFailException &e) {
        std::cerr << "The test "  << e.GetTestName() << " has failed." << std::endl;
        return 1;
    }

    cout << "All tests finished sucessfuly" << endl;
    return 0;
}

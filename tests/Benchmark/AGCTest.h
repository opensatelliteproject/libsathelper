/*
 * AGCTest.h
 *
 *  Created on: 05/01/2017
 *      Author: Lucas Teske
 */

#ifndef TESTS_AGCTEST_H_
#define TESTS_AGCTEST_H_

#include "BaseBenchmark.h"

namespace SatHelper {

    class AGCTest: public BaseBenchmark {
    public:
        std::string TestName() const override { return std::string("AGC Test"); }
        bool RunTest() override;
    };

} /* namespace SatHelper */

#endif /* TESTS_AGCTEST_H_ */

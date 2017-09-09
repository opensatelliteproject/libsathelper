/*
 * CorrelationTest.h
 *
 *  Created on: 05/01/2017
 *      Author: Lucas Teske
 */

#ifndef TESTS_VITERBITEST_H_
#define TESTS_VITERBITEST_H_

#include "BaseBenchmark.h"

namespace SatHelper {

    class CorrelationTest: public BaseBenchmark {
    public:
        std::string TestName() const override { return std::string("Correlation Test"); }
        bool RunTest() override;
    };

} /* namespace SatHelper */

#endif /* TESTS_VITERBITEST_H_ */

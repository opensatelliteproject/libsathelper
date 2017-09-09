/*
 * CostasLoopTest.h
 *
 *  Created on: 09/09/2017
 *      Author: Lucas Teske
 */

#ifndef TESTS_COSTASLOOPTEST_H_
#define TESTS_COSTASLOOPTEST_H_

#include "BaseBenchmark.h"

namespace SatHelper {

    class CostasLoopTest: public BaseBenchmark {
    public:
        std::string TestName() const override { return std::string("CostasLoop Test"); }
        bool RunTest() override;
    };

} /* namespace SatHelper */

#endif /* TESTS_COSTASLOOPTEST_H_ */

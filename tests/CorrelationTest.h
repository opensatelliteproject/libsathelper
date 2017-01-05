/*
 * CorrelationTest.h
 *
 *  Created on: 05/01/2017
 *      Author: Lucas Teske
 */

#ifndef TESTS_CORRELATIONTEST_H_
#define TESTS_CORRELATIONTEST_H_

#include "BaseTest.h"

namespace SatHelper {

    class CorrelationTest: public BaseTest {

    public:
        std::string TestName() const override { return std::string("Correlation Test"); }
        bool RunTest() override;

        CorrelationTest();
        virtual ~CorrelationTest();
    };

} /* namespace SatHelper */

#endif /* TESTS_CORRELATIONTEST_H_ */

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
    private:
        static const uint8_t word[];
        static const uint8_t data[];
        static const uint32_t correlation[];

    public:
        std::string TestName() const override { return std::string("Correlation Test"); }
        bool RunTest() override;
    };

} /* namespace SatHelper */

#endif /* TESTS_CORRELATIONTEST_H_ */

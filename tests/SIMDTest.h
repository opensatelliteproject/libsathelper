/*
 * SIMDTest.h
 *
 *  Created on: 08/01/2017
 *      Author: Lucas Teske
 */

#ifndef TESTS_SIMDTEST_H_
#define TESTS_SIMDTEST_H_

#include "BaseTest.h"

namespace SatHelper {

    class SIMDTest: public BaseTest {
    public:
        std::string TestName() const override { return std::string("SIMD Test"); }
        bool RunTest() override;
    };

} /* namespace SatHelper */

#endif /* TESTS_SIMDTEST_H_ */

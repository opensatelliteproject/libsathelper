/*
 * DifferentialEncodingTest.h
 *
 *  Created on: 25/01/2017
 *      Author: Lucas Teske
 */

#ifndef TESTS_DIFFERENTIALENCODING_H_
#define TESTS_DIFFERENTIALENCODING_H_

#include "BaseTest.h"

namespace SatHelper {

    class DifferentialEncodingTest: public BaseTest {
    public:
        std::string TestName() const override { return std::string("Differential Encoding Test"); }
        bool RunTest() override;
    };

} /* namespace SatHelper */

#endif /* TESTS_DIFFERENTIALENCODING_H_ */

/*
 * ViterbiTest.h
 *
 *  Created on: 05/01/2017
 *      Author: Lucas Teske
 */

#ifndef TESTS_VITERBITEST_H_
#define TESTS_VITERBITEST_H_

#include "BaseTest.h"

namespace SatHelper {

    class ViterbiTest: public BaseTest {
    public:
        std::string TestName() const override { return std::string("Viterbi Test"); }
        bool RunTest() override;

        ViterbiTest();
        virtual ~ViterbiTest();
    };

} /* namespace SatHelper */

#endif /* TESTS_VITERBITEST_H_ */

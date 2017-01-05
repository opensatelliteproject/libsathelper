/*
 * DerandomizerTest.h
 *
 *  Created on: 05/01/2017
 *      Author: Lucas Teske
 */

#ifndef TESTS_DERANDOMIZERTEST_H_
#define TESTS_DERANDOMIZERTEST_H_

#include "BaseTest.h"

namespace SatHelper {

    class DerandomizerTest: public BaseTest {
    private:
        const static uint8_t testString[];
        const static uint8_t randomizedString[];
    public:
        std::string TestName() const override { return std::string("Derandomizer Test"); }
        bool RunTest() override;
    };

} /* namespace SatHelper */

#endif /* TESTS_DERANDOMIZERTEST_H_ */

/*
 * ReedSolomonTest.h
 *
 *  Created on: 05/01/2017
 *      Author: Lucas Teske
 */

#ifndef TESTS_REEDSOLOMONTEST_H_
#define TESTS_REEDSOLOMONTEST_H_

#include "BaseTest.h"

namespace SatHelper {

    class ReedSolomonTest: public BaseTest {
    public:

        std::string TestName() const override { return std::string("Reed Solomon Test"); }
        bool RunTest() override;

        ReedSolomonTest();
        virtual ~ReedSolomonTest();
    };

} /* namespace SatHelper */

#endif /* TESTS_REEDSOLOMONTEST_H_ */

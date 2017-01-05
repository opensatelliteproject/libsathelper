/*
 * BaseTest.h
 *
 *  Created on: 05/01/2017
 *      Author: Lucas Teske
 */

#ifndef TESTS_BASETEST_H_
#define TESTS_BASETEST_H_

#include <string>

namespace SatHelper {
    class BaseTest {
    public:
        virtual std::string TestName() const = 0;
        virtual bool RunTest() = 0;

        virtual ~BaseTest() {

        }
    };
}


#endif /* TESTS_BASETEST_H_ */

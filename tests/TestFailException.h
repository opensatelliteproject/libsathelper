/*
 * TestFailException.h
 *
 *  Created on: 05/01/2017
 *      Author: Lucas Teske
 */

#ifndef TESTS_TESTFAILEXCEPTION_H_
#define TESTS_TESTFAILEXCEPTION_H_

#include <exception>

namespace SatHelper {

    class TestFailException: public std::exception {
    private:
        std::string testName;

    public:
        TestFailException(const std::string &testName) : testName(testName) {}
        inline const std::string &GetTestName() const { return testName; }
    };

} /* namespace SatHelper */

#endif /* TESTS_TESTFAILEXCEPTION_H_ */

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

#define RUNTEST(T) \
    using namespace SatHelper; \
    using namespace std; \
    int main(int argc, char **argv) { \
      T test; \
      cout << "Starting " << test.TestName() << endl; \
      if (!test.RunTest()) { \
          std::cerr << "The test "  << test.TestName() << " has failed." << std::endl; \
          return 1; \
      } \
      return 0; \
    }

#endif /* TESTS_BASETEST_H_ */

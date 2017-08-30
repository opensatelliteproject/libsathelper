/*
 * BaseBenchmark.h
 *
 *  Created on: 05/01/2017
 *      Author: Lucas Teske
 */

#ifndef TESTS_BASEBENCHMARK_H_
#define TESTS_BASEBENCHMARK_H_

#include <string>
#include <chrono>

namespace SatHelper {
    class BaseBenchmark {
    public:
        virtual std::string TestName() const = 0;
        virtual bool RunTest() = 0;

        virtual ~BaseBenchmark() {

        }
    };
}

#define RUNTEST(T) \
    using namespace SatHelper; \
    using namespace std; \
    int main(int argc, char **argv) { \
      T test; \
      cout << "Starting " << test.TestName() << endl; \
      auto start = std::chrono::system_clock::now();\
      if (!test.RunTest()) { \
          cerr << "The test "  << test.TestName() << " has failed." << std::endl; \
          return 1; \
      } \
      auto end = std::chrono::system_clock::now();\
      auto elapsed = end - start;\
      auto ticks = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();\
      cerr << "The test took " << ticks << "ns" << endl;\
      return 0; \
    }

#endif /* TESTS_BASEBENCHMARK_H_ */

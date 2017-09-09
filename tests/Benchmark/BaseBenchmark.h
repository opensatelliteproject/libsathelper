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
      cerr << c_info << "Starting Benchmark " << c_bold << test.TestName() << c_default << tcendl; \
      cerr << c_dim << c_warn << "--------------------------------------------------------" << tcendl; \
      auto start = std::chrono::system_clock::now();\
      if (!test.RunTest()) { \
          cerr << c_error << "The Benchmark " << c_bold << c_warn << test.TestName() << c_default << c_error << " has failed." << tcendl; \
          return 1; \
      } \
      cerr << c_dim << c_warn << "--------------------------------------------------------" << tcendl; \
      auto end = std::chrono::system_clock::now();\
      auto elapsed = end - start;\
      auto ticks = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();\
      cerr << c_info << "The Benchmark took " << c_bold << ticks << c_default << c_info << " ns" << tcendl;\
      return 0; \
    }

#endif /* TESTS_BASEBENCHMARK_H_ */

#include "TestFailException.h"
#include "CorrelationTest.h"
#include "DerandomizerTest.h"
#include "PacketFixerTest.h"
#include "ReedSolomonTest.h"
#include "ViterbiTest.h"

// Class Tester Template - by Paulo Torrens

#ifndef _TESTER_TEMPLATE
#define _TESTER_TEMPLATE

#include <type_traits>

namespace SatHelper {
    template<typename ... Args> struct TestExecuter;

    template<typename T, typename ... Args> struct TestExecuter<T, Args...> :
        public std::enable_if<std::is_base_of<BaseTest, T>::value, TestExecuter<Args...>>::type {

        static inline void run() {
            T t;
            std::cout << "Running " << t.TestName() << std::endl;
            if (t.RunTest()) {
                std::cout << t.TestName() << " OK" << std::endl;
                TestExecuter<Args...>::run();
            } else {
                std::cout << t.TestName() << " FAIL" << std::endl;
                throw TestFailException(t.TestName());
            }
        }
    };

    template<> struct TestExecuter<> {
        static inline void run() {
            std::cout << "All tests were executed! ;)" << std::endl;
        }
    };

#define RunTests(...) TestExecuter<__VA_ARGS__>::run();
}

#endif

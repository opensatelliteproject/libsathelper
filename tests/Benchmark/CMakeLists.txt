cmake_minimum_required (VERSION 2.6)
project (SatHelperTest)
enable_language(CXX)

# C++11 Macro
macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
  endif ()
endmacro(use_cxx11)

use_cxx11()


# Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

# Test
SET(AVAILABLE_TESTS "BenchMark_FIRTest;BenchMark_CorrelationTest;BenchMark_CostasLoopTest;BenchMark_ViterbiTest;BenchMark_AGCTest")

foreach(TEST_BENCH_NAME ${AVAILABLE_TESTS})
  string(REPLACE "BenchMark_" "" TEST_NAME ${TEST_BENCH_NAME})
  add_executable (${TEST_BENCH_NAME} ${TEST_NAME}.cpp)
  # add_test (NAME ${TEST_NAME} COMMAND ${TEST_NAME})
  target_link_libraries (${TEST_BENCH_NAME} correct)
  target_link_libraries (${TEST_BENCH_NAME} SatHelper)
  if(WIN32)
    target_link_libraries(${TEST_BENCH_NAME} wsock32 ws2_32)
    #set(CMAKE_EXE_LINKER_FLAGS "-static")
  endif()
endforeach()
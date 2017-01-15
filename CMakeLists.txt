cmake_minimum_required (VERSION 2.6)
project (SatHelper)
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

# Version
set(VERSION_INFO_MAJOR_VERSION 1)
set(VERSION_INFO_MINOR_VERSION 3)
set(VERSION_INFO_MAINT_VERSION 0git)

# Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

# Includes
include_directories ("${PROJECT_SOURCE_DIR}/includes")
include_directories ("${PROJECT_SOURCE_DIR}/includes/SatHelper")
include_directories ("${PROJECT_SOURCE_DIR}/includes/SatHelper/dsp")
include_directories ("${PROJECT_SOURCE_DIR}/includes/SatHelper/exceptions")
include_directories ("${PROJECT_SOURCE_DIR}/includes/SatHelper/SIMD")

# Library Source Code
file(GLOB SOURCES src/*.cpp src/SIMD/*.cpp src/dsp/*.cpp)

# Library Targets
add_library(${PROJECT_NAME} SHARED ${SOURCES})
add_library(${PROJECT_NAME}_s STATIC ${SOURCES})
SET_TARGET_PROPERTIES(${PROJECT_NAME}_s PROPERTIES OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(${PROJECT_NAME}   PROPERTIES OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)

# Links
target_link_libraries (${PROJECT_NAME} correct)

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(TARGETS ${PROJECT_NAME}_s DESTINATION lib)

# Install library headers
file(GLOB HEADERS includes/SatHelper/*.h)
file(GLOB HEADERS_DSP includes/SatHelper/dsp/*.h)
file(GLOB HEADERS_SIMD includes/SatHelper/SIMD/*.h)
file(GLOB HEADERS_EXCEPTIONS includes/SatHelper/exceptions/*.h)

install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})
install(FILES ${HEADERS_DSP} DESTINATION include/${PROJECT_NAME}/dsp)
install(FILES ${HEADERS_SIMD} DESTINATION include/${PROJECT_NAME}/SIMD)
install(FILES ${HEADERS_EXCEPTIONS} DESTINATION include/${PROJECT_NAME}/exceptions)

add_subdirectory(tests)
enable_testing()

SET(AVAILABLE_TESTS "CorrelationTest;DerandomizerTest;PacketFixerTest;ReedSolomonTest;SIMDTest;ViterbiTest")

foreach(TEST_NAME ${AVAILABLE_TESTS})
  add_test (NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

# Debian Package
SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Lucas Teske")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libcorrect")
SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION "SatHelper library for Satellite Projects")
INCLUDE(CPack)
cmake_minimum_required (VERSION 2.6)
project (SatHelper)
enable_language(CXX)

set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)

# C++11 Macro
macro(use_cxx11)
  set (CMAKE_CXX_STANDARD 11)
endmacro(use_cxx11)

use_cxx11()

include(CheckCompilerFlags)

if(CMAKE_COMPILER_IS_GNUCXX)
    ADD_CXX_COMPILER_FLAG_IF_AVAILABLE(-Wsign-compare HAVE_WARN_SIGN_COMPARE)
    ADD_CXX_COMPILER_FLAG_IF_AVAILABLE(-Wall HAVE_WARN_ALL)
    ADD_CXX_COMPILER_FLAG_IF_AVAILABLE(-Wno-uninitialized HAVE_WARN_NO_UNINITIALIZED)
    ADD_CXX_COMPILER_FLAG_IF_AVAILABLE(-O3 HAVE_O3)
    ADD_CXX_COMPILER_FLAG_IF_AVAILABLE(-ffast-math HAVE_FAST_MATH)
    #ADD_CXX_COMPILER_FLAG_IF_AVAILABLE(-mfma HAVE_FMA)
endif(CMAKE_COMPILER_IS_GNUCXX)

# Version
set(VERSION_INFO_MAJOR_VERSION 1)
set(VERSION_INFO_MINOR_VERSION 1)
set(VERSION_INFO_MAINT_VERSION 0)

add_definitions(-DMAJOR_VERSION=${VERSION_INFO_MAJOR_VERSION})
add_definitions(-DMINOR_VERSION=${VERSION_INFO_MINOR_VERSION})
add_definitions(-DMAINT_VERSION=${VERSION_INFO_MAINT_VERSION})
add_definitions(-DGIT_SHA1=${GIT_SHA1})

if(NOT WIN32)
EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )
else()
# What to do? Assume x86?
set(ARCHITECTURE x86)
endif()

message( STATUS "Architecture: ${ARCHITECTURE}" )


# Flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fPIC -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC -O3")

if(${ARCHITECTURE} STREQUAL "aarch64")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -funsafe-math-optimizations -mtune=cortex-a53 -ftree-vectorize")
endif()

if(${ARCHITECTURE} STREQUAL "armv7l")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -funsafe-math-optimizations -mfloat-abi=hard -mfpu=neon -ftree-vectorize -I/usr/include/arm-linux-gnueabihf/c++/5/ -I/usr/include/arm-linux-gnueabihf/")
endif()

if(${ARCHITECTURE} STREQUAL "i686")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
endif()

if(${ARCHITECTURE} STREQUAL "x86" OR ${ARCHITECTURE} STREQUAL "x86_64" OR ${ARCHITECTURE} STREQUAL "i686")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse -msse3 -mstackrealign")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse -msse3 -mstackrealign")
endif()


# Includes
include_directories ("${PROJECT_SOURCE_DIR}/includes")
include_directories ("${PROJECT_SOURCE_DIR}/includes/SatHelper")
include_directories ("${PROJECT_SOURCE_DIR}/includes/SatHelper/dsp")
include_directories ("${PROJECT_SOURCE_DIR}/includes/SatHelper/exceptions")
include_directories ("${PROJECT_SOURCE_DIR}/includes/SatHelper/SIMD")

if(APPLE)
  include_directories ("/usr/local/include")
  link_directories ("/usr/local/lib")
endif()

# Library Source Code
file(GLOB SOURCES src/*.cpp src/SIMD/*.cpp src/dsp/*.cpp)

# Library Targets
add_library(${PROJECT_NAME} SHARED ${SOURCES})
add_library(${PROJECT_NAME}_s STATIC ${SOURCES})
SET_TARGET_PROPERTIES(${PROJECT_NAME}_s PROPERTIES OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(${PROJECT_NAME}   PROPERTIES OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)

# Links
target_link_libraries (${PROJECT_NAME} correct.a)
if(WIN32)
  target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static")
endif()

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
add_subdirectory(tests/Benchmark)
enable_testing()

SET(AVAILABLE_TESTS "DifferentialEncodingTest;CorrelationTest;DerandomizerTest;PacketFixerTest;ReedSolomonTest;SIMDTest;ViterbiTest;BenchMark_FIRTest")

foreach(TEST_NAME ${AVAILABLE_TESTS})
  add_test (NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

# Debian Package
SET(CPACK_GENERATOR "DEB")
SET(CPACK_PACKAGE_NAME "libSatHelper")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Lucas Teske")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libcorrect")
SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION "SatHelper library for Satellite Projects")
SET(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_INFO_MAJOR_VERSION})
SET(CPACK_PACKAGE_VERSION_MINOR ${VERSION_INFO_MINOR_VERSION})
SET(CPACK_PACKAGE_VERSION_PATCH ${VERSION_INFO_MAINT_VERSION})
INCLUDE(CPack)

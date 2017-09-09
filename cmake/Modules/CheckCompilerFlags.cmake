########################################################################
# Check if a compiler flag works and conditionally set a compile define.
#  - flag the compiler flag to check for
#  - have the variable to set with result
########################################################################
macro(ADD_CXX_COMPILER_FLAG_IF_AVAILABLE flag have)
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG(${flag} ${have})
    if(${have})
      if(${CMAKE_VERSION} VERSION_GREATER "2.8.4")
        STRING(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_dup)
        if(${flag_dup} EQUAL -1)
          set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}")
          set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${flag}")
        endif(${flag_dup} EQUAL -1)
      endif(${CMAKE_VERSION} VERSION_GREATER "2.8.4")
    endif(${have})
endmacro(ADD_CXX_COMPILER_FLAG_IF_AVAILABLE)

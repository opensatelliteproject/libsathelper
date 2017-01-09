################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/SIMD/MemoryOp.cpp \
../src/SIMD/Operations.cpp 

OBJS += \
./src/SIMD/MemoryOp.o \
./src/SIMD/Operations.o 

CPP_DEPS += \
./src/SIMD/MemoryOp.d \
./src/SIMD/Operations.d 


# Each subdirectory must supply rules for building sources it contributes
src/SIMD/%.o: ../src/SIMD/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I../includes -I../includes/exceptions -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



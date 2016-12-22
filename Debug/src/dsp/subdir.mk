################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/dsp/controlloop.cpp \
../src/dsp/costasloop.cpp 

OBJS += \
./src/dsp/controlloop.o \
./src/dsp/costasloop.o 

CPP_DEPS += \
./src/dsp/controlloop.d \
./src/dsp/costasloop.d 


# Each subdirectory must supply rules for building sources it contributes
src/dsp/%.o: ../src/dsp/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I../includes -I../includes/exceptions -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



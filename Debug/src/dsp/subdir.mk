################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/dsp/clockrecovery.cpp \
../src/dsp/controlloop.cpp \
../src/dsp/costasloop.cpp \
../src/dsp/filters.cpp \
../src/dsp/firinterpolator.cpp \
../src/dsp/firkernel.cpp 

OBJS += \
./src/dsp/clockrecovery.o \
./src/dsp/controlloop.o \
./src/dsp/costasloop.o \
./src/dsp/filters.o \
./src/dsp/firinterpolator.o \
./src/dsp/firkernel.o 

CPP_DEPS += \
./src/dsp/clockrecovery.d \
./src/dsp/controlloop.d \
./src/dsp/costasloop.d \
./src/dsp/filters.d \
./src/dsp/firinterpolator.d \
./src/dsp/firkernel.d 


# Each subdirectory must supply rules for building sources it contributes
src/dsp/%.o: ../src/dsp/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I../includes -I../includes/exceptions -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



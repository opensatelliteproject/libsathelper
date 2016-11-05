################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/correlator.cpp \
../src/packetfixer.cpp \
../src/reedsolomon.cpp \
../src/viterbi27.cpp 

OBJS += \
./src/correlator.o \
./src/packetfixer.o \
./src/reedsolomon.o \
./src/viterbi27.o 

CPP_DEPS += \
./src/correlator.d \
./src/packetfixer.d \
./src/reedsolomon.d \
./src/viterbi27.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I"/home/lucas/Works/OpenSatelliteProject/open-satellite-project/SatHelper/includes" -I"/home/lucas/Works/OpenSatelliteProject/open-satellite-project/SatHelper/includes/exceptions" -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



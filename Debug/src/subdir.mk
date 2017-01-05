################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/correlator.cpp \
../src/derandomizer.cpp \
../src/packetfixer.cpp \
../src/reedsolomon.cpp \
../src/screenmanager.cpp \
../src/socket.cpp \
../src/tcpclient.cpp \
../src/tcpserver.cpp \
../src/viterbi27.cpp 

OBJS += \
./src/correlator.o \
./src/derandomizer.o \
./src/packetfixer.o \
./src/reedsolomon.o \
./src/screenmanager.o \
./src/socket.o \
./src/tcpclient.o \
./src/tcpserver.o \
./src/viterbi27.o 

CPP_DEPS += \
./src/correlator.d \
./src/derandomizer.d \
./src/packetfixer.d \
./src/reedsolomon.d \
./src/screenmanager.d \
./src/socket.d \
./src/tcpclient.d \
./src/tcpserver.d \
./src/viterbi27.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I../includes -I../includes/exceptions -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



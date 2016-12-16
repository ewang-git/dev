################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../testpopen.cpp 

OBJS += \
./testpopen.o 

CPP_DEPS += \
./testpopen.d 


# Each subdirectory must supply rules for building sources it contributes
testpopen.o: ../testpopen.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"c:\mingw\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"testpopen.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



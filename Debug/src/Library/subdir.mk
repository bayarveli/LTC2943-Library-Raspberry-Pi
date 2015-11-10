################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Library/IMI2C.cpp \
../src/Library/LTC2943.cpp 

OBJS += \
./src/Library/IMI2C.o \
./src/Library/LTC2943.o 

CPP_DEPS += \
./src/Library/IMI2C.d \
./src/Library/LTC2943.d 


# Each subdirectory must supply rules for building sources it contributes
src/Library/%.o: ../src/Library/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



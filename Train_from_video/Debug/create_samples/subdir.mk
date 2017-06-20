################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../create_samples/createsamples.cpp \
../create_samples/utility.cpp 

OBJS += \
./create_samples/createsamples.o \
./create_samples/utility.o 

CPP_DEPS += \
./create_samples/createsamples.d \
./create_samples/utility.d 


# Each subdirectory must supply rules for building sources it contributes
create_samples/%.o: ../create_samples/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/int.c \
../Src/main.c \
../Src/ports.c \
../Src/projectconf.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/systemfunctions.c \
../Src/uart.c 

OBJS += \
./Src/int.o \
./Src/main.o \
./Src/ports.o \
./Src/projectconf.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/systemfunctions.o \
./Src/uart.o 

C_DEPS += \
./Src/int.d \
./Src/main.d \
./Src/ports.d \
./Src/projectconf.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/systemfunctions.d \
./Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/int.d ./Src/int.o ./Src/int.su ./Src/main.d ./Src/main.o ./Src/main.su ./Src/ports.d ./Src/ports.o ./Src/ports.su ./Src/projectconf.d ./Src/projectconf.o ./Src/projectconf.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/systemfunctions.d ./Src/systemfunctions.o ./Src/systemfunctions.su ./Src/uart.d ./Src/uart.o ./Src/uart.su

.PHONY: clean-Src


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/am2302.c \
../Src/int.c \
../Src/main.c \
../Src/onewire.c \
../Src/ports.c \
../Src/projectconf.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/systemfunctions.c 

OBJS += \
./Src/am2302.o \
./Src/int.o \
./Src/main.o \
./Src/onewire.o \
./Src/ports.o \
./Src/projectconf.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/systemfunctions.o 

C_DEPS += \
./Src/am2302.d \
./Src/int.d \
./Src/main.d \
./Src/onewire.d \
./Src/ports.d \
./Src/projectconf.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/systemfunctions.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/am2302.d ./Src/am2302.o ./Src/am2302.su ./Src/int.d ./Src/int.o ./Src/int.su ./Src/main.d ./Src/main.o ./Src/main.su ./Src/onewire.d ./Src/onewire.o ./Src/onewire.su ./Src/ports.d ./Src/ports.o ./Src/ports.su ./Src/projectconf.d ./Src/projectconf.o ./Src/projectconf.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/systemfunctions.d ./Src/systemfunctions.o ./Src/systemfunctions.su

.PHONY: clean-Src


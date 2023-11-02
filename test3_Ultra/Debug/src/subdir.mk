################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/BlinkLed.c \
../src/GPT_PBconfig.c \
../src/GPT_Program.c \
../src/HIR_Program.c \
../src/MEXTI_Program.c \
../src/MGPIO_Program.c \
../src/MNIVC_Program.c \
../src/MRCC_Program.c \
../src/Timer.c \
../src/Ultrasonic.c \
../src/initialize-hardware.c \
../src/main.c \
../src/main_delay.c \
../src/stm32f4xx_hal_msp.c \
../src/write.c 

OBJS += \
./src/BlinkLed.o \
./src/GPT_PBconfig.o \
./src/GPT_Program.o \
./src/HIR_Program.o \
./src/MEXTI_Program.o \
./src/MGPIO_Program.o \
./src/MNIVC_Program.o \
./src/MRCC_Program.o \
./src/Timer.o \
./src/Ultrasonic.o \
./src/initialize-hardware.o \
./src/main.o \
./src/main_delay.o \
./src/stm32f4xx_hal_msp.o \
./src/write.o 

C_DEPS += \
./src/BlinkLed.d \
./src/GPT_PBconfig.d \
./src/GPT_Program.d \
./src/HIR_Program.d \
./src/MEXTI_Program.d \
./src/MGPIO_Program.d \
./src/MNIVC_Program.d \
./src/MRCC_Program.d \
./src/Timer.d \
./src/Ultrasonic.d \
./src/initialize-hardware.d \
./src/main.d \
./src/main_delay.d \
./src/stm32f4xx_hal_msp.d \
./src/write.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F401xC -DUSE_HAL_DRIVER -DHSE_VALUE=25000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



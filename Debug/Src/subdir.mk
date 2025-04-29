################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/clock_control.c \
../Src/interrupt.c \
../Src/io_port.c \
../Src/main.c \
../Src/timer_control.c 

OBJS += \
./Src/clock_control.o \
./Src/interrupt.o \
./Src/io_port.o \
./Src/main.o \
./Src/timer_control.o 

C_DEPS += \
./Src/clock_control.d \
./Src/interrupt.d \
./Src/io_port.d \
./Src/main.d \
./Src/timer_control.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32G031xx -DSTM32G031J6Mx -DSTM32 -DSTM32G0 -c -I"C:/Users/idune/STM32CubeIDE/workspace_1.14.1/Low_Layer_PWM/Inc" -I"C:/Users/idune/STM32CubeIDE/workspace_1.14.1/Low_Layer_PWM/Inc/Sys" -I"C:/Users/idune/STM32CubeIDE/workspace_1.14.1/Low_Layer_PWM/Src" -I"C:/Users/idune/STM32CubeIDE/workspace_1.14.1/Low_Layer_PWM/Src/Sys" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/clock_control.cyclo ./Src/clock_control.d ./Src/clock_control.o ./Src/clock_control.su ./Src/interrupt.cyclo ./Src/interrupt.d ./Src/interrupt.o ./Src/interrupt.su ./Src/io_port.cyclo ./Src/io_port.d ./Src/io_port.o ./Src/io_port.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/timer_control.cyclo ./Src/timer_control.d ./Src/timer_control.o ./Src/timer_control.su

.PHONY: clean-Src


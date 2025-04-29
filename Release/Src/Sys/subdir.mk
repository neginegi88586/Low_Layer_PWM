################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Sys/syscalls.c \
../Src/Sys/sysmem.c \
../Src/Sys/system_stm32g0xx.c 

OBJS += \
./Src/Sys/syscalls.o \
./Src/Sys/sysmem.o \
./Src/Sys/system_stm32g0xx.o 

C_DEPS += \
./Src/Sys/syscalls.d \
./Src/Sys/sysmem.d \
./Src/Sys/system_stm32g0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Sys/%.o Src/Sys/%.su Src/Sys/%.cyclo: ../Src/Sys/%.c Src/Sys/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DSTM32G031J6Mx -DSTM32G031xx -DSTM32 -DSTM32G0 -c -I"C:/Users/idune/STM32CubeIDE/workspace_1.14.1/Low_Layer_PWM/Inc/Sys" -I"C:/Users/idune/STM32CubeIDE/workspace_1.14.1/Low_Layer_PWM/Src/Sys" -I"C:/Users/idune/STM32CubeIDE/workspace_1.14.1/Low_Layer_PWM/Inc" -I"C:/Users/idune/STM32CubeIDE/workspace_1.14.1/Low_Layer_PWM/Src" -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-Sys

clean-Src-2f-Sys:
	-$(RM) ./Src/Sys/syscalls.cyclo ./Src/Sys/syscalls.d ./Src/Sys/syscalls.o ./Src/Sys/syscalls.su ./Src/Sys/sysmem.cyclo ./Src/Sys/sysmem.d ./Src/Sys/sysmem.o ./Src/Sys/sysmem.su ./Src/Sys/system_stm32g0xx.cyclo ./Src/Sys/system_stm32g0xx.d ./Src/Sys/system_stm32g0xx.o ./Src/Sys/system_stm32g0xx.su

.PHONY: clean-Src-2f-Sys


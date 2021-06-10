################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Flick/flick.c 

OBJS += \
./Drivers/Flick/flick.o 

C_DEPS += \
./Drivers/Flick/flick.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Flick/flick.o: ../Drivers/Flick/flick.c Drivers/Flick/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Flick/flick.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


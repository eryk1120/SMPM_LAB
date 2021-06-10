################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/LCD/st7735.c \
../Drivers/LCD/stm32_adafruit_lcd.c 

OBJS += \
./Drivers/LCD/st7735.o \
./Drivers/LCD/stm32_adafruit_lcd.o 

C_DEPS += \
./Drivers/LCD/st7735.d \
./Drivers/LCD/stm32_adafruit_lcd.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/LCD/st7735.o: ../Drivers/LCD/st7735.c Drivers/LCD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LCD/st7735.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/LCD/stm32_adafruit_lcd.o: ../Drivers/LCD/stm32_adafruit_lcd.c Drivers/LCD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LCD/stm32_adafruit_lcd.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


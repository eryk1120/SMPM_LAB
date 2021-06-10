################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/LCD/Fonts/font12.c \
../Drivers/LCD/Fonts/font16.c \
../Drivers/LCD/Fonts/font20.c \
../Drivers/LCD/Fonts/font24.c \
../Drivers/LCD/Fonts/font8.c 

OBJS += \
./Drivers/LCD/Fonts/font12.o \
./Drivers/LCD/Fonts/font16.o \
./Drivers/LCD/Fonts/font20.o \
./Drivers/LCD/Fonts/font24.o \
./Drivers/LCD/Fonts/font8.o 

C_DEPS += \
./Drivers/LCD/Fonts/font12.d \
./Drivers/LCD/Fonts/font16.d \
./Drivers/LCD/Fonts/font20.d \
./Drivers/LCD/Fonts/font24.d \
./Drivers/LCD/Fonts/font8.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/LCD/Fonts/font12.o: ../Drivers/LCD/Fonts/font12.c Drivers/LCD/Fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LCD/Fonts/font12.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/LCD/Fonts/font16.o: ../Drivers/LCD/Fonts/font16.c Drivers/LCD/Fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LCD/Fonts/font16.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/LCD/Fonts/font20.o: ../Drivers/LCD/Fonts/font20.c Drivers/LCD/Fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LCD/Fonts/font20.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/LCD/Fonts/font24.o: ../Drivers/LCD/Fonts/font24.c Drivers/LCD/Fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LCD/Fonts/font24.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/LCD/Fonts/font8.o: ../Drivers/LCD/Fonts/font8.c Drivers/LCD/Fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LCD/Fonts/font8.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


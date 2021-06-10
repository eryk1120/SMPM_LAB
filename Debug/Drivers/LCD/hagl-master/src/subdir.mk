################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/LCD/hagl-master/src/bitmap.c \
../Drivers/LCD/hagl-master/src/clip.c \
../Drivers/LCD/hagl-master/src/fontx.c \
../Drivers/LCD/hagl-master/src/hagl.c \
../Drivers/LCD/hagl-master/src/hsl.c \
../Drivers/LCD/hagl-master/src/rgb565.c \
../Drivers/LCD/hagl-master/src/rgb888.c \
../Drivers/LCD/hagl-master/src/tjpgd.c 

OBJS += \
./Drivers/LCD/hagl-master/src/bitmap.o \
./Drivers/LCD/hagl-master/src/clip.o \
./Drivers/LCD/hagl-master/src/fontx.o \
./Drivers/LCD/hagl-master/src/hagl.o \
./Drivers/LCD/hagl-master/src/hsl.o \
./Drivers/LCD/hagl-master/src/rgb565.o \
./Drivers/LCD/hagl-master/src/rgb888.o \
./Drivers/LCD/hagl-master/src/tjpgd.o 

C_DEPS += \
./Drivers/LCD/hagl-master/src/bitmap.d \
./Drivers/LCD/hagl-master/src/clip.d \
./Drivers/LCD/hagl-master/src/fontx.d \
./Drivers/LCD/hagl-master/src/hagl.d \
./Drivers/LCD/hagl-master/src/hsl.d \
./Drivers/LCD/hagl-master/src/rgb565.d \
./Drivers/LCD/hagl-master/src/rgb888.d \
./Drivers/LCD/hagl-master/src/tjpgd.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/LCD/hagl-master/src/bitmap.o: ../Drivers/LCD/hagl-master/src/bitmap.c Drivers/LCD/hagl-master/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LCD/hagl-master/src/bitmap.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/LCD/hagl-master/src/clip.o: ../Drivers/LCD/hagl-master/src/clip.c Drivers/LCD/hagl-master/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LCD/hagl-master/src/clip.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/LCD/hagl-master/src/fontx.o: ../Drivers/LCD/hagl-master/src/fontx.c Drivers/LCD/hagl-master/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LCD/hagl-master/src/fontx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/LCD/hagl-master/src/hagl.o: ../Drivers/LCD/hagl-master/src/hagl.c Drivers/LCD/hagl-master/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LCD/hagl-master/src/hagl.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/LCD/hagl-master/src/hsl.o: ../Drivers/LCD/hagl-master/src/hsl.c Drivers/LCD/hagl-master/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LCD/hagl-master/src/hsl.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/LCD/hagl-master/src/rgb565.o: ../Drivers/LCD/hagl-master/src/rgb565.c Drivers/LCD/hagl-master/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LCD/hagl-master/src/rgb565.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/LCD/hagl-master/src/rgb888.o: ../Drivers/LCD/hagl-master/src/rgb888.c Drivers/LCD/hagl-master/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LCD/hagl-master/src/rgb888.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/LCD/hagl-master/src/tjpgd.o: ../Drivers/LCD/hagl-master/src/tjpgd.c Drivers/LCD/hagl-master/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LCD/hagl-master/src/tjpgd.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


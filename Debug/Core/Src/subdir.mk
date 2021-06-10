################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/GUI_MENU_SMPM.c \
../Core/Src/lcd.c \
../Core/Src/main.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c 

OBJS += \
./Core/Src/GUI_MENU_SMPM.o \
./Core/Src/lcd.o \
./Core/Src/main.o \
./Core/Src/stm32l4xx_hal_msp.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o 

C_DEPS += \
./Core/Src/GUI_MENU_SMPM.d \
./Core/Src/lcd.d \
./Core/Src/main.d \
./Core/Src/stm32l4xx_hal_msp.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/GUI_MENU_SMPM.o: ../Core/Src/GUI_MENU_SMPM.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/GUI_MENU_SMPM.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/lcd.o: ../Core/Src/lcd.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/lcd.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/main.o: ../Core/Src/main.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32l4xx_hal_msp.o: ../Core/Src/stm32l4xx_hal_msp.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32l4xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32l4xx_it.o: ../Core/Src/stm32l4xx_it.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32l4xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/syscalls.o: ../Core/Src/syscalls.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/sysmem.o: ../Core/Src/sysmem.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/system_stm32l4xx.o: ../Core/Src/system_stm32l4xx.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/Flick/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/hagl-master/include" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/IMU/Inc" -I"C:/Users/szewc/OneDrive/Dokumenty/GitHub/SMPM_LAB/Drivers/LCD/Inc" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/system_stm32l4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


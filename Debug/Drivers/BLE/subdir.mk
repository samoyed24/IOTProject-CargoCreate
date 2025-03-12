################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BLE/ble.c 

OBJS += \
./Drivers/BLE/ble.o 

C_DEPS += \
./Drivers/BLE/ble.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BLE/%.o Drivers/BLE/%.su Drivers/BLE/%.cyclo: ../Drivers/BLE/%.c Drivers/BLE/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BLE

clean-Drivers-2f-BLE:
	-$(RM) ./Drivers/BLE/ble.cyclo ./Drivers/BLE/ble.d ./Drivers/BLE/ble.o ./Drivers/BLE/ble.su

.PHONY: clean-Drivers-2f-BLE


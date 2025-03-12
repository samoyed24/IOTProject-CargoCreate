################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Wifi/wifi.c 

OBJS += \
./Drivers/Wifi/wifi.o 

C_DEPS += \
./Drivers/Wifi/wifi.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Wifi/%.o Drivers/Wifi/%.su Drivers/Wifi/%.cyclo: ../Drivers/Wifi/%.c Drivers/Wifi/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Wifi

clean-Drivers-2f-Wifi:
	-$(RM) ./Drivers/Wifi/wifi.cyclo ./Drivers/Wifi/wifi.d ./Drivers/Wifi/wifi.o ./Drivers/Wifi/wifi.su

.PHONY: clean-Drivers-2f-Wifi


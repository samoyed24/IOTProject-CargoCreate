################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/HX711/hx711.c 

OBJS += \
./Drivers/HX711/hx711.o 

C_DEPS += \
./Drivers/HX711/hx711.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/HX711/%.o Drivers/HX711/%.su Drivers/HX711/%.cyclo: ../Drivers/HX711/%.c Drivers/HX711/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-HX711

clean-Drivers-2f-HX711:
	-$(RM) ./Drivers/HX711/hx711.cyclo ./Drivers/HX711/hx711.d ./Drivers/HX711/hx711.o ./Drivers/HX711/hx711.su

.PHONY: clean-Drivers-2f-HX711


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Buzzer/buzzer.c 

OBJS += \
./Drivers/Buzzer/buzzer.o 

C_DEPS += \
./Drivers/Buzzer/buzzer.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Buzzer/%.o Drivers/Buzzer/%.su Drivers/Buzzer/%.cyclo: ../Drivers/Buzzer/%.c Drivers/Buzzer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Buzzer

clean-Drivers-2f-Buzzer:
	-$(RM) ./Drivers/Buzzer/buzzer.cyclo ./Drivers/Buzzer/buzzer.d ./Drivers/Buzzer/buzzer.o ./Drivers/Buzzer/buzzer.su

.PHONY: clean-Drivers-2f-Buzzer


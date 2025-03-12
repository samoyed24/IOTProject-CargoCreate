################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Message/message.c 

OBJS += \
./Drivers/Message/message.o 

C_DEPS += \
./Drivers/Message/message.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Message/%.o Drivers/Message/%.su Drivers/Message/%.cyclo: ../Drivers/Message/%.c Drivers/Message/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Message

clean-Drivers-2f-Message:
	-$(RM) ./Drivers/Message/message.cyclo ./Drivers/Message/message.d ./Drivers/Message/message.o ./Drivers/Message/message.su

.PHONY: clean-Drivers-2f-Message


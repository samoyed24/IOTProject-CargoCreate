################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Huawei/huawei.c 

OBJS += \
./Drivers/Huawei/huawei.o 

C_DEPS += \
./Drivers/Huawei/huawei.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Huawei/%.o Drivers/Huawei/%.su Drivers/Huawei/%.cyclo: ../Drivers/Huawei/%.c Drivers/Huawei/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Huawei

clean-Drivers-2f-Huawei:
	-$(RM) ./Drivers/Huawei/huawei.cyclo ./Drivers/Huawei/huawei.d ./Drivers/Huawei/huawei.o ./Drivers/Huawei/huawei.su

.PHONY: clean-Drivers-2f-Huawei


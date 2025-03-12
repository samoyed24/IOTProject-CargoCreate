################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/RC522/rc522.c \
../Drivers/RC522/rfid_uid.c 

OBJS += \
./Drivers/RC522/rc522.o \
./Drivers/RC522/rfid_uid.o 

C_DEPS += \
./Drivers/RC522/rc522.d \
./Drivers/RC522/rfid_uid.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/RC522/%.o Drivers/RC522/%.su Drivers/RC522/%.cyclo: ../Drivers/RC522/%.c Drivers/RC522/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-RC522

clean-Drivers-2f-RC522:
	-$(RM) ./Drivers/RC522/rc522.cyclo ./Drivers/RC522/rc522.d ./Drivers/RC522/rc522.o ./Drivers/RC522/rc522.su ./Drivers/RC522/rfid_uid.cyclo ./Drivers/RC522/rfid_uid.d ./Drivers/RC522/rfid_uid.o ./Drivers/RC522/rfid_uid.su

.PHONY: clean-Drivers-2f-RC522


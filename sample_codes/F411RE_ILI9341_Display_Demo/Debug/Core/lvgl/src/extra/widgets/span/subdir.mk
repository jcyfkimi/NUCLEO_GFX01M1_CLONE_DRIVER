################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/lvgl/src/extra/widgets/span/lv_span.c 

OBJS += \
./Core/lvgl/src/extra/widgets/span/lv_span.o 

C_DEPS += \
./Core/lvgl/src/extra/widgets/span/lv_span.d 


# Each subdirectory must supply rules for building sources it contributes
Core/lvgl/src/extra/widgets/span/%.o Core/lvgl/src/extra/widgets/span/%.su: ../Core/lvgl/src/extra/widgets/span/%.c Core/lvgl/src/extra/widgets/span/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/Users/Kimi/STM32CubeIDE/workspace_1.5.1/F411RE_ILI9341_Display_Demo/Core/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-lvgl-2f-src-2f-extra-2f-widgets-2f-span

clean-Core-2f-lvgl-2f-src-2f-extra-2f-widgets-2f-span:
	-$(RM) ./Core/lvgl/src/extra/widgets/span/lv_span.d ./Core/lvgl/src/extra/widgets/span/lv_span.o ./Core/lvgl/src/extra/widgets/span/lv_span.su

.PHONY: clean-Core-2f-lvgl-2f-src-2f-extra-2f-widgets-2f-span

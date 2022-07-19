################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/lvgl/demos/keypad_encoder/lv_demo_keypad_encoder.c 

OBJS += \
./Core/lvgl/demos/keypad_encoder/lv_demo_keypad_encoder.o 

C_DEPS += \
./Core/lvgl/demos/keypad_encoder/lv_demo_keypad_encoder.d 


# Each subdirectory must supply rules for building sources it contributes
Core/lvgl/demos/keypad_encoder/%.o Core/lvgl/demos/keypad_encoder/%.su: ../Core/lvgl/demos/keypad_encoder/%.c Core/lvgl/demos/keypad_encoder/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/Users/Kimi/STM32CubeIDE/workspace_1.5.1/F411RE_ILI9341_Display_Demo_DMA/Core/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-lvgl-2f-demos-2f-keypad_encoder

clean-Core-2f-lvgl-2f-demos-2f-keypad_encoder:
	-$(RM) ./Core/lvgl/demos/keypad_encoder/lv_demo_keypad_encoder.d ./Core/lvgl/demos/keypad_encoder/lv_demo_keypad_encoder.o ./Core/lvgl/demos/keypad_encoder/lv_demo_keypad_encoder.su

.PHONY: clean-Core-2f-lvgl-2f-demos-2f-keypad_encoder


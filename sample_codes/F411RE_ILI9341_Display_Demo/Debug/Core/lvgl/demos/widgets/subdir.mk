################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/lvgl/demos/widgets/lv_demo_widgets.c 

OBJS += \
./Core/lvgl/demos/widgets/lv_demo_widgets.o 

C_DEPS += \
./Core/lvgl/demos/widgets/lv_demo_widgets.d 


# Each subdirectory must supply rules for building sources it contributes
Core/lvgl/demos/widgets/%.o Core/lvgl/demos/widgets/%.su: ../Core/lvgl/demos/widgets/%.c Core/lvgl/demos/widgets/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/Users/Kimi/STM32CubeIDE/workspace_1.5.1/F411RE_ILI9341_Display_Demo/Core/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-lvgl-2f-demos-2f-widgets

clean-Core-2f-lvgl-2f-demos-2f-widgets:
	-$(RM) ./Core/lvgl/demos/widgets/lv_demo_widgets.d ./Core/lvgl/demos/widgets/lv_demo_widgets.o ./Core/lvgl/demos/widgets/lv_demo_widgets.su

.PHONY: clean-Core-2f-lvgl-2f-demos-2f-widgets


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/lvgl/examples/widgets/menu/lv_example_menu_1.c \
../Core/lvgl/examples/widgets/menu/lv_example_menu_2.c \
../Core/lvgl/examples/widgets/menu/lv_example_menu_3.c \
../Core/lvgl/examples/widgets/menu/lv_example_menu_4.c \
../Core/lvgl/examples/widgets/menu/lv_example_menu_5.c 

OBJS += \
./Core/lvgl/examples/widgets/menu/lv_example_menu_1.o \
./Core/lvgl/examples/widgets/menu/lv_example_menu_2.o \
./Core/lvgl/examples/widgets/menu/lv_example_menu_3.o \
./Core/lvgl/examples/widgets/menu/lv_example_menu_4.o \
./Core/lvgl/examples/widgets/menu/lv_example_menu_5.o 

C_DEPS += \
./Core/lvgl/examples/widgets/menu/lv_example_menu_1.d \
./Core/lvgl/examples/widgets/menu/lv_example_menu_2.d \
./Core/lvgl/examples/widgets/menu/lv_example_menu_3.d \
./Core/lvgl/examples/widgets/menu/lv_example_menu_4.d \
./Core/lvgl/examples/widgets/menu/lv_example_menu_5.d 


# Each subdirectory must supply rules for building sources it contributes
Core/lvgl/examples/widgets/menu/%.o Core/lvgl/examples/widgets/menu/%.su: ../Core/lvgl/examples/widgets/menu/%.c Core/lvgl/examples/widgets/menu/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/Users/Kimi/STM32CubeIDE/workspace_1.5.1/F411RE_ILI9341_Display_Demo_DMA/Core/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-lvgl-2f-examples-2f-widgets-2f-menu

clean-Core-2f-lvgl-2f-examples-2f-widgets-2f-menu:
	-$(RM) ./Core/lvgl/examples/widgets/menu/lv_example_menu_1.d ./Core/lvgl/examples/widgets/menu/lv_example_menu_1.o ./Core/lvgl/examples/widgets/menu/lv_example_menu_1.su ./Core/lvgl/examples/widgets/menu/lv_example_menu_2.d ./Core/lvgl/examples/widgets/menu/lv_example_menu_2.o ./Core/lvgl/examples/widgets/menu/lv_example_menu_2.su ./Core/lvgl/examples/widgets/menu/lv_example_menu_3.d ./Core/lvgl/examples/widgets/menu/lv_example_menu_3.o ./Core/lvgl/examples/widgets/menu/lv_example_menu_3.su ./Core/lvgl/examples/widgets/menu/lv_example_menu_4.d ./Core/lvgl/examples/widgets/menu/lv_example_menu_4.o ./Core/lvgl/examples/widgets/menu/lv_example_menu_4.su ./Core/lvgl/examples/widgets/menu/lv_example_menu_5.d ./Core/lvgl/examples/widgets/menu/lv_example_menu_5.o ./Core/lvgl/examples/widgets/menu/lv_example_menu_5.su

.PHONY: clean-Core-2f-lvgl-2f-examples-2f-widgets-2f-menu


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/lvgl/examples/widgets/chart/lv_example_chart_1.c \
../Core/lvgl/examples/widgets/chart/lv_example_chart_2.c \
../Core/lvgl/examples/widgets/chart/lv_example_chart_3.c \
../Core/lvgl/examples/widgets/chart/lv_example_chart_4.c \
../Core/lvgl/examples/widgets/chart/lv_example_chart_5.c \
../Core/lvgl/examples/widgets/chart/lv_example_chart_6.c \
../Core/lvgl/examples/widgets/chart/lv_example_chart_7.c \
../Core/lvgl/examples/widgets/chart/lv_example_chart_8.c \
../Core/lvgl/examples/widgets/chart/lv_example_chart_9.c 

OBJS += \
./Core/lvgl/examples/widgets/chart/lv_example_chart_1.o \
./Core/lvgl/examples/widgets/chart/lv_example_chart_2.o \
./Core/lvgl/examples/widgets/chart/lv_example_chart_3.o \
./Core/lvgl/examples/widgets/chart/lv_example_chart_4.o \
./Core/lvgl/examples/widgets/chart/lv_example_chart_5.o \
./Core/lvgl/examples/widgets/chart/lv_example_chart_6.o \
./Core/lvgl/examples/widgets/chart/lv_example_chart_7.o \
./Core/lvgl/examples/widgets/chart/lv_example_chart_8.o \
./Core/lvgl/examples/widgets/chart/lv_example_chart_9.o 

C_DEPS += \
./Core/lvgl/examples/widgets/chart/lv_example_chart_1.d \
./Core/lvgl/examples/widgets/chart/lv_example_chart_2.d \
./Core/lvgl/examples/widgets/chart/lv_example_chart_3.d \
./Core/lvgl/examples/widgets/chart/lv_example_chart_4.d \
./Core/lvgl/examples/widgets/chart/lv_example_chart_5.d \
./Core/lvgl/examples/widgets/chart/lv_example_chart_6.d \
./Core/lvgl/examples/widgets/chart/lv_example_chart_7.d \
./Core/lvgl/examples/widgets/chart/lv_example_chart_8.d \
./Core/lvgl/examples/widgets/chart/lv_example_chart_9.d 


# Each subdirectory must supply rules for building sources it contributes
Core/lvgl/examples/widgets/chart/%.o Core/lvgl/examples/widgets/chart/%.su: ../Core/lvgl/examples/widgets/chart/%.c Core/lvgl/examples/widgets/chart/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/Users/Kimi/STM32CubeIDE/workspace_1.5.1/F411RE_ILI9341_Display_Demo_DMA/Core/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-lvgl-2f-examples-2f-widgets-2f-chart

clean-Core-2f-lvgl-2f-examples-2f-widgets-2f-chart:
	-$(RM) ./Core/lvgl/examples/widgets/chart/lv_example_chart_1.d ./Core/lvgl/examples/widgets/chart/lv_example_chart_1.o ./Core/lvgl/examples/widgets/chart/lv_example_chart_1.su ./Core/lvgl/examples/widgets/chart/lv_example_chart_2.d ./Core/lvgl/examples/widgets/chart/lv_example_chart_2.o ./Core/lvgl/examples/widgets/chart/lv_example_chart_2.su ./Core/lvgl/examples/widgets/chart/lv_example_chart_3.d ./Core/lvgl/examples/widgets/chart/lv_example_chart_3.o ./Core/lvgl/examples/widgets/chart/lv_example_chart_3.su ./Core/lvgl/examples/widgets/chart/lv_example_chart_4.d ./Core/lvgl/examples/widgets/chart/lv_example_chart_4.o ./Core/lvgl/examples/widgets/chart/lv_example_chart_4.su ./Core/lvgl/examples/widgets/chart/lv_example_chart_5.d ./Core/lvgl/examples/widgets/chart/lv_example_chart_5.o ./Core/lvgl/examples/widgets/chart/lv_example_chart_5.su ./Core/lvgl/examples/widgets/chart/lv_example_chart_6.d ./Core/lvgl/examples/widgets/chart/lv_example_chart_6.o ./Core/lvgl/examples/widgets/chart/lv_example_chart_6.su ./Core/lvgl/examples/widgets/chart/lv_example_chart_7.d ./Core/lvgl/examples/widgets/chart/lv_example_chart_7.o ./Core/lvgl/examples/widgets/chart/lv_example_chart_7.su ./Core/lvgl/examples/widgets/chart/lv_example_chart_8.d ./Core/lvgl/examples/widgets/chart/lv_example_chart_8.o ./Core/lvgl/examples/widgets/chart/lv_example_chart_8.su ./Core/lvgl/examples/widgets/chart/lv_example_chart_9.d ./Core/lvgl/examples/widgets/chart/lv_example_chart_9.o ./Core/lvgl/examples/widgets/chart/lv_example_chart_9.su

.PHONY: clean-Core-2f-lvgl-2f-examples-2f-widgets-2f-chart


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/lvgl/tests/src/lv_test_indev.c \
../Core/lvgl/tests/src/lv_test_init.c 

OBJS += \
./Core/lvgl/tests/src/lv_test_indev.o \
./Core/lvgl/tests/src/lv_test_init.o 

C_DEPS += \
./Core/lvgl/tests/src/lv_test_indev.d \
./Core/lvgl/tests/src/lv_test_init.d 


# Each subdirectory must supply rules for building sources it contributes
Core/lvgl/tests/src/%.o Core/lvgl/tests/src/%.su: ../Core/lvgl/tests/src/%.c Core/lvgl/tests/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/Users/Kimi/STM32CubeIDE/workspace_1.5.1/F411RE_ILI9341_Display_Demo_DMA/Core/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-lvgl-2f-tests-2f-src

clean-Core-2f-lvgl-2f-tests-2f-src:
	-$(RM) ./Core/lvgl/tests/src/lv_test_indev.d ./Core/lvgl/tests/src/lv_test_indev.o ./Core/lvgl/tests/src/lv_test_indev.su ./Core/lvgl/tests/src/lv_test_init.d ./Core/lvgl/tests/src/lv_test_init.o ./Core/lvgl/tests/src/lv_test_init.su

.PHONY: clean-Core-2f-lvgl-2f-tests-2f-src


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/lvgl/src/draw/nxp_vglite/lv_gpu_nxp_vglite.c 

OBJS += \
./Core/lvgl/src/draw/nxp_vglite/lv_gpu_nxp_vglite.o 

C_DEPS += \
./Core/lvgl/src/draw/nxp_vglite/lv_gpu_nxp_vglite.d 


# Each subdirectory must supply rules for building sources it contributes
Core/lvgl/src/draw/nxp_vglite/%.o Core/lvgl/src/draw/nxp_vglite/%.su: ../Core/lvgl/src/draw/nxp_vglite/%.c Core/lvgl/src/draw/nxp_vglite/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/Users/Kimi/STM32CubeIDE/workspace_1.5.1/F411RE_ILI9341_Display_Demo/Core/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-lvgl-2f-src-2f-draw-2f-nxp_vglite

clean-Core-2f-lvgl-2f-src-2f-draw-2f-nxp_vglite:
	-$(RM) ./Core/lvgl/src/draw/nxp_vglite/lv_gpu_nxp_vglite.d ./Core/lvgl/src/draw/nxp_vglite/lv_gpu_nxp_vglite.o ./Core/lvgl/src/draw/nxp_vglite/lv_gpu_nxp_vglite.su

.PHONY: clean-Core-2f-lvgl-2f-src-2f-draw-2f-nxp_vglite


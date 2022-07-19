/*
 * lcd_lvgl_dma.c
 *
 *  Created on: 2022年7月19日
 *      Author: Kimi
 */


#include <stdio.h>
#include <string.h>
#include "main.h"
#include "lcd_ili9341.h"
#include "lv_conf.h"
#include "lvgl.h"
#include "lcd_lvgl_dma.h"

#define DISPLAY_BUFFER_LINES 	(40)

static lv_disp_drv_t disp_drv;

static void disp_flush_dma(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

// DMA Call back function
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi){
	if(hspi->Instance == SPI1){
		disp_SPI_TxCpltCallback();
		lv_disp_flush_ready(&disp_drv);
	}
}

void lv_port_disp_init(void)
{
	disp_init();

	static lv_disp_draw_buf_t disp_buf_2;
	static lv_color_t buf2_1[LV_HOR_RES_MAX * DISPLAY_BUFFER_LINES] __attribute__((aligned(4))); /*A buffer for 10 rows*/
	static lv_color_t buf2_2[LV_HOR_RES_MAX * DISPLAY_BUFFER_LINES] __attribute__((aligned(4))); /*An other buffer for 10 rows*/
	lv_disp_draw_buf_init(&disp_buf_2, buf2_1, buf2_2, LV_HOR_RES_MAX * DISPLAY_BUFFER_LINES); /*Initialize the display buffer*/

	//lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv); /*Basic initialization*/

	/*Set up the functions to access to your display*/
	disp_set_rotation(SCREEN_HORIZONTAL_1);

	/*Set the resolution of the display*/
	disp_drv.hor_res = 320;
	disp_drv.ver_res = 240;

	/*Used to copy the buffer's content to the display*/
	disp_drv.flush_cb = disp_flush_dma;

	/*Set a display buffer*/
	disp_drv.draw_buf = &disp_buf_2;

	/*Finally register the driver*/
	lv_disp_drv_register(&disp_drv);
}

static void disp_flush_dma(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
	uint32_t size = 0;
	disp_set_address_window(area->x1, area->y1, area->x2, area->y2);
	size = (area->x2 - area->x1 + 1) * (area->y2 - area->y1 + 1) * 2;
	disp_draw_bitmap_dma((uint8_t *) color_p, size);
}



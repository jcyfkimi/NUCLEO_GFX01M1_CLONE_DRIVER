/*
 * lcd_lvgl.c
 *
 *  Created on: 2022年6月30日
 *      Author: Kimi
 */

#include "lcd_lvgl.h"
#include "lv_conf.h"
#include "lvgl.h"
//#include "user_setting.h"
#include "string.h"
//#include "functions.h"
#include "main.h"
#include "lcd_ili9341.h"

//static lv_disp_drv_t disp_drv;
////static int32_t x1_flush;
////static int32_t y1_flush;
////static int32_t x2_flush;
////static int32_t y2_fill;
////static int32_t y_fill_act;
////static const lv_color_t * buf_to_flush;
//
//static lv_color_t disp_buf1[DISP_HOR_RES * 10];
//static lv_color_t disp_buf2[DISP_HOR_RES * 10];
//
//static volatile uint32_t t_saved = 0;
//void monitor_cb(lv_disp_drv_t * d, uint32_t t, uint32_t p)
//{
//	t_saved = t;
//}
//
///*These 3 functions are needed by LittlevGL*/
//static void Display_flush(lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_p);
//
//void Display_init(int rotation, SPI_HandleTypeDef *hspi)
//{
//
//	static lv_disp_draw_buf_t buf;
//
//	lv_disp_draw_buf_init(&buf, disp_buf1, disp_buf2, DISP_HOR_RES * 10);
//
//	lv_disp_drv_init(&disp_drv);
//
//	ILI9341_Init(hspi);
//	ILI9341_Set_Rotation(rotation);
//
//	ILI9341_Fill_Screen(BLACK);
//
//	disp_drv.draw_buf = &buf;
//	disp_drv.flush_cb = Display_flush;
//	disp_drv.monitor_cb = monitor_cb;
//	disp_drv.hor_res = DISP_HOR_RES;
//	disp_drv.ver_res = DISP_VER_RES;
//	disp_drv.rotated = rotation;
//	lv_disp_drv_register(&disp_drv);
//}
//
//
//
///**********************
// *   STATIC FUNCTIONS
// **********************/
//
///**
// * Flush a color buffer
// * @param x1 left coordinate of the rectangle
// * @param x2 right coordinate of the rectangle
// * @param y1 top coordinate of the rectangle
// * @param y2 bottom coordinate of the rectangle
// * @param color_p pointer to an array of colors
// */
//static void Display_flush(lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_p)
//{
//	/*Return if the area is out the screen*/
//
//	if(area->x2 < 0) return;
//	if(area->y2 < 0) return;
//	if(area->x1 > DISP_HOR_RES - 1) return;
//	if(area->y1 > DISP_VER_RES - 1) return;
//
//
//	// int indx = 0;
////	setAddrWindow(area->x1, area->y1, area->x2, area->y2);
//    for(int y=area->y1;y<=area->y2;y++)
//    {
//        for(int x=area->x1;x<=area->x2;x++)
//        {
//            //DISP_fb[indx] = color_p->full;
//            ILI9341_Draw_Vertical_Line(x, y, 1, color_p->full);
//            color_p++;
//        }
//
//    }
//
//    lv_disp_flush_ready(drv);
//}



/*********************
 *      DEFINES
 *********************/

#define DISPLAY_BUFFER_LINES 40

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
/**********************
 *  STATIC VARIABLES
 **********************/

static lv_disp_drv_t disp_drv;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

void lv_port_disp_init(void)
{
    /*-------------------------
     * Initialize your display
     * -----------------------*/
    disp_init();

    /*-----------------------------
     * Create a buffer for drawing
     *----------------------------*/

    /* LVGL requires a buffer where it draws the objects. The buffer's has to be greater than 1 display row
     *
     * There are three buffering configurations:
     * 1. Create ONE buffer with some rows:
     *      LVGL will draw the display's content here and writes it to your display
     *
     * 2. Create TWO buffer with some rows:
     *      LVGL will draw the display's content to a buffer and writes it your display.
     *      You should use DMA to write the buffer's content to the display.
     *      It will enable LVGL to draw the next part of the screen to the other buffer while
     *      the data is being sent form the first buffer. It makes rendering and flushing parallel.
     *
     * 3. Create TWO screen-sized buffer:
     *      Similar to 2) but the buffer have to be screen sized. When LVGL is ready it will give the
     *      whole frame to display. This way you only need to change the frame buffer's address instead of
     *      copying the pixels.
     * */

    /* Example for 1) */
//    static lv_disp_buf_t disp_buf_1;
//    static lv_color_t buf1_1[LV_HOR_RES_MAX * 10];                      /*A buffer for 10 rows*/
//    lv_disp_buf_init(&disp_buf_1, buf1_1, NULL, LV_HOR_RES_MAX * 10);   /*Initialize the display buffer*/

    /* Example for 2) */
    static lv_disp_draw_buf_t disp_buf_2;
    static lv_color_t buf2_1[LV_HOR_RES_MAX * DISPLAY_BUFFER_LINES] __attribute__((aligned(4)));                        /*A buffer for 10 rows*/
    static lv_color_t buf2_2[LV_HOR_RES_MAX * DISPLAY_BUFFER_LINES] __attribute__((aligned(4)));                        /*An other buffer for 10 rows*/
    lv_disp_draw_buf_init(&disp_buf_2, buf2_1, buf2_2, LV_HOR_RES_MAX * DISPLAY_BUFFER_LINES);   /*Initialize the display buffer*/

    /* Example for 3) */
//    static lv_disp_buf_t disp_buf_3;
//    static lv_color_t buf3_1[LV_HOR_RES_MAX * LV_VER_RES_MAX];            /*A screen sized buffer*/
//    static lv_color_t buf3_2[LV_HOR_RES_MAX * LV_VER_RES_MAX];            /*An other screen sized buffer*/
//    lv_disp_buf_init(&disp_buf_3, buf3_1, buf3_2, LV_HOR_RES_MAX * LV_VER_RES_MAX);   /*Initialize the display buffer*/


    /*-----------------------------------
     * Register the display in LVGL
     *----------------------------------*/

    //lv_disp_drv_t disp_drv;                         /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/

    /*Set up the functions to access to your display*/
    disp_set_rotation(SCREEN_HORIZONTAL_1);

    /*Set the resolution of the display*/
    disp_drv.hor_res = 320;
    disp_drv.ver_res = 240;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = disp_flush;

    /*Set a display buffer*/
    disp_drv.draw_buf = &disp_buf_2;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}

/* Flush the content of the internal buffer the specific area on the display
 * You can use DMA or any hardware acceleration to do this operation in the background but
 * 'lv_disp_flush_ready()' has to be called when finished. */
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
	//ScreenFlushDMA(area->x1, area->y1, area->x2, area->y2, (uint8_t *)color_p, disp_drv);
	uint32_t size = 0;
	disp_set_address_window(area->x1, area->y1, area->x2, area->y2);
	size = (area->x2 - area->x1 + 1) * (area->y2 - area->y1 + 1) * 2;
	disp_draw_bitmap((uint8_t *) color_p, size);

	lv_disp_flush_ready(disp_drv);
}



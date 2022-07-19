/*
 * lcd_ili9341.h
 *
 *  Created on: Jul 12, 2022
 *      Author: Kimi
 */

#ifndef INC_LCD_ILI9341_H_
#define INC_LCD_ILI9341_H_

#include "main.h"

#define ILI9341_SCREEN_HEIGHT 					(240)
#define ILI9341_SCREEN_WIDTH 					(320)

//CHIP SELECT PIN AND PORT, STANDARD GPIO
#define LCD_CS_PORT								(SPI1_NCS_GPIO_Port)
#define LCD_CS_PIN								(SPI1_NCS_Pin)

//DATA COMMAND PIN AND PORT, STANDARD GPIO
#define LCD_DC_PORT								(SPI1_DCX_GPIO_Port)
#define LCD_DC_PIN								(SPI1_DCX_Pin)

//RESET PIN AND PORT, STANDARD GPIO
#define	LCD_RST_PORT							(LCD_NRESET_GPIO_Port)
#define	LCD_RST_PIN								(LCD_NRESET_Pin)

#define BURST_MAX_SIZE 							(500)

#define BLACK      								(0x0000)
#define NAVY        							(0x000F)
#define DARKGREEN   							(0x03E0)
#define DARKCYAN    							(0x03EF)
#define MAROON      							(0x7800)
#define PURPLE      							(0x780F)
#define OLIVE       							(0x7BE0)
#define LIGHTGREY   							(0xC618)
#define DARKGREY    							(0x7BEF)
#define BLUE        							(0x001F)
#define GREEN       							(0x07E0)
#define CYAN        							(0x07FF)
#define RED         							(0xF800)
#define MAGENTA     							(0xF81F)
#define YELLOW      							(0xFFE0)
#define WHITE       							(0xFFFF)
#define ORANGE      							(0xFD20)
#define GREENYELLOW 							(0xAFE5)
#define PINK        							(0xF81F)

#define SCREEN_VERTICAL_1						(0)
#define SCREEN_HORIZONTAL_1						(1)
#define SCREEN_VERTICAL_2						(2)
#define SCREEN_HORIZONTAL_2						(3)


void disp_init(void);
void disp_set_address_window(uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd);
void disp_draw_pixel(uint16_t xPos,uint16_t yPos,uint16_t pData);
void disp_draw_bitmap(uint8_t *pData, uint32_t size);
void disp_set_rotation(uint8_t rot);
void disp_fill_screen(uint16_t color);
void disp_draw_color_burst(uint16_t color, uint32_t size);
void disp_draw_bitmap_dma(uint8_t *pData, uint32_t size);
void disp_fill_screen_dma(uint16_t color);
void disp_draw_color_dma(uint8_t *pData, uint32_t size);
void disp_SPI_TxCpltCallback(void);



#endif /* INC_LCD_ILI9341_H_ */

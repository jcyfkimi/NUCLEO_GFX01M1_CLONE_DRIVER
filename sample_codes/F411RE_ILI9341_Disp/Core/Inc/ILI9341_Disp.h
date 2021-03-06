/*
 * ILI9341_Disp.h
 *
 *  Created on: Dec 7, 2021
 *      Author: Kimi_Jin
 */

#ifndef INC_ILI9341_DISP_H_
#define INC_ILI9341_DISP_H_

#include "stm32f4xx_hal.h"
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
#define	LCD_RST_PORT							(DISP_NRESET_GPIO_Port)
#define	LCD_RST_PIN								(DISP_NRESET_Pin)

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

void ILI9341_SPI_Init(SPI_HandleTypeDef *hspi);
void ILI9341_SPI_Send(unsigned char data);
void ILI9341_Write_Command(uint8_t cmd);
void ILI9341_Write_Data(uint8_t data);
void ILI9341_Set_Address(uint16_t pos_x1, uint16_t pos_y1, uint16_t pos_x2, uint16_t pos_y2);
void ILI9341_Reset(void);
void ILI9341_Set_Rotation(uint8_t rot);
void ILI9341_Enable(void);
void ILI9341_Init(SPI_HandleTypeDef *hspi);
void ILI9341_Fill_Screen(uint16_t colour);
void ILI9341_Draw_Colour(uint16_t colour);
void ILI9341_Draw_Pixel(uint16_t pos_x,uint16_t pos_y,uint16_t colour);
void ILI9341_Draw_Colour_Burst(uint16_t colour, uint32_t size);
void ILI9341_Draw_Rectangle(uint16_t pos_x, uint16_t pos_y, uint16_t width, uint16_t height, uint16_t colour);
void ILI9341_Draw_Horizontal_Line(uint16_t pos_x, uint16_t pos_y, uint16_t width, uint16_t colour);
void ILI9341_Draw_Vertical_Line(uint16_t pos_x, uint16_t pos_y, uint16_t height, uint16_t colour);


#endif /* INC_ILI9341_DISP_H_ */

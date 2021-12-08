/*
 * graphic.h
 *
 *  Created on: Dec 7, 2021
 *      Author: Kimi_Jin
 */

#ifndef INC_GRAPHIC_H_
#define INC_GRAPHIC_H_

#include "stm32f4xx_hal.h"

#define HORIZONTAL_IMAGE			(0)
#define VERTICAL_IMAGE				(1)

void Graphic_Draw_Hollow_Circle(uint16_t pos_x, uint16_t pos_y, uint16_t radius, uint16_t colour);
void Graphic_Draw_Filled_Circle(uint16_t pos_x, uint16_t pos_y, uint16_t radius, uint16_t colour);
void Graphic_Draw_Hollow_Rectangle_Coord(uint16_t pos_x0, uint16_t pos_y0, uint16_t pos_x1, uint16_t pos_y1, uint16_t colour);
void Graphic_Draw_Filled_Rectangle_Coord(uint16_t pos_x0, uint16_t pos_y0, uint16_t pos_x1, uint16_t pos_y1, uint16_t colour);
void Graphic_Draw_Char(char character, uint8_t pos_x, uint8_t pos_y, uint16_t colour, uint16_t size, uint16_t background_colour);
void Graphic_Draw_Text(const char* Text, uint8_t pos_x, uint8_t pos_y, uint16_t colour, uint16_t size, uint16_t background_colour);
void Graphic_Draw_Filled_Rectangle_Size_Text(uint16_t pos_x0, uint16_t pos_y0, uint16_t size_x, uint16_t size_y, uint16_t colour);

//USING CONVERTER: http://www.digole.com/tools/PicturetoC_Hex_converter.php
//65K colour (2Bytes / Pixel)
void Graphic_Draw_Image(SPI_HandleTypeDef *hspi, const char* image, uint8_t orientation);


#endif /* INC_GRAPHIC_H_ */

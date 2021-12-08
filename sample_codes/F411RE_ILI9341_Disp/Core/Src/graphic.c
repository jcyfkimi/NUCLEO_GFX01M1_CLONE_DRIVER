/*
 * Graphic.c
 *
 *  Created on: Dec 7, 2021
 *      Author: Kimi_Jin
 */

#include "stdint.h"
#include "graphic.h"
#include "ILI9341_Disp.h"
#include "font.h"


/*Draw hollow circle at pos_x,pos_y location with specified radius and colour. pos_x and pos_y represent circles center */
void Graphic_Draw_Hollow_Circle(uint16_t pos_x, uint16_t pos_y, uint16_t radius, uint16_t colour)
{
	int x = radius - 1;
	int y = 0;
	int dx = 1;
	int dy = 1;
	int err = dx - (radius << 1);

	while (x >= y)
	{
		ILI9341_Draw_Pixel(pos_x + x, pos_y + y, colour);
		ILI9341_Draw_Pixel(pos_x + y, pos_y + x, colour);
		ILI9341_Draw_Pixel(pos_x - y, pos_y + x, colour);
		ILI9341_Draw_Pixel(pos_x - x, pos_y + y, colour);
		ILI9341_Draw_Pixel(pos_x - x, pos_y - y, colour);
		ILI9341_Draw_Pixel(pos_x - y, pos_y - x, colour);
		ILI9341_Draw_Pixel(pos_x + y, pos_y - x, colour);
		ILI9341_Draw_Pixel(pos_x + x, pos_y - y, colour);

		if (err <= 0)
		{
			y++;
			err += dy;
			dy += 2;
		}
		if (err > 0)
		{
			x--;
			dx += 2;
			err += (-radius << 1) + dx;
		}
	}
}

/*Draw filled circle at pos_x,pos_y location with specified radius and colour. pos_x and pos_y represent circles center */
void Graphic_Draw_Filled_Circle(uint16_t pos_x, uint16_t pos_y, uint16_t radius, uint16_t colour)
{

	int x = radius;
	int y = 0;
	int xChange = 1 - (radius << 1);
	int yChange = 0;
	int radiusError = 0;

	while (x >= y)
	{
		for (int i = pos_x - x; i <= pos_x + x; i++)
		{
			ILI9341_Draw_Pixel(i, pos_y + y, colour);
			ILI9341_Draw_Pixel(i, pos_y - y, colour);
		}
		for (int i = pos_x - y; i <= pos_x + y; i++)
		{
			ILI9341_Draw_Pixel(i, pos_y + x, colour);
			ILI9341_Draw_Pixel(i, pos_y - x, colour);
		}

		y++;
		radiusError += yChange;
		yChange += 2;
		if (((radiusError << 1) + xChange) > 0)
		{
			x--;
			radiusError += xChange;
			xChange += 2;
		}
	}
	//Really slow implementation, will require future overhaul
	//TODO:	https://stackoverflow.com/questions/1201200/fast-algorithm-for-drawing-filled-circles
}

/*Draw a hollow rectangle between positions pos_x0,pos_y0 and pos_x1,pos_y1 with specified colour*/
void Graphic_Draw_Hollow_Rectangle_Coord(uint16_t pos_x0, uint16_t pos_y0, uint16_t pos_x1, uint16_t pos_y1, uint16_t colour)
{
	uint16_t X_length = 0;
	uint16_t Y_length = 0;
	uint8_t Negative_X = 0;
	uint8_t Negative_Y = 0;
	float Calc_Negative = 0;

	Calc_Negative = pos_x1 - pos_x0;
	if (Calc_Negative < 0)
	{
		Negative_X = 1;
	}
	Calc_Negative = 0;

	Calc_Negative = pos_y1 - pos_y0;
	if (Calc_Negative < 0)
	{
		Negative_Y = 1;
	}

	//DRAW HORIZONTAL!
	if (!Negative_X)
	{
		X_length = pos_x1 - pos_x0;
	}
	else
	{
		X_length = pos_x0 - pos_x1;
	}
	ILI9341_Draw_Horizontal_Line(pos_x0, pos_y0, X_length, colour);
	ILI9341_Draw_Horizontal_Line(pos_x0, pos_y1, X_length, colour);

	//DRAW VERTICAL!
	if (!Negative_Y)
	{
		Y_length = pos_y1 - pos_y0;
	}
	else
	{
		Y_length = pos_y0 - pos_y1;
	}
	ILI9341_Draw_Vertical_Line(pos_x0, pos_y0, Y_length, colour);
	ILI9341_Draw_Vertical_Line(pos_x1, pos_y0, Y_length, colour);

	if ((X_length > 0) || (Y_length > 0))
	{
		ILI9341_Draw_Pixel(pos_x1, pos_y1, colour);
	}

}

/*Draw a filled rectangle between positions X0,Y0 and X1,Y1 with specified colour*/
void Graphic_Draw_Filled_Rectangle_Coord(uint16_t pos_x0, uint16_t pos_y0, uint16_t pos_x1, uint16_t pos_y1, uint16_t colour)
{
	uint16_t X_length = 0;
	uint16_t Y_length = 0;
	uint8_t Negative_X = 0;
	uint8_t Negative_Y = 0;
	int32_t Calc_Negative = 0;

	uint16_t X0_true = 0;
	uint16_t Y0_true = 0;

	Calc_Negative = pos_x1 - pos_x0;
	if (Calc_Negative < 0)
		Negative_X = 1;
	Calc_Negative = 0;

	Calc_Negative = pos_y1 - pos_x0;
	if (Calc_Negative < 0)
		Negative_Y = 1;

	//DRAW HORIZONTAL!
	if (!Negative_X)
	{
		X_length = pos_x1 - pos_x0;
		X0_true = pos_x0;
	}
	else
	{
		X_length = pos_x0 - pos_x1;
		X0_true = pos_x1;
	}

	//DRAW VERTICAL!
	if (!Negative_Y)
	{
		Y_length = pos_y1 - pos_x0;
		Y0_true = pos_x0;
	}
	else
	{
		Y_length = pos_x0 - pos_y1;
		Y0_true = pos_y1;
	}

	ILI9341_Draw_Rectangle(X0_true, Y0_true, X_length, Y_length, colour);
}

/*Draws a character (fonts imported from fonts.h) at X,Y location with specified font colour, size and Background colour*/
/*See fonts.h implementation of font on what is required for changing to a different font when switching fonts libraries*/
void Graphic_Draw_Char(char character, uint8_t pos_x, uint8_t pos_y, uint16_t colour, uint16_t size, uint16_t background_colour)
{
	uint8_t function_char;
	uint8_t i, j;

	function_char = character;

	if (function_char < ' ')
	{
		character = 0;
	}
	else
	{
		function_char -= 32;
	}

	char temp[CHAR_WIDTH];
	for (uint8_t k = 0; k < CHAR_WIDTH; k++)
	{
		temp[k] = font_5x5[function_char][k];
	}

	// Draw pixels
	ILI9341_Draw_Rectangle(pos_x, pos_y, CHAR_WIDTH * size, CHAR_HEIGHT * size, background_colour);
	for (j = 0; j < CHAR_WIDTH; j++)
	{
		for (i = 0; i < CHAR_HEIGHT; i++)
		{
			if (temp[j] & (1 << i))
			{
				if (size == 1)
				{
					ILI9341_Draw_Pixel(pos_x + j, pos_y + i, colour);
				}
				else
				{
					ILI9341_Draw_Rectangle(pos_x + (j * size), pos_y + (i * size), size, size, colour);
				}
			}
		}
	}
}

/*Draws an array of characters (fonts imported from fonts.h) at X,Y location with specified font colour, size and Background colour*/
/*See fonts.h implementation of font on what is required for changing to a different font when switching fonts libraries*/
void Graphic_Draw_Text(const char* text, uint8_t pos_x, uint8_t pos_y, uint16_t colour, uint16_t size, uint16_t background_colour)
{
    while (*text)
    {
        Graphic_Draw_Char(*text++, pos_x, pos_y, colour, size, background_colour);
        pos_x += CHAR_WIDTH*size;
    }
}
void Graphic_Draw_Filled_Rectangle_Size_Text(uint16_t pos_x0, uint16_t pos_y0, uint16_t size_x, uint16_t size_y, uint16_t colour)
{

}

/*Draws a full screen picture from flash. Image converted from RGB .jpeg/other to C array using online converter*/
//USING CONVERTER: http://www.digole.com/tools/PicturetoC_Hex_converter.php
//65K colour (2Bytes / Pixel)
void Graphic_Draw_Image(SPI_HandleTypeDef *hspi, const char* image, uint8_t orientation)
{
	if (orientation == SCREEN_HORIZONTAL_1)
	{
		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
		ILI9341_Set_Address(0, 0, ILI9341_SCREEN_WIDTH, ILI9341_SCREEN_HEIGHT);

		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);		// Pull low CS pin
		HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);		// Pull high DC pin

		unsigned char Temp_small_buffer[BURST_MAX_SIZE];
		uint32_t counter = 0;
		for (uint32_t i = 0; i < ILI9341_SCREEN_WIDTH * ILI9341_SCREEN_HEIGHT * 2 / BURST_MAX_SIZE; i++)
		{
			for (uint32_t k = 0; k < BURST_MAX_SIZE; k++)
			{
				Temp_small_buffer[k] = image[counter + k];
			}
			HAL_SPI_Transmit(hspi, (unsigned char*) Temp_small_buffer, BURST_MAX_SIZE, 10);
			counter += BURST_MAX_SIZE;
		}
		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
	}
	else if (orientation == SCREEN_HORIZONTAL_2)
	{
		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
		ILI9341_Set_Address(0, 0, ILI9341_SCREEN_WIDTH, ILI9341_SCREEN_HEIGHT);

		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);		// Pull low CS pin
		HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);		// Pull high DC pin

		unsigned char Temp_small_buffer[BURST_MAX_SIZE];
		uint32_t counter = 0;
		for (uint32_t i = 0; i < ILI9341_SCREEN_WIDTH * ILI9341_SCREEN_HEIGHT * 2 / BURST_MAX_SIZE; i++)
		{
			for (uint32_t k = 0; k < BURST_MAX_SIZE; k++)
			{
				Temp_small_buffer[k] = image[counter + k];
			}
			HAL_SPI_Transmit(hspi, (unsigned char*) Temp_small_buffer, BURST_MAX_SIZE, 10);
			counter += BURST_MAX_SIZE;
		}
		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
	}
	else if (orientation == SCREEN_VERTICAL_2)
	{
		ILI9341_Set_Rotation(SCREEN_VERTICAL_2);
		ILI9341_Set_Address(0, 0, ILI9341_SCREEN_HEIGHT, ILI9341_SCREEN_WIDTH);

		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);		// Pull low CS pin
		HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);		// Pull high DC pin

		unsigned char Temp_small_buffer[BURST_MAX_SIZE];
		uint32_t counter = 0;
		for (uint32_t i = 0; i < ILI9341_SCREEN_WIDTH * ILI9341_SCREEN_HEIGHT * 2 / BURST_MAX_SIZE; i++)
		{
			for (uint32_t k = 0; k < BURST_MAX_SIZE; k++)
			{
				Temp_small_buffer[k] = image[counter + k];
			}
			HAL_SPI_Transmit(hspi, (unsigned char*) Temp_small_buffer, BURST_MAX_SIZE, 10);
			counter += BURST_MAX_SIZE;
		}
		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
	}
	else if (orientation == SCREEN_VERTICAL_1)
	{
		ILI9341_Set_Rotation(SCREEN_VERTICAL_1);
		ILI9341_Set_Address(0, 0, ILI9341_SCREEN_HEIGHT, ILI9341_SCREEN_WIDTH);

		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);		// Pull low CS pin
		HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);		// Pull high DC pin

		unsigned char Temp_small_buffer[BURST_MAX_SIZE];
		uint32_t counter = 0;
		for (uint32_t i = 0; i < ILI9341_SCREEN_WIDTH * ILI9341_SCREEN_HEIGHT * 2 / BURST_MAX_SIZE; i++)
		{
			for (uint32_t k = 0; k < BURST_MAX_SIZE; k++)
			{
				Temp_small_buffer[k] = image[counter + k];
			}
			HAL_SPI_Transmit(hspi, (unsigned char*) Temp_small_buffer, BURST_MAX_SIZE, 10);
			counter += BURST_MAX_SIZE;
		}
		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
	}
}


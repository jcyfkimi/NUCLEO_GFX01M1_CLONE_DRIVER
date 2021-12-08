/*
 * ILI9341_Disp.c
 *
 *  Created on: Dec 7, 2021
 *      Author: Kimi Jin
 */


#include "ILI9341_Disp.h"
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal_gpio.h"

SPI_HandleTypeDef *hspi_instance;

/* Global Variables ------------------------------------------------------------------*/
volatile uint16_t LCD_HEIGHT = ILI9341_SCREEN_HEIGHT;
volatile uint16_t LCD_WIDTH	 = ILI9341_SCREEN_WIDTH;

/* Initialize SPI */
void ILI9341_SPI_Init(SPI_HandleTypeDef *hspi)
{
	hspi_instance = hspi;
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);		// Pull low CS pin
}

/*Send one byte data (char) to LCD*/
void ILI9341_SPI_Send(unsigned char data)
{
	HAL_SPI_Transmit(hspi_instance, &data, 1, 1);
}

/* Send one byte command (char) to LCD */
void ILI9341_Write_Command(uint8_t cmd)
{
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);		// Pull low CS pin
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);		// Pull low DC pin
	ILI9341_SPI_Send(cmd);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);		// Pull high CS pin
}

/* Send one byte data (char) to LCD */
void ILI9341_Write_Data(uint8_t data)
{
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);		// Pull high DC pin
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);		// Pull low CS pin
	ILI9341_SPI_Send(data);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);		// Pull high CS pin
}

/* Set Address - Location block - to draw into */
void ILI9341_Set_Address(uint16_t pos_x1, uint16_t pos_y1, uint16_t pos_x2, uint16_t pos_y2)
{
	ILI9341_Write_Command(0x2A);
	ILI9341_Write_Data(pos_x1>>8);
	ILI9341_Write_Data(pos_x1);
	ILI9341_Write_Data(pos_x2>>8);
	ILI9341_Write_Data(pos_x2);

	ILI9341_Write_Command(0x2B);
	ILI9341_Write_Data(pos_y1>>8);
	ILI9341_Write_Data(pos_y1);
	ILI9341_Write_Data(pos_y2>>8);
	ILI9341_Write_Data(pos_y2);

	ILI9341_Write_Command(0x2C);
}

/*HARDWARE RESET*/
void ILI9341_Reset(void)
{
	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_RESET);		// Pull low RST pin
	HAL_Delay(200);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);			// Pull low CS pin
	HAL_Delay(200);
	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);			// Pull high RST pin
}


/*Ser rotation of the screen - changes x0 and y0*/
void ILI9341_Set_Rotation(uint8_t rot)
{
	uint8_t screen_rotation = rot;

	ILI9341_Write_Command(0x36);
	HAL_Delay(1);

	switch (screen_rotation)
	{
	case SCREEN_VERTICAL_1:
		ILI9341_Write_Data(0x40 | 0x08);
		LCD_WIDTH = 240;
		LCD_HEIGHT = 320;
		break;
	case SCREEN_HORIZONTAL_1:
		ILI9341_Write_Data(0x20 | 0x08);
		LCD_WIDTH = 320;
		LCD_HEIGHT = 240;
		break;
	case SCREEN_VERTICAL_2:
		ILI9341_Write_Data(0x80 | 0x08);
		LCD_WIDTH = 240;
		LCD_HEIGHT = 320;
		break;
	case SCREEN_HORIZONTAL_2:
		ILI9341_Write_Data(0x40 | 0x80 | 0x20 | 0x08);
		LCD_WIDTH = 320;
		LCD_HEIGHT = 240;
		break;
	default:
		//EXIT IF SCREEN ROTATION NOT VALID!
		break;
	}
}

/*Enable LCD display*/
void ILI9341_Enable(void)
{
	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);		// Pull high RST pin
}


void ILI9341_Init(SPI_HandleTypeDef *hspi)
{
	ILI9341_Enable();
	ILI9341_SPI_Init(hspi);
	ILI9341_Reset();

	//SOFTWARE RESET
	ILI9341_Write_Command(0x01);
	HAL_Delay(1000);

	//POWER CONTROL A
	ILI9341_Write_Command(0xCB);
	ILI9341_Write_Data(0x39);
	ILI9341_Write_Data(0x2C);
	ILI9341_Write_Data(0x00);
	ILI9341_Write_Data(0x34);
	ILI9341_Write_Data(0x02);

	//POWER CONTROL B
	ILI9341_Write_Command(0xCF);
	ILI9341_Write_Data(0x00);
	ILI9341_Write_Data(0xC1);
	ILI9341_Write_Data(0x30);

	//DRIVER TIMING CONTROL A
	ILI9341_Write_Command(0xE8);
	ILI9341_Write_Data(0x85);
	ILI9341_Write_Data(0x00);
	ILI9341_Write_Data(0x78);

	//DRIVER TIMING CONTROL B
	ILI9341_Write_Command(0xEA);
	ILI9341_Write_Data(0x00);
	ILI9341_Write_Data(0x00);

	//POWER ON SEQUENCE CONTROL
	ILI9341_Write_Command(0xED);
	ILI9341_Write_Data(0x64);
	ILI9341_Write_Data(0x03);
	ILI9341_Write_Data(0x12);
	ILI9341_Write_Data(0x81);

	//PUMP RATIO CONTROL
	ILI9341_Write_Command(0xF7);
	ILI9341_Write_Data(0x20);

	//POWER CONTROL,VRH[5:0]
	ILI9341_Write_Command(0xC0);
	ILI9341_Write_Data(0x23);

	//POWER CONTROL,SAP[2:0];BT[3:0]
	ILI9341_Write_Command(0xC1);
	ILI9341_Write_Data(0x10);

	//VCM CONTROL
	ILI9341_Write_Command(0xC5);
	ILI9341_Write_Data(0x3E);
	ILI9341_Write_Data(0x28);

	//VCM CONTROL 2
	ILI9341_Write_Command(0xC7);
	ILI9341_Write_Data(0x86);

	//MEMORY ACCESS CONTROL
	ILI9341_Write_Command(0x36);
	ILI9341_Write_Data(0x48);

	//PIXEL FORMAT
	ILI9341_Write_Command(0x3A);
	ILI9341_Write_Data(0x55);

	//FRAME RATIO CONTROL, STANDARD RGB COLOR
	ILI9341_Write_Command(0xB1);
	ILI9341_Write_Data(0x00);
	ILI9341_Write_Data(0x18);

	//DISPLAY FUNCTION CONTROL
	ILI9341_Write_Command(0xB6);
	ILI9341_Write_Data(0x08);
	ILI9341_Write_Data(0x82);
	ILI9341_Write_Data(0x27);

	//3GAMMA FUNCTION DISABLE
	ILI9341_Write_Command(0xF2);
	ILI9341_Write_Data(0x00);

	//GAMMA CURVE SELECTED
	ILI9341_Write_Command(0x26);
	ILI9341_Write_Data(0x01);

	//POSITIVE GAMMA CORRECTION
	ILI9341_Write_Command(0xE0);
	ILI9341_Write_Data(0x0F);
	ILI9341_Write_Data(0x31);
	ILI9341_Write_Data(0x2B);
	ILI9341_Write_Data(0x0C);
	ILI9341_Write_Data(0x0E);
	ILI9341_Write_Data(0x08);
	ILI9341_Write_Data(0x4E);
	ILI9341_Write_Data(0xF1);
	ILI9341_Write_Data(0x37);
	ILI9341_Write_Data(0x07);
	ILI9341_Write_Data(0x10);
	ILI9341_Write_Data(0x03);
	ILI9341_Write_Data(0x0E);
	ILI9341_Write_Data(0x09);
	ILI9341_Write_Data(0x00);

	//NEGATIVE GAMMA CORRECTION
	ILI9341_Write_Command(0xE1);
	ILI9341_Write_Data(0x00);
	ILI9341_Write_Data(0x0E);
	ILI9341_Write_Data(0x14);
	ILI9341_Write_Data(0x03);
	ILI9341_Write_Data(0x11);
	ILI9341_Write_Data(0x07);
	ILI9341_Write_Data(0x31);
	ILI9341_Write_Data(0xC1);
	ILI9341_Write_Data(0x48);
	ILI9341_Write_Data(0x08);
	ILI9341_Write_Data(0x0F);
	ILI9341_Write_Data(0x0C);
	ILI9341_Write_Data(0x31);
	ILI9341_Write_Data(0x36);
	ILI9341_Write_Data(0x0F);

	//EXIT SLEEP
	ILI9341_Write_Command(0x11);
	HAL_Delay(120);

	//TURN ON DISPLAY
	ILI9341_Write_Command(0x29);

	//STARTING ROTATION
	ILI9341_Set_Rotation(SCREEN_VERTICAL_1);
}

/*Sends single pixel colour information to LCD*/
void ILI9341_Fill_Screen(uint16_t colour)
{
	ILI9341_Set_Address(0,0,LCD_WIDTH,LCD_HEIGHT);
	ILI9341_Draw_Colour_Burst(colour, LCD_WIDTH*LCD_HEIGHT);
}


void ILI9341_Draw_Colour(uint16_t colour)
{
	//SENDS COLOUR
	unsigned char buffer[2] = {colour>>8, colour};
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	HAL_SPI_Transmit(hspi_instance, buffer, 2, 1);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

//DRAW PIXEL AT XY POSITION WITH SELECTED COLOUR
//
//Location is dependant on screen orientation. x0 and y0 locations change with orientations.
//Using pixels to draw big simple structures is not recommended as it is really slow
//Try using either rectangles or lines if possible
//
void ILI9341_Draw_Pixel(uint16_t pos_x,uint16_t pos_y,uint16_t colour)
{
	if ((pos_x >= LCD_WIDTH) || (pos_y >= LCD_HEIGHT))
	{
		return;	//OUT OF BOUNDS!
	}

	//ADDRESS
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	ILI9341_SPI_Send(0x2A);
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);

	//XDATA
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	unsigned char tmp_buffer[4] = { pos_x >> 8, pos_x, (pos_x + 1) >> 8, (pos_x + 1) };
	HAL_SPI_Transmit(hspi_instance, tmp_buffer, 4, 1);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);

	//ADDRESS
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	ILI9341_SPI_Send(0x2B);
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);

	//YDATA
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	unsigned char tmp_buffer1[4] = { pos_y >> 8, pos_y, (pos_y + 1) >> 8, (pos_y + 1) };
	HAL_SPI_Transmit(hspi_instance, tmp_buffer1, 4, 1);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);

	//ADDRESS
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	ILI9341_SPI_Send(0x2C);
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);

	//COLOUR
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	unsigned char tmp_buffer2[2] = { colour >> 8, colour };
	HAL_SPI_Transmit(hspi_instance, tmp_buffer2, 2, 1);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

/*Sends block colour information to LCD*/
void ILI9341_Draw_Colour_Burst(uint16_t colour, uint32_t size)
{
	//SENDS COLOUR
	uint32_t buffer_size = 0;
	if ((size * 2) < BURST_MAX_SIZE)
	{
		buffer_size = size;
	}
	else
	{
		buffer_size = BURST_MAX_SIZE;
	}

	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);

	unsigned char chifted = colour >> 8;
	;
	unsigned char burst_buffer[buffer_size];
	for (uint32_t j = 0; j < buffer_size; j += 2)
	{
		burst_buffer[j] = chifted;
		burst_buffer[j + 1] = colour;
	}

	uint32_t snd_size = size * 2;
	uint32_t snd_in_blk = snd_size / buffer_size;
	uint32_t remainder_size = snd_size % buffer_size;

	if (snd_in_blk != 0)
	{
		for (uint32_t j = 0; j < (snd_in_blk); j++)
		{
			HAL_SPI_Transmit(hspi_instance, (unsigned char*) burst_buffer,buffer_size, 10);
		}
	}

	//REMAINDER!
	HAL_SPI_Transmit(hspi_instance, (unsigned char*) burst_buffer, remainder_size, 10);

	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);

}


//DRAW RECTANGLE OF SET SIZE AND HEIGTH AT X and Y POSITION WITH CUSTOM COLOUR
//
//Rectangle is hollow. X and Y positions mark the upper left corner of rectangle
//As with all other draw calls x0 and y0 locations dependant on screen orientation
//
void ILI9341_Draw_Rectangle(uint16_t pos_x, uint16_t pos_y, uint16_t width, uint16_t height, uint16_t colour)
{
	if ((pos_x >= LCD_WIDTH) || (pos_y >= LCD_HEIGHT))
	{
		return;
	}
	if ((pos_x + width - 1) >= LCD_WIDTH)
	{
		width = LCD_WIDTH - pos_x;
	}
	if ((pos_y + height - 1) >= LCD_HEIGHT)
	{
		height = LCD_HEIGHT - pos_y;
	}
	ILI9341_Set_Address(pos_x, pos_y, pos_x + width - 1, pos_y + height - 1);
	ILI9341_Draw_Colour_Burst(colour, height * width);
}

//DRAW LINE FROM X,Y LOCATION to X+Width,Y LOCATION
void ILI9341_Draw_Horizontal_Line(uint16_t pos_x, uint16_t pos_y, uint16_t width, uint16_t colour)
{
	if ((pos_x >= LCD_WIDTH) || (pos_y >= LCD_HEIGHT))
	{
		return;
	}
	if ((pos_x + width - 1) >= LCD_WIDTH)
	{
		width = LCD_WIDTH - pos_x;
	}
	ILI9341_Set_Address(pos_x, pos_y, pos_x + width - 1, pos_y);
	ILI9341_Draw_Colour_Burst(colour, width);
}

//DRAW LINE FROM X,Y LOCATION to X,Y+Height LOCATION
void ILI9341_Draw_Vertical_Line(uint16_t pos_x, uint16_t pos_y, uint16_t height, uint16_t colour)
{
	if ((pos_x >= LCD_WIDTH) || (pos_y >= LCD_HEIGHT))
	{
		return;
	}

	if ((pos_y + height - 1) >= LCD_HEIGHT)
	{
		height = LCD_HEIGHT - pos_y;
	}
	ILI9341_Set_Address(pos_x, pos_y, pos_x, pos_y + height - 1);
	ILI9341_Draw_Colour_Burst(colour, height);
}


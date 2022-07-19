/*
 * lcd_ili9341.c
 *
 *  Created on: Jul 12, 2022
 *      Author: Kimi
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "lcd_ili9341.h"

extern SPI_HandleTypeDef hspi1;

volatile uint16_t LCD_HEIGHT = ILI9341_SCREEN_HEIGHT;
volatile uint16_t LCD_WIDTH	 = ILI9341_SCREEN_WIDTH;

static void WriteCommand(uint8_t cmd);
static void WriteDataByte(uint8_t dat);

static void WriteCommand(uint8_t cmd)
{
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);		// Pull low CS pin
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);		// Pull high CS pin
}

static void WriteDataByte(uint8_t dat)
{
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);		// Pull low CS pin
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
	HAL_SPI_Transmit(&hspi1, &dat, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);		// Pull high CS pin
}
void disp_set_rotation(uint8_t rot)
{
	uint8_t screen_rotation = rot;

	WriteCommand(0x36);
	HAL_Delay(1);

	switch (screen_rotation) {
	case SCREEN_VERTICAL_1:
		WriteDataByte(0x40 | 0x08);
		LCD_WIDTH = 240;
		LCD_HEIGHT = 320;
		break;
	case SCREEN_HORIZONTAL_1:
		WriteDataByte(0x20 | 0x08);
		LCD_WIDTH = 320;
		LCD_HEIGHT = 240;
		break;
	case SCREEN_VERTICAL_2:
		WriteDataByte(0x80 | 0x08);
		LCD_WIDTH = 240;
		LCD_HEIGHT = 320;
		break;
	case SCREEN_HORIZONTAL_2:
		WriteDataByte(0x40 | 0x80 | 0x20 | 0x08);
		LCD_WIDTH = 320;
		LCD_HEIGHT = 240;
		break;
	default:
		//EXIT IF SCREEN ROTATION NOT VALID!
		break;
	}
}

/*Enable LCD display*/
void disp_enable(void)
{
	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);		// Pull high RST pin
}
void disp_spi_init(void)
{
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);		// Pull low CS pin
}

/*HARDWARE RESET*/
void disp_reset(void)
{
	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_RESET);		// Pull low RST pin
	HAL_Delay(200);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);			// Pull low CS pin
	HAL_Delay(200);
	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);			// Pull high RST pin
}

void disp_init(void)
{
	disp_enable();
	disp_spi_init();
	disp_reset();

	//SOFTWARE RESET
	WriteCommand(0x01);
	HAL_Delay(1000);

	//POWER CONTROL A
	WriteCommand(0xCB);
	WriteDataByte(0x39);
	WriteDataByte(0x2C);
	WriteDataByte(0x00);
	WriteDataByte(0x34);
	WriteDataByte(0x02);

	//POWER CONTROL B
	WriteCommand(0xCF);
	WriteDataByte(0x00);
	WriteDataByte(0xC1);
	WriteDataByte(0x30);

	//DRIVER TIMING CONTROL A
	WriteCommand(0xE8);
	WriteDataByte(0x85);
	WriteDataByte(0x00);
	WriteDataByte(0x78);

	//DRIVER TIMING CONTROL B
	WriteCommand(0xEA);
	WriteDataByte(0x00);
	WriteDataByte(0x00);

	//POWER ON SEQUENCE CONTROL
	WriteCommand(0xED);
	WriteDataByte(0x64);
	WriteDataByte(0x03);
	WriteDataByte(0x12);
	WriteDataByte(0x81);

	//PUMP RATIO CONTROL
	WriteCommand(0xF7);
	WriteDataByte(0x20);

	//POWER CONTROL,VRH[5:0]
	WriteCommand(0xC0);
	WriteDataByte(0x23);

	//POWER CONTROL,SAP[2:0];BT[3:0]
	WriteCommand(0xC1);
	WriteDataByte(0x10);

	//VCM CONTROL
	WriteCommand(0xC5);
	WriteDataByte(0x3E);
	WriteDataByte(0x28);

	//VCM CONTROL 2
	WriteCommand(0xC7);
	WriteDataByte(0x86);

	//MEMORY ACCESS CONTROL
	WriteCommand(0x36);
	WriteDataByte(0x48);

	//PIXEL FORMAT
	WriteCommand(0x3A);
	WriteDataByte(0x55);

	//FRAME RATIO CONTROL, STANDARD RGB COLOR
	WriteCommand(0xB1);
	WriteDataByte(0x00);
	WriteDataByte(0x18);

	//DISPLAY FUNCTION CONTROL
	WriteCommand(0xB6);
	WriteDataByte(0x08);
	WriteDataByte(0x82);
	WriteDataByte(0x27);

	//3GAMMA FUNCTION DISABLE
	WriteCommand(0xF2);
	WriteDataByte(0x00);

	//GAMMA CURVE SELECTED
	WriteCommand(0x26);
	WriteDataByte(0x01);

	//POSITIVE GAMMA CORRECTION
	WriteCommand(0xE0);
	WriteDataByte(0x0F);
	WriteDataByte(0x31);
	WriteDataByte(0x2B);
	WriteDataByte(0x0C);
	WriteDataByte(0x0E);
	WriteDataByte(0x08);
	WriteDataByte(0x4E);
	WriteDataByte(0xF1);
	WriteDataByte(0x37);
	WriteDataByte(0x07);
	WriteDataByte(0x10);
	WriteDataByte(0x03);
	WriteDataByte(0x0E);
	WriteDataByte(0x09);
	WriteDataByte(0x00);

	//NEGATIVE GAMMA CORRECTION
	WriteCommand(0xE1);
	WriteDataByte(0x00);
	WriteDataByte(0x0E);
	WriteDataByte(0x14);
	WriteDataByte(0x03);
	WriteDataByte(0x11);
	WriteDataByte(0x07);
	WriteDataByte(0x31);
	WriteDataByte(0xC1);
	WriteDataByte(0x48);
	WriteDataByte(0x08);
	WriteDataByte(0x0F);
	WriteDataByte(0x0C);
	WriteDataByte(0x31);
	WriteDataByte(0x36);
	WriteDataByte(0x0F);

	//EXIT SLEEP
	WriteCommand(0x11);
	HAL_Delay(120);

	//TURN ON DISPLAY
	WriteCommand(0x29);

	//STARTING ROTATION
	disp_set_rotation(SCREEN_VERTICAL_1);
}

void disp_set_address_window(uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd)
{
	WriteCommand(0x2A);
	WriteDataByte(xStar >> 8);
	WriteDataByte(0x00FF & xStar);
	WriteDataByte(xEnd >> 8);
	WriteDataByte(0x00FF & xEnd);

	WriteCommand(0x2B);
	WriteDataByte(yStar >> 8);
	WriteDataByte(0x00FF & yStar);
	WriteDataByte(yEnd >> 8);
	WriteDataByte(0x00FF & yEnd);

	WriteCommand(0x2C);
}

void disp_draw_pixel(uint16_t xPos,uint16_t yPos,uint16_t pData)
{
	unsigned char tmp_buffer[4];

	//ADDRESS
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	WriteDataByte(0x2A);
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);

	//XDATA
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	memset(&tmp_buffer, 0, sizeof(tmp_buffer));
	tmp_buffer[0] = xPos >> 8;
	tmp_buffer[1] = xPos;
	tmp_buffer[2] = (xPos + 1) >> 8;
	tmp_buffer[3] = (xPos + 1);
	HAL_SPI_Transmit(&hspi1, tmp_buffer, 4, 1);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);

	//ADDRESS
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	WriteDataByte(0x2B);
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);

	//YDATA
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	memset(&tmp_buffer, 0, sizeof(tmp_buffer));
	tmp_buffer[0] = yPos >> 8;
	tmp_buffer[1] = yPos;
	tmp_buffer[2] = (yPos + 1) >> 8;
	tmp_buffer[3] = (yPos + 1);
	HAL_SPI_Transmit(&hspi1, tmp_buffer, 4, 1);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);

	//ADDRESS
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	WriteDataByte(0x2C);
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);

	//data
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	memset(&tmp_buffer, 0, sizeof(tmp_buffer));
	tmp_buffer[0] = pData >> 8;
	tmp_buffer[1] = pData;
	HAL_SPI_Transmit(&hspi1, tmp_buffer, 2, 1);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}



/*Sends single pixel colour information to LCD*/
void disp_fill_screen(uint16_t color)
{
	disp_set_address_window(0,0,LCD_WIDTH,LCD_HEIGHT);
	disp_draw_color_burst(color, LCD_WIDTH*LCD_HEIGHT);
}

/*Sends block colour information to LCD*/
void disp_draw_color_burst(uint16_t color, uint32_t size)
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

	unsigned char chifted = color >> 8;
	unsigned char burst_buffer[buffer_size];
	for (uint32_t j = 0; j < buffer_size; j += 2)
	{
		burst_buffer[j] = chifted;
		burst_buffer[j + 1] = color;
	}

	uint32_t snd_size = size * 2;
	uint32_t snd_in_blk = snd_size / buffer_size;
	uint32_t remainder_size = snd_size % buffer_size;

	if (snd_in_blk != 0)
	{
		for (uint32_t j = 0; j < (snd_in_blk); j++)
		{
			HAL_SPI_Transmit(&hspi1, (unsigned char*) burst_buffer,buffer_size, 10);
		}
	}

	//REMAINDER!
	HAL_SPI_Transmit(&hspi1, (unsigned char*) burst_buffer, remainder_size, 10);

	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);

}


void disp_draw_bitmap(uint8_t *pData, uint32_t size)
{
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, pData, size, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

void disp_SPI_TxCpltCallback(void)
{
	// Just pull high the cs pin
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}


void disp_draw_color_dma(uint8_t *pData, uint32_t size)
{
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	HAL_SPI_Transmit_DMA(&hspi1, pData ,size);
}

void disp_draw_bitmap_dma(uint8_t *pData, uint32_t size)
{
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	HAL_SPI_Transmit_DMA(&hspi1, pData, size);
}

void disp_fill_screen_dma(uint16_t color)
{
	uint16_t *buff;
	uint16_t size;
	int i = 0;

	size = LCD_WIDTH*LCD_HEIGHT*2;

	buff = (uint16_t *) malloc(size);
	if(NULL != buff)
	{
		// Fill in buffer
		for(i = 0; i < size/2; i++)
		{
			buff[i] = color;
		}

		disp_set_address_window(0,0,LCD_WIDTH,LCD_HEIGHT);
		disp_draw_color_dma((uint8_t *)buff, LCD_WIDTH*LCD_HEIGHT*2);
	}

}


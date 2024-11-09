/**
 ******************************************************************************
 * @file           : I2C_LCD.c
 * @author         : Danh Phan
 * @brief          : Library to interact to LCD peripheral by I2C protocol
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 *							REVISION HISTORY
 * Version 1.0.0: Initial release
 ******************************************************************************
 */


// Include libraries
#include "I2C_LCD.h"


// APIs
void i2c_lcd_send_cmd (I2C_HandleTypeDef *p_h2ic, uint16_t devAdrr, uint8_t cmd)	// RS = 0 (command)
{
	uint8_t data_h, data_l;
	uint8_t data_t[4];
	data_h = cmd & LCD_DATA_MASK;
	data_l = (cmd<<4) & LCD_DATA_MASK;
	data_t[0] = data_h | LCD_EN_MASK | LCD_BT_MASK;  // EN = 1
	data_t[1] = data_h | LCD_BT_MASK;  				 // EN = 0
	data_t[2] = data_l | LCD_EN_MASK | LCD_BT_MASK;  // EN = 1
	data_t[3] = data_l | LCD_BT_MASK;  				 // EN = 0
	HAL_I2C_Master_Transmit(p_h2ic, devAdrr, data_t, 4, 100);
}


void i2c_lcd_send_char (I2C_HandleTypeDef *p_h2ic, uint16_t devAdrr, uint8_t data)	// RS = 1 (data)
{
	uint8_t data_h, data_l;
	uint8_t data_t[4];
	data_h = data & LCD_DATA_MASK;
	data_l = (data<<4) & LCD_DATA_MASK;
	data_t[0] = data_h | LCD_EN_MASK | LCD_RS_MASK | LCD_BT_MASK;  		// EN = 1
	data_t[1] = data_h | LCD_RS_MASK | LCD_BT_MASK;  					// EN = 0
	data_t[2] = data_l | LCD_EN_MASK | LCD_RS_MASK | LCD_BT_MASK;  		// EN = 1
	data_t[3] = data_l | LCD_RS_MASK | LCD_BT_MASK;  					// EN = 0
	HAL_I2C_Master_Transmit(p_h2ic, devAdrr, data_t, 4, 100);
}


void i2c_lcd_init (I2C_HandleTypeDef *p_h2ic, uint16_t devAdrr)
{
	HAL_Delay(50);
	i2c_lcd_send_cmd (p_h2ic, devAdrr, 0x02);		// Return home
	HAL_Delay(1);
	i2c_lcd_send_cmd(p_h2ic, devAdrr, 0x28);		// Function set (4 bit mode, 2 line display)
	HAL_Delay(1);
	i2c_lcd_send_cmd(p_h2ic, devAdrr, 0x01);		// Clear display
	HAL_Delay(1);
	i2c_lcd_send_cmd(p_h2ic, devAdrr, 0x06);		// Entry mode set (increment cursor, no shift)
	HAL_Delay(1);
	i2c_lcd_send_cmd(p_h2ic, devAdrr, 0x0C);		// Display on
	HAL_Delay(1);
}


void i2c_lcd_send_string (I2C_HandleTypeDef *p_h2ic, uint16_t devAdrr, uint8_t *p_str)
{
	while (*p_str)
		i2c_lcd_send_char(p_h2ic, devAdrr, *p_str++);
}


void i2c_lcd_set_position (I2C_HandleTypeDef *p_h2ic, uint16_t devAdrr, uint8_t row, uint8_t col)
{
	uint8_t address = 0x80;
	switch (row)
	{
		case 1:
			address |= ROW_1_BASE;
			break;
		case 2:
			address |= ROW_2_BASE;
			break;
		case 3:
			address |= ROW_3_BASE;
			break;
		case 4:
			address |= ROW_4_BASE;
			break;
		default:
			break;
	}
	address += (col - 1);
	i2c_lcd_send_cmd(p_h2ic, devAdrr, address);
}


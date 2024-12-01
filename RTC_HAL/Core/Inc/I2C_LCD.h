/**
 ******************************************************************************
 * @file           : I2C_LCD.h
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
#ifndef INC_I2C_LCD_H_
#define INC_I2C_LCD_H_


// Include libraries
#include "stm32f4xx_hal.h"


// Variables


// Macroes
/* 				I/0 port between I2C module and LCD
 * P0 P1 P2 P3 P4 P5 P6 P7
 * RS RW EN BT D4 D5 D6 D7
 * */
#define LCD_DATA_MASK 0xF0
#define LCD_BT_MASK 0x08
#define LCD_EN_MASK 0x04
#define LCD_RW_MASK 0x02
#define LCD_RS_MASK 0x01

#define ROW_1_BASE 0x00
#define ROW_2_BASE 0x40
#define ROW_3_BASE 0x14
#define ROW_4_BASE 0x54


// Prototypes
/**
  * @brief  Initialize lcd
  * @param  *p_hi2c: pointer to I2C instance
  * @param  devAdrr: address of device
  * @retval None
  */
void i2c_lcd_init (I2C_HandleTypeDef *p_hi2c, uint16_t devAdrr);


/**
  * @brief  Send command to the lcd
  * @param  *p_hi2c: pointer to I2C instance
  * @param  devAdrr: address of device
  * @param  cmd: 1 byte data to control operation of lcd
  * @retval None
  */
void i2c_lcd_send_cmd (I2C_HandleTypeDef *p_hi2c, uint16_t devAdrr, uint8_t cmd);


/**
  * @brief  Send data to the lcd
  * @param  *p_hi2c: pointer to I2C instance
  * @param  devAdrr: address of device
  * @param  data: 1 byte data to send to lcd
  * @retval None
  */
void i2c_lcd_send_char (I2C_HandleTypeDef *p_hi2c, uint16_t devAdrr, uint8_t data);


/**
  * @brief  Send string to the lcd
  * @param  *p_hi2c: pointer to I2C instance
  * @param  devAdrr: address of device
  * @param  str: 1 pointer to string to display on lcd
  * @retval None
  */
void i2c_lcd_send_string (I2C_HandleTypeDef *p_hi2c, uint16_t devAdrr, uint8_t *str);


/**
  * @brief  Set position to display data on LCD
  * @param  *p_hi2c: pointer to I2C instance
  * @param  devAdrr: address of device
  * @param  row: row position (1-index)
  * @param  col: col position (1-index)
  * @retval None
  */
void i2c_lcd_set_position (I2C_HandleTypeDef *p_h2ic, uint16_t devAdrr, uint8_t row, uint8_t col);


#endif /* INC_I2C_LCD_H_ */

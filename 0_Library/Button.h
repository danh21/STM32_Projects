/**
 ******************************************************************************
 * @file           : Button.h
 * @author         : Danh Phan
 * @brief          : Library to interact to Button
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
#ifndef BUTTON_H_
#define BUTTON_H_


// Include libraries
#include <stm32f407xx.h>
#include <stdbool.h>


// Macroes


// Data types
typedef enum {
	pull_down,
	pull_up
} GPIO_pull;


// Prototypes
/**
  * @brief  Initialize port of button
  * @param  pPort: pointer to GPIO port
  * @retval None
  */
void Btn_init(GPIO_TypeDef* pPort);


/**
  * @brief  Check whether button is pressed or not
  * @param  pPort: pointer to GPIO port
  * @param  pin: pin of port
  * @param  pull: pull-up or pull-down
  * @retval status of button
  */
_Bool btn_isPressed (GPIO_TypeDef* pPort, uint8_t pin, GPIO_pull pull);


/**
  * @brief  Wait until button is released
  * @param  pPort: pointer to GPIO port
  * @param  pin: pin of port
  * @param  pull: pull-up or pull-down
  * @retval status of button
  */
void waitUntil_btn_isReleased(GPIO_TypeDef* pPort, uint8_t pin, GPIO_pull pull);


#endif /* BUTTON_H_ */

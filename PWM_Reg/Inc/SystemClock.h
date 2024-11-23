/**
 ******************************************************************************
 * @file           : SystemClock.h
 * @author         : Danh Phan
 * @brief          : Library to interact to system clock of MCU
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
#ifndef SYSTEMCLOCK_H_
#define SYSTEMCLOCK_H_


// Include libraries
#include <stm32f407xx.h>


// Macroes


// Prototypes
/**
  * @brief  Initialize default system clock
  * @param  None
  * @retval None
  */
void SystemClock_config(void);


/**
  * @brief  Returns the HCLK frequency
  * @param  None
  * @retval None
  */
uint32_t Get_HCLK_freq(void);


/**
  * @brief  Returns the PCLK1 frequency
  * @param  None
  * @retval None
  */
uint32_t Get_PCLK1_freq(void);


/**
  * @brief  Returns the PCLK2 frequency
  * @param  None
  * @retval None
  */
uint32_t Get_PCLK2_freq(void);


#endif /* SYSTEMCLOCK_H_ */

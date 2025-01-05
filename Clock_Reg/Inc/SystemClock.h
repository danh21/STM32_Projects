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
 * Version 1.1.0: Modify comments, add SystemClock_config_MCO1 function
 * Version 1.2.0: Modify SystemClock_config_MCO1 function to add div param;
 * rename SystemClock_config to SystemClock_config_HSI; add SystemClock_config_HSE
 ******************************************************************************
 */
#ifndef SYSTEMCLOCK_H_
#define SYSTEMCLOCK_H_


// Include libraries
#include <stm32f407xx.h>


// Macroes


// Prototypes
/**
  * @brief  Initialize default system clock as HSI
  * @param  None
  * @retval None
  */
void SystemClock_config_HSI(void);


/**
  * @brief  Initialize default system clock as HSE
  * @param  None
  * @retval None
  */
void SystemClock_config_HSE(void);


/**
  * @brief  Returns the internal AHB clock frequency
  * @param  None
  * @retval HCLK frequency
  */
uint32_t SystemClock_get_HCLK_freq(void);


/**
  * @brief  Returns the internal APB1 clock frequency
  * @param  None
  * @retval PCLK1 frequency
  */
uint32_t SystemClock_get_PCLK1_freq(void);


/**
  * @brief  Returns the internal APB2 clock frequency
  * @param  None
  * @retval PCLK2 frequency
  */
uint32_t SystemClock_get_PCLK2_freq(void);


/**
  * @brief  Config MCO (Microcontroller Clock Output)
  * @param  div: prescaler (division by 2->5)
  * @retval None
  */
void SystemClock_config_MCO1(uint8_t div);


#endif /* SYSTEMCLOCK_H_ */

/**
 ******************************************************************************
 * @file           : Timer.h
 * @author         : Danh Phan
 * @brief          : Library to interact to Timer
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
 * Version 1.1.0: Add PWM mode and software delay
 ******************************************************************************
 */
#ifndef TIMER_H_
#define TIMER_H_

// Include libraries
#include <stm32f407xx.h>
#include "SystemClock.h"



// Data struct
typedef struct PWM_ctrl {
	TIM_TypeDef *pTIM;			// input Timer
	uint8_t channel;			// input channel
	GPIO_TypeDef *pPort;		// correspond output port
	int pin;					// correspond output pin
} PWM_ctrl_t;



// Macroes
#define T_timer		0.001		// expect 1ms
#define AutoReload	2000		// Auto-reload value



// Prototypes
/**
  * @brief  stuff delay
  * @param  time: stuff delay
  * @retval None
  */
void Software_delay(uint32_t time);

/**
  * @brief  Initialize Timer
  * @param  pTIM: pointer to timer instance
  * @retval None
  */
void Timer_init(TIM_TypeDef *pTIM);

/**
  * @brief  delay by ms
  * @param  pTIM: pointer to timer instance
  * @param  ms: delay by milisecond
  * @retval None
  */
void Timer_delay_ms(TIM_TypeDef *pTIM, uint32_t ms);

/**
  * @brief  initialize PWM
  * @param  pCtrl: pointer to PWM instance

  * @retval None
  */
void PWM_init(PWM_ctrl_t *pCtrl);

/**
  * @brief  generate PWM auto
  * @param  pCtrl: pointer to PWM instance
  * @retval None
  */
void PWM_generate_auto(PWM_ctrl_t *pCtrl);



#endif /* TIMER_H_ */

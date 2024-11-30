/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : STM32 works with FreeRTOS
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
  * 						REVISION HISTORY
  *	Version 1.0.0: Initial release
  *	Version 2.0.0: Use button to switch task and use Mutex to avoid accessing to resource at the same time
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct led_ctrl {
	uint32_t task;
	uint16_t led;
	uint16_t pin;
	GPIO_TypeDef *port;
} led_ctrl_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
osThreadId ctrl_led1Handle;
osThreadId ctrl_led2Handle;
osThreadId ctrl_led3Handle;
osMutexId myMutex01Handle;
/* USER CODE BEGIN PV */
led_ctrl_t ctrl_led1_instance = {
	1,
	1,
	led1_Pin,
	led1_GPIO_Port
};

led_ctrl_t ctrl_led2_instance = {
	2,
	2,
	led2_Pin,
	led2_GPIO_Port
};

led_ctrl_t ctrl_led3_instance = {
	3,
	3,
	led3_Pin,
	led3_GPIO_Port
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void ctrl_led1_entry(void const * argument);
void ctrl_led2_entry(void const * argument);
void ctrl_led3_entry(void const * argument);

/* USER CODE BEGIN PFP */
void handleTask(uint32_t task, uint16_t led, uint16_t pin, GPIO_TypeDef *port);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len) {
  for (int DataIdx = 0; DataIdx < len; DataIdx++)
    ITM_SendChar(*ptr++);
  return len;
}


void handleTask(uint32_t task, uint16_t led, uint16_t pin, GPIO_TypeDef *port)
{
	osMutexWait(myMutex01Handle, osWaitForever);

	printf("\nTask %ld starts\n", task);
	printf("LED %d ON\n", led);
	HAL_GPIO_WritePin(port, pin, 1);
	HAL_Delay(1000);

	printf("Waiting for pressed button\n");
	if (HAL_GPIO_ReadPin(btn_GPIO_Port, btn_Pin) == 0)
		while (HAL_GPIO_ReadPin(btn_GPIO_Port, btn_Pin) == 0);
	printf("Button is pressed\n");

	HAL_GPIO_WritePin(port, pin, 0);
	printf("LED %d OFF\n", led);
	printf("Task %ld finishes\n", task);

	osMutexRelease(myMutex01Handle);
	osDelay(200);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Create the mutex(es) */
  /* definition and creation of myMutex01 */
  osMutexDef(myMutex01);
  myMutex01Handle = osMutexCreate(osMutex(myMutex01));

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of ctrl_led1 */
  osThreadDef(ctrl_led1, ctrl_led1_entry, osPriorityNormal, 0, 128);
  ctrl_led1Handle = osThreadCreate(osThread(ctrl_led1), (void*) &ctrl_led1_instance);

  /* definition and creation of ctrl_led2 */
  osThreadDef(ctrl_led2, ctrl_led2_entry, osPriorityNormal, 0, 128);
  ctrl_led2Handle = osThreadCreate(osThread(ctrl_led2), (void*) &ctrl_led2_instance);

  /* definition and creation of ctrl_led3 */
  osThreadDef(ctrl_led3, ctrl_led3_entry, osPriorityNormal, 0, 128);
  ctrl_led3Handle = osThreadCreate(osThread(ctrl_led3), (void*) &ctrl_led3_instance);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, led1_Pin|led2_Pin|led3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : btn_Pin */
  GPIO_InitStruct.Pin = btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : led1_Pin led2_Pin led3_Pin */
  GPIO_InitStruct.Pin = led1_Pin|led2_Pin|led3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_ctrl_led1_entry */
/**
  * @brief  Function implementing the ctrl_led1 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_ctrl_led1_entry */
void ctrl_led1_entry(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
	  led_ctrl_t *args = (led_ctrl_t *) argument;
	  handleTask(args->task, args->led, args->pin, args->port);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_ctrl_led2_entry */
/**
* @brief Function implementing the ctrl_led2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ctrl_led2_entry */
void ctrl_led2_entry(void const * argument)
{
  /* USER CODE BEGIN ctrl_led2_entry */
  /* Infinite loop */
  for(;;)
  {
	  led_ctrl_t *args = (led_ctrl_t *) argument;
	  handleTask(args->task, args->led, args->pin, args->port);
  }
  /* USER CODE END ctrl_led2_entry */
}

/* USER CODE BEGIN Header_ctrl_led3_entry */
/**
* @brief Function implementing the ctrl_led3 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ctrl_led3_entry */
void ctrl_led3_entry(void const * argument)
{
  /* USER CODE BEGIN ctrl_led3_entry */
  /* Infinite loop */
  for(;;)
  {
	  led_ctrl_t *args = (led_ctrl_t *) argument;
	  handleTask(args->task, args->led, args->pin, args->port);
  }
  /* USER CODE END ctrl_led3_entry */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

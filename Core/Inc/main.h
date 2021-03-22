/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PA0_Pin GPIO_PIN_0
#define PA0_GPIO_Port GPIOA
#define PA0_EXTI_IRQn EXTI0_IRQn
#define LD12_Pin GPIO_PIN_12
#define LD12_GPIO_Port GPIOD
#define LD13_Pin GPIO_PIN_13
#define LD13_GPIO_Port GPIOD
#define LD14_Pin GPIO_PIN_14
#define LD14_GPIO_Port GPIOD
#define LD15_Pin GPIO_PIN_15
#define LD15_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */
#define R1_PORT GPIOD
#define R1_PIN GPIO_PIN_7

#define R2_PORT GPIOD
#define R2_PIN GPIO_PIN_6

#define R3_PORT GPIOD
#define R3_PIN GPIO_PIN_5

#define R4_PORT GPIOD
#define R4_PIN GPIO_PIN_4

#define C1_PORT GPIOD
#define C1_PIN GPIO_PIN_3

#define C2_PORT GPIOD
#define C2_PIN GPIO_PIN_2

#define C3_PORT GPIOD
#define C3_PIN GPIO_PIN_1

#define C4_PORT GPIOC
#define C4_PIN GPIO_PIN_12

#define ALERT_1 "    ALARM!   "
#define ALERT_2 "   WSTAWAJ!!!   "

struct time{
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;;
	uint8_t days;;
	uint8_t months;
	uint8_t years;
};
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

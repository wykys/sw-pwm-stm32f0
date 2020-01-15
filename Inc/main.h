/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "stm32f0xx_hal.h"

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
#define PWM7_Pin GPIO_PIN_0
#define PWM7_GPIO_Port GPIOF
#define PWM8_Pin GPIO_PIN_1
#define PWM8_GPIO_Port GPIOF
#define PWM14_Pin GPIO_PIN_0
#define PWM14_GPIO_Port GPIOA
#define PWM15_Pin GPIO_PIN_1
#define PWM15_GPIO_Port GPIOA
#define PWM16_Pin GPIO_PIN_3
#define PWM16_GPIO_Port GPIOA
#define PWM17_Pin GPIO_PIN_4
#define PWM17_GPIO_Port GPIOA
#define PWM18_Pin GPIO_PIN_5
#define PWM18_GPIO_Port GPIOA
#define PWM19_Pin GPIO_PIN_6
#define PWM19_GPIO_Port GPIOA
#define PWM20_Pin GPIO_PIN_7
#define PWM20_GPIO_Port GPIOA
#define PWM3_Pin GPIO_PIN_0
#define PWM3_GPIO_Port GPIOB
#define PWM6_Pin GPIO_PIN_1
#define PWM6_GPIO_Port GPIOB
#define PWM9_Pin GPIO_PIN_8
#define PWM9_GPIO_Port GPIOA
#define PWM0_Pin GPIO_PIN_9
#define PWM0_GPIO_Port GPIOA
#define PWM1_Pin GPIO_PIN_10
#define PWM1_GPIO_Port GPIOA
#define PWM10_Pin GPIO_PIN_11
#define PWM10_GPIO_Port GPIOA
#define PWM2_Pin GPIO_PIN_12
#define PWM2_GPIO_Port GPIOA
#define PWM13_Pin GPIO_PIN_3
#define PWM13_GPIO_Port GPIOB
#define PWM12_Pin GPIO_PIN_4
#define PWM12_GPIO_Port GPIOB
#define PWM11_Pin GPIO_PIN_5
#define PWM11_GPIO_Port GPIOB
#define PWM5_Pin GPIO_PIN_6
#define PWM5_GPIO_Port GPIOB
#define PWM4_Pin GPIO_PIN_7
#define PWM4_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

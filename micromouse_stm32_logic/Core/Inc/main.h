/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
ADC_HandleTypeDef* Get_HADC1_Ptr(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DEBUG_LED_Pin GPIO_PIN_13
#define DEBUG_LED_GPIO_Port GPIOC
#define Right_Receiver_Pin GPIO_PIN_0
#define Right_Receiver_GPIO_Port GPIOC
#define Front_Right_Receiver_Pin GPIO_PIN_1
#define Front_Right_Receiver_GPIO_Port GPIOC
#define Front_Left_Receiver_Pin GPIO_PIN_2
#define Front_Left_Receiver_GPIO_Port GPIOC
#define Left_Receiver_Pin GPIO_PIN_3
#define Left_Receiver_GPIO_Port GPIOC
#define Front_Right_Emitter_Pin GPIO_PIN_0
#define Front_Right_Emitter_GPIO_Port GPIOA
#define Right_Emitter_Pin GPIO_PIN_1
#define Right_Emitter_GPIO_Port GPIOA
#define Front_Left_Emitter_Pin GPIO_PIN_2
#define Front_Left_Emitter_GPIO_Port GPIOA
#define Left_Emitter_Pin GPIO_PIN_3
#define Left_Emitter_GPIO_Port GPIOA
#define LeftEncoderCh1_Pin GPIO_PIN_6
#define LeftEncoderCh1_GPIO_Port GPIOA
#define LeftEncoderCh2_Pin GPIO_PIN_7
#define LeftEncoderCh2_GPIO_Port GPIOA
#define RightEncoderCh2_Pin GPIO_PIN_6
#define RightEncoderCh2_GPIO_Port GPIOC
#define RightEncoderCh1_Pin GPIO_PIN_7
#define RightEncoderCh1_GPIO_Port GPIOC
#define L_BATT_LED_Pin GPIO_PIN_8
#define L_BATT_LED_GPIO_Port GPIOC
#define R_BATT_LED_Pin GPIO_PIN_9
#define R_BATT_LED_GPIO_Port GPIOC
#define START_BUTTON_Pin GPIO_PIN_11
#define START_BUTTON_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

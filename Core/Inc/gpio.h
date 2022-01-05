/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define S0_L HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,0)
#define S0_H HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1)

#define S1_L HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,0)
#define S1_H HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,1)

#define S2_L HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,0)
#define S2_H HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,1)

#define S3_L HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,0)
#define S3_H HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,1)

#define LED_OFF HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,0)
#define LED_ON  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,1)

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max3(a,b,c) (((a) > (b) ? (a) : (b)) > (c) ? ((a) > (b) ? (a) : (b)) : (c))
#define min3(a,b,c) (((a) < (b) ? (a) : (b)) < (c) ? ((a) < (b) ? (a) : (b)) : (c))

/* USER CODE END Private defines */

void MX_GPIO_Init(void);
void filter(int s2, int s3);
void TCS_Next(int s2, int s3);
void Sonic_Trig(uint16_t us);
void Sonic_Trig1(uint16_t us);
void rgb2hsv(uint16_t *rgb, uint16_t *hsv);
/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

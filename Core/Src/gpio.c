/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
#include "tim.h"
#include "stdio.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */
//�˲���ģʽѡ����������S2��S3�ĵ�λ��ѡ��졢�̡���������ɫ���˲���
void filter(int s2, int s3)
{
	if(s2 == 0 && s3 == 0){
			S2_L;S3_L;
		}
	if(s2 == 0 && s3 == 1){
			S2_L;S3_H;
		}
	if(s2 == 1 && s3 == 0){
			S2_H;S3_L;
		}
	if(s2 == 1 && s3 == 1){
			S2_H;S3_H;
		}
}


int flag = 0;
int count = 0;

void TCS_Next(int s2, int s3)
{
	count = 0;	//ͳ������������
	flag++;		//����źż�����־+1��������һ����ɫ������ͳ��
	filter(s2,s3); 	//ѡ����ɫ�˲���ģʽ
}
/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_RESET);
	
	/*Configure GPIO pin Output Level */	
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);	
	
	/*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

   /*Configure GPIO pins : PH4 PH5 ��ɫ������*/
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 PA6 ��ɫ������*/
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 ��ɫ������*/
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	


  /*Configure GPIO pins : PB13 PB14 PB15 ѭ��������*/ 
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	

  /*Configure GPIO pins : PC6 PC7 ѭ��������*/ 
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PH3 PH2 ������*/
	GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_3,0);
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_2,0);

}

/* USER CODE BEGIN 2 ���������봫���� */
void Sonic_Trig(uint16_t us)
{
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_3,1);
	Delay_us(us);
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_3,0);

}
void Sonic_Trig1(uint16_t us)
{
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_2,1);
	Delay_us(us);
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_2,0);
}

void rgb2hsv(uint16_t *rgb, uint16_t *hsv)
{
    float max, min, delta=0;
    float r = (rgb[0]/255);
    float g = (rgb[1]/255);
    float b = (rgb[2]/255);

    max = max3(r, g, b);
    min = min3(r, g, b);
    delta = (max - min);

    //printf("r:%f, g:%f, b:%f\n", r, g, b);

    if (delta == 0) {
        hsv[0] = 0;
    } else {
        if (r == max) {
            hsv[0] = ((g-b)/delta)*60; 
        } else if (g == max) {
            hsv[0] = 120+(((b-r)/delta)*60); 
        } else if (b == max) {
            hsv[0] = 240 + (((r-g)/delta)*60);
        }

        if (hsv[0] < 0) {
            hsv[0] += 360;
        }
    }

    if (max == 0) {
        hsv[1] = 0;
    } else {
       hsv[1] = (float)(delta/max);
    }

    hsv[2] = max;

    hsv[2] = (unsigned int)(((rgb[0]&0xff)<<16) | ((rgb[1]&0xff)<<8) | (rgb[2]&0xff));
}


/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

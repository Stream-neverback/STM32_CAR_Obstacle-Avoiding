/**
  ******************************************************************************
  * File Name          : TIM.c
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
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
#include "tim.h"

/* USER CODE BEGIN 0 */
#include "stdio.h"
#include "gpio.h"
#include "usart.h"
/* USER CODE END 0 */

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim6;

/* TIM1 init function */
void MX_TIM1_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 499;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 50000;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}
/* TIM2 init function */
void MX_TIM2_Init(void)
{
  TIM_SlaveConfigTypeDef sSlaveConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 0xffffffff;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;
  sSlaveConfig.InputTrigger = TIM_TS_TI1FP1;
  sSlaveConfig.TriggerPolarity = TIM_TRIGGERPOLARITY_RISING;
  sSlaveConfig.TriggerFilter = 0;
  if (HAL_TIM_SlaveConfigSynchro(&htim2, &sSlaveConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}
/* TIM5 init function */
void MX_TIM5_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 99;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 0xffffffff;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim5) != HAL_OK)
  {
    Error_Handler(); 
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim5, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
	if (HAL_TIM_IC_ConfigChannel(&htim5, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }


}

/* TIM6 init function */
void MX_TIM6_Init(void)
{
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 99;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 65535;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_ENABLE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}



void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(tim_baseHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspInit 0 */

  /* USER CODE END TIM1_MspInit 0 */
    /* TIM1 clock enable */
    __HAL_RCC_TIM1_CLK_ENABLE();

    /* TIM1 interrupt Init */
    HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
  /* USER CODE BEGIN TIM1_MspInit 1 */

  /* USER CODE END TIM1_MspInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspInit 0 */

  /* USER CODE END TIM2_MspInit 0 */
    /* TIM2 clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM2 GPIO Configuration
    PA0/WKUP     ------> TIM2_CH1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM2_MspInit 1 */

  /* USER CODE END TIM2_MspInit 1 */
  }
	 else if(tim_baseHandle->Instance==TIM5)
  {
  /* USER CODE BEGIN TIM5_MspInit 0 */

  /* USER CODE END TIM5_MspInit 0 */
    /* TIM5 clock enable */
    __HAL_RCC_TIM5_CLK_ENABLE();

    __HAL_RCC_GPIOH_CLK_ENABLE();
    /**TIM5 GPIO Configuration
    PA0/WKUP     ------> TIM5_CH1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM5;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
		
//		GPIO_InitStruct.Pin = GPIO_PIN_11;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//    GPIO_InitStruct.Alternate = GPIO_AF2_TIM5;
//    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* TIM5 interrupt Init */
    HAL_NVIC_SetPriority(TIM5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM5_IRQn);
  /* USER CODE BEGIN TIM5_MspInit 1 */

  /* USER CODE END TIM5_MspInit 1 */
  }
	else if(tim_baseHandle->Instance==TIM6)
  {
  /* USER CODE BEGIN TIM6_MspInit 0 */

  /* USER CODE END TIM6_MspInit 0 */
    /* TIM6 clock enable */
    __HAL_RCC_TIM6_CLK_ENABLE();

    /* TIM6 interrupt Init */
    HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
  /* USER CODE BEGIN TIM6_MspInit 1 */

  /* USER CODE END TIM6_MspInit 1 */
  }

}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspDeInit 0 */

  /* USER CODE END TIM1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM1_CLK_DISABLE();

    /* TIM1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM1_UP_TIM10_IRQn);
  /* USER CODE BEGIN TIM1_MspDeInit 1 */

  /* USER CODE END TIM1_MspDeInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspDeInit 0 */

  /* USER CODE END TIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();

    /**TIM2 GPIO Configuration
    PA0/WKUP     ------> TIM2_CH1
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0);

  /* USER CODE BEGIN TIM2_MspDeInit 1 */

  /* USER CODE END TIM2_MspDeInit 1 */
  }
	else if(tim_baseHandle->Instance==TIM5)
  {
  /* USER CODE BEGIN TIM5_MspDeInit 0 */

  /* USER CODE END TIM5_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM5_CLK_DISABLE();

    /**TIM5 GPIO Configuration
    PA0/WKUP     ------> TIM5_CH1
    PA1     ------> TIM5_CH2
    */
    HAL_GPIO_DeInit(GPIOH, GPIO_PIN_10|GPIO_PIN_11);

    /* TIM5 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM5_IRQn);
  /* USER CODE BEGIN TIM5_MspDeInit 1 */

  /* USER CODE END TIM5_MspDeInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM6)
  {
  /* USER CODE BEGIN TIM6_MspDeInit 0 */

  /* USER CODE END TIM6_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM6_CLK_DISABLE();

    /* TIM6 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM6_DAC_IRQn);
  /* USER CODE BEGIN TIM6_MspDeInit 1 */

  /* USER CODE END TIM6_MspDeInit 1 */
  }

}

/* USER CODE BEGIN 1 */
//�жϷ�����
void TIM5_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htim5);
}

void TIM6_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htim6);
}

uint8_t  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬		    				
uint32_t  TIM5CH1_CAPTURE_Date2;	//����2 ���벶��ֵTIM5��32λ
uint32_t  TIM5CH1_CAPTURE_Date1;	//����1
uint8_t  TIM5CH2_CAPTURE_STA=0;	//���벶��״̬		    				
uint32_t	TIM5CH2_CAPTURE_Date2;	//����2
uint32_t  TIM5CH2_CAPTURE_Date1;	//����1

//�����жϻص�����

extern int count;		
extern int flag;	
int cnt[3];		//����RGB����ɫ������ֵ

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM1){
		
		count = __HAL_TIM_GET_COUNTER(&htim2); //��TIM2ͳ�Ƶ�����������count
		__HAL_TIM_SET_COUNTER(&htim2,0);	//TIM2���㣬�Ա���һ�����¼���������

//		printf("Updated!\r\n");
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
		
		switch(flag){
		case 0:
//				printf("---TCS START!---\r\n");
				TCS_Next(0, 0);
				break;
		case 1:
//				printf("RED = %d\t", count); //��ӡ0.5s�ڵĺ�ɫͨ���˲���ʱ��TCS3200�����������
				cnt[0] = count; //���浽����
				TCS_Next(1, 1);	//��һ��ѡ����ɫ����ͨ���˲�����ģʽ
				break;
		case 2:
//				printf("GREEN = %d\t", count); //��ӡ0.5s�ڵ���ɫͨ���˲���ʱ��TCS3200�����������
				cnt[1] = count; //���浽����
				TCS_Next(0, 1);	//��һ��ѡ����ɫ����ͨ���˲�����ģʽ
				break;
		case 3:
//				printf("BLUE = %d\r\n", count); //��ӡ0.5s�ڵ���ɫͨ���˲���ʱ��TCS3200�����������
//				printf("---TCS END!---\r\n");
				cnt[2] = count; //���浽����
				TCS_Next(1, 0);	//���˲�����ģʽ
				break;
		default:
				count = 0;	//����������
				break;
			}
		}
	else if(htim->Instance == TIM5){
    if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
    {
      if(TIM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
      {
        if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
        {
          TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
          TIM5CH1_CAPTURE_Date2=0XFFFFFFFF;
        }else TIM5CH1_CAPTURE_STA++;
      }
    }
    if((TIM5CH2_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
    {
      if(TIM5CH2_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
      {
        if((TIM5CH2_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
        {
          TIM5CH2_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
          TIM5CH2_CAPTURE_Date2=0XFFFFFFFF;
        }else TIM5CH2_CAPTURE_STA++;
      }
    }
  }
}


uint16_t Ultrasonic_us1 = 0;
uint16_t Ultrasonic_us2 = 0;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//�����жϷ���ʱִ��
{
  if(htim->Instance == TIM5){
    if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_1) {
      if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
      {
        if(TIM5CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
        {	  			
          TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
          TIM5CH1_CAPTURE_Date2=HAL_TIM_ReadCapturedValue(&htim5,TIM_CHANNEL_1);//��ȡ��ǰ�Ĳ���ֵ.

          Ultrasonic_us1=TIM5CH1_CAPTURE_STA&0X3F;
          Ultrasonic_us1*=0XFFFFFFFF;						//���ʱ���ܺ�
          Ultrasonic_us1+=TIM5CH1_CAPTURE_Date2;		
          Ultrasonic_us1-=TIM5CH1_CAPTURE_Date1;		//�õ��ܵĸߵ�ƽʱ��
          TIM5CH1_CAPTURE_Date1=0;
          TIM5CH1_CAPTURE_STA=0;        //������һ�β���

          TIM_RESET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_1);   //һ��Ҫ�����ԭ�������ã���
          TIM_SET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//����TIM5ͨ��1�����ز���
        }else  								//��δ��ʼ,��һ�β���������
        {
          TIM5CH1_CAPTURE_STA=0;			//���
          TIM5CH1_CAPTURE_Date2=0;
          TIM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
//					__HAL_TIM_DISABLE(&htim5);
//					__HAL_TIM_SET_COUNTER(&htim5,0);
          TIM5CH1_CAPTURE_Date1=HAL_TIM_ReadCapturedValue(&htim5,TIM_CHANNEL_1);//��ȡ��ǰ�Ĳ���ֵ.
          TIM_RESET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_1);   //һ��Ҫ�����ԭ�������ã���
          TIM_SET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);//��ʱ��5ͨ��1����Ϊ�½��ز���
//					__HAL_TIM_ENABLE(&htim5);
        }	      
      }
    } 
    else if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_2) {   
      if((TIM5CH2_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
      {
        if(TIM5CH2_CAPTURE_STA&0X40)		//����һ���½��� 		
        {	  			
          TIM5CH2_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
          TIM5CH2_CAPTURE_Date2=HAL_TIM_ReadCapturedValue(&htim5,TIM_CHANNEL_2);//��ȡ��ǰ�Ĳ���ֵ.

          Ultrasonic_us2=TIM5CH2_CAPTURE_STA&0X3F;
          Ultrasonic_us2*=0XFFFFFFFF;						//���ʱ���ܺ�
          Ultrasonic_us2+=TIM5CH2_CAPTURE_Date2;		
          Ultrasonic_us2-=TIM5CH2_CAPTURE_Date1;		//�õ��ܵĸߵ�ƽʱ��
          TIM5CH2_CAPTURE_Date1=0;
          TIM5CH2_CAPTURE_STA=0;        //������һ�β���

          TIM_RESET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_2);   //һ��Ҫ�����ԭ�������ã���
          TIM_SET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_2,TIM_ICPOLARITY_RISING);//����TIM5ͨ��2�����ز���
        }else  								//��δ��ʼ,��һ�β���������
        {
          TIM5CH2_CAPTURE_STA=0;			//���
          TIM5CH2_CAPTURE_Date2=0;
          TIM5CH2_CAPTURE_STA|=0X40;		//��ǲ�����������
//					__HAL_TIM_DISABLE(&htim5);
//					__HAL_TIM_SET_COUNTER(&htim5,0);
          TIM5CH2_CAPTURE_Date1=HAL_TIM_ReadCapturedValue(&htim5,TIM_CHANNEL_2);//��ȡ��ǰ�Ĳ���ֵ.
          TIM_RESET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_2);   //һ��Ҫ�����ԭ�������ã���
          TIM_SET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_2,TIM_ICPOLARITY_FALLING);//��ʱ��5ͨ��2����Ϊ�½��ز���
//					__HAL_TIM_ENABLE(&htim5);
        }
      }        
    }
	}
//	__HAL_TIM_CLEAR_IT(&htim5, TIM_IT_CC1|TIM_IT_CC2);
}
//void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
//{
////	printf("CAPTURE Success!");	
//if(htim->Instance == TIM5){
//		//������
//		if(Capture_Flag == 1)
//		{
//			
//			__HAL_TIM_DISABLE(&htim5);        //�رն�ʱ��5
//			__HAL_TIM_SET_COUNTER(&htim5,0);
//			if(Front_flag == 1 && Right_flag == 0){
//			TIM_RESET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_1);   //һ��Ҫ�����ԭ�������ã���
//			TIM_SET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);//��ʱ��5ͨ��1����Ϊ�½��ز���
//			}
//			else if(Front_flag == 0 && Right_flag == 1){
//			TIM_RESET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_2);   //һ��Ҫ�����ԭ�������ã���
//			TIM_SET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_2,TIM_ICPOLARITY_FALLING);//��ʱ��5ͨ��1����Ϊ�½��ز���
//			}
//			__HAL_TIM_ENABLE(&htim5);//ʹ�ܶ�ʱ��5
//			Capture_Flag = 0;
//		}
//		//�½���
//		else
//		{
//			if(Front_flag == 1 && Right_flag == 0){
//			Ultrasonic_us = HAL_TIM_ReadCapturedValue(&htim5,TIM_CHANNEL_1);
//			TIM_RESET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_1);		//һ��Ҫ�����ԭ�������ã���
//			TIM_SET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//��ʱ��5ͨ��1����Ϊ�����ز���
//			}
//			
//			else if(Front_flag == 0 && Right_flag == 1){
//			Ultrasonic_us1 = HAL_TIM_ReadCapturedValue(&htim5,TIM_CHANNEL_2);
//			TIM_RESET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_2);		//һ��Ҫ�����ԭ�������ã���
//			TIM_SET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_2,TIM_ICPOLARITY_RISING);//��ʱ��5ͨ��1����Ϊ�����ز���
//			}
//			
//			Capture_Flag = 1;
//		}
//	}
//}	
////		//������
////		if(Capture_Flag == 1)
////		{
////			
////			__HAL_TIM_DISABLE(&htim5);        //�رն�ʱ��5
////			__HAL_TIM_SET_COUNTER(&htim5,0);
////			TIM_RESET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_1);   //һ��Ҫ�����ԭ�������ã���
////			TIM_SET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);//��ʱ��5ͨ��1����Ϊ�½��ز���
////			
////			__HAL_TIM_ENABLE(&htim5);//ʹ�ܶ�ʱ��5
////			Capture_Flag = 0;

////		}
////		//�½���
////		else
////		{
////			Ultrasonic_us = HAL_TIM_ReadCapturedValue(&htim5,TIM_CHANNEL_1);
////			TIM_RESET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_1);		//һ��Ҫ�����ԭ�������ã���
////			TIM_SET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//��ʱ��5ͨ��1����Ϊ�����ز���

//////			printf("Ultrasonic distance: %d cm \r\n",(int)(Ultrasonic_us * 17.0 / 1000));
////			
////			Capture_Flag = 1;
////			}
////	}
////	
////	
////		
////		//������
////		if(Capture_Flag1 == 1)
////		{
////			
////			__HAL_TIM_DISABLE(&htim5);        //�رն�ʱ��5
////			__HAL_TIM_SET_COUNTER(&htim5,0);

////			TIM_RESET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_2);   //һ��Ҫ�����ԭ�������ã���
////			TIM_SET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_2,TIM_ICPOLARITY_FALLING);//��ʱ��5ͨ��2����Ϊ�½��ز���

////			Capture_Flag1 = 0;
////		}
////		//�½���
////		else
////		{
////			Ultrasonic_us1 = HAL_TIM_ReadCapturedValue(&htim5,TIM_CHANNEL_2);
////			
////			TIM_RESET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_2);		//һ��Ҫ�����ԭ�������ã���
////			TIM_SET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_2,TIM_ICPOLARITY_RISING);//��ʱ��5ͨ��2����Ϊ�����ز���
//////			printf("Ultrasonic distance: %d cm \r\n",(int)(Ultrasonic_us * 17.0 / 1000));

////			Capture_Flag1 = 1;
////			}
//                            
////	if(htim->Instance == TIM4)
////	{
////		//������
////		if(Capture_Flag1 == 1)
////		{
////			
////			__HAL_TIM_DISABLE(&htim4);        //�رն�ʱ��5
////			__HAL_TIM_SET_COUNTER(&htim4,0);
////			TIM_RESET_CAPTUREPOLARITY(&htim4,TIM_CHANNEL_1);   //һ��Ҫ�����ԭ�������ã���
////			TIM_SET_CAPTUREPOLARITY(&htim4,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);//��ʱ��4ͨ��1����Ϊ�½��ز���
////			__HAL_TIM_ENABLE(&htim4);//ʹ�ܶ�ʱ��5
////			Capture_Flag1 = 0;
////		}
////		//�½���
////		else
////		{
////			Ultrasonic_us1 = HAL_TIM_ReadCapturedValue(&htim4,TIM_CHANNEL_1);
////			TIM_RESET_CAPTUREPOLARITY(&htim4,TIM_CHANNEL_1);		//һ��Ҫ�����ԭ�������ã���
////			TIM_SET_CAPTUREPOLARITY(&htim4,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//��ʱ��4ͨ��1����Ϊ�����ز���
//////			printf("Ultrasonic distance: %d cm \r\n",(int)(Ultrasonic_us * 17.0 / 1000));
////			
////			Capture_Flag1 = 1;
////			}
////	}

//��ʱ�����뼶��ʱ�������ʱʱ��Ϊ65535us��������������ʱʱ�䣬������쳣��
void Delay_us(uint16_t us)
{
	HAL_TIM_Base_Start(&htim6);
	__HAL_TIM_SET_COUNTER(&htim6,0);
	while(us > __HAL_TIM_GET_COUNTER(&htim6) ) {};
	HAL_TIM_Base_Stop(&htim6);
	
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

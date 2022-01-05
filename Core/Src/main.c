/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "motor.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

extern int flag;
extern int count;
extern int cnt[3];
uint16_t rgb[3];
uint16_t hsv[3];
float float_hsv[3];
float RGB_Scale[3];		//储存3个RGB比例因子
float distance_forward = 0;
float distance_right = 0;
float distance_right_initial = 10;
extern uint16_t Ultrasonic_us1;
extern uint16_t Ultrasonic_us2;
int Front_flag = 0;
int Right_flag = 0;
int KEY1; 
int KEY2;
int KEY3;
int KEY4;
int KEY5;
int turn_flag = 0; // straight is 0, turn is 1
int turn_flag1 = 0; // straight is 0, turn is 1
int turn_dir = 0; // left is even, right is odd
int turn_cnt = 0; // turn counter
float PWM = 0;
int red_count = 0;
int stop_flag = 0;
int a = 0;
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
	MX_USART1_UART_Init();
	MX_USART2_UART_Init();
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
	MX_TIM5_Init();
  MX_TIM6_Init();
//	HAL_Delay(1000);
//	CircleR();
//	HAL_Delay(1000);
//	CircleL();
	//	printf("ok");
  /* USER CODE BEGIN 2 */
	
	
	HAL_TIM_Base_Start_IT(&htim1);	//使能定时器1
	HAL_TIM_Base_Start(&htim2);	//使能定时器2
//	HAL_TIM_Base_Start_IT(&htim5);
//		printf("ok");
	HAL_TIM_IC_Start_IT(&htim5,TIM_CHANNEL_1);   //开始捕获TIM5的通道1
	HAL_TIM_IC_Start_IT(&htim5,TIM_CHANNEL_2);   //开始捕获TIM5的通道1
	__HAL_TIM_ENABLE_IT(&htim5,TIM_IT_UPDATE);   //使能更新中断

	//选择2%的输出比例因子
	S0_L;
	S1_H;
	LED_ON;		//打开四个白色LED，进行白平衡
	HAL_Delay(3000);		//延时三秒，等待识别
	//通过白平衡测试，计算得到白色物的RGB值255与0.5秒内三色光脉冲数的RGB比例因子
	for(int i=0;i<3;i++)
	{
		RGB_Scale[i] = 255.0/cnt[i];
		printf("Scaler: %5lf  \r\n", RGB_Scale[i]);
	}
	//红绿蓝三色光分别对应的0.5s内TCS3200输出脉冲数，乘以相应的比例因子就是我们所谓的RGB标准值
	//打印被测物体的RGB值
	
	for(int i=0; i<3; i++)
	{
		printf("%d \r\n", (int) (cnt[i]*RGB_Scale[i]));
	}
	printf("White Balance Done!\r\n");
	//白平衡结束
	if(Ultrasonic_us2 != 0)
		distance_right_initial = (float)(Ultrasonic_us2 * 17.0 / 1000);
	float target = distance_right_initial;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
		flag = 0;
		count = 0;
//		printf("while loop is running!\r\n");
//		HAL_Delay(600); //500
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);
	
		for(int i=0; i<3; i++)
		{
			if(i==0){
				printf("RGB = (");
			}
			if(i==2){
				printf("%d)\r\n",(int) (cnt[i]*RGB_Scale[i]));
			  rgb[i] = (int) (cnt[i]*RGB_Scale[i]);
			}
			else
				printf("%d, ", (int) (cnt[i]*RGB_Scale[i]));
			rgb[i] = (int) (cnt[i]*RGB_Scale[i]);
		}
//	rgb2hsv(rgb, hsv);
//	float_hsv[0] = (float) (hsv[0]);
//	float_hsv[1] = (float) (hsv[1]);
//	float_hsv[2] = (float) (hsv[2]);		
//	printf(	"HSV = %f, %f, %f\r\n",float_hsv[0],(float_hsv[1]),(float_hsv[2]));
  KEY1 = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13);
  KEY2 = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_6);		
  KEY3 = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14);
  KEY4 = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_7);
  KEY5 = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15);
//	printf("%d, %d, %d\r\n",KEY1, KEY3, KEY5);
	printf("%d, %d, %d, %d, %d\r\n",KEY1, KEY2, KEY3, KEY4, KEY5);
	Sonic_Trig(20);
	
//		__HAL_TIM_DISABLE(&htim5);
  Sonic_Trig1(20);

		if(Ultrasonic_us1 != 0 && Ultrasonic_us2 != 0)	
        printf("Front distance: %.*f cm\r\nRight distance: %.*f cm\r\n", 2, (float)(Ultrasonic_us1 * 17.0 / 1000), 2, (float)(Ultrasonic_us2 * 17.0 / 1000));
		distance_forward = (float)(Ultrasonic_us1 * 17.0 / 1000);
		distance_right = (float)(Ultrasonic_us2 * 17.0 / 1000);
		if(distance_right < 27.5 && turn_flag == 0 && turn_dir <= 3){
			PWM = Position_PID(distance_right,target);    
		}
        else{
			PWM = 0;
		}
      if(stop_flag == 0){  
		if(distance_forward  <= 27.4 && distance_forward  >= 7) {turn_flag = 1;}//检测到即将到达角落
        if(distance_forward  <= 24 && distance_forward  >= 7) {turn_flag1 = 1;}//检测到即将到达角落
		if(turn_flag == 1 && (turn_dir/2)%2 == 0) {
			CircleL();//原地转90度左转
//			Stop();
			turn_dir = turn_dir + 1;
			turn_cnt +=1;
			Ultrasonic_us1 = 50;
			HAL_Delay(585);
			turn_flag = 0;
            turn_flag1 = 0;
		}
		else if(turn_flag1 == 1 && turn_dir == 2) {
            HAL_Delay(200);
//			Stop();//停车
            if(turn_dir%2==0){
			CircleR1();//原地转90度右转
            }
//            else{
//			CircleR();//原地转90度右转
//            }
//			Stop();	//delay防止超声误检测
			turn_dir = turn_dir + 1;
			turn_cnt +=1;
			Ultrasonic_us1 = 50;
            Ultrasonic_us2 = 50;
			HAL_Delay(600);
		turn_flag = 0;
            turn_flag1 = 0;
		}
        else if(turn_flag1 == 1 && turn_dir == 3) {
//			Stop();//停车
//            if(turn_dir%2==1){
            HAL_Delay(200);
			CircleR();//原地转90度右转
//            }
//			Stop();	//delay防止超声误检测
			turn_dir = turn_dir + 1;
			turn_cnt +=1;
			Ultrasonic_us1 = 50;
			HAL_Delay(600);
            turn_flag = 0;
		turn_flag1 = 0;
		}
        else if(turn_flag == 0 && turn_dir == 4){
            CarGo();
            HAL_Delay(450);
        }
		else{
			CarGo_PID(PWM);//直线前进
			HAL_Delay(450);
		}
		if(cnt[0]*RGB_Scale[0] > cnt[1]*RGB_Scale[1] && turn_cnt >= 4){
			red_count = red_count+1;
			if (red_count >= 4){
                HAL_Delay(50);
				Stop();
				stop_flag = 1;
			}
		}
        
//		if(turn_cnt == 4){
//		    if(1){
//		        Stop();//拐弯4次检测到恰当颜色后停车
//		    }
//		    else{
//                CarGo();//未检测到目标颜色继续前进
//		    }

//		}
		
    /* USER CODE BEGIN 3 */
  }
			else if(stop_flag == 1){
			Stop();
				a = 1;
			}
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "pidctl.h"
#include "arm_math.h"
#include "bsp_can.h"
#include "CALCULATE.h"
#include "logic.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern motor_measure_t *motor_data_can2[8];
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/**
  ******************************************************************************
  * @attention
  *
  *	�ϵ�ǰע��������ID������logic.h�У�
  *
  *	2006������Ϊ4
  *	3508������Ϊ3
  *
  ******************************************************************************
  */
/*------------------------------------------------------------------------------
	current_state
	��צ��ǰ״̬��S_0, S_1, S_2, S_3��
	����Ϊ�ı��צλ��
	S_0 (3508:0mm    2006:10��            )
	S_1 (3508:100mm  2006:65��/115��/165��)
	S_2 (3508:90mm   2006:65��/115��/165��)
	S_3 (3508:50mm   2006:65��/115��/165��)
------------------------------------------------------------------------------*/
enum State current_state = S_0;

/*------------------------------------------------------------------------------
	Logic_FLAG
	��ǰ����߼���־��FREE, PINCH, PLACE��
	����Ϊ�жϵ�ǰ���мв������ǷŲ���
------------------------------------------------------------------------------*/
enum FLAG Logic_FLAG=FREE;

/*------------------------------------------------------------------------------
	move_FLAG
	����ƶ�״̬��־��FREE, MOVE, FINISH��
	����Ϊ������Ƿ񵽴�Ŀ��
------------------------------------------------------------------------------*/
enum FLAG move_FLAG[8]={FREE,FREE};

/*------------------------------------------------------------------------------
	servo_FLAG
	���״̬��־��FREE, FINISH��
	����Ϊ�ж϶�������Ƿ����
------------------------------------------------------------------------------*/
enum FLAG servo_FLAG=FREE;

/*------------------------------------------------------------------------------
	num_state
	���������0, 1, 2, 3 ��
	����Ϊ��¼��ǰ�洢��������������һ�������߼����иı�
------------------------------------------------------------------------------*/
uint8_t num_state=0;

/*------------------------------------------------------------------------------
	TEMP_YAW_TGT_2006
	��switch�иı�2006�Ƕ�
------------------------------------------------------------------------------*/
float TEMP_YAW_TGT_2006=0;

/*------------------------------------------------------------------------------
	motor_state
	���״̬��1, 2��
	�ı���������SPD/ANG
	�������ϵ���㣬���Ѳ��ã�
------------------------------------------------------------------------------*/
//uint8_t motor_state[8]={0};

/*------------------------------------------------------------------------------
	logic_change
	�߼��ı䣨PINCH, PLACE��
	ң��������
------------------------------------------------------------------------------*/
enum FLAG logic_change = FREE;


/*------------------------------------------------------------------------------
	PID
	PID����
------------------------------------------------------------------------------*/

//Ŀ��Ƕ�
float YAW_TGT[8] = {0};
//Ŀ���ٶ�
//int SPD_TGT[8] = {0};//{-500,500}
//�����ĽǶ�
float ANG_TGT[8] = {0};
//��ǰ�Ƕ�
float current_ang=0;
//can�����ֵ
int can_output[8] = {0};
//��־λ
uint8_t FLAG=0;

/*------------------------------------------------------------------------------
	�����
	�����ϵ�����ʼ��
	�������ԣ����Ѳ��ã�
------------------------------------------------------------------------------*/
////RESET���
//float ZERO_POINT[8] ={0};
////��ת��ʼ�ͽ����ķ��ؽǶ���Ȧ�������ʱ��1s��
//float STL_BGN_ANG[8]={0,0},STL_END_ANG[8]={0,0};
////��ת���
//int stl_error[8]={0};
////��תʱ�������
//int stl_counter[8]={0};
//uint8_t init_FLAG[8]={0};

/*------------------------------------------------------------------------------
	ң��������
	���ڼ��ң������������
------------------------------------------------------------------------------*/
//���սṹ��
DataPacket DataRe;
//ҡ�˱���
int16_t lx ,ly,rx,ry,lp,rp;
//��������
uint8_t B1,B2;
//У��λ
uint8_t Cal_Parity;
//FALG
uint8_t USART_FLAG=0;

	
/*------------------------------------------------------------------------------
	target_monitor����
	�����жϵ���Ƿ񵽴�Ŀ��Ƕ�
------------------------------------------------------------------------------*/
//��ǰ�Ƕ�
float current_target[8]={0};
//�Ƕ����
float target_error[8]={0};
//���Ա��������ڿ�ͼ��΢��PID
float test_target=0;


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
  MX_DMA_Init();
  MX_TIM10_Init();
  MX_USART3_UART_Init();
  MX_TIM3_Init();
  MX_CAN1_Init();
  MX_CAN2_Init();
  /* USER CODE BEGIN 2 */
	pidctl_initialize(); 
	
	HAL_TIM_Base_Start_IT(&htim10); 
	
	//PWM��ʼ
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
	//CAN��ʼ��
	can_filter_init();
	HAL_CAN_Start(&hcan2); 
	HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
	//DMA��ʼ
	HAL_UART_Receive_DMA(&huart3, (uint8_t*)&DataRe,1);
	
	/*PID*/
	
	/*2006*/
	//SPD 
	rtP.ANG_S_P_CH2_4 = 0.6901*0.7 ;
	rtP.ANG_S_I_CH2_4 = 2.3727*0.11;
	rtP.ANG_S_D_CH2_4 = 0.0126;
	//ANG
	rtP.ANG_A_P_CH2_4 = 0.83005*0.6 ;
	rtP.ANG_A_I_CH2_4 = 0.38548*0.02 ;
	rtP.ANG_A_D_CH2_4 = 0.051858 ;
	
	/*3508*/
	//SPD 
	rtP.ANG_S_P_CH2_3 = 0.6901*0.75 ;
	rtP.ANG_S_I_CH2_3 = 2.3727*0.17;
	rtP.ANG_S_D_CH2_3 = 0.01;
	//ANG
	rtP.ANG_A_P_CH2_3 = 0.83005*0.85 ;
	rtP.ANG_A_I_CH2_3 = 0.38548*0.02 ;
	rtP.ANG_A_D_CH2_3 = 0.04 ;

	//����
	rtP.DEADBAND_CH2_3 = 800;
	rtP.DEADBAND_CH2_4 = 800;
	rtP.TRANS_CH2_3  = 0.4;
	rtP.TRANS_CH2_4  = 0.4;
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, servo_LO);  // ����ɿ�
	HAL_Delay(500);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  //ִ���߼��ı�
	  LOGIC();
	  HAL_Delay(100);

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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim10)
	{
		target_monitor();
		/* 3508 */
		ANG_TGT[M_3508]  = YAW_TGT[M_3508] * 3591 * 8191/(187 * 360) ;
		rtU.yaw_status11    = 2 ;// ANG
		rtU.yaw_target11    = ANG_TGT[M_3508];
		rtU.yaw_circle11    = motor_data_can2[M_3508]->circle;
		can_output[M_3508] = rtY.yaw_ANG_OUT11 ;
		rtU.yaw_speed_rpm11 = motor_data_can2[M_3508]->speed_rpm;
		rtU.yaw_ecd11       = motor_data_can2[M_3508]->ecd;
		rtU.yaw_last_ecd11  = motor_data_can2[M_3508]->last_ecd;
		/* OUT PUT */	
		motor_data_can2[M_3508]->circle = rtU.yaw_circle11;
		
		
		/* 2006 */
		ANG_TGT[M_2006]  = YAW_TGT[M_2006] * 36 * 8191 * 2 /( 1 * 360) ;
		rtU.yaw_status12    = 2 ;// ANG
		rtU.yaw_target12    = ANG_TGT[M_2006];
		rtU.yaw_circle12    = motor_data_can2[M_2006]->circle;
		can_output[M_2006] = rtY.yaw_ANG_OUT12 ;
		rtU.yaw_speed_rpm12 = motor_data_can2[M_2006]->speed_rpm;
		rtU.yaw_ecd12       = motor_data_can2[M_2006]->ecd;
		rtU.yaw_last_ecd12  = motor_data_can2[M_2006]->last_ecd;
		/* OUT PUT */	
		motor_data_can2[M_2006]->circle = rtU.yaw_circle12;
		
//		test_target=motor_data_can2[M_2006]->speed_rpm;
//		test_target=((motor_data_can2[M_2006]->ecd)+(motor_data_can2[M_2006]->circle)*8191)*( 1 * 360)/(2 * 8191 * 36);
//		if (test_target<0)
//		{
//			test_target=0;
//		}
		
		pidctl_step();
		
		CAN2_cmd_chassis(0,0,can_output[M_3508],can_output[M_2006],0,0,0,0);

		motor_state_update_can2();

	}
	
}

//ң��������
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
		if (huart->Instance == USART3)
    {
		if(DataRe.header==0xAA && USART_FLAG==0)
		{
			CAL_MESSAGE();
			HAL_UART_Receive_DMA(&huart3, (uint8_t*)&DataRe+1, sizeof(DataPacket)-1);
			USART_FLAG=1;
		}
		if(DataRe.header==0xAA && USART_FLAG==1)
		{
			CAL_MESSAGE();
			HAL_UART_Receive_DMA(&huart3, (uint8_t*)&DataRe, sizeof(DataPacket));
		}
		else
		{
			HAL_UART_Receive_DMA(&huart3, (uint8_t*)&DataRe, 1);
			USART_FLAG=0;
		}				
	}
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART3)
    {
		HAL_UART_Receive_DMA(&huart3, (uint8_t*)&DataRe, 1);
		USART_FLAG=0;
    }
}

/* USER CODE END 4 */

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

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
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "PID_MODEL.h"
#include "arm_math.h"
#include "bsp_can.h"
#include "CALCULATE.h"
#include "new_logic.h"
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
  *	check moto id before use the project
  *
  *	2006 ID 1
  *	3508 ID 0
  *
  ******************************************************************************
  */

/*------------------------------------------------------------------------------
	PID
	PID value
------------------------------------------------------------------------------*/
//angle target(uncalculated)
float YAW_TGT[8] = {0};
float M_3508_YAW_TGT=0;
float SPD_TGT[8] = {0};//{-500,500}
//angle target(calculated)
float ANG_TGT[8] = {0};
float current_ang=0;
int can_output[8] = {0};

uint8_t FLAG=0;

/*------------------------------------------------------------------------------
	controller value
------------------------------------------------------------------------------*/
//struct
DataPacket DataRe_ESP;
DataPacket DataRe_LORA;
//rocker value
int16_t lx_ESP ,ly_ESP,rx_ESP,ry_ESP,lp_ESP,rp_ESP;
int16_t lx_LORA ,ly_LORA,rx_LORA,ry_LORA,lp_LORA,rp_LORA;
//bottom value
uint8_t B1_ESP,B2_ESP;
uint8_t B1_LORA,B2_LORA;

uint8_t Cal_Parity_ESP;
uint8_t Cal_Parity_LORA;
//FALG
uint8_t USART_FLAG_ESP=0;
uint8_t USART_FLAG_LORA=0;
	
/*------------------------------------------------------------------------------
	target_monitor
------------------------------------------------------------------------------*/
float current_target[8]={0};
float target_error[8]={0};
float test_target=0;

uint16_t HT_moto_yaw=0;

uint8_t LOGIC_FLAG=0;
uint8_t next_state=0;
uint8_t I2C_TRANS_FLAG=0;
uint8_t M_3508_TRANS_FLAG=0;
uint8_t HIGH_TROQUE_TRANS_FLAG=0;
uint8_t current_state=0;
uint8_t GPIO_CHANGE_STATE_1;
uint8_t GPIO_CHANGE_STATE_2;
uint8_t GPIO_CHANGE_FLAG=0;
MotorExtentTypeDef motorExtent = {
  .state = 0xab,
};
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
  MX_I2C1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	PID_MODEL_initialize(); 
	
	HAL_TIM_Base_Start_IT(&htim10); 
	
	//PWM start
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
	//CAN init
	can_filter_init();
	HAL_CAN_Start(&hcan2); 
	HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
	//DMA start
	HAL_UART_Receive_DMA(&huart3, (uint8_t*)&DataRe_ESP,1);
	HAL_UART_Receive_DMA(&huart2, (uint8_t*)&DataRe_LORA,1);
	/*PID*/
	
	/*2006*/
	//SPD 
  rtP.SPD_P_CH2_4 = 0.6901*3 ;
  rtP.SPD_I_CH2_4 = 2.3727*0.8;
  rtP.SPD_D_CH2_4 = 0.0126;
	// rtP.ANG_S_P_CH2_4 = 0.6901*0.7 ;
	// rtP.ANG_S_I_CH2_4 = 2.3727*0.11;
	// rtP.ANG_S_D_CH2_4 = 0.0126;
	// //ANG
	// rtP.ANG_A_P_CH2_4 = 0.83005*0.6 ;
	// rtP.ANG_A_I_CH2_4 = 0.38548*0.02 ;
	// rtP.ANG_A_D_CH2_4 = 0.051858 ;
	
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
	rtP.TRANS_CH2_3  = 0.1;
	rtP.TRANS_CH2_4  = 0.1;
	//__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 17000);  // ����ɿ�???
	
	HAL_Delay(500);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    
    task_yaw_catch();

    // if(M_3508_TRANS_FLAG==1){
    //   YAW_TGT[M_3508] = M_3508_YAW_TGT;
    //   M_3508_TRANS_FLAG=0;
    // }

    // switch(GPIO_CHANGE_FLAG){
    //   case 1:
    //     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
    //     break;
    //   case 2:
    //     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
    //     break;
    //   case 3:
    //     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
    //     break;
    //   case 4:
    //     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
    //     break;
    //   default:
    //     break;
    // }


	//   LOGIC();

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
    if(HIGH_TROQUE_TRANS_FLAG){
      if(HAL_I2C_Master_Transmit_DMA(&hi2c1, (uint16_t)I2C_SLAVE_ADDRESS, (uint8_t *)&motorExtent, sizeof(motorExtent))!= HAL_OK)
      {
        /* Error_Handler() function is called when Timeout error occurs.
          When Acknowledge failure occurs (Slave don't acknowledge it's address)
          Master restarts communication */
        if (HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF)
        {
          Error_Handler();
        }
      }else{
        HIGH_TROQUE_TRANS_FLAG=0;
      }
      
    }
//		target_monitor(); 
		/* 3508 */
		ANG_TGT[M_3508]  = YAW_TGT[M_3508] * 3591 * 8191/(187 * 360) ;
		rtU.yaw_status_CH2_3    = 2 ;// ANG
		rtU.yaw_target_CH2_3    = ANG_TGT[M_3508];
		rtU.yaw_circle_CH2_3    = motor_data_can2[M_3508]->circle;
		can_output[M_3508] = rtY.yaw_ANG_OUT_CH2_3 ;
		rtU.yaw_speed_rpm_CH2_3 = motor_data_can2[M_3508]->speed_rpm;
		rtU.yaw_ecd_CH2_3       = motor_data_can2[M_3508]->ecd;
		rtU.yaw_last_ecd_CH2_3  = motor_data_can2[M_3508]->last_ecd;
		/* OUT PUT */	
		motor_data_can2[M_3508]->circle = rtU.yaw_circle_CH2_3;
		
		
		/* 2006 */
		ANG_TGT[M_2006]  = YAW_TGT[M_2006] * 36 * 8191 * 2 /( 1 * 360) ;
		rtU.yaw_status_CH2_4    = 1 ;// ANG
		rtU.yaw_target_CH2_4    = SPD_TGT[M_2006];
		rtU.yaw_circle_CH2_4    = motor_data_can2[M_2006]->circle;
		can_output[M_2006] = rtY.yaw_SPD_OUT_CH2_4 ;
		rtU.yaw_speed_rpm_CH2_4 = motor_data_can2[M_2006]->speed_rpm;
		rtU.yaw_ecd_CH2_4       = motor_data_can2[M_2006]->ecd;
		rtU.yaw_last_ecd_CH2_4  = motor_data_can2[M_2006]->last_ecd;
		/* OUT PUT */	
		motor_data_can2[M_2006]->circle = rtU.yaw_circle_CH2_4;
		
//		test_target=motor_data_can2[M_2006]->speed_rpm;
//		test_target=((motor_data_can2[M_2006]->ecd)+(motor_data_can2[M_2006]->circle)*8191)*( 1 * 360)/(2 * 8191 * 36);
//		if (test_target<0)
//		{
//			test_target=0;
//		}
		
		PID_MODEL_step();
		
		CAN2_cmd_chassis(can_output[M_3508],can_output[M_2006],0,0,0,0,0,0);
		
		motor_state_update_can2();

	}
	
}

//ң��������
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
		if (huart->Instance == USART3)
    {
		  if(DataRe_ESP.header==0xAA && USART_FLAG_ESP==0)
		  {
		  	CAL_MESSAGE_ESP();
		  	HAL_UART_Receive_DMA(&huart3, (uint8_t*)&DataRe_ESP+1, sizeof(DataPacket)-1);
		  	USART_FLAG_ESP=1;
		  }
		  else if(DataRe_ESP.header==0xAA && USART_FLAG_ESP==1)
		  {
		  	CAL_MESSAGE_ESP();
		  	HAL_UART_Receive_DMA(&huart3, (uint8_t*)&DataRe_ESP, sizeof(DataPacket));
		  }
      else
      {
        HAL_UART_Receive_DMA(&huart3, (uint8_t*)&DataRe_ESP, 1);
        USART_FLAG_ESP=0;
      }			
    }
    //   //LORA
    // if (huart->Instance == USART2)
    // {
		//   if(DataRe_LORA.header==0xAA && USART_FLAG_LORA==0)
		//   {
		//   	CAL_MESSAGE_LORA();
		//   	HAL_UART_Receive_DMA(&huart2, (uint8_t*)&DataRe_LORA+1, sizeof(DataPacket)-1);
		//   	USART_FLAG_LORA=1;
		//   }
		//   if(DataRe_LORA.header==0xAA && USART_FLAG_LORA==1)
		//   {
		//   	CAL_MESSAGE_LORA();
		//   	HAL_UART_Receive_DMA(&huart2, (uint8_t*)&DataRe_LORA, sizeof(DataPacket));
		//   }
		//   else
		//   {
		//   	HAL_UART_Receive_DMA(&huart2, (uint8_t*)&DataRe_LORA, 1);
		//   	USART_FLAG_LORA=0;
		//   }		
	  // }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART3)
    {
		  HAL_UART_Receive_DMA(&huart3, (uint8_t*)&DataRe_ESP, 1);
		  USART_FLAG_ESP=0;
    }

    // if (huart->Instance == USART2)
    // {
		//   HAL_UART_Receive_DMA(&huart2, (uint8_t*)&DataRe_LORA, 1);
		//   USART_FLAG_LORA=0;
    // }
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

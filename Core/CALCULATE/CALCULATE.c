/****
	*   @brief 本代码是遥控器接收端的解析代码
	*   @brief 使用方法：
	*   @brief 一、将下列代码复制到main函数的全局变量声明中，然后就可以在main函数中使用这些数据

	//接收结构体
	DataPacket DataRe_ESP;
	DataPacket DataRe_LORA;
	//摇杆变量
	int16_t lx_ESP ,ly_ESP,rx_ESP,ry_ESP,lp_ESP,rp_ESP;
	int16_t lx_LORA ,ly_LORA,rx_LORA,ry_LORA,lp_LORA,rp_LORA;
	//按键变量
	uint8_t B1_ESP,B2_ESP;
	uint8_t B1_LORA,B2_LORA;
	//校验位
	uint8_t Cal_Parity_ESP;
	uint8_t Cal_Parity_LORA;
	//FALG
	uint8_t USART_FLAG_ESP=0;
	uint8_t USART_FLAG_LORA=0;

	*   @brief 二、在初始化部分启动一次DMA接收

	HAL_UART_Receive_DMA(&huart3, (uint8_t*)&DataRe_ESP,1);
	HAL_UART_Receive_DMA(&huart2, (uint8_t*)&DataRe_LORA,1);

	*   @brief 三、将接收代码复制到main函数的用户代码部分

	
	void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
		//ESP
		if (huart->Instance == USART3)
		{
			if(DataRe_ESP.header==0xAA && USART_FLAG_ESP==0)
			{
				CAL_MESSAGE_ESP();
				HAL_UART_Receive_DMA(&huart3, (uint8_t*)&DataRe_ESP+1, sizeof(DataPacket)-1);
				USART_FLAG_ESP=1;
			}
			if(DataRe_ESP.header==0xAA && USART_FLAG_ESP==1)
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
		//LORA
		if (huart->Instance == USART2)
		{
			if(DataRe_LORA.header==0xAA && USART_FLAG_LORA==0)
			{
				CAL_MESSAGE_LORA();
				HAL_UART_Receive_DMA(&huart2, (uint8_t*)&DataRe_LORA+1, sizeof(DataPacket)-1);
				USART_FLAG_LORA=1;
			}
			if(DataRe_LORA.header==0xAA && USART_FLAG_LORA==1)
			{
				CAL_MESSAGE_LORA();
				HAL_UART_Receive_DMA(&huart2, (uint8_t*)&DataRe_LORA, sizeof(DataPacket));
			}
			else
			{
				HAL_UART_Receive_DMA(&huart2, (uint8_t*)&DataRe_LORA, 1);
				USART_FLAG_LORA=0;
			}		
		}
	}

	void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
	{
		//ESP
		if (huart->Instance == USART3)
		{
			HAL_UART_Receive_DMA(&huart3, (uint8_t*)&DataRe_ESP, 1);
			USART_FLAG_ESP=0;
		}
		//LORA
		if (huart->Instance == USART2)
		{
			HAL_UART_Receive_DMA(&huart2, (uint8_t*)&DataRe_LORA, 1);
			USART_FLAG_LORA=0;
		}
	}

  *
  ****/
#include "CALCULATE.h"
#include "main.h"
#include "tim.h"

//计算校验位
uint8_t CalculateParity(const uint8_t* data, int dataSize) {
	//奇校验
  uint8_t parity = 1;
  for (int i = 0; i < dataSize; i++) {
    parity ^= data[i];  
  }
  return parity;
}

void CAL_MESSAGE_ESP(void)
{
	// 检测帧头帧尾是否正确
  if (DataRe_ESP.header == 0xAA&& DataRe_ESP.footer == 0xDD) {  
    Cal_Parity_ESP = CalculateParity(DataRe_ESP.data, sizeof(DataRe_ESP.data));
    // 判断奇偶校验是否合规
    if (Cal_Parity_ESP == DataRe_ESP.parity) {
			// 解算摇杆与电位器数据
			lx_ESP = (DataRe_ESP.data[LX_MSB] << 8) | DataRe_ESP.data[LX_LSB];
			ly_ESP = (DataRe_ESP.data[LY_MSB] << 8) | DataRe_ESP.data[LY_LSB];
			rx_ESP = (DataRe_ESP.data[RX_MSB] << 8) | DataRe_ESP.data[RX_LSB];
			ry_ESP = (DataRe_ESP.data[RY_MSB] << 8) | DataRe_ESP.data[RY_LSB];
			lp_ESP = (DataRe_ESP.data[LP_MSB] << 8) | DataRe_ESP.data[LP_LSB];
			rp_ESP = (DataRe_ESP.data[RP_MSB] << 8) | DataRe_ESP.data[RP_LSB];
			// 符号扩展
			lx_ESP = (lx_ESP & 0x8000) ? (lx_ESP | 0xFFFF0000) : lx_ESP;
			ly_ESP = (ly_ESP & 0x8000) ? (ly_ESP | 0xFFFF0000) : ly_ESP;
			rx_ESP = (rx_ESP & 0x8000) ? (rx_ESP | 0xFFFF0000) : rx_ESP;
			ry_ESP = (ry_ESP & 0x8000) ? (ry_ESP | 0xFFFF0000) : ry_ESP;
			lp_ESP = (lp_ESP & 0x8000) ? (lp_ESP | 0xFFFF0000) : lp_ESP;
			rp_ESP = (rp_ESP & 0x8000) ? (rp_ESP | 0xFFFF0000) : rp_ESP;
			
			//按键更新
			if((B1_ESP&0x01)==0&&(DataRe_ESP.data[BOT1]&0x01)==0x01)
			{
				//按下按键1
				LOGIC_FLAG=1;
				next_state=1;

			}
			else if((B1_ESP&0x01)==0x01&&(DataRe_ESP.data[BOT1]&0x01)==0)
			{
				//松开按键1
				
			}
			
			if((B1_ESP&0x02)==0&&(DataRe_ESP.data[BOT1]&0x02)==0x02)
			{
				LOGIC_FLAG=1;
				next_state=2;
				//按下按键2
			}
			else if((B1_ESP&0x02)==0x02&&(DataRe_ESP.data[BOT1]&0x02)==0)
			{
				//松开按键2
			}
			
			if((B1_ESP&0x04)==0&&(DataRe_ESP.data[BOT1]&0x04)==0x04)
			{
				//按下按键3
			}
			else if((B1_ESP&0x04)==0x04&&(DataRe_ESP.data[BOT1]&0x04)==0)
			{
				//松开按键3
			}
			
			if((B1_ESP&0x08)==0&&(DataRe_ESP.data[BOT1]&0x08)==0x08)
			{
				//按下按键4
			}
			else if((B1_ESP&0x08)==0x08&&(DataRe_ESP.data[BOT1]&0x08)==0)
			{
				//松开按键4
			}
			
			if((B1_ESP&0x10)==0&&(DataRe_ESP.data[BOT1]&0x10)==0x10)
			{
				//按下按键5
			}
			else if((B1_ESP&0x10)==0x10&&(DataRe_ESP.data[BOT1]&0x10)==0)
			{
				//松开按键5
			}
			
			if((B1_ESP&0x20)==0&&(DataRe_ESP.data[BOT1]&0x20)==0x20)
			{
				//按下按键6
			}
			else if((B1_ESP&0x20)==0x20&&(DataRe_ESP.data[BOT1]&0x20)==0)
			{
				//松开按键6
			}
			
			if((B1_ESP&0x40)==0&&(DataRe_ESP.data[BOT1]&0x40)==0x40)
			{
				//按下按键7
			}
			else if((B1_ESP&0x40)==0x40&&(DataRe_ESP.data[BOT1]&0x40)==0)
			{
				//松开按键7
			}
			
			if((B1_ESP&0x80)==0&&(DataRe_ESP.data[BOT1]&0x80)==0x80)
			{
				//按下按键8
			}
			else if((B1_ESP&0x80)==0x80&&(DataRe_ESP.data[BOT1]&0x80)==0)
			{
				//松开按键8
			}
			
			
			
			//开关更新
			if((B2_ESP&0x01)==0&&(DataRe_ESP.data[BOT2]&0x01)==0x01)
			{
				//开关A1
			}
			if(((B2_ESP&0x01)==0x01&&(DataRe_ESP.data[BOT2]&0x01)==0)||((B2_ESP&0x02)==0x02&&(DataRe_ESP.data[BOT2]&0x02)==0))
			{
				//开关A关
			}
			if((B2_ESP&0x02)==0&&(DataRe_ESP.data[BOT2]&0x02)==0x02)
			{
				//开关A2
			}
			
			if((B2_ESP&0x04)==0&&(DataRe_ESP.data[BOT2]&0x04)==0x04)
			{
				//开关B1
			}
			if(((B2_ESP&0x04)==0x04&&(DataRe_ESP.data[BOT2]&0x04)==0)||((B2_ESP&0x08)==0x08&&(DataRe_ESP.data[BOT2]&0x08)==0))
			{
				//开关B关
			}
			if((B2_ESP&0x08)==0&&(DataRe_ESP.data[BOT2]&0x08)==0x08)
			{
				//开关B2
			}

			
			if((B2_ESP&0x10)==0&&(DataRe_ESP.data[BOT2]&0x10)==0x10)
			{
				
				//开关C1
			}
			if(((B2_ESP&0x10)==0x10&&(DataRe_ESP.data[BOT2]&0x10)==0)||((B2_ESP&0x20)==0x20&&(DataRe_ESP.data[BOT2]&0x20)==0))
			{
				//开关C关
			}
			if((B2_ESP&0x20)==0&&(DataRe_ESP.data[BOT2]&0x20)==0x20)
			{
				//开关C2
			}

			
			if((B2_ESP&0x40)==0&&(DataRe_ESP.data[BOT2]&0x40)==0x40)
			{
				//开关D1
			}
			if(((B2_ESP&0x40)==0x40&&(DataRe_ESP.data[BOT2]&0x40)==0)||((B2_ESP&0x80)==0x80&&(DataRe_ESP.data[BOT2]&0x80)==0))
			{
				//开关D关
			}
			if((B2_ESP&0x80)==0&&(DataRe_ESP.data[BOT2]&0x80)==0x80)
			{
				//开关D2
			}

			//更新标志位
			B1_ESP=DataRe_ESP.data[BOT1];
			B2_ESP=DataRe_ESP.data[BOT2];
			
    } 
  }
}

// void CAL_MESSAGE_LORA(void)
// {
// 	// 检测帧头帧尾是否正确
//   if (DataRe_LORA.header == 0xAA&& DataRe_LORA.footer == 0xDD) {  
//     Cal_Parity_LORA = CalculateParity(DataRe_LORA.data, sizeof(DataRe_LORA.data));
//     // 判断奇偶校验是否合规
//     if (Cal_Parity_LORA == DataRe_LORA.parity) {
// 			// 解算摇杆与电位器数据
// 			lx_LORA = (DataRe_LORA.data[LX_MSB] << 8) | DataRe_LORA.data[LX_LSB];
// 			ly_LORA = (DataRe_LORA.data[LY_MSB] << 8) | DataRe_LORA.data[LY_LSB];
// 			rx_LORA = (DataRe_LORA.data[RX_MSB] << 8) | DataRe_LORA.data[RX_LSB];
// 			ry_LORA = (DataRe_LORA.data[RY_MSB] << 8) | DataRe_LORA.data[RY_LSB];
// 			lp_LORA = (DataRe_LORA.data[LP_MSB] << 8) | DataRe_LORA.data[LP_LSB];
// 			rp_LORA = (DataRe_LORA.data[RP_MSB] << 8) | DataRe_LORA.data[RP_LSB];
// 			// 符号扩展
// 			lx_LORA = (lx_LORA & 0x8000) ? (lx_LORA | 0xFFFF0000) : lx_LORA;
// 			ly_LORA = (ly_LORA & 0x8000) ? (ly_LORA | 0xFFFF0000) : ly_LORA;
// 			rx_LORA = (rx_LORA & 0x8000) ? (rx_LORA | 0xFFFF0000) : rx_LORA;
// 			ry_LORA = (ry_LORA & 0x8000) ? (ry_LORA | 0xFFFF0000) : ry_LORA;
// 			lp_LORA = (lp_LORA & 0x8000) ? (lp_LORA | 0xFFFF0000) : lp_LORA;
// 			rp_LORA = (rp_LORA & 0x8000) ? (rp_LORA | 0xFFFF0000) : rp_LORA;
			
// 			//按键更新
// 			if((B1_LORA&0x01)==0&&(DataRe_LORA.data[BOT1]&0x01)==0x01)
// 			{
// 				//按下按键1
// 				I2C_TRANS_FLAG=1;
// 				motorExtent.state = 0xab;

// 			}
// 			else if((B1_LORA&0x01)==0x01&&(DataRe_LORA.data[BOT1]&0x01)==0)
// 			{
// 				//松开按键1
				
// 			}
			
// 			if((B1_LORA&0x02)==0&&(DataRe_LORA.data[BOT1]&0x02)==0x02)
// 			{
// 				I2C_TRANS_FLAG=1;
// 				motorExtent.state = 0xcd;
// 				//按下按键2
// 			}
// 			else if((B1_LORA&0x02)==0x02&&(DataRe_LORA.data[BOT1]&0x02)==0)
// 			{
// 				//松开按键2
// 			}
			
// 			if((B1_LORA&0x04)==0&&(DataRe_LORA.data[BOT1]&0x04)==0x04)
// 			{

// 				//按下按键3
// 			}
// 			else if((B1_LORA&0x04)==0x04&&(DataRe_LORA.data[BOT1]&0x04)==0)
// 			{
// 				//松开按键3
// 			}
			
// 			if((B1_LORA&0x08)==0&&(DataRe_LORA.data[BOT1]&0x08)==0x08)
// 			{

// 				//按下按键4
// 			}
// 			else if((B1_LORA&0x08)==0x08&&(DataRe_LORA.data[BOT1]&0x08)==0)
// 			{
// 				//松开按键4
// 			}
			
// 			if((B1_LORA&0x10)==0&&(DataRe_LORA.data[BOT1]&0x10)==0x10)
// 			{
// 				//下
			
// 				//按下按键5
// 			}
// 			else if((B1_LORA&0x10)==0x10&&(DataRe_LORA.data[BOT1]&0x10)==0)
// 			{
// 				//松开按键5
// 			}
			
// 			if((B1_LORA&0x20)==0&&(DataRe_LORA.data[BOT1]&0x20)==0x20)
// 			{
// 				//上
		
// 				//按下按键6
// 			}
// 			else if((B1_LORA&0x20)==0x20&&(DataRe_LORA.data[BOT1]&0x20)==0)
// 			{
// 				//松开按键6
// 			}
			
// 			if((B1_LORA&0x40)==0&&(DataRe_LORA.data[BOT1]&0x40)==0x40)
// 			{
			
// 				//按下按键7
// 			}
// 			else if((B1_LORA&0x40)==0x40&&(DataRe_LORA.data[BOT1]&0x40)==0)
// 			{
// 				//松开按键7
// 			}
			
// 			if((B1_LORA&0x80)==0&&(DataRe_LORA.data[BOT1]&0x80)==0x80)
// 			{
			
// 				//按下按键8
// 			}
// 			else if((B1_LORA&0x80)==0x80&&(DataRe_LORA.data[BOT1]&0x80)==0)
// 			{
// 				//松开按键8
// 			}
			
			
			
// 			//开关更新
// 			if((B2_LORA&0x01)==0&&(DataRe_LORA.data[BOT2]&0x01)==0x01)
// 			{
// 				//开关A1开
// 			}
// 			else if((B2_LORA&0x01)==0x01&&(DataRe_LORA.data[BOT2]&0x01)==0)
// 			{
// 				//开关A1关
// 			}
			
// 			if((B2_LORA&0x02)==0&&(DataRe_LORA.data[BOT2]&0x02)==0x02)
// 			{
// 				//开关A2开
// 			}
// 			else if((B2_LORA&0x02)==0x02&&(DataRe_LORA.data[BOT2]&0x02)==0)
// 			{
// 				//开关A2关
// 			}
			
// 			if((B2_LORA&0x04)==0&&(DataRe_LORA.data[BOT2]&0x04)==0x04)
// 			{
// 				//开关B1开
// 			}
// 			else if((B2_LORA&0x04)==0x04&&(DataRe_LORA.data[BOT2]&0x04)==0)
// 			{
// 				//开关B1关
// 			}
			
// 			if((B2_LORA&0x08)==0&&(DataRe_LORA.data[BOT2]&0x08)==0x08)
// 			{
// 				//开关B2开
// 			}
// 			else if((B2_LORA&0x08)==0x08&&(DataRe_LORA.data[BOT2]&0x08)==0)
// 			{
// 				//开关B2关
// 			}
			
// 			if((B2_LORA&0x10)==0&&(DataRe_LORA.data[BOT2]&0x10)==0x10)
// 			{
				
// 				//开关C1开
// 			}
// 			else if((B2_LORA&0x10)==0x10&&(DataRe_LORA.data[BOT2]&0x10)==0)
// 			{
// 				//开关C1关
// 			}
			
// 			if((B2_LORA&0x20)==0&&(DataRe_LORA.data[BOT2]&0x20)==0x20)
// 			{
// 				//开关C2开
// 			}
// 			else if((B2_LORA&0x20)==0x20&&(DataRe_LORA.data[BOT2]&0x20)==0)
// 			{
// 				//开关C2关
// 			}
			
// 			if((B2_LORA&0x40)==0&&(DataRe_LORA.data[BOT2]&0x40)==0x40)
// 			{
// 				//开关D1开
// 			}
// 			else if((B2_LORA&0x40)==0x40&&(DataRe_LORA.data[BOT2]&0x40)==0)
// 			{
// 				//开关D1关
// 			}
			
// 			if((B2_LORA&0x80)==0&&(DataRe_LORA.data[BOT2]&0x80)==0x80)
// 			{
// 				//开关D1开
// 			}
// 			else if((B2_LORA&0x80)==0x80&&(DataRe_LORA.data[BOT2]&0x80)==0)
// 			{
// 				//开关D2关
// 			}
// 			//更新标志位
// 			B1_LORA=DataRe_LORA.data[BOT1];
// 			B2_LORA=DataRe_LORA.data[BOT2];
			
//     } 
//   }
// }


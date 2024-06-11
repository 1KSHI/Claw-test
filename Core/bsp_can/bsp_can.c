/**
  *   @brief 这里是CAN中断接收函数，接收电机数据,CAN发送函数发送电机电流控制电机.
**/
#include "bsp_can.h"
#include "main.h"

extern CAN_HandleTypeDef hcan1; //CAN串口1
extern CAN_HandleTypeDef hcan2; //CAN串口2

static motor_measure_t motor_chassis_can1[8];
static motor_measure_t motor_chassis_can2[8];

//CAN1电机返回数据
motor_measure_t *motor_data_can1[8];
//CAN2电机返回数据
motor_measure_t *motor_data_can2[8];

//CAN1传输
static CAN_TxHeaderTypeDef chassis_tx_message;
static CAN_TxHeaderTypeDef chassis_tx_message2;

//CAN2传输
static CAN_TxHeaderTypeDef chassis_tx_message1;
static CAN_TxHeaderTypeDef chassis_tx_message3;

//CAN1储存电机返回数据（高八位第八位）
static uint8_t chassis_can_send_data[8];
static uint8_t chassis_can_send_data2[8]; 
//CAN2储存电机返回数据（高八位第八位）
static uint8_t chassis_can_send_data1[8];
static uint8_t chassis_can_send_data3[8]; 

/// @brief
#define get_motor_measure(ptr, data)                               \
  {                                                                \
    (ptr)->last_ecd = (ptr)->ecd;                                  \
    (ptr)->ecd = (uint16_t)((data)[0] << 8 | (data)[1]);           \
    (ptr)->speed_rpm = (uint16_t)((data)[2] << 8 | (data)[3]);     \
    (ptr)->given_current = (uint16_t)((data)[4] << 8 | (data)[5]); \
    (ptr)->temperate = (data)[6];                                  \
  }

void circle_cc(motor_measure_t *ptr)
{

  if (((ptr)->ecd - (ptr)->last_ecd) > 5000)
  {
    ptr->circle -= 1;
  }
  else if (((ptr)->ecd - (ptr)->last_ecd) < -5000)
  {

    ptr->circle += 1;
  }
}

/*	
电机数据：      0:底盘电机1 3508电机,              1:底盘电机2 3508电机,
		        2:底盘电机3 3508电机,              3:底盘电机4 3508电机;
                4:yaw云台电机 6020电机;            5:pitch云台电机 6020电机; 
		        6:拨弹电机 2006电机
*/

/// @brief hal库CAN回调函数,接收电机数据
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  if (hcan == &hcan1)
  {
    CAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[8];

    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data);

    switch (rx_header.StdId)
    {
    case CAN_3508_M1_ID:
    case CAN_3508_M2_ID:
    case CAN_3508_M3_ID:
    case CAN_3508_M4_ID:
    case CAN_3508_M5_ID:
    case CAN_3508_M6_ID:
    case CAN_3508_M7_ID:
    case CAN_3508_M8_ID:
    {

      static uint8_t i = 0;
      // get motor id
      i = rx_header.StdId - CAN_3508_M1_ID;
      get_motor_measure(&motor_chassis_can1[i], rx_data);
      circle_cc(&motor_chassis_can1[i]);
      break;
    }
    default:
    {
      break;
    }
    }
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
  }

  if (hcan == &hcan2)
  {
    CAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[8];

    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data);

    switch (rx_header.StdId)
    {
    case CAN_2006_M1_ID:
    case CAN_2006_M2_ID:
    case CAN_2006_M3_ID:
    case CAN_2006_M4_ID:
    case CAN_2006_M5_ID:
    case CAN_2006_M6_ID:
    case CAN_2006_M7_ID:
    case CAN_2006_M8_ID:
    {

      static uint8_t i = 0;
      // get motor id
      i = rx_header.StdId - CAN_2006_M1_ID;
      get_motor_measure(&motor_chassis_can2[i], rx_data);
      circle_cc(&motor_chassis_can2[i]);
      break;
    }
    default:
    {
      break;
    }
    }
    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
  }
}

/**
  * @brief          发送电机控制电流(0x201,0x202,0x203,0x204,0x205,0x206,0x207,0x208)
  * @param[in]      motor1: (0x201) 3508电机控制电流, 范围 [-16384,16384]
  * @param[in]      motor2: (0x202) 3508电机控制电流, 范围 [-16384,16384]
  * @param[in]      motor3: (0x203) 3508电机控制电流, 范围 [-16384,16384]
  * @param[in]      motor4: (0x204) 3508电机控制电流, 范围 [-16384,16384]
  * @param[in]      motor1: (0x205) 3508电机控制电流, 范围 [-16384,16384]
  * @param[in]      motor2: (0x206) 3508电机控制电流, 范围 [-16384,16384]
  * @param[in]      motor3: (0x207) 3508电机控制电流, 范围 [-16384,16384]
  * @param[in]      motor4: (0x208) 3508电机控制电流, 范围 [-16384,16384]
  */

//CAN1数据输入
void CAN1_cmd_chassis(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4, int16_t motor5, int16_t motor6, int16_t motor7, int16_t motor8)
{
  uint32_t send_mail_box;
  chassis_tx_message.StdId = CAN_CHASSIS_ALL_ID;
  chassis_tx_message.IDE = CAN_ID_STD;
  chassis_tx_message.RTR = CAN_RTR_DATA;
  chassis_tx_message.DLC = 0x08;
  chassis_can_send_data[0] = motor1 >> 8;
  chassis_can_send_data[1] = motor1;
  chassis_can_send_data[2] = motor2 >> 8;
  chassis_can_send_data[3] = motor2;
  chassis_can_send_data[4] = motor3 >> 8;
  chassis_can_send_data[5] = motor3;
  chassis_can_send_data[6] = motor4 >> 8;
  chassis_can_send_data[7] = motor4;
  
  HAL_CAN_AddTxMessage(&hcan1, &chassis_tx_message, chassis_can_send_data, &send_mail_box);

  chassis_tx_message2.StdId = CAN_GIMBAL_ALL_ID;
  chassis_tx_message2.IDE = CAN_ID_STD;
  chassis_tx_message2.RTR = CAN_RTR_DATA;
  chassis_tx_message2.DLC = 0x08;
  chassis_can_send_data2[0] = motor5 >> 8;
  chassis_can_send_data2[1] = motor5;
  chassis_can_send_data2[2] = motor6 >> 8;
  chassis_can_send_data2[3] = motor6;
  chassis_can_send_data2[4] = motor7 >> 8;
  chassis_can_send_data2[5] = motor7;
  chassis_can_send_data2[6] = motor8 >> 8;
  chassis_can_send_data2[7] = motor8;

  HAL_CAN_AddTxMessage(&hcan1, &chassis_tx_message2, chassis_can_send_data2, &send_mail_box);
  
}

//CAN2数据输入
void CAN2_cmd_chassis(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4, int16_t motor5, int16_t motor6, int16_t motor7, int16_t motor8)
{
  uint32_t send_mail_box;
  chassis_tx_message1.StdId = CAN_CHASSIS_ALL_ID;
  chassis_tx_message1.IDE = CAN_ID_STD;
  chassis_tx_message1.RTR = CAN_RTR_DATA;
  chassis_tx_message1.DLC = 0x08;
  chassis_can_send_data1[0] = motor1 >> 8;
  chassis_can_send_data1[1] = motor1;
  chassis_can_send_data1[2] = motor2 >> 8;
  chassis_can_send_data1[3] = motor2;
  chassis_can_send_data1[4] = motor3 >> 8;
  chassis_can_send_data1[5] = motor3;
  chassis_can_send_data1[6] = motor4 >> 8;
  chassis_can_send_data1[7] = motor4;

  HAL_CAN_AddTxMessage(&hcan2, &chassis_tx_message1, chassis_can_send_data1, &send_mail_box);

  chassis_tx_message3.StdId = CAN_GIMBAL_ALL_ID;
  chassis_tx_message3.IDE = CAN_ID_STD;
  chassis_tx_message3.RTR = CAN_RTR_DATA;
  chassis_tx_message3.DLC = 0x08;
  chassis_can_send_data3[0] = motor5 >> 8;
  chassis_can_send_data3[1] = motor5;
  chassis_can_send_data3[2] = motor6 >> 8;
  chassis_can_send_data3[3] = motor6;
  chassis_can_send_data3[4] = motor7 >> 8;
  chassis_can_send_data3[5] = motor7;
  chassis_can_send_data3[6] = motor8 >> 8;
  chassis_can_send_data3[7] = motor8;

  HAL_CAN_AddTxMessage(&hcan2, &chassis_tx_message3, chassis_can_send_data3, &send_mail_box);
}

//返回CAN1电机数据指针
motor_measure_t *get_chassis_motor_measure_point_can1(uint8_t i)
{
  return &motor_chassis_can1[(i)];
}

//返回CAN2电机数据指针
motor_measure_t *get_chassis_motor_measure_point_can2(uint8_t i)
{
  return &motor_chassis_can2[(i)];
}


void can_filter_init(void)
{
  CAN_FilterTypeDef can_filter_st;
  can_filter_st.FilterActivation = ENABLE;
  can_filter_st.FilterMode = CAN_FILTERMODE_IDMASK;
  can_filter_st.FilterScale = CAN_FILTERSCALE_32BIT;
  can_filter_st.FilterIdHigh = 0x0000;
  can_filter_st.FilterIdLow = 0x0000;
  can_filter_st.FilterMaskIdHigh = 0x0000;
  can_filter_st.FilterMaskIdLow = 0x0000;
  can_filter_st.FilterBank = 0;
  can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;
  HAL_CAN_ConfigFilter(&hcan1, &can_filter_st);
  HAL_CAN_Start(&hcan1);
  HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);

  HAL_CAN_ConfigFilter(&hcan2, &can_filter_st);
  HAL_CAN_Start(&hcan2);
  HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
}


//更新CAN1电机状态
void motor_state_update_can1()
{
  motor_data_can1[0] = get_chassis_motor_measure_point_can1(0);
  motor_data_can1[1] = get_chassis_motor_measure_point_can1(1);
  motor_data_can1[2] = get_chassis_motor_measure_point_can1(2);
  motor_data_can1[3] = get_chassis_motor_measure_point_can1(3);
  motor_data_can1[4] = get_chassis_motor_measure_point_can1(4);
  motor_data_can1[5] = get_chassis_motor_measure_point_can1(5);
  motor_data_can1[6] = get_chassis_motor_measure_point_can1(6);
  motor_data_can1[7] = get_chassis_motor_measure_point_can1(7);
}

//更新CAN2电机状态
void motor_state_update_can2()
{

  motor_data_can2[0] = get_chassis_motor_measure_point_can2(0);
  motor_data_can2[1] = get_chassis_motor_measure_point_can2(1);
  motor_data_can2[2] = get_chassis_motor_measure_point_can2(2);
  motor_data_can2[3] = get_chassis_motor_measure_point_can2(3);
  motor_data_can2[4] = get_chassis_motor_measure_point_can2(4);
  motor_data_can2[5] = get_chassis_motor_measure_point_can2(5);
  motor_data_can2[6] = get_chassis_motor_measure_point_can2(6);
  motor_data_can2[7] = get_chassis_motor_measure_point_can2(7);
}

//*******************************************************************�¼�

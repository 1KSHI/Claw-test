#ifndef CALCULATE_H
#define CALCULATE_H

#include "main.h"
#include "new_logic.h"
//重定义数组位
#define LX_LSB      0
#define LX_MSB      1
#define LY_LSB      2
#define LY_MSB      3
#define RX_LSB      4
#define RX_MSB      5
#define RY_LSB      6
#define RY_MSB      7
#define LP_LSB      8
#define LP_MSB      9
#define RP_LSB      10
#define RP_MSB      11
#define BOT1        12
#define BOT2        13

extern uint8_t I2C_TRANS_FLAG;
extern uint8_t M_3508_TRANS_FLAG;
extern uint8_t GPIO_CHANGE_FLAG;

extern uint8_t GPIO_CHANGE_STATE_1;
extern uint8_t GPIO_CHANGE_STATE_2;

extern float M_3508_YAW_TGT;
//重定义结构体
typedef struct struct_message {
  uint8_t header;
  uint8_t parity;
  uint8_t data[15];
  uint8_t footer;
} DataPacket;

//结构体
extern DataPacket DataRe_ESP;
//摇杆变量
extern int16_t lx_ESP ,ly_ESP,rx_ESP,ry_ESP,lp_ESP,rp_ESP;
//按键，开关
extern uint8_t B1_ESP,B2_ESP;
//校验位
extern uint8_t Cal_Parity_ESP;

//接收结构体
extern DataPacket DataRe_LORA;
//摇杆变量
extern int16_t lx_LORA ,ly_LORA,rx_LORA,ry_LORA,lp_LORA,rp_LORA;
//按键变量
extern uint8_t B1_LORA,B2_LORA;
//校验位
extern uint8_t Cal_Parity_LORA;


// 当前状态
extern enum State current_state;
extern int button_press_count;
uint8_t CalculateParity(const uint8_t* data, int dataSize);

void CAL_MESSAGE_ESP(void);
void CAL_MESSAGE_LORA(void);

#endif

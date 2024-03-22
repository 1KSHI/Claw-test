#ifndef LOGIC_H
#define LOGIC_H
#include "main.h"
#include "bsp_can.h"
#include "PID_MODEL.h"

/*动作完成判定*/
#define DOWN_ALLOW       0
#define UP_ALLOW         1
#define DOWN					   2
#define UP  					   3

/*动作完成判定*/
#define LEFT_ALLOW       0
#define RIGHT_ALLOW      1
#define LEFT       		   2
#define RIGHT  					 3

/*电机定义*/
#define  M_2006      0
#define  M_3508      1


#define Delay_Time  1000

extern int a_test;
extern int b_test;
extern int SPD_TGT[2];
extern uint8_t motor_state[2];
extern uint8_t init_FLAG[2];
//电机运动标志
extern enum FLAG move_FLAG[2];
//舵机运动标志
extern enum FLAG servo_FLAG;
//当前存放数量
extern uint8_t num_state;
extern enum FLAG Logic_FLAG;
extern enum FLAG logic_change;
extern double ZERO_POINT[2];
extern double TEMP_YAW_TGT_2006;
//1s内运动误差检测
extern double STL_BGN_ANG[2],STL_END_ANG[2];
extern int stl_error[2];
extern int stl_counter[2];

//电机数据
extern motor_measure_t   *motor_data[4];

//角度检测
extern double current_target[2];
extern double target_error[2];

//已转换目标角度
extern int ANG_TGT[2];

//目标角度
extern double YAW_TGT[2];

//电机数据
extern P rtP;

// 当前状态
extern enum State current_state;
void error_count_3508(void);
void error_count_2006(void);
void init_jaw(void);
//目标角度检测
void target_monitor(void);

//夹爪逻辑函数
void LOGIC(void);

//按键计数
extern int Pinch_count;
extern int Place_count;
// 定义夹爪状态
enum State {
    S_0,
		S_1,
		S_2,
		S_3
};

// 定义运动FLAG状态
enum FLAG {
    FREE,
    MOVE,
    FINISH,
		PINCH,
		PLACE
};


//void error_count();
//void init_jaw();
#endif


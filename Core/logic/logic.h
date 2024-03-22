#ifndef LOGIC_H
#define LOGIC_H
#include "main.h"
#include "bsp_can.h"
#include "PID_MODEL.h"

/*��������ж�*/
#define DOWN_ALLOW       0
#define UP_ALLOW         1
#define DOWN					   2
#define UP  					   3

/*��������ж�*/
#define LEFT_ALLOW       0
#define RIGHT_ALLOW      1
#define LEFT       		   2
#define RIGHT  					 3

/*�������*/
#define  M_2006      0
#define  M_3508      1


#define Delay_Time  1000

extern int a_test;
extern int b_test;
extern int SPD_TGT[2];
extern uint8_t motor_state[2];
extern uint8_t init_FLAG[2];
//����˶���־
extern enum FLAG move_FLAG[2];
//����˶���־
extern enum FLAG servo_FLAG;
//��ǰ�������
extern uint8_t num_state;
extern enum FLAG Logic_FLAG;
extern enum FLAG logic_change;
extern double ZERO_POINT[2];
extern double TEMP_YAW_TGT_2006;
//1s���˶������
extern double STL_BGN_ANG[2],STL_END_ANG[2];
extern int stl_error[2];
extern int stl_counter[2];

//�������
extern motor_measure_t   *motor_data[4];

//�Ƕȼ��
extern double current_target[2];
extern double target_error[2];

//��ת��Ŀ��Ƕ�
extern int ANG_TGT[2];

//Ŀ��Ƕ�
extern double YAW_TGT[2];

//�������
extern P rtP;

// ��ǰ״̬
extern enum State current_state;
void error_count_3508(void);
void error_count_2006(void);
void init_jaw(void);
//Ŀ��Ƕȼ��
void target_monitor(void);

//��צ�߼�����
void LOGIC(void);

//��������
extern int Pinch_count;
extern int Place_count;
// �����צ״̬
enum State {
    S_0,
		S_1,
		S_2,
		S_3
};

// �����˶�FLAG״̬
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


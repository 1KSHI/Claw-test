#ifndef NEW_LOGIC_H
#define NEW_LOGIC_H
#include "main.h"
#include "i2c.h"

#define M_2006 1
#define M_3508 0

typedef struct
{
  uint8_t state;
} MotorExtentTypeDef;

enum state{
  init=0,
  task_yaw_catch=1,
  task_yaw_replace=2,
  handle_TRANS_ON=3,
  handle_TRANS_OFF=4,
  handle_PLACE_SERVO_ON=5,
  handle_PLACE_SERVO_OFF=6,
  close=7
};


typedef void (*func_ptr)();
extern uint8_t catch_en;
extern uint8_t HIGH_TROQUE_TRANS_FLAG;
extern uint8_t SERVO_FLAG;
extern uint8_t SWITCH_SERVO;
extern MotorExtentTypeDef motorExtent;
extern float YAW_TGT[8];
extern uint8_t LOGIC_FLAG;
extern enum state next_state;
extern enum state current_state;

void handle_M_3508_UP(void);
void handle_M_3508_DOWN(void);
void handle_FRONT_CATCH_SERVO_ON(void);
void handle_FRONT_CATCH_SERVO_OFF(void);
void handle_TRANS_ON(void);
void handle_TRANS_OFF(void);
void handle_BACK_SERVO_ON(void);
void handle_BACK_SERVO_OFF(void);
void handle_HIGH_TORQUE(uint8_t *motorExtent);
void LOGIC(void);


void task_yaw_catch(void);
void task_yaw_replace(void);

#endif

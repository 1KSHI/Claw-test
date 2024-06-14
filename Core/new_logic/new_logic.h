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

extern MotorExtentTypeDef motorExtent;
extern float YAW_TGT[8];
extern uint8_t LOGIC_FLAG;
extern uint8_t logic_state;
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

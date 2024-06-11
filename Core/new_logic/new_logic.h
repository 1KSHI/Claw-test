#ifndef NEW_LOGIC_H
#define NEW_LOGIC_H
#include "main.h"
#include "i2c.h"

#define M_2006 3
#define M_3508 2

typedef struct
{
  uint8_t state;
} MotorExtentTypeDef;

extern MotorExtentTypeDef motorExtent;
extern float YAW_TGT[8];


void handle_M_3508_UP(void);
void handle_M_3508_DOWN(void);
void handle_FRONT_SERVO_ON(void);
void handle_FRONT_SERVO_OFF(void);
void handle_TRANS_ON(void);
void handle_TRANS_OFF(void);
void handle_BACK_SERVO_ON(void);
void handle_BACK_SERVO_OFF(void);
void handle_HIGH_TORQUE(MotorExtentTypeDef *motorExtent);


void task_yaw_catch(void);
void task_yaw_replace(void);
void task_place(void);

#endif

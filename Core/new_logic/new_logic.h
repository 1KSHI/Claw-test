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

typedef void (*func_ptr)();

func_ptr func_table[] = {
    init,
    task_yaw_catch,
    task_yaw_replace,
    handle_TRANS_ON,
    handle_TRANS_OFF,
    handle_PLACE_SERVO_ON,
    handle_PLACE_SERVO_OFF,
    close
};

extern uint8_t HIGH_TROQUE_TRANS_FLAG;
extern MotorExtentTypeDef motorExtent;
extern float YAW_TGT[8];
extern uint8_t LOGIC_FLAG;
extern uint8_t next_state;
extern uint8_t current_state;

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

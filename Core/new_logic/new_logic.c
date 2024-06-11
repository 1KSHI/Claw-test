#include "new_logic.h"
#include "i2c.h"
///
void handle_M_3508_UP(void){
    //ANG_TAG
    YAW_TGT[M_3508] = 30;
}

void handle_M_3508_DOWN(void){
    //ANG_TAG
    YAW_TGT[M_3508] = 0;
}

void handle_FRONT_SERVO_ON(void){
    //GPIO控制
}

void handle_FRONT_SERVO_OFF(void){
    //GPIO控制
}

void handle_TRANS_ON(void){
    //SPD_TAG
}

void handle_TRANS_OFF(void){
    //SPD_TAG
}

void handle_BACK_SERVO_ON(void){
    //PWM
}

void handle_BACK_SERVO_OFF(void){
    //PWM
}

void handle_HIGH_TORQUE(MotorExtentTypeDef *motorExtent){
    //I2C_TRANS
    HAL_I2C_Master_Transmit_DMA(&hi2c1, (uint16_t)I2C_SLAVE_ADDRESS, (uint8_t *)motorExtent, sizeof(motorExtent));
}


void task_yaw_catch(void){
    HAL_Delay(500);
    handle_FRONT_SERVO_ON();
    HAL_Delay(1000);
    //handle_M_3508_UP();
    HAL_Delay(2000);
    motorExtent.state = 0xab;
    handle_HIGH_TORQUE(&motorExtent);
    HAL_Delay(2000);
    handle_FRONT_SERVO_OFF();
    HAL_Delay(500);
}

void task_yaw_replace(void){
    HAL_Delay(500);
    motorExtent.state = 0xcd;
    handle_HIGH_TORQUE(&motorExtent);
    HAL_Delay(2000);
    handle_M_3508_DOWN();
    HAL_Delay(500);
}

void task_place(void){

}




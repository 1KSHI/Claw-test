#include "new_logic.h"
#include "i2c.h"
///
void handle_M_3508_UP(void){
    //ANG_TAG
    YAW_TGT[M_3508] = 720;
}

void handle_M_3508_DOWN(void){
    //ANG_TAG
    YAW_TGT[M_3508] = 120;
}

void handle_FRONT_CATCH_SERVO_ON(void){
    //GPIO控制
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
}

void handle_FRONT_CATCH_SERVO_OFF(void){
    //GPIO控制
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
}

void handle_FRONT_LEN_SERVO_ON(void){
    //GPIO控制
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
}

void handle_FRONT_LEN_SERVO_OFF(void){
    //GPIO控制
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
}

void handle_TRANS_ON(void){
    //SPD_TAG
    YAW_TGT[M_2006]=360;
}

void handle_TRANS_OFF(void){
    //SPD_TAG
    YAW_TGT[M_2006]=0;
}

void handle_BACK_SERVO_ON(void){
    //PWM
}

void handle_BACK_SERVO_OFF(void){
    //PWM
}

void handle_PLACE_SERVO_ON(void){
    //PWM
}

void handle_PLACE_SERVO_OFF(void){
    //PWM
}

void handle_HIGH_TORQUE(uint8_t *motorExtent){
    //I2C_TRANS
    while(HAL_I2C_Master_Transmit_DMA(&hi2c1, (uint16_t)I2C_SLAVE_ADDRESS, motorExtent, sizeof(motorExtent))!= HAL_OK)
    {
        /* Error_Handler() function is called when Timeout error occurs.
        When Acknowledge failure occurs (Slave don't acknowledge it's address)
        Master restarts communication */
        if (HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF)
        {
        Error_Handler();
        }
    }

    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
    {
    } 
}



void task_yaw_catch(void){
    HAL_Delay(500);
    handle_FRONT_CATCH_SERVO_ON();
    HAL_Delay(1000);
    handle_M_3508_UP();
    HAL_Delay(2000);
    motorExtent.state = 0xcd;
    handle_HIGH_TORQUE((uint8_t *)&motorExtent);
    HAL_Delay(2000);
    handle_FRONT_CATCH_SERVO_OFF();
    HAL_Delay(500);
}

void task_yaw_replace(void){
    HAL_Delay(500);
    motorExtent.state = 0xab;
    handle_HIGH_TORQUE((uint8_t *)&motorExtent);
    HAL_Delay(2000);
    handle_M_3508_DOWN();
    HAL_Delay(500);
}

void init(void){
    handle_FRONT_LEN_SERVO_ON();
}

void close(void){
    handle_FRONT_LEN_SERVO_OFF();
}

void LOGIC(void){
    if(LOGIC_FLAG){
        switch(logic_state){
            case 0:
                init();
                break;
            case 1:
                task_yaw_catch();
                break;
            case 2:
                task_yaw_replace();
                break;
            case 3:
                handle_TRANS_ON();
                break;
            case 4:
                handle_TRANS_OFF();
                break;
            case 5:
                handle_PLACE_SERVO_ON();
                break;
            case 6:
                handle_PLACE_SERVO_OFF();
                break;
            case 7:
                close();
                break;
            default:
                break;
        }
        LOGIC_FLAG=0;
    }
}




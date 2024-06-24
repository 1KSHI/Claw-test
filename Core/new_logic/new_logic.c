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
    SERVO_FLAG=1;
    SWITCH_SERVO=1;
    
}

void handle_FRONT_CATCH_SERVO_OFF(void){
    //GPIO控制
    SERVO_FLAG=1;
    SWITCH_SERVO=2;
    
}

void handle_FRONT_LEN_SERVO_ON(void){
    //GPIO控制
    SERVO_FLAG=1;
    SWITCH_SERVO=3;
   
}

void handle_FRONT_LEN_SERVO_OFF(void){
    //GPIO控制
    SERVO_FLAG=1;
    SWITCH_SERVO=4;
    
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
    
}

void task_yaw_catch(void){
    handle_FRONT_CATCH_SERVO_ON();
    HAL_Delay(1000);
    YAW_TGT[M_3508] = 1000;
    // motorExtent.state = 0xcd;
    // HIGH_TROQUE_TRANS_FLAG=1;
    // HAL_Delay(2000);
    // handle_FRONT_CATCH_SERVO_OFF();
}

void task_yaw_replace(void){
    // motorExtent.state = 0xab;
    // HIGH_TROQUE_TRANS_FLAG =1;
    // HAL_Delay(2000);
    YAW_TGT[M_3508] = 0;
    HAL_Delay(2000);
    handle_FRONT_CATCH_SERVO_OFF();
}

void init(void){
    motorExtent.state = 0xab;
    HIGH_TROQUE_TRANS_FLAG=1;
    HAL_Delay(1000);
    YAW_TGT[M_3508] = 0;
    // HAL_Delay(1000);
    // handle_FRONT_LEN_SERVO_ON();
}

void close(void){

}

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


void LOGIC(void){
    if(LOGIC_FLAG){
        if(current_state != next_state){
            if(next_state==task_yaw_catch && catch_en){
                func_table[next_state]();
                current_state = next_state;
                catch_en=0;
            }
            if(next_state==task_yaw_replace && !catch_en){
                func_table[next_state]();
                current_state = next_state;
                catch_en=1;
            }
            if(next_state!=task_yaw_catch || next_state!=task_yaw_replace){
                func_table[next_state]();
                current_state = next_state;
            }   
        } else if(next_state==init){
            func_table[next_state]();
        }

        LOGIC_FLAG=0;
    }
}



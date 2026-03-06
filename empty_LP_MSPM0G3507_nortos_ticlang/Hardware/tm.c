#include "encoder.h"
#include "motor.h"
#include "IR_module.h"
#include "mpu6050.h"
#include "oled.h"

#define BASE_SPEED  3000
#define TURN_SPEED  1500
#define STOP_TIME_MS 100

void tm1()
{
    char buf[16];
    IR_Module_Read();

    // 全灭，直行
    if(ir_dh1_state == 0 && ir_dh2_state == 0 && ir_dh3_state == 0 && ir_dh4_state == 0){
        Set_Speed(0, BASE_SPEED);
        Set_Speed(1, BASE_SPEED);
    }
    // 仅中间两个检测到，标准直行
    else if(ir_dh2_state == 1 && ir_dh3_state == 1 && ir_dh1_state == 0 && ir_dh4_state == 0){
        Set_Speed(0, BASE_SPEED);
        Set_Speed(1, BASE_SPEED);
    }
    // 偏左了，右轮快一点，左轮慢一点
    else if(ir_dh2_state == 1 && ir_dh3_state == 0){
        Set_Speed(0, BASE_SPEED);
        Set_Speed(1, TURN_SPEED);
    }
    // 偏右了，左轮快一点，右轮慢一点
    else if(ir_dh2_state == 0 && ir_dh3_state == 1){
        Set_Speed(0, TURN_SPEED);
        Set_Speed(1, BASE_SPEED);
    }
    // 极左：只有最左一个亮
    else if(ir_dh4_state == 1 && ir_dh1_state == 0 && ir_dh2_state == 0 && ir_dh3_state == 0){
        Set_Speed(0, TURN_SPEED / 2);
        Set_Speed(1, BASE_SPEED*2);
    }

    // 极右：只有最右一个亮
    else if(ir_dh1_state == 1 && ir_dh2_state == 0 && ir_dh3_state == 0 && ir_dh4_state == 0){
        Set_Speed(0, BASE_SPEED*2);
        Set_Speed(1, TURN_SPEED / 2);
    }
    // // 全亮，停止（如为终点或交叉路口）
    // else if(ir_dh1_state && ir_dh2_state && ir_dh3_state && ir_dh4_state){
    //     Set_Speed(0, 0);
    //     Set_Speed(1, 0);
    //     delay_ms(STOP_TIME_MS);
    // }
    else {
        // 其他情况兜底处理为直行
        Set_Speed(0, BASE_SPEED);
        Set_Speed(1, BASE_SPEED);
    }
    
}



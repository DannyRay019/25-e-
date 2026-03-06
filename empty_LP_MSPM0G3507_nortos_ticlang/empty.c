
#include "board.h"
#include "oled.h"
#include "motor.h"
#include "encoder.h"
#include "IR_module.h"
#include "tm.h"
#include "mpu6050.h"
#define DELAY (3200000)

int32_t encoderA_cnt,PWMA,encoderC_cnt,PWMC;
uint32_t cnt=0;
float yaw = 0.0f;
void test1();
void test2();

// 从 start 到 current 的最小角度差（[-180,180]）
float angle_diff(float start, float current) {
    float diff = current - start;
    while (diff > 180.0f) diff -= 360.0f;
    while (diff < -180.0f) diff += 360.0f;
    return diff;
}

// 只用陀螺积分更新 yaw（假设陀螺设为 500°/s 模式，FS_SEL=1）
void checkout() {
    int16_t accel[3], gyro[3];
    float temperature;
    mpu6050_read(gyro, accel, &temperature);

    int16_t gz_raw = gyro[2];
    // 500°/s 模式下灵敏度是 65.5 LSB/(°/s)
    float gz_dps = ((float)gz_raw) / 65.5f; // 单位：度每秒

    float dt = 0.01f; // 10ms 采样间隔，理论上要用实际定时器测得的真实 dt 更准

    yaw += gz_dps * dt;

    // 归一化到 [-180,180]
    while (yaw > 180.0f) yaw -= 360.0f;
    while (yaw < -180.0f) yaw += 360.0f;
}



void tm2()
{
    char buf[64];
    delay_ms(30);
    checkout();
	yaw = 0.0f;
    float yaw_start = yaw;
    delay_ms(30);
    Set_Speed(0, 3000);
    Set_Speed(1, -3000);
    while (1)
    {
        checkout(); // 更新 yaw
		snprintf(buf, sizeof(buf), "yaw:%f", yaw);
		OLED_ShowString(0,4,buf);
        float delta = angle_diff(yaw_start, yaw);
        if (fabsf(delta) >= 22.0f) {
            Set_Speed(0, 0);
            Set_Speed(1, 0);
            break;
        }
        delay_ms(10);
    }
    delay_ms(200);
}

int flag_move=0;

int main(void)
{
	int i=0;
    SYSCFG_DL_init();
	DL_Timer_startCounter(PWM_0_INST);
	DL_Timer_startCounter(PWM_1_INST);
	NVIC_ClearPendingIRQ(ENCODERA_INT_IRQN);
    NVIC_ClearPendingIRQ(ENCODERC_INT_IRQN);
	NVIC_EnableIRQ(ENCODERA_INT_IRQN);
    NVIC_EnableIRQ(ENCODERC_INT_IRQN);
	NVIC_ClearPendingIRQ(TIMER_0_INST_INT_IRQN);
	NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    OLED_Init();
	mpu6050_init();
	while (1)
    {
        clear_coder();
		float distA;
		char buf[16];
		while(1){
			distA = Get_TotalDistanceA_cm();
			snprintf(buf, sizeof(buf), "countA:%f", distA);
			OLED_ShowString(0, 2, buf);
			if(distA>17000.0f){
				tm2();
				break;
			}
			tm1();
			delay_ms(20);
		}

	}
}



//10ms��ʱ�ж�
void TIMER_0_INST_IRQHandler(void)
{
    if(DL_TimerA_getPendingInterrupt(TIMER_0_INST))
    {
        if(DL_TIMER_IIDX_ZERO)
        {			
		}
    }
}

#include "encoder.h"
#include <stdint.h>
#include <math.h>
uint32_t gpio_interrup1,gpio_interrup3;
int Get_Encoder_countA=0;
int Get_Encoder_countC=0;

void GROUP1_IRQHandler(void)//Group1的中断服务函数
{
    gpio_interrup1 = DL_GPIO_getEnabledInterruptStatus(ENCODERA_PORT,ENCODERA_E1A_PIN|ENCODERA_E1B_PIN);
    gpio_interrup3 = DL_GPIO_getEnabledInterruptStatus(ENCODERC_PORT,ENCODERC_E3A_PIN|ENCODERC_E3B_PIN);
    
    
	//encoderA
	if((gpio_interrup1 & ENCODERA_E1A_PIN)==ENCODERA_E1A_PIN)
	{
		if(!DL_GPIO_readPins(ENCODERA_PORT,ENCODERA_E1B_PIN))
		{
			Get_Encoder_countA--;
		}
		else
		{
			Get_Encoder_countA++;
		}
	}
	else if((gpio_interrup1 & ENCODERA_E1B_PIN)==ENCODERA_E1B_PIN)
	{
		if(!DL_GPIO_readPins(ENCODERA_PORT,ENCODERA_E1A_PIN))
		{
			Get_Encoder_countA++;
		}
		else
		{
			Get_Encoder_countA--;
		}
	}
	
	//encoderC
	if((gpio_interrup3 & ENCODERC_E3A_PIN)==ENCODERC_E3A_PIN)
	{
		if(!DL_GPIO_readPins(ENCODERC_PORT,ENCODERC_E3B_PIN))
		{
			Get_Encoder_countC--;
		}
		else
		{
			Get_Encoder_countC++;
		}
	}
	else if((gpio_interrup3 & ENCODERC_E3B_PIN)==ENCODERC_E3B_PIN)
	{
		if(!DL_GPIO_readPins(ENCODERC_PORT,ENCODERC_E3A_PIN))
		{
			Get_Encoder_countC++;
		}                 
		else              
		{                 
			Get_Encoder_countC--;
		}
	}
	DL_GPIO_clearInterruptStatus(ENCODERA_PORT,ENCODERA_E1A_PIN|ENCODERA_E1B_PIN);
	DL_GPIO_clearInterruptStatus(ENCODERC_PORT,ENCODERC_E3A_PIN|ENCODERC_E3B_PIN);
}

// 配置结构：轮子直径（cm）、编码器每圈原始脉冲、四分频倍数、减速比（motor_rev_per_wheel_rev）
typedef struct {
    float wheel_diameter_cm;    // 车轮直径，单位 cm
    int pulses_per_rev;         // 编码器本体每转一圈的原始脉冲 (A/B 相每个状态未分频前)
    int quadrature;             // 四分频：2 或 4（你用 A/B 边沿都判断一般是 4）
    float gear_ratio;           // 电机转一圈对应车轮转多少圈（有减速设为 <1；如果编码器装在轮子上设 1）
} EncoderConfig;

/**
 * @brief  计算本次与上次编码器计数差值对应的增量距离（带方向），单位 cm
 * @param  current_count 当前编码器计数（可带正负方向）
 * @param  last_count_ptr 指向保存的上一次计数（函数内部更新）
 * @param  cfg 配置（轮径、脉冲数、四分频、减速比）
 * @return 本次增量行驶距离，单位 cm（正/负表示方向）
 */
float Encoder_GetDeltaDistanceCm(int32_t current_count, int32_t *last_count_ptr, const EncoderConfig *cfg) {
    int32_t delta = current_count - *last_count_ptr;
    *last_count_ptr = current_count;

    // 轮周 = π * D
    float wheel_circumference = 3.1415926f * cfg->wheel_diameter_cm;

    // 每圈实际的有效脉冲数（编码器*四分频*电机->车轮关系）
    // gear_ratio 表示「电机转一圈对应车轮转多少圈」；如果编码器在轮子上且无减速，设 gear_ratio=1
    float effective_pulses_per_wheel_rev = cfg->pulses_per_rev * cfg->quadrature * cfg->gear_ratio;

    if (effective_pulses_per_wheel_rev == 0) return 0.0f; // 防除0

    // 每个脉冲对应的距离
    float distance_per_pulse = wheel_circumference / effective_pulses_per_wheel_rev;

    return delta * distance_per_pulse;
}

int32_t last_countA = 0;
float total_distanceA = 0.0f;

void clear_coder(){
	last_countA = 0;
	total_distanceA = 0.0f;
	Get_Encoder_countA = 0;
}

float Get_TotalDistanceA_cm(void) {

    // 示例配置：轮径6.5cm，编码器本体128脉冲/圈，四分频，编码器装在轮子上（无减速）
    const EncoderConfig cfg = {
        .wheel_diameter_cm = 4.8f,
        .pulses_per_rev = 13,
        .quadrature = 4,
        .gear_ratio = 1.0f / 20.0f 
    };

    float delta = Encoder_GetDeltaDistanceCm(Get_Encoder_countA, &last_countA, &cfg);
    total_distanceA += delta;
    return total_distanceA;
}



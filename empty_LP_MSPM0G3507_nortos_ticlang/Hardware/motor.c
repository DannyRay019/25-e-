#include "motor.h"
float Velcity_Kp=1.0,  Velcity_Ki=0.4,  Velcity_Kd; //����ٶ�PID����


void Set_Speed(int waychoose,int pwmnum)
{
	if(waychoose==0 && pwmnum<0)
    {
        DL_GPIO_setPins(AIN_PORT,AIN_AIN1_PIN);
        DL_GPIO_setPins(BIN_PORT,BIN_BIN2_PIN);
        DL_GPIO_clearPins(AIN_PORT,AIN_AIN2_PIN);
        DL_GPIO_clearPins(BIN_PORT,BIN_BIN1_PIN);
		DL_Timer_setCaptureCompareValue(PWM_0_INST,ABS(pwmnum),GPIO_PWM_0_C0_IDX);
        DL_Timer_setCaptureCompareValue(PWM_0_INST,ABS(pwmnum),GPIO_PWM_0_C1_IDX);
    }
    else if(waychoose==0 && pwmnum>=0)
    {
        DL_GPIO_setPins(AIN_PORT,AIN_AIN2_PIN);
        DL_GPIO_setPins(BIN_PORT,BIN_BIN1_PIN);
        DL_GPIO_clearPins(AIN_PORT,AIN_AIN1_PIN);
        DL_GPIO_clearPins(BIN_PORT,BIN_BIN2_PIN);
		DL_Timer_setCaptureCompareValue(PWM_0_INST,ABS(pwmnum),GPIO_PWM_0_C0_IDX);
        DL_Timer_setCaptureCompareValue(PWM_0_INST,ABS(pwmnum),GPIO_PWM_0_C1_IDX);
        
    }
    else if(waychoose==1 && pwmnum<0)
    {
		DL_GPIO_setPins(CIN_PORT,CIN_CIN2_PIN);
        DL_GPIO_setPins(DIN_PORT,DIN_DIN1_PIN);
        DL_GPIO_clearPins(CIN_PORT,CIN_CIN1_PIN);
        DL_GPIO_clearPins(DIN_PORT,DIN_DIN2_PIN);
        DL_Timer_setCaptureCompareValue(PWM_1_INST,ABS(pwmnum),GPIO_PWM_1_C0_IDX);
        DL_Timer_setCaptureCompareValue(PWM_1_INST,ABS(pwmnum),GPIO_PWM_1_C1_IDX);
    }
    else if(waychoose==1 && pwmnum>=0)
    {
		DL_GPIO_setPins(CIN_PORT,CIN_CIN1_PIN);
        DL_GPIO_setPins(DIN_PORT,DIN_DIN2_PIN);
        DL_GPIO_clearPins(CIN_PORT,CIN_CIN2_PIN);
        DL_GPIO_clearPins(DIN_PORT,DIN_DIN1_PIN);
        DL_Timer_setCaptureCompareValue(PWM_1_INST,ABS(pwmnum),GPIO_PWM_1_C0_IDX);
        DL_Timer_setCaptureCompareValue(PWM_1_INST,ABS(pwmnum),GPIO_PWM_1_C1_IDX);
    }
}




void Set_PWM(int pwmL,int pwmR)
{
	 if(pwmL>0)
    {
        DL_GPIO_setPins(AIN_PORT,AIN_AIN2_PIN);
        DL_GPIO_clearPins(AIN_PORT,AIN_AIN1_PIN);
		DL_Timer_setCaptureCompareValue(PWM_0_INST,ABS(pwmR),GPIO_PWM_0_C0_IDX);
       
    }
    else
    {
         DL_GPIO_setPins(AIN_PORT,AIN_AIN1_PIN);
        DL_GPIO_clearPins(AIN_PORT,AIN_AIN2_PIN);
		DL_Timer_setCaptureCompareValue(PWM_0_INST,ABS(pwmR),GPIO_PWM_0_C0_IDX);
       
    }
    if(pwmR>0)
    {
		DL_GPIO_setPins(BIN_PORT,BIN_BIN2_PIN);
        DL_GPIO_clearPins(BIN_PORT,BIN_BIN1_PIN);
		
		
       
        DL_Timer_setCaptureCompareValue(PWM_0_INST,ABS(pwmL),GPIO_PWM_0_C1_IDX);
    }
    else
    {
		DL_GPIO_setPins(BIN_PORT,BIN_BIN1_PIN);
        DL_GPIO_clearPins(BIN_PORT,BIN_BIN2_PIN);
		
       
		 DL_Timer_setCaptureCompareValue(PWM_0_INST,ABS(pwmL),GPIO_PWM_0_C1_IDX);
    }
   

}

/***************************************************************************
�������ܣ������PID�ջ�����
��ڲ��������ҵ���ı�����ֵ
����ֵ  �������PWM
***************************************************************************/
int Velocity_A(int TargetVelocity, int CurrentVelocity)
{  
    int Bias;  //������ر���
		static int ControlVelocityA, Last_biasA; //��̬�������������ý�������ֵ��Ȼ����
		
		Bias=TargetVelocity-CurrentVelocity; //���ٶ�ƫ��
		
		ControlVelocityA+=Velcity_Ki*(Bias-Last_biasA)+Velcity_Kp*Bias;  //����ʽPI������
                                                                   //Velcity_Kp*(Bias-Last_bias) ����Ϊ���Ƽ��ٶ�
	                                                                 //Velcity_Ki*Bias             �ٶȿ���ֵ��Bias���ϻ��ֵõ� ƫ��Խ����ٶ�Խ��
		Last_biasA=Bias;	
	    if(ControlVelocityA>7000) ControlVelocityA=7000;
	    else if(ControlVelocityA<-7000) ControlVelocityA=-7000;
		return ControlVelocityA; //�����ٶȿ���ֵ
}

/***************************************************************************
�������ܣ������PID�ջ�����
��ڲ��������ҵ���ı�����ֵ
����ֵ  �������PWM
***************************************************************************/
int Velocity_C(int TargetVelocity, int CurrentVelocity)
{  
    int Bias;  //������ر���
		static int ControlVelocityC, Last_biasC; //��̬�������������ý�������ֵ��Ȼ����
		
		Bias=TargetVelocity-CurrentVelocity; //���ٶ�ƫ��
		
		ControlVelocityC+=Velcity_Ki*(Bias-Last_biasC)+Velcity_Kp*Bias;  //����ʽPI������
                                                                   //Velcity_Kp*(Bias-Last_bias) ����Ϊ���Ƽ��ٶ�
	                                                                 //Velcity_Ki*Bias             �ٶȿ���ֵ��Bias���ϻ��ֵõ� ƫ��Խ����ٶ�Խ��
		Last_biasC=Bias;	
	    if(ControlVelocityC>7000) ControlVelocityC=7000;
	    else if(ControlVelocityC<-7000) ControlVelocityC=-7000;
		return ControlVelocityC; //�����ٶȿ���ֵ
}


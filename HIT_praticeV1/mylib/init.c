# include"init.h"


void all_init(void)
{
      TIM1_Config();
	    Usart_Configuration();//���ڳ�ʼ������
	
	    ADC1_Config();
	    CurrentZeroPointConfirm();
      
	    /*********  Ѱ�����   *********/
//	    reset_Config();
//	    while(!MotorMsg.Encoder.flag)
//			{
//			SetMotorPWM(750);
//			}
			SetMotorPWM(0);
	    Encoder_InitConfig();
	    TIM3_Start();
	    PID_InitConfig();
	    MotorMsg_InitConfig();
	    MotorMsg.Encoder.flag=0;
}

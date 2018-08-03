/*Include---------------------------*/
#include "stm32f10x_lib.h"		//�������е�ͷ�ļ�
#include "init.h"

extern float a,f,CurrentZeroPoint;
extern Motor_Control_TIME MotorTime;
extern float pwm;
extern POS_PID_Struct pid_config,PID_Motor_I;  //������;  //������
/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{
	//----------ʹ���ⲿRC����-----------
	RCC_DeInit();			//��ʼ��Ϊȱʡֵ
	RCC_HSEConfig(RCC_HSE_ON);	//ʹ���ⲿ�ĸ���ʱ�� 
	while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);	//�ȴ��ⲿ����ʱ��ʹ�ܾ���
	
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);	//Enable Prefetch Buffer
	FLASH_SetLatency(FLASH_Latency_2);		//Flash 2 wait state
	
	RCC_HCLKConfig(RCC_SYSCLK_Div1);		//HCLK = SYSCLK
	RCC_PCLK2Config(RCC_HCLK_Div1);			//PCLK2 =  HCLK
	RCC_PCLK1Config(RCC_HCLK_Div2);			//PCLK1 = HCLK/2
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);	//PLLCLK = 8MHZ * 9 =72MHZ
	RCC_PLLCmd(ENABLE);			//Enable PLLCLK

	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);	//Wait till PLLCLK is ready
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);	//Select PLL as system clock
	while(RCC_GetSYSCLKSource()!=0x08);		//Wait till PLL is used as system clock source
	
	//---------����Ӧ����ʱ��--------------------
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO,ENABLE);	//ʹ��APB2�����GPIOA��ʱ��		 
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
//	//����ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOC,ENABLE);
}

 

//void IO_Configuration(void)
//{
//	 GPIO_InitTypeDef GPIO_InitStructure; //GPIO�⺯���ṹ��
//	
//	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//	 /* Configure USART1 Tx (PA9) as alternate function push-pull */
//	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//PA9ʱ���ٶ�50MHz
//	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
//	 GPIO_Init(GPIOB, &GPIO_InitStructure);
//	
//}



/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/ 
int  main(void)
{  
//  	  int i;
      RCC_Configuration(); 
      delay_init(72);
  	  all_init();
	   
//	    for(i=0;i<=60000;i++)
//	 {
//	    CurrentZeroPointConfirm();
//	    printf("%.5f\r\n",CurrentZeroPoint);
//	 }
	   while(1)
		 {

			   if(MotorMsg.Encoder.flag!=0)
	       {
            #ifdef P_V_I_CONTROL_MODE  
	            printf("%.3f %.3f  %.3f  %.3f\r\n",MotorMsg.Encoder.Pos*360.0/36864,pwm,pid_config.LastError,pid_config.SumErr);
            #endif
					 
					  #ifdef P_V_CONTROL_MODE  
	            printf("%.3f  %.3f  %.3f  %.3f\r\n",MotorMsg.Encoder.Pos*360.0/36864,pwm,pid_config.LastError,pid_config.SumErr);
            #endif
					 
					  #ifdef V_I_CONTROL_MODE
					    printf ("%.3f %.3f  %.3f  %.3f  %.3f\r\n",MotorMsg.Current,MotorMsg.Encoder.Vol*1.0f,pwm,pid_config.LastError,pid_config.SumErr);
					  #endif
					  
					  #ifdef P_I_CONTROL_MODE
					    printf ("%.3f %.3f  %.3f  %.3f  %.3f \r\n",MotorMsg.Encoder.Pos*360.0/36864,pwm,pid_config.LastError,PID_Motor_I.I,pid_config.OutPut);
					  #endif
						
					  #ifdef P_CONTROL_MODE  
	            printf("%.3f\r\n",MotorMsg.Encoder.Pos*360.0/36864);
            #endif
					 
					  #ifdef V_CONTROL_MODE
					    printf("%.4f  %.4f\r\n",MotorMsg.Current,MotorMsg.zero);
					  #endif
						
					  #ifdef I_CONTROL_MODE
					    printf ("%.3f  %.3f  %.3f  %.3f  %.3f \r\n",MotorMsg.Current,pwm,pid_config.LastError,PID_Motor_I.I,pid_config.OutPut);
					  #endif
					 MotorMsg.Encoder.flag=0;
				 }

		    
		
		 }

	 }





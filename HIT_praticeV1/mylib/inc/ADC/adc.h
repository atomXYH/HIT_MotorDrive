#ifndef _ADC_H
#define _ADC_H
#endif


#include "stm32f10x_lib.h"		//�������е�ͷ�ļ�

void ADC1_Config(void);
u16 Get_ADC_Value(void);
void CurrentZeroPointConfirm(void);
float CurrentFitlter(float current);
float Get_Current(u8 mode);

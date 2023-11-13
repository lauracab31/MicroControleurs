#ifndef MYADC_H
#define MYADC_H

#include "stm32f10x.h"
#include "Driver_GPIO.h"

void MyADC_Init(ADC_TypeDef * Adc);
int MyADC_GetValue(int chan);


#endif
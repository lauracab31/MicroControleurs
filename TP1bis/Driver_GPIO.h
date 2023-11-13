#ifndef MYGPIO_H
#define MYGPIO_H
#include "stm32f10x.h"

#define In_Floating  0x0100
#define In_PullDown  0x1000
#define In_PullUp    0x1000
#define In_Analog    0x0000
#define Out_Ppull    0x0001
#define Out_OD       0x0101
#define AltOut_Ppull 0x1001
#define AltOut_OD    0x1101

void MyGPIO_Init (GPIO_TypeDef * GPIO, char GPIO_Pin, char GPIO_Conf);
int MyGPIO_Read(GPIO_TypeDef * GPIO, char GPIO_Pin);
void MyGPIO_Set(GPIO_TypeDef * GPIO, char GPIO_Pin);
void MyGPIO_Reset(GPIO_TypeDef * GPIO, char GPIO_Pin);
void MyGPIO_Toggle(GPIO_TypeDef * GPIO, char GPIO_Pin);
void MyGPIO_Clock(char GPIO);

#endif

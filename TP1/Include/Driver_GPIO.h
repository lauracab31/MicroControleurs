#ifndef MYGPIO_H
#define MYGPIO_H
#include "stm32f10x.h"

#define In_Floating  0x04  //on met 0x04 car on veut mettre 01 à CNF et 00 à MODE ( p.171)
#define In_PullDown  0x08
#define In_PullUp    0x28
#define In_Analog    0x00
#define Out_Ppull    0x01
#define Out_OD       0x05
#define AltOut_Ppull 0x09
#define AltOut_OD    0x0D

void MyGPIO_Init (GPIO_TypeDef * GPIO, char GPIO_Pin, char GPIO_Conf);
int MyGPIO_Read(GPIO_TypeDef * GPIO, char GPIO_Pin);
void MyGPIO_Set(GPIO_TypeDef * GPIO, char GPIO_Pin);
void MyGPIO_Reset(GPIO_TypeDef * GPIO, char GPIO_Pin);
void MyGPIO_Toggle(GPIO_TypeDef * GPIO, char GPIO_Pin);
void MyGPIO_Clock(char GPIO);

#endif

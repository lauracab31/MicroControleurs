#ifndef MYGPIO_H
#define MYGPIO_H
#include "stm32f10x.h"

#define In_Floating  0x04
#define In_PullDown  0x08
#define In_PullUp    0x08
#define In_Analog    0x00
#define Out_Ppull    0x01
#define Out_OD       0x05
#define AltOut_Ppull 0x09
#define AltOut_OD    0x0D

void MyGPIO_Init (GPIO_TypeDef * GPIO, char GPIO_Pin, char GPIO_Conf){
	if(GPIO_Pin < 8) {
		GPIO->CRL &= ~(0x0F<<4*GPIO_Pin);
		GPIO->CRL |= (GPIO_Conf<<4*GPIO_Pin);
	}else{
		GPIO->CRH &= ~(0x0F<<4*(GPIO_Pin - 8));
		GPIO->CRH |= (GPIO_Conf<<4*(GPIO_Pin - 8));
	}
}
int MyGPIO_Read(GPIO_TypeDef * GPIO, char GPIO_Pin){
	if((GPIO->IDR & (0x01<<GPIO_Pin))==(0x01<<GPIO_Pin)) {
		return 1;
	}else{
		return 0;
	}
}
void MyGPIO_Set(GPIO_TypeDef * GPIO, char GPIO_Pin){
	GPIO->BSRR |= (0x01<<GPIO_Pin);
}
void MyGPIO_Reset(GPIO_TypeDef * GPIO, char GPIO_Pin){
	GPIO->BRR |= (0x01<<GPIO_Pin);
}
void MyGPIO_Toggle(GPIO_TypeDef * GPIO, char GPIO_Pin){
	if(MyGPIO_Read(GPIO,GPIO_Pin) == 1){
		MyGPIO_Reset(GPIO,GPIO_Pin);
	}else{
		MyGPIO_Set(GPIO,GPIO_Pin);
	}
}
void MyGPIO_Clock(char GPIO){
	RCC->APB2ENR |= (0x01<<(GPIO - '?'));
}
#endif

#include "stm32f10x.h"
#include "Driver_GPIO.h"


void MyADC_Init(ADC_TypeDef * Adc) {
	if (Adc==ADC1) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	}	else if (Adc==ADC2) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
	}
	
	RCC->CFGR &= ~(0x03<<14);  // Prescaler mis à 6
	RCC->CFGR |= 0x02<<14;
	
	Adc->CR2 |= 0x01<<20; //exttrig
	Adc->CR2 |= 0x07<<17; //Choisir SWSTART comme évenement externe
	
	Adc->CR2 |= 0x01;
	
	
}

int MyADC_GetValue(int chan)
{
	// spécifie rle canal
	if (chan>9) {
		ADC1->SMPR1 &= ~(0x07<<((chan-10)*3));
		ADC1->SMPR1 |= (0x02<<((chan-10)*3));
	} else {
		ADC1->SMPR2 &= ~(0x07<<(chan*3));
		ADC1->SMPR2 |= 0x02<<(chan*3);
	}
	
	ADC1->SQR3 &= ~(31);
	ADC1->SQR3 |= chan
	
	// lancer la conv par le vit SWSTART
	
	ADC1->CR2 |= 0x01<<22
	// attendre que la conversion soit finie EOC
	
	while(not((ADC->SR & (0x01<<1))==(0x01<<1))) {
		null;
	}
	
	return(ADC->DR);
	
}

#include "stm32f10x.h"

/*#define In_Floating  0x04  //on met 0x04 car on veut mettre 01 � CNF et 00 � MODE ( p.171)
#define In_PullDown  0x08
#define In_PullUp    0x28
#define In_Analog    0x00
#define Out_Ppull    0x01
#define Out_OD       0x05
#define AltOut_Ppull 0x09
#define AltOut_OD    0x0D*/

void MyGPIO_Init (GPIO_TypeDef * GPIO, char GPIO_Pin, char GPIO_Conf){ //GPIO_Pin : ce qu'on veut changer, et conf ce qu'on veut mettre � la place
	
	if (GPIO==GPIOA) RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
			
	
	if(GPIO_Pin < 8) {  //car quand c'est en low, le pin <8
		
		GPIO->CRL &= ~(0x0F<<4*GPIO_Pin);   //si on veut mettre en low, c'est GPIO->CRL, on met tout � 0
		if (GPIO_Conf == 0x28){ 
			GPIO->CRL |= (0x08<<4*GPIO_Pin);
			GPIO->ODR |= (0x01<<GPIO_Pin);
		}else{
			GPIO->CRL |= (GPIO_Conf<<4*GPIO_Pin);
		}
	}else{
		GPIO->CRH &= ~(0x0F<<4*(GPIO_Pin - 8));  //M�me mais -8 car �a va de 8 � 15
		if (GPIO_Conf == 0x28){ 
			GPIO->CRL |= (0x08<<4*(GPIO_Pin-8));
			GPIO->ODR |= (0x01<<GPIO_Pin);
		}else{
		GPIO->CRH |= (GPIO_Conf<<4*(GPIO_Pin - 8));
	}
	
	}
			
}
int MyGPIO_Read(GPIO_TypeDef * GPIO, char GPIO_Pin){ // on compare 2 valeurs : que des 0 et le bit GPIO_Pin qu'on lit  dans IDR et que des 0 et 1 d�cal� de GPIO_Pin
	if((GPIO->IDR & (0x01<<GPIO_Pin))==(0x01<<GPIO_Pin)) { //si le registre GPIO_Pin est � 1 on renvoie 1 sinon on renvoie 0 (avec le 1er & on a la veleur du GPIO->IDR � notre Pin, et de l'autre c�t� on teste si �a vaut 0x01 d�cal� de pin
		return 1;
	}else{
		return 0;
	}
}
void MyGPIO_Set(GPIO_TypeDef * GPIO, char GPIO_Pin){ //on met le Bit d�cal� de GPIO_Pin � 1
	GPIO->BSRR |= (0x01<<GPIO_Pin);
}
void MyGPIO_Reset(GPIO_TypeDef * GPIO, char GPIO_Pin){
	GPIO->BRR |= (0x01<<GPIO_Pin);
}
void MyGPIO_Toggle(GPIO_TypeDef * GPIO, char GPIO_Pin){ //Toggle : pour inverser un bit
	GPIO->ODR ^= (0x01<<GPIO_Pin);
}
void MyGPIO_Clock(char GPIO){
	RCC->APB2ENR |= (0x01<<(GPIO - '?')); // ? car on veut faire -22
}

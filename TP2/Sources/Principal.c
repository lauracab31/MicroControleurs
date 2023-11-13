#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"


void Callback(void) {
	MyGPIO_Toggle(GPIOA,6);
}

int main(void) {
	
	MyGPIO_Init(GPIOA,6,Out_Ppull);
	

	
	MyTimer_Base_Init(TIM4,36000-1,1000-1);
	MyTimer_ActiveIT(TIM4,3, Callback);
	MyTimer_PWM(TIM4,1);
	MyTimer_SetDutyCycle(TIM4,1,25);
	MyTimer_Base_Start(TIM4);
	
	
	
	do{
	}while(1);
	
	/*RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	TIM2->CR1 |= (0x01);
	
	TIM2->ARR = (36000-1);  //ARR = valeur à partir de laquelle on réinitialise le compteur  (T = 500ms et Tck1=72M)
	TIM2->PSC = (1000-1);*/
	
	
	
}




 //RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4);
	
/*PROJET 1



	MyGPIO_Clock('A');
	MyGPIO_Clock('B');
	MyGPIO_Clock('C');
	// PA6 en sortie pp : CNFMOD = 0001
 //GPIOA->CRL &= ~(0x0F<<4*6); //on écrase toute la section à 0
 //GPIOA->CRL |= (0x01<<4*6); //on met 0001 à la place
	MyGPIO_Init(GPIOA,6,Out_Ppull);
	GPIOA->CRL |= (0x01 <<24); //on configure le port a5 en output (10Hz)
 
 GPIOA->CRL &= ~((0x01 <<26)|(0x01<<27)); //on configure le port a5 en push-pull
 GPIOA->ODR |= (0x01 <<6); //on active le registre 5 pour allumer la led
	
//Pas besoin de toucher au mode de C13 car il est en input au reset
 
		do
		{	if(MyGPIO_Read(GPIOA,7) == 1){
				MyGPIO_Reset(GPIOA,6);
			}else{
				MyGPIO_Set(GPIOA,6);
		}
	}while(1);*/

/*if((GPIOA->IDR & (GPIO_IDR_IDR7))==GPIO_IDR_IDR7){///GPIO_IDR_7 = 1<<7 // lorsque le bouton poussoir est allumé, la led s'allume (bouton = port 7 et led = port 6)
					GPIOA->ODR &= ~(0x01<<6);
			}else{
				GPIOA->ODR |= (0x01<<6);
			}*/
			
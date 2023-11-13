#include "stm32f10x.h"
#include "../Include/Driver_GPIO.h"
int main(void) 
{
 //RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4);
	MyGPIO_Clock('A');
	MyGPIO_Clock('B');
	MyGPIO_Clock('C');
	// PA6 en sortie pp : CNFMOD = 0001
 //GPIOA->CRL &= ~(0x0F<<4*6); //on écrase toute la section à 0
 //GPIOA->CRL |= (0x01<<4*6); //on met 0001 à la place
	MyGPIO_Init(GPIOA,6,Out_Ppull);
	/*GPIOA->CRL |= (0x01 <<24); //on configure le port a5 en output (10Hz)
 
 GPIOA->CRL &= ~((0x01 <<26)|(0x01<<27)); //on configure le port a5 en push-pull
 GPIOA->ODR |= (0x01 <<6); //on active le registre 5 pour allumer la led*/
	
//Pas besoin de toucher au mode de C13 car il est en input au reset
 
		do
		{	if(MyGPIO_Read(GPIOA,7) == 1){
				MyGPIO_Reset(GPIOA,6);
			}else{
				MyGPIO_Set(GPIOA,6);
		}
	}while(1);

}
/*if((GPIOA->IDR & (GPIO_IDR_IDR7))==GPIO_IDR_IDR7){///GPIO_IDR_7 = 1<<7 // lorsque le bouton poussoir est allumé, la led s'allume (bouton = port 7 et led = port 6)
					GPIOA->ODR &= ~(0x01<<6);
			}else{
				GPIOA->ODR |= (0x01<<6);
			}*/

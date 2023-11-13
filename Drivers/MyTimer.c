#include "stm32f10x.h" 
#include "Driver_GPIO.h"

void (*PIT1) (void);
void (*PIT2) (void);
void (*PIT3) (void);
void (*PIT4) (void);


void MyTimer_Base_Init(TIM_TypeDef * Timer, unsigned short ARR, unsigned short PSC) {
	
	if (Timer == TIM1) {  //Le timer1 est sur APB2 et les autres sur APB1 (schéma)
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	}else if (Timer == TIM2) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	}else if (Timer == TIM3) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	}else if (Timer == TIM4) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	}

	Timer->ARR = (ARR); //ARR = valeur à partir de laquelle on réinitialise le compteur 
	Timer->PSC = (PSC);  // PSC = régule l'horloge apparayée au timer 
	
}

void MyTimer_ActiveIT (TIM_TypeDef * Timer, char Prio, void (*IT_function) (void)){
	
	Timer->DIER |= (0x01);
	
	if (Timer == TIM1) { 
		NVIC->IP[25] =Prio<<4; //on met la priorité à Prio
		NVIC->ISER[0] |= 0x01<<25; //set enable registers for interruptions
		PIT1=IT_function;
	}else if (Timer == TIM2) {
		NVIC->IP[28] =Prio<<4;
		NVIC->ISER[0] |= 0x01<<28;
		PIT2=IT_function;
	}else if (Timer == TIM3) {
		NVIC->IP[29] =Prio<<4;
		NVIC->ISER[0] |= 0x01<<29;
		PIT3=IT_function;
	}else if (Timer == TIM4) {
		NVIC->IP[30] =Prio<<4;
		NVIC->ISER[0] |= 0x01<<30;
		PIT4=IT_function;
	}
	
}

void TIM1_UP_IRQHandler(void){
	TIM1->SR &= ~(0x01);
	(*PIT1) ();
}

void TIM2_IRQHandler(void){
	TIM2->SR &= ~(0x01);
	(*PIT2) ();
}

void TIM3_IRQHandler(void){
	TIM3->SR &= ~(0x01);
	(*PIT3) ();
}

void TIM4_IRQHandler(void){
	TIM4->SR &= ~(0x01);
	(*PIT4) ();
}

void MyTimer_PWM(TIM_TypeDef * Timer, char Channel){
	Timer->CCER |= (1<<4*(Channel-1)); //on les active
	if (Channel > 2){
		Timer->CCMR2 &= ~(3<<8*(Channel - 3));
		Timer->CCMR2 |= (96<<8*(Channel - 3));		//on met en output le 3 et le 4 (il faut mettre à 0 ce champ de bits)
	}else{
		Timer->CCMR1 &= ~(3<<8*(Channel - 1));
		Timer->CCMR1 |= (96<<8*(Channel - 1));		//on met en output le 1 et le 2
	}
	
	if (Timer == TIM4){
		if (Channel == 1) {
			MyGPIO_Init(GPIOB,6,AltOut_Ppull);
		}
	}else if (Timer == TIM3) {
		if (Channel == 1) {
			MyGPIO_Init(GPIOB,4,AltOut_Ppull);
		}else if (Channel == 2) {
			MyGPIO_Init(GPIOC,7,AltOut_Ppull);
		}
	}else if (Timer == TIM2) {
		if (Channel == 2) {
			MyGPIO_Init(GPIOB,3,AltOut_Ppull);
		}else if (Channel ==3) {
			MyGPIO_Init(GPIOB,10,AltOut_Ppull);
		}
	}
}

void MyTimer_SetDutyCycle(TIM_TypeDef * Timer, char Channel, int Rapport) {
	
	int Cycle = (Rapport*(Timer->ARR))/100;
	
	if(Channel==1) {
		Timer->CCR1 = Cycle;
	}else if(Channel==2) {
		Timer->CCR2 = Cycle;
	}else if(Channel==3) {
		Timer->CCR3 = Cycle;
	}else if(Channel==4) {
		Timer->CCR4 = Cycle;
	}
}
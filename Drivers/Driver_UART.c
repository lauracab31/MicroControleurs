#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"

void Uart_init(USART_TypeDef * Uart, unsigned int baudrate){
	if (Uart == USART1){
		RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;
	} else if (Uart == USART2){
		RCC -> APB1ENR |= RCC_APB1ENR_USART2EN;
	} else if (Uart == USART3){
		RCC -> APB1ENR |= RCC_APB1ENR_USART3EN;
	} 
	
	Uart -> CR1 |= USART_CR1_UE;
	Uart -> CR1 &= ~USART_CR1_M;
	Uart -> CR2 &= USART_CR2_STOP;
	//DMA 
	//Uart-> CR3 |= USART_CR3_DMAT;
	//bandrate Tx/Rx band = fCK/(16*USARTDIV)
	//Uart -> BRR 
	int fPCLK;	
	if (Uart == USART1){
		fPCLK = 72000000;
	} else {
	  fPCLK = 36000000;
	}
	
	
	Uart-> CR1 |= USART_CR1_TE;	
}

void Send(USART_TypeDef * Uart, char data){
	Uart->DR |= data;
	while(!(Uart->SR & USART_SR_TC));
}

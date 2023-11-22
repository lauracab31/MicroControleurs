#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"

/*void Uart_init(USART_TypeDef * Uart, unsigned int baudrate) {
    // 根据输入的 Uart 参数选择使能相应的外设时钟
    if (Uart == USART1) {
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    } else if (Uart == USART2) {
        RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    } else if (Uart == USART3) {
        RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
    } else if (Uart == UART4) {
        RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
    } else if (Uart == UART5) {
        RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
    }

    // 使能 USART 外设
    Uart->CR1 |= USART_CR1_UE;
    
    // 清除原来的 M 和 STOP 位
    Uart->CR1 &= ~USART_CR1_M;
    Uart->CR2 &= ~USART_CR2_STOP;

    // 波特率计算
    int fPCLK;
    if (Uart == USART1 || Uart == USART2) {
        fPCLK = 72000000;
    } else {
        fPCLK = 36000000;
    }
    Uart->BRR = fCK / (16 * baudrate);

    // 使能发送功能
    Uart->CR1 |= USART_CR1_TE; 
}
*/

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

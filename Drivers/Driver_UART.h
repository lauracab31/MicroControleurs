#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"

void Uart_init(USART_TypeDef * Uart,unsigned int baudrate);

void Send(USART_TypeDef * Uart, char data);

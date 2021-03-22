#ifndef __UART_H__
#define __UART_H__

#include "stm32f10x_conf.h"
#include "stdint.h"
#include "stdio.h"


#define INTERRUPT_EN      //串口中断标志，
#define USART1_BAUDRATE  115200

uint8_t USART1_RXData_Resolve(uint8_t rx_data);
void usart1_Init(uint32_t bound);
void USART_SendByByte(USART_TypeDef* USARTx,uint8_t data);





#endif

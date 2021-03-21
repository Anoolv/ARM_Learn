#ifndef __UART_H__
#define __UART_H__

#include "stm32f10x_conf.h"
#include "pin_cfg_mask.h"
#include "stdint.h"
#include "stdio.h"


#define INTERRUPT_EN                 //串口中断标志，
#define USART1_BAUDRATE  115200


void Usart1_InitCfg(uint32_t bound);
void Usart_SendByte(USART_TypeDef* USARTx, uint8_t data);
void Usart_SendHalfWord(USART_TypeDef* USARTx, uint16_t data);
void Usart_SendString(USART_TypeDef* USARTx, char* p_data);

#endif

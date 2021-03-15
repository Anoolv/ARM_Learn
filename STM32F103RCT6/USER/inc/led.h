#ifndef	__LED_H__
#define	__LED_H__

#include <stm32f10x.h>
#include "stm32f10x_conf.h"

#define RGT_OPT_FLAG		//寄存器操作标志位,使用寄存器操作就定义，使用库函数就注释掉

#define LED1_PORT 			GPIOA   
#define LED1_PIN 			GPIO_Pin_8
#define LED1_PORT_RCC		RCC_APB2Periph_GPIOA

#define LED2_PORT 			GPIOD   
#define LED2_PIN 			GPIO_Pin_2
#define LED2_PORT_RCC		RCC_APB2Periph_GPIOD	

typedef enum
{
	LED_1 = 0,
	LED_2 = 1	
}LED_NUM;

void LED_Init(void );
void Led_Ctl(LED_NUM num, BitAction status);

#endif

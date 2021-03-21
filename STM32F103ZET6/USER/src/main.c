#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "clock_config.h"
#include "led.h"
#include "usart.h"

int main(void)
{
	char * say_hi = "welcome to my channel!";
	RCC_HSEConfig(RCC_HSE_ON);
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	LED_Init();
	Usart1_InitCfg(USART1_BAUDRATE);

	Usart_SendString(USART1, say_hi);
	while(1)
	{	
		Led_Ctl(LED_1,Bit_RESET);
		delay_ms(500);
		Led_Ctl(LED_1,Bit_SET);
		Led_Ctl(LED_2,Bit_RESET);
		delay_ms(500);
		Led_Ctl(LED_2,Bit_SET);
	}	
	
}

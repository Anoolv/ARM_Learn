#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "led.h"
#include "lcd.h"
#include "usart.h"

int main(void)
{
	char * say_hi = "Hello,this is Anoolv! ^-^ \n welcome to my channel!\n";
	LED_Init();
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	usart1_Init(USART1_BAUDRATE);

	printf(say_hi);

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

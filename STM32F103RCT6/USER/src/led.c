#include "led.h"



/***
*@function: this function is used to initial the LED hardware,
*		   like GPIO Clock  Registersand so on.
*
***/
#ifdef RGT_OPT_FLAG				//是否定义了寄存器操作标志位
void LED_Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPDEN ;

	GPIOA->CRH &= ~(GPIO_CRH_CNF8 | GPIO_CRH_MODE8) ;
	GPIOD->CRL &= ~(GPIO_CRL_CNF2 | GPIO_CRL_MODE2) ;

	GPIOA->CRH |= (GPIO_CRH_MODE8) ;
	GPIOD->CRL |= (GPIO_CRL_MODE2) ;

	GPIOA->BSRR = LED1_PIN;
	GPIOD->BSRR = LED2_PIN;
}

void Led_Ctl(LED_NUM num,BitAction status)
{
	switch(num)
	{
		case LED_1:
			if(status)
				GPIOA->BSRR = LED1_PIN ;	
			else 
				GPIOA->BRR = LED1_PIN ;
		break;

		case LED_2:
			if(status)
				GPIOD->BSRR = LED2_PIN ;
			else
				GPIOD->BRR = LED2_PIN ; 
		break;

		default:
			GPIOA->BSRR = LED1_PIN;
			GPIOD->BSRR = LED2_PIN;
		break;
	}
}

#else
void LED_Init(void)
{
	GPIO_InitTypeDef LED_IO_Struct;					//define a struct variable of gpio for the 
													//led needed,and use to "GPIO_Init()"
	
	RCC_APB2PeriphClockCmd(LED1_PORT_RCC,ENABLE);
    RCC_APB2PeriphClockCmd(LED1_PORT_RCC,ENABLE);    //initial GPIO clock
	
	LED_IO_Struct.GPIO_Pin = LED1_PIN;			//set the io which is used
	LED_IO_Struct.GPIO_Mode = GPIO_Mode_Out_PP;		//set as Push-pull output mode
	LED_IO_Struct.GPIO_Speed = GPIO_Speed_50MHz;	//set working speed as 50MHz
	GPIO_Init(LED1_PORT,&LED_IO_Struct);

	LED_IO_Struct.GPIO_Pin = LED2_PIN;			//set the io which is used
	LED_IO_Struct.GPIO_Mode = GPIO_Mode_Out_PP;		//set as Push-pull output mode
	LED_IO_Struct.GPIO_Speed = GPIO_Speed_50MHz;	//set working speed as 50MHz
    GPIO_Init(LED2_PORT ,&LED_IO_Struct);                        //initial GPIO registers

    GPIO_SetBits(LED1_PORT ,LED1_PIN);    
    GPIO_SetBits(LED2_PORT ,LED2_PIN);                         //reset GPIO level status

}
/***
*function: control LED working status
*
***/
void Led_Ctl(LED_NUM num,BitAction status)
{
	switch(num)
	{
		case LED_1:
			if(status)
				GPIO_SetBits(LED1_PORT,LED1_PIN);
			else 
				GPIO_ResetBits(LED1_PORT,LED1_PIN);
		break;

		case LED_2:
			if(status)
				GPIO_SetBits(LED2_PORT,LED2_PIN);
			else
				GPIO_ResetBits(LED2_PORT,LED2_PIN);
		break;

		default:
			GPIO_ResetBits(LED1_PORT ,LED1_PIN);
			GPIO_ResetBits(LED2_PORT ,LED2_PIN);
		break;
	}
}
#endif

/*******************************************************************************
 * Func:	clock_config.c
 * Describle: thiese functions are used to configure the SYStick,
 * 			for the function of delay.  
 * Created on: 2021年3月2日
 * Author: kaysen
*******************************************************************************/
#include "clock_config.h"


/*******************************************************************************
 * @函 数 名         : delay_us
 * @函数功能		   : us延时，
 * @输    入         : nus：要延时的us数
 *					注意:nus的值,不要大于798915us(最大值即2^24/fac_us@fac_us=21)
 * @输    出         : 无
 *******************************************************************************/
void delay_us(uint32_t us) 
{
	uint32_t temp;
	SysTick->LOAD = SystemCoreClock/8/ULTS*us; 		//时间加载,YSTICK的时钟固定为AHB时钟的1/8
	SysTick->VAL = 0x00;        					//清空计数器
	SysTick->CTRL = 0x01;							//开始倒数
	do 
	{
		temp = SysTick->CTRL;
	} while ((temp & 0x01) && !(temp & (1 << 16)));		//等待时间到达
	SysTick->CTRL = 0X00;								//关闭计数器
	SysTick->VAL = 0X00;      					 		//清空计数器
}
 
/*******************************************************************************
 * 函 数 名         : delay_ms
 * 函数功能		   : ms延时，
 * 输    入         : nms：要延时的ms数
 *					注意:nms的值,SysTick->LOAD为24位寄存器，
 *					不要大于0xffffff*8*1000/SYSCLK
 *					对72M条件下,nms<=1864ms
 * 输    出         : 无
 *******************************************************************************/
void delay_ms(uint16_t ms) 
{
	u32 temp;
	SysTick->LOAD = (uint32_t)SystemCoreClock/8/MILLIS*ms;			//时间加载(SysTick->LOAD为24bit)
	//SysTick->LOAD = (uint32_t)9000000/MILLIS*ms;
	SysTick->VAL = 0x00;											//清空计数器
	SysTick->CTRL = 0x01;											//开始倒数
	do 
	{
		temp = SysTick->CTRL;
	} while ((temp & 0x01) && !(temp & (1 << 16)));					//等待时间到达
	SysTick->CTRL = 0X00;											//关闭计数器
	SysTick->VAL = 0X00;      					 					//清空计数器 
}

void delay_s(uint8_t s) 
{
	u32 temp;
	SysTick->LOAD = (u32)SystemCoreClock/8/SECOND*s;				//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL = 0x00;											//清空计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;						//开始倒数
	SysTick->CTRL = 0x01;											//开始倒数
	do {
		temp = SysTick->CTRL;
	} while ((temp & 0x01) && !(temp & (1 << 16)));					//等待时间到达
	SysTick->CTRL = 0X00;											//关闭计数器
	SysTick->VAL = 0X00;      					 					//清空计数器  
}

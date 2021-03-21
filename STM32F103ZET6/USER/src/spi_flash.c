#include "spi.h"
#include "W25X16.h"
/*****
 * @function:  SPI2_InitCfg()
 * @brief  SPI2的初始化配置，具体配置为：主机模式-CLK空闲为高
 *         -偶数采样-8bit传输-LSB模式的双线单向输出模式
 * @param  USARTx:USART1-USART5
 *         data：发送的数据   
 * @retval 无
 *****/ 
void SPI2_InitCfg()
{
    RCC->APB2ENR |= 0X00001008 ;
    GPIOB->CRH &= 0X0000FFFF ;
    GPIOB->CRH |= 0XB4BB ;

    SPI2->CR1 &= ~(0X40CF) ;
    SPI2->CR1 |= 0X40CF ;
    SPI2->CR2 &= ~(0X0040) ;
    SPI2->CR2 |= 0X0040 ;

    SPI2_STOP();
}

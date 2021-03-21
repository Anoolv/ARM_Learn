#ifndef __SPI_H__
#define __SPI_H__

#include "stm32f10x.h"
#include "stm32f10x_conf.h"


#define SPI2_PORT        GPIOB
#define SPI2_CS_PIN      GPIO_Pin_12
#define SPI2_SCK_PIN     GPIO_Pin_13
#define SPI2_MISO_PIN    GPIO_Pin_14
#define SPI2_MOSI_PIN    GPIO_Pin_15

#define SPI2_STOP()       (GPIOB->ODR |= 0X1000) //停止信号 FLASH: CS引脚高电平
#define SPI2_START()      (GPIOB->ODR &= 0XEFFF)


void SPI2_InitCfg();
  
#endif

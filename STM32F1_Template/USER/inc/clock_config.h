#ifndef __CLOCK_CONFIG__
#define __CLOCK_CONFIG__

#include <stm32f10x.h>
#include "stm32f10x_conf.h"

/**—” ± ±º‰ªªÀ„∫Í**/
#define SECOND	1
#define MILLIS	1000
#define ULTS	1000000   

void delay_ms(uint16_t ms);
void delay_us(uint32_t us);
void delay_s(uint8_t s);

#endif

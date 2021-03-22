#include "stm32f0xx_conf.h"
#include "led.h"
int main()
{
    led_Init();
    while(1)
    {
        led_Ctl(ON);
    }
    return 0;
}

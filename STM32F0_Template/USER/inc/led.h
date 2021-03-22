#ifndef LED_H
#define LED_H

typedef enum
{
    ON  = 0,
    OFF = 1
}LED_STATUS;

extern LED_STATUS led_sta;
void led_Init(void);
void led_Ctl(LED_STATUS status);

#endif
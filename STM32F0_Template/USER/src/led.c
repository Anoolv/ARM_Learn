#include "led.h"
#include "stm32f0xx.h"
#include "stm32f0xx_gpio.h"

LED_STATUS led_sta;
void led_Init(void)
{
    // RCC->AHBENR |= RCC_AHBENR_GPIOAEN ;

    // GPIOA->MODER &= ~GPIO_MODER_MODER7;
    // GPIOA->MODER |= GPIO_MODER_MODER7_0;

    // GPIOA->OTYPER |= GPIO_OTYPER_OT_7;

    // GPIOA->PUPDR &= 0xFFFFCFFF;

    // GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR7;
    // GPIOA->BSRR |= GPIO_BSRR_BR_7;
    GPIO_InitTypeDef led;
    led.GPIO_Mode = GPIO_Mode_OUT;
    led.GPIO_Speed = GPIO_Speed_Level_3;
    led.GPIO_Pin = GPIO_Pin_7;
    led.GPIO_PuPd = GPIO_PuPd_NOPULL;
    led.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOA,&led);
    GPIO_ResetBits(GPIOA,GPIO_Pin_7);

}
void led_Ctl(LED_STATUS status)
{
    switch(status)
    {
        case ON:
            GPIOA->MODER &= ~GPIO_MODER_MODER7;
            GPIOA->MODER |= GPIO_MODER_MODER7_0; 
            GPIOA->ODR |= GPIO_ODR_7;
             //GPIO_SetBits(GPIOA,GPIO_Pin_7);
            //GPIOA->ODR |= GPIO_ODR_7;
            break;
        case OFF:
            GPIOA->MODER &= ~GPIO_MODER_MODER7;
            GPIOA->MODER |= GPIO_MODER_MODER7_0;
            GPIOA->ODR &= ~GPIO_ODR_7;
            // GPIO_ResetBits(GPIOA,GPIO_Pin_7);
            //GPIOA->ODR &= ~(GPIO_ODR_7);
            break;
        
        default:
             GPIO_ResetBits(GPIOA,GPIO_Pin_7);
            //GPIOA->BSRR |= GPIO_BSRR_BR_7;
            break;
    }
}

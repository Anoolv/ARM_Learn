/********************************************************************************
  * @file    usart.c
  * @author  Anoolv
  * @version V1.0
  * @date    2021-03
  * @brief   usart初始化配置；重定向c库printf函数到 USART1 端口；
  ******************************************************************************/
#include "usart.h"

 /*****
  * @brief  重定向c库函数printf到串口，重定向后可使用printf函数
  * @param  无
  * @retval 无
  * @note 
  *****/
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}


 /*****
  * @brief  重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
  * @param  无
  * @retval 无
  * @note  
  *****/
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}


 /*****
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  * @note 不允许外部文件调用，在 usart1_Init 中调用配置中断
  *****/
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}


/*****
 * @function usart1_Init(uint32_t pclk2 , uint32_t bound)
 * @brief  初始化USART1：1、使能串口和所使用的IO（PA9 PA10）的时钟，
 *         2、设置IO为相应状态（工作模式、工作速率）；
 *         3、配置波特率；
 * @param  pclk2:PCLK2时钟频率(Mhz)  bound:波特率 
 * @retval 无
 *****/ 
void usart1_Init(uint32_t bound)
{
/*** 0：计算波特率寄存器的值 ***/  
    float temp ;
    uint32_t pclk2;
    uint16_t mantissa ;                             
    uint16_t fraction ;	  

    RCC_ClocksTypeDef RCC_ClocksStatus;
    RCC_GetClocksFreq(&RCC_ClocksStatus);
    pclk2 = RCC_ClocksStatus.PCLK2_Frequency;

    temp=(float)(pclk2*1000000)/(bound*16) ;   //得到USARTDIV
    mantissa=temp ;				                    //得到波特率整数部分
    fraction=(temp-mantissa)*16 ;              //得到波特率小数部分	 
    mantissa<<=4 ;
    mantissa+=fraction ;                       //得到寄存器存储的波特率的十六进制值
/*** 1：串口时钟使能、GPIO时钟使能***/
  //  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA,ENABLE);
    RCC->APB2ENR = RCC_APB2ENR_USART1EN  | RCC_APB2ENR_IOPAEN ;
/****2：串口复位，非必须**/ 

/***3：IO模式设置:GPIO_Init（）；***/
    GPIOA->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10 \
                  | GPIO_CRH_CNF9 | GPIO_CRH_MODE9) ;    
    GPIOA->CRH |= (GPIO_CRH_CNF9_1 | GPIO_CRH_CNF10_0 \
                  | GPIO_CRH_MODE9) ; //p9 作为Tx引脚，设置为复用-推挽-输出模式；p10作为Rx引脚，设置为复用-浮空-输入模式
/***4：配置波特率寄存器***/ 
    USART1->BRR |=  mantissa ;
#ifdef INTERRUPT_EN
/***5：开启中断并且初始化NVIC***/
     NVIC_Configuration() ;
     USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
#endif
/***6：使能串口***/
    USART1->CR1 |= USART_CR1_UE ;

}

/***7：编写中断处理函数***/
 /*****
  * @brief  USART1回调函数，实现了将接收数据处理后，返回发送方的功能
  * @param  无
  * @retval 无
  * @note 
  *****/
void UASRT1_CallBack(void)
{
  uint8_t data_temp;
  if(USART1->SR & USART_SR_RXNE)
  {
      data_temp = ( USART1->DR & (uint16_t)0x01FF );
      data_temp = USART1_RXData_Resolve(data_temp);
      USART1->DR = ( (uint16_t)0x01FF & data_temp );
  }
}

 /*****
  * @brief  USART1接收数据的处理函数，具体处理过程待书写
  * @param  无
  * @retval 无
  * @note 
  *****/
uint8_t USART1_RXData_Resolve(uint8_t rx_data)
{
    uint8_t data_resolved = rx_data;

    return data_resolved;
}
 
 
void USART_SendByByte(USART_TypeDef* USARTx,uint8_t data)
{
    
    while (USARTx->SR & USART_FLAG_TXE);
    USARTx->DR = (data & 0x01ff);
    
}

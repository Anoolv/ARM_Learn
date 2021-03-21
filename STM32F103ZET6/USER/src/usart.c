/********************************************************************************
  * @file    usart.c
  * @author  Anoolv
  * @version V1.0
  * @date    2021-03
  * @brief   usart初始化配置；重定向c库printf函数到 USART1 端口；
  ******************************************************************************/
#include "usart.h"


/*****
 * @function: usart1_Init(uint32_t bound)
 * @brief  初始化USART1：1、使能串口和所使用的IO（PA9 PA10）的时钟，
 *         2、设置IO为相应状态（工作模式、工作速率）；
 *         3、配置波特率；
 * @param  bound:波特率，USART1的时钟为PCLK2时钟频率(Mhz)   
 * @retval 无
 *****/ 
void Usart1_InitCfg(uint32_t bound)
{
  USART_InitTypeDef USART1_InitStruct ;
  NVIC_InitTypeDef NVIC_InitStructure ;

  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN ; 
  GPIOA->CRH |= 0X000004B0;

  USART1_InitStruct.USART_BaudRate = bound ;
  USART1_InitStruct.USART_HardwareFlowControl =  USART_HardwareFlowControl_None ;
  USART1_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx ;
  USART1_InitStruct.USART_Parity = USART_Parity_No ;
  USART1_InitStruct.USART_StopBits = USART_StopBits_1 ;
  USART1_InitStruct.USART_WordLength = USART_WordLength_8b ;
  USART_Init(USART1,&USART1_InitStruct) ;

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

  USART1->CR1 |= 0X2020 ;
}

/*****
 * @function: UsartSendByte(USART_TypeDef* USARTx,uint8_t data)
 * @brief  发送一个字节的数据
 * @param  USARTx:USART1-USART5
 *         data：发送的数据   
 * @retval 无
 *****/ 
void Usart_SendByte(USART_TypeDef* USARTx, uint8_t data)
{
  while ( (USART1->SR & USART_FLAG_TXE) == RESET);
 // USART_SendData(USARTx,data);
  USART1->DR = (data & 0x01FF);
  while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
}

/*****
 * @function: UsartSendHalfWord(USART_TypeDef* USARTx, uint16_t data)
 * @brief  发送两个字节的数据
 * @param  USARTx:USART1-USART5
 *         data：发送的数据   
 * @retval 无
 *****/ 
void Usart_SendHalfWord(USART_TypeDef* USARTx, uint16_t data)
{
  uint8_t data_H, data_L ;
  data_H =(uint8_t) (data >> 8) ;
  data_L = (uint8_t) data;

  while ( (USART1->SR & USART_FLAG_TXE) == RESET);
  USART_SendData(USARTx,data_H);
  while ( (USART1->SR & USART_FLAG_TXE) == RESET);
  USART_SendData(USARTx,data_L);
}

/*****
 * @function:  UsartSendString(USART_TypeDef* USARTx, char* p_data)
 * @brief  发送一个字符串
 * @param  USARTx:USART1-USART5
 *         data：发送的数据   
 * @retval 无
 *****/ 
void Usart_SendString(USART_TypeDef* USARTx, char* p_data)
{
  unsigned int str_offset = 0 ;
  char last_char = '\0' ;
  do
  {
    while ( (USART1->SR & USART_FLAG_TXE) == RESET);
    USART_SendData(USARTx, *(p_data + str_offset));
    str_offset ++ ;
  } while (*(p_data + str_offset) != last_char) ;

   while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
  
}

void USART1_IRQHandler(void)
{
  uint8_t res_data;
  
  if(USART_GetITStatus(USART1,USART_IT_RXNE))
  {
    res_data = USART_ReceiveData(USART1);
    USART_SendData(USART1,(res_data & 0x01FF));
  }
}
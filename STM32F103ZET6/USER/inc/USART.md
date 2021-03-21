一、串口相关寄存器

1:  USART_SR---状态寄存器
2:  USART_DR---数据寄存器
3:  USART_BRR---波特率寄存器
4： USART_CR1---控制使能寄存器（发送、接收、中断）



二、串口操作常用库函数

1:  void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct);
    初始化函数，用于 波特率，数据字长，奇偶校验的设置，以及硬件流控制和收发使能。

2： void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
    串口使能函数

3： void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState);
    相关中断配置函数

4： void USART_SendData(USART_TypeDef* USARTx, uint16_t Data);
    数据发送函数：发送数据到串口的DR寄存器

5： uint16_t USART_ReceiveData(USART_TypeDef* USARTx);
    数据接收函数：从DR寄存器读取接收到的数据

6： FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG);
    获取状态标识位函数： 获取串口的状态

7： void USART_ClearFlag(USART_TypeDef* USARTx, uint16_t USART_FLAG);
    清除状态标识位函数

8： ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint16_t USART_IT);
    获取中断标识位函数

9： void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT);
    清除中断标识位函数

<!-- 三、串口配置步骤

1：串口时钟使能、GPIO时钟使能：void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, 
                            FunctionalStateNewState);

2：串口复位：USART_DeInit();//非必须

3：GPIO模式设置:GPIO_Init（）；模式设置为GPIO_Mode_AF_PP

4：串口初始化：USART_Init（）；

5：开启中断并且初始化NVIC: NVIC_Init();
                         USART_ITConfig();

6：使能串口：USART_Cmd();

7：编写中断处理函数：USARTx_IRQHandler();

8:串口数据收发：

9：串口传输状态和中断状态获取： -->


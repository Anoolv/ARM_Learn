#include "lcd.h"

/****************************************************************************
* @function:	LCD_GPIO_GPIO_Config( void )
* @brief:  LCD_GPIO  �漰GPIO����
* @param:  ��
* @retval: ��
* @note:  LCD_GPIO��MCU�����ã����Ŷ�Ӧ���±���ʾ��
*	 _______________________________________________________________________
*	|		LCD:	|	MCU--AF:	   |		LCD:		MCU--AF:		|
*	|---------------|------------------|------------------------------------|	
*	|		DB1		|	PD_14--D0	   |		DB10		PE_11--D8       |
*	|		DB2		|	PD_15--D1	   |		DB11		PE_12--D9		|	
*	|		DB3		|	PD_0--D2	   |		DB12		PE_13--D10		|
*	|		DB4		|	PD_1--D3	   |		DB13		PE_14--D11		|
*	|		DB5		|	PE_7--D4	   |		DB14		PE_15--D12		|
*	|		DB6		|	PE_8--D5	   |		DB15		PD_8--D13		|
*	|		DB7		|	PE_9--D6	   |		DB16		PD_9--D14		|
*	|		DB8		|	PE_10--D7	   |		DB17		PD_10--D15		|
*	|---------------|------------------|------------------------------------|
*	|	LCD_CS		|	PG_12--NE4	   |		T_CS		PF_11--T_CS  	|
*	|	WR/CLK		|	PD_5--NWE      |		RS			PG_0--A10  		|
*	|	RST			|	NRST--RESET	   |		RD			PD_4--NOE 		|
*	|	BL			|	PB_0--LCD_BL   |		MOSI		PF_9--T_MOSI	|
*	|	VDD3.3		|	VCC3.3         |		MO			-  				|
*	|	MISO		|	PB_2--T_MISO   |		CLK			PD_14--SCK  	|
*	|	T_PEN		|	PF_10--T_PEN   |								  	|
*	|_______________________________________________________________________|
***************************************************************************/
void LCD_GPIO_GPIO_Config( void )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitTypeDef* LCD_GPIO = &GPIO_InitStructure;
	/*** GPIO_PORTʱ��enable ***/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB|
							RCC_APB2Periph_GPIOD|
							RCC_APB2Periph_GPIOD|
							RCC_APB2Periph_GPIOG,
							ENABLE);

	/*** LCD_GPIO_BL---MCU_GPIOB���� ***/
	LCD_GPIO->GPIO_Pin = GPIO_Pin_0;
	LCD_GPIO->GPIO_Mode = GPIO_Mode_Out_PP;
	LCD_GPIO->GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOB,LCD_GPIO);

	/*** MCU_GPIOD FSMC�������� ***/
	LCD_GPIO->GPIO_Pin =( GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|
					 	  GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|
					 	  GPIO_Pin_10|GPIO_Pin_14|GPIO_Pin_15 ) ; //PORTD�����������  
 	LCD_GPIO->GPIO_Mode = GPIO_Mode_AF_PP; 		 //����FSMC�������   
	LCD_GPIO->GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOD,LCD_GPIO);
	
	/*** MCU_GPIOE FSMC�������� ***/
	LCD_GPIO->GPIO_Pin =( GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|
					 	  GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|
					 	  GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15 ) ; //PORTD�����������  
 	LCD_GPIO->GPIO_Mode = GPIO_Mode_AF_PP; 		 //����FSMC�������   
	LCD_GPIO->GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOE,LCD_GPIO);
	
	/*** MCU_GPIOG FSMC��LCDƬѡ���������� ***/
	LCD_GPIO->GPIO_Pin =( GPIO_Pin_0|GPIO_Pin_12 ) ; //PORTD�����������  
 	LCD_GPIO->GPIO_Mode = GPIO_Mode_AF_PP; 		 //����FSMC�������   
	LCD_GPIO->GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOG,LCD_GPIO);
}

/*****************************************************************
* @function:	LCD_FSMC_Config( void )
* @brief  LCD FSMC ģʽ����
* @param  ��
* @retval ��
*****************************************************************/
void LCD_FSMC_Config( void )
{
	/*** ����fsmc nor sram��ʼ���ṹ�� ***/
	/*** ����fsmc nor sram�ṹ��ָ�루����ʹ�ã� ***/
	FSMC_NORSRAMInitTypeDef		NORSRAM_Init_Struct;
	FSMC_NORSRAMInitTypeDef*	NORSRAM_Prt = &NORSRAM_Init_Struct;
	/*** ����WriteTiming��ʼ���ṹ�� ***/
	/*** ����WriteTiming�ṹ��ָ�루����ʹ�ã� ***/
	FSMC_NORSRAMTimingInitTypeDef	WriteTiming;
	FSMC_NORSRAMTimingInitTypeDef*  WT_Ptr = &WriteTiming;
	/*** ����Read_WriteTiming��ʼ���ṹ�� ***/
	/*** ����Read_WriteTiming�ṹ��ָ�루����ʹ�ã� ***/
	FSMC_NORSRAMTimingInitTypeDef 	Read_WriteTiming;
	FSMC_NORSRAMTimingInitTypeDef*  RWT_Ptr = &Read_WriteTiming;
	
	/*** ��ַ����ʱ�䣨ADDSET��Ϊ1��HCLK   ***/
	RWT_Ptr->FSMC_AddressSetupTime = 0x00;	 
	/*** ��ַ����ʱ�䣨ADDHLD��   ***/
	RWT_Ptr->FSMC_AddressHoldTime = 0x00;	 
	/*** ���ݽ���ʱ��Ϊ4��HCLK   ***/
	RWT_Ptr->FSMC_DataSetupTime = 0x03;		 	
	RWT_Ptr->FSMC_BusTurnAroundDuration = 0x00;
	RWT_Ptr->FSMC_CLKDivision = 0x00;
	RWT_Ptr->FSMC_DataLatency = 0x00;
	RWT_Ptr->FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 
	
	WT_Ptr->FSMC_AddressSetupTime = 0x01;	 //��ַ����ʱ�䣨ADDSET��Ϊ2��HCLK 1/36M=27ns
	WT_Ptr->FSMC_AddressHoldTime = 0x00;	 //��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�	
	WT_Ptr->FSMC_DataSetupTime = 0x0f;		 // ���ݱ���ʱ��Ϊ16��HCLK,��ΪҺ������IC�Ķ����ݵ�ʱ���ٶȲ���̫�죬�����1289���IC��
	WT_Ptr->FSMC_BusTurnAroundDuration = 0x00;
	WT_Ptr->FSMC_CLKDivision = 0x00;
	WT_Ptr->FSMC_DataLatency = 0x00;
	WT_Ptr->FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 
		
	/*** ����ʹ�õ��Ĵ洢���ź����� ***/
	NORSRAM_Prt->FSMC_Bank = FSMC_Bank1_NORSRAM4;
	/*** ���ô洢������ ***/
	NORSRAM_Prt->FSMC_MemoryType = FSMC_MemoryType_SRAM;
	/*** �������ݿ��(8bit/16bit) ***/
	NORSRAM_Prt->FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	/*** д����ʹ�� ***/
	NORSRAM_Prt->FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	/***  FSMC_BurstAccessMode_Disable ***/
	NORSRAM_Prt->FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	NORSRAM_Prt->FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	NORSRAM_Prt->FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable; 
	NORSRAM_Prt->FSMC_WrapMode = FSMC_WrapMode_Disable;   
	NORSRAM_Prt->FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
	NORSRAM_Prt->FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//  �洢��дʹ��
	NORSRAM_Prt->FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
	NORSRAM_Prt->FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // ��дʹ�ò�ͬ��ʱ��
	NORSRAM_Prt->FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
	NORSRAM_Prt->FSMC_ReadWriteTimingStruct = WT_Ptr; //��дʱ��
	NORSRAM_Prt->FSMC_WriteTimingStruct = RWT_Ptr;  //дʱ��
	
	/*** ���ÿ⺯����ʼ��FSMC���� ***/
	FSMC_NORSRAMInit(NORSRAM_Prt);
	/*** ʹ��BANK1 ***/
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);
	/*** ʹ��FSMCʱ�� ***/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC , ENABLE);
}



#ifndef LCD_H
#define LCD_H

#include "clock_config.h"
#include "stm32f10x_conf.h"
#include "stm32f10x.h"

/*
*********************ɫ��ֵ********************************
 */
//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
//#define LIGHTGRAY        0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)
/*
********************* LCD��������********************************
 */
typedef struct
{
    uint16_t GET_ID;      //0XD3    //��ȡLCD��ID�������ж�LCD�ͺ�
    uint16_t X_SET;       //0X2A    //�ڴ����ң����ϵ��µ�ɨ�跽ʽ��Ĭ�ϣ�ʱ���������ú����꣨x ���꣩
    uint16_t Y_SET;       //0X2B    //�ڴ����ң����ϵ��µ�ɨ�跽ʽ��Ĭ�ϣ�ʱ���������������꣨y ���꣩
    uint16_t WT_GRAM;     //0X2C    //��GRAMд����ɫ����
    uint16_t RD_GRAM;     //0X2E    //��GRAMд����ɫ����
    uint16_t WTRD_DIR;    //0X36    //����������дGRAMʱ������LCDɨ�跽�򣬺��MY�� MX�� MV����
}LCD_COMMAND;

extern const  LCD_COMMAND ILI9341_CMD;  //�˴��õ���ΪILI9341�ͺŵ�LCD

/*
********************* LCD��ַ�ṹ��********************************
 */
typedef struct
{
	vu16 LCD_REG;
	vu16 LCD_RAM;
} LCD_ADDR;
//ʹ��NOR/SRAM�� Bank1.sector4,��ַλHADDR[27,26]=11 A10��Ϊ�������������� 
//ע������ʱSTM32�ڲ�������һλ����! 
#define LCD_BASE        ((uint32_t)(0x6C000000 | 0x000007FE))
#define LCD             ((LCD_ADDR *) LCD_BASE)			    

/*
*********************LCD��������********************************
 */
typedef struct 
{
    uint16_t    LCD_Width;
    uint16_t    LCD_Length;

    uint16_t    LCD_ID;
}LCD_BASE_PARA;

extern LCD_BASE_PARA LCD_Base_Para;

/*
*********************LCD��ʾ����********************************
 */
typedef struct
{
    uint16_t    Back_Color;     //����ɫ
    uint16_t    Point_Color;    //����ɫ
    uint8_t     Display_Dir;    //0,������1������
    uint16_t    X_CDT;         //  ��ʾ��x������ʼλ��
    uint16_t    Y_CDT;         //  ��ʾ��Y������ʼλ��
}LCD_DISPLAY_PARA;

extern LCD_DISPLAY_PARA LCD_Display_Para;
/*
*********************LCDɨ�跽���־********************************
 */
typedef enum
{
    DFT_SCAN_DIR = 0,  //0Ĭ�ϵ�ɨ�跽��

    L2R_U2D , //1 ������,���ϵ���
    L2R_D2U , //2 ������,���µ���
    R2L_U2D , //3 ���ҵ���,���ϵ���
    R2L_D2U , //4 ���ҵ���,���µ���

    U2D_L2R , //5 ���ϵ���,������
    U2D_R2L , //6 ���ϵ���,���ҵ���
    D2U_L2R , //7 ���µ���,������
    D2U_R2L , //8 ���µ���,���ҵ���	 

}SCAN_DIR_FLAG;

extern SCAN_DIR_FLAG Scan_DIR_Flag;
void LCD_FSMC_Config( void );
void LCD_GPIO_Config( void );


/**
* @brief  lcd ��ʼ���ú�����������ʼ����FSMC��GPIO��
* @param  ��
* @retval ��
*/
void LCD_Init( void );
#endif

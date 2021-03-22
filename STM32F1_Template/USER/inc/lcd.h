#ifndef LCD_H
#define LCD_H

#include "clock_config.h"
#include "stm32f10x_conf.h"
#include "stm32f10x.h"

/*
*********************色彩值********************************
 */
//画笔颜色
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
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
//#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)
/*
********************* LCD常用命令********************************
 */
typedef struct
{
    uint16_t GET_ID;      //0XD3    //读取LCD的ID，用于判断LCD型号
    uint16_t X_SET;       //0X2A    //在从左到右，从上到下的扫描方式（默认）时，用于设置横坐标（x 坐标）
    uint16_t Y_SET;       //0X2B    //在从左到右，从上到下的扫描方式（默认）时，用于设置纵坐标（y 坐标）
    uint16_t WT_GRAM;     //0X2C    //往GRAM写入颜色数据
    uint16_t RD_GRAM;     //0X2E    //往GRAM写入颜色数据
    uint16_t WTRD_DIR;    //0X36    //用于连续读写GRAM时，控制LCD扫描方向，后跟MY、 MX、 MV参数
}LCD_COMMAND;

extern const  LCD_COMMAND ILI9341_CMD;  //此处用到的为ILI9341型号的LCD

/*
********************* LCD地址结构体********************************
 */
typedef struct
{
	vu16 LCD_REG;
	vu16 LCD_RAM;
} LCD_ADDR;
//使用NOR/SRAM的 Bank1.sector4,地址位HADDR[27,26]=11 A10作为数据命令区分线 
//注意设置时STM32内部会右移一位对其! 
#define LCD_BASE        ((uint32_t)(0x6C000000 | 0x000007FE))
#define LCD             ((LCD_ADDR *) LCD_BASE)			    

/*
*********************LCD基础参数********************************
 */
typedef struct 
{
    uint16_t    LCD_Width;
    uint16_t    LCD_Length;

    uint16_t    LCD_ID;
}LCD_BASE_PARA;

extern LCD_BASE_PARA LCD_Base_Para;

/*
*********************LCD显示参数********************************
 */
typedef struct
{
    uint16_t    Back_Color;     //背景色
    uint16_t    Point_Color;    //画笔色
    uint8_t     Display_Dir;    //0,竖屏；1，横屏
    uint16_t    X_CDT;         //  显示点x坐标起始位置
    uint16_t    Y_CDT;         //  显示点Y坐标起始位置
}LCD_DISPLAY_PARA;

extern LCD_DISPLAY_PARA LCD_Display_Para;
/*
*********************LCD扫描方向标志********************************
 */
typedef enum
{
    DFT_SCAN_DIR = 0,  //0默认的扫描方向

    L2R_U2D , //1 从左到右,从上到下
    L2R_D2U , //2 从左到右,从下到上
    R2L_U2D , //3 从右到左,从上到下
    R2L_D2U , //4 从右到左,从下到上

    U2D_L2R , //5 从上到下,从左到右
    U2D_R2L , //6 从上到下,从右到左
    D2U_L2R , //7 从下到上,从左到右
    D2U_R2L , //8 从下到上,从右到左	 

}SCAN_DIR_FLAG;

extern SCAN_DIR_FLAG Scan_DIR_Flag;
void LCD_FSMC_Config( void );
void LCD_GPIO_Config( void );


/**
* @brief  lcd 初始化该函数，函数初始化了FSMC、GPIO等
* @param  无
* @retval 无
*/
void LCD_Init( void );
#endif

#ifndef  __PIN_CFG_MASK__
#define  __PIN_CFG_MASK__

/*** CR寄存器CNF位通用输出模式设置 ***/
#define CNF_PP_G         0X0        
#define CNF_OD_G         0X4
/*** CR寄存器CNF位复用输出模式设置 ***/
#define CNF_PP_A         0X8
#define CNF_OD_A         0XC
/*** CR寄存器MODE位通用和复用输出模式设置 ***/
#define MOD_LOW_O        0X2        //输出速度为2MHZ
#define MOD_MID_O        0X1        //输出速度为10MHZ
#define MOD_HIG_O        0X3        //输出速度为50MHZ
/*** CR寄存器MODE位输入模式设置 ***/
#define MOD_IN           0X0 
/*** CR寄存器CNF位输入模式设置 ***/
#define CNF_ANALOG_IN    0X0
#define CNF_FLOAT_IN     0X4
#define CNF_PDPU_IN      0X8
/*** CR寄存器MODE位输入模式设置 ***/

/*** GPIO_CR寄存器单个pin配置 ***/
#define PIN_MASK        0xF          //单个pin脚的掩码值，用于取反清零pin脚 CR寄存器的值 

#define GPOP_PP_50MHZ   (CNF_PP_G | MOD_HIG_O)          //单个pin脚通用-推挽-输出模式，50MHz速率对应的CR寄存器值  
#define AFOP_PP_50MHZ   (CNF_PP_A | MOD_HIG_O)          //单个pin脚复用-推挽-输出模式，50MHz速率对应的CR寄存器值  
#define IP_FT           (CNF_FLOAT_IN | MOD_IN)          //单个pin脚浮空-输入模式，对应的CR寄存器值  


#endif
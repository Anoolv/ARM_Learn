该文件夹内为ST ARM系列部分芯片的工程模板，使用环境为VSCode+EIDE插件；请悉知。

EIDE插件可兼容KEIL5及以上工程。

.eide           :为EIDE配置文件（请勿删除）
.vscode         :为vscode配置文件（请勿删除）

STM32F10x_StdPeriph_Driver  \
CMSIS           :为ST官方标准库文件（其中.ld链接文件为CubeMX生成）
OBJS            :为EIDE生成目标文件存放路径
USER            :为用户代码存放路径
.code-workspace ：该后缀文件为EIDE工程文件

该工程实现了USART1的基本通信（数据收发）


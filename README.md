# SYD8811SDK  
## 本程序版权属于成都盛芯微科技SYDTEK，更多内容请看官网：<a href="http://www.sydtek.com/" title="Title">http://www.sydtek.com/</a>

2018-12-26  
1.第一版
<br/><br/><br/>

2019-1-24  
1.修改触摸的驱动使其有自动校正的功能！
<br/><br/><br/>

2019-3-22  
1.更新SDK中各个工程的协议栈lib文档，涉及的文件如下：
"SYD8811_SDK\Source Code\SYD8811_ble_peripheral\3.SYD8811_HID\ble\syd8811_ble_lib.lib"
"SYD8811_SDK\Source Code\ble\syd8811_ble_lib.lib"
"SYD8811_SDK\Source Code\SYD8811_ble_peripheral\1.SYD8811_UART original\ble\syd8811_ble_lib.lib"
"SYD8811_SDK\Source Code\SYD8811_ble_peripheral\1.SYD8811_UART\ble\syd8811_ble_lib.lib"
"SYD8811_SDK\SourceCode\SYD8811_ble_peripheral\2.SYD8811_UART_Capdet_Touch\ble\syd8811_ble_lib.lib"
<br/><br/><br/>

2019-5-22  
1、整理Source Code工程的架构，各个文件功能说明如下  
A、Driver、Include、Rtt存放8811相关的外设驱动文件  
<2>、BLE文件夹存放OTA升级相关文件  
<3>、Lib文件夹存放协议栈lib、软件定时器lib、触摸lib  
<4>、SYD8811_ble_peripheral文件夹存放8811 BLE相关例程（透传、HID）  
<5>、SYD8811_peripheral文件夹存放8811外设相关例程（ADC、PWM、IIC、TIMER、RTC等）  
2、更新协议栈lib    "SYD8811_SDK\Source Code\Lib\syd8811_ble_lib.lib"    
3、按照规定格式，整理SYD8811_ble_peripheral文件夹和SYD8811_peripheral文件夹的各个工程  
4、更新Documentation文件下8811手册  
<1>、《SYD8811_BLE_DS_v1p1_CN_20190508》  
<2>、《SYD8811_BLE_DS_v1p2_EN_20190508》  
5、更新tool文件夹下SYDTEK Studio tool  
<1>、《SYDTEK Studio release20190521》  
6.更新《SYD8811_SDK\Source Code\SYD8811_peripheral》目录下各工程头文件引索目录，比如ADC工程中把“..\adc”改成“..\”  
7.修改《SYD8811_SDK\Source Code\SYD8811_peripheral》目录下各工程的《config.h》文件，增加“#define _DEBUG_”一句话，使用宏“_DEBUG_”让工程往UART输出log  
8.删除《SYD8811_SDK\Source Code\Include\syd_type.h》文件以及各个工程对其的引用  
9.增加文件："SYD8811_SDK\Documentation\SYD8811_pinmux_table_20190527.xlsx"，对SYD8811的pinmux进行介绍   
<br/><br/><br/>

2019-6-10   
修改《SYDTEK Studio  release20190610v3.5.0 》  
1.这里务必使用最新的tool，原来的tool可能会出现意想不到的情况！  
2.增加文章"SYD8811_SDK release\Documentation\SYD8811内存和代码的分布.pdf"  
3.修改了所有带BLE的工程的“profile”文件夹，在OTA的服务中增加上“write without Rspone"属性  
4.增加工程《SPI_Master_FLASH_limiting_speed》  
5.增加工程《uart1_debug》  
6.增加工程《4.SYD8811_BLE_UART_GPIO_open_power》  
7.增加工程《5.SYD8811_BLE_UART_EVBOLED_Scan》  
8.修改Hpwm的驱动，主要体现在：HPWM_IRQHandler和Hpwm_Init函数！       
<br/><br/><br/>

2019-7-5  
1.增加工程《SYD8811_SDK\SourceCode\SYD8811_peripheral_misc\SYD8811_BLE_UART_EVBOLED_notifyen_open_power_XTAL》  
2.修改RTT的驱动，使其能够输出浮点函数，替换         
3.使用最新版本的《SYDTEK Studio》，版本号为《V3.8.9 20190628.7z》  
4.增加工程《SYD8811_SDK\Source Code\SYD8811_peripheral_misc\CLK_XO16_To_Gpio》  
<br/><br/><br/>

2019-7-15  
1.增加工程《"SYD8811_SDK\Source Code\SYD8811_peripheral_misc\flash_internal_custom_3k"》  
2.增加工程《"SYD8811_SDK\Source Code\SYD8811_peripheral_misc\flash_internal_custom_Anysize"》  
3.把涉及到BLE的项目使用timer0改为使用timer1，因为软件定时器系统也使用timer0，涉及到的项目有：  
A.SYD8811_SDK\Source Code\SYD8811_ble_peripheral\1.SYD8811_BLE_UART_notifyen_open_power  
B.SYD8811_SDK\Source Code\SYD8811_ble_peripheral\3.SYD8811_BLE_UART_EVBOLED_notifyen_open_power  
C.SYD8811_SDK\Source Code\SYD8811_ble_peripheral\4.SYD8811_BLE_UART_GPIO_open_power  
E.SYD8811_SDK\Source Code\SYD8811_ble_peripheral\5.SYD8811_BLE_UART_EVBOLED_Scan  
F.SYD8811_SDK\Source Code\SYD8811_peripheral_misc\SYD8811_BLE_UART_EVBOLED_MAC  
G.SYD8811_SDK\SourceCode\SYD8811_peripheral_misc\SYD8811_BLE_UART_EVBOLED_notifyen_open_power_verdor_datas  
H.SYD8811_SDK\SourceCode\SYD8811_peripheral_misc\SYD8811_BLE_UART_EVBOLED_notifyen_open_power_XTAL  
I.SYD8811_SDK\Source Code\SYD8811_peripheral_misc\SYD8811_BLE_UART_LowPower  
J.SYD8811_SDK\SourceCode\SYD8811_peripheral_misc\SYD8811_BLE_UART_notifyen_open_power_restartadv   
修改在send_to_master和timer_1_callback两个函数中
<br/><br/><br/>

20190729  
1.修改RTT驱动，让keil显示实际使用的内存，涉及到所有使用RTT的程序,修改的文件是"Source Code\Rtt\SEGGER_RTT.C""和"\Source Code\RTT\SEGGER_RTT_Conf.h"  
2.更新最新版本的“SYDTEK_Studio”，版本号为V4.2.2  
<br/><br/><br/>

20190812  
1.增加工程《"SYD8811_SDK\Source Code\SYD8811_ble_peripheral\6.SYD8811_ANCS"》    
2.增加工程《"SYD8811_SDK\Source Code\SYD8811_peripheral_misc\SYD8811_UART_OTA"》    
3.修改工程《“SYD8811_SDK\Source Code\SYD8811_ble_peripheral\2.SYD8811_HID”》  
<br/><br/><br/>



20190828 172839
1.增加工程《"SYD8811_SDK\Source Code\SYD8811_peripheral_misc\SYD8811_dtm_tx"》    
2.增加工程《"SYD8811_SDK\Source Code\SYD8811_peripheral_misc\SYD8811_dtm_rx"》  
3.修改RTC驱动Syd8811_softtimer_lib.lib   
4.SYDTEK Studio更新到V4.4.8版本<SYDTEK Studio  release V4.4.8 20190828 173034>   
<br/><br/><br/>




20190918 164058  
1.增加工程《"SYD8811_SDK\Source Code\SYD8811_peripheral\GPIO_IRQ"》    
2.增加文件《SYD8810_pinmux_table_20190917 144554》    
3.在“Documentation”目录中增加SYD8810规格书并且更新SYD8811规格书    
4.更新"tool"目录下，SYDTEK Studio版本到V4.6.2    
5.增加工程“Source Code\SYD8811_peripheral_misc\flash peotect”    
6.增加工程“flash_internal_custom_CodeB”    
7.更新插件“SYD8811_512kB_Flash.FLM”    

20191011 202207  
1.更新"tool"目录下，SYDTEK Studio版本到V4.9.5    
2.更新插件“SYD8811_512kB_Flash.FLM”    
3.增加工程“Source Code\SYD8811_peripheral_misc\SYD8811_dtm_tx_adjust_power”    
4.更新协议栈lib为“syd8811_ble_lib20191025.lib”  
5.增加工程“Source Code\SYD8811_peripheral_misc\SYD8811_BLE_UART_OTA_FLASHDATA”  
6.更新协议栈lib为“syd8811_ble_lib20191113.lib”  
7.增加工程“Source Code\SYD8811_peripheral_misc\SYD8811_BLE_UART_BLE_Duplex  
<br/><br/><br/>


20191120 163458  
1.更新协议栈lib为“syd8811_ble_lib20191115.lib”    
2.修改各个带蓝牙OTA的工程，在睡眠前加上“if( ota_state == 1)  ota_manage();     //OTA擦除命令到来，马上擦除”    
3.更新协议栈lib为“syd881120191122.lib”    
4.增加工程“Source Code\SYD8811_peripheral_misc\SYD8811_BLE_UART_OTA_FLASHDATA_size”  
5.syd8811_ble_lib20191128.lib”    
6.更新HID例程的Profilem,请看“\Source Code\SYD8811_ble_peripheral\2.SYD8811_HID”    
7.增加工程“Source Code\SYD8811_peripheral_misc\adc_VBAT”并且更新gpadc.c文件，使之能够计算出VBAT    
<br/><br/><br/>




20191209 145405
1.更新协议栈lib为“syd8811_ble_lib20191209.lib”        
2.修改ADC校准方式，涉及工程为“SYD8811_SDK\Source Code\SYD8811_peripheral\adc”和“SYD8811_SDK\Source Code\SYD8811_peripheral_misc\adc_VBAT”        
3.增加工程“SYD8811_SDK\Source Code\SYD8811_peripheral_misc\SYD8811_BLE_UART_notifyen_open_power_RSSI”        
4.增加工程“SYD8811_SDK\Source Code\SYD8811_peripheral_misc\SYD8811_HID_Music_play”        
5.修改OTA.C文件，在ota_cmd函数中的“if(((int)p_cmd % 4)!=0)”及其else分子中把“if(ota_state==2)”条件改为“if((ota_state==2) || (ota_state==1))”，“if(ota_state==8)”条件改为“if((ota_state==8) || (ota_state==7))”，本次修改涉及到SDK中所有带有OTA功能的工程！        
6.更新"tool"目录下，SYDTEK Studio版本到V4.9.8 20191213 145803    
7.增加工程“SYD8811_SDK\Source Code\SYD8811_peripheral_misc\GPIO_Speed  
8.更新文件“"Documentation\SYD8810_pinmux_table_20191225 144444.xlsx"”  
9.增加工程“SYD8811_SDK\Source Code\SYD8811_peripheral_misc\SYD8811_BLE_calender”  
10.更新"tool"目录下，SYDTEK Studio版本到SYDTEK Studio  release v5.0.1 20191227 224019    
11.更新协议栈lib为“syd8811_ble_lib20200110 182231.lib”        
12.增加工程“SYD8811_SDK\Source Code\SYD8811_peripheral_misc\SYD8811_BLE_mixture_banding  
13.更新"tool"目录下，SYDTEK Studio版本到SYDTEK Studio  release V5.2.0 20200110 145356    
14.更新"tool"目录下，SYD Service Utility版本到SYD Service Utility release V2.2 20200110 102733    
<br/><br/><br/>



20200114 155843
1.更新文件“SYD8810_pinmux_table_20200114 155902”、“SYD8811_pinmux_table_20200114 155924.xlsx”            
2.增加工程“\Source Code\SYD8811_peripheral_misc\SYD8811_BLE_Reset_at_Gpio21”  
3.在“Documentation”目录增加文件：SYD_8811_BLE_Library.pdf，SYD8811_Register_Discription_V1.xls    
4.更新文档“SYD8811_pinmux_table.xlsx”和“SYD8810_pinmux_table.xlsx”   
5.修改“lib.h”中的“SYSTEM_CLOCK_16M_XOSC”为“SYSTEM_CLOCK_32M_XOSC”   
6.增加文件“SYD8810 透传硬件资料(layout未完成)20200304 104323.7z”和SYD8811 透传硬件资料20191106 164501.7z  
<br/><br/><br/>




20200305 201724
修改BLE工程中关于使用32.768KHz外部晶振的gpio管脚配置的bug，涉及到所有带BLE功能的工程，修改全部在gpio_init函数中，修改方式如下  
#ifndef USER_32K_CLOCK_RCOSC   
case GPIO_0:   
case GPIO_1:   
break;    
#endif    
<br/><br/><br/>




20200307 182645
1.增加工程：Source Code\SYD8811_peripheral_misc\HPWM_Complementary_Output,实现高速PWM的互补和死区输出！并且去掉Hpwm_Init函数重得语句：NVIC_EnableIRQ(HPWM_IRQn)，原因如下 安装原来的驱动方式，会在HPWM_IRQHandler中断函数中动态修改占空比，这样不方便测试的时候看结果，这里把中断关闭后，显示的波形就是代码设置的波形  
2.增加工程：Source Code\SYD8811_peripheral_misc\SYD8811_BLE_UART_TX,  
3.修改SDK中透传工程中串口的bug，bug如下：  
配置串口优先级，  
打开定时器唤醒源  
串口加上uart_0_ClrFiFo  
涉及到的工程有：  
\Source Code\SYD8811_peripheral_misc\SYD8811_BLE_UART_BLE_Duplex  
Source Code\SYD8811_ble_peripheral\1.SYD8811_BLE_UART_notifyen_open_power  
\Source Code\SYD8811_ble_peripheral\4.SYD8811_BLE_UART_GPIO_open_power  
4.增加工程：Source Code\SYD8811_peripheral_misc\SYD8811_Who_Wackup,  
5.修改文档“SYD8810_pinmux_table”和“SYD8811_pinmux_table”，把GPIO21的默认功能改成GPIO，而不是复位    
6.增加工程：Source Code\SYD8811_peripheral_misc\SYD8811_HID_Service_Change,    
7.更新协议栈lib文件，syd8811_ble_lib20200408 145619.lib  
8.增加工程：Source Code\SYD8811_peripheral_misc\SYD8811_BLE_AES,注意这个工程只有在syd8811_ble_lib20200410 075415.lib之后的lib才有用    
<br/><br/><br/>
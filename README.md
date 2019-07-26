# SYD8811SDK
SYD8811SDK  这里有SYD8811最新的SDK与更新日志，大家可以直接从这里下载与使用，如果有问题，也建议将问题发布到这里，如果我看到，会做回复的！

2018-12-26
1.第一版

2019-1-24
1.修改触摸的驱动使其有自动校正的功能！

2019-3-22
1.更新SDK中各个工程的协议栈lib文档，涉及的文件如下：
"SYD8811_SDK\Source Code\SYD8811_ble_peripheral\3.SYD8811_HID\ble\syd8811_ble_lib.lib"
"SYD8811_SDK\Source Code\ble\syd8811_ble_lib.lib"
"SYD8811_SDK\Source Code\SYD8811_ble_peripheral\1.SYD8811_UART original\ble\syd8811_ble_lib.lib"
"SYD8811_SDK\Source Code\SYD8811_ble_peripheral\1.SYD8811_UART\ble\syd8811_ble_lib.lib"
"SYD8811_SDK\Source Code\SYD8811_ble_peripheral\2.SYD8811_UART_Capdet_Touch\ble\syd8811_ble_lib.lib"


2019-5-22
1、整理Source Code工程的架构，各个文件功能说明如下
<1>、Driver、Include、Rtt存放8811相关的外设驱动文件
<2>、BLE文件夹存放OTA升级相关文件
<3>、Lib文件夹存放协议栈lib、软件定时器lib、触摸lib
<4>、SYD8811_ble_peripheral文件夹存放8811 BLE相关例程（透传、HID）
<5>、SYD8811_peripheral文件夹存放8811外设相关例程（ADC、PWM、IIC、TIMER、RTC等）

2、更新协议栈lib"SYD8811_SDK\Source Code\Lib\syd8811_ble_lib.lib"

3、按照规定格式，整理SYD8811_ble_peripheral文件夹和SYD8811_peripheral文件夹的各个工程

4、更新Documentation文件下8811手册
<1>、《SYD8811_BLE_DS_v1p1_CN_20190508》
<2>、《SYD8811_BLE_DS_v1p2_EN_20190508》

5、更新tool文件夹下SYDTEK Studio tool
<1>、《SYDTEK Studio release20190521》

2019-5-27
1.更新《SYD8811_SDK\Source Code\SYD8811_peripheral》目录下各工程头文件引索目录，比如ADC工程中把“..\adc”改成“..\”
2.修改《SYD8811_SDK\Source Code\SYD8811_peripheral》目录下各工程的《config.h》文件，增加“#define _DEBUG_”一句话，使用宏“_DEBUG_”让工程往UART输出log
3.删除《SYD8811_SDK\Source Code\Include\syd_type.h》文件以及各个工程对其的引用
4.增加文件："SYD8811_SDK\Documentation\SYD8811_pinmux_table_20190527.xlsx"，对SYD8811的pinmux进行介绍

2019-6-10 
修改《SYDTEK Studio  release20190610v3.5.0 》这里务必使用最新的tool，原来的tool可能会出现意想不到的情况！

2019-6-12  
增加文章"SYD8811_SDK release\Documentation\SYD8811内存和代码的分布.pdf"
修改了所有带BLE的工程的“profile”文件夹，在OTA的服务中增加上“write without Rspone"属性

2019-6-17  
增加工程《SPI_Master_FLASH_limiting_speed》
增加工程《uart1_debug》
增加工程《4.SYD8811_BLE_UART_GPIO_open_power》
增加工程《5.SYD8811_BLE_UART_EVBOLED_Scan》
            
            
2019-6-26   

修改Hpwm的驱动，主要体现在：HPWM_IRQHandler和Hpwm_Init函数！     

2019-7-1

1.增加工程《SYD8811_SDK\Source Code\SYD8811_peripheral_misc》
2.修改RTT的驱动，使其能够输出浮点函数，替换       

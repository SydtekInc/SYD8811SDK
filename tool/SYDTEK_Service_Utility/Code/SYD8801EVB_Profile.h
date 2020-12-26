#ifndef _BLE_PROFILE_H_
#define _BLE_PROFILE_H_

#include "ARMCM0.h"

/* Handle Index */
#define SERVICE_CHANGED_IDX 0
#define BATTERY_LEVEL_IDX 1
#define UART_NOTIFY_IDX 2
#define WECHAT_INDICATE_IDX 3

/* GENERIC_ACCESS*/
#define GENERIC_ACCESS 0x1800
#define DEVICE_NAME_UUID 0x2A00
#define DEVICE_NAME_VALUE_HANDLE 0x0003
#define APPEARANCE_UUID 0x2A01
#define APPEARANCE_VALUE_HANDLE 0x0005
#define PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_UUID 0x2A04
#define PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_VALUE_HANDLE 0x0007

/* GENERIC_ATTRIBUTE*/
#define GENERIC_ATTRIBUTE 0x1801
#define SERVICE_CHANGED_UUID 0x2A05
#define SERVICE_CHANGED_VALUE_HANDLE 0x000A

/* DEVICE_INFORMATION*/
#define DEVICE_INFORMATION 0x180A
#define MANUFACTURER_NAME_STRING_UUID 0x2A29
#define MANUFACTURER_NAME_STRING_VALUE_HANDLE 0x000E
#define MODEL_NUMBER_STRING_UUID 0x2A24
#define MODEL_NUMBER_STRING_VALUE_HANDLE 0x0010
#define SERIAL_NUMBER_STRING_UUID 0x2A25
#define SERIAL_NUMBER_STRING_VALUE_HANDLE 0x0012
#define HARDWARE_REVISION_STRING_UUID 0x2A27
#define HARDWARE_REVISION_STRING_VALUE_HANDLE 0x0014
#define FIRMWARE_REVISION_STRING_UUID 0x2A26
#define FIRMWARE_REVISION_STRING_VALUE_HANDLE 0x0016
#define SOFTWARE_REVISION_STRING_UUID 0x2A28
#define SOFTWARE_REVISION_STRING_VALUE_HANDLE 0x0018
#define PNP_ID_UUID 0x2A50
#define PNP_ID_VALUE_HANDLE 0x001A

/* BATTERY_SERVICE*/
#define BATTERY_SERVICE 0x180F
#define BATTERY_LEVEL_UUID 0x2A19
#define BATTERY_LEVEL_VALUE_HANDLE 0x001D

/* UART*/
#define UART 0x0001
#define UART_Write_UUID 0x0002
#define UART_Write_VALUE_HANDLE 0x0022
#define UART_NOTIFY_UUID 0x0003
#define UART_NOTIFY_VALUE_HANDLE 0x0024

/* WECHAT*/
#define WECHAT 0xFEE7
#define WECHAT_WRITE_UUID 0xFEC7
#define WECHAT_WRITE_VALUE_HANDLE 0x0028
#define WECHAT_INDICATE_UUID 0xFEC8
#define WECHAT_INDICATE_VALUE_HANDLE 0x002A
#define WECHAT_READ__UUID 0xFEC9
#define WECHAT_READ__VALUE_HANDLE 0x002D

/* OTA*/
#define OTA 0xFF00
#define OTA_Read_Write_UUID 0xFF01
#define OTA_Read_Write_VALUE_HANDLE 0x0030


static const uint8_t  _gatt_database_report_handle[] =
{
   0x04,
   0x01, 0x18, 0x05, 0x2A, 0x0A, 0x00, 0x0B, 0x00, 0x00, 0x00, 
   0x0F, 0x18, 0x19, 0x2A, 0x1D, 0x00, 0x1F, 0x00, 0x00, 0x00, 
   0x01, 0x00, 0x03, 0x00, 0x24, 0x00, 0x25, 0x00, 0x00, 0x00, 
   0xE7, 0xFE, 0xC8, 0xFE, 0x2A, 0x00, 0x2B, 0x00, 0x00, 0x00, 
};

static const uint8_t _gatt_database_include[] =
{
   0x0A, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
};

static const uint8_t _gatt_database_primary[] =
{
   0x09, 0x01, 0x00, 0x00, 0x28, 0x07, 0x00, 0x00, 0x18, //     0x0001  <Primary Service(0x2800)>  <GENERIC_ACCESS(0x1800)>
   0x09, 0x08, 0x00, 0x00, 0x28, 0x0B, 0x00, 0x01, 0x18, //     0x0008  <Primary Service(0x2800)>  <GENERIC_ATTRIBUTE(0x1801)>
   0x09, 0x0C, 0x00, 0x00, 0x28, 0x1A, 0x00, 0x0A, 0x18, //     0x000C  <Primary Service(0x2800)>  <DEVICE_INFORMATION(0x180A)>
   0x09, 0x1B, 0x00, 0x00, 0x28, 0x1F, 0x00, 0x0F, 0x18, //     0x001B  <Primary Service(0x2800)>  <BATTERY_SERVICE(0x180F)>
   0x09, 0x20, 0x00, 0x00, 0x28, 0x25, 0x00, 0x01, 0x00, //     0x0020  <Primary Service(0x2800)>  <UART(0x0001)>
   0x09, 0x26, 0x00, 0x00, 0x28, 0x2D, 0x00, 0xE7, 0xFE, //     0x0026  <Primary Service(0x2800)>  <WECHAT(0xFEE7)>
   0x09, 0x2E, 0x00, 0x00, 0x28, 0xFF, 0xFF, 0x00, 0xFF, //     0x002E  <Primary Service(0x2800)>  <OTA(0xFF00)>
};

static const uint8_t _gatt_database_characteristic[] =
{
   0x0A, 0x02, 0x00, 0x03, 0x28, 0x02, 0x03, 0x00, 0x00, 0x2A, //     0x0002  <Characteristic(0x2803)>  <Properties:0x02>  <Value Handle:0x0003>  <UUID:GAP.DEVICE_NAME(0x2A00)>
   0x0A, 0x04, 0x00, 0x03, 0x28, 0x02, 0x05, 0x00, 0x01, 0x2A, //     0x0004  <Characteristic(0x2803)>  <Properties:0x02>  <Value Handle:0x0005>  <UUID:GAP.APPEARANCE(0x2A01)>
   0x0A, 0x06, 0x00, 0x03, 0x28, 0x02, 0x07, 0x00, 0x04, 0x2A, //     0x0006  <Characteristic(0x2803)>  <Properties:0x02>  <Value Handle:0x0007>  <UUID:GAP.PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS(0x2A04)>
   0x0A, 0x09, 0x00, 0x03, 0x28, 0x22, 0x0A, 0x00, 0x05, 0x2A, //     0x0009  <Characteristic(0x2803)>  <Properties:0x22>  <Value Handle:0x000A>  <UUID:GATT.SERVICE_CHANGED(0x2A05)>
   0x0A, 0x0D, 0x00, 0x03, 0x28, 0x02, 0x0E, 0x00, 0x29, 0x2A, //     0x000D  <Characteristic(0x2803)>  <Properties:0x02>  <Value Handle:0x000E>  <UUID:MANUFACTURER_NAME_STRING(0x2A29)>
   0x0A, 0x0F, 0x00, 0x03, 0x28, 0x02, 0x10, 0x00, 0x24, 0x2A, //     0x000F  <Characteristic(0x2803)>  <Properties:0x02>  <Value Handle:0x0010>  <UUID:MODEL_NUMBER_STRING(0x2A24)>
   0x0A, 0x11, 0x00, 0x03, 0x28, 0x02, 0x12, 0x00, 0x25, 0x2A, //     0x0011  <Characteristic(0x2803)>  <Properties:0x02>  <Value Handle:0x0012>  <UUID:SERIAL_NUMBER_STRING(0x2A25)>
   0x0A, 0x13, 0x00, 0x03, 0x28, 0x02, 0x14, 0x00, 0x27, 0x2A, //     0x0013  <Characteristic(0x2803)>  <Properties:0x02>  <Value Handle:0x0014>  <UUID:HARDWARE_REVISION_STRING(0x2A27)>
   0x0A, 0x15, 0x00, 0x03, 0x28, 0x02, 0x16, 0x00, 0x26, 0x2A, //     0x0015  <Characteristic(0x2803)>  <Properties:0x02>  <Value Handle:0x0016>  <UUID:FIRMWARE_REVISION_STRING(0x2A26)>
   0x0A, 0x17, 0x00, 0x03, 0x28, 0x02, 0x18, 0x00, 0x28, 0x2A, //     0x0017  <Characteristic(0x2803)>  <Properties:0x02>  <Value Handle:0x0018>  <UUID:SOFTWARE_REVISION_STRING(0x2A28)>
   0x0A, 0x19, 0x00, 0x03, 0x28, 0x02, 0x1A, 0x00, 0x50, 0x2A, //     0x0019  <Characteristic(0x2803)>  <Properties:0x02>  <Value Handle:0x001A>  <UUID:PNP_ID(0x2A50)>
   0x0A, 0x1C, 0x00, 0x03, 0x28, 0x12, 0x1D, 0x00, 0x19, 0x2A, //     0x001C  <Characteristic(0x2803)>  <Properties:0x12>  <Value Handle:0x001D>  <UUID:BATTERY_LEVEL(0x2A19)>
   0x0A, 0x21, 0x00, 0x03, 0x28, 0x0A, 0x22, 0x00, 0x02, 0x00, //     0x0021  <Characteristic(0x2803)>  <Properties:0x0A>  <Value Handle:0x0022>  <UUID:UART Write(0x0002)>
   0x0A, 0x23, 0x00, 0x03, 0x28, 0x12, 0x24, 0x00, 0x03, 0x00, //     0x0023  <Characteristic(0x2803)>  <Properties:0x12>  <Value Handle:0x0024>  <UUID:UART NOTIFY(0x0003)>
   0x0A, 0x27, 0x00, 0x03, 0x28, 0x08, 0x28, 0x00, 0xC7, 0xFE, //     0x0027  <Characteristic(0x2803)>  <Properties:0x08>  <Value Handle:0x0028>  <UUID:WECHAT WRITE(0xFEC7)>
   0x0A, 0x29, 0x00, 0x03, 0x28, 0x20, 0x2A, 0x00, 0xC8, 0xFE, //     0x0029  <Characteristic(0x2803)>  <Properties:0x20>  <Value Handle:0x002A>  <UUID:WECHAT_INDICATE(0xFEC8)>
   0x0A, 0x2C, 0x00, 0x03, 0x28, 0x02, 0x2D, 0x00, 0xC9, 0xFE, //     0x002C  <Characteristic(0x2803)>  <Properties:0x02>  <Value Handle:0x002D>  <UUID:WECHAT_READ (0xFEC9)>
   0x0A, 0x2F, 0x00, 0x03, 0x28, 0x0A, 0x30, 0x00, 0x01, 0xFF, //     0x002F  <Characteristic(0x2803)>  <Properties:0x0A>  <Value Handle:0x0030>  <UUID:OTA Read Write(0xFF01)>
   0x0A, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, //     End
};

static const uint8_t _gatt_database_value[] =
{
   0x0E, 0x00, 0x03, 0x00, 0x10, 0x00, 0x2A, 0x53, 0x59, 0x44, 0x20, 0x45, 0x56, 0x42, //     0x0003    <UUID:GAP.DEVICE_NAME(0x2A00)>  <Value:Name(SYD EVB)>
   0x0C, 0x00, 0x05, 0x00, 0x10, 0x01, 0x2A, 0x30, 0x30, 0x20, 0x30, 0x30, //     0x0005    <UUID:GAP.APPEARANCE(0x2A01)>  <Value:Category(00 00)>
   0x0F, 0x00, 0x07, 0x00, 0x10, 0x04, 0x2A, 0x06, 0x00, 0x06, 0x00, 0x30, 0x00, 0x64, 0x00, //     0x0007    <UUID:GAP.PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS(0x2A04)>  <Value:Minimum Connection Interval(0x0006), Maximum Connection Interval(0x0006), Slave Latency(0x0030), Connection Supervision Timeout Multiplier(0x0064)>
   0x0B, 0x00, 0x0A, 0x00, 0x10, 0x05, 0x2A, 0x00, 0x00, 0x00, 0x00, //     0x000A    <UUID:GATT.SERVICE_CHANGED(0x2A05)>  <Value:Start of Affected Attribute Handle Range(0x0000), End of Affected Attribute Handle Range(0x0000)>
   0x09, 0x00, 0x0B, 0x00, 0x10, 0x02, 0x29, 0x00, 0x00, //     0x000B    <UUID:GATT.CLIENT_CHARACTERISTIC_CONFIGURATION(0x2902)>  <Value:(Properties(0x00 0x00))>
   0x12, 0x00, 0x0E, 0x00, 0x10, 0x29, 0x2A, 0x53, 0x59, 0x44, 0x54, 0x45, 0x4B, 0x20, 0x49, 0x6E, 0x63, 0x2E, //     0x000E    <UUID:MANUFACTURER_NAME_STRING(0x2A29)>  <Value:Manufacturer Name(SYDTEK Inc.)>
   0x0E, 0x00, 0x10, 0x00, 0x10, 0x24, 0x2A, 0x53, 0x59, 0x44, 0x38, 0x38, 0x30, 0x31, //     0x0010    <UUID:MODEL_NUMBER_STRING(0x2A24)>  <Value:Model Number(SYD8801)>
   0x0C, 0x00, 0x12, 0x00, 0x10, 0x25, 0x2A, 0x31, 0x2E, 0x30, 0x2E, 0x30, //     0x0012    <UUID:SERIAL_NUMBER_STRING(0x2A25)>  <Value:Serial Number(1.0.0)>
   0x0C, 0x00, 0x14, 0x00, 0x10, 0x27, 0x2A, 0x32, 0x2E, 0x30, 0x2E, 0x30, //     0x0014    <UUID:HARDWARE_REVISION_STRING(0x2A27)>  <Value:Hardware Revision(2.0.0)>
   0x0C, 0x00, 0x16, 0x00, 0x10, 0x26, 0x2A, 0x33, 0x2E, 0x30, 0x2E, 0x30, //     0x0016    <UUID:FIRMWARE_REVISION_STRING(0x2A26)>  <Value:Firmware Revision(3.0.0)>
   0x0C, 0x00, 0x18, 0x00, 0x10, 0x28, 0x2A, 0x34, 0x2E, 0x30, 0x2E, 0x30, //     0x0018    <UUID:SOFTWARE_REVISION_STRING(0x2A28)>  <Value:Software Revision(4.0.0)>
   0x0E, 0x00, 0x1A, 0x00, 0x10, 0x50, 0x2A, 0x02, 0x66, 0x66, 0x01, 0x00, 0x01, 0x00, //     0x001A    <UUID:PNP_ID(0x2A50)>  <Value:Vendor ID Source(0x02), Vendor ID(0x6666), Product ID(0x0001), Product Version(0x0001)>
   0x07, 0x00, 0x1D, 0x00, 0x10, 0x19, 0x2A, //     0x001D    <UUID:BATTERY_LEVEL(0x2A19)>  <Value:Level()>
   0x07, 0x00, 0x1E, 0x00, 0x10, 0x04, 0x29, //     0x001E    <UUID:GATT.CHARACTERISTIC_PRESENTATION_FORMAT(0x2904)>  <Value:(Format(), Exponent(), Unit(), Namespace(), Description())>
   0x09, 0x00, 0x1F, 0x00, 0x10, 0x02, 0x29, 0x00, 0x00, //     0x001F    <UUID:GATT.CLIENT_CHARACTERISTIC_CONFIGURATION(0x2902)>  <Value:(Properties(0x00 0x00))>
   0x1C, 0x00, 0x22, 0x00, 0x10, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //     0x0022    <UUID:UART Write(0x0002)>  <Value:Vender Define Value(0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00)>
   0x1C, 0x00, 0x24, 0x00, 0x10, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //     0x0024    <UUID:UART NOTIFY(0x0003)>  <Value:Vender Define Value(0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00)>
   0x09, 0x00, 0x25, 0x00, 0x10, 0x02, 0x29, 0x00, 0x00, //     0x0025    <UUID:CLIENT_CHARACTERISTIC_CONFIGURATION(0x2902)>  <Value:(Properties(0x00 0x00))>
   0x1C, 0x00, 0x28, 0x00, 0x10, 0xC7, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //     0x0028    <UUID:WECHAT WRITE(0xFEC7)>  <Value:Vender Define Value(0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00)>
   0x1C, 0x00, 0x2A, 0x00, 0x10, 0xC8, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //     0x002A    <UUID:WECHAT_INDICATE(0xFEC8)>  <Value:Vender Define Value(0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00)>
   0x09, 0x00, 0x2B, 0x00, 0x10, 0x02, 0x29, 0x00, 0x00, //     0x002B    <UUID:CLIENT_CHARACTERISTIC_CONFIGURATION(0x2902)>  <Value:(Properties(0x00 0x00))>
   0x1C, 0x00, 0x2D, 0x00, 0x10, 0xC9, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //     0x002D    <UUID:WECHAT_READ (0xFEC9)>  <Value:Vender Define Value(0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00)>
   0x1C, 0x00, 0x30, 0x00, 0x10, 0x01, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //     0x0030    <UUID:OTA Read Write(0xFF01)>  <Value:Vender Define Value(0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00)>
   0xFF, 0xFF, 0xFF, 0xFF, //     End
};

#endif

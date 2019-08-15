#ifndef _OTA_UART_H_
#define _OTA_UART_H_

#include "ARMCM0.h"
#include "config.h"

#define _UART_OTA_

#ifdef _UART_OTA_

#pragma pack(1)

#define UART_OTA_CMD_ERASE		0x16
#define UART_OTA_CMD_WRITE		0x17
#define UART_OTA_CMD_UPGRADE	0x18

#define UART_OTA_COMMAND_SUCCESS      0x01
#define UART_OTA_COMMAND_FAILED       0x00
#define UART_OTA_EVT_COMMAND_COMPLETE 0x0E
#define UART_OTA_CMD_COMPLETE_DATA_SZ	  2
#define UART_OTA_CMD_COMPLETE_RETURN_SZ	4

//更新程序bin数据包最大
#define UART_OTA_MAX_FW_WRITE_SZ	    128
/**********************************************************************/
struct cmd_uart_ota_erase {
	uint16_t	status;
};

struct cmd_uart_ota_write {
	uint32_t offset;
	uint16_t sz;
	uint8_t	data[UART_OTA_MAX_FW_WRITE_SZ];
};

struct cmd_uart_ota_upgrade {
	uint32_t	sz;
	uint16_t	checksum;
};

union  uart_cmd_parm {
	struct cmd_uart_ota_erase						Cmd_UART_OTA_Erase;
	struct cmd_uart_ota_write						Cmd_UART_OTA_Write;
	struct cmd_uart_ota_upgrade					Cmd_UART_OTA_Upgrade;
};

struct uart_hci_cmd {
	uint8_t	opcode;
	uint8_t	len;
	union uart_cmd_parm cmdparm;
};



struct uart_master_ota_result{
	uint8_t complete_flag;
	uint8_t data_sz;
	uint8_t cmd;
	uint8_t result;
};

struct uart_ota_fw_info{
	uint32_t fw_sz;
	uint32_t fw_check;
	uint32_t fw_offset;
	uint32_t ota_fw_send_all_num;
	uint32_t ota_fw_current_num;
	uint8_t *p_fw;
};
/**********************************************************************/




#pragma pack()

//slave
extern uint8_t uart_ota_state;       //0:未OTA 1:OTA擦除完成 2:FW写入 3:FW更新

extern void uart_slave_ota_handle(uint8_t *p_cmd, uint8_t sz);
extern void uart_send(const uint8_t * buf, uint8_t sz);//外部实现

//Master
extern uint8_t uart_master_ota_flag; //0:未OTA 1:正在OTA 2:OTA出错 3:OTA成功

extern void uart_master_ota_init(const uint8_t * p_fw, uint32_t fw_sz);
extern void uart_master_ota_start(void);
extern void uart_master_ota_handle(uint8_t *p_cmd, uint8_t sz);

#endif
#endif


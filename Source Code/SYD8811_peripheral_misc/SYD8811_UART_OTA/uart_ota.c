#include "uart_ota.h"
#include "lib.h"
#include "debug.h"
#include <string.h>
#include "delay.h"
#include "softtimer.h"
#include "DebugLog.h"


#ifdef _UART_OTA_


////////////////////////////////UART SLAVE OTA////////////////////////////////
uint8_t uart_ota_state=0; //0:未OTA 1:正在OTA擦除完成 2:FW写入 3:FW更新

static void Uart_Slave_OTA_CMD_Complete(uint8_t cmd, uint8_t result)
{
	uint8_t ret[4] = {0};
	
	ret[0] = UART_OTA_EVT_COMMAND_COMPLETE;
	ret[1] = UART_OTA_CMD_COMPLETE_DATA_SZ;
	ret[2] = cmd;
	ret[3] = result;
	
	uart_send(ret, UART_OTA_CMD_COMPLETE_RETURN_SZ);
}


static void Uart_Slave_OTA_Cmd_Erase(void)
{
	uint8_t st = 0;
	
	st = CodeErase();//成功返回1, 失败返回0
	Uart_Slave_OTA_CMD_Complete(UART_OTA_CMD_ERASE, st);
}

static void Uart_Slave_OTA_Cmd_Write(struct cmd_uart_ota_write *p_cmd)
{
	uint8_t st = 0;

	st = CodeWrite(p_cmd->offset, p_cmd->sz, p_cmd->data);
	Uart_Slave_OTA_CMD_Complete(UART_OTA_CMD_WRITE, st);
}

static void Uart_Slave_OTA_Cmd_Upgrade(struct cmd_uart_ota_upgrade *p_cmd)
{
	uint8_t st = 0;
	dbg_printf("p_cmd->sz----->0x%08x\r\n", p_cmd->sz);
	dbg_printf("p_cmd->checksum----->0x%08x\r\n", p_cmd->checksum);
	st = CodeUpdate(NULL, NULL, p_cmd->sz, p_cmd->checksum);
	Uart_Slave_OTA_CMD_Complete(UART_OTA_CMD_UPGRADE, st);
	if(st == 1)
	{
		dbg_printf("UART OTA SUCCESS, Reset MCU ing\r\n");
		delay_ms(300);
		SystemReset();
	}
	else
	{
		dbg_printf("UART OTA Failed\r\n");
	}
}

void uart_slave_ota_handle(uint8_t *p_cmd, uint8_t sz)
{
	struct uart_hci_cmd *pcmd = (struct uart_hci_cmd*)p_cmd;

	switch(pcmd->opcode)
	{	
		case UART_OTA_CMD_ERASE:
			#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
				dbg_printf("CMD_FW_ERASE\r\n");
			#endif
			Uart_Slave_OTA_Cmd_Erase();
			uart_ota_state =1; //最好放到main函数while(1)处理
			break;
		case UART_OTA_CMD_WRITE:
			#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
				dbg_printf("UART_OTA_CMD_WRITE\r\n");
			#endif
			Uart_Slave_OTA_Cmd_Write(&pcmd->cmdparm.Cmd_UART_OTA_Write);
			uart_ota_state=2;
			break;
		case UART_OTA_CMD_UPGRADE:
			#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
				dbg_printf("UART_OTA_CMD_UPGRADE\r\n");
			#endif
			Uart_Slave_OTA_Cmd_Upgrade(&pcmd->cmdparm.Cmd_UART_OTA_Upgrade);
			uart_ota_state=3;
			break;
	}
}

////////////////////////////////UART MASTER OTA////////////////////////////////
uint8_t uart_master_ota_flag = 0; //0:未OTA 1:正在OTA 2:OTA出错 3:OTA成功
struct uart_ota_fw_info ota_fw_info;

static void uart_master_ota_cmd_erase(void)
{
	struct uart_hci_cmd ota_dat = {0};
	
	ota_dat.opcode = UART_OTA_CMD_ERASE;
	ota_dat.len = sizeof(struct cmd_uart_ota_erase);
	ota_dat.cmdparm.Cmd_UART_OTA_Erase.status = 0x01;
	
	uart_send((uint8_t *)&ota_dat, ota_dat.len+2);
}



static void uart_master_ota_cmd_upgrade(void)
{
	struct uart_hci_cmd ota_dat = {0};

	ota_dat.opcode = UART_OTA_CMD_UPGRADE;
	ota_dat.len = sizeof(struct cmd_uart_ota_write);
	ota_dat.cmdparm.Cmd_UART_OTA_Upgrade.sz = ota_fw_info.fw_sz;
	ota_dat.cmdparm.Cmd_UART_OTA_Upgrade.checksum = ota_fw_info.fw_check;
	
//	dbg_printf("ota_fw_current_num----->%d\r\n", ota_fw_current_num);
//	dbg_printf("fw_check----->0x%08x\r\n", fw_check);
//	dbg_printf("fw_sz----->0x%08x\r\n", fw_sz);	
//	dbg_hexdump("upgrade:\r\n", (uint8_t *)&ota_dat,0x08);
	
	uart_send((uint8_t *)&ota_dat, ota_dat.len+2);
}




static void uart_master_ota_cmd_write(void)
{
	struct uart_hci_cmd ota_dat = {0};
	
	uint16_t one_packet_fw_sz = UART_OTA_MAX_FW_WRITE_SZ;
	
	ota_dat.opcode = UART_OTA_CMD_WRITE;
	
//	dbg_printf("\r\n----->%s\r\n", __FUNCTION__);
//	dbg_printf("----->%d\r\n", ota_fw_info.ota_fw_current_num);
//	dbg_printf("----->%d\r\n", ota_fw_info.ota_fw_send_all_num);
	
	if(ota_fw_info.ota_fw_current_num < ota_fw_info.ota_fw_send_all_num)
	{
		ota_fw_info.fw_offset = ota_fw_info.ota_fw_current_num*UART_OTA_MAX_FW_WRITE_SZ;
		
		if(ota_fw_info.ota_fw_current_num == (ota_fw_info.ota_fw_send_all_num - 1))//最后一包
		{
			//长度
			one_packet_fw_sz= ota_fw_info.fw_sz%UART_OTA_MAX_FW_WRITE_SZ;
			
			ota_dat.cmdparm.Cmd_UART_OTA_Write.offset = ota_fw_info.fw_offset;
			ota_dat.cmdparm.Cmd_UART_OTA_Write.sz = one_packet_fw_sz;
			ota_dat.len = 0x06 + ota_dat.cmdparm.Cmd_UART_OTA_Write.sz;
			memcpy((uint8_t *)ota_dat.cmdparm.Cmd_UART_OTA_Write.data, ota_fw_info.p_fw+ota_fw_info.fw_offset, ota_dat.cmdparm.Cmd_UART_OTA_Write.sz);
		}
		else
		{
			ota_dat.cmdparm.Cmd_UART_OTA_Write.offset = ota_fw_info.fw_offset;
			ota_dat.cmdparm.Cmd_UART_OTA_Write.sz = one_packet_fw_sz;
			ota_dat.len = 0x06 + ota_dat.cmdparm.Cmd_UART_OTA_Write.sz;
			memcpy((uint8_t *)ota_dat.cmdparm.Cmd_UART_OTA_Write.data, ota_fw_info.p_fw+ota_fw_info.fw_offset, ota_dat.cmdparm.Cmd_UART_OTA_Write.sz);
			
		}
//		dbg_hexdump("uart master tx data\r\n", (uint8_t *)&ota_dat, ota_dat.len +2);
		uart_send((uint8_t *)&ota_dat, ota_dat.len +2);

	}
	else if(ota_fw_info.ota_fw_current_num == ota_fw_info.ota_fw_send_all_num)//发送完,发送更新命令
	{
		uart_master_ota_cmd_upgrade();
	}	
}



void uart_master_ota_init(const uint8_t * p_fw, uint32_t fw_sz)
{
	uint32_t i = 0;
	
	uart_master_ota_flag = 0;
	memset(&ota_fw_info, 0x00, sizeof(ota_fw_info));

	ota_fw_info.p_fw=(void*)p_fw;
	ota_fw_info.fw_sz = fw_sz;
	
	for(i=0; i<fw_sz; i++){
		ota_fw_info.fw_check += p_fw[i];
	}
	
	ota_fw_info.ota_fw_send_all_num = fw_sz/UART_OTA_MAX_FW_WRITE_SZ;
	
	if(fw_sz%UART_OTA_MAX_FW_WRITE_SZ){
		ota_fw_info.ota_fw_send_all_num += 1;
	}
//	dbg_printf("ota_fw_current_num----->%d\r\n", ota_fw_info.ota_fw_current_num);
//	dbg_printf("ota_fw_send_all_num----->%d\r\n", ota_fw_info.ota_fw_send_all_num);
//	dbg_printf("fw_check----->0x%08x\r\n", ota_fw_info.fw_check);
//	dbg_printf("fw_offset----->0x%08x\r\n", ota_fw_info.fw_offset);
//	dbg_printf("fw_sz----->0x%08x\r\n", ota_fw_info.fw_sz);
}

void uart_master_ota_start(void)
{
	if(uart_master_ota_flag == 0)
	{
		uart_master_ota_cmd_erase();
		uart_master_ota_flag = 1;
	}
}

void uart_master_ota_handle(uint8_t *p_cmd, uint8_t sz)
{
	struct uart_master_ota_result *pcmd = (struct uart_master_ota_result*)p_cmd;
	
	if(pcmd->complete_flag == UART_OTA_EVT_COMMAND_COMPLETE)
	{
		switch(pcmd->cmd)
		{	
			case UART_OTA_CMD_ERASE:
			{
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
					dbg_printf("CMD_FW_ERASE RETURN\r\n");
				#endif
				if(pcmd->result == UART_OTA_COMMAND_SUCCESS)
				{
					#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
						dbg_printf("CMD_FW_ERASE success\r\n");
					#endif
					//第一包FW
					uart_master_ota_cmd_write();
				}
				else
				{
					#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
						dbg_printf("CMD_FW_ERASE failed\r\n");
					#endif
					uart_master_ota_flag = 2;
				}
			}
			break;
				
			case UART_OTA_CMD_WRITE:
			{
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
					dbg_printf("UART_OTA_CMD_WRITE RETURN\r\n");
				#endif
				if(pcmd->result == UART_OTA_COMMAND_SUCCESS)
				{
					#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
						dbg_printf("UART_OTA_CMD_WRITE success\r\n");
					#endif
					ota_fw_info.ota_fw_current_num ++;
				}
				else
				{
					#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
						dbg_printf("UART_OTA_CMD_WRITE failed\r\n");
					#endif
				}
				uart_master_ota_cmd_write();
			}
			break;

			case UART_OTA_CMD_UPGRADE:
			{
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
					dbg_printf("UART_OTA_CMD_UPGRADE RETURN\r\n");
				#endif
				if(pcmd->result == UART_OTA_COMMAND_SUCCESS)
				{
					#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
						dbg_printf("UART_OTA_CMD_UPGRADE success\r\n");
					#endif
					uart_master_ota_flag = 3;
				}
				else
				{
					#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
						dbg_printf("UART_OTA_CMD_UPGRADE failed\r\n");
					#endif
					uart_master_ota_flag = 2;
				}
			}
			break;				
		}	
	}
}

#endif


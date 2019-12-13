#include "ota.h"
#include "lib.h"
#include "debug.h"
#include <string.h>
#include "delay.h"
#include "softtimer.h"
#include "DebugLog.h"
#ifdef _OTA_

uint8_t ota_state=0;
uint8_t ota_writecnt=0;
uint16_t ota_section_size=0,ota_receive_size=0,ota_section_check=0,ota_receive_check=0;
uint32_t ota_section_offset=0;

static uint8_t EvtBuf[sizeof(struct hci_evt)];
struct hci_evt *pevt = (struct hci_evt *)EvtBuf;
__align(4) struct ota_write_info ota_w;
#define p_flash_stack  ((uint8_t *) 0x2000074a)

static void EvtCommandComplete(uint8_t opcode, uint8_t *ret_parm, uint8_t ret_len)
{
	pevt->evtcode = EVT_COMMAND_COMPLETE;
	pevt->evtlen = ret_len + CMD_COMPLETE_HDR_SZ;
	
	pevt->evtparm.EvtCommandComplete.opcode= opcode;

	memcpy((uint8_t *)&pevt->evtparm.EvtCommandComplete.RetParm, ret_parm, ret_len);
}

void CmdFwErase(void)
{
	struct ret_fw_erase_cmd	Ret;

//	DBGPRINTF(("CmdFwErase\r\n"));

	CodeErase();

	Ret.status = ERR_COMMAND_SUCCESS;
	
	EvtCommandComplete(CMD_FW_ERASE, (uint8_t *)&Ret, sizeof (Ret));
}

static void Cmd4KSETTINGWrite(struct cmd_fw_write *p_cmd)
{
	struct ret_fw_erase_cmd	Ret;

	if(p_cmd->offset>4096) return;
	if((p_cmd->offset+p_cmd->sz)>4096) p_cmd->sz=4096-p_cmd->offset;
	
	memcpy(p_flash_stack+p_cmd->offset,p_cmd->data,p_cmd->sz);
	
	DBGPRINTF("cmd4KSETTINGWrite %x %x\r\n",p_cmd->offset,p_cmd->sz);

	Ret.status = ERR_COMMAND_SUCCESS;
	
	EvtCommandComplete(CMD_FW_WRITE, (uint8_t *)&Ret, sizeof (Ret));
}

static void CmdFwWriteStart(uint8_t status,uint16_t sz,uint16_t checksum)
{
	struct ret_fw_write_start_cmd	Ret;
	Ret.sz=sz;
	Ret.checksum=checksum;
	Ret.status=status;
	
	EvtCommandComplete(CMD_FW_WRITE_START, (uint8_t *)&Ret, sizeof (Ret));
}

static void Cmd4KSETTINGUpgrade(struct cmd_4ksetting_upgrade *p_cmd)
{
	struct ret_fw_erase_cmd	Ret;
	
	uint8_t temp = 0;
	temp = Setting4kUpdate(p_flash_stack,p_cmd->checksum,p_cmd->Xor);
	#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
	DBGPRINTF("CodeUpdate=%d %x %x\r\n", temp,p_cmd->checksum,p_cmd->Xor);
	#endif
	
	if(temp==0)
		Ret.status = ERR_COMMAND_FAILED;
	else 
	{
		Ret.status = ERR_COMMAND_SUCCESS;
	}
	
	EvtCommandComplete(CMD_FW_UPGRADE, (uint8_t *)&Ret, sizeof (Ret));

}

static void CmdFwUpgradev20(struct cmd_fw_upgrade_V20 *p_cmd)
{
	struct ret_fw_erase_cmd	Ret;
	uint8_t temp = 0;

	if(ota_w.idx != 0)
		CodeWrite(ota_w.cnt*32, ota_w.idx, ota_w.buf);
	
	#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
	DBGPRINTF("ota sz:%x checksum:%x ",p_cmd->sz,p_cmd->checksum);
	#endif
	temp = CodeUpdate(NULL, NULL, p_cmd->sz, p_cmd->checksum);
	#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
	DBGPRINTF("CodeUpdatev20=%d\r\n", temp);
	#endif

	if(temp==0)
		Ret.status = ERR_COMMAND_FAILED;
	else 
		Ret.status = ERR_COMMAND_SUCCESS;
	
	EvtCommandComplete(CMD_FW_UPGRADE, (uint8_t *)&Ret, sizeof (Ret));
}

static void CmdFlashdataUpgradev30(struct cmd_fw_upgrade_V20 *p_cmd)
{
	struct ret_fw_erase_cmd	Ret;
	uint8_t temp = 0;
	
	#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
	DBGPRINTF("ota sz:%x checksum:%x ",p_cmd->sz,p_cmd->checksum);
	#endif
	temp = FlashDataUpdate(p_cmd->sz, p_cmd->checksum);
	#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
	DBGPRINTF("CodeUpdatev30=%d\r\n", temp);
	#endif

	if(temp==0)
		Ret.status = ERR_COMMAND_FAILED;
	else 
		Ret.status = ERR_COMMAND_SUCCESS;
	
	EvtCommandComplete(CMD_FW_UPGRADE, (uint8_t *)&Ret, sizeof (Ret));
}

void ota_cmd(uint8_t *p_cmd, uint8_t sz)
{
	struct hci_cmd *pcmd = (struct hci_cmd*)p_cmd;
	if((ota_section_size==0) || (ota_state==0))
	{
		switch(pcmd->opcode)
		{	
			case CMD_FW_ERASE:
				BLSetConnectionUpdate(0);  //ota
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
					dbg_printf("CMD_FW_ERASE\r\n");
				#endif
				//CmdFwErase();//最好放到main函数while(1)处理
				Timer_Evt_Start(EVT_1S_OTA);
				ota_state=1;
				ota_section_offset=0;
				break;
			case CMD_4KSETTING_ERASE:
				BLSetConnectionUpdate(0);  //ota
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
					dbg_printf("4KSETTING_ERASE \r\n");
				#endif
			    ota_state=4;
				ota_section_offset=0;
				break;
			case CMD_4KSETTING_WRITE:
				Cmd4KSETTINGWrite(&pcmd->cmdparm.CmdFwWrite);
				ota_state=5;
				break;
			case CMD_4KSETTING_UPGRADE:
				Cmd4KSETTINGUpgrade(&pcmd->cmdparm.Cmd4ksettingUpgrade);
				ota_state=6;
				break;
			case CMD_FW_UPGRADEV20:
				CmdFwUpgradev20(&pcmd->cmdparm.CmdFwUpgradeV20);
				ota_state=3;
				break;
			case CMD_FW_WRITE_START:
				ota_section_size=pcmd->cmdparm.CmdFwWriteStart.sz;
				ota_section_check=pcmd->cmdparm.CmdFwWriteStart.checksum;
				ota_section_offset=pcmd->cmdparm.CmdFwWriteStart.offset;
				ota_receive_size=0;
				ota_receive_check=0;
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
				dbg_printf("CMD_FW_WRITE_START offset:%x,size:%x checksum:%x\r\n",pcmd->cmdparm.CmdFwWriteStart.offset,ota_section_size,pcmd->cmdparm.CmdFwWriteStart.checksum);
				#endif
				break;
			case CMD_FLASHDATA_ERASE:
				BLSetConnectionUpdate(0);  //ota
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
					dbg_printf("FLASHDATA_ERASE \r\n");
				#endif
				//EraseFlashData(0, 30);  //假设FLASHDATA区域大小为120KB扇区数目为120KB/4KB=30  这里擦除需要比较长的时间，所以APP那端要延时一下
				Timer_Evt_Start(EVT_1S_OTA);
			    ota_state=7;
				ota_section_offset=0;
				break;
			case CMD_FLASHDATA_START:
				ota_section_size=pcmd->cmdparm.CmdFwWriteStart.sz;
				ota_section_check=pcmd->cmdparm.CmdFwWriteStart.checksum;
				ota_section_offset=pcmd->cmdparm.CmdFwWriteStart.offset;
				ota_receive_size=0;
				ota_receive_check=0;
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
				dbg_printf("FLASHDATA_WRITE_START offset:%x,size:%x checksum:%x\r\n",pcmd->cmdparm.CmdFwWriteStart.offset,ota_section_size,pcmd->cmdparm.CmdFwWriteStart.checksum);
				#endif
				break;
			case CMD_FLASHDATA_UPGRADEV30:
				CmdFlashdataUpgradev30(&pcmd->cmdparm.CmdFwUpgradeV20);
				ota_state=3;
				break;
		}
	}
	else
	{
		uint16_t idx;
		ota_writecnt =0;
		
		for(idx=0;idx < sz ; idx++)
			ota_receive_check += p_cmd[idx];
		
		if(((int)p_cmd % 4)!=0)
		{
			memcpy(ota_w.buf,p_cmd,sz);
			if((ota_state==2) || (ota_state==1))
			{
				idx=CodeWrite(ota_section_offset+ota_receive_size, sz, ota_w.buf);
//				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
//				dbg_printf("CodeWrite noalign:%x %x",ota_section_offset+ota_receive_size,idx);
//				#endif
			}
			else if((ota_state==8)  || (ota_state==7))
			{
				WriteFlashData(ota_section_offset+ota_receive_size, sz, ota_w.buf);
//				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
//				dbg_printf("FlashData noalign  ");
//				#endif
			}

		}
		else
		{
			if((ota_state==2) || (ota_state==1))
			{
				idx=CodeWrite(ota_section_offset+ota_receive_size, sz, p_cmd);
//				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
//				dbg_printf("CodeWrite align:%x %x",ota_section_offset+ota_receive_size,idx);
//				#endif
			}
			else if((ota_state==8)  || (ota_state==7))
			{
				WriteFlashData(ota_section_offset+ota_receive_size, sz, p_cmd);
//				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
//				dbg_printf("FlashData align  ");
//				#endif
			}

		}
		
//		#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
//		dbg_printf("section_offset:%x receive_size:%x section_size:%x\r\n",ota_section_offset,ota_receive_size,ota_section_size);
//		#endif

		ota_receive_size +=sz;
		if(ota_receive_size>=ota_section_size)
		{
			if(ota_receive_check==ota_section_check)
			{
				CmdFwWriteStart(ERR_COMMAND_SUCCESS,ota_receive_size,ota_receive_check);
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
				dbg_printf("section OK! ");
				#endif
			}
			else
			{
				CmdFwWriteStart(ERR_COMMAND_FAILED,ota_receive_size,ota_receive_check);
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
				dbg_printf("section faile! ");
				#endif
			}
			#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
			dbg_printf("ota_receive_check:%x ota_section_check:%x\r\n",ota_receive_check,ota_section_check);
			#endif
			
			ota_variable_clear(false);
		}
	}
}

void ota_variable_clear(uint8_t all)
{
	if(all)
	{
		ota_state=0;
		ota_writecnt=0;
	}
	ota_section_size=0;
	ota_section_check=0;
	ota_receive_size=0;
	ota_receive_check=0;
	ota_section_offset=0;
}

void ota_rsp(uint8_t *p_rsp, uint8_t *p_sz)
{
	memcpy(p_rsp, EvtBuf,  pevt->evtlen + 2);

	*p_sz = pevt->evtlen + 2;		
	
	memset(EvtBuf,0,sizeof(EvtBuf));
}
#endif


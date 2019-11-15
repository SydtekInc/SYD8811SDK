#ifndef _OTA_H_
#define _OTA_H_

#include "ARMCM0.h"
#include "config.h"

#define _OTA_
#ifdef _OTA_

#pragma pack(1)

#define CMD_4KSETTING_ERASE		0x11
#define CMD_4KSETTING_WRITE		0x12
#define CMD_4KSETTING_UPGRADE	0x13
#define CMD_FW_WRITE_START		0x14
#define CMD_FW_UPGRADEV20		   0x15
#define CMD_FW_ERASE		0x16
#define CMD_FW_WRITE		0x17
#define CMD_FW_UPGRADE	0x18
#define CMD_FLASHDATA_ERASE		0x20
#define CMD_FLASHDATA_WRITE		0x21
#define CMD_FLASHDATA_UPGRADE	0x22
#define CMD_FLASHDATA_START		0x23
#define CMD_FLASHDATA_UPGRADEV30		   0x24

#define ERR_COMMAND_SUCCESS           0x00
#define ERR_COMMAND_FAILED           0x01
#define EVT_COMMAND_COMPLETE		(0x0E)
#define CMD_COMPLETE_HDR_SZ		1
#define MAX_FW_WRITE_SZ			15

struct ret_fw_erase_cmd {
	uint8_t 	status;
};

struct cmd_fw_write {
	uint16_t	offset;
	uint8_t	sz;
	uint8_t	data[MAX_FW_WRITE_SZ];
};


struct cmd_fw_write_start {
	uint32_t	offset;
	uint16_t	sz;
	uint16_t	checksum;
};

struct ret_fw_write_cmd {
	uint8_t 	status;
};

struct ret_fw_write_start_cmd {
	uint8_t 	status;
	uint16_t	sz;
	uint16_t	checksum;
};

struct cmd_fw_upgrade {
	uint16_t	sz;
	uint16_t	checksum;
};

struct cmd_4ksetting_upgrade {
	uint8_t	Xor;
	uint32_t	checksum;
};

struct cmd_fw_upgrade_V20 {
	uint32_t	sz;
	uint16_t	checksum;
};

struct ret_fw_upgrade_cmd {
	uint8_t 	status;
};

union  cmd_parm {
	struct cmd_fw_write			CmdFwWrite;
	struct cmd_fw_upgrade		CmdFwUpgrade;
	struct cmd_fw_write_start			CmdFwWriteStart;
	struct cmd_fw_upgrade_V20			CmdFwUpgradeV20;
	struct cmd_4ksetting_upgrade			Cmd4ksettingUpgrade;
};

struct hci_cmd {
	uint8_t	opcode;
	uint8_t	len;
	union cmd_parm cmdparm;
};

union ret_parm {
	struct ret_fw_erase_cmd		RetFwEraseCmd;
	struct ret_fw_write_cmd		RetFwWriteCmd;
	struct ret_fw_upgrade_cmd		RetFwUpgradeCmd;
	struct ret_fw_write_start_cmd		RetFwWriteStartCmd;
};

struct evt_command_complete {
	uint8_t	opcode;
	union ret_parm RetParm;
};

union  evt_parm {
	struct evt_command_complete 				EvtCommandComplete;
};

struct hci_evt {
	uint8_t	evtcode;
	uint8_t	evtlen;
	union evt_parm evtparm;
};

extern uint8_t ota_state,ota_writecnt;

#pragma pack()

#pragma pack(4)
struct ota_write_info{
	uint8_t	buf[32];
	uint32_t	cnt;
	uint8_t	idx;
};
#pragma pack()

extern void ota_cmd(uint8_t *p_cmd, uint8_t sz);
extern void ota_rsp(uint8_t *p_rsp, uint8_t *p_sz);
extern void CmdFwErase(void);
extern void ota_variable_clear(uint8_t all);

#endif

#endif


#ifndef _ANCS_H_
#define _ANCS_H_

#include "lib.h"

#define ANCS_MSG_LEN		300
#define ANCS_TITLE_LEN		18
#define ANCS_APPID_LEN		30


typedef enum
{
  ACTION_ID_POSITIVE = 0,  /**< Positive action. */
  ACTION_ID_NEGATIVE       /**< Negative action. */
} ancs_action_id_values_t;

typedef struct
{
	uint8_t valid;
  uint8_t appid_len;
	uint8_t appid[ANCS_APPID_LEN];
	uint8_t title_len;
	uint8_t title[ANCS_TITLE_LEN];
	uint16_t msg_len;
	uint8_t msg[ANCS_MSG_LEN];	
	uint8_t ancs_uid[4];	
} ancs_msg_t;

extern ancs_msg_t ancs_msg;

extern void ancs_service_enable(void);
extern void clr_ancs_msg(void);
extern void ancs_service_att_data(struct attc_ble_evt *p_attc);
extern void ancs_result(uint8_t result);


extern void ancs_perform_notification_action(uint8_t *uid, ancs_action_id_values_t action_id);

#endif

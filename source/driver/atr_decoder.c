#include "atr_decoder.h"
#include "debug.h"

enum {
    T0 = 0,
    T1,
};

enum {
    TA1,
    TA2,
    TA15,
    TC1,
    TC2,
    TD1,
    // For array declaration
    TOTAL,
};

static uint8_t parsed_data[TOTAL];
static uint8_t default_fd = DEFAULT_FD;
static uint32_t parsed_bitmask;

void atr_reset(void)
{
    parsed_bitmask = 0;
}

bool atr_decode(SC_ATR *atr)
{
    int mask, i;
    int currentProtocol;
    int index;
    uint8_t TA15 = 0x07;
    
    // T0
    atr->HLength = atr->T0 & 0x0F;
    mask = atr->T0 & 0xF0;
    index = 1;
    
    while (mask != 0) 
	{
        int T[4];
		
        for (i = 0; i < 4; i++) 
		{
            if ((mask >> (i + 4)) & 0x01) 
			{
                T[i] = (int)atr->T[atr->ILength];
                atr->ILength++;
            }
            else 
			{
                T[i] = -1;
            }
        }
        
        // TA
        if (T[0] != -1) 
		{
            // TA1 - Fi, Di
            if (index == 1) 
			{
                parsed_data[TA1] = T[0] & 0xFF;
                parsed_bitmask |= (1 << TA1);
            }
            else if (index == 2) 
			{ // TA2 - PPS Mode
                parsed_data[TA2] = T[0] & 0xFF;
                parsed_bitmask |= (1 << TA2);
            }
            else if (currentProtocol == 15) 
			{
                parsed_data[TA15] = T[0] & 0xFF;
                parsed_bitmask |= (1 << TA15);
            }
        }
        
        // TB - deprecated or T = 1, do not support for now
        
        // TC
        if (T[2] != -1) 
		{
            //TC1 - Extra guard time
            if (index == 1)
            {
                parsed_data[TC1] = T[2] & 0xFF;
                parsed_bitmask |= (1 << TC1);
            }
            else if (index == 2)
            {
                parsed_data[TC2] = T[2] & 0xFF;
                parsed_bitmask |= (1 << TC2);
            }
        }
        
        // TD
        if (T[3] != -1) 
		{
            // next TD exist
            mask = T[3] & 0xF0;
            currentProtocol = T[3] & 0x0F;
            // TD1
            if (index == 1) 
			{
                parsed_data[TD1] = T[3] & 0xFF;
                parsed_bitmask |= (1 << TD1);
            }
        }
        else
        {
			mask = 0;
		}
        
        index++;
    }
    
    // TH
    atr->Th_Start = atr->ILength;
    // TCK exists
    if (atr->ILength + atr->HLength + 2 != atr->TotalLength)
    {
        uint8_t check = atr->T0;
        int i;
        
        for (i = 0; i < atr->TotalLength - 2; i++)
        {
			check ^= atr->T[i];
		}

        atr->Check = check;
    }
    
    return (bool)atr->Check;
}

uint8_t atr_decoder_get_extra_guard_time(void)
{
    if (parsed_bitmask & (1 << TC1))
        return parsed_data[TC1];
    return 0;
}

uint8_t atr_decoder_get_waiting_integer(void)
{
    uint8_t wi = 10;
    if (parsed_bitmask & (1 << TC2))
        wi = parsed_data[TC2];
    
    return wi;
}

bool atr_decoder_get_clock_stop(bool *high)
{
    bool en = false;
    
    *high = false;
    if ((parsed_bitmask & (1 << TA15)) && (parsed_data[TA15] & 0xC0)) 
	{
        en = true;
        *high = (bool)((parsed_data[TA15] & 0x80) == 0);
    }
    return en;
}

bool atr_decoder_allow_pps(void)
{
    return (bool)((parsed_bitmask & (1 << TA2)) == 0);
}

bool atr_decoder_allow_switch_mode(void)
{
    return (bool)((parsed_bitmask & (1 << TA2)) && (!(parsed_data[TA2] & 0x80))); 	//bypb add:!
}

uint8_t atr_decoder_get_protocol(void) 
{
    // specific mode
    if (parsed_bitmask & (1 << TA2)) 
	{
        return parsed_data[TA2] & 0x0F;
    }
    // first offer
    else if (parsed_bitmask & (1 << TD1)) 
	{
        return parsed_data[TD1] & 0x0F;
    }
    
    return 0;
}

uint8_t atr_decoder_get_FD(void)
{
    if (parsed_bitmask & (1 << TA1))
    {
        return parsed_data[TA1];
    }
    return default_fd;
}

void atr_decoder_config_default_FD(uint8_t fd)
{
    default_fd = fd;
}

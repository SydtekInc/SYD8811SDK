#include"crc.h"


void InvertUint8(uint8_t *dBuf,uint8_t *srcBuf)
{
    uint8_t i;
    uint8_t tmp[4];
    tmp[0] = 0;
    for(i=0;i< 8;i++)
    {
      if(srcBuf[0]& (1 << i))
        tmp[0]|=1<<(7-i);
    }
    dBuf[0] = tmp[0];
}


void InvertUint16(uint16_t *dBuf,uint16_t *srcBuf)
{
    uint8_t i;
    uint16_t tmp[4];
    tmp[0] = 0;
    for(i=0;i< 16;i++)
    {
      if(srcBuf[0]& (1 << i))
        tmp[0]|=1<<(15 - i);
    }
    dBuf[0] = tmp[0];
}



uint16_t CRC16_IBM(uint8_t *puchMsg, uint32_t usDataLen)
{
  uint16_t wCRCin = 0x0000;
  uint16_t wCPoly = 0x8005;
  uint8_t wChar = 0;
  uint8_t i;

  while (usDataLen--)
  {
        wChar = *(puchMsg++);
        InvertUint8(&wChar,&wChar);
        wCRCin ^= (wChar << 8);
        for(i = 0;i < 8;i++)
        {
          if(wCRCin & 0x8000)
            wCRCin = (wCRCin << 1) ^ wCPoly;
          else
            wCRCin = wCRCin << 1;
        }
  }
  InvertUint16(&wCRCin,&wCRCin);
  return (wCRCin) ;
}

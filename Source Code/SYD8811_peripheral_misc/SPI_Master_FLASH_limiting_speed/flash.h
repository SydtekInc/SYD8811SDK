#ifndef _SYD8801_SPI_H_
#define _SYD8801_SPI_H_

#include "ARMCM0.h" 

extern void spi_write(uint8_t *p_data,uint16_t num);
extern void spi_read(uint8_t *p_data,uint16_t num);
extern void spi_write_byte(uint8_t p_data);

//FLASH读写  ID
//#define FLASH_ID 0X684014    //BYD80A
#define FLASH_ID1 0XE04014    //BY25Q80A
#define FLASH_ID2  0x5e4014       //XTX最新flash

//指令表
#define BY25_WriteEnable		0x06 
#define BY25_WriteDisable		0x04 
#define BY25_ReadStatusReg		0x05 
#define BY25_WriteStatusReg		0x01 
#define BY25_ReadData			0x03 
#define BY25_FastReadData		0x0B 
#define BY25_FastReadDual		0x3B 
#define BY25_PageProgram		0x02 
#define BY25_BlockErase			0xD8 
#define BY25_SectorErase		0x20 
#define BY25_ChipErase			0xC7 
#define BY25_PowerDown			0xB9 
#define BY25_ReleasePowerDown	0xAB 
#define BY25_DeviceID			0xAB 
#define BY25_ManufactDeviceID	0x90 
#define BY25_JedecDeviceID		0x9F 

extern unsigned long int SPI_Flash_ReadID(void);
extern void SPI_Flash_Write(unsigned char* pBuffer,unsigned long int WriteAddr,unsigned short int NumByteToWrite);
extern void SPI_Flash_Read(unsigned char* pBuffer,unsigned long int ReadAddr,unsigned short int NumByteToRead);
extern void SPI_Flash_Erase_Sector(unsigned long int Dst_Addr);
extern void SPI_Flash_Erase(unsigned long int Dst_Addr,unsigned char num);
extern void SPI_Flash_Write_NoCheck(unsigned char* pBuffer,unsigned long int WriteAddr,unsigned short int NumByteToWrite);  
extern void SPI_FLASH_Write_Enable(void);   
extern void SPI_Flash_Write_Page(unsigned char* pBuffer,unsigned long int WriteAddr,unsigned short int NumByteToWrite);

#endif


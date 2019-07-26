/*
spi的操作文件

作者：北京盛源达科技有限公司
日期：2016/7/8
*/
#include "spi.h"
#include "flash.h"
#include "string.h"

/*******************************************************************************
* Function Name  : SPI_Flash_ReadID
* Description    : 读取SPI_FLASH即BY2516的ID号
* Input          : None
* Output         : None
* Return         : Temp：器件的ID号
* Data           : 2014/8/24
* programmer     : piaoran
* remark         ：例子 dbg_printf("FlashID:%x\r\n",SPI_Flash_ReadID());
*******************************************************************************/
unsigned long int SPI_Flash_ReadID(void)
{
	unsigned long int Temp = 0;	  	
	uint8_t rx[4]={0};
	spi_cs_enable(FLASH_SPI);
	Temp =BY25_JedecDeviceID;
	spi_write((uint8_t *)&Temp,1);
	spi_read(rx,4);
	Temp=rx[1]<<16 | rx[2]<<8 | rx[3];
	spi_cs_disable(FLASH_SPI);
	return Temp;
}  
/*******************************************************************************
* Function Name  : SPI_Flash_ReadSR
* Description    : SPI_flash读取状态函数
* Input          : None
* Output         : None
* Return         : byte：器件的状态寄存器
* Data           : 2014/8/24
* programmer     : piaoran
* remark         ：例子 SPI_FLASH_Write_Enable();
*******************************************************************************/
unsigned char SPI_Flash_ReadSR(void)   
{  
	unsigned char Temp = 0;	  	
	spi_cs_enable(FLASH_SPI);
	
	Temp =BY25_ReadStatusReg;
	spi_write(&Temp,1);
	spi_read(&Temp,1);	
	spi_cs_disable(FLASH_SPI);
	return Temp;
} 
/*******************************************************************************
* Function Name  : SPI_Flash_Wait_Busy
* Description    : 等待SPI_flash空闲函数
* Input          : None
* Output         : None
* Return         : None
* Data           : 2014/8/24
* programmer     : piaoran
* remark         ：例子 SPI_Flash_Wait_Busy();
*******************************************************************************/
void SPI_Flash_Wait_Busy(void)   
{   
	while ((SPI_Flash_ReadSR()&0x01)==0x01);   // 等待BUSY位清空
}
/*******************************************************************************
* Function Name  : SPI_FLASH_Write_Enable
* Description    : SPI_flash写使能函数
* Input          : None
* Output         : None
* Return         : None
* Data           : 2014/8/24
* programmer     : piaoran
* remark         ：例子 SPI_FLASH_Write_Enable();
*******************************************************************************/
void SPI_FLASH_Write_Enable(void)   
{	
	unsigned char Temp = 0;	  	
	spi_cs_enable(FLASH_SPI);
	
	Temp =BY25_WriteEnable;
	spi_write(&Temp,1);
	
	spi_cs_disable(FLASH_SPI);
} 
/*******************************************************************************
* Function Name  : SPI_Flash_Erase_Sector
* Description    : 擦除SPI扇区函数
* Input          : Dst_Addr：数据扇区地址
* Output         : None
* Return         : None
* Data           : 2014/8/24
* programmer     : piaoran
* remark         ：例子SPI_Flash_Erase_Sector(100);
*******************************************************************************/
void SPI_Flash_Erase_Sector(unsigned long int Dst_Addr)   
{   	
    uint8_t tx[4]={BY25_SectorErase,0xFF,0xFF,0xFF};
    SPI_FLASH_Write_Enable();                  //SET WEL 	 
	SPI_Flash_Wait_Busy();   
	tx[1]=(unsigned char)((Dst_Addr)>>16);
	tx[2]=(unsigned char)((Dst_Addr)>>8);
	tx[3]=(unsigned char)Dst_Addr;
	spi_cs_enable(FLASH_SPI);
	spi_write(tx,4);
	spi_cs_disable(FLASH_SPI);
	SPI_Flash_Wait_Busy();   				   //等待擦除完成
}  
void SPI_Flash_Erase(unsigned long int Dst_Addr,unsigned char num)   
{   	
	uint8_t i=0;
  for(i=0;i<num;i++)  SPI_Flash_Erase_Sector(Dst_Addr+i*4096);
}  
/*******************************************************************************
* Function Name  : SPI_Flash_Read
* Description    : 向BY2516读函数
* Input          : pBuffer：要读出的数组
                   WriteAddr：要读出的地址
                   NumByteToWrite：要读出多大的数据 最大为4096
* Output         : None
* Return         : None
* Data           : 2014/8/24
* programmer     : piaoran
* remark         ：例子 SPI_Flash_Read(RX_BUFF,wordaddr,32);
*******************************************************************************/
void SPI_Flash_Read(unsigned char* pBuffer,unsigned long int ReadAddr,unsigned short int NumByteToRead)   
{ 
 	unsigned short int i=0;    	
	unsigned long int secpos=0;
	unsigned short int secoff=0;
	uint8_t rx[32]={0};
	secpos=NumByteToRead/32;//扇区地址 0~511 for BY2516
	secoff=NumByteToRead%32;//在扇区内的偏移
	spi_cs_enable(FLASH_SPI);
	rx[0]=BY25_ReadData;
	rx[1]=(unsigned char)((ReadAddr)>>16);
	rx[2]=(unsigned char)((ReadAddr)>>8);
	rx[3]=(unsigned char)ReadAddr;
	spi_write(rx,4);
	for(i=0;i<secpos;i++)
	{ 
		spi_read(rx,32);
		memcpy(pBuffer+i*32,rx,32);   //循环读数
	}
	spi_read(rx,secoff);
	memcpy(&pBuffer[i*32],rx,secoff);   
	spi_cs_disable(FLASH_SPI);  	      
}  
/*******************************************************************************
* Function Name  : SPI_Flash_Write_NoCheck
* Description    : 向BY2516写页函数
* Input          : pBuffer：要写入的数组
                   WriteAddr：要写入的地址
                   NumByteToWrite：要写多大的数据 最大为4096
* Output         : None
* Return         : None
* Data           : 2014/8/24
* programmer     : piaoran
* remark         ：例子 SPI_Flash_Write_Pag(SPI_FLASH_BUF,secpos*4096,4096);
*******************************************************************************/
void SPI_Flash_Write_Page(unsigned char* pBuffer,unsigned long int WriteAddr,unsigned short int NumByteToWrite)
{	 	
 	unsigned short int i=0;    	
	unsigned long int secpos=0;
	unsigned short int secoff=0;
	uint8_t tx[32]={0};
	secpos=NumByteToWrite/32;//扇区地址 0~511 for BY2516
	secoff=NumByteToWrite%32;//在扇区内的偏移
	SPI_FLASH_Write_Enable();                  //SET WEL 
	spi_cs_enable(FLASH_SPI);
	tx[0]=BY25_PageProgram;
	tx[1]=(unsigned char)((WriteAddr)>>16);
	tx[2]=(unsigned char)((WriteAddr)>>8);
	tx[3]=(unsigned char)WriteAddr;
	spi_write(tx,4);
	for(i=0;i<secpos;i++)
	{ 
		memcpy(tx,&pBuffer[i*32],32);  
		spi_write(tx,32);
	}
	memcpy(tx,&pBuffer[i*32],secoff);  
	spi_write(tx,secoff);
	 
	spi_cs_disable(FLASH_SPI);  	      
	SPI_Flash_Wait_Busy();					   //等待写入结束
} 
/*******************************************************************************
* Function Name  : SPI_Flash_Write_NoCheck
* Description    : 向BY2516写块区函数
* Input          : pBuffer：要写入的数组
                   WriteAddr：要写入的地址
                   NumByteToWrite：要写多大的数据 最大为4096
* Output         : None
* Return         : None
* Data           : 2014/8/24
* programmer     : piaoran
* remark         ：例子 SPI_Flash_Write_NoCheck(SPI_FLASH_BUF,secpos*4096,4096);
*******************************************************************************/
void SPI_Flash_Write_NoCheck(unsigned char* pBuffer,unsigned long int WriteAddr,unsigned short int NumByteToWrite)   
{ 			 		 
	unsigned short int pageremain;	   
	pageremain=256-WriteAddr%256; //单页剩余的字节数		 	    
	if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//不大于256个字节
	while(1)
	{	   
		SPI_Flash_Write_Page(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite==pageremain)break;//写入结束了
	 	else //NumByteToWrite>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	

			NumByteToWrite-=pageremain;			  //减去已经写入了的字节数
			if(NumByteToWrite>256)pageremain=256; //一次可以写入256个字节
			else pageremain=NumByteToWrite; 	  //不够256个字节了
		}
	};	    
} 


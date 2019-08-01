/*
spi�Ĳ����ļ�

���ߣ�����ʢԴ��Ƽ����޹�˾
���ڣ�2016/7/8
*/
#include "spi.h"
#include "flash.h"
#include "string.h"

/*******************************************************************************
* Function Name  : SPI_Flash_ReadID
* Description    : ��ȡSPI_FLASH��BY2516��ID��
* Input          : None
* Output         : None
* Return         : Temp��������ID��
* Data           : 2014/8/24
* programmer     : piaoran
* remark         ������ dbg_printf("FlashID:%x\r\n",SPI_Flash_ReadID());
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
* Description    : SPI_flash��ȡ״̬����
* Input          : None
* Output         : None
* Return         : byte��������״̬�Ĵ���
* Data           : 2014/8/24
* programmer     : piaoran
* remark         ������ SPI_FLASH_Write_Enable();
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
* Description    : �ȴ�SPI_flash���к���
* Input          : None
* Output         : None
* Return         : None
* Data           : 2014/8/24
* programmer     : piaoran
* remark         ������ SPI_Flash_Wait_Busy();
*******************************************************************************/
void SPI_Flash_Wait_Busy(void)   
{   
	while ((SPI_Flash_ReadSR()&0x01)==0x01);   // �ȴ�BUSYλ���
}
/*******************************************************************************
* Function Name  : SPI_FLASH_Write_Enable
* Description    : SPI_flashдʹ�ܺ���
* Input          : None
* Output         : None
* Return         : None
* Data           : 2014/8/24
* programmer     : piaoran
* remark         ������ SPI_FLASH_Write_Enable();
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
* Description    : ����SPI��������
* Input          : Dst_Addr������������ַ
* Output         : None
* Return         : None
* Data           : 2014/8/24
* programmer     : piaoran
* remark         ������SPI_Flash_Erase_Sector(100);
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
	SPI_Flash_Wait_Busy();   				   //�ȴ��������
}  
void SPI_Flash_Erase(unsigned long int Dst_Addr,unsigned char num)   
{   	
	uint8_t i=0;
  for(i=0;i<num;i++)  SPI_Flash_Erase_Sector(Dst_Addr+i*4096);
}  
/*******************************************************************************
* Function Name  : SPI_Flash_Read
* Description    : ��BY2516������
* Input          : pBuffer��Ҫ����������
                   WriteAddr��Ҫ�����ĵ�ַ
                   NumByteToWrite��Ҫ������������ ���Ϊ4096
* Output         : None
* Return         : None
* Data           : 2014/8/24
* programmer     : piaoran
* remark         ������ SPI_Flash_Read(RX_BUFF,wordaddr,32);
*******************************************************************************/
void SPI_Flash_Read(unsigned char* pBuffer,unsigned long int ReadAddr,unsigned short int NumByteToRead)   
{ 
 	unsigned short int i=0;    	
	unsigned long int secpos=0;
	unsigned short int secoff=0;
	uint8_t rx[4]={0};
	secpos=NumByteToRead/32;//������ַ 0~511 for BY2516
	secoff=NumByteToRead%32;//�������ڵ�ƫ��
	spi_cs_enable(FLASH_SPI);
	rx[0]=BY25_ReadData;
	rx[1]=(unsigned char)((ReadAddr)>>16);
	rx[2]=(unsigned char)((ReadAddr)>>8);
	rx[3]=(unsigned char)ReadAddr;
	spi_write(rx,4);
	for(i=0;i<secpos;i++)
	{ 
		spi_read(pBuffer+i*32,32);
	}
	spi_read(&pBuffer[i*32],secoff);
	spi_cs_disable(FLASH_SPI);  	      
}  
/*******************************************************************************
* Function Name  : SPI_Flash_Write_NoCheck
* Description    : ��BY2516дҳ����
* Input          : pBuffer��Ҫд�������
                   WriteAddr��Ҫд��ĵ�ַ
                   NumByteToWrite��Ҫд�������� ���Ϊ4096
* Output         : None
* Return         : None
* Data           : 2014/8/24
* programmer     : piaoran
* remark         ������ SPI_Flash_Write_Pag(SPI_FLASH_BUF,secpos*4096,4096);
*******************************************************************************/
void SPI_Flash_Write_Page(unsigned char* pBuffer,unsigned long int WriteAddr,unsigned short int NumByteToWrite)
{	 	
 	unsigned short int i=0;    	
	unsigned long int secpos=0;
	unsigned short int secoff=0;
	uint8_t tx[4]={0};
	secpos=NumByteToWrite/32;//������ַ 0~511 for BY2516
	secoff=NumByteToWrite%32;//�������ڵ�ƫ��
	SPI_FLASH_Write_Enable();                  //SET WEL 
	spi_cs_enable(FLASH_SPI);
	tx[0]=BY25_PageProgram;
	tx[1]=(unsigned char)((WriteAddr)>>16);
	tx[2]=(unsigned char)((WriteAddr)>>8);
	tx[3]=(unsigned char)WriteAddr;
	spi_write(tx,4);
	for(i=0;i<secpos;i++)
	{ 
		spi_write(&pBuffer[i*32],32);
	}
	spi_write(&pBuffer[i*32],secoff);
	 
	spi_cs_disable(FLASH_SPI);  	      
	SPI_Flash_Wait_Busy();					   //�ȴ�д�����
} 
/*******************************************************************************
* Function Name  : SPI_Flash_Write_NoCheck
* Description    : ��BY2516д��������
* Input          : pBuffer��Ҫд�������
                   WriteAddr��Ҫд��ĵ�ַ
                   NumByteToWrite��Ҫд�������� ���Ϊ4096
* Output         : None
* Return         : None
* Data           : 2014/8/24
* programmer     : piaoran
* remark         ������ SPI_Flash_Write_NoCheck(SPI_FLASH_BUF,secpos*4096,4096);
*******************************************************************************/
void SPI_Flash_Write_NoCheck(unsigned char* pBuffer,unsigned long int WriteAddr,unsigned short int NumByteToWrite)   
{ 			 		 
	unsigned short int pageremain;	   
	pageremain=256-WriteAddr%256; //��ҳʣ����ֽ���		 	    
	if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//������256���ֽ�
	while(1)
	{	   
		SPI_Flash_Write_Page(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite==pageremain)break;//д�������
	 	else //NumByteToWrite>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	

			NumByteToWrite-=pageremain;			  //��ȥ�Ѿ�д���˵��ֽ���
			if(NumByteToWrite>256)pageremain=256; //һ�ο���д��256���ֽ�
			else pageremain=NumByteToWrite; 	  //����256���ֽ���
		}
	};	    
} 


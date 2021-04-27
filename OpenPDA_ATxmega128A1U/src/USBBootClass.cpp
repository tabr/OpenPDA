// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma  once
/*  
*  USBBootClass.cpp
*
*  Created:  01.05.2018  12:19:47
*  Author:  tabr
*/


#include  "USBBootClass.hpp"
#include "stdio.h"
/*
//  default  constructor
USBBootClass::USBBootClass()
{
}  //USBBootClass

//  default  destructor
USBBootClass::~USBBootClass()
{
}  //~USBBootClass
*/
void USBBootClass::CommandProcess(void)
  {
  switch  (this->commandProcessing)
    {
    case  COMMAND_SELECT_MEMORY:
      {
      udi_hid_generic_send_report_in(this->outgoingData);//вставить  чего,  может?!
      this->commandProcessing	=  COMMAND_NONE;
      }
    break;
    
    case  COMMAND_READ:
      {
      PORTF.OUTSET	=  1<<4;
      if  (this->selectedMemory  ==  PDAMEMORY_TWI_EEPROM)
        {
        ExternalEEPROMTWI::readFromDevice(this->addressH,  this->addressL,  USB_PAYLOAD_SIZE,  &this->outgoingData[USB_BUFFER_START_SECTION_PAYLOAD]);
        //readFromDevice(this->addressH,  this->addressL,  USB_PAYLOAD_SIZE,  &this->outgoingData[USB_BUFFER_START_SECTION_PAYLOAD]);
        //memset(&this->outgoingData[USB_BUFFER_START_SECTION_PAYLOAD],  0xAA,  USB_PAYLOAD_SIZE);
        }
      else  if  (this->selectedMemory  ==  PDAMEMORY_MEDIA_FLASH)
        {
        //M25P05_Read(this->addressH,this->addressM,this->addressL,  USB_PAYLOAD_SIZE,  &this->outgoingData[USB_BUFFER_START_SECTION_PAYLOAD]  );
        MediaMemory.ReadData(this->addressH,this->addressM,this->addressL,  &this->outgoingData[USB_BUFFER_START_SECTION_PAYLOAD],  (uint16_t)USB_PAYLOAD_SIZE);
        }
      udi_hid_generic_send_report_in(this->outgoingData);
      this->commandProcessing	=  COMMAND_NONE;
      PORTF.OUTCLR	=  1<<4;
      }
    break;
    
    case  COMMAND_WRITE:
      {
      char lcd_buf[32];
      LcdStringUpdate(1,LCD_LINE_2,(char*)"COMMAND_WRITE");
      PORTF.OUTSET	=  1<<4;
      if  (this->selectedMemory  ==  PDAMEMORY_TWI_EEPROM)
      	{
        LcdStringUpdate(1,LCD_LINE_3,(char*)"PDAMEMORY_TWI_EEPROM");
      	this->addressProcessing.value_int	=  0;
      	uint16_t  iterations			=  TWI_EEPROM_SIZE_IN_BYTES/USB_PAYLOAD_SIZE;
      	while  (iterations  >  0)
      		{
      		if  (this->isWriteBufferEmpty())
      			{
            //LcdStringUpdate(1,LCD_LINE_3,(char*)"WB empty[%03d]");
            static uint8_t asdasd=0;
            sprintf (lcd_buf,"WB empty[%03d]",++asdasd);
            LcdString(1,LCD_LINE_4);
            n3310LcdClass::RequestUpdate();
      			continue;
      			}
      		uint8_t  *pBuf	=  &this->writeBuffers[(this->writeBufferBottom * USB_PAYLOAD_SIZE)];
          //uint8_t  zzz[2]={1,2};
      		
      		for  (uint8_t  i=0;i<(USB_PAYLOAD_SIZE/TWI_EEPROM_WRITE_PAGE_SIZE);i++)
      			{
            uint8_t addr_h  = this->addressProcessing.byte_field.ml;
            uint8_t addr_l  = this->addressProcessing.byte_field.l;
            uint8_t* data   = &pBuf[(i*TWI_EEPROM_WRITE_PAGE_SIZE)];
      			ExternalEEPROMTWI::writeToDevice(addr_h,  addr_l,  (uint16_t)TWI_EEPROM_WRITE_PAGE_SIZE,  data);
            //uint16_t k=(i*TWI_EEPROM_WRITE_PAGE_SIZE);
            //for (uint8_t j=0;j<3;j++)
              //{
              //ExternalEEPROMTWI::writeToDevice(this->addressProcessing.byte_field.ml,  this->addressProcessing.byte_field.l,  1,  &pBuf[(i*TWI_EEPROM_WRITE_PAGE_SIZE)+0]);
              //ExternalEEPROMTWI::writeToDevice(this->addressProcessing.byte_field.ml,  this->addressProcessing.byte_field.l,  1,  &pBuf[(i*TWI_EEPROM_WRITE_PAGE_SIZE)+1]);
              //_delay_ms(TWI_EEPROM_WRITE_DELAY_MS);
              //}
      			//ExternalEEPROMTWI::writeToDevice(this->addressProcessing.byte_field.ml,  this->addressProcessing.byte_field.l,  1,  &pBuf[(i*TWI_EEPROM_WRITE_PAGE_SIZE)]);
            //_delay_ms(TWI_EEPROM_WRITE_DELAY_MS);
      			//ExternalEEPROMTWI::writeToDevice(0,  0,  TWI_EEPROM_WRITE_PAGE_SIZE,  pBuf);
            
            //sprintf (Lcd.lcd_buf,"%03d%03u %03d%03d",this->addressProcessing.byte_field.ml, this->addressProcessing.byte_field.l,  pBuf[(i*TWI_EEPROM_WRITE_PAGE_SIZE)],  pBuf[(i*TWI_EEPROM_WRITE_PAGE_SIZE)+1]);
            sprintf (lcd_buf,"%03d%03u %03d%03d",addr_h,  addr_l,  data[0], data[1]);
            LcdString(1,LCD_LINE_5);
            n3310LcdClass::RequestUpdate();
      			this->addressProcessing.value_int+=TWI_EEPROM_WRITE_PAGE_SIZE;
      			_delay_ms(TWI_EEPROM_WRITE_DELAY_MS);
      			}
      		iterations--;
      		this->writeBuffer_IncrementBottom();
      		}
      	udi_hid_generic_send_report_in(this->outgoingData);
      	this->commandProcessing	=  COMMAND_NONE;
      	}
      else  if  (this->selectedMemory  ==  PDAMEMORY_MEDIA_FLASH)
      	{
        LcdStringUpdate(1,LCD_LINE_3,(char*)"PDAMEMORY_MEDIA_FLASH");
      	this->addressProcessing.value_int	=  0;
      	uint16_t  iterations			=  (MEDIA_FLASH_SIZE_IN_BYTES/USB_PAYLOAD_SIZE);
        LcdStringUpdate(1,LCD_LINE_3,(char*)"Erasing...");
        MediaMemory.EraseDevice();
        //sprintf (lcd_buf,"iter:[%03d]",iterations);
        //LcdStringUpdate(1,LCD_LINE_6,lcd_buf);
        LcdStringUpdate(1,LCD_LINE_3,(char*)"Erasing done");
//        _delay_ms(1000);
      	while  (iterations  >  0)
      		{
          sprintf (lcd_buf,"iter[%05d]",iterations);
          LcdStringUpdate(1,LCD_LINE_6,lcd_buf);
      		if  (this->isWriteBufferEmpty())
      			{
            static uint8_t asdasd=0;
            sprintf (lcd_buf,"WB empty[%03d]",++asdasd);
            LcdStringUpdate(1,LCD_LINE_4,lcd_buf);
      			continue;
      			}
      		uint8_t  *pBuf	=  &this->writeBuffers[(this->writeBufferBottom  *  USB_PAYLOAD_SIZE)];
//      		uint8_t i=0;
      		for (uint8_t i=0;i<(USB_PAYLOAD_SIZE/MEDIA_FLASH_WRITE_PAGE_SIZE);i++)
      			{
      			//M25P05_Write_enable();
      			///M25P05_PageProgram(this->addressProcessing.byte_field.mh,this->addressProcessing.byte_field.ml,this->addressProcessing.byte_field.l,  &pBuf[(i*MEDIA_FLASH_WRITE_PAGE_SIZE)],  MEDIA_FLASH_WRITE_PAGE_SIZE);
            MediaMemory.WriteData(this->addressProcessing.byte_field.mh,this->addressProcessing.byte_field.ml,this->addressProcessing.byte_field.l,  &pBuf[(i*MEDIA_FLASH_WRITE_PAGE_SIZE)],  (uint16_t)MEDIA_FLASH_WRITE_PAGE_SIZE);
            sprintf (lcd_buf,"wAddr:%04uk",(uint16_t)(this->addressProcessing.value_int/1000));
            LcdStringUpdate(1,LCD_LINE_5,lcd_buf);
    				this->addressProcessing.value_int+=MEDIA_FLASH_WRITE_PAGE_SIZE;
    				//while((M25P05_Read_Status_Register()  &  (1<<STATUS_REGISTER_BIT00_BUSY))  !=  0);//ожидаю  окончания  записи
    				}
    			iterations--;
    			this->writeBuffer_IncrementBottom();
    			}
    		udi_hid_generic_send_report_in(this->outgoingData);
    		this->commandProcessing	=  COMMAND_NONE;
        LcdStringUpdate(1,LCD_LINE_5,(char*)"done wrt flash");
    
    		}
    	PORTF.OUTCLR	=  1<<4;
      }
    break;
    }
  }
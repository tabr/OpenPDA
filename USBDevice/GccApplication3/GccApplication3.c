// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/* 
 * This file is part of the OpenPDA distribution https://github.com/tabr/OpenPDA
 * Copyright (c) 2010-2021 Mateshko Andrei (tabr).
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 2.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
 //http://we.easyelectronics.ru/AVR/avr-studio-50-i-xmega256a3-nachalo.html
/* -Wl,--section-start=.text=0x20000
 * GccApplication3.c
 *
 * Created: 2015-01-19 22:28:20
 *  Author: tabr


еще в свойствах проекта под выбором O1 Os
я добавил -finline-limit=1
а в General галочку первую поставил
// Sleep manager options
//#define CONFIG_SLEEPMGR_ENABLE
 */ 
#define	F_CPU 		32000000UL
//#define	F_CPU 		2000000UL
#define ATMEL_STUDIO

//#define W_LCD
#define W_MEDIA_FLASH
//#define W_BUTTON_ENTER
//#define BOOT_INTERRUPTS_REMAP

#include <avr/io.h>
#include <util/delay.h>

#include "src/asf.h"
#include "TWI_c.h"
#include "protocol.h"
#include <string.h>

#include "D:\projects\stalker\lib\my_defines.h"
#ifdef W_MEDIA_FLASH
#include "D:\projects\stalker\lib\M25P05_instructions.h"
#include "d:\projects\stalker\lib\M25P05.c"
#endif
#include "D:\projects\stalker\lib\unionsFixed.h"

//#include "iopins.h"
//#include "pinlist.h"
//#include "D:\projects\stalker\lib\stalker\drivers\Driver_IO_xmega128a1u.h"
#include <stdio.h>
//#include "n3310lcd.h"
#ifdef W_LCD
#include "n3310_new.c"
#endif


//uint8_t dummyData [UDI_HID_REPORT_OUT_SIZE]	= {0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t outgoingData [UDI_HID_REPORT_OUT_SIZE];
uint8_t incomingData [UDI_HID_REPORT_IN_SIZE];
/*
uint8_t buffer0[USB_PAYLOAD_SIZE];
uint8_t buffer1[USB_PAYLOAD_SIZE];
uint8_t buffer2[USB_PAYLOAD_SIZE];
uint8_t buffer3[USB_PAYLOAD_SIZE];

uint8_t *writeBuffers[USB_WRITE_BUFFERS_NUM]	= {buffer0, buffer1, buffer2, buffer3};
*/
uint8_t writeBuffers[(USB_WRITE_BUFFERS_NUM * USB_PAYLOAD_SIZE)];
uint8_t writeBufferTop							= 0;
uint8_t writeBufferBottom						= 0;


bool isWriteBufferEmpty(void)
	{
	return (writeBufferTop == writeBufferBottom);
	}
bool isWriteBufferFull(void)
	{
	// empty if ((writeBufferTop + 1) == writeBufferBottom)
	// то есть, если голова в следующий раз догонит зад
	uint8_t writeBufferTopTemp	= ((writeBufferTop + 1) & USB_WRITE_BUFFERS_MASK);
	return (writeBufferTopTemp == writeBufferBottom);
	}
void writeBuffer_IncrementTop(void)
	{
	writeBufferTop++;
	writeBufferTop	&= USB_WRITE_BUFFERS_MASK;
	}
void writeBuffer_IncrementBottom(void)
	{
	writeBufferBottom++;
	writeBufferBottom	&= USB_WRITE_BUFFERS_MASK;
	}
void writeBuffer_Write(uint8_t *data, uint8_t size)
	{
	memcpy (&writeBuffers[(writeBufferTop * USB_PAYLOAD_SIZE)], data, size);
	writeBuffer_IncrementTop();
	}

volatile uint8_t commandProcessing				= 0;
volatile uint8_t selectedMemory					= 0;
volatile uint8_t addressH						= 0;
volatile uint8_t addressM						= 0;
volatile uint8_t addressL						= 0;
//volatile uint8_t writeBuffer_NumBusyBuffersMask	= 0;
//volatile uint8_t writeBuffer_Head				= 0;
volatile bool isAwaitingForData					= false;

//bool isBusy										= false;
//uint8_t currentState							= 0;
//uint8_t EEPROM_packetID							= 0;


//typedef void* AppPtr;
void startApplication()
	{
	/*
	void (*reset_vect)( void ) = 0x0000;
	while ((NVM.STATUS & NVM_NVMBUSY_bm) != 0);
	// Jump into main code
	EIND = 0x00;
	reset_vect();*/
	// exit bootloader
	//AppPtr application_vector = (AppPtr)0x000000;
	void (*reset_vect)( void ) = 0x0000;

//					udc_detach();
//					udc_stop();
//					cpu_irq_disable();

	
	//uint8_t temp = PMIC.CTRL;
	//temp |= PMIC_IVSEL_bm;
	
	
	//uint8_t byte_u8 = (PMIC.CTRL & ((uint8_t) ~PMIC_IVSEL_bm));
	
	//CCP = CCP_IOREG_gc;      // unlock IVSEL
	//PMIC.CTRL = temp;
	
	udc_detach();
	udc_stop();
	cpu_irq_disable();
	
//	ccp_write_io((uint8_t*)&PMIC.CTRL, 0);
	EIND = 0;				// indirect jumps go to app section
	
//	CCP = CCP_IOREG_gc;		// unlock IVSEL
//	PMIC.CTRL = 0;			// disable interrupts
//	EIND = 0;				// indirect jumps go to app section
//	RAMPZ = 0;				// LPM uses lower 64k of flash
	//application_vector();
	reset_vect();
	}
/*
void isp_start_appli(void)
	{
	cpu_irq_disable();
	// generate soft reset for Xmega
	//start_app_key=0x55AA;
	ccp_write_io((uint8_t *)&RST.CTRL, RST.CTRL | RST_SWRST_bm);
	while (1);
	}*/
/*uint8_t getFreeWriteBuffersNum(void)
	{
	return (USB_WRITE_BUFFERS_NUM - writeBuffer_NumBusyBuffers);
	}*/
	
/*uint8_t getFirstFreeWriteBufferID(void)//проверь кол-во сначала
	{
	uint8_t bufferId=0;
	if (writeBuffer_NumBusyBuffers == USB_WRITE_BUFFERS_NUM)
		return 0;
	bufferId	= (writeBuffer_Head + writeBuffer_NumBusyBuffers) % USB_WRITE_BUFFERS_NUM;
	}*/
void my_callback_generic_set_feature(uint8_t *report_feature)
	{
	
	//PORTF.OUTTGL	= 1<<4;
	/*if (commandProcessing != COMMAND_NONE)
		{
		while(1)
			{
			PORTF.OUTTGL	= 1<<4;
			_delay_ms(100);
			}
		}*/ //при записи в буффер должно отрабатывать
	switch (report_feature[PACKET_FEATURE_STRUCTURE_COMMAND])
		{
		case COMMAND_WB_RESET_BUFFERS:
			writeBufferTop		= 0;
			writeBufferBottom	= 0;
			udi_hid_generic_send_report_in(outgoingData);
		break;
		case COMMAND_SELECT_MEMORY:
			if (report_feature[PACKET_FEATURE_STRUCTURE_SM_MEMORY] < PDAMEMORY_ERROR && report_feature[PACKET_FEATURE_STRUCTURE_SM_MEMORY] > PDAMEMORY_NONE)//заменить бы на что-то вроде "isMemoryGood()"
				{
				selectedMemory		= report_feature[PACKET_FEATURE_STRUCTURE_SM_MEMORY];
				commandProcessing	= report_feature[PACKET_FEATURE_STRUCTURE_SM_COMMAND];
				//PORTF.OUTSET	= 1<<4;
				//udi_hid_generic_send_report_in(outgoingData);//вставить чего, может?!
				/*while(1)
					{
					PORTF.OUTTGL	= 1<<4;
					_delay_ms(100);
					}*/
				}
			break;
		case COMMAND_READ:
		case COMMAND_WRITE:
			commandProcessing	= report_feature[PACKET_FEATURE_STRUCTURE_RW_COMMAND];
			addressH			= report_feature[PACKET_FEATURE_STRUCTURE_RW_ADDRESS_H];
			addressM			= report_feature[PACKET_FEATURE_STRUCTURE_RW_ADDRESS_M];
			addressL			= report_feature[PACKET_FEATURE_STRUCTURE_RW_ADDRESS_L];
/*char lcdBuf[15];
						sprintf (lcdBuf, "%03d %03d %03d",  addressH,addressM,addressL  );
						LcdGotoXYFont(0,LCD_LINE_6);
						LcdStr(FONT_1X,(byte*)lcdBuf);
						LcdUpdate();
		while(1)
				{
				PORTF.OUTTGL	= 1<<4;
				_delay_ms(100);
				}*/
		break;
		
		case COMMAND_WB_GET_STATUS:
			
//			outgoingData[PACKET_RESPOND_GWBS_BUFFER_STATUS]		= writeBuffersStatus;
			outgoingData[PACKET_RESPOND_GWBS_TOP]				= writeBufferTop;
			outgoingData[PACKET_RESPOND_GWBS_BOTTOM]			= writeBufferBottom;
			//outgoingData[PACKET_RESPOND_GWBS_BUSYBUF_MASK]	= writeBuffer_NumBusyBuffersMask;//getFirstFreeWriteBufferID();
			udi_hid_generic_send_report_in(outgoingData);
		break;
		}
	
	}
void my_callback_generic_report_out(uint8_t *bufferData)
	{
	//uint8_t bufferID;
	//if (!isAwaitingForData)
	//	return;
	switch(bufferData[PACKET_GENERIC_STRUCTURE_COMMAND])
		{
		case COMMAND_WB_WRITE:
			{
			/*uint8_t bufferID	= bufferData[PACKET_SETBUFFER_STRUCTURE_BUFFERID];
			if (bufferID >= USB_WRITE_BUFFERS_NUM)
				{
				return;
				}*/
			writeBuffer_Write(&bufferData[USB_BUFFER_START_SECTION_PAYLOAD], USB_PAYLOAD_SIZE);
			//memcpy(&writeBuffers[(bufferID * USB_PAYLOAD_SIZE)], &bufferData[USB_BUFFER_START_SECTION_PAYLOAD], USB_PAYLOAD_SIZE);
//			sbi(writeBuffer_NumBusyBuffersMask,bufferID);
			}
		break;
		}
	}
/*void setCorrectAnswerDataFromRequested(void)
	{
	outgoingData[PACKET_HEAD_STRUCTURE_COMMAND]		= incomingData[PACKET_HEAD_STRUCTURE_COMMAND];
	outgoingData[PACKET_HEAD_STRUCTURE_ADDRESS_H]	= incomingData[PACKET_HEAD_STRUCTURE_ADDRESS_H];
	outgoingData[PACKET_HEAD_STRUCTURE_ADDRESS_MH]	= incomingData[PACKET_HEAD_STRUCTURE_ADDRESS_MH];
	outgoingData[PACKET_HEAD_STRUCTURE_ADDRESS_ML]	= incomingData[PACKET_HEAD_STRUCTURE_ADDRESS_ML];
	outgoingData[PACKET_HEAD_STRUCTURE_ADDRESS_L]	= incomingData[PACKET_HEAD_STRUCTURE_ADDRESS_L];
	outgoingData[PACKET_HEAD_STRUCTURE_SENDER_DATA]	= incomingData[PACKET_HEAD_STRUCTURE_SENDER_DATA];
	}*/
int main(void)
	{
	//uint32_t addressProcessing=0;
	UNION_UINT32_LITTLE_ENDIAN addressProcessing;
	//uint8_t tmp=0;
	#ifdef W_LCD
		char lcdBuf[15];
		uint8_t tmp=0;
	#endif
	
	/*for (uint8_t i=0;i<64;i++)
		{
		outgoingData[i]=i;
		}*/
	PORTA.DIRSET	= 0xff;
	PORTB.DIRSET	= 0xff;
	PORTC.DIRSET	= 0xff;
	PORTD.DIRSET	= 0xff;
	PORTE.DIRSET	= 0xff;
	PORTF.DIRSET	= 0xff;
	PORTH.DIRSET	= 0xff;
	PORTJ.DIRSET	= 0xff;
	PORTK.DIRSET	= 0xff;
	PORTQ.DIRSET	= 0xff;

	PORTA.OUTCLR	= 0xff;
	PORTB.OUTCLR	= 0xff;
	PORTC.OUTCLR	= 0xff;
	PORTD.OUTCLR	= 0xff;
	PORTE.OUTCLR	= 0xff;
	PORTF.OUTCLR	= 0xff;
	PORTH.OUTCLR	= 0xff;
	PORTJ.OUTCLR	= 0xff;
	PORTK.OUTCLR	= 0xff;
	PORTQ.OUTCLR	= 0xff;

	PORTF.DIRSET	= 1<<4;
	PORTF.OUTCLR	= 1<<4;
	#ifdef W_BUTTON_ENTER
	PORTA.DIRCLR	= 1<<2;
	//PORTA.OUTCLR	= 1<<2;
	PORTA.PIN2CTRL	= PORT_OPC_PULLUP_gc;
	#endif
	
	//writeBuffers[0]	= &buffer0;
	
//	startApplication();
	
	#ifdef BOOT_INTERRUPTS_REMAP
	// Map interrupt vectors table in bootloader section
	ccp_write_io((uint8_t*)&PMIC.CTRL, PMIC_IVSEL_bm | PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm);//works!
	#endif
	
	irq_initialize_vectors();
    cpu_irq_enable();
    sysclk_init();	
//	_delay_ms(2000);
	/*
	OSC.XOSCCTRL = OSC_FRQRANGE_12TO16_gc | OSC_XOSCSEL_XTAL_256CLK_gc; // configure the XTAL input
	OSC.CTRL |= OSC_XOSCEN_bm; // start XTAL
	while (!(OSC.STATUS & OSC_XOSCRDY_bm)); // wait until ready
	_delay_ms(100/2);

	OSC.PLLCTRL = OSC_PLLSRC_XOSC_gc | 0x2; // XTAL->PLL, 2x multiplier
	OSC.CTRL |= OSC_PLLEN_bm; // start PLL
	while (!(OSC.STATUS & OSC_PLLRDY_bm)); // wait until ready
	_delay_ms(100/2);
	CCP = CCP_IOREG_gc; // allow changing CLK.CTRL
	CLK.CTRL = CLK_SCLKSEL_PLL_gc; // use PLL output as system clock
	*/
	#ifdef W_BUTTON_ENTER
	if ((PORTA.IN & (1<<2)) != 0)//то есть высокий уровень
		{
		startApplication();
		}
	#endif
    udc_start();
	udc_attach(); //подсоединяемся к хосту
//	USB.ADDR	= 0xFF;
    sysclk_enable_module(SYSCLK_PORT_C, SYSCLK_TC0); // включение тактирования таймера ТС0
    sysclk_enable_module(SYSCLK_PORT_C, SYSCLK_TWI);
    sysclk_enable_module(SYSCLK_PORT_C, SYSCLK_SPI);
    sysclk_enable_module(SYSCLK_PORT_E, SYSCLK_SPI);
	
	
	TWI(&TWIC, TWI_EEPROM_TWI_ADDRESS, TWI_EEPROM_SPEED_KHZ);
	#ifdef W_MEDIA_FLASH
	PORTD.OUTSET	= 1<<1;//RFM69_SS
	M25P05_Init();
	#endif
	//uint8_t i = 0;
	/*uint8_t tmpData[10]={
		(2700>>8), (2700 & 0xFF),			//000 Время в секундах отсидки в мертвяке - 45мин
		30,									//002 кол-во секунд для регена (меньше - быстрее)
		100,								//003 максимальное ХП, которое игрок может накопить
		90,									//004 кол-во ХП, с которым стартует Игрок
		100,								//005 максимальная радиационная доза, которую может накопить игрок
		85,									//006 уровень, при котором наносится двойной урон радиацией
		1,									//007 множитель урона от радиации
		(600>>8), (600 & 0xFF)				//008 Время в секундах на отыгрыш зомби
	};
	writeToDevice(0, 10, tmpData);*/
	/*
	PORTF.OUTSET	= 1<<4;
	uint8_t tmpData[128];
	memset(tmpData, 0, 128);
//	writeToDevice(0, 32, tmpData);
	uint8_t bufferPtr=0;
	for (uint8_t i=0;i<(USB_PAGE_SIZE/TWI_EEPROM_WRITE_PAGE_SIZE);i++)
		{
		writeToDevice(EEPROMAddress, TWI_EEPROM_WRITE_PAGE_SIZE, &tmpData[bufferPtr]);
		EEPROMAddress+=8;
		bufferPtr+=8;
		_delay_ms(100);
		}
	PORTF.OUTCLR	= 1<<4;
	*/
	/*M25P05_Write_enable();
	M25P05_BulkErase();//нужно разр запись сначала!
	M25P05_Write_disable();
	while((M25P05_Read_Status_Register() & 1) != 0);//ожидаю окончания стирания
	*/
	uint8_t i=0;
	while(++i< 9)
		{
		PORTF.OUTTGL	= 1<<4;
		_delay_ms(500);
		}
	#ifdef W_LCD
		LcdInit();
	//	sprintf (lcd_buf, "test");
	//	LcdString(1,LCD_LINE_1);
		LcdGotoXYFont(0,LCD_LINE_1);
		LcdStr(FONT_1X,(byte*)"test ");
		LcdUpdate();
	#endif
    while(1)
		{
		#ifdef W_LCD
			sprintf (lcdBuf, "%03d %03d %03d",selectedMemory,commandProcessing, writeBufferTop);
			LcdGotoXYFont(0,LCD_LINE_1);
			LcdStr(FONT_1X,(byte*)lcdBuf);

			sprintf (lcdBuf, "%03d%03d  %03d%03d",writeBuffers[0],writeBuffers[1],writeBuffers[2],writeBuffers[3]);
			LcdGotoXYFont(0,LCD_LINE_2);
			LcdStr(FONT_1X,(byte*)lcdBuf);

			LcdUpdate();
		#endif
		switch (commandProcessing)
			{
			case COMMAND_SELECT_MEMORY:
				//PORTF.OUTSET	= 1<<4;
				udi_hid_generic_send_report_in(outgoingData);//вставить чего, может?!
				commandProcessing	= COMMAND_NONE;
			break;

			case COMMAND_READ:
				PORTF.OUTSET	= 1<<4;
				if (selectedMemory == PDAMEMORY_TWI_EEPROM)
					{
					readFromDevice(addressH, addressL, USB_PAYLOAD_SIZE, &outgoingData[USB_BUFFER_START_SECTION_PAYLOAD]);
					}
				else if (selectedMemory == PDAMEMORY_MEDIA_FLASH)
					{
					#ifdef W_MEDIA_FLASH
					//while((M25P05_Read_Status_Register() & (1<<STATUS_REGISTER_BIT00_BUSY)) != 0);
					M25P05_Read(addressH,addressM,addressL, USB_PAYLOAD_SIZE, &outgoingData[USB_BUFFER_START_SECTION_PAYLOAD] );
					/*if ((addressH | addressM | addressL) == 0)
						{
						sprintf (lcdBuf, "OK!!!!");
						LcdGotoXYFont(0,LCD_LINE_1);
						LcdStr(FONT_1X,(byte*)lcdBuf);
					sprintf (lcdBuf, "%03d %03d %03d",  addressH,addressM,addressL  );
					LcdGotoXYFont(0,LCD_LINE_2);
					LcdStr(FONT_1X,(byte*)lcdBuf);
						LcdUpdate();
						while (1);
						}*/
					/*
					sprintf (lcdBuf, "читаю [%03d]", ++tmp);
					LcdGotoXYFont(0,LCD_LINE_1);
					LcdStr(FONT_1X,(byte*)lcdBuf);

					sprintf (lcdBuf, "%03d %03d %03d",  addressH,addressM,addressL  );
					LcdGotoXYFont(0,LCD_LINE_2);
					LcdStr(FONT_1X,(byte*)lcdBuf);

					sprintf (lcdBuf, "%03d%03d %03d%03d",  outgoingData[USB_BUFFER_START_SECTION_PAYLOAD + 0], outgoingData[USB_BUFFER_START_SECTION_PAYLOAD + 1], outgoingData[USB_BUFFER_START_SECTION_PAYLOAD + 2], outgoingData[USB_BUFFER_START_SECTION_PAYLOAD + 3]  );
					LcdGotoXYFont(0,LCD_LINE_3);
					LcdStr(FONT_1X,(byte*)lcdBuf);
					LcdUpdate();*/
					//_delay_ms(1000);
					#endif //W_MEDIA_FLASH
					}
				udi_hid_generic_send_report_in(outgoingData);
				commandProcessing	= COMMAND_NONE;
				PORTF.OUTCLR	= 1<<4;
			break;
			
			case COMMAND_WRITE:
				PORTF.OUTSET	= 1<<4;
				if (selectedMemory == PDAMEMORY_TWI_EEPROM)
					{
					addressProcessing.value_int	= 0;
					uint16_t iterations			= TWI_EEPROM_SIZE_IN_BYTES/USB_PAYLOAD_SIZE;
					while (iterations > 0)
						{
						#ifdef W_LCD
							sprintf (lcdBuf, "[%03d %05d]", writeBufferTop, iterations);
							LcdGotoXYFont(0,LCD_LINE_1);
							LcdStr(FONT_1X,(byte*)lcdBuf);
							LcdUpdate();
						#endif
						if (isWriteBufferEmpty())
							{
							#ifdef W_LCD
								sprintf (lcdBuf, "жду данные");
								LcdGotoXYFont(0,LCD_LINE_4);
								LcdStr(FONT_1X,(byte*)lcdBuf);
								sprintf (lcdBuf, "%03d", ++tmp);
								LcdGotoXYFont(0,LCD_LINE_5);
								LcdStr(FONT_1X,(byte*)lcdBuf);
								LcdUpdate();
							#endif
							continue;
							}
						uint8_t *pBuf	= &writeBuffers[(writeBufferBottom * USB_PAYLOAD_SIZE)];
						
						for (uint8_t i=0;i<(USB_PAYLOAD_SIZE/TWI_EEPROM_WRITE_PAGE_SIZE);i++)
							{
							writeToDevice(addressProcessing.byte_field.ml, addressProcessing.byte_field.l, TWI_EEPROM_WRITE_PAGE_SIZE, &pBuf[(i*TWI_EEPROM_WRITE_PAGE_SIZE)]);
							addressProcessing.value_int+=TWI_EEPROM_WRITE_PAGE_SIZE;

							#ifdef W_LCD
								sprintf (lcdBuf, "%03d %03d %03d",  iterations, addressProcessing.byte_field.ml, addressProcessing.byte_field.l  );
								LcdGotoXYFont(0,LCD_LINE_3);
								LcdStr(FONT_1X,(byte*)lcdBuf);
								LcdUpdate();
							#endif

							_delay_ms(TWI_EEPROM_WRITE_DELAY_MS);
							}
						iterations--;
						writeBuffer_IncrementBottom();
						}
					udi_hid_generic_send_report_in(outgoingData);
					commandProcessing	= COMMAND_NONE;
					#ifdef W_LCD
						LcdClear();
					#endif
					}
				else if (selectedMemory == PDAMEMORY_MEDIA_FLASH)
					{
					#ifdef W_MEDIA_FLASH
					addressProcessing.value_int	= 0;
					uint16_t iterations			= MEDIA_FLASH_SIZE_IN_BYTES/USB_PAYLOAD_SIZE;
					M25P05_Write_enable();
					M25P05_BulkErase();//нужно разр запись сначала!
					M25P05_Write_disable();
					while((M25P05_Read_Status_Register() & 1) != 0);//ожидаю окончания стирания
					while (iterations > 0)
						{
						#ifdef W_LCD
						sprintf (lcdBuf, "[%03d %05d]", writeBufferTop, iterations);
						LcdGotoXYFont(0,LCD_LINE_1);
						LcdStr(FONT_1X,(byte*)lcdBuf);
						LcdUpdate();
						#endif
						if (isWriteBufferEmpty())
							{
							#ifdef W_LCD
							sprintf (lcdBuf, "жду данные");
							LcdGotoXYFont(0,LCD_LINE_4);
							LcdStr(FONT_1X,(byte*)lcdBuf);
							sprintf (lcdBuf, "%03d", ++tmp);
							LcdGotoXYFont(0,LCD_LINE_5);
							LcdStr(FONT_1X,(byte*)lcdBuf);
							LcdUpdate();
							#endif
							continue;
							}
						uint8_t *pBuf	= &writeBuffers[(writeBufferBottom * USB_PAYLOAD_SIZE)];
						
						for (uint8_t i=0;i<(USB_PAYLOAD_SIZE/MEDIA_FLASH_WRITE_PAGE_SIZE);i++)
						//i=0;
							{
//							writeToDevice(addressProcessing.byte_field.ml, addressProcessing.byte_field.l, MEDIA_FLASH_WRITE_PAGE_SIZE, &pBuf[(i*MEDIA_FLASH_WRITE_PAGE_SIZE)]);
							M25P05_Write_enable();
							//while((M25P05_Read_Status_Register() & (1<<STATUS_REGISTER_BIT01_WEL)) == 0);//ожидаю wp
							M25P05_PageProgram(addressProcessing.byte_field.mh,addressProcessing.byte_field.ml,addressProcessing.byte_field.l, &pBuf[(i*MEDIA_FLASH_WRITE_PAGE_SIZE)], MEDIA_FLASH_WRITE_PAGE_SIZE);
							//M25P05_ByteProgram(addressProcessing.byte_field.mh,addressProcessing.byte_field.ml,addressProcessing.byte_field.l, pBuf[(i*MEDIA_FLASH_WRITE_PAGE_SIZE)]);
							//_delay_ms(10);
							/*for (uint8_t i=0;i<USB_PAYLOAD_SIZE;i++)
								{
								M25P05_Write_enable();
								M25P05_ByteProgram(addressProcessing.byte_field.mh,addressProcessing.byte_field.ml,addressProcessing.byte_field.l,10);
								while((M25P05_Read_Status_Register() & 1) != 0);
								addressProcessing.value_int++;
								}*/
/*iterations=1;
							sprintf (lcdBuf, "%03d %03d%03d%03d", i,  addressProcessing.byte_field.mh, addressProcessing.byte_field.ml, addressProcessing.byte_field.l  );
							LcdGotoXYFont(0,LCD_LINE_3);
							LcdStr(FONT_1X,(byte*)lcdBuf);
							sprintf (lcdBuf, "%03d%03d %03d%03d",  pBuf[(i*MEDIA_FLASH_WRITE_PAGE_SIZE)], pBuf[(i*MEDIA_FLASH_WRITE_PAGE_SIZE)+1], pBuf[(i*MEDIA_FLASH_WRITE_PAGE_SIZE)+2], pBuf[(i*MEDIA_FLASH_WRITE_PAGE_SIZE)+3]  );
							LcdGotoXYFont(0,LCD_LINE_6);
							LcdStr(FONT_1X,(byte*)lcdBuf);
							LcdUpdate();*/

							addressProcessing.value_int+=MEDIA_FLASH_WRITE_PAGE_SIZE;
							while((M25P05_Read_Status_Register() & (1<<STATUS_REGISTER_BIT00_BUSY)) != 0);//ожидаю окончания записи
							//_delay_ms(MEDIA_FLASH_WRITE_DELAY_MS);
							//_delay_ms(250);
							}
						iterations--;
						writeBuffer_IncrementBottom();
						//M25P05_Write_disable();
						}
					udi_hid_generic_send_report_in(outgoingData);
					commandProcessing	= COMMAND_NONE;
					#ifdef W_LCD
						LcdClear();
					#endif
					#endif //W_MEDIA_FLASH
					}
				PORTF.OUTCLR	= 1<<4;
			break;
			}
		
		/*switch (commandProcessing)
			{
			case COMMAND_READ:
				PORTF.OUTSET	= 1<<4;
				if (selectedMemory == MEMORY_TWI_EEPROM)
					{
					readFromDevice(incomingData[PACKET_HEAD_STRUCTURE_ADDRESS_L], USB_PAYLOAD_SIZE, &outgoingData[BUFFER_START_SECTION_PAYLOAD]);
					setCorrectAnswerDataFromRequested();
					}
				else if (selectedMemory == MEMORY_MEDIA_FLASH)
					{
					//M25P05_Read(incomingData[PACKET_HEAD_STRUCTURE_ADDRESS_MH],incomingData[PACKET_HEAD_STRUCTURE_ADDRESS_ML],incomingData[PACKET_HEAD_STRUCTURE_ADDRESS_L], USB_PAYLOAD_SIZE, &outgoingData[BUFFER_START_SECTION_PAYLOAD] );
					//outgoingData[BUFFER_START_SECTION_PAYLOAD]=9;
					//outgoingData[BUFFER_START_SECTION_PAYLOAD]=M25P05_Read_DataByte(0,0,0);
					setCorrectAnswerDataFromRequested();
					}
				PORTF.OUTCLR	= 1<<4;
				commandProcessing	= COMMAND_NONE;
			break;
			case COMMAND_WRITE:
				PORTF.OUTSET	= 1<<4;
				if (selectedMemory == MEMORY_TWI_EEPROM)
					{
					TWI_EEPROM_Address_t EEPROMAddress	= incomingData[PACKET_HEAD_STRUCTURE_ADDRESS_L];
					uint8_t bufferPtr					= BUFFER_START_SECTION_PAYLOAD;

					for (uint8_t i=0;i<(USB_PAYLOAD_SIZE/TWI_EEPROM_WRITE_PAGE_SIZE);i++)
						{
						writeToDevice(EEPROMAddress, TWI_EEPROM_WRITE_PAGE_SIZE, &incomingData[bufferPtr]);
						EEPROMAddress+=8;
						bufferPtr+=8;
						_delay_ms(10);
						}
					setCorrectAnswerDataFromRequested();
					}
				PORTF.OUTCLR	= 1<<4;
				commandProcessing	= COMMAND_NONE;
			break;
			}
		outgoingData[PACKET_HEAD_STRUCTURE_RANDOM_ITERATOR]++;
		udi_hid_generic_send_report_in(outgoingData);
		*/
 	}
}
//#include "n3310lcd.c"

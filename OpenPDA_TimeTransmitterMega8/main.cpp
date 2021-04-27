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
 /*
 * TimeTransmitterMega8.cpp
 *
 * Created: 2015-10-23 01:30:15
 * Author : tabr
 */ 
#define ATMEL_STUDIO				6.2
#define F_CPU 8000000L
#define SELECTED_BYTE_ORDER   DEF_BYTE_ORDER_LITTLE_ENDIAN


#define SOFT_SPI					1
#define HACK_RCV_RESTART

#define cbi(port,bit)   port&=~(1<<bit);
#define sbi(port,bit)   port|=(1<<bit);


// Voltage Reference: AVCC with external capacitor at AREF pin
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (1<<ADLAR))
enum LCD_LINES
{
	LCD_LINE_1=1,
	LCD_LINE_2,
	LCD_LINE_3,
	LCD_LINE_4,
	LCD_LINE_5,
	LCD_LINE_6
};
class Driver_Clock
{
	public:
	//void select_16x2_MHZExternal();
	protected:
	private:
};
class Runnable
{
	
};

//#define BOMB_ID	8

#define  N3310_WITHOUT_DMA


//#if (BOMB_ID > 127)
//#define IS_BOMB_BLOCKER	1
//#endif
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <avr/eeprom.h>
#include <util/atomic.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <avr/sleep.h>

#include "TODOmacro.h"



#include "stalker/drivers/Driver_IO_mega8a.hpp"
#include "unionsFixed.h"
//#include "stalker/drivers/Driver_IO_mega168pa.h"
#include "pin.h"
#include "stalker/drivers/Driver_AnoRadRarioModule_RFM23.hpp"
#include "crc16.h"
#include "stalker/HAL.hpp"
#include "n3310lcd.c"
//#include "n3310_new.h"
//#include "stalker/LcdClass.h"
//#include "n3310LcdClass.h"
//#include "stalker/drivers/StalkerUI_Class_n3310.h"

#include "stalker/Class_StalkerLayer1.hpp"
#include "TimeClass.hpp"
#include <LogClass.hpp>

//n3310LcdClass LcdDisplay;
Class_HAL HAL;
TimeClass TimeRTC;
class PlayerDummuClass
	{
	public:
		void Revive(void)
			{
			
			}
	protected:
	private:
	};
//LcdClass Lcd;

PlayerDummuClass Player;
volatile bool isNeedLCDUpdate=false;
uint8_t timeUpdateTimer	= 255;//not used
bool SPILocked=false;//not used
bool timeSyncReceivedAtLastOnce=false;//not used

ISR(TIMER1_OVF_vect)
	{
	isNeedLCDUpdate=true;
	TimeRTC.incrementSeconds();
	TCNT1H=0x85EE >> 8;
	TCNT1L=0x85EE & 0xff;
	}
uint8_t read_adc(unsigned char adc_input)
	{
	ADMUX=adc_input | ADC_VREF_TYPE;
	// Delay needed for the stabilization of the ADC input voltage
	_delay_us(10);
	// Start the AD conversion
	ADCSRA|=(1<<ADSC);
	// Wait for the AD conversion to complete
	while ((ADCSRA & (1<<ADIF))==0);
	ADCSRA|=(1<<ADIF);
	return ADCH;
	}
const PROGMEM char STR_DOWN[] = "down";
int main(void)
	{
    //uint8_t txBuffer[Class_StalkerLayer0::STRUCTURE_SIZE];
	
	//uint8_t tmpSecond=0;
	uint8_t selectedState=0;
	uint8_t buttonsLocked=0;
	//StalkerUI_Class StalkerUI;
	
//    DDRD	|= 1<<2 | 1<<3 | 1<<4 | 1<<6;
	Button0::setDirOut();
	Button0::setPullUp();
	Button1::setDirOut();
	Button1::setPullUp();
	Button2::setDirOut();
	Button2::setPullUp();
	
	#define BUTTON_PLUS		Button0
	#define BUTTON_SELECT	Button1
	#define BUTTON_ENTER	Button2

	//LED::setDirOut();
	RedLEDPin::setDirOut();
	GreenLEDPin::setDirOut();
	//LED::setOutHigh();
	
	RedLEDPin::setOutLow();
	GreenLEDPin::setOutHigh();


	// Timer/Counter 0 initialization
	// Clock source: System Clock
	// Clock value: Timer 0 Stopped
	TCCR0=(0<<CS02) | (0<<CS01) | (0<<CS00);
	TCNT0=0x00;

	// Timer/Counter 1 initialization
	// Clock source: System Clock
	// Clock value: 31,250 kHz
	// Mode: Normal top=0xFFFF
	// OC1A output: Disconnected
	// OC1B output: Disconnected
	// Noise Canceler: Off
	// Input Capture on Falling Edge
	// Timer Period: 1 s
	// Timer1 Overflow Interrupt: On
	// Input Capture Interrupt: Off
	// Compare A Match Interrupt: Off
	// Compare B Match Interrupt: Off
	TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
	TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (1<<CS12) | (0<<CS11) | (0<<CS10);
	TCNT1H=0x85;
	TCNT1L=0xEE;
	ICR1H=0x00;
	ICR1L=0x00;
	OCR1AH=0x00;
	OCR1AL=0x00;
	OCR1BH=0x00;
	OCR1BL=0x00;



	// Timer/Counter 2 initialization
	ASSR=0<<AS2;
	TCCR2=(0<<FOC2) | (0<<COM21) | (0<<COM20) | (0<<WGM21) | (1<<CS22) | (1<<CS21) | (1<<CS20);
	TCNT2=0;//32.768 ms
	OCR2=0x00;


	// Timer(s)/Counter(s) Interrupt(s) initialization
//	TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<TOIE0);
//	TIMSK=(0<<OCIE2) | (1<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<TOIE0);

	// Timer(s)/Counter(s) Interrupt(s) initialization
	TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<TOIE0);

	// External Interrupt(s) initialization
	// INT0: Off
	// INT1: Off
	MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);

	// USART initialization
	// USART disabled
	UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (0<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);

	// Analog Comparator initialization
	// Analog Comparator: Off
	// The Analog Comparator's positive input is
	// connected to the AIN0 pin
	// The Analog Comparator's negative input is
	// connected to the AIN1 pin
	ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
	SFIOR=(0<<ACME);

	// ADC initialization
	// ADC Clock frequency: 7,813 kHz
	// ADC Voltage Reference: Int., cap. on AREF
//	ADMUX=ADC_VREF_TYPE;
	ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADFR) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
//	ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADFR) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	SFIOR=(0<<ACME);
	/*
	// SPI initialization
	// SPI disabled
	SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);
	*/
	// TWI initialization
	// TWI disabled
	TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);
	
	Class_StalkerLayer0 StalkerLayer0;
	
	//LcdDisplay.IOInit();
	//LcdDisplay.HardwareInitialization();
	//LcdStringUpdate(1,LCD_LINE_1, (char*)"LCD started");
	HAL.IOInit();
//	HAL.EnvironmentRarioModule.setTXBuffer(txBuffer);
//	HAL.EnvironmentRarioModule.setRXBuffer(txBuffer);
	StalkerLayer0.HardwareInitialization();
	HAL.EnvironmentRarioModule.setTXPower(HAL.EnvironmentRarioModule.TX_POWER_MAX);

	StalkerLayer0.SetTXPacketType(Class_StalkerLayer0::PACKET_TYPE_TIMEUPDATE);
	
	/*
	HAL.EnvironmentRarioModule.setPacketSize(Class_StalkerLayer0::STRUCTURE_SIZE);
	HAL.EnvironmentRarioModule.setTXBuffer(txBuffer);
	HAL.EnvironmentRarioModule.setRXBuffer(txBuffer);
	if (HAL.EnvironmentRarioModule.HardwareInitialization() != Class_HAL::ERROR_NO_ERRORS)
		{
		LcdClearCache();
		LcdStringUpdate(1,LCD_LINE_1, (char*)"RM init fail");
		while(1)
			{
			GreenLEDPin::setOutToggle();
			_delay_ms(100);
			}
		}
	*/
	
	
	//HAL.EnvironmentRarioModule.receiveBegin();
	LcdInit();
	LcdClear();
	//LcdStringUpdate(1,LCD_LINE_1, (char*)"starting...");
	sprintf (lcd_buf, "Уст. время:");
	LcdString(1, LCD_LINE_1);
	sprintf (lcd_buf, "*");
	LcdString(selectedState+1, LCD_LINE_3);
	LcdUpdate();
	RedLEDPin::setOutLow();
	GreenLEDPin::setOutLow();
    while (1) 
		{
		if (buttonsLocked > 0)
			{
			//todo
			//locking
			}
		else if (BUTTON_PLUS::isPinLow())
			{
			buttonsLocked=40;
			//LcdString(1,LCD_LINE_1, (char*)"button1");
			switch (selectedState)
				{
				case 0:
					{
					TimeRTC.hour+=10;
					}
				break;

				case 1:
					{
					TimeRTC.hour+=1;
					}
				break;

				case 3:
					{
					TimeRTC.minute+=10;
					}
				break;

				case 4:
					{
					TimeRTC.minute+=1;
					}
				break;

				case 6:
					{
					TimeRTC.second+=10;
					}
				break;

				case 7:
					{
					TimeRTC.second+=1;
					}
				break;
				}
			}
		else if (BUTTON_SELECT::isPinLow())
			{
			buttonsLocked=40;
			//sprintf (lcd_buf, " "); 
			//LcdString(selectedState+1, LCD_LINE_3);
			LcdChr((char*)" ",selectedState+1, LCD_LINE_3);
			if (++selectedState == 8)
				{
				selectedState=0;
				}
			if (selectedState == 2 || selectedState == 5)
				{
				selectedState++;
				}
			//sprintf (lcd_buf, "*"); 
			//LcdString(selectedState+1, LCD_LINE_3);
			LcdChr((char*)"*",selectedState+1, LCD_LINE_3);
			}
		else if (BUTTON_ENTER::isPinLow())
			{
			break;
			}

		TimeRTC.Update();
		sprintf (lcd_buf,"%02u:%02u:%02u", TimeRTC.hour, TimeRTC.minute, TimeRTC.second);
		LcdString(1,LCD_LINE_2);
		LcdUpdate();
		if (buttonsLocked > 0)
			{
			buttonsLocked--;
			}
		//_delay_ms(250);
		}
	sprintf (lcd_buf, " ");
	LcdString(selectedState+1, LCD_LINE_3);
	sei();
	//volatile uint8_t i=0;
	while(1)
		{
		if (isNeedLCDUpdate)
			{
	
			isNeedLCDUpdate=false;
			
			StalkerLayer0.packetContainerTX[1]	= TimeRTC.hour;
			StalkerLayer0.packetContainerTX[2]	= TimeRTC.minute;
			StalkerLayer0.packetContainerTX[3]	= TimeRTC.second;
			
			StalkerLayer0.prepareTimeUpdatePacket();
			HAL.EnvironmentRarioModule.sendBufferToRM();
			StalkerLayer0.sendPacket();
			
			sprintf (lcd_buf,"%02u:%02u:%02u", TimeRTC.hour, TimeRTC.minute, TimeRTC.second);
			LcdString(1,LCD_LINE_2);
			LcdUpdate();
			RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, 1<<5);	// to ready mode
			}
		//_delay_ms(10);
		}
	}

#include "stalker/Class_StalkerLayer0.cpp"
#include "stalker/Class_StalkerLayer1.cpp"
#include "stalker/drivers/Driver_AnoRadRarioModule_RFM23.cpp"
//#include "n3310_new.c"
#include "crc16.c"
//#include "stalker/LcdClass.cpp"
//#include "stalker/drivers/StalkerUI_Class_n3310.cpp"
//#include "n3310LcdClass.cpp"


void LogClass::Log(MESSAGES msg, uint8_t p1/* =0 */, uint8_t p2/* =0 */, uint8_t p3/* =0 */, uint8_t p4/* =0 */, uint8_t p5/* =0 */, uint8_t p6/* =0 */)
{

}

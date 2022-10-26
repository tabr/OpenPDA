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
 * Transmitter_mega8.cpp
 *
 * Created: 2015-04-13 21:32:59
 *  Author: tabr
 */ 
#define F_CPU 8000000L
#define cbi(port,bit)   port&=~(1<<bit);
#define sbi(port,bit)   port|=(1<<bit);
#define SELECTED_BYTE_ORDER   DEF_BYTE_ORDER_LITTLE_ENDIAN
//#define delay_ms		_delay_ms


#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h> // работа с прерывани€ми
#include <avr/sleep.h> // здесь описаны режимы сна
#include <avr/power.h>
#include <util/crc16.h>
#include <string.h>
#include <avr/eeprom.h>

#include <LogClass.hpp>

//#include "../x128_test2/src/QuestClass.h"

#define CRC_TABLE_RAM               1
//#define CHOOSEN_ANORAD_1            1
#define RFM22B_CHOOSE_TRANSMITTER   1
//#define DO_HACK_RESTART_PERIODICALLY
//#define GRANADE
//#define TX_POWER                    1//anoradData[CHOOSEN_ANORAD][0]

//178-9,984ms
//128-16.384
//99-20,096
//00-32.768

//#define TCNT_VALUE					255-155-(32/2)
//#define TCNT_VALUE					255-77-(32/2)
#define TCNT_MAX					128
#define TCNT_MIN					0
#define TCNT_RAND_RANGE				(TCNT_MAX-TCNT_MIN) //128
//#define TCNT_VALUE					(TCNT_MAX - RAND_RANGE)//128-RAND_RANGE
//#define LIB_PATH					"../../lib"

//#define  sendString(var) {}

#ifdef DO_HACK_RESTART_PERIODICALLY
#warning "DO_HACK_RESTART_PERIODICALLY"
#endif // DO_HACK_RESTART_PERIODICALLY

// Voltage Reference: AVCC with external capacitor at AREF pin
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (1<<ADLAR))
#include "stalker/drivers/Driver_IO_mega8a.hpp"
void Hack_RcvMayStuckTimer_Reload(void);
/*
class Driver_Clock
{
	public:
	void select_16x2_MHZExternal();
	protected:
	private:
};
class Runnable
{
	
};
class ITimerListener
{

};
*/
//#include "TemporaryClass.h"

#include "TODOmacro.h"
#include "unionsFixed.h"
#include "typedefs.h"
#include "../OpenPDA_Simple_mega8/pin.h"
#include <PlayerEffectsInterface.hpp>
#include <crc16.h>
#include <stalker/TimerClass.hpp>
#include <stalker/drivers/Driver_AnoRadRarioModule_RFM23.hpp>
#include "../OpenPDA_Simple_mega8/src/DummyClasses.hpp"
//#include "stalker/drivers/Driver_IO_mega168pa.h"
//#include "stalker/drivers/Driver_AnoRadRarioModule_RFM23.hpp"
#include "stalker/Class_StalkerLayer0.hpp"
#include "../OpenPDA_ATxmega128A1U/src/AnomalyClass.hpp"
//#include "gameAnoradData.h"




//#include "../../lib/rfm22b-23b_registers.h"
//#include "../../lib/rfm22b.c"


//UNION_UINT16 crc;
//bool denyTransmition    = 1;
volatile bool startTX					= false;
volatile bool SPILocked					= false;
volatile uint8_t TCNT_rand				= 0;
#define HACK_RCV_RESTART_TIMER_VALUE	255
volatile uint8_t Hack_RcvMayStuckTimer	= HACK_RCV_RESTART_TIMER_VALUE;

Driver_ClockDummy HWClock;
Class_HAL HAL(&HWClock);



ISR(TIMER0_OVF_vect)
	{
	//[128]	16384
	//[0]	32768
	// Reinitialize Timer1 value
	TCNT0=TCNT_MIN+TCNT_rand;
	startTX	= true;//может и не надо, т.к. проц всЄ равно проснЄтс€ тольк оот этого прерывани€
	}
/*
ISR(TIMER2_OVF_vect)
	{
	// Reinitialize Timer2 value
	startTX	= true;
	TCNT2	= TCNT_VALUE+TCNT_rand;
//	TCNT2	= TCNT_VALUE;
//	TCNT2	= TCNT_VALUE+(rand() % 32);
//	TCNT2	= 0;
//	PORTD	^= 1<<3;
	}
*/
// Read the 8 most significant bits
// of the AD conversion result
uint8_t read_adc(unsigned char adc_input)
	{
	ADMUX=adc_input | ADC_VREF_TYPE;
	// Delay needed for the stabilization of the ADC input voltage
	_delay_us(10);
	// Start the AD conversion
	ADCSRA|=(1<<ADSC);
	// Wait for the AD conversion to complete
	while ((ADCSRA & (1<<ADIF))==0) {};
	ADCSRA|=(1<<ADIF);
	return ADCH;
	}

int main(void)
	{
	uint8_t txPower=0;
	//Ќельз€ обнул€ть, т.к. клыссы отработали свои конструкторы!
	//DDRD	|= 1<<2 | 1<<3 | 1<<4 | 1<<6;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 7,813 kHz
TCCR0=(1<<CS02) | (0<<CS01) | (1<<CS00);
TCNT0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;
/*
// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 1000,000 kHz
// Mode: Normal top=0xFFFF
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 10 ms
// Timer1 Overflow Interrupt: On
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (1<<CS11) | (0<<CS10);
TCNT1H=0xD8;
TCNT1L=0xF0;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;
*/


// Timer/Counter 2 initialization
ASSR=0<<AS2;
//TCCR2=(0<<FOC2) | (0<<COM21) | (0<<COM20) | (0<<WGM21) | (0<<CS22) | (0<<CS21) | (1<<CS20);
//TCNT2=TCNT_VALUE;
TCCR2=(0<<FOC2) | (0<<COM21) | (0<<COM20) | (0<<WGM21) | (0<<CS22) | (0<<CS21) | (0<<CS20);// now disabled
TCNT2=0x00;
OCR2=0x00;


// Timer(s)/Counter(s) Interrupt(s) initialization
//TIMSK=(0<<OCIE2) | (1<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<TOIE0);
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (1<<TOIE0);

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
ADMUX=ADC_VREF_TYPE;
ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADFR) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
SFIOR=(0<<ACME);
/*
// SPI initialization
// SPI disabled
SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);
*/
// TWI initialization
// TWI disabled
TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);



  //eeprom_write_byte((uint8_t *) 0x00, 18);while(true){RedLEDPin::SetOutToggle();_delay_ms(100);};
  //eeprom_write_byte((uint8_t *) 0x00, 3);
  uint8_t RID = eeprom_read_byte((uint8_t *) 0x00);
//  #warning "[T] bad code style!"
//  if (RID == 0xFF)
//    {
//    eeprom_write_byte((uint8_t *) 0x00, 33);
//    RID = eeprom_read_byte((uint8_t *) 0x00);
    if (RID == 0xFF)
      {
      RedLEDPin::SetOutLow();
      GreenLEDPin::SetOutHigh();
      while(1)
        {
        _delay_ms(100);
        RedLEDPin::SetOutToggle();
        GreenLEDPin::SetOutToggle();
        };
      }
//    }

	BuzzerPin::SetDirOut();
	BuzzerPin_H::SetDirOut();
	RedLEDPin::SetDirOut();
	GreenLEDPin::SetDirOut();
	DeviceAlivePin::SetDirOut();

	RedLEDPin::SetOutHigh();
	GreenLEDPin::SetOutHigh();
	BuzzerPin::SetOutLow();
	BuzzerPin_H::SetOutLow();
	
	Class_StalkerLayer0 StalkerLayer0;
	HAL.IOInit();
	StalkerLayer0.HardwareInitialization();
	
	wdt_reset();
	
	txPower	= ~(read_adc(7));
	
//	if (txPower > 127)
	txPower	= txPower>>5;
	
	for (uint8_t i=0;i<txPower;i++)
		{
		RedLEDPin::SetOutHigh();
		_delay_ms(75);
		RedLEDPin::SetOutLow();
		_delay_ms(200);
		}

	_delay_ms(500);
	RedLEDPin::SetOutHigh();
	_delay_ms(500);
	RedLEDPin::SetOutLow();

	HAL.EnvironmentRarioModule.setTXPower(txPower);
	//HAL.EnvironmentRarioModule.setTXPower(7);
	
	
	asm("sei");
	//sbi(PORTD,4);
	//StalkerLayer0.setID1(CHOOSEN_ANORAD);
	//uint8_t* packet	= StalkerLayer0.getT
	
	
	
	StalkerLayer0.packetContainerTX[Class_StalkerLayer0::STRUCTURE_0X02_DATA_H]	= 0;
	StalkerLayer0.packetContainerTX[Class_StalkerLayer0::STRUCTURE_0X03_DATA_L]	= RID;//CHOOSEN_ANORAD;
	StalkerLayer0.prepareEnvironmentPacket();
	StalkerLayer0.sendPacket();
	
	/*
	StalkerLayer0.SetTXPacketSubType(10);
	StalkerLayer0.packetContainerTX[Class_StalkerLayer0::STRUCTURE_0X02_DATA_H]	= 11;
	StalkerLayer0.packetContainerTX[Class_StalkerLayer0::STRUCTURE_0X03_DATA_L]	= 12;
	StalkerLayer0.prepareMultyBytePacket(11, 13);
	*/
	
	
	//set_sleep_mode(SLEEP_MODE_PWR_SAVE);//ONLY IF  ASYNCRONIOUS, may be crystal installed!!!!!
	set_sleep_mode(SLEEP_MODE_IDLE);
//	srand(CHOOSEN_ANORAD);
	srand(RID);
	//RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, 0);
//	power_timer0_disable();
//	power_timer1_disable();
//	power_twi_disable();
  wdt_reset();
	wdt_enable(WDTO_2S);
	RedLEDPin::SetOutLow();
	GreenLEDPin::SetOutLow();
	/*
	UNION_UINT16 fakeCRC;
	UNION_UINT16 RandomData;
	fakeCRC.value_int=0;
	RandomData.value_int=0;
	while(1)
		{
		wdt_reset();
		GreenLEDPin::SetOutHigh();
		StalkerLayer0.packetContainer[0]=RandomData.byte_field.h;
		StalkerLayer0.packetContainer[1]=RandomData.byte_field.l;
		StalkerLayer0.packetContainer[2]=fakeCRC.byte_field.h;
		StalkerLayer0.packetContainer[3]=fakeCRC.byte_field.l;
		StalkerLayer0.packetContainer[4]=fakeCRC.byte_field.h;
		StalkerLayer0.packetContainer[5]=fakeCRC.byte_field.l;
		HAL.EnvironmentRarioModule.sendBufferToRM();
		if (++fakeCRC.value_int == 0)
			{
			RandomData.value_int++;
			}
		
		StalkerLayer0.sendPacket();
		while (RFM22B_PinNIRQ::isPinHigh());// wait for packet sent interrupt (NIRQ goes low)//nahua??!
 		GreenLEDPin::SetOutLow();
		}
	*/
	//uint8_t z=0;
	//StalkerLayer0.sendPacket();
  #ifdef DO_HACK_RESTART_PERIODICALLY
	uint16_t restartCounter	= 0;
  #endif
  //RedLEDPin::SetOutHigh();
  #warning "[T] REWRITE THIS bad code!"
  #warning "[T] add check is RM alive - freeze fix"
  while(1)//main cycle
		{
    #ifdef DO_HACK_RESTART_PERIODICALLY
    #warning "Hack TX restart enabled!"
		if (++restartCounter == (57*60*5))//~50hz //ISR 7.8 kHz - rand
			{
			while(1){};
			}
    #endif //DO_HACK_RESTART_PERIODICALLY
		//TCNT_rand	= (rand() % RAND_RANGE);
		//TCNT_rand	= 255;
        //asm("wdr");
		wdt_reset();
		DeviceAlivePin::SetOutHigh();
		if (startTX == true)
			{
/*
  while(1)
    {
    wdt_reset();
    RedLEDPin::SetOutToggle();
    _delay_ms(500);
    }
*/
//    #warning "Stucks here!"
			while (RFM22B_PinNIRQ::IsPinHigh())// wait for packet sent interrupt (NIRQ goes low)
        {
        //RedLEDPin::SetOutToggle();
        //_delay_ms(250);
        };
			TCNT_rand	= (rand() % (TCNT_RAND_RANGE+1));
			//_delay_ms(100);
			//PORTD ^= 1<<3;
//			TCNT2=TCNT_VALUE+(rand() % 32);
			GreenLEDPin::SetOutHigh();
			/*
			while(1)
				{
					wdt_reset();
			StalkerLayer0.packetContainer[2]=RandomData.byte_field.h;
			StalkerLayer0.packetContainer[3]=RandomData.byte_field.l;
			StalkerLayer0.packetContainer[4]=fakeCRC.byte_field.h;
			StalkerLayer0.packetContainer[5]=fakeCRC.byte_field.l;
			StalkerLayer0.packetContainer[6]=fakeCRC.byte_field.h;
			StalkerLayer0.packetContainer[7]=fakeCRC.byte_field.l;
			HAL.EnvironmentRarioModule.sendBufferToRM();
			if (++RandomData.value_int == 0xFFFF)
				{
				fakeCRC.value_int++;
				}
			*/
			/*
			StalkerLayer0.packetContainerTX[Class_StalkerLayer0::STRUCTURE_0X02_DATA_H]	= 11;
			StalkerLayer0.packetContainerTX[Class_StalkerLayer0::STRUCTURE_0X03_DATA_L]	= 12;
			StalkerLayer0.prepareMultyBytePacket(11, z);
			if (++z > 128)
				{
				z=0;
				}
			HAL.EnvironmentRarioModule.sendBufferToRM();
			*/
/*
      if (HAL.EnvironmentRarioModule.getState() != Driver_AnoRadRarioModule::TRX_STATE::TRX_STATE_IDLE)
        {
        while(1)
          {
          RedLEDPin::SetOutToggle();
          GreenLEDPin::SetOutToggle();
          _delay_ms(500);
          }
        }*/
       //This should be antistuck??!

       //RedLEDPin::SetOutHigh();
       while(HAL.EnvironmentRarioModule.getState() != Driver_AnoRadRarioModule::TRX_STATE::TRX_STATE_IDLE)
        {
        //Error! It should be IDLE.
        }
      //RedLEDPin::SetOutLow();

			StalkerLayer0.sendPacket();
			//while (RFM22B_PinNIRQ::isPinHigh());// wait for packet sent interrupt (NIRQ goes low)//nahua??!
			//startTX	= false;
			GreenLEDPin::SetOutLow();
			//	}
//			RFM22B_POWER_OFF;
			}
		DeviceAlivePin::SetOutLow();
//		RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, 1<<5);	// to ready mode
		sleep_enable(); // разрешаем сон
		//sleep_bod_disable();
		sleep_cpu(); // спать!
//		sleep
		//delay_ms(100);
		}
	}
void Hack_RcvMayStuckTimer_Reload(void)
	{
	Hack_RcvMayStuckTimer	= HACK_RCV_RESTART_TIMER_VALUE;
	}
void LogClass::Log(MESSAGES msg, uint8_t p1/* =0 */, uint8_t p2/* =0 */, uint8_t p3/* =0 */, uint8_t p4/* =0 */, uint8_t p5/* =0 */, uint8_t p6/* =0 */)
  {

  }
#include "stalker/drivers/Driver_AnoRadRarioModule_RFM23.cpp"
#include "stalker/Class_StalkerLayer0.cpp"
#include "crc16.c"
#include "stalker/HAL.cpp"
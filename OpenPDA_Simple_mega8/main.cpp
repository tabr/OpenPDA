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
//#define delay_ms		_delay_ms
#define SELECTED_BYTE_ORDER   DEF_BYTE_ORDER_LITTLE_ENDIAN

#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("TODO - " #x))
//char RAM_STR_UNDEFINED[]                           = "[undefined]";


#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h> // работа с прерываниями
#include <avr/sleep.h> // здесь описаны режимы сна
#include <avr/power.h>
//#include <util/crc16.h>
#include <avr/pgmspace.h>
#include <string.h>

#include "LogClass.hpp"


#define TEMPORARY_ANORAD_PARAMETER_TYPE					0x00
#define TEMPORARY_ANORAD_PARAMETER_RAD_MULTIPLIER		0x01
#define TEMPORARY_ANORAD_PARAMETER_ANO_TYPE				0x02
#define TEMPORARY_ANORAD_PARAMETER_ANO_SKIP				0x03
#define TEMPORARY_ANORAD_PARAMETER_ANO_KILL				0x04
#define TEMPORARY_ANORAD_PARAMETER_0					0x01
#define TEMPORARY_ANORAD_PARAMETER_1					0x02
#define TEMPORARY_ANORAD_PARAMETER_2					0x03
#define TEMPORARY_ANORAD_PARAMETER_3					0x04

//#define IS_MONOLYTH
//#define IDDQD
//#define START_TEST_LOOP

//#define CRC_TABLE_RAM
/////#define CHOOSEN_ANORAD              6
//#define RFM22B_CHOOSE_TRANSMITTER   1
#define ATMEL_STUDIO				7.0
//#define ANORAD_IN_FLASH             1
//#define LCD_USING					1
//#define DEBUG_USART

#ifdef DEBUG_USART
//	#define DEBUG_USART_STR
	#define DEBUG_USART_CODES
#define DEBUG_USART_CURRENT_LOGLEVEL	DEBUG_USART_LOGLEVEL_DEBUG

#endif //DEBUG_USART

//#define DEBUG_USART_DAMAGE
//#define DEBUG_USART_REVIVE
//#define DEBUG_USART_ENV_PACKETS
//#define DEBUG_USART_ENV_PACKETS_MIN

//////////////////////////////////////////


//#ifdef DEBUG_BUILD
//#warning "DEBUG_BUILD"
//#endif // DEBUG_BUILD
//#ifdef FAKE_ADC_POWER
//#warning "FAKE_ADC_POWER"
//#endif // FAKE_ADC_POWER
#ifdef IDDQD
#warning "IDDQD"
#endif // IDDQD




////////////includes

#include "typedefs.h"

// Voltage Reference: AVCC with external capacitor at AREF pin
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (1<<ADLAR))
#include <stalker/drivers/Driver_IO_mega8a.hpp>

#include <PlayerEffectsInterface.hpp>
#include <DeviceConfigClass.hpp>
#include "src/Debug_USART.hpp"
#include "src/DummyClasses.hpp"
#include "src/LedProcess.hpp"
//PlayerEffect_SafeShelterClass* EffectSafeShelter	= new PlayerEffect_SafeShelterClass(0, 1, 30);//30 sec
#define EffectSafeShelter 0xab

#include "unionsFixed.h"
//#include "stalker/drivers/Driver_IO_mega168pa.h"
#include "pin.h"
#ifdef LCD_USING
	#include "n3310lcd.h"
	#include "stalker/LcdClass.h"
	#include "n3310LcdClass.h"
#endif

#define MEMORYMANAGER_POOL_SIZE 195
//#define MEMORYMANAGER_POOL_SIZE 64
#include <MemoryManager.hpp>
MemoryManagerClass MemoryManager;
#include <cpp_NEW_support.h>
#include <crc16.h>
#include <stalker/TimerClass.hpp>
#include <stalker/drivers/Driver_AnoRadRarioModule_RFM23.hpp>
#include <TimeClass.hpp>

#include "strings.h"

#include "stalker/Class_StalkerLayer1.hpp"
#include "stalker/Class_StalkerLayer2.hpp"
#include "../OpenPDA_ATxmega128A1U/src/InGameEventsClass.hpp"
#include "../OpenPDA_ATxmega128A1U/src/InGameEvent_BlowoutClass.hpp"
#include "../OpenPDA_ATxmega128A1U/src/InGameEvent_RadStormClass.hpp"
#include "../OpenPDA_ATxmega128A1U/src/InGameEvent_SleepTimeClass.hpp"
#include "../OpenPDA_ATxmega128A1U/src/QuestClass.hpp"
#include "../OpenPDA_ATxmega128A1U/src/GameConfig.hpp"
#include "../OpenPDA_ATxmega128A1U/src/TimeUpdateClass.hpp"

#include "src/AnomalySimpleClass.hpp"
#include "src/PlayerEffectsSimpleClass.hpp"
#include "src/PlayerClass.hpp"
#include <ErrorClass.hpp>
#include <LcdStringCopyClass.hpp>
#include "Node.hpp"
#include "src/interrupts.h"

///////////proto
void BuzzerOff(void);
void BuzzerOn(void);
void BuzzerToggle(void);
void BuzzerInit(void);
void BuzzerActivate(uint8_t ms);
void EnterSleepMode(void);
void EnterNormalMode(void);
bool IsInSleepMode(void);
void PlayDeathSound(void);
void Hack_RcvMayStuckTimer_Reload(void);

///////////game defines
#define SAFE_SHELTER_TIMER				7
#define BLOWOUT_DAMAGE					50
#define RADSTORM_DAMAGE					7

///////////vars

volatile uint8_t buzzerOnCounter		= 0;
//volatile uint8_t hui					= 0;
volatile bool oneSecPassed				= false;
char STR_None[]							= "[None]";
uint8_t EffectSafeShelterHack   = 123;
#define HACK_RCV_RESTART_TIMER_VALUE	255
volatile uint8_t Hack_RcvMayStuckTimer	= HACK_RCV_RESTART_TIMER_VALUE;
//int ggg;
//#define HACK_RCV_RESTART Hack_RcvMayStuckTimer	= HACK_RCV_RESTART_TIMER_VALUE

//bool timeSyncReceivedAtLastOnce			= false;
bool killedByTimeSync					= false;
bool killedBySleepEvt					= false;
volatile bool deviseInSleepMode			= false;
uint8_t DeviceID						= 0;
EEMEM uint8_t ee_var;
uint8_t grenadeDelayHackTimer			= 0;
#warning "unimplemented grenadeDelayHackTimer"

uint8_t timeUpdateTimer					= 0;
uint8_t blowoutActivityTimer			= 0;

volatile uint8_t soundDeathStage		= 0;
uint8_t InGameEvent_SleepTimer			= 0;
uint8_t PsyBeepKeepOnHack           = 0;//hack var
EmissionInstanceDetectorDummyClass EmissionInstanceDetector;
SoundDummyClass PDASound;
///////////classes

class GrenadeSimpleClass
  {
  public:
    void ProcessSignal(uint8_t signalPower);
  protected:
  private:
  };

GrenadeSimpleClass Grenade;
TimeClass TimeRTC;
TimerMSClass TimerMS;
Driver_ClockDummy HWClock;
Class_HAL HAL(&HWClock);
//Class_HAL HAL;
InGameEventsClass InGameEvents;
InGameEvent_BlowoutClass BlowoutEvent;
InGameEvent_RadStormClass RadStormEvent;
InGameEvent_SleepTimeClass SleepEvent;
GameConfig GameCFG;
PlayerSimpleClass Player;
ErrorClass Errors;
EnvironmentDummyClass Env;
AnomalySimpleClass Anomaly;
QuestDummyClass Quest;
DeviceConfigClass DeviceConfig;
LcdStringCopyClass LcdStringCopy;
LedProcessClass Led;
PDAMenuDummyClass PDAMenu;
Class_StalkerLayer2 StalkerLayer2;
PlayerEffectsSimpleClass PlayerEffects;
TimeUpdateClass TimeUpdate;


#ifdef LCD_USING
	LcdClass Lcd;
//	n3310LcdClass<n3310Pins> LcdDisplay;
	n3310LcdClass LcdDisplay;
#endif


int main(void)
	{
	//uint8_t txPower=0;
	//uint8_t selectedAnoradData[Class_StalkerLayer2::NUM_PACKET_PARAMETERS];
//	uint8_t greenLedtimer				= 0;
	
	
	//clock_prescale_set(clock_div_2);

	
	//Нельзя обнулять, т.к. клыссы отработали свои конструкторы!
//	DDRD	|= 1<<0 | 1<<1 | 1<<2 | 0<<3 | 0<<4 | 0<<5 | 1<<6 | 0<<7;
//	cbi(DDRD, DDRD3);
//	cbi(DDRD, DDRD4);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
TCCR0=(0<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x00;

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



// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: 7,813 kHz
// Mode: Normal top=0xFF
// OC2 output: Disconnected
// Timer Period: 9,984 ms
ASSR=0<<AS2;
TCCR2=(0<<FOC2) | (0<<COM21) | (0<<COM20) | (0<<WGM21) | (1<<CS22) | (1<<CS21) | (1<<CS20);
//TCCR2=(0<<FOC2) | (0<<COM21) | (0<<COM20) | (0<<WGM21) | (0<<CS22) | (0<<CS21) | (0<<CS20);// now disabled
TCNT2=0xB2; //9,984 ms
//TCNT2=0x00; //32.768 ms
OCR2=0x00;

/*
// Timer/Counter 2 initialization
// Clock source: TOSC1 pin
// Clock value: PCK2/1024
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=1<<AS2;
TCCR2=(0<<FOC2) | (0<<WGM20) | (0<<COM21) | (0<<COM20) | (0<<WGM21) | (1<<CS22) | (1<<CS21) | (1<<CS20);
TCNT2=0x00;
OCR2=0x00;
*/


// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (1<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<TOIE0);


// External Interrupt(s) initialization

// INT0: Off
// INT1: On
// INT1 Mode: Falling Edge
GICR|=(1<<INT1) | (0<<INT0);
MCUCR=(1<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
GIFR=(1<<INTF1) | (0<<INTF0);
/*
// INT0: Off
// INT1: On
// INT1 Mode: Low level
GICR|=(1<<INT1) | (0<<INT0);
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
GIFR=(1<<INTF1) | (0<<INTF0);
*/

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: Off
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud Rate: 19200
//UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (0<<U2X) | (0<<MPCM);
//UCSRB=(0<<RXCIE) | (1<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
//UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
//UBRRH=0x00;
//UBRRL=0x19;

// USART initialization
#ifdef DEBUG_USART
/*
	// Communication Parameters: 8 Data, 1 Stop, No Parity
	// USART Receiver: Off
	// USART Transmitter: On
	// USART Mode: Asynchronous
	// USART Baud Rate: 9600
	UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (1<<U2X) | (0<<MPCM);
	UCSRB=(0<<RXCIE) | (1<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
	UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
	UBRRH=0x00;
	UBRRL=0x33;
*/

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: Off
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud Rate: 25000 (x2 = 50000)
UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (1<<U2X) | (0<<MPCM);

#ifdef DEBUG_USART_CODES //no TXCIE
	UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
#else
	UCSRB=(0<<RXCIE) | (1<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
#endif //DEBUG_USART_CODES

UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
UBRRH=0x00;
//UBRRL=0x13;
UBRRL=0x00;

#else
	// USART disabled
	UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (0<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
#endif //DEBUG_USART

	#ifdef DEBUG_USART_CODES
	USART_SendCode(static_cast<USART_DEBUG_CODES>(10));
	USART_SendCode(static_cast<USART_DEBUG_CODES>(13));
	USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_SYSTEM_STARING);
	#endif // DEBUG_USART_CODES

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
ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADFR) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
SFIOR=(0<<ACME);
/*
// SPI initialization
// SPI disabled
SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);
*/
// TWI initialization
// TWI disabled
TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);

	
	#ifdef LCD_USING
		LcdDisplay.IOInit();
		LcdDisplay.HardwareInitialization();
	#endif


	BuzzerInit();
	RedLEDPin::SetDirOut();
	GreenLEDPin::SetDirOut();
	RedLEDPin::SetOutHigh();
	GreenLEDPin::SetOutHigh();
	DeviceAlivePin::SetDirOut();
	#ifdef LCD_USING
		LCD_LEDPin::SetDirOut();
	#endif
	
	#ifdef LCD_USING
		sprintf (lcd_buf, "runlevel 0");
		LcdString(1,LCD_LINE_1);
		LcdUpdate();
	#endif

	GreenLEDPin::SetOutLow();
	RedLEDPin::SetOutLow();

	//eeprom_write_byte(&ee_var, 100);
/*
	DeviceID = eeprom_read_byte(&ee_var);
	if (DeviceID == 99)
		{
		GreenLEDPin::SetOutHigh();
		while(1);
		}
	else
		{
		RedLEDPin::SetOutHigh();
		while(1);
		}
*/
  //BuzzerOn();


	HAL.IOInit();
	EnterNormalMode();

	wdt_reset();

//	RFM22B_RegisterWrite(RFM22B_REGISTER_0B_GPIO_0_CONFIGURATION,   ((1<<5) | Driver_AnoRadRarioModule::GPIO_FUICTION_SELECT_RX_STATE_OUT));
//	RFM22B_RegisterWrite(RFM22B_REGISTER_0B_GPIO_0_CONFIGURATION,   ((1<<5) | Driver_AnoRadRarioModule::GPIO_FUICTION_SELECT_VALID_PREAMBLE_DETECT_OUT));
	//RFM22B_RegisterWrite(RFM22B_REGISTER_0B_GPIO_0_CONFIGURATION,   ((1<<5) | 0b1110));
	//RFM22B_RegisterWrite(RFM22B_REGISTER_0B_GPIO_0_CONFIGURATION,   ((1<<3) | (1<<4) | (1<<0) | (1<<5)));
	
	
	//sbi(PORTD,4);
	//StalkerLayer0.setID(CHOOSEN_ANORAD);
	//StalkerLayer0.preparePacket();
	//set_sleep_mode(SLEEP_MODE_PWR_SAVE);//ONLY IF  ASYNCRONIOUS, need to be be crystal installed!!!!!
	//#ifdef DEBUG_USART
		set_sleep_mode(SLEEP_MODE_IDLE);
	//#else
	//	set_sleep_mode(SLEEP_MODE_ADC);//INT1 falling enge does not works
	//#endif // DEBUG_USART
	//srand(CHOOSEN_ANORAD);
	//StalkerLayer0.sendPacket();
	//RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, 0);
//	power_timer0_disable();
//	power_timer1_disable();
//	power_twi_disable();



	wdt_enable(WDTO_2S);
	
	#ifdef LCD_USING
		LCD_LEDPin::SetOutHigh();
	#endif
	//InGameEvents.registerNew(10,02, 10,02, 2, BlowoutEvent);
	#include "GameTemplate_Radiomarks.hpp"
	#include "GameTemplate_InGameEvents.hpp"

	asm("sei");
	HAL.EnvironmentRarioModule.receiveBegin();
	//BuzzerPin::SetOutHigh();
	//BuzzerPin_H::SetOutHigh();
	//uint8_t tmpChar=0;
	//char str[]	= "hui\n";
	#ifdef DEBUG_USART_STR
		memset(USARTBuffer,0,TX_BUFFER_SIZE);
	#endif

	TimerMS.RegisterListener(&Player);
	TimerMS.RegisterListener(&StalkerLayer2);
    //start beep
    BuzzerOn();
    _delay_ms(100);
    BuzzerOff();
    _delay_ms(1000);

	RedLEDPin::SetOutLow();
	GreenLEDPin::SetOutLow();

	#ifdef START_TEST_LOOP
	while(1)	
		{ 
		asm("cli");
		wdt_reset();
		GreenLEDPin::SetOutHigh();
		RedLEDPin::SetOutHigh();
		BuzzerOn();
		_delay_ms(100);
		GreenLEDPin::SetOutLow();
		RedLEDPin::SetOutLow();
		BuzzerOff();
		_delay_ms(900);
		}
	#endif //START_TEST_LOOP
	#ifdef DEBUG_USART_STR
		USART_startTX((char*)"[00]start\r\n");
	#endif
	#ifdef DEBUG_USART_CODES
		USART_SendCode(static_cast<USART_DEBUG_CODES>(10));
		USART_SendCode(static_cast<USART_DEBUG_CODES>(13));
		USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_SYSTEM_STARTED);
		USART_SendCode(static_cast<USART_DEBUG_CODES>(10));
		USART_SendCode(static_cast<USART_DEBUG_CODES>(13));
	#endif // DEBUG_USART_CODES
	BuzzerActivate(130);//start beep
	_delay_ms(200);
    while(1)
		{
		#ifdef DEBUG_USART_CODES
      if (USART_DEBUG_CODES::USART_DEBUG_CODE_SYSTEM_ALIVE != 0)
			  USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_SYSTEM_ALIVE, DEBUG_USART_LOGLEVEL_DEBUG);
		#endif // DEBUG_USART_CODES
		//PORTD ^= 1<<6;
		//RedLEDPin::SetOutToggle();
		//TCNT_rand	= rand() % 32;
        //asm("wdr");
		wdt_reset();
		//sbi(PORTD,2);
		DeviceAlivePin::SetOutHigh();
		TimerMS.CheckPassed();
		
		//continue;
		
		if (oneSecPassed)
			{
			oneSecPassed	= false;
			if (Hack_RcvMayStuckTimer == 0)
				{
				HAL.EnvironmentRarioModule.receiveBegin();
				Hack_RcvMayStuckTimer_Reload();
        if(HAL.EnvironmentRarioModule.getState() != Driver_AnoRadRarioModule::TRX_STATE::TRX_STATE_RECEIVING)
          {
          StalkerLayer2.HardwareInitialization();
          HAL.EnvironmentRarioModule.receiveBegin();
          #warning "[T] hack?"
          }
				#ifdef DEBUG_USART_CODES
					USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_RCV_RESTARTED_BY_HACK);
				#endif // DEBUG_USART_CODES
				}

			if (InGameEvent_SleepTimer > 0)
				{
				InGameEvent_SleepTimer--;
				}
			if (TimeUpdate.IsTimeSyncReceivedAtLastOnce() == false)
				{
				#ifdef DEBUG_USART_CODES
  			  USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_TIME_NOT_SYNC);
				#endif // DEBUG_USART_CODES
				if (Player.IsAlive())
					{
					killedByTimeSync	= true;
					//Player.Kill(TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC);
					Player.SetHealth(0);
					//while(1);
					//Player.RenewDeathTimer();
					}
				Player.RenewDeathTimer();
				//while(1);
				}
			else
				{
				if (InGameEvent_SleepTimer > 0)//значит, мы в промежутках сна
					{
					#ifdef DEBUG_USART_CODES
						USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_KIILED_BY_SLEEP_EVT);
					#endif // DEBUG_USART_CODES
					killedBySleepEvt	= true;
					if (Player.IsAlive())
						{
						Player.SetHealth(0);
						BuzzerActivate(250);
						EnterSleepMode();
						#ifdef DEBUG_USART_CODES
							USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_KIILED_BY_SLEEP_EVT1);
						#endif // DEBUG_USART_CODES
						}
					Player.RenewDeathTimer();
					}
				else
					{
					if (killedBySleepEvt)
						{
						#ifdef DEBUG_USART_CODES
							USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_REVIVED_BY_SLEEP_EVT);
						#endif // DEBUG_USART_CODES
						Player.Revive();
						EnterNormalMode();
						Player.Revive();
						killedBySleepEvt	= false;
						}
					}
				}
/*
			#ifdef DEBUG_USART_STR
//				while (tx_counter > 0);//ждем окончания передачи
//				USART_startTX((char*)"[00]hui\r\n");
//				while (tx_counter > 0);//ждем окончания передачи
				//uint8_t* BlowoutParameters=InGameEvents.getParameters(0);
				//uint8_t* Evt1Parameters=InGameEvents.getParameters(1);
				//uint8_t* Evt2Parameters=InGameEvents.getParameters(2);
				//uint8_t* Evt3Parameters=InGameEvents.getParameters(3);
				//sprintf(USARTBuffer, "Time: %02u:%02u:%02u blow(%01u):%02u:%02u %02u:%02u H:%03u(%03u) z:%05u d:%05u alive:%01u SP:%03u nirqLO%01u GP%01d rssiRcv%01u SPIL%01u slp%01u\r\n", TimeRTC.hour, TimeRTC.minute, TimeRTC.second, isBlowoutActive(), BlowoutParameters[InGameEventsClass::PARAMETER_START_H], BlowoutParameters[InGameEventsClass::PARAMETER_START_M], BlowoutParameters[InGameEventsClass::PARAMETER_END_H], BlowoutParameters[InGameEventsClass::PARAMETER_END_M], Player.GetCurrentHealth(), Player.GetHealthPercent(), Player.GetZombieTimeRemain(), Player.GetDeathTimeRemain(),  Player.isAlive(), StalkerLayer2.L1.L0.SignalPower, RFM22B_PinNIRQ::isPinLow(), StalkerLayer2.L1.L0.isGoodPacketReceived(), HAL.EnvironmentRarioModule.RSSIReceived, SPILocked, IsInSleepMode());
				
				sprintf(USARTBuffer, "%02u:%02u:%02u h%03u rssi%03u %01u %01u %01u %03u\r\n", TimeRTC.GetHour(), TimeRTC.GetMinute(), TimeRTC.GetSecond(), hui, HAL.EnvironmentRarioModule.globalRSSI, HAL.EnvironmentRarioModule.isPacketReceived(), SPILockedByInterupt, SPILockedByMain, HAL.EnvironmentRarioModule.RXState);
				USART_startTX(strlen(USARTBuffer));
//				sprintf(USARTBuffer, "Time: %05u %05u %05u\r\n", TimeRTC.AsMinutesPassed(), TimeRTC.AsMinutesPassed(Evt1Parameters[InGameEventsClass::PARAMETER_START_H], Evt1Parameters[InGameEventsClass::PARAMETER_START_M]), TimeRTC.AsMinutesPassed(Evt1Parameters[InGameEventsClass::PARAMETER_END_H], Evt1Parameters[InGameEventsClass::PARAMETER_END_M]));
//				USART_startTX(strlen(USARTBuffer));
				timeUpdateTimer=0;
			#endif // DEBUG_USART
*/
			TimeRTC.IncrementSeconds();//обрабатываю время
			
			if (timeUpdateTimer > 0)//Таймер обновления времени
				{
				--timeUpdateTimer;
				}
			
			if (blowoutActivityTimer > 0)//таймер выброса, чтобы смотреть, когда он закончится
				{
				if (--blowoutActivityTimer == 0)
					{
					RedLEDPin::SetOutLow();
					BuzzerOff();
					}
				}
			
			Led.Process();
			InGameEvents.checkState(); //игровые события, упрощённо
			
			//Player.oneSecondPassed();
			}
		#ifdef LCD_USING
//			vasya	= vasya/9;
//			sprintf (lcd_buf, "[%01u%01u %03d]", SPILocked, HAL.EnvironmentRarioModule.RSSIReceived, (rand() & 255));
			sprintf (lcd_buf, "[%01u%01u%01u%01u%01u %03d]", SPILocked, HAL.EnvironmentRarioModule.RSSIReceived, RFM22B_PinNIRQ::isPinLow(), isPlayerAlive(), isLastAggressorPsy, test);
			LcdString(1,LCD_LINE_1);
		#endif
/*
		if (isPacketShouldProcess() && !SPILocked && RFM22B_PinNIRQ::isPinLow())
			{
			//sprintf(USARTBuffer, "packet arrived\r\n");
			//USART_startTX(strlen(USARTBuffer));
			SPILocked	= true;
			if (!HAL.EnvironmentRarioModule.RSSIReceived)
				{
				HAL.EnvironmentRarioModule.globalRSSI			= HAL.EnvironmentRarioModule.fetchRSSIRaw();
				}
			//packetProcessCounter-=10;//10 == 100ms
			PacketProcessed();
			//StalkerLayer2.EnvironmentProcess();
			StalkerLayer2.EnvironmentLookAround();
*/
			//sprintf (lcd_buf, "[1]");LcdString(1,LCD_LINE_1);
/*
//			if (StalkerLayer0.checkEnvironmentPacketAcception())
			if (StalkerLayer1.isEnvironmentActive())
				{
				//sprintf (lcd_buf, "[2]");LcdString(1,LCD_LINE_1);
				//uint8_t *packet	= StalkerLayer1.L0.packetContainer;
				//PORTD^=1<<6;
				//const uint8_t *AD			= anoradData[StalkerLayer1.getReceivedEnvPacketID()];
				RadiomarkInstanceClass* selectedRadiomark	= GameCFG.Radiomarks.GetFromID(StalkerLayer1.getReceivedEnvPacketID());
				uint8_t SignalPower			= StalkerLayer1.L0.SignalPower;
				isLastAggressorPsy			= false;

				switch (selectedRadiomark->GetType())
					{
					case RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY:
						{
						RadiomarkRadiationAnomayClass RadAno	= RadiomarkRadiationAnomayClass(selectedRadiomark);
						//if (isPlayerAlive())
						if (Player.isAlive())
							{
							if (RadAno.GetRadiationMultiplier() > 0)
								{
								uint16_t itmp	= RadAno.GetRadiationMultiplier() * SignalPower;//multiplier * [rssi/2]
								if (itmp> 255)
									{
									itmp=255;
									}
								//PlayerHealthDecrease(itmp);
								Player.DealSimpleDamage(itmp);
								}
							if (RadAno.GetAnomalyType() > 0)
								{
								if (SignalPower > RadAno.GetAnomalyKillLevel())
									{
									//PlayerDie();
									Player.Die();
									}
								else if (SignalPower > RadAno.GetAnomalySkipLevel())
									{
									//PlayerHealthDecrease ((SignalPower-selectedAnoradData[ANORAD_PARAMETER_ANO_SKIP]));
									Player.DealSimpleDamage((SignalPower-RadAno.GetAnomalySkipLevel()));
									}
								}
							}
						}
					break;
					
					case RadiomarkInstanceClass::RADIOMARK_TYPE_PSY:
						{
						//if (isPlayerAlive())
						if (Player.isAlive())
							{
							isLastAggressorPsy	= true;
							//PlayerHealthDecrease(SignalPower);
							Player.DealSimpleDamage(SignalPower);
							}
						}
					break;
					
					case RadiomarkInstanceClass::RADIOMARK_TYPE_REVIVE:
						{
						//if (isPlayerDead)
						if (Player.isDead())
							{
							//PlayerRevive();
							Player.Revive();
							}
						}
					break;
					
					case RadiomarkInstanceClass::RADIOMARK_TYPE_SAFE_ZONE:
					case RadiomarkInstanceClass::RADIOMARK_TYPE_SAFE_SHELTER:
						{
						//PlayerInSafeShelterTimer	= SAFE_SHELTER_TIMER;
						Player.SetInSafeZone(true);
						}
					break;
					}
				#ifdef LCD_USING
					sprintf (lcd_buf, "%03d %03d %03d,%1u%1u", HAL.EnvironmentRarioModule.getRSSIRaw(), StalkerLayer1.L0.RSSIRaw, StalkerLayer1.L0.SignalPower, SPILocked, HAL.EnvironmentRarioModule.RSSIReceived);
					LcdString(1,LCD_LINE_2);
//					sprintf (lcd_buf, "%03u%03u  %03u%03u", selectedAnoradData[0], selectedAnoradData[1], selectedAnoradData[2], selectedAnoradData[3]);
//					LcdString(1,LCD_LINE_3);
				#endif
				StalkerLayer1.L0.packetProcessed();
				}
*/
/*
			//sprintf (lcd_buf, "[3]");LcdString(1,LCD_LINE_1);
			HAL.EnvironmentRarioModule.RSSIReceived	= false;
			//StalkerLayer0.receiveBegin();//TODO: это уже есть в "checkEnvironmentPacketAcception"
			//sprintf (lcd_buf, "[4]");LcdString(1,LCD_LINE_1);
			SPILocked		= false;
			}
*/
		

		/*if ((PIND & 1<<4) == 0)
			{
			if ((RFM22B_getStatus() & Driver_AnoRadRarioModule::STATUS_STATE_RX) == 0 && StalkerLayer0.isGoodPacketReceived	== false)
				{
				StalkerLayer0.getEnvPacketAndRSSI();
				if (StalkerLayer0.checkReceivedPacketCRC())
					{
					PORTD^=1<<6;
					
					//sbi(PORTD,6);
					//uint8_t *packet	= anoradData
					//_delay_ms(1000);
					//cbi(PORTD,6);
					}
				HAL.EnvironmentRarioModule.receiveBegin();
				}
			}*/
		//if (HAL.EnvironmentRarioModule.isPacketReceived())
		/*if (RFM22B_PinGPIO0::isPinLow())
		{
			if ((RFM22B_getStatus() & Driver_AnoRadRarioModule::STATUS_STATE_RX) == 0)
			{
			//		radio.receivePacket();
			//		radio.receiveBegin();
			StalkerLayer0.getEnvPacketAndRSSI();
			StalkerLayer0.receiveBegin();
			if (StalkerLayer0.checkReceivedPacketCRC())
				{
				StalkerLayer0.isGoodPacketReceived	= true;
				PORTD^=1<<6;
				}
			}
		}*/
		/*if (startTX == true)
			{
			PORTD ^= 1<<3;
//			TCNT2=TCNT_VALUE+(rand() % 32);
			StalkerLayer0.sendPacket();
			startTX	= false;
//			RFM22B_POWER_OFF;
			}*/
		//cbi(PORTD,2);
		DeviceAlivePin::SetOutLow();
//		RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, 1<<5);	// to ready mode
		sleep_enable(); // разрешаем сон
//		sleep_bod_disable();
		//power_all_disable();

		sleep_cpu(); // спать!
		sleep_disable();
//		sleep
		//delay_ms(100);
		}
	}
//////////////<-main
//////////////func->
void InGameEvent_BlowoutClass::Task (void)
	{
	blowoutActivityTimer=5;
//	if (isPlayerAlive() && !isPlayerZombie())
//	if (Player.IsAlive() && !(Player.IsZombie()))
	if (Player.IsAlive())
		{
		RedLEDPin::SetOutHigh();
//		if (isPlayerInSafeShelter())//safe shelter effect
		if (Player.IsInSafeZone())//safe shelter effect
			{
		
			}
		else
			{
//			USART_startTX((char*)"1\r\n");
			//PlayerHealthDecrease(BLOWOUT_DAMAGE);
			Player.DealDamage({value:BLOWOUT_DAMAGE, damageSource:TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT});
//      if (Player.IsAlive())
      #ifdef DEBUG_USART_CODES
        USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_BLOWOUT_DAMAGE);
      #endif // DEBUG_USART_CODES
      //Player.Revive();
      //uint16_t hp  = Player.GetCurrentHealth();
      /*if (hp > 100)
        {
        while(1);
        }*/
      /*
      USART_SendCode((uint8_t)*"(");
      //USART_SendCode((uint8_t)*"0" + 1);
      USART_SendCode((uint8_t)*"0" + (hp/100));
      hp  = hp%100;
      USART_SendCode((uint8_t)*"0" + (hp/10));
      hp  = hp%10;
      USART_SendCode((uint8_t)*"0" + hp);
      USART_SendCode((uint8_t)*")");
      */
      //Player.Kill(TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT);
			}
		}
	}
void InGameEvent_RadStormClass::Task (void)
	{
	blowoutActivityTimer=5;
//  zzz({value:1,src:DamageSource_t::DAMAGE_SOURCE_GENERIC});
//  zzz({m_value:1,m_damageSource:DamageSource_t::DAMAGE_SOURCE_GENERIC,m_aggressorSource:DamageClass::AGGRESSOR_SOURCE::AGGRESSOR_SOURCE_EXTERNAL});
//	if (isPlayerAlive() && !isPlayerZombie())
	if (Player.IsAlive() & !(Player.IsZombie()))
		{
		RedLEDPin::SetOutHigh();
//		if (isPlayerInSafeShelter())//safe shelter effect
		if (Player.IsInSafeZone())//safe shelter effect
			{
			
			}
		else
			{
//			USART_startTX((char*)"1\r\n");
			//PlayerHealthDecrease(BLOWOUT_DAMAGE);
			Player.DealDamage({value:RADSTORM_DAMAGE, damageSource:TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT});
			}
		}
	}
void InGameEvent_SleepTimeClass::Task (void)
	{
	InGameEvent_SleepTimer=5;
	};


void EnvironmentDummyClass::RadLevelSetFilter(uint8_t value)
	{
//	USART_startTX((char*)"[Environment::RadLevelSetFilter]\r\n");
	//if (value >= 32)
	//Player.DealSimpleDamage(value, TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL);
  Player.DealDamage({value:value, damageSource:TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL});
	}
void EnvironmentDummyClass::setPsyLevelFilter(uint8_t value)
	{
//	USART_startTX((char*)"[Environment::setPsyLevelFilter]\r\n");
	//Player.DealSimpleDamage(value, TemporaryClass::DamageSource::DAMAGE_SOURCE_PSY);
  Player.DealDamage({value:value, damageSource:TemporaryClass::DamageSource::DAMAGE_SOURCE_PSY});
	}
void EnterSleepMode(void)
	{
	deviseInSleepMode = true;
	}
void EnterNormalMode(void)
	{
	deviseInSleepMode = false;
	StalkerLayer2.HardwareInitialization();
	
	if (!StalkerLayer2.L1.L0.isModuleReadyToWork())
		{
		while (1)
			{
			RedLEDPin::SetOutToggle();
			_delay_ms(100);
			}
		}
	RFM22B_RegisterWrite(RFM22B_REGISTER_0B_GPIO_0_CONFIGURATION,   ((1<<5) | Driver_AnoRadRarioModule::GPIO_FUICTION_SELECT_VALID_PREAMBLE_DETECT_OUT));
	StalkerLayer2.L1.L0.packetProcessed();
	HAL.EnvironmentRarioModule.receiveBegin();
	}
bool IsInSleepMode(void)
	{
	return deviseInSleepMode;
	}

bool DeviceConfigClass::IsAddressedToMe(DeviceID_t DID)
	{
	if (DID == 0xFF)
		{
		return true;
		}
	return false;
	}
void BuzzerInit(void)
	{
	BuzzerPin::SetDirOut();
	BuzzerPin_H::SetDirOut();

	BuzzerOff();
	}
void BuzzerOn(void)
	{
	BuzzerPin::SetOutHigh();
	BuzzerPin_H::SetOutHigh();
	}
void BuzzerOff(void)
	{
	BuzzerPin::SetOutLow();
	BuzzerPin_H::SetOutLow();
	}
void BuzzerToggle(void)
	{
	BuzzerPin::SetOutToggle();
	BuzzerPin_H::SetOutToggle();
	}
void BuzzerActivate(uint8_t ms)
	{
	BuzzerOn();
	buzzerOnCounter	= (ms/10);
	}
bool isBlowoutActive(void)
	{
	return (blowoutActivityTimer > 0);
	}
void PlayDeathSound(void)
	{
	soundDeathStage=1;
	}
void Hack_RcvMayStuckTimer_Reload(void)
	{
	Hack_RcvMayStuckTimer	= HACK_RCV_RESTART_TIMER_VALUE;
	}
#include "stalker/drivers/Driver_AnoRadRarioModule_RFM23.cpp"
#include "stalker/Class_StalkerLayer0.cpp"
#ifdef LCD_USING
#include "n3310lcd.c"
#endif
#include "stalker/Class_StalkerLayer1.cpp"
#include "stalker/Class_StalkerLayer2.cpp"
#include "../OpenPDA_ATxmega128A1U/src/InGameEventsClass.cpp"

#include "../OpenPDA_ATxmega128A1U/src/Items.cpp"
#include "../OpenPDA_ATxmega128A1U/src/ArtefactClass.cpp"

#include "crc16.c"
#include "src/LedProcess.cpp"
#include "src/PlayerClass.cpp"
#include "MemoryManager.cpp"
#include "../OpenPDA_ATxmega128A1U/src/GameConfig.cpp"
//#include "../OpenPDA_ATxmega128A1U/src/ErrorClass.cpp"
#include "stalker/TimerClass.cpp"
#include <ErrorClass.cpp>
#include "../OpenPDA_ATxmega128A1U\src\SuitsContainerClass.cpp"
#include "../OpenPDA_ATxmega128A1U\src\Suits.cpp"
#include "../OpenPDA_ATxmega128A1U\src\FactionsClass.cpp"
#include "src/interrupts.c"
#include "src/PlayerEffectsSimpleClass.cpp"
#include "src/AnomalySimpleClass.cpp"
#include "stalker/HAL.cpp"
#include "../OpenPDA_ATxmega128A1U/src/TimeUpdateClass.cpp"
#include <RadiomarkClass.cpp>
#include "PlayerEffectsInterface.cpp"


#warning "need to finish bellow!"
void GrenadeSimpleClass::ProcessSignal(uint8_t signalPower)
  {
    
  }
void LogClass::Log(MESSAGES msg, uint8_t p1/* =0 */, uint8_t p2/* =0 */, uint8_t p3/* =0 */, uint8_t p4/* =0 */, uint8_t p5/* =0 */, uint8_t p6/* =0 */)
  {

  }
#ifndef DRIVER_IO_H
#define DRIVER_IO_H

#include <stdint.h>
#include <stddef.h>
#include <avr/io.h>

#include "typedefs.h"

typedef uint8_t IOPin;
typedef PORT_t IOPort;
//#define (*(PORT_t *)) IOPort;

//uintptr_t	zzz	= IOPORTC_ADDR;
//template <uint16_t selectedPort, uint8_t selectedPin>
//(*(PORT_t *) IOPORTC).OUTSET	= 1<<1;
//PORTC;
//namespace ZZZ
//{

//template <uintptr_t portAddr, uint8_t selectedPin>
/*struct  
	{
	uintptr_t portAddr;
	uint8_t selectedPin;
//	(portAddr)portAddr;
	} DriverIO_PortStruct;*/

//#define IOPORTA_ADDR			(uintptr_t)&PORTA //0x0600  /* I/O Ports */
//#define IOPORTB_ADDR			(uintptr_t)&PORTB //0x0620  /* I/O Ports */
//#define IOPORTC_ADDR			(uintptr_t)&PORTC //0x0640  /* I/O Ports */
//#define IOPORTD_ADDR			(uintptr_t)&PORTD //0x0660  /* I/O Ports */
//#define IOPORTE_ADDR			(uintptr_t)&PORTE //0x0680  /* I/O Ports */
//#define IOPORTF_ADDR			(uintptr_t)&PORTF //0x06A0  /* I/O Ports */
//#define IOPORTH_ADDR			(uintptr_t)&PORTH //0x06E0  /* I/O Ports */
//#define IOPORTJ_ADDR			(uintptr_t)&PORTJ //0x0700  /* I/O Ports */
//#define IOPORTK_ADDR			(uintptr_t)&PORTK //0x0720  /* I/O Ports */
//#define IOPORTQ_ADDR			(uintptr_t)&PORTQ //0x07C0  /* I/O Ports */
//#define IOPORTR_ADDR			(uintptr_t)&PORTR //0x07E0  /* I/O Ports */

/*
//специализация шаблона(оставить на будущее):
template< uintptr_t portAddr, uint8_t pin> class Driver_IO_Pin_PULLUP {};
template< uintptr_t portAddr> class Driver_IO_Pin_PULLUP< portAddr,0 >
	{
	public:
	static void pullup()
		{
		((PORT_t*)portAddr)->PIN0CTRL	= PORT_OPC_PULLUP_gc;
		}
	
	};
template< uintptr_t portAddr> class Driver_IO_Pin_PULLUP< portAddr,1 >
	{
	public:
	static void pullup()
		{
		((PORT_t*)portAddr)->PIN1CTRL	= PORT_OPC_PULLUP_gc;
		}
	
	};
template< uintptr_t portAddr> class Driver_IO_Pin_PULLUP< portAddr,5 >
	{
	public:
	static void pullup()
		{
		((PORT_t*)portAddr)->PIN5CTRL	= PORT_OPC_PULLUP_gc;
		}
	
	};
*/
//auto a=1;
/*
template <uintptr_t portAddr, uint8_t selectedPin>
class Driver_IO_Pin1
	{
		
	};
//typedef Driver_IO_Pin1<PORTA, 4> asdasd;
#define Driver_IO_Pin1HACK(port,pin) Driver_IO_Pin1<(uintptr_t)&port, pin>
//typedef Driver_IO_Pin1<(uintptr_t)&PORTA, 1>
//Driver_IO_Pin1HACK(PORTA, 1);

//typedef Driver_IO_Pin1<IOPORTC_ADDR, 4> aaasss;
typedef Driver_IO_Pin1HACK(PORTA,1) sssddd;
*/
//template <PORT_t T>
//class TestClass
//	{
	//T.DIR=1;
//	};

template <volatile uintptr_t portAddr, uint8_t selectedPin>
class Driver_IO_PinClass
	{
	private:
		constexpr static PORT_t* GetPort()
			{
			return (PORT_t*)portAddr;
			}
	public:
		static void SetOutHigh()
			{
			GetPort()->OUTSET	= 1<<selectedPin;
			}
		static void SetOutLow()
			{
			GetPort()->OUTCLR	= 1<<selectedPin;
			}
		static void SetOutToggle()
			{
			GetPort()->OUTTGL	= 1<<selectedPin;
			}
		static void SetDirOut()
			{
			GetPort()->DIRSET	= 1<<selectedPin;
			/*
			if (selectedPin == 0)
			GetPort()->PIN0CTRL	= PORT_OPC_TOTEM_gc;
			else if (selectedPin == 1)
			GetPort()->PIN1CTRL	= PORT_OPC_TOTEM_gc;
			else if (selectedPin == 2)
			GetPort()->PIN2CTRL	= PORT_OPC_TOTEM_gc;
			else if (selectedPin == 3)
			GetPort()->PIN3CTRL	= PORT_OPC_TOTEM_gc;
			else if (selectedPin == 4)
			GetPort()->PIN4CTRL	= PORT_OPC_TOTEM_gc;
			else if (selectedPin == 5)
			GetPort()->PIN5CTRL	= PORT_OPC_TOTEM_gc;
			else if (selectedPin == 6)
			GetPort()->PIN6CTRL	= PORT_OPC_TOTEM_gc;
			else if (selectedPin == 7)
			GetPort()->PIN7CTRL	= PORT_OPC_TOTEM_gc;
			*/
			}
		static void SetDirIn()
			{
			GetPort()->DIRCLR	= 1<<selectedPin;
			/*
			if (selectedPin == 0)
			GetPort()->PIN0CTRL	= PORT_OPC_TOTEM_gc;
			else if (selectedPin == 1)
			GetPort()->PIN1CTRL	= PORT_OPC_TOTEM_gc;
			else if (selectedPin == 2)
			GetPort()->PIN2CTRL	= PORT_OPC_TOTEM_gc;
			else if (selectedPin == 3)
			GetPort()->PIN3CTRL	= PORT_OPC_TOTEM_gc;
			else if (selectedPin == 4)
			GetPort()->PIN4CTRL	= PORT_OPC_TOTEM_gc;
			else if (selectedPin == 5)
			GetPort()->PIN5CTRL	= PORT_OPC_TOTEM_gc;
			else if (selectedPin == 6)
			GetPort()->PIN6CTRL	= PORT_OPC_TOTEM_gc;
			else if (selectedPin == 7)
			GetPort()->PIN7CTRL	= PORT_OPC_TOTEM_gc;
			*/
			}
		static bool IsPinHigh ()
			{
			return GetPort()->IN & 1<<selectedPin;
			}
		static bool IsPinLow ()
			{
			return (GetPort()->IN & 1<<selectedPin) == 0;
			}
//		template<>
//		static void test<1> ()
//			{
//			
//			}
		static void SetPullUp ()//TODO: шаблоны бля!!!
			{
			//Driver_IO_Pin_PULLUP<portAddr,selectedPin>::pullup();
			if (selectedPin == 0)
				GetPort()->PIN0CTRL	= PORT_OPC_PULLUP_gc;
			else if (selectedPin == 1)
				GetPort()->PIN1CTRL	= PORT_OPC_PULLUP_gc;
			else if (selectedPin == 2)
				GetPort()->PIN2CTRL	= PORT_OPC_PULLUP_gc;
			else if (selectedPin == 3)
				GetPort()->PIN3CTRL	= PORT_OPC_PULLUP_gc;
			else if (selectedPin == 4)
				GetPort()->PIN4CTRL	= PORT_OPC_PULLUP_gc;
			else if (selectedPin == 5)
				GetPort()->PIN5CTRL	= PORT_OPC_PULLUP_gc;
			else if (selectedPin == 6)
				GetPort()->PIN6CTRL	= PORT_OPC_PULLUP_gc;
			else if (selectedPin == 7)
				GetPort()->PIN7CTRL	= PORT_OPC_PULLUP_gc;
			
			}
		static void SetPullDown ()//TODO: шаблоны бля!!!
			{
			//Driver_IO_Pin_PULLUP<portAddr,selectedPin>::pullup();
			if (selectedPin == 0)
				GetPort()->PIN0CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (selectedPin == 1)
				GetPort()->PIN1CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (selectedPin == 2)
				GetPort()->PIN2CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (selectedPin == 3)
				GetPort()->PIN3CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (selectedPin == 4)
				GetPort()->PIN4CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (selectedPin == 5)
				GetPort()->PIN5CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (selectedPin == 6)
				GetPort()->PIN6CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (selectedPin == 7)
				GetPort()->PIN7CTRL	= PORT_OPC_PULLDOWN_gc;
			
			}
	};

template <uintptr_t spiAddr, volatile uintptr_t portAddr, uint8_t selectedPin>
//template <uintptr_t spiAddr, class PIN>
class Driver_IO_SPIClass
	{
	public:
		static void SendRequest (uint8_t* data, uint16_t length)
			{
			for (uint16_t i=0;i<length;i++)
				{
				Send(data[i]);
				}
			}
		static void Communicate(uint8_t request, uint8_t* answer=NULL, uint16_t answerLength=0)
			{
			ActivateDevice();
			Send(request);
			if (answerLength > 0)
				{
				ReadPacket (answer, answerLength);
				}
			DeactivateDevice();
			}
		static void Communicate(uint8_t* requestArray, uint8_t requestLength, uint8_t* answer=NULL, uint16_t answerLength=0)
			{
			ActivateDevice();
			if (requestLength > 0)
				{
				SendRequest(requestArray, requestLength);
				}
			if (answerLength > 0)
				{
				ReadPacket (answer, answerLength);
				}
			DeactivateDevice();
			}
		static uint8_t Send(uint8_t byte)
			{
			//Driver_IO_PinClass<portAddr, selectedPin>::SetOutHigh();
			getSPI()->DATA	= byte;
			while (!(getSPI()->STATUS & SPI_IF_bm))
				{
				}        //Wait Interrupt
			return getSPI()->DATA;
			}
		static void ActivateDevice(void)
			{
			Driver_IO_PinClass<portAddr, selectedPin>::SetOutLow();
			//PIN::SetOutLow();
			}
		static void DeactivateDevice(void)
			{
			Driver_IO_PinClass<portAddr, selectedPin>::SetOutHigh();
			//PIN::SetOutHigh();
			}
		static void ReadPacket(uint8_t* data, uint16_t length)
			{
			for (uint16_t i=0;i<length;i++)
				{
				data[i]	= Send(0);
				}
			}
	protected:
	private:
		constexpr static SPI_t* getSPI()
			{
			return (SPI_t*)spiAddr;
			}
	};


template <uintptr_t twiAddr, TWI_Data_t deviceSlaveAddress, uint16_t interfaceSpeedKhz>
class Driver_IO_TWIClass
	{
	public:
		const static uint8_t BIT_READ		= 0x01;

		static bool beginTransmission(void)
			{
			uint8_t j=0;
			getTWI()->MASTER.ADDR = deviceSlaveAddress;// & ~0x01;
			while (!(getTWI()->MASTER.STATUS & TWI_MASTER_WIF_bm))
				{
				if (++j == 64)//32 - малоб 48 - норм
					{
					twi_stop();
					return false;
					}
				_delay_us(1);
				}
			return true;
			}
		static bool sendByte(TWI_Data_t data)
			{
			uint8_t j=0;
			getTWI()->MASTER.DATA = data;
			while (!(getTWI()->MASTER.STATUS & TWI_MASTER_WIF_bm))
				{
				if (++j == 96)//64 - малоб 70 - норм
					{
					twi_stop();
					return false;
					}
				_delay_us(1);
				}
//			this->twi_stop();
			return true;
			}
		static void requestRead(void)
			{
			getTWI()->MASTER.ADDR		= deviceSlaveAddress | BIT_READ;
			getTWI()->MASTER.STATUS		|= TWI_MASTER_RIF_bm;
			getTWI()->MASTER.CTRLC		= TWI_MASTER_CMD_RECVTRANS_gc;
			}
		static bool writeToDevice(uint8_t deviceAddress, uint8_t bytesToWrite, uint8_t *writeData)
			{
			beginTransmission();
			sendByte(deviceAddress);
			for(uint8_t i=0;i<bytesToWrite;i++)
				{
				sendByte(writeData[i]);
				}
			twi_stop();
			return true;
			}
		static bool writeToDevice(uint8_t deviceAddressH,uint8_t deviceAddressL, uint16_t bytesToWrite, uint8_t *writeData)
			{
			beginTransmission();
			sendByte(deviceAddressH);
			sendByte(deviceAddressL);
			for(uint16_t i=0;i<bytesToWrite;i++)
				{
				sendByte(writeData[i]);
				}
			twi_stop();
			return true;
			}
		static bool readFromDevice(uint8_t registerAddress, uint8_t bytesToRead, uint8_t *readData)
			{
			beginTransmission();
			sendByte(registerAddress);
			requestRead();
			for(uint8_t i=0;i<bytesToRead;i++)
				{// read date and time
				readData[i]	= readByte();
				}
			twi_stop();
			return true;
			
			}
		static bool readFromDevice(uint8_t registerAddressH, uint8_t registerAddressL, uint16_t bytesToRead, uint8_t *readData)
			{
			if (!(beginTransmission()))
				{
				return false;
				}
			sendByte(registerAddressH);
			sendByte(registerAddressL);
			requestRead();
			for(uint16_t i=0;i<bytesToRead;i++)
				{// read date and time
				readData[i]	= readByte();
				}
			twi_stop();
			return true;
			
			}
		static uint8_t readByte(void)
			{
			uint8_t j=0;
			while(!(getTWI()->MASTER.STATUS&TWI_MASTER_RIF_bm))
				{
				if (++j == 96)//64 - малоб 70 - норм
					{
					twi_stop();
					return 0;
					}
				_delay_us(1);
				}
			return getTWI()->MASTER.DATA;
			}
		static void twi_stop(void)
			{
			getTWI()->MASTER.CTRLC = (TWI_MASTER_ACKACT_bm | TWI_MASTER_CMD_STOP_gc);
			}
		static void HardwareInitialization(void)
			{
			getTWI()->MASTER.CTRLB		= TWI_MASTER_SMEN_bm; //-V807
			getTWI()->MASTER.BAUD		= ((F_CPU / ((uint32_t)2 * interfaceSpeedKhz * 1000)) - 5);
			getTWI()->MASTER.CTRLA		= TWI_MASTER_ENABLE_bm;
			getTWI()->MASTER.STATUS		= TWI_MASTER_BUSSTATE_IDLE_gc;
			
			twi_stop();
			}
	protected:
	private:
		constexpr static TWI_t* getTWI()
			{
			return (TWI_t*)twiAddr;
			}
	};


#define Driver_IO_Pin(port,pin) Driver_IO_PinClass<reinterpret_cast<uintptr_t>((volatile uintptr_t)0 + &port), pin>

#define Driver_IO_SPI(spi,port,pin) Driver_IO_SPIClass<reinterpret_cast<uintptr_t>((uintptr_t)0 + &spi),reinterpret_cast<uintptr_t>((volatile uintptr_t)0 + &port), pin>
//#define Driver_IO_SPI(spi,PIN) Driver_IO_SPIClass<reinterpret_cast<uintptr_t>((uintptr_t)0 + &spi), PIN>
#define Driver_IO_TWI(twi, deviceSlaveAddress, interfaceSpeedKhz) Driver_IO_TWIClass<reinterpret_cast<uintptr_t>((uintptr_t)0 + &twi), deviceSlaveAddress, interfaceSpeedKhz>
/*
template< uintptr_t portAddr> class Driver_IO_Pin< portAddr,2 >
	{
	void test2()
		{
		
		}
	};
*/
/*
template< uintptr_t portAddr, uint8_t selectedPin> class Driver_IO_Pin<portAddr, 1>
{
	static void zzz()
		{
		((PORT_t*)portAddr).PIN1CTRL	= PORT_OPC_PULLUP_gc;
		}
};*/

/*
template <uintptr_t portAddr, uint8_t selectedPin>
void Driver_IO_Pin<portAddr, 1>::test(void)
	{
	((PORT_t*)portAddr).PIN1CTRL	= 1;
	}
*/
/*
class Driver_IO_Pin
	{
	public:
		const static PORT_t *port	= PORTB;
//		static PORT_t port;
		IOPin pin;
		Driver_IO_Pin()
			{
			this->port	= &PORTB;
			}
		Driver_IO_Pin(IOPort &port, IOPin pin)
			{
			this->port	= &port;
			this->pin	= pin;
			}
		void SetDirOut ()
			{
			this->port->DIRSET	= 1<<this->pin;
			}
		void SetDirIn ()
			{
			this->port->DIRCLR	= 1<<this->pin;
			}
		void SetOutToggle ()
			{
			this->port->OUTTGL	= 1<<this->pin;
			}
		void SetOutHigh ()
			{
			this->port->OUTSET	= 1<<this->pin;
			}
		void SetOutLow ()
			{
			this->port->OUTCLR	=1<<this->pin;
			}
		bool IsPinHigh ()
			{
			return port->IN & 1<<this->pin;
			}
		bool IsPinLow ()
			{
			return (this->port->IN & 1<<this->pin) == 0;
			}
		void SetPullUp ()
			{
			if (this->pin == 0)
				this->port->PIN0CTRL	= PORT_OPC_PULLUP_gc;
			else if (this->pin == 1)
				this->port->PIN1CTRL	= PORT_OPC_PULLUP_gc;
			else if (this->pin == 2)
				this->port->PIN2CTRL	= PORT_OPC_PULLUP_gc;
			else if (this->pin == 3)
				this->port->PIN3CTRL	= PORT_OPC_PULLUP_gc;
			else if (this->pin == 4)
				this->port->PIN4CTRL	= PORT_OPC_PULLUP_gc;
			else if (this->pin == 5)
				this->port->PIN5CTRL	= PORT_OPC_PULLUP_gc;
			else if (this->pin == 6)
				this->port->PIN6CTRL	= PORT_OPC_PULLUP_gc;
			else if (this->pin == 7)
				this->port->PIN7CTRL	= PORT_OPC_PULLUP_gc;
			}
		void SetPullDown ()
			{
			if (this->pin == 0)
				this->port->PIN0CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (this->pin == 1)
				this->port->PIN1CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (this->pin == 2)
				this->port->PIN2CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (this->pin == 3)
				this->port->PIN3CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (this->pin == 4)
				this->port->PIN4CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (this->pin == 5)
				this->port->PIN5CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (this->pin == 6)
				this->port->PIN6CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (this->pin == 7)
				this->port->PIN7CTRL	= PORT_OPC_PULLDOWN_gc;
			}
	};
*/
//const PORT_t Driver_IO_Pin::port	= (PORT_t)PORTB;
//Driver_IO_Pin IOTest(PORTB, 1);
//PORTB;
/*
class Driver_IO
	{
	public:
		const static uint8_t PB0		= 0;// PB0
		const static uint8_t PB1		= 1;// PB1
		const static uint8_t PB2		= 2;// PB2
		const static uint8_t PB3		= 3;// PB3
		const static uint8_t PB4		= 4;// PB4
		const static uint8_t PB5		= 5;// PB5
		const static uint8_t PB6		= 6;// PB6
		const static uint8_t PB7		= 7;// PB7
		const static uint8_t PC0		= 8;// PC0
		const static uint8_t PC1		= 9;// PC1
		const static uint8_t PC2		= 10;//PC2
		const static uint8_t PC3		= 11;//PC3
		const static uint8_t PC4		= 12;//PC4
		const static uint8_t PC5		= 13;//PC5
		const static uint8_t PC6		= 14;//PC6
		const static uint8_t PC7		= 15;//PC7
		const static uint8_t PD0		= 16;//PD0
		const static uint8_t PD1		= 17;//PD1
		const static uint8_t PD2		= 18;//PD2
		const static uint8_t PD3		= 19;//PD3
		const static uint8_t PD4		= 20;//PD4
		const static uint8_t PD5		= 21;//PD5
		const static uint8_t PD6		= 22;//PD6
		const static uint8_t PD7		= 23;//PD7
		const static uint8_t PE0		= 24;//PE0
		const static uint8_t PE1		= 25;//PE1
		const static uint8_t PE2		= 26;//PE2
		const static uint8_t PE3		= 27;//PE3
		const static uint8_t PE4		= 28;//PE4
		const static uint8_t PE5		= 29;//PE5
		const static uint8_t PE6		= 30;//PE6
		const static uint8_t PE7		= 31;//PE7
		const static uint8_t PF0		= 32;
		const static uint8_t PF1		= 33;
		const static uint8_t PF2		= 34;
		const static uint8_t PF3		= 35;
		const static uint8_t PF4		= 36;
		const static uint8_t PF5		= 37;
		const static uint8_t PF6		= 38;
		const static uint8_t PF7		= 39;
		const static uint8_t PH0		= 40;
		const static uint8_t PH1		= 41;
		const static uint8_t PH2		= 42;
		const static uint8_t PH3		= 43;
		const static uint8_t PH4		= 44;
		const static uint8_t PH5		= 45;
		const static uint8_t PH6		= 46;
		const static uint8_t PH7		= 47;
		const static uint8_t PJ0		= 48;
		const static uint8_t PJ1		= 49;
		const static uint8_t PJ2		= 50;
		const static uint8_t PJ3		= 51;
		const static uint8_t PJ4		= 52;
		const static uint8_t PJ5		= 53;
		const static uint8_t PJ6		= 54;
		const static uint8_t PJ7		= 55;
		const static uint8_t PK0		= 56;
		const static uint8_t PK1		= 57;
		const static uint8_t PK2		= 58;
		const static uint8_t PK3		= 59;
		const static uint8_t PK4		= 60;
		const static uint8_t PK5		= 61;
		const static uint8_t PK6		= 62;
		const static uint8_t PK7		= 63;
		const static uint8_t PA0		= 64;
		const static uint8_t PA1		= 65;
		const static uint8_t PA2		= 66;
		const static uint8_t PA3		= 67;
		const static uint8_t PA4		= 68;
		const static uint8_t PA5		= 69;
		const static uint8_t PA6		= 70;
		const static uint8_t PA7		= 71;
		const static uint8_t PIN_COUNT	= 72;

		static PORT_t* PORTS[PIN_COUNT/8];
		static register8_t PIN_CTRLS[8];


		void SetDirOut (uint8_t pin)
			{
			this->PORTS[pin>>3]->DIRSET	= 1<<( pin % 8 );
			}
		void SetDirIn (uint8_t pin)
			{
			this->PORTS[pin>>3]->DIRCLR	= 1<<( pin % 8 );
			}
		void SetOutToggle (uint8_t pin)
			{
			this->PORTS[pin>>3]->OUTTGL	= 1<<( pin % 8 );
			}
		void SetOutHigh (uint8_t pin)
			{
			this->PORTS[pin>>3]->OUTSET	= 1<<( pin % 8 );
			}
		void SetOutLow (uint8_t pin)
			{
			this->PORTS[pin>>3]->OUTCLR	= 1<<( pin % 8 );
			}
		bool IsPinHigh (uint8_t pin)
			{
			return this->PORTS[pin>>3]->IN & 1<<( pin % 8 );
			}
		bool IsPinLow (uint8_t pin)
			{
			return (this->PORTS[pin>>3]->IN & 1<<( pin % 8 )) == 0;
			}
		void SetPullUp (uint8_t pin)
			{
			uint8_t pPin	= pin % 8;
			if (pPin == 0)
				this->PORTS[pin>>3]->PIN0CTRL	= PORT_OPC_PULLUP_gc;
			else if (pPin == 1)
				this->PORTS[pin>>3]->PIN1CTRL	= PORT_OPC_PULLUP_gc;
			else if (pPin == 2)
				this->PORTS[pin>>3]->PIN2CTRL	= PORT_OPC_PULLUP_gc;
			else if (pPin == 3)
				this->PORTS[pin>>3]->PIN3CTRL	= PORT_OPC_PULLUP_gc;
			else if (pPin == 4)
				this->PORTS[pin>>3]->PIN4CTRL	= PORT_OPC_PULLUP_gc;
			else if (pPin == 5)
				this->PORTS[pin>>3]->PIN5CTRL	= PORT_OPC_PULLUP_gc;
			else if (pPin == 6)
				this->PORTS[pin>>3]->PIN6CTRL	= PORT_OPC_PULLUP_gc;
			else if (pPin == 7)
				this->PORTS[pin>>3]->PIN7CTRL	= PORT_OPC_PULLUP_gc;
			}
		void SetPullDown (uint8_t pin)
			{
			uint8_t pPin	= pin % 8;
			if (pPin == 0)
				this->PORTS[pin>>3]->PIN0CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (pPin == 1)
				this->PORTS[pin>>3]->PIN1CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (pPin == 2)
				this->PORTS[pin>>3]->PIN2CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (pPin == 3)
				this->PORTS[pin>>3]->PIN3CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (pPin == 4)
				this->PORTS[pin>>3]->PIN4CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (pPin == 5)
				this->PORTS[pin>>3]->PIN5CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (pPin == 6)
				this->PORTS[pin>>3]->PIN6CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (pPin == 7)
				this->PORTS[pin>>3]->PIN7CTRL	= PORT_OPC_PULLDOWN_gc;
			}
	protected:
	private:
	};
*/
//void SPI_SimpleInit(void* parameters);

#endif

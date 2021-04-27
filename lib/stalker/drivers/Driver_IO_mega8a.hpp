#ifndef DRIVER_IO_H
#define DRIVER_IO_H

typedef uint8_t IOPin;
//typedef PORT_t IOPort;
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
#define IOPORTB_ADDR			0x18  /* I/O Ports */
#define IOPORTC_ADDR			0x15  /* I/O Ports */
#define IOPORTD_ADDR			0x12  /* I/O Ports */

#define IODDRB_ADDR				0x17  /* I/O Ports */
#define IODDRC_ADDR				0x14  /* I/O Ports */
#define IODDRD_ADDR				0x11  /* I/O Ports */

#define IOPINB_ADDR				0x16  /* I/O Ports */
#define IOPINC_ADDR				0x13  /* I/O Ports */
#define IOPIND_ADDR				0x10  /* I/O Ports */


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
template <uintptr_t portAddr, uint8_t selectedPin>
class Driver_IO_Pin1
	{
		
	};

//template <uintptr_t portAddr, uint8_t selectedPin>
//template <volatile uint8_t pPORT, volatile uint8_t pDDR, uint8_t selectedPin>
template <volatile uint8_t PIN_ADDR, uint8_t selectedPin>
class Driver_IO_Pin
	{
	private:

		/*static PORT_t* getPort()
			{
			return (PORT_t*)portAddr;
			}*/
	public:
		/*
    static void setOutHigh(){};
		static void setOutLow(){};
		static void setOutToggle(){};
		static void setDirOut(){};
		static void setDirIn(){};
		static bool isPinHigh (){};
		static bool isPinLow (){};
		static void setPullUp (){};
    */
		static void SetOutHigh()
			{
			sbi(_SFR_IO8(PIN_ADDR+2),selectedPin);
			}
		static void SetOutLow()
			{
			cbi(_SFR_IO8(PIN_ADDR+2),selectedPin);
			}
		static void SetOutToggle()
			{
			_SFR_IO8(PIN_ADDR+2)	^= 1<<selectedPin;
			}
		static void SetDirOut()
			{
			sbi(_SFR_IO8(PIN_ADDR+1),selectedPin);
			}
		static void SetDirIn()
			{
			cbi(_SFR_IO8(PIN_ADDR+1),selectedPin);
			}
		static bool IsPinHigh ()
			{
			return _SFR_IO8(PIN_ADDR+0) & (1<<selectedPin);
			}
		static bool IsPinLow ()
			{
			return (_SFR_IO8(PIN_ADDR+0) & (1<<selectedPin)) == 0;
			}
		static void SetPullUp ()
			{
			SetOutHigh();
			}
		/*template<>
		static void test<1> ()
			{
			
			}*/
		/*static void setPullUp ()//TODO: шаблоны бля!!!
			{
			//Driver_IO_Pin_PULLUP<portAddr,selectedPin>::pullup();
			if (selectedPin == 0)
				getPort()->PIN0CTRL	= PORT_OPC_PULLUP_gc;
			else if (selectedPin == 1)
				getPort()->PIN1CTRL	= PORT_OPC_PULLUP_gc;
			else if (selectedPin == 2)
				getPort()->PIN2CTRL	= PORT_OPC_PULLUP_gc;
			else if (selectedPin == 3)
				getPort()->PIN3CTRL	= PORT_OPC_PULLUP_gc;
			else if (selectedPin == 4)
				getPort()->PIN4CTRL	= PORT_OPC_PULLUP_gc;
			else if (selectedPin == 5)
				getPort()->PIN5CTRL	= PORT_OPC_PULLUP_gc;
			else if (selectedPin == 6)
				getPort()->PIN6CTRL	= PORT_OPC_PULLUP_gc;
			else if (selectedPin == 7)
				getPort()->PIN7CTRL	= PORT_OPC_PULLUP_gc;
			
			}
		static void setPullDown ()//TODO: шаблоны бля!!!
			{
			//Driver_IO_Pin_PULLUP<portAddr,selectedPin>::pullup();
			if (selectedPin == 0)
				getPort()->PIN0CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (selectedPin == 1)
				getPort()->PIN1CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (selectedPin == 2)
				getPort()->PIN2CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (selectedPin == 3)
				getPort()->PIN3CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (selectedPin == 4)
				getPort()->PIN4CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (selectedPin == 5)
				getPort()->PIN5CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (selectedPin == 6)
				getPort()->PIN6CTRL	= PORT_OPC_PULLDOWN_gc;
			else if (selectedPin == 7)
				getPort()->PIN7CTRL	= PORT_OPC_PULLDOWN_gc;
			
			}*/
	};
//#define Driver_IO_Pin(port,pin) Driver_IO_PinClass<(uintptr_t)&port, pin>
class Driver_IO
	{
	public:
	protected:
	private:
	};
void SPI_SimpleInit(void* parameters)
	{
	
	};
#endif
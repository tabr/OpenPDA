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
#define IOPORTB_ADDR			PORTB  /* I/O Ports */
#define IOPORTC_ADDR			PORTC  /* I/O Ports */
#define IOPORTD_ADDR			PORTD  /* I/O Ports */


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
template <volatile uint8_t* pPORT, volatile uint8_t* pDDR, uint8_t selectedPin>
class Driver_IO_Pin
	{
	private:

		/*static PORT_t* getPort()
			{
			return (PORT_t*)portAddr;
			}*/
	public:
		static void setOutHigh()
			{
			sbi(*pPORT,selectedPin);
			}
		static void setOutLow()
			{
			cbi(*pPORT,selectedPin);
			}
		static void setOutToggle()
			{
			*pPORT	^= 1<<selectedPin;
			}
		static void setDirOut()
			{
			sbi(*pDDR,selectedPin);
			}
		static void setDirIn()
			{
			cbi(*pDDR,selectedPin);
			}
		static bool isPinHigh ()
			{
			return (*pPORT) & 1<<selectedPin;
			}
		static bool isPinLow ()
			{
			return ((*pPORT) & 1<<selectedPin) == 0;
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

class Driver_IO
	{
	public:
	protected:
	private:
	};
#endif
#ifndef DRIVER_IO_H
#define DRIVER_IO_H

typedef uint8_t IOPin;

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
			}
		static void SetDirIn()
			{
			GetPort()->DIRCLR	= 1<<selectedPin;
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
/*
template <uintptr_t spiAddr, volatile uintptr_t portAddr, uint8_t selectedPin>
//template <uintptr_t spiAddr, class PIN>
class Driver_IO_SPIClass
	{
	public:
		static void SendRequest (uint8_t* data, uint8_t length)
			{
			for (uint8_t i=0;i<length;i++)
				{
				Send(data[i]);
				}
			}
		static void Communicate(uint8_t request, uint8_t* answer=NULL, uint8_t answerLength=0)
			{
			ActivateDevice();
			Send(request);
			if (answerLength > 0)
				{
				ReadPacket (answer, answerLength);
				}
			DeactivateDevice();
			}
		static void Communicate(uint8_t* requestArray, uint8_t requestLength, uint8_t* answer=NULL, uint8_t answerLength=0)
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
		static void ReadPacket(uint8_t* data, uint8_t length)
			{
			for (uint8_t i=0;i<length;i++)
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


template <uintptr_t twiAddr, TWI_Data deviceSlaveAddress, uint16_t interfaceSpeedKhz>
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
		static bool sendByte(TWI_Data data)
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
			getTWI()->MASTER.CTRLB		= TWI_MASTER_SMEN_bm;
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

*/
#define Driver_IO_Pin(port,pin) Driver_IO_PinClass<reinterpret_cast<uintptr_t>((volatile uintptr_t)0 + &port), pin>

//#define Driver_IO_SPI(spi,port,pin) Driver_IO_SPIClass<reinterpret_cast<uintptr_t>((uintptr_t)0 + &spi),reinterpret_cast<uintptr_t>((volatile uintptr_t)0 + &port), pin>
//#define Driver_IO_TWI(twi, deviceSlaveAddress, interfaceSpeedKhz) Driver_IO_TWIClass<reinterpret_cast<uintptr_t>((uintptr_t)0 + &twi), deviceSlaveAddress, interfaceSpeedKhz>

#endif

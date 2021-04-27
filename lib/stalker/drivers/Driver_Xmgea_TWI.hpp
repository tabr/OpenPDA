/*
 * OneWire.h
 *
 * Created: 2015-02-14 01:55:15
 *  Author: tabr
 */ 


#ifndef TWOWIRE_H_
#define TWOWIRE_H_

//#include "boards/pcb_1.h"


//typedef uint8_t TWI_Data;
class TWI
	{
	public:
//		const static uint32_t BAUDRATE		= 400000;
		const static uint8_t BIT_READ		= 0x01;

		TWI_t *twi;

		bool beginTransmission(void)
			{
			uint8_t j=0;
			this->twi->MASTER.ADDR = this->deviceSlaveAddress;// & ~0x01;
			while (!(this->twi->MASTER.STATUS & TWI_MASTER_WIF_bm))
				{
				if (++j == 64)//32 - малоб 48 - норм
					{
					this->twi_stop();
					return false;
					}
				_delay_us(1);
				}
			return true;
			}
		bool sendByte(TWI_Data data)
			{
			uint8_t j=0;
			this->twi->MASTER.DATA = data;
			while (!(this->twi->MASTER.STATUS & TWI_MASTER_WIF_bm))
				{
				if (++j == 96)//64 - малоб 70 - норм
					{
					this->twi_stop();
					return false;
					}
				_delay_us(1);
				}
//			this->twi_stop();
			return true;
			}
		void requestRead(void)
			{
			this->twi->MASTER.ADDR		= this->deviceSlaveAddress | this->BIT_READ;
			this->twi->MASTER.STATUS	|= TWI_MASTER_RIF_bm;
			this->twi->MASTER.CTRLC		= TWI_MASTER_CMD_RECVTRANS_gc;
			}
		bool writeToDevice(uint8_t deviceAddress, uint8_t bytesToWrite, uint8_t *writeData)
			{
			this->beginTransmission();
			this->sendByte(deviceAddress);
			for(uint8_t i=0;i<bytesToWrite;i++)
				{
				this->sendByte(writeData[i]);
				}
			this->twi_stop();
			return true;
			}
		bool writeToDevice(uint8_t deviceAddressH,uint8_t deviceAddressL, uint16_t bytesToWrite, uint8_t *writeData)
			{
			this->beginTransmission();
			this->sendByte(deviceAddressH);
			this->sendByte(deviceAddressL);
			for(uint16_t i=0;i<bytesToWrite;i++)
				{
				this->sendByte(writeData[i]);
				}
			this->twi_stop();
			return true;
			}
		bool readFromDevice(uint8_t registerAddress, uint8_t bytesToRead, uint8_t *readData)
			{
			/*
			uint8_t i;
//			uint8_t address = 0xC0;

//			address |= 0x01;
			this->twi->MASTER.ADDR = this->deviceAddress & ~0x01;
			while(!(this->twi->MASTER.STATUS&TWI_MASTER_WIF_bm));
			//	twiname->MASTER.DATA = 0x00;       // write word addrpointer first
			this->twi->MASTER.ADDR = (this->deviceAddress | 0x01);    // send read command
			for(i=0;i<2;i++)
				{                // read date and time
				while(!(this->twi->MASTER.STATUS&TWI_MASTER_RIF_bm));
				readData[i] = this->twi->MASTER.DATA;
				}
			return true;*/
			
//			uint8_t i;//,j=0;
			this->beginTransmission();
			/*
			this->twi->MASTER.ADDR = this->deviceAddress;// & ~0x01;
			j=0;
			while (!(this->twi->MASTER.STATUS & TWI_MASTER_WIF_bm) || (this->twi->MASTER.STATUS & TWI_SLAVE_RXACK_bm))
				{
				if (++j == 64)//32 - малоб 48 - норм
					{
					this->twi_stop();
					return false;
					}
				delay_us(1);
				}
			*/
			this->sendByte(registerAddress);
			/*
			this->twi->MASTER.DATA = registerAddress;
			j=0;
			while (!(this->twi->MASTER.STATUS & TWI_MASTER_WIF_bm))
				{
				if (++j == 96)//64 - малоб 70 - норм
					{
					this->twi_stop();
					return false;
					}
				delay_us(1);
				}
			*/
//			this->twi_stop();///??????????????????????!!!!!!!!!
//			_delay_ms(10);
			this->requestRead();
//			this->twi->MASTER.ADDR = this->deviceAddress | 0x01;
/*
//’”…Ќяяяяяяя!!!!!!!!!!!!!
			while (!(this->twi->MASTER.STATUS & TWI_MASTER_RIF_bm))
				{
				if (++j == 96)//64 - малоб 70 - норм
					{
					this->twi_stop();
					return false;
					}
				delay_us(1);
				}
*/
//			this->twi->MASTER.STATUS |= TWI_MASTER_RIF_bm;
//			this->twi->MASTER.CTRLC = TWI_MASTER_CMD_RECVTRANS_gc;
			for(uint8_t i=0;i<bytesToRead;i++)
				{// read date and time
				/*
				j=1;
				while(!(this->twi->MASTER.STATUS&TWI_MASTER_RIF_bm))
					{
					if (++j == 96)//64 - малоб 70 - норм
						{
						this->twi_stop();
						return false;
						}
					delay_us(1);
					}
				readData[i]	= this->twi->MASTER.DATA;
				*/
				readData[i]	= this->readByte();
				}
			this->twi_stop();
			return true;
			
			}
		bool readFromDevice(uint8_t registerAddressH, uint8_t registerAddressL, uint16_t bytesToRead, uint8_t *readData)
			{
			if (!(this->beginTransmission()))
				{
				return false;
				}
			this->sendByte(registerAddressH);
			this->sendByte(registerAddressL);
			this->requestRead();
			for(uint16_t i=0;i<bytesToRead;i++)
				{// read date and time
				readData[i]	= this->readByte();
				}
			this->twi_stop();
			return true;
			
			}
		uint8_t readByte(void)
			{
			uint8_t j=0;
			while(!(this->twi->MASTER.STATUS&TWI_MASTER_RIF_bm))
				{
				if (++j == 96)//64 - малоб 70 - норм
					{
					this->twi_stop();
					return 0;
					}
				_delay_us(1);
				}
			return this->twi->MASTER.DATA;
			}
		/*bool receive(uint8_t bytesToRead, uint8_t *readData)
			{
			uint8_t j=0;
			
			this->twi->MASTER.ADDR = this->deviceAddress | 0x01;
			while (!(this->twi->MASTER.STATUS & TWI_MASTER_RIF_bm))
				{
				if (++j == 96)//64 - малоб 70 - норм
					{
					this->twi_stop();
					return false;
					}
				delay_us(1);
				}
			
			this->twi->MASTER.STATUS |= TWI_MASTER_RIF_bm;
			this->twi->MASTER.CTRLC = TWI_MASTER_CMD_RECVTRANS_gc;
			for(uint8_t i=0;i<bytesToRead;i++)
				{// read date and time
				j=0;
				while(!(this->twi->MASTER.STATUS&TWI_MASTER_RIF_bm))
					{
					if (++j == 96)//64 - малоб 70 - норм
						{
						this->twi_stop();
						return false;
						}
					delay_us(1);
					}
				readData[i]	= this->twi->MASTER.DATA;
				}
			
			return true;
			}*/
		/*void endTransmission(void)
			{
			
			}*/
		void twi_stop(void)
			{
			this->twi->MASTER.CTRLC = (TWI_MASTER_ACKACT_bm | TWI_MASTER_CMD_STOP_gc);
			}
		TWI (TWI_t *twi_p, TWI_Data addr, uint16_t interfaceSpeedKhz)
//		OneWire ()
			{
			this->twi					= twi_p;
			this->deviceSlaveAddress	= addr;
//			this->twi					= &TWIC;//twi_p;
//			this->deviceAddress			= (0x4 << 2 | 0x0);//addr;

			this->twi->MASTER.CTRLB		= TWI_MASTER_SMEN_bm;
			//#define TWI_BAUD(F_SYS, F_TWI) ((F_SYS / (2 * F_TWI)) - 5)
			//#define TWI_BAUDSETTING TWI_BAUD(F_CPU, TWI_BAUDRATE)
//			this->twi->MASTER.BAUD		= ((F_CPU / (2 * this->BAUDRATE)) - 5);
			this->twi->MASTER.BAUD		= ((F_CPU / ((uint32_t)2 * interfaceSpeedKhz * 1000)) - 5);
			this->twi->MASTER.CTRLA		= TWI_MASTER_ENABLE_bm;
			this->twi->MASTER.STATUS	= TWI_MASTER_BUSSTATE_IDLE_gc;
			
			this->twi_stop();
			}
	protected:
	private:
		TWI_Data deviceSlaveAddress;
	};




#endif /* TWOWIRE_H_ */
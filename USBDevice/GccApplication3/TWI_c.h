/*
 * TWI_c.h
 *
 * Created: 2015-02-22 00:40:31
 *  Author: tabr
 */ 


#ifndef TWI_C_H_
#define TWI_C_H_


const static uint8_t BIT_READ		= 0x01;
typedef uint8_t TWI_Data;

TWI_Data deviceSlaveAddress;
void twi_stop();
uint8_t readByte(void);

TWI_t *twi;

		bool beginTransmission(void)
			{
			uint8_t j=0;
			twi->MASTER.ADDR = deviceSlaveAddress;// & ~0x01;
			while (!(twi->MASTER.STATUS & TWI_MASTER_WIF_bm))
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
		bool sendByte(TWI_Data data)
			{
			uint8_t j=0;
			twi->MASTER.DATA = data;
			while (!(twi->MASTER.STATUS & TWI_MASTER_WIF_bm))
				{
				if (++j == 96)//64 - малоб 70 - норм
					{
					twi_stop();
					return false;
					}
				_delay_us(1);
				}
//			twi_stop();
			return true;
			}
		void requestRead(void)
			{
			twi->MASTER.ADDR		= deviceSlaveAddress | BIT_READ;
			twi->MASTER.STATUS	|= TWI_MASTER_RIF_bm;
			twi->MASTER.CTRLC		= TWI_MASTER_CMD_RECVTRANS_gc;
			}
		bool writeToDevice(uint8_t deviceAddressH, uint8_t deviceAddressL, uint16_t bytesToWrite, uint8_t *writeData)
			{
			beginTransmission();
			sendByte(deviceAddressH);
			sendByte(deviceAddressL);
			for(uint16_t i=0;i<bytesToWrite;i++)
				{
				sendByte(writeData[i]);
//				if (i%16 == 15)
//					_delay_ms(10);
				}
			twi_stop();
			return true;
			}
		bool readFromDevice(uint8_t deviceAddressH, uint8_t deviceAddressL, uint16_t bytesToRead, uint8_t *readData)
			{
			beginTransmission();
			sendByte(deviceAddressH);
			sendByte(deviceAddressL);
			requestRead();
			for(uint16_t i=0;i<bytesToRead;i++)
				{
				readData[i]	= readByte();
				}
			twi_stop();
			return true;
			}
		uint8_t readByte(void)
			{
			uint8_t j=0;
			while(!(twi->MASTER.STATUS&TWI_MASTER_RIF_bm))
				{
				if (++j == 96)//64 - малоб 70 - норм
					{
					twi_stop();
					return 0;
					}
				_delay_us(1);
				}
			return twi->MASTER.DATA;
			}
		/*bool receive(uint8_t bytesToRead, uint8_t *readData)
			{
			uint8_t j=0;
			
			twi->MASTER.ADDR = deviceAddress | 0x01;
			while (!(twi->MASTER.STATUS & TWI_MASTER_RIF_bm))
				{
				if (++j == 96)//64 - малоб 70 - норм
					{
					twi_stop();
					return false;
					}
				delay_us(1);
				}
			
			twi->MASTER.STATUS |= TWI_MASTER_RIF_bm;
			twi->MASTER.CTRLC = TWI_MASTER_CMD_RECVTRANS_gc;
			for(uint8_t i=0;i<bytesToRead;i++)
				{// read date and time
				j=0;
				while(!(twi->MASTER.STATUS&TWI_MASTER_RIF_bm))
					{
					if (++j == 96)//64 - малоб 70 - норм
						{
						twi_stop();
						return false;
						}
					delay_us(1);
					}
				readData[i]	= twi->MASTER.DATA;
				}
			
			return true;
			}*/
		/*void endTransmission(void)
			{
			
			}*/
		void twi_stop(void)
			{
			twi->MASTER.CTRLC = (TWI_MASTER_ACKACT_bm | TWI_MASTER_CMD_STOP_gc);
			}
		void TWI (TWI_t *twi_p, TWI_Data addr, uint16_t interfaceSpeedKhz)
//		OneWire ()
			{
			twi						= twi_p;
			deviceSlaveAddress		= addr;
//			twi					= &TWIC;//twi_p;
//			deviceAddress			= (0x4 << 2 | 0x0);//addr;

			twi->MASTER.CTRLB		= TWI_MASTER_SMEN_bm;
			//#define TWI_BAUD(F_SYS, F_TWI) ((F_SYS / (2 * F_TWI)) - 5)
			//#define TWI_BAUDSETTING TWI_BAUD(F_CPU, TWI_BAUDRATE)
//			twi->MASTER.BAUD		= ((F_CPU / (2 * BAUDRATE)) - 5);
			twi->MASTER.BAUD		= ((F_CPU / (2 * interfaceSpeedKhz * 1000)) - 5);
			twi->MASTER.CTRLA		= TWI_MASTER_ENABLE_bm;
			twi->MASTER.STATUS	= TWI_MASTER_BUSSTATE_IDLE_gc;
			
			twi_stop();
			}

#endif /* TWI_C_H_ */
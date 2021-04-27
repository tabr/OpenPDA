/*
 * Driver_AR1010.h
 *
 * Created: 2015-02-12 19:01:45
 *  Author: tabr
 * https://github.com/adamjansch/AR1010lib/blob/master/ar1010lib.cpp
 */ 


#ifndef DRIVER_AR1010_H_
#define DRIVER_AR1010_H_

//#include "boards/compiler_defines.h"
//#include <avr/io.h>
//#include <util/delay.h>
//#include "stalker/drivers/Driver_Xmgea_TWI.h"
//#include "my_defines.h"
//#include "unionsFixed.h"
//#include "boards/pcb_1.h"

#define MASK_STC (1<<5)		//0x0020  // Seek/Tune/PowerOn complete  D5 in  adress 13H 
//#define ADDR_STATUS	0x13	// the address of status register


//typedef uint8_t OneWireDeviceAddress;
typedef uint16_t AR1010_RegisterLength;
typedef uint8_t AR1010_VolumeLevel;
typedef uint8_t AR1010_SignalStrength;


class AR1010
	{
	public:
		const static uint8_t REGISTER_R0				= 0x00;
		const static uint8_t REGISTER_R1				= 0x01;
		const static uint8_t REGISTER_R2				= 0x02;
		const static uint8_t REGISTER_R3				= 0x03;
		const static uint8_t REGISTER_R4				= 0x04;
		const static uint8_t REGISTER_R5				= 0x05;
		const static uint8_t REGISTER_R6				= 0x06;
		const static uint8_t REGISTER_R7				= 0x07;
		const static uint8_t REGISTER_R8				= 0x08;
		const static uint8_t REGISTER_R9				= 0x09;
		const static uint8_t REGISTER_R10				= 0x0A;
		const static uint8_t REGISTER_R11				= 0x0B;
		const static uint8_t REGISTER_R12				= 0x0C;
		const static uint8_t REGISTER_R13				= 0x0D;
		const static uint8_t REGISTER_R14				= 0x0E;
		const static uint8_t REGISTER_R15				= 0x0F;
		const static uint8_t REGISTER_R16				= 0x10;
		const static uint8_t REGISTER_R17				= 0x11;
		const static uint8_t REGISTER_RSSI				= 0x12;
		const static uint8_t REGISTER_STATUS			= 0x13;
		const static uint8_t REGISTER_RBS				= 0x14;
		const static uint8_t REGISTER_RDS1				= 0x15;
		const static uint8_t REGISTER_RDS2				= 0x16;
		const static uint8_t REGISTER_RDS3				= 0x17;
		const static uint8_t REGISTER_RDS4				= 0x18;
		const static uint8_t REGISTER_RDS5				= 0x19;
		const static uint8_t REGISTER_RDS6				= 0x1A;
		const static uint8_t REGISTER_DEVID				= 0x1B;
		const static uint8_t REGISTER_CHIPID			= 0x1C;

		const static uint8_t REGISTERS_NUM				= 18;
		const static uint8_t VOLUME_LEVELS_NUM			= 22;
		const static uint16_t VOLUME_R03MASK			= 0b0000011110000000;
		const static uint16_t VOLUME_R14MASK			= 0b0000000000001111;

		const static uint8_t REGISTER_R1_BIT01_HMUTE	= 1;
		const static uint8_t REGISTER_R1_BIT02_SMUTE	= 2;
		const static uint8_t REGISTER_R1_BIT03_MONO		= 3;

		const static uint8_t REGISTER_R2_BIT09_TUNE		= 9;

		const static uint8_t REGISTER_STATUS_BIT05_STC	= 5;

		const static uint8_t DEVICE_ADDRESS		= 0x20;
		const static uint16_t CHAN_MASK			= 0xFE00;			 // Bit range of register 2's channel setting
		
		const static uint16_t register_init[REGISTERS_NUM];
		const static uint8_t volume[VOLUME_LEVELS_NUM];
		bool isDisabled=true;
		
		uint8_t tmp;
		bool isMuted;
		AR1010_SignalStrength lastRSSIFiltered;
	
		AR1010_RegisterLength readStatus(void);
		bool isSTC_Set(void);
		void IOInit(void);																		//empty
		void HardwareInitialization(void);														//WARNING! Contain delay_ms
		void tuneOFF();
		void tuneON();
		void smuteON();
		void smuteOFF();
		void hmuteON();
		void hmuteOFF();
		void forceMonoON();
		void forceMonoOFF();
		void setFrequency(uint16_t frequency);
		void setVolume(AR1010_VolumeLevel level);
		void setVolumeMin(void);
		void setVolumeMax(void);
		void deviceEnable(void);
		void deviceDisable(void);
		AR1010_SignalStrength getRSSIValue(void);
//		AR1010(TWI *twi)
//			{
//			this->Wire				= twi;
//			this->tmp				= 0;
//			this->isMuted			= false;
//			this->lastRSSIFiltered	= 0;
//			}
		AR1010(void)
			{
//			this->Wire		= new TWI(&FM_TWI, this->DEVICE_ADDRESS, 400);
			//this->Wire			= MemoryManager.allocate()
			//PORTE.PIN0CTRL = PORT_OPC_WIREDANDPULL_gc;
			//PORTE.PIN1CTRL = PORT_OPC_WIREDANDPULL_gc;
			this->tmp				= 0;
			this->isMuted			= false;
			this->lastRSSIFiltered	= 0;
			}
	protected:
	private:
		void writeToRegister(TWI_Data_t registerAddress, AR1010_RegisterLength data);
		AR1010_RegisterLength readFromRegister(TWI_Data_t registerAddress);
		bool getBitFromRegister(TWI_Data_t registerAddress, uint8_t bitNum);
		void setBitInRegister(TWI_Data_t registerAddress, uint8_t bitNum);
		void clearBitInRegister(TWI_Data_t registerAddress, uint8_t bitNum);

//		TWI *Wire;
	};

#endif /* DRIVER_AR1010_H_ */
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * Driver_AR1010.cpp
 *
 * Created: 2015-02-14 00:06:36
 *  Author: tabr
 */ 
#include "Driver_AR1010.hpp"
void AR1010::IOInit(void)
	{
	
	}
void AR1010::deviceEnable(void)
	{
	this->setBitInRegister(this->REGISTER_R0, 0);
	//this->writeToRegister(this->REGISTER_R0, (this->register_init[0] | 1<<0));
	this->isDisabled	= false;
	}
void AR1010::deviceDisable(void)
	{
	this->clearBitInRegister(this->REGISTER_R0, 0);
	//this->writeToRegister(this->REGISTER_R0, (this->register_init[0] & ~(1<<0)));
	this->hmuteON();
	this->isDisabled	= true;
	}
void AR1010::HardwareInitialization(void)
	{
	if (this->isDisabled)
		{
		return;
		}
	this->writeToRegister(this->REGISTER_R0, this->register_init[0] & 0xFFFE);
	for(uint8_t i = 1; i < this->REGISTERS_NUM; i++)
		{
		this->writeToRegister(i, this->register_init[i]);
		}
	this->writeToRegister(this->REGISTER_R0, this->register_init[0]);
//	uint16_t status = 0;
	while (not this->isSTC_Set());
//	while (status == 0)
//	{
		//status	= this->readStatus();
		
		//sprintf (lcd_buf, "%05d %03d", status, randomPseudo);
		//LcdString(1,LCD_LINE_5);
		//LcdUpdate();
		//status	= status & MASK_STC;
//		_delay_ms(1);
//		}
	}
void AR1010::writeToRegister(TWI_Data_t registerAddress, AR1010_RegisterLength data)
	{
	uint8_t value1 = (data & 0xFF00) >> 8;
	uint8_t value2 = (data & 0x00FF);

	Ar1010TWI::beginTransmission();
	Ar1010TWI::sendByte(registerAddress);

	Ar1010TWI::sendByte(value1);
	Ar1010TWI::sendByte(value2);
	
	Ar1010TWI::twi_stop();
	}
AR1010_RegisterLength AR1010::readFromRegister(TWI_Data_t registerAddress)
	{
	uint8_t	readedData[2];

	if (!Ar1010TWI::readFromDevice(registerAddress, 2, readedData))
		{
		this->tmp |= 1<<5;
		}

	//Combine two bytes into one 16-bit word
	int16_t temp = readedData[0] << 8;
	temp |= readedData[1];
	
	return(temp);
	}
bool AR1010::getBitFromRegister(TWI_Data_t registerAddress, uint8_t bitNum)
	{
	AR1010_RegisterLength temp;
	uint8_t mask;

	mask	= 1<<bitNum;
	temp	= this->readFromRegister(registerAddress);
	return ((temp & mask) == mask);
	}
void AR1010::setBitInRegister(TWI_Data_t registerAddress, uint8_t bitNum)
	{
	AR1010_RegisterLength temp;
	temp	= this->readFromRegister(registerAddress);
	sbi(temp, bitNum);
	this->writeToRegister(registerAddress, temp);
	}
void AR1010::clearBitInRegister(TWI_Data_t registerAddress, uint8_t bitNum)
	{
	AR1010_RegisterLength temp;
	temp	= this->readFromRegister(registerAddress);
	cbi(temp, bitNum);
	this->writeToRegister(registerAddress, temp);
	}
//////////////////////////////////////////////////
AR1010_RegisterLength AR1010::readStatus(void)
	{
	if (this->isDisabled)
		{
		return 0;
		}
	return this->readFromRegister(this->REGISTER_STATUS);
	}

void AR1010::tuneOFF(void)
	{
	if (this->isDisabled)
		{
		return;
		}
	this->clearBitInRegister(this->REGISTER_R2, this->REGISTER_R2_BIT09_TUNE);
	/*
	uint16_t temp;
	temp = this->readFromRegister(this->REGISTER_R2);
	cbi(temp, this->REGISTER_R2_BIT09_TUNE);
	this->writeToRegister(this->REGISTER_R2, temp);
	*/
	}
void AR1010::tuneON(void)
	{
	if (this->isDisabled)
		{
		return;
		}
	this->setBitInRegister(this->REGISTER_R2, this->REGISTER_R2_BIT09_TUNE);
	/*
	uint16_t temp;
	temp = this->readFromRegister(this->REGISTER_R2);
	sbi(temp, this->REGISTER_R2_BIT09_TUNE);
	this->writeToRegister(this->REGISTER_R2, temp);
	*/
	}
void AR1010::setFrequency(uint16_t frequency)
	{
	//[87.5-108.0]
	if (this->isDisabled)
		{
		return;
		}
	/*
	1) Set hmute Bit 
	2) Clear TUNE Bit 
	3) Clear SEEK Bit
	4) Set BAND/SPACE/CHAN Bits
	5) Enable TUNE Bit 
	6) Wait STC flag (Seek/Tune Comlete, in Status Register
	7) Clear hmute Bit 
	8) Update Functions (optional) 
	*/
	uint16_t register2, channel = frequency - 690;

	this->tuneOFF();

	// Correct out of lower range
	if(channel < 185)
		{
		channel = 185;
		}
	else if(channel > 390)
		{
		channel = 390;
		}
	
	register2	= readFromRegister(2);
	register2	= register2 & this->CHAN_MASK;
	register2 |= channel;
	this->writeToRegister(2, register2);

	this->tuneON();
	
	
	while (!this->isSTC_Set());
	
	//setBitInRegister(tune_bit[0], tune_bit[1], 1);	// Set tune bit
	}
void AR1010::setVolume(AR1010_VolumeLevel level)
	{
	if (this->isDisabled)
		{
		return;
		}
	uint16_t reg3, reg14;
//	reg3 = this->readFromRegister(this->REGISTER_R3) & 0xF87F; //Zero out bits D7-D10
	reg3 = this->readFromRegister(this->REGISTER_R3) & (!this->VOLUME_R03MASK); //Zero out bits D7-D10
	reg3 |= ( (this->volume[level] & 0x0F) << 7); //Mask in D7-D10
	
//	reg14 = this->readFromRegister(this->REGISTER_R14) & 0x0FFF; //Zero out bits D12-D15
	reg14 = this->readFromRegister(this->REGISTER_R14) & (!this->VOLUME_R14MASK); //Zero out bits D12-D15
	reg14 |= ((this->volume[level] & 0xF0) << 8); //Mask in D12-D15
	
	this->writeToRegister(this->REGISTER_R3, reg3);
	this->writeToRegister(this->REGISTER_R14, reg14);
	}
void AR1010::setVolumeMin(void)
	{
	if (this->isDisabled)
		{
		return;
		}
	this->setVolume(0);
	}
void AR1010::setVolumeMax(void)
	{
	if (this->isDisabled)
		{
		return;
		}
	this->setVolume(this->VOLUME_LEVELS_NUM-1);
	}
bool AR1010::isSTC_Set(void)
	{
	if (this->isDisabled)
		{
		return 0;
		}
	//return ((this->readStatus() & MASK_STC) == MASK_STC);
	return this->getBitFromRegister(this->REGISTER_STATUS, this->REGISTER_STATUS_BIT05_STC);
	}
void AR1010::smuteON()
	{
	if (this->isDisabled)
		{
		return;
		}
	this->setBitInRegister(this->REGISTER_R1, this->REGISTER_R1_BIT02_SMUTE);
	}
void AR1010::smuteOFF()
	{
	if (this->isDisabled)
		{
		return;
		}
	this->clearBitInRegister(this->REGISTER_R1, this->REGISTER_R1_BIT02_SMUTE);
	}
void AR1010::hmuteON()
	{
	if (this->isDisabled)
		{
		return;
		}
	this->setBitInRegister(this->REGISTER_R1, this->REGISTER_R1_BIT01_HMUTE);
	this->isMuted	= true;
	}
void AR1010::hmuteOFF()
	{
	if (this->isDisabled)
		{
		return;
		}
	this->clearBitInRegister(this->REGISTER_R1, this->REGISTER_R1_BIT01_HMUTE);
	this->isMuted	= false;
	}
void AR1010::forceMonoON()
	{
	if (this->isDisabled)
		{
		return;
		}
	this->setBitInRegister(this->REGISTER_R1, this->REGISTER_R1_BIT03_MONO);
	}
void AR1010::forceMonoOFF()
	{
	if (this->isDisabled)
		{
		return;
		}
	this->clearBitInRegister(this->REGISTER_R1, this->REGISTER_R1_BIT03_MONO);
	}
AR1010_SignalStrength AR1010::getRSSIValue(void)
	{
	if (this->isDisabled)
		{
		return 0;
		}
	UNION_UINT16_LITTLE_ENDIAN readedData;//ЕБАНАРОТ!!! перевёруты Hi, Low байты - LowByteFirst - fixed!!!
	readedData.value_int			= this->readFromRegister(this->REGISTER_RSSI);
	//readedData.byte_field.l		= readedData.byte_field.h>>1;
	this->lastRSSIFiltered	= ((readedData.byte_field.h>>1) + lastRSSIFiltered) >> 1;
	return readedData.byte_field.h;
	
	/*
	uint16_t rssi;
	
	rssi = this->readFromRegister(this->REGISTER_RSSI);
	rssi &= 0xFE00;
	rssi >>= 9;

	return(rssi);
	*/
	}
const uint16_t AR1010::register_init[AR1010::REGISTERS_NUM]=
	{
	0xFFFF, //R0
	0x5B15, //R1
	0xF4B9, //R2 Tune/Channel
	0x8012, //R3 seekTHD = 18
	0x0400, //R4
	0x28AA, //R5
	0x4400, //R6
	0x1EE7,	// R7
	0x7141,	// R8
	0x007D,	// R9
	0x82C6,	// R10  disable wrap
	0x4F55,	// R11. <--- (disable xo_output)
	0x970C,	// R12.
	0xB845,	// R13
	0xFC2D,	// R14 : Volume control 2
	0x8097,	// R15
	0x04A1,	// R16
	0xDF6A	// R17
/*
	0xFFFB,     // R0:  1111 1111 1111 1011
	0x5B15,     // R1:  0101 1011 0001 0101 - Mono (D3), Softmute (D2), Hardmute (D1)  !! SOFT-MUTED BY DEFAULT !!
	0xD0B9,     // R2:  1101 0000 1011 1001 - Tune/Channel
	0xA010,     // R3:  1010 0000 0001 0000 - Seekup (D15), Seek bit (D14), Space 100kHz (D13), Seek threshold: 16 (D6-D0)
	0x0780,     // R4:  0000 0111 1000 0000
	0x28AB,     // R5:  0010 1000 1010 1011
	0x6400,     // R6:  0110 0100 0000 0000
	0x1EE7,		// R7:  0001 1110 1110 0111
	0x7141,		// R8:  0111 0001 0100 0001
	0x007D,		// R9:  0000 0000 0111 1101
	0x82C6,		// R10: 1000 0010 1100 0110 - Seek wrap (D3)
	0x4E55,		// R11: 0100 1110 0101 0101
	0x970C,		// R12: 1001 0111 0000 1100
	0xB845,		// R13: 1011 1000 0100 0101
	0xFC2D,		// R14: 1111 1100 0010 1101 - Volume control 2 (D12-D15)
	0x8097,		// R15: 1000 0000 1001 0111
	0x04A1,		// R16: 0000 0100 1010 0001
	0xDF61		// R17: 1101 1111 0110 0001
*/
	/*
	0xFFFF, //R0
	0x5B15, //R1
	0xF4B9, //R2 Tune/Channel
	0x8012, //R3 seekTHD = 18
	0x0400, //R4
	0x28AA, //R5
	0x4400, //R6
	0x1EE7,	// R7
	0x7141,	// R8
	0x007D,	// R9
	0x82C6,	// R10  disable wrap
	0x4F55,	// R11. <--- (disable xo_output)
	0x970C,	// R12.
	0xB845,	// R13
	0xFC2D,	// R14 : Volume control 2
	0x8097,	// R15
	0x04A1,	// R16
	0xDF6A	// R17
*/
	};


// volume control (increasing)
const uint8_t AR1010::volume[AR1010::VOLUME_LEVELS_NUM] =
{
	0x0F,	// step 0
	0xCF,	// 1
	0xDF,	// 2
	0xEF,	// 3
	0xFF,	// 4
	0xEE,	// 5
	0xFE,	// 6
	0xED,	// 7
	0xFD,	// 8
	0xFB,	// 9
	0xFA,	// 10
	0xF9,	// 11
	0xF7,	// 12
	0xE6,	// 13
	0xF6,	// 14
	0xE5,	// 15
	0xF5,	// 16
	0xE3,	// 17
	0xF3,	// 18
	0xF2,	// 19
	0xF1,	// 20
	0xF0	// 21 <------ default setting
};

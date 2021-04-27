// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
void Driver_AnoRadRarioModule::setTXBuffer(uint8_t* buf)
	{
	this->txBuffer		= buf;
	this->isTXBufInit	= true;
	}
void Driver_AnoRadRarioModule::setRXBuffer(uint8_t* buf)
	{
	this->rxBuffer		= buf;
	this->isRXBufInit	= true;
	}
uint8_t Driver_AnoRadRarioModule::HardwareInitialization(void)
	{
	if (this->packetSize == 0)
		{
		return Class_HAL::ERROR_RM0_PACKET_SIZE_NOT_SET;
		}
//	return 0;
	//TODO: написать норм драйвер
	//this->IOInit();
//	PORTC.DIRSET	= 1<<4;
//	return 0;
	const uint8_t CONFIG[][2] =
	{
		/* 0x01 */ { RFM69_REGISTER_01_OPMODE, RF_OPMODE_SEQUENCER_ON | RF_OPMODE_LISTEN_OFF | RF_OPMODE_STANDBY },
		//		/* 0x02 */ { REG_DATAMODUL, RF_DATAMODUL_DATAMODE_PACKET | RF_DATAMODUL_MODULATIONTYPE_FSK | RF_DATAMODUL_MODULATIONSHAPING_00 }, //no shaping
		/* 0x02 */ { RFM69_REGISTER_02_DATAMODUL, RF_DATAMODUL_DATAMODE_PACKET | RF_DATAMODUL_MODULATIONTYPE_FSK | RFM69_REGISTER_02_DATAMODUL_10_MODULATION_SHAPING_FCK_GF_05 }, //GFSK
		//		/* 0x03 */ { REG_BITRATEMSB, RF_BITRATEMSB_55555}, //default:4.8 KBPS
		//		/* 0x04 */ { REG_BITRATELSB, RF_BITRATELSB_55555}, //FREQ=32MHZ/RF[15:0]
		//		/* 0x05 */ { REG_FDEVMSB, RF_FDEVMSB_50000}, //default:5khz, (FDEV + BitRate/2 <= 500Khz)
		//		/* 0x06 */ { REG_FDEVLSB, RF_FDEVLSB_50000},
		//		/* 0x07 */ { REG_FRFMSB, (freqBand==RF69_315MHZ ? RF_FRFMSB_315 : (freqBand==RF69_433MHZ ? RF_FRFMSB_433 : (freqBand==RF69_868MHZ ? RF_FRFMSB_868 : RF_FRFMSB_915))) },
		//		/* 0x08 */ { REG_FRFMID, (freqBand==RF69_315MHZ ? RF_FRFMID_315 : (freqBand==RF69_433MHZ ? RF_FRFMID_433 : (freqBand==RF69_868MHZ ? RF_FRFMID_868 : RF_FRFMID_915))) },
		//		/* 0x09 */ { REG_FRFLSB, (freqBand==RF69_315MHZ ? RF_FRFLSB_315 : (freqBand==RF69_433MHZ ? RF_FRFLSB_433 : (freqBand==RF69_868MHZ ? RF_FRFLSB_868 : RF_FRFLSB_915))) },

		//		/* 0x03 */ { REG_BITRATEMSB, RFM69_RF_BITRATEMSB_FROM_BITRATE(55555)},
		//		/* 0x04 */ { REG_BITRATELSB, RFM69_RF_BITRATELSB_FROM_BITRATE(55555)},
		//		/* 0x03 */ { REG_BITRATEMSB, RFM69_RF_BITRATEMSB_FROM_BITRATE(64000)},
		//		/* 0x04 */ { REG_BITRATELSB, RFM69_RF_BITRATELSB_FROM_BITRATE(64000)},
		/* 0x03 */ { RFM69_REGISTER_03_BITRATEMSB, RFM69_RF_BITRATEMSB_FROM_BITRATE(128000)},
		/* 0x04 */ { RFM69_REGISTER_04_BITRATELSB, RFM69_RF_BITRATELSB_FROM_BITRATE(128000)},
		/* 0x05 */ { RFM69_REGISTER_05_FDEVMSB, RFM69_FDEVMSB_FROM_FREQ(100000)}, //default:5khz, (FDEV + BitRate/2 <= 500Khz)
		/* 0x06 */ { RFM69_REGISTER_06_FDEVLSB, RFM69_FDEVLSB_FROM_FREQ(100000)},
		/* 0x07 */ { RFM69_REGISTER_07_FRFMSB, RFM69_FRFMSB_FROM_FREQ(RFM69_FREQUENCY) },
		/* 0x08 */ { RFM69_REGISTER_08_FRFMID, RFM69_FRFMID_FROM_FREQ(RFM69_FREQUENCY) },
		/* 0x09 */ { RFM69_REGISTER_09_FRFLSB, RFM69_FRFLSB_FROM_FREQ(RFM69_FREQUENCY) },
		
		// looks like PA1 and PA2 are not implemented on RFM69W, hence the max output power is 13dBm
		// +17dBm and +20dBm are possible on RFM69HW
		// +13dBm formula: Pout=-18+OutputPower (with PA0 or PA1**)
		// +17dBm formula: Pout=-14+OutputPower (with PA1 and PA2)**
		// +20dBm formula: Pout=-11+OutputPower (with PA1 and PA2)** and high power PA settings (section 3.3.7 in datasheet)
		///* 0x11 */ { REG_PALEVEL, RF_PALEVEL_PA0_ON | RF_PALEVEL_PA1_OFF | RF_PALEVEL_PA2_OFF | RF_PALEVEL_OUTPUTPOWER_11111},
		///* 0x13 */ { REG_OCP, RF_OCP_ON | RF_OCP_TRIM_95 }, //over current protection (default is 95mA)
		
		///* 0x18*/ { REG_LNA,  RF_LNA_ZIN_200 | RF_LNA_CURRENTGAIN }, //as suggested by mav here: http://lowpowerlab.com/forum/index.php/topic,296.msg1571.html
		
		// RXBW defaults are { REG_RXBW, RF_RXBW_DCCFREQ_010 | RF_RXBW_MANT_24 | RF_RXBW_EXP_5} (RxBw: 10.4khz)
		/* 0x19 */ { RFM69_REGISTER_19_RXBW, RF_RXBW_DCCFREQ_010 | RF_RXBW_MANT_16 | RF_RXBW_EXP_2 }, //(BitRate < 2 * RxBw)
		/* 0x25 */ { RFM69_REGISTER_25_DIOMAPPING1, RF_DIOMAPPING1_DIO0_01 }, //DIO0 is the only IRQ we're using
		/* 0x29 */ { RFM69_REGISTER_29_RSSITHRESH, 220 }, //must be set to dBm = (-Sensitivity / 2) - default is 0xE4=228 so -114dBm
		///* 0x2d */ { REG_PREAMBLELSB, RF_PREAMBLESIZE_LSB_VALUE } // default 3 preamble bytes 0xAAAAAA
		//		/* 0x2e */ { REG_SYNCCONFIG, RF_SYNC_ON | RF_SYNC_FIFOFILL_AUTO | RF_SYNC_SIZE_2 | RF_SYNC_TOL_0 },
		//		/* 0x2f */ { REG_SYNCVALUE1, 0x2D },      //attempt to make this compatible with sync1 byte of RFM12B lib
		//		/* 0x30 */ { REG_SYNCVALUE2, networkID }, //NETWORK ID

		{ RFM69_REGISTER_2C_PREAMBLEMSB, 0x00},
		{ RFM69_REGISTER_2D_PREAMBLELSB, 0x06},

		/* 0x2e */ { RFM69_REGISTER_2E_SYNCCONFIG, RF_SYNC_ON | RF_SYNC_FIFOFILL_AUTO | RF_SYNC_SIZE_4 | RF_SYNC_TOL_0 },
		/* 0x2f */ { RFM69_REGISTER_2F_SYNCVALUE1, 0x59 },      //attempt to make this compatible with sync1 byte of RFM12B lib
		/* 0x30 */ { RFM69_REGISTER_30_SYNCVALUE2, 0xa6 }, //NETWORK ID
		/* 0x30 */ { RFM69_REGISTER_31_SYNCVALUE3, 0xa6 },
		/* 0x30 */ { RFM69_REGISTER_32_SYNCVALUE4, 0x65 },


		//		/* 0x37 */ { REG_PACKETCONFIG1, RF_PACKET1_FORMAT_VARIABLE | RF_PACKET1_DCFREE_OFF | RF_PACKET1_CRC_ON | RF_PACKET1_CRCAUTOCLEAR_ON | RF_PACKET1_ADRSFILTERING_OFF },
		//		/* 0x38 */ { REG_PAYLOADLENGTH, 66 }, //in variable length mode: the max frame size, not used in TX
#ifdef RFM69_HW_CRC
				/* 0x37 */ { RFM69_REGISTER_37_PACKETCONFIG1, RF_PACKET1_FORMAT_FIXED | RF_PACKET1_DCFREE_OFF | RF_PACKET1_CRC_ON  | RF_PACKET1_CRCAUTOCLEAR_ON  | RF_PACKET1_ADRSFILTERING_OFF },
#else
				/* 0x37 */ { RFM69_REGISTER_37_PACKETCONFIG1, RF_PACKET1_FORMAT_FIXED | RF_PACKET1_DCFREE_OFF | RF_PACKET1_CRC_OFF | RF_PACKET1_CRCAUTOCLEAR_OFF | RF_PACKET1_ADRSFILTERING_OFF },
#endif
		//		/* 0x37 */ { RFM69_REGISTER_37_PACKETCONFIG1, RF_PACKET1_FORMAT_FIXED | RF_PACKET1_DCFREE_OFF | RF_PACKET1_CRC_ON  | RF_PACKET1_CRCAUTOCLEAR_OFF | RF_PACKET1_ADRSFILTERING_OFF },
		/* 0x38 */ { RFM69_REGISTER_38_PAYLOADLENGTH, this->packetSize }, //in variable length mode: the max frame size, not used in TX
//		/* 0x38 */ { RFM69_REGISTER_38_PAYLOADLENGTH,  4}, //in variable length mode: the max frame size, not used in TX
		//* 0x39 */ { REG_NODEADRS, nodeID }, //turned off because we're not using address filtering
//		/* 0x3C */ { RFM69_REGISTER_3C_FIFOTHRESH, RF_FIFOTHRESH_TXSTART_FIFONOTEMPTY | RF_FIFOTHRESH_VALUE }, //TX on FIFO not empty
//		/* 0x3C */ { RFM69_REGISTER_3C_FIFOTHRESH, RFM69_REGISTER_3C_FIFOTHRESH_7_TX_START_CONDITION_FIFO_NOT_EMPTY | RF_FIFOTHRESH_VALUE }, //TX on FIFO not empty
		/* 0x3C */ { RFM69_REGISTER_3C_FIFOTHRESH, (uint8_t)(this->packetSize-1) }, //TX on FIFO not empty
		/* 0x3d */ { RFM69_REGISTER_3D_PACKETCONFIG2, RF_PACKET2_RXRESTARTDELAY_2BITS | RF_PACKET2_AUTORXRESTART_ON | RF_PACKET2_AES_OFF }, //RXRESTARTDELAY must match transmitter PA ramp-down time (bitrate dependent)
		/* 0x6F */ { RFM69_REGISTER_6F_TESTDAGC, RF_DAGC_IMPROVED_LOWBETA0 }, // run DAGC continuously in RX mode, recommended default for AfcLowBetaOn=0
		{255, 0}
	};

	//	pinMode(_slaveSelectPin, OUTPUT);
	
	//	SPI.setDataMode(SPI_MODE0);
	//	SPI.setBitOrder(MSBFIRST);
	//	SPI.setClockDivider(SPI_CLOCK_DIV2); //max speed, except on Due which can run at system clock speed
	//	SPI.begin();
	
//	return 0;
	//this->writeRegister(RFM69_REGISTER_2F_SYNCVALUE1, 0xaa);
	//this->writeRegister(RFM69_REGISTER_2F_SYNCVALUE1, 0x55);
	do this->writeRegister(RFM69_REGISTER_2F_SYNCVALUE1, 0xaa); while (this->readRegister(RFM69_REGISTER_2F_SYNCVALUE1) != 0xaa);
	do this->writeRegister(RFM69_REGISTER_2F_SYNCVALUE1, 0x55); while (this->readRegister(RFM69_REGISTER_2F_SYNCVALUE1) != 0x55);
	
	for (uint8_t i = 0; CONFIG[i][0] != 255; i++)
		{
		this->writeRegister(CONFIG[i][0], CONFIG[i][1]);
		}

	//	RFM69_SetFrequencyCarrier(432750592);

	// Encryption is persistent between resets and can trip you up during debugging.
	// Disable it during initialization so we always start from a known state.
	radio.encrypt(0);
	
//	this->ClearFifo();

	radio.setHighPower(true); //called regardless if it's a RFM69W or RFM69HW
	radio.setMode(RF69_MODE_STANDBY);
	while ((this->readRegister(RFM69_REGISTER_27_IRQFLAGS1) & RFM69_REGISTER_27_IRQFLAGS1_7_MODE_READY_SET) == 0x00); // Wait for ModeReady
	//	radio.encrypt(ENCRYPTKEY);
	//radio.encrypt(0);
	//radio.promiscuous(promiscuousMode);
	this->isRMInit	= true;
	return Class_HAL::ERROR_NO_ERRORS;
	}
void Driver_AnoRadRarioModule::setPacketSize(uint8_t size)
	{
	if (!this->isRMInit)
		{
		this->packetSize	= size;
		}
	this->writeRegister(RFM69_REGISTER_38_PAYLOADLENGTH,this->packetSize);
	}
void Driver_AnoRadRarioModule::writeRegister(uint8_t addr, uint8_t value)
	{
	SPI.select();
	SPI.transfer(addr | 0x80);
	SPI.transfer(value);
	SPI.unselect();
	}
uint8_t Driver_AnoRadRarioModule::readRegister(uint8_t addr)
	{
	SPI.select();
	SPI.transfer(addr & 0x7F);
	uint8_t regval = SPI.transfer(0);
	SPI.unselect();
	return regval;
	}
void Driver_AnoRadRarioModule::IOInit(void)
	{
//	IOPort.SetDirIn(RFM69_MISO_PORT_t,		RFM69_MISO_PIN);
//	IOPort.SetDirOut(RFM69_SS_PORT_t,		RFM69_SS_PIN);
//	IOPort.SetDirOut(RFM69_MOSI_PORT_t,		RFM69_MOSI_PIN);
//	IOPort.SetDirOut(RFM69_CLK_PORT_t,		RFM69_CLK_PIN);
//	IOPort.SetOutLow(RFM69_CLK_PORT_t,		RFM69_CLK_PIN);
/*
	HAL.IO.SetDirOut(RFM69_CLK_PIN_HAL);
	HAL.IO.SetOutLow(RFM69_CLK_PIN_HAL);
	HAL.IO.SetDirIn(RFM69_MISO_PIN_HAL);
	HAL.IO.SetDirOut(RFM69_MOSI_PIN_HAL);
	HAL.IO.SetDirOut(RFM69_SS_PIN_HAL);
	
	
	//IOPort.SetDirIn(RFM69_DIO0_PORT_t,		RFM69_DIO0_PIN);
	HAL.IO.SetDirIn(RFM69_DIO5_PIN_HAL);

*/
	RFM69ClkPin::SetDirOut();
	RFM69ClkPin::SetOutHigh();
	
	RFM69MisoPin::SetDirIn();

	RFM69MosiPin::SetDirOut();
	RFM69MosiPin::SetOutHigh();
	RFM69SSPin::SetDirOut();
	RFM69SSPin::SetOutHigh();
	
	RFM69Dio5Pin::SetDirIn();
	

	//PORTC.DIRSET		= 1<<4;
	RFM69SPI_SS_Pin::SetDirOut();
//	RFM69SPI_SS_Pin::SetOutHigh();
	//					  [double CLK]	[enable][DORD] [master][transfer mode][clk prescaller]
	RFM69_SPI.CTRL		= 1<<7			| 1<<6	| 0<<5 | 1<<4 | (0<<3 | 0<<2) | (0<<1 | 0<<0); //-V501
	//	RFM69_SPI.CTRL	= 0<<7			| 1<<6	| 0<<5 | 1<<4 | (0<<3 | 0<<2) | (1<<1 | 1<<0);
	RFM69_SPI.INTCTRL = SPI_INTLVL_OFF_gc ; // no interrupt
	}
/*void Driver_AnoRadRarioModule::TXMode(void)
	{
	radio.receiveBegin();
	}*/
void Driver_AnoRadRarioModule::getPacket(void)
	{
	radio.setMode(RF69_MODE_STANDBY);
	radio.select();
	SPI.transfer(REG_FIFO & 0x7f);
	for (uint8_t i= 0; i < this->packetSize; i++)
		{
		this->rxBuffer[i]	= SPI.transfer(0);
		//_RXBuffer[i] = SPI.transfer(0);
		}
	radio.unselect();
	}
uint8_t Driver_AnoRadRarioModule::getRSSIRaw(void)
	{
	return radio.readRSSI_RAW();
	}
bool Driver_AnoRadRarioModule::isPacketReceived(void)
	{
	//return RFM69_DIO0_HIGH;
	return radio.isPacketReceivedHigh();
	}
void Driver_AnoRadRarioModule::receiveBegin(void)
	{
	radio.receiveBegin();
	}
void Driver_AnoRadRarioModule::sendBufferToRM(void)
	{
	//void RFM69::sendFrame(uint8_t toAddress, const void* buffer, uint8_t bufferSize)
	radio.select();
	SPI.transfer(REG_FIFO | 0x80);
	for (uint8_t i=0; i < this->packetSize; i++)
		{
		SPI.transfer(this->txBuffer[i]);
		}
	radio.unselect();
	}
bool Driver_AnoRadRarioModule::switchMode(TRX_STATE mode)	
	{
	switch (mode)
		{
		case Driver_AnoRadRarioModuleInterfaceClass::TRX_STATE_IDLE:
			{
			
			}
		break;

		case Driver_AnoRadRarioModuleInterfaceClass::TRX_STATE_RECEIVING:
			{
			if (radio._isRFM69HW)
				{
				radio.setHighPowerRegs(false);
				}
			radio.writeReg(REG_OPMODE, (radio.readReg(RFM69_REGISTER_01_OPMODE) & 0xE3) | RF_OPMODE_RECEIVER);
			}
		break;

		case Driver_AnoRadRarioModuleInterfaceClass::TRX_STATE_TRANSMITTING:
			{
			if (radio._isRFM69HW)
				{
				radio.setHighPowerRegs(true);
				}
			radio.writeReg(REG_OPMODE, (radio.readReg(RFM69_REGISTER_01_OPMODE) & 0xE3) | RF_OPMODE_TRANSMITTER);
			//uint8_t reg	= radio.readReg(RFM69_REGISTER_01_OPMODE) & 0xE3;
			//reg |= (RF_OPMODE_TRANSMITTER);
			//radio.writeReg(REG_OPMODE, RF_OPMODE_TRANSMITTER);
			//radio.writeReg(REG_OPMODE, reg);
			}
		break;

		case Driver_AnoRadRarioModuleInterfaceClass::TRX_STATE_STANDBY:
			{
			if (radio._isRFM69HW)
				{
				radio.setHighPowerRegs(true);
				}
			radio.writeReg(REG_OPMODE, (radio.readReg(RFM69_REGISTER_01_OPMODE) & 0xE3) | RF_OPMODE_STANDBY);
			}
		break;

		case Driver_AnoRadRarioModuleInterfaceClass::TRX_STATE_UNKNOWN:
			{
			
			}
		break;
		}
	return true;
	}
uint8_t Driver_AnoRadRarioModule::startTX(void)
	{
	this->switchMode(TRX_STATE_TRANSMITTING);
	//radio.setMode(RF69_MODE_TX);
	return Class_HAL::ERROR_NO_ERRORS;
	}
void Driver_AnoRadRarioModule::setTXPower(uint8_t pwr)
	{
	radio.setPowerLevel(pwr);
	}
void Driver_AnoRadRarioModule::deviceEnable(void)
	{
	radio.writeReg(REG_OPMODE, (radio.readReg(RFM69_REGISTER_01_OPMODE) & 0xE3) | RF_OPMODE_STANDBY);
	}
void Driver_AnoRadRarioModule::deviceDisable(void)
	{
	radio.writeReg(REG_OPMODE, (radio.readReg(RFM69_REGISTER_01_OPMODE) & 0xE3) | RF_OPMODE_SLEEP);
	}
void Driver_AnoRadRarioModule::waitModeReady(void)
	{
	while ((radio.readReg(REG_IRQFLAGS1) & RF_IRQFLAGS1_MODEREADY) == 0x00); // Wait for ModeReady
	}
void Driver_AnoRadRarioModule::ClearFifo(void)
	{
	radio.select();
	SPI.transfer(REG_FIFO | 0x80);
	for (uint8_t i=0; i < this->packetSize; i++)
		{
		SPI.transfer(0);
		}
	radio.unselect();
	}
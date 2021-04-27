// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

void Driver_AnoRadRarioModule::setPacketSize(uint8_t size)
	{
	if (!this->isRMInit)
		{
		this->packetSize	= size;
		}
	RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 this->packetSize);
	}
/*uint8_t Driver_AnoRadRarioModule::HardwareInitialization(void)
	{
	return this->initRM();
	//return Class_HAL::ERROR_NO_ERRORS;
	}*/
uint8_t Driver_AnoRadRarioModule::HardwareInitialization(void)//ONLY AFTER setPacketSize
	{
	if (this->packetSize == 0)
		{
		this->isRMInit	= false;
		return Class_HAL::ERROR_RM0_PACKET_SIZE_NOT_SET;
		}
	//RFM22B_ioinit();//Йобыныйтыврот - эта штука определена в конструкторе класса драйвера, но там, видимо, она не отрабатывается =(
	this->RFM22B_reset();
	uint8_t i=0;
	while(1)
		{
		//PORTD	^= 1<<4;
		if (RFM22B_getVersion() == 0x06)
			{
			break;
			}
		else
			{
			_delay_ms(250);
			}
		this->RFM22B_init();
		if (++i > this->RM_INIT_MAX_RETRIES)
			{
			this->isRMInit	= false;
			return Class_HAL::ERROR_RM0_INIT_FAILED;
			}
		}

	this->isRMInit	= true;
	return Class_HAL::ERROR_NO_ERRORS;
	}
uint8_t Driver_AnoRadRarioModule::sendPacket(void)
	{
	if (!this->isTXBufInit)
		{
		return Class_HAL::ERROR_RM0_TX_BUF_NOT_INIT;
		}
	if (!this->isRMInit)
		{
		return Class_HAL::ERROR_RM0_NOT_INIT;
		}
	this->RFM22B_txMode();
	return Class_HAL::ERROR_NO_ERRORS;
	}
void Driver_AnoRadRarioModule::setTXPower(uint8_t pwr)
	{
	if (pwr > this->TX_POWER_MAX)
		pwr	= this->TX_POWER_MAX;
	this->txPower	= pwr;
	RFM22B_RegisterWrite(RFM22B_REGISTER_6D_TX_POWER,                               (RFM22B_LNA_SW | this->txPower));		// Tx power to max
	}
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
		uint8_t Driver_AnoRadRarioModule::clearTXBuf(void)
			{
			if (!this->isTXBufInit)
				{
				return Class_HAL::ERROR_RM0_TX_BUF_NOT_INIT;
				}
			for (uint8_t i=0;i<this->packetSize;i++)
				{
				this->txBuffer[i]	= 0;
				}
			return Class_HAL::ERROR_NO_ERRORS;
			}
		uint8_t Driver_AnoRadRarioModule::clearRXBuf(void)
			{
			if (!this->isRXBufInit)
				{
				return Class_HAL::ERROR_RM0_RX_BUF_NOT_INIT;
				}
			for (uint8_t i=0;i<this->packetSize;i++)
				{
				this->rxBuffer[i]	= 0;
				}
			return Class_HAL::ERROR_NO_ERRORS;
			}
		void Driver_AnoRadRarioModule::RFM22B_init(void)
			{
//			this->RFM22B_init128kbps50khz();
			this->RFM22B_init128kbps100khz();
			//this->RFM22B_init128kbps50khzNoHeader();
			}
		void Driver_AnoRadRarioModule::RFM22B_init4Kbps_w_crc(void)
			{
			RFM22B_RegisterWrite(RFM22B_REGISTER_1C_IF_FILTER_BANDWIDTH,                    0xAB);
			RFM22B_RegisterWrite(RFM22B_REGISTER_1D_AFC_LOOP_GEARSHIFT_OVERRIDE,            0x40);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_20_CLOCK_RECOVERY_OVERSAMPLING_RATIO,      0xEE);;		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_21_CLOCK_RECOVERY_OFFSET_2,                0x40);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_22_CLOCK_RECOVERY_OFFSET_1,                0x2B);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_23_CLOCK_RECOVERY_OFFSET_0,                0xB1);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_24_CLOCK_RECOVERY_TIMING_LOOP_GAIN_1,      0x00);		// clock recovery timing
			RFM22B_RegisterWrite(RFM22B_REGISTER_25_CLOCK_RECOVERY_TIMING_LOOP_GAIN_0,      0x09);		// clock recovery timing
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_2A_AFC_LIMITER,                            0x24);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2C_OOK_COUNTER_VALUE_1,                    0x29);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2D_OOK_COUNTER_VALUE_2,                    0x38);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2E_SLICER_PEAK_HOLD,                       0x29);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_30_DATA_ACCESS_CONTROL,                    0xAC);

			RFM22B_RegisterWrite(RFM22B_REGISTER_32_HEADER_CONTROL_1,                       0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_33_HEADER_CONTROL_2,						(0<<7 | 0x0e));

			RFM22B_RegisterWrite(RFM22B_REGISTER_34_PREAMBLE_LENGTH,                        this->PREAMBLE_LENGTH);
			RFM22B_RegisterWrite(RFM22B_REGISTER_35_PREAMBLE_DETECTION_CONTROL,             0x32);

			RFM22B_RegisterWrite(RFM22B_REGISTER_36_SYNC_WORD_3,                            this->SYNC_WORD_3);		// synchronize word
			RFM22B_RegisterWrite(RFM22B_REGISTER_37_SYNC_WORD_2,                            this->SYNC_WORD_2);
			RFM22B_RegisterWrite(RFM22B_REGISTER_38_SYNC_WORD_1,                            this->SYNC_WORD_1);
			RFM22B_RegisterWrite(RFM22B_REGISTER_39_SYNC_WORD_0,                            this->SYNC_WORD_0);

			RFM22B_RegisterWrite(RFM22B_REGISTER_3A_TRANSMIT_HEADER_3,                      this->TX_HEADER_3);		// set tx header 3
			RFM22B_RegisterWrite(RFM22B_REGISTER_3B_TRANSMIT_HEADER_2,                      this->TX_HEADER_2);		// set tx header 2
			RFM22B_RegisterWrite(RFM22B_REGISTER_3C_TRANSMIT_HEADER_1,                      this->TX_HEADER_1);		// set tx header 1
			RFM22B_RegisterWrite(RFM22B_REGISTER_3D_TRANSMIT_HEADER_0,                      this->TX_HEADER_0);		// set tx header 0
			//RFM22B_RegisterWrite(0x3E, 17);		// set packet length to 17 bytes (max size: 255 bytes)
			//	RFM22B_setTransmitPacketSize(PKTSIZE);	// set packet length to PKTSIZE bytes (max size: 255 bytes)
			RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 (this->packetSize));//+1 - переменная длина пакета
			//    RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 PKTSIZE+1);//+1 - переменная длина пакета
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_3F_CHECK_HEADER_3,                         0x00);		// set rx header
			RFM22B_RegisterWrite(RFM22B_REGISTER_40_CHECK_HEADER_2,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_41_CHECK_HEADER_1,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_42_CHECK_HEADER_0,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_43_HEADER_ENABLE_3,                        0xFF);		// check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_44_HEADER_ENABLE_2,                        0xFF);		// Check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_45_HEADER_ENABLE_1,                        0xFF);		// check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_46_HEADER_ENABLE_0,                        0xFF);		// Check all bits


			//TX DATA RATE
			RFM22B_RegisterWrite(RFM22B_REGISTER_6E_TX_DATA_RATE_1,                         0x20);		// TX data rate 1
			RFM22B_RegisterWrite(RFM22B_REGISTER_6F_TX_DATA_RATE_0,                         0xC5);		// TX data rate 0
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_6D_TX_POWER,                               (RFM22B_LNA_SW | this->txPower));		// Tx power to max
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_70_MODULATION_MODE_CONTROL_1,              0x2c);
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x22);//FSK
			RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x23);//GFSK
			RFM22B_RegisterWrite(RFM22B_REGISTER_72_FREQUENCY_DEVIATION,                    0x50);		// Frequency deviation setting to 50K=80*625

			//	RFM22B_RegisterWrite(RFM22B_REGISTER_73_FREQUENCY_OFFSET_1,                     0x00);		// No frequency offset
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_74_FREQUENCY_OFFSET_2,                     0x00);		// No frequency offset

			RFM22B_RegisterWrite(RFM22B_REGISTER_75_FREQUENCY_BAND_SELECT,                  0x54);		// frequency set to 446MHz
			RFM22B_RegisterWrite(RFM22B_REGISTER_76_NOMINAL_CARRIER_FREQUENCY_1,            0x96);		// frequency set to 446MHz
			RFM22B_RegisterWrite(RFM22B_REGISTER_77_NOMINAL_CARRIER_FREQUENCY_0,            0x00);		// frequency set to 446Mhz
			}
		void Driver_AnoRadRarioModule::RFM22B_init8kbps(void)
			{
			RFM22B_RegisterWrite(RFM22B_REGISTER_1C_IF_FILTER_BANDWIDTH,                    0xAB);
			RFM22B_RegisterWrite(RFM22B_REGISTER_1D_AFC_LOOP_GEARSHIFT_OVERRIDE,            0x40);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_20_CLOCK_RECOVERY_OVERSAMPLING_RATIO,      0x77);;		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_21_CLOCK_RECOVERY_OFFSET_2,                0x20);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_22_CLOCK_RECOVERY_OFFSET_1,                0x57);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_23_CLOCK_RECOVERY_OFFSET_0,                0x62);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_24_CLOCK_RECOVERY_TIMING_LOOP_GAIN_1,      0x00);		// clock recovery timing
			RFM22B_RegisterWrite(RFM22B_REGISTER_25_CLOCK_RECOVERY_TIMING_LOOP_GAIN_0,      0x1E);		// clock recovery timing
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_2A_AFC_LIMITER,                            0x24);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2C_OOK_COUNTER_VALUE_1,                    0x28);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2D_OOK_COUNTER_VALUE_2,                    0x9C);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2E_SLICER_PEAK_HOLD,                       0x29);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_30_DATA_ACCESS_CONTROL,                    0xA8);

			RFM22B_RegisterWrite(RFM22B_REGISTER_32_HEADER_CONTROL_1,                       0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_33_HEADER_CONTROL_2,						(0<<7 | 0x0e));

			RFM22B_RegisterWrite(RFM22B_REGISTER_34_PREAMBLE_LENGTH,                        this->PREAMBLE_LENGTH);
			RFM22B_RegisterWrite(RFM22B_REGISTER_35_PREAMBLE_DETECTION_CONTROL,             0x32);

			RFM22B_RegisterWrite(RFM22B_REGISTER_36_SYNC_WORD_3,                            this->SYNC_WORD_3);		// synchronize word
			RFM22B_RegisterWrite(RFM22B_REGISTER_37_SYNC_WORD_2,                            this->SYNC_WORD_2);
			RFM22B_RegisterWrite(RFM22B_REGISTER_38_SYNC_WORD_1,                            this->SYNC_WORD_1);
			RFM22B_RegisterWrite(RFM22B_REGISTER_39_SYNC_WORD_0,                            this->SYNC_WORD_0);

			RFM22B_RegisterWrite(RFM22B_REGISTER_3A_TRANSMIT_HEADER_3,                      this->TX_HEADER_3);		// set tx header 3
			RFM22B_RegisterWrite(RFM22B_REGISTER_3B_TRANSMIT_HEADER_2,                      this->TX_HEADER_2);		// set tx header 2
			RFM22B_RegisterWrite(RFM22B_REGISTER_3C_TRANSMIT_HEADER_1,                      this->TX_HEADER_1);		// set tx header 1
			RFM22B_RegisterWrite(RFM22B_REGISTER_3D_TRANSMIT_HEADER_0,                      this->TX_HEADER_0);		// set tx header 0
			//RFM22B_RegisterWrite(0x3E, 17);		// set packet length to 17 bytes (max size: 255 bytes)
			//	RFM22B_setTransmitPacketSize(PKTSIZE);	// set packet length to PKTSIZE bytes (max size: 255 bytes)
			RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 (this->packetSize));//+1 - переменная длина пакета
			//    RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 PKTSIZE+1);//+1 - переменная длина пакета
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_3F_CHECK_HEADER_3,                         0x00);		// set rx header
			RFM22B_RegisterWrite(RFM22B_REGISTER_40_CHECK_HEADER_2,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_41_CHECK_HEADER_1,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_42_CHECK_HEADER_0,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_43_HEADER_ENABLE_3,                        0xFF);		// check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_44_HEADER_ENABLE_2,                        0xFF);		// Check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_45_HEADER_ENABLE_1,                        0xFF);		// check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_46_HEADER_ENABLE_0,                        0xFF);		// Check all bits


			//TX DATA RATE
			RFM22B_RegisterWrite(RFM22B_REGISTER_6E_TX_DATA_RATE_1,                         0x41);;		// TX data rate 1
			RFM22B_RegisterWrite(RFM22B_REGISTER_6F_TX_DATA_RATE_0,                         0x89);		// TX data rate 0
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_6D_TX_POWER,                               (RFM22B_LNA_SW | this->txPower));		// Tx power to max
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_70_MODULATION_MODE_CONTROL_1,              0x2c);
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x22);//FSK
			RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x23);//GFSK
			RFM22B_RegisterWrite(RFM22B_REGISTER_72_FREQUENCY_DEVIATION,                    0x50);		// Frequency deviation setting to 50K=80*625

			//	RFM22B_RegisterWrite(RFM22B_REGISTER_73_FREQUENCY_OFFSET_1,                     0x00);		// No frequency offset
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_74_FREQUENCY_OFFSET_2,                     0x00);		// No frequency offset

			RFM22B_RegisterWrite(RFM22B_REGISTER_75_FREQUENCY_BAND_SELECT,                  0x54);		// frequency set to 446MHz
			RFM22B_RegisterWrite(RFM22B_REGISTER_76_NOMINAL_CARRIER_FREQUENCY_1,            0x96);		// frequency set to 446MHz
			RFM22B_RegisterWrite(RFM22B_REGISTER_77_NOMINAL_CARRIER_FREQUENCY_0,            0x00);		// frequency set to 446Mhz
			}
		void Driver_AnoRadRarioModule::RFM22B_init16kbps(void)
			{
			RFM22B_RegisterWrite(RFM22B_REGISTER_1C_IF_FILTER_BANDWIDTH,                    0xAC);
			RFM22B_RegisterWrite(RFM22B_REGISTER_1D_AFC_LOOP_GEARSHIFT_OVERRIDE,            0x40);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_20_CLOCK_RECOVERY_OVERSAMPLING_RATIO,      0xBC);;		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_21_CLOCK_RECOVERY_OFFSET_2,                0x00);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_22_CLOCK_RECOVERY_OFFSET_1,                0xAE);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_23_CLOCK_RECOVERY_OFFSET_0,                0xC3);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_24_CLOCK_RECOVERY_TIMING_LOOP_GAIN_1,      0x00);		// clock recovery timing
			RFM22B_RegisterWrite(RFM22B_REGISTER_25_CLOCK_RECOVERY_TIMING_LOOP_GAIN_0,      0x72);		// clock recovery timing
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_2A_AFC_LIMITER,                            0x28);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2C_OOK_COUNTER_VALUE_1,                    0x28);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2D_OOK_COUNTER_VALUE_2,                    0x4E);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2E_SLICER_PEAK_HOLD,                       0x29);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_30_DATA_ACCESS_CONTROL,                    0xA8);

			RFM22B_RegisterWrite(RFM22B_REGISTER_32_HEADER_CONTROL_1,                       0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_33_HEADER_CONTROL_2,						(0<<7 | 0x0e));

			RFM22B_RegisterWrite(RFM22B_REGISTER_34_PREAMBLE_LENGTH,                        this->PREAMBLE_LENGTH);
			RFM22B_RegisterWrite(RFM22B_REGISTER_35_PREAMBLE_DETECTION_CONTROL,             0x32);

			RFM22B_RegisterWrite(RFM22B_REGISTER_36_SYNC_WORD_3,                            this->SYNC_WORD_3);		// synchronize word
			RFM22B_RegisterWrite(RFM22B_REGISTER_37_SYNC_WORD_2,                            this->SYNC_WORD_2);
			RFM22B_RegisterWrite(RFM22B_REGISTER_38_SYNC_WORD_1,                            this->SYNC_WORD_1);
			RFM22B_RegisterWrite(RFM22B_REGISTER_39_SYNC_WORD_0,                            this->SYNC_WORD_0);

			RFM22B_RegisterWrite(RFM22B_REGISTER_3A_TRANSMIT_HEADER_3,                      this->TX_HEADER_3);		// set tx header 3
			RFM22B_RegisterWrite(RFM22B_REGISTER_3B_TRANSMIT_HEADER_2,                      this->TX_HEADER_2);		// set tx header 2
			RFM22B_RegisterWrite(RFM22B_REGISTER_3C_TRANSMIT_HEADER_1,                      this->TX_HEADER_1);		// set tx header 1
			RFM22B_RegisterWrite(RFM22B_REGISTER_3D_TRANSMIT_HEADER_0,                      this->TX_HEADER_0);		// set tx header 0
			//RFM22B_RegisterWrite(0x3E, 17);		// set packet length to 17 bytes (max size: 255 bytes)
			//	RFM22B_setTransmitPacketSize(PKTSIZE);	// set packet length to PKTSIZE bytes (max size: 255 bytes)
			RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 (this->packetSize));//+1 - переменная длина пакета
			//    RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 PKTSIZE+1);//+1 - переменная длина пакета
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_3F_CHECK_HEADER_3,                         0x00);		// set rx header
			RFM22B_RegisterWrite(RFM22B_REGISTER_40_CHECK_HEADER_2,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_41_CHECK_HEADER_1,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_42_CHECK_HEADER_0,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_43_HEADER_ENABLE_3,                        0xFF);		// check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_44_HEADER_ENABLE_2,                        0xFF);		// Check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_45_HEADER_ENABLE_1,                        0xFF);		// check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_46_HEADER_ENABLE_0,                        0xFF);		// Check all bits


			//TX DATA RATE
			RFM22B_RegisterWrite(RFM22B_REGISTER_6E_TX_DATA_RATE_1,                         0x83);;		// TX data rate 1
			RFM22B_RegisterWrite(RFM22B_REGISTER_6F_TX_DATA_RATE_0,                         0x12);		// TX data rate 0
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_6D_TX_POWER,                               (RFM22B_LNA_SW | this->txPower));		// Tx power to max
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_70_MODULATION_MODE_CONTROL_1,              0x2c);
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x22);//FSK
			RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x23);//GFSK
			RFM22B_RegisterWrite(RFM22B_REGISTER_72_FREQUENCY_DEVIATION,                    0x50);		// Frequency deviation setting to 50K=80*625

			//	RFM22B_RegisterWrite(RFM22B_REGISTER_73_FREQUENCY_OFFSET_1,                     0x00);		// No frequency offset
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_74_FREQUENCY_OFFSET_2,                     0x00);		// No frequency offset

			RFM22B_RegisterWrite(RFM22B_REGISTER_75_FREQUENCY_BAND_SELECT,                  0x54);		// frequency set to 446MHz
			RFM22B_RegisterWrite(RFM22B_REGISTER_76_NOMINAL_CARRIER_FREQUENCY_1,            0x96);		// frequency set to 446MHz
			RFM22B_RegisterWrite(RFM22B_REGISTER_77_NOMINAL_CARRIER_FREQUENCY_0,            0x00);		// frequency set to 446Mhz
			}
		void Driver_AnoRadRarioModule::RFM22B_init32kbps(void)//1kbps
			{
			RFM22B_RegisterWrite(RFM22B_REGISTER_1C_IF_FILTER_BANDWIDTH,                    0xAD);
			RFM22B_RegisterWrite(RFM22B_REGISTER_1D_AFC_LOOP_GEARSHIFT_OVERRIDE,            0x40);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_20_CLOCK_RECOVERY_OVERSAMPLING_RATIO,      0x5E);;		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_21_CLOCK_RECOVERY_OFFSET_2,                0x01);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_22_CLOCK_RECOVERY_OFFSET_1,                0x5D);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_23_CLOCK_RECOVERY_OFFSET_0,                0x86);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_24_CLOCK_RECOVERY_TIMING_LOOP_GAIN_1,      0x01);		// clock recovery timing
			RFM22B_RegisterWrite(RFM22B_REGISTER_25_CLOCK_RECOVERY_TIMING_LOOP_GAIN_0,      0xC0);		// clock recovery timing
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_2A_AFC_LIMITER,                            0x3C);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2C_OOK_COUNTER_VALUE_1,                    0x28);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2D_OOK_COUNTER_VALUE_2,                    0x27);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2E_SLICER_PEAK_HOLD,                       0x29);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_30_DATA_ACCESS_CONTROL,                    0xA8);

			RFM22B_RegisterWrite(RFM22B_REGISTER_32_HEADER_CONTROL_1,                       0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_33_HEADER_CONTROL_2,						(0<<7 | 0x0e));

			RFM22B_RegisterWrite(RFM22B_REGISTER_34_PREAMBLE_LENGTH,                        this->PREAMBLE_LENGTH);
			RFM22B_RegisterWrite(RFM22B_REGISTER_35_PREAMBLE_DETECTION_CONTROL,             0x32);

			RFM22B_RegisterWrite(RFM22B_REGISTER_36_SYNC_WORD_3,                            this->SYNC_WORD_3);		// synchronize word
			RFM22B_RegisterWrite(RFM22B_REGISTER_37_SYNC_WORD_2,                            this->SYNC_WORD_2);
			RFM22B_RegisterWrite(RFM22B_REGISTER_38_SYNC_WORD_1,                            this->SYNC_WORD_1);
			RFM22B_RegisterWrite(RFM22B_REGISTER_39_SYNC_WORD_0,                            this->SYNC_WORD_0);

			RFM22B_RegisterWrite(RFM22B_REGISTER_3A_TRANSMIT_HEADER_3,                      this->TX_HEADER_3);		// set tx header 3
			RFM22B_RegisterWrite(RFM22B_REGISTER_3B_TRANSMIT_HEADER_2,                      this->TX_HEADER_2);		// set tx header 2
			RFM22B_RegisterWrite(RFM22B_REGISTER_3C_TRANSMIT_HEADER_1,                      this->TX_HEADER_1);		// set tx header 1
			RFM22B_RegisterWrite(RFM22B_REGISTER_3D_TRANSMIT_HEADER_0,                      this->TX_HEADER_0);		// set tx header 0
			//RFM22B_RegisterWrite(0x3E, 17);		// set packet length to 17 bytes (max size: 255 bytes)
			//	RFM22B_setTransmitPacketSize(PKTSIZE);	// set packet length to PKTSIZE bytes (max size: 255 bytes)
			RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 (this->packetSize));//+1 - переменная длина пакета
			//    RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 PKTSIZE+1);//+1 - переменная длина пакета
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_3F_CHECK_HEADER_3,                         0x00);		// set rx header
			RFM22B_RegisterWrite(RFM22B_REGISTER_40_CHECK_HEADER_2,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_41_CHECK_HEADER_1,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_42_CHECK_HEADER_0,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_43_HEADER_ENABLE_3,                        0xFF);		// check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_44_HEADER_ENABLE_2,                        0xFF);		// Check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_45_HEADER_ENABLE_1,                        0xFF);		// check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_46_HEADER_ENABLE_0,                        0xFF);		// Check all bits


			//TX DATA RATE
			RFM22B_RegisterWrite(RFM22B_REGISTER_6E_TX_DATA_RATE_1,                         0x08);;		// TX data rate 1
			RFM22B_RegisterWrite(RFM22B_REGISTER_6F_TX_DATA_RATE_0,                         0x31);		// TX data rate 0
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_6D_TX_POWER,                               (RFM22B_LNA_SW | this->txPower));		// Tx power to max
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_70_MODULATION_MODE_CONTROL_1,              0x0c);
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x22);//FSK
			RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x23);//GFSK
			RFM22B_RegisterWrite(RFM22B_REGISTER_72_FREQUENCY_DEVIATION,                    0x50);		// Frequency deviation setting to 50K=80*625

			//	RFM22B_RegisterWrite(RFM22B_REGISTER_73_FREQUENCY_OFFSET_1,                     0x00);		// No frequency offset
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_74_FREQUENCY_OFFSET_2,                     0x00);		// No frequency offset

			RFM22B_RegisterWrite(RFM22B_REGISTER_75_FREQUENCY_BAND_SELECT,                  0x54);		// frequency set to 446MHz
			RFM22B_RegisterWrite(RFM22B_REGISTER_76_NOMINAL_CARRIER_FREQUENCY_1,            0x96);		// frequency set to 446MHz
			RFM22B_RegisterWrite(RFM22B_REGISTER_77_NOMINAL_CARRIER_FREQUENCY_0,            0x00);		// frequency set to 446Mhz
			}
		void Driver_AnoRadRarioModule::RFM22B_init64kbps(void)//1kbps
			{
			RFM22B_RegisterWrite(RFM22B_REGISTER_1C_IF_FILTER_BANDWIDTH,                    0x95);
			RFM22B_RegisterWrite(RFM22B_REGISTER_1D_AFC_LOOP_GEARSHIFT_OVERRIDE,            0x40);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_20_CLOCK_RECOVERY_OVERSAMPLING_RATIO,      0x5e);//0x5e);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_21_CLOCK_RECOVERY_OFFSET_2,                0x01);//0x01);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_22_CLOCK_RECOVERY_OFFSET_1,                0x5d);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_23_CLOCK_RECOVERY_OFFSET_0,                0x86);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_24_CLOCK_RECOVERY_TIMING_LOOP_GAIN_1,      0x03);		// clock recovery timing
			RFM22B_RegisterWrite(RFM22B_REGISTER_25_CLOCK_RECOVERY_TIMING_LOOP_GAIN_0,      0x7e);		// clock recovery timing
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_2A_AFC_LIMITER,                            0x3c);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2C_OOK_COUNTER_VALUE_1,                    0x28);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2D_OOK_COUNTER_VALUE_2,                    0x13);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2E_SLICER_PEAK_HOLD,                       0x29);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_30_DATA_ACCESS_CONTROL,                    0xa8);

			RFM22B_RegisterWrite(RFM22B_REGISTER_32_HEADER_CONTROL_1,                       0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_33_HEADER_CONTROL_2,						(0<<7 | 0x0e));

			RFM22B_RegisterWrite(RFM22B_REGISTER_34_PREAMBLE_LENGTH,                        this->PREAMBLE_LENGTH);
			RFM22B_RegisterWrite(RFM22B_REGISTER_35_PREAMBLE_DETECTION_CONTROL,             0x32);

			RFM22B_RegisterWrite(RFM22B_REGISTER_36_SYNC_WORD_3,                            this->SYNC_WORD_3);		// synchronize word
			RFM22B_RegisterWrite(RFM22B_REGISTER_37_SYNC_WORD_2,                            this->SYNC_WORD_2);
			RFM22B_RegisterWrite(RFM22B_REGISTER_38_SYNC_WORD_1,                            this->SYNC_WORD_1);
			RFM22B_RegisterWrite(RFM22B_REGISTER_39_SYNC_WORD_0,                            this->SYNC_WORD_0);

			RFM22B_RegisterWrite(RFM22B_REGISTER_3A_TRANSMIT_HEADER_3,                      this->TX_HEADER_3);		// set tx header 3
			RFM22B_RegisterWrite(RFM22B_REGISTER_3B_TRANSMIT_HEADER_2,                      this->TX_HEADER_2);		// set tx header 2
			RFM22B_RegisterWrite(RFM22B_REGISTER_3C_TRANSMIT_HEADER_1,                      this->TX_HEADER_1);		// set tx header 1
			RFM22B_RegisterWrite(RFM22B_REGISTER_3D_TRANSMIT_HEADER_0,                      this->TX_HEADER_0);		// set tx header 0
			//RFM22B_RegisterWrite(0x3E, 17);		// set packet length to 17 bytes (max size: 255 bytes)
			//	RFM22B_setTransmitPacketSize(PKTSIZE);	// set packet length to PKTSIZE bytes (max size: 255 bytes)
			RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 (this->packetSize));//+1 - переменная длина пакета
			//    RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 PKTSIZE+1);//+1 - переменная длина пакета
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_3F_CHECK_HEADER_3,                         0x00);		// set rx header
			RFM22B_RegisterWrite(RFM22B_REGISTER_40_CHECK_HEADER_2,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_41_CHECK_HEADER_1,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_42_CHECK_HEADER_0,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_43_HEADER_ENABLE_3,                        0xFF);		// check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_44_HEADER_ENABLE_2,                        0xFF);		// Check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_45_HEADER_ENABLE_1,                        0xFF);		// check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_46_HEADER_ENABLE_0,                        0xFF);		// Check all bits


			//TX DATA RATE
			RFM22B_RegisterWrite(RFM22B_REGISTER_6E_TX_DATA_RATE_1,                         0x10);;		// TX data rate 1
			RFM22B_RegisterWrite(RFM22B_REGISTER_6F_TX_DATA_RATE_0,                         0x62);		// TX data rate 0
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_6D_TX_POWER,                               (RFM22B_LNA_SW | this->txPower));		// Tx power to max
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_70_MODULATION_MODE_CONTROL_1,              0x0c);
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x22);//FSK
			RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x23);//GFSK
			RFM22B_RegisterWrite(RFM22B_REGISTER_72_FREQUENCY_DEVIATION,                    0x50);		// Frequency deviation setting to 50K=80*625

			//	RFM22B_RegisterWrite(RFM22B_REGISTER_73_FREQUENCY_OFFSET_1,                     0x00);		// No frequency offset
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_74_FREQUENCY_OFFSET_2,                     0x00);		// No frequency offset

			RFM22B_RegisterWrite(RFM22B_REGISTER_75_FREQUENCY_BAND_SELECT,                  0x54);		// frequency set to 446MHz
			RFM22B_RegisterWrite(RFM22B_REGISTER_76_NOMINAL_CARRIER_FREQUENCY_1,            0x96);		// frequency set to 446MHz
			RFM22B_RegisterWrite(RFM22B_REGISTER_77_NOMINAL_CARRIER_FREQUENCY_0,            0x00);		// frequency set to 446Mhz
			}
		/*void Driver_AnoRadRarioModule::RFM22B_init128kbps(void)
			{
			RFM22B_RegisterWrite(RFM22B_REGISTER_1C_IF_FILTER_BANDWIDTH,                    0x82);//<-128kbps 0x95);//<-64kbps
			RFM22B_RegisterWrite(RFM22B_REGISTER_1D_AFC_LOOP_GEARSHIFT_OVERRIDE,            0x40);//<-128kbps 0x40);//<-64kbps
				
			RFM22B_RegisterWrite(RFM22B_REGISTER_20_CLOCK_RECOVERY_OVERSAMPLING_RATIO,      0x5e);//0x5e);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_21_CLOCK_RECOVERY_OFFSET_2,                0x01);//0x01);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_22_CLOCK_RECOVERY_OFFSET_1,                0x5d);//0x5d);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_23_CLOCK_RECOVERY_OFFSET_0,                0x86);//0x86);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_24_CLOCK_RECOVERY_TIMING_LOOP_GAIN_1,      0x06);//0x03);		// clock recovery timing
			RFM22B_RegisterWrite(RFM22B_REGISTER_25_CLOCK_RECOVERY_TIMING_LOOP_GAIN_0,      0xfb);//0x7e);		// clock recovery timing
				
			RFM22B_RegisterWrite(RFM22B_REGISTER_2A_AFC_LIMITER,                            0x50);//3c);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2C_OOK_COUNTER_VALUE_1,                    0x28);//28);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2D_OOK_COUNTER_VALUE_2,                    0x09);//13);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2E_SLICER_PEAK_HOLD,                       0x28);//29);
				
			RFM22B_RegisterWrite(RFM22B_REGISTER_30_DATA_ACCESS_CONTROL,                    0xa8);

			RFM22B_RegisterWrite(RFM22B_REGISTER_32_HEADER_CONTROL_1,                       0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_33_HEADER_CONTROL_2,						(0<<7 | 0x0e));

			RFM22B_RegisterWrite(RFM22B_REGISTER_34_PREAMBLE_LENGTH,                        this->PREAMBLE_LENGTH);
			RFM22B_RegisterWrite(RFM22B_REGISTER_35_PREAMBLE_DETECTION_CONTROL,             0x32);

			RFM22B_RegisterWrite(RFM22B_REGISTER_36_SYNC_WORD_3,                            this->SYNC_WORD_3);		// synchronize word
			RFM22B_RegisterWrite(RFM22B_REGISTER_37_SYNC_WORD_2,                            this->SYNC_WORD_2);
			RFM22B_RegisterWrite(RFM22B_REGISTER_38_SYNC_WORD_1,                            this->SYNC_WORD_1);
			RFM22B_RegisterWrite(RFM22B_REGISTER_39_SYNC_WORD_0,                            this->SYNC_WORD_0);

			RFM22B_RegisterWrite(RFM22B_REGISTER_3A_TRANSMIT_HEADER_3,                      this->TX_HEADER_3);		// set tx header 3
			RFM22B_RegisterWrite(RFM22B_REGISTER_3B_TRANSMIT_HEADER_2,                      this->TX_HEADER_2);		// set tx header 2
			RFM22B_RegisterWrite(RFM22B_REGISTER_3C_TRANSMIT_HEADER_1,                      this->TX_HEADER_1);		// set tx header 1
			RFM22B_RegisterWrite(RFM22B_REGISTER_3D_TRANSMIT_HEADER_0,                      this->TX_HEADER_0);		// set tx header 0
			//RFM22B_RegisterWrite(0x3E, 17);		// set packet length to 17 bytes (max size: 255 bytes)
			//	RFM22B_setTransmitPacketSize(PKTSIZE);	// set packet length to PKTSIZE bytes (max size: 255 bytes)
			RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 (this->packetSize));//+1 - переменная длина пакета
			//    RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 PKTSIZE+1);//+1 - переменная длина пакета
				
			RFM22B_RegisterWrite(RFM22B_REGISTER_3F_CHECK_HEADER_3,                         0x00);		// set rx header
			RFM22B_RegisterWrite(RFM22B_REGISTER_40_CHECK_HEADER_2,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_41_CHECK_HEADER_1,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_42_CHECK_HEADER_0,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_43_HEADER_ENABLE_3,                        0xFF);		// check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_44_HEADER_ENABLE_2,                        0xFF);		// Check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_45_HEADER_ENABLE_1,                        0xFF);		// check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_46_HEADER_ENABLE_0,                        0xFF);		// Check all bits


			//TX DATA RATE
			RFM22B_RegisterWrite(RFM22B_REGISTER_6E_TX_DATA_RATE_1,                         0x20);//<-128kbps 10);		// TX data rate 1
			RFM22B_RegisterWrite(RFM22B_REGISTER_6F_TX_DATA_RATE_0,                         0xc5);//<-128kbps 62);		// TX data rate 0
				
			RFM22B_RegisterWrite(RFM22B_REGISTER_6D_TX_POWER,                               (RFM22B_LNA_SW | this->txPower));		// Tx power to max
				
			RFM22B_RegisterWrite(RFM22B_REGISTER_70_MODULATION_MODE_CONTROL_1,              0x0c);
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x22);//FSK
			RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x23);//GFSK
			RFM22B_RegisterWrite(RFM22B_REGISTER_72_FREQUENCY_DEVIATION,                    0x50);		// Frequency deviation setting to 50K=80*625

			//	RFM22B_RegisterWrite(RFM22B_REGISTER_73_FREQUENCY_OFFSET_1,                     0x00);		// No frequency offset
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_74_FREQUENCY_OFFSET_2,                     0x00);		// No frequency offset

			RFM22B_RegisterWrite(RFM22B_REGISTER_75_FREQUENCY_BAND_SELECT,                  0x54);		// frequency set to 446MHz
			RFM22B_RegisterWrite(RFM22B_REGISTER_76_NOMINAL_CARRIER_FREQUENCY_1,            0x96);		// frequency set to 446MHz
			RFM22B_RegisterWrite(RFM22B_REGISTER_77_NOMINAL_CARRIER_FREQUENCY_0,            0x00);		// frequency set to 446Mhz
			}*/
		void Driver_AnoRadRarioModule::RFM22B_init128kbps50khzNoHeader(void)
		{
			RFM22B_RegisterWrite(RFM22B_REGISTER_1C_IF_FILTER_BANDWIDTH,                    0x82);
			RFM22B_RegisterWrite(RFM22B_REGISTER_1D_AFC_LOOP_GEARSHIFT_OVERRIDE,            0x44);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_1E_AFC_TIMING_CONTROL,						0x0a);
			RFM22B_RegisterWrite(RFM22B_REGISTER_1F_CLOCK_RECOVERY_GEARSHIFT_OVERRIDE,		0x03);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_20_CLOCK_RECOVERY_OVERSAMPLING_RATIO,      0x5e);//0x5e);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_21_CLOCK_RECOVERY_OFFSET_2,                0x01);//0x01);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_22_CLOCK_RECOVERY_OFFSET_1,                0x5d);//0x5d);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_23_CLOCK_RECOVERY_OFFSET_0,                0x86);//0x86);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_24_CLOCK_RECOVERY_TIMING_LOOP_GAIN_1,      0x06);//0x03);		// clock recovery timing
			RFM22B_RegisterWrite(RFM22B_REGISTER_25_CLOCK_RECOVERY_TIMING_LOOP_GAIN_0,      0xfb);//0x7e);		// clock recovery timing
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_2A_AFC_LIMITER,                            0x50);//3c);
//			RFM22B_RegisterWrite(RFM22B_REGISTER_2C_OOK_COUNTER_VALUE_1,                    0x28);//28);//This setting is relevant only in OOK
//			RFM22B_RegisterWrite(RFM22B_REGISTER_2D_OOK_COUNTER_VALUE_2,                    0x09);//13);//This setting is relevant only in OOK
//			RFM22B_RegisterWrite(RFM22B_REGISTER_2E_SLICER_PEAK_HOLD,                       0x28);//29);//This setting is relevant only in OOK
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_30_DATA_ACCESS_CONTROL,                    0x21);

//			RFM22B_RegisterWrite(RFM22B_REGISTER_32_HEADER_CONTROL_1,                       0x8c);
			RFM22B_RegisterWrite(RFM22B_REGISTER_33_HEADER_CONTROL_2,						(0<<7 | 0x0E));

			RFM22B_RegisterWrite(RFM22B_REGISTER_34_PREAMBLE_LENGTH,                        this->PREAMBLE_LENGTH);
			RFM22B_RegisterWrite(RFM22B_REGISTER_35_PREAMBLE_DETECTION_CONTROL,             0x2a);

			RFM22B_RegisterWrite(RFM22B_REGISTER_36_SYNC_WORD_3,                            this->SYNC_WORD_3);		// synchronize word
			RFM22B_RegisterWrite(RFM22B_REGISTER_37_SYNC_WORD_2,                            this->SYNC_WORD_2);
			RFM22B_RegisterWrite(RFM22B_REGISTER_38_SYNC_WORD_1,                            this->SYNC_WORD_1);
			RFM22B_RegisterWrite(RFM22B_REGISTER_39_SYNC_WORD_0,                            this->SYNC_WORD_0);

//			RFM22B_RegisterWrite(RFM22B_REGISTER_3A_TRANSMIT_HEADER_3,                      this->TX_HEADER_3);		// set tx header 3
//			RFM22B_RegisterWrite(RFM22B_REGISTER_3B_TRANSMIT_HEADER_2,                      this->TX_HEADER_2);		// set tx header 2
//			RFM22B_RegisterWrite(RFM22B_REGISTER_3C_TRANSMIT_HEADER_1,                      this->TX_HEADER_1);		// set tx header 1
//			RFM22B_RegisterWrite(RFM22B_REGISTER_3D_TRANSMIT_HEADER_0,                      this->TX_HEADER_0);		// set tx header 0
			//RFM22B_RegisterWrite(0x3E, 17);		// set packet length to 17 bytes (max size: 255 bytes)
			//	RFM22B_setTransmitPacketSize(PKTSIZE);	// set packet length to PKTSIZE bytes (max size: 255 bytes)
//			RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 (this->packetSize));//+1 - переменная длина пакета
			//    RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 PKTSIZE+1);//+1 - переменная длина пакета
			
//			RFM22B_RegisterWrite(RFM22B_REGISTER_3F_CHECK_HEADER_3,                         0x00);		// set rx header
//			RFM22B_RegisterWrite(RFM22B_REGISTER_40_CHECK_HEADER_2,                         0x00);
//			RFM22B_RegisterWrite(RFM22B_REGISTER_41_CHECK_HEADER_1,                         0x00);
//			RFM22B_RegisterWrite(RFM22B_REGISTER_42_CHECK_HEADER_0,                         0x00);
//			RFM22B_RegisterWrite(RFM22B_REGISTER_43_HEADER_ENABLE_3,                        0xFF);		// check all bits
//			RFM22B_RegisterWrite(RFM22B_REGISTER_44_HEADER_ENABLE_2,                        0xFF);		// Check all bits
//			RFM22B_RegisterWrite(RFM22B_REGISTER_45_HEADER_ENABLE_1,                        0xFF);		// check all bits
//			RFM22B_RegisterWrite(RFM22B_REGISTER_46_HEADER_ENABLE_0,                        0xFF);		// Check all bits


			//TX DATA RATE
			RFM22B_RegisterWrite(0x58, 0xC0);
			RFM22B_RegisterWrite(0x69, 0x60);
			RFM22B_RegisterWrite(RFM22B_REGISTER_6E_TX_DATA_RATE_1,                         0x20);//<-128kbps 10);		// TX data rate 1
			RFM22B_RegisterWrite(RFM22B_REGISTER_6F_TX_DATA_RATE_0,                         0xc5);//<-128kbps 62);		// TX data rate 0
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_6D_TX_POWER,                               (RFM22B_LNA_SW | this->txPower));		// Tx power to max
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_70_MODULATION_MODE_CONTROL_1,              0x04);
//			RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x22);//FSK
			RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x23);//GFSK
			RFM22B_RegisterWrite(RFM22B_REGISTER_72_FREQUENCY_DEVIATION,                    0x50);		// Frequency deviation setting to 50K=80*625

			//	RFM22B_RegisterWrite(RFM22B_REGISTER_73_FREQUENCY_OFFSET_1,                     0x00);		// No frequency offset
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_74_FREQUENCY_OFFSET_2,                     0x00);		// No frequency offset

			RFM22B_RegisterWrite(RFM22B_REGISTER_75_FREQUENCY_BAND_SELECT,                  0x54);		// frequency set to 446MHz
			RFM22B_RegisterWrite(RFM22B_REGISTER_76_NOMINAL_CARRIER_FREQUENCY_1,            0x96);		// frequency set to 446MHz
			RFM22B_RegisterWrite(RFM22B_REGISTER_77_NOMINAL_CARRIER_FREQUENCY_0,            0x00);		// frequency set to 446Mhz
			}
		void Driver_AnoRadRarioModule::RFM22B_init128kbps100khz(void)
			{
			RFM22B_RegisterWrite(RFM22B_REGISTER_1C_IF_FILTER_BANDWIDTH,                    0x88);
			RFM22B_RegisterWrite(RFM22B_REGISTER_1D_AFC_LOOP_GEARSHIFT_OVERRIDE,            0x44);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_1E_AFC_TIMING_CONTROL,						0x0a);
			RFM22B_RegisterWrite(RFM22B_REGISTER_1F_CLOCK_RECOVERY_GEARSHIFT_OVERRIDE,		0x03);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_20_CLOCK_RECOVERY_OVERSAMPLING_RATIO,      0x5e);//0x5e);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_21_CLOCK_RECOVERY_OFFSET_2,                0x01);//0x01);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_22_CLOCK_RECOVERY_OFFSET_1,                0x5d);//0x5d);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_23_CLOCK_RECOVERY_OFFSET_0,                0x86);//0x86);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_24_CLOCK_RECOVERY_TIMING_LOOP_GAIN_1,      0x03);//0x03);		// clock recovery timing
			RFM22B_RegisterWrite(RFM22B_REGISTER_25_CLOCK_RECOVERY_TIMING_LOOP_GAIN_0,      0x7e);//0x7e);		// clock recovery timing
				
			RFM22B_RegisterWrite(RFM22B_REGISTER_2A_AFC_LIMITER,                            0x50);//3c);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2C_OOK_COUNTER_VALUE_1,                    0x28);//28);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2D_OOK_COUNTER_VALUE_2,                    0x09);//13);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2E_SLICER_PEAK_HOLD,                       0x28);//29);
				
			RFM22B_RegisterWrite(RFM22B_REGISTER_30_DATA_ACCESS_CONTROL,                    0xa8);

			RFM22B_RegisterWrite(RFM22B_REGISTER_32_HEADER_CONTROL_1,                       0x8c);
			RFM22B_RegisterWrite(RFM22B_REGISTER_33_HEADER_CONTROL_2,						(0<<7 | 0x0e));

			RFM22B_RegisterWrite(RFM22B_REGISTER_34_PREAMBLE_LENGTH,                        this->PREAMBLE_LENGTH);
			RFM22B_RegisterWrite(RFM22B_REGISTER_35_PREAMBLE_DETECTION_CONTROL,             0x2a);

			RFM22B_RegisterWrite(RFM22B_REGISTER_36_SYNC_WORD_3,                            this->SYNC_WORD_3);		// synchronize word
			RFM22B_RegisterWrite(RFM22B_REGISTER_37_SYNC_WORD_2,                            this->SYNC_WORD_2);
			RFM22B_RegisterWrite(RFM22B_REGISTER_38_SYNC_WORD_1,                            this->SYNC_WORD_1);
			RFM22B_RegisterWrite(RFM22B_REGISTER_39_SYNC_WORD_0,                            this->SYNC_WORD_0);

			RFM22B_RegisterWrite(RFM22B_REGISTER_3A_TRANSMIT_HEADER_3,                      this->TX_HEADER_3);		// set tx header 3
			RFM22B_RegisterWrite(RFM22B_REGISTER_3B_TRANSMIT_HEADER_2,                      this->TX_HEADER_2);		// set tx header 2
			RFM22B_RegisterWrite(RFM22B_REGISTER_3C_TRANSMIT_HEADER_1,                      this->TX_HEADER_1);		// set tx header 1
			RFM22B_RegisterWrite(RFM22B_REGISTER_3D_TRANSMIT_HEADER_0,                      this->TX_HEADER_0);		// set tx header 0
			//RFM22B_RegisterWrite(0x3E, 17);		// set packet length to 17 bytes (max size: 255 bytes)
			//	RFM22B_setTransmitPacketSize(PKTSIZE);	// set packet length to PKTSIZE bytes (max size: 255 bytes)
			RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 (this->packetSize));//+1 - переменная длина пакета
			//    RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 PKTSIZE+1);//+1 - переменная длина пакета
				
			RFM22B_RegisterWrite(RFM22B_REGISTER_3F_CHECK_HEADER_3,                         0x00);		// set rx header
			RFM22B_RegisterWrite(RFM22B_REGISTER_40_CHECK_HEADER_2,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_41_CHECK_HEADER_1,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_42_CHECK_HEADER_0,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_43_HEADER_ENABLE_3,                        0xFF);		// check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_44_HEADER_ENABLE_2,                        0xFF);		// Check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_45_HEADER_ENABLE_1,                        0xFF);		// check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_46_HEADER_ENABLE_0,                        0xFF);		// Check all bits


			//TX DATA RATE
			RFM22B_RegisterWrite(0x58, 0xC0);
			RFM22B_RegisterWrite(0x69, 0x60);
			RFM22B_RegisterWrite(RFM22B_REGISTER_6E_TX_DATA_RATE_1,                         0x20);//<-128kbps 10);		// TX data rate 1
			RFM22B_RegisterWrite(RFM22B_REGISTER_6F_TX_DATA_RATE_0,                         0xc5);//<-128kbps 62);		// TX data rate 0
				
			RFM22B_RegisterWrite(RFM22B_REGISTER_6D_TX_POWER,                               (RFM22B_LNA_SW | this->txPower));		// Tx power to max
				
			RFM22B_RegisterWrite(RFM22B_REGISTER_70_MODULATION_MODE_CONTROL_1,              0x0c);
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x22);//FSK
			RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x23);//GFSK
			RFM22B_RegisterWrite(RFM22B_REGISTER_72_FREQUENCY_DEVIATION,                    0xa0);		// Frequency deviation setting to 50K=80*625

			//	RFM22B_RegisterWrite(RFM22B_REGISTER_73_FREQUENCY_OFFSET_1,                     0x00);		// No frequency offset
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_74_FREQUENCY_OFFSET_2,                     0x00);		// No frequency offset

			RFM22B_RegisterWrite(RFM22B_REGISTER_75_FREQUENCY_BAND_SELECT,                  0x54);		// frequency set to 446MHz
			RFM22B_RegisterWrite(RFM22B_REGISTER_76_NOMINAL_CARRIER_FREQUENCY_1,            0x96);		// frequency set to 446MHz
			RFM22B_RegisterWrite(RFM22B_REGISTER_77_NOMINAL_CARRIER_FREQUENCY_0,            0x00);		// frequency set to 446Mhz
			}
		void Driver_AnoRadRarioModule::RFM22B_init128kbps50khz(void)
			{
			RFM22B_RegisterWrite(RFM22B_REGISTER_1C_IF_FILTER_BANDWIDTH,                    0x82);
			RFM22B_RegisterWrite(RFM22B_REGISTER_1D_AFC_LOOP_GEARSHIFT_OVERRIDE,            0x44);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_1E_AFC_TIMING_CONTROL,						0x0a);
			RFM22B_RegisterWrite(RFM22B_REGISTER_1F_CLOCK_RECOVERY_GEARSHIFT_OVERRIDE,		0x03);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_20_CLOCK_RECOVERY_OVERSAMPLING_RATIO,      0x5e);//0x5e);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_21_CLOCK_RECOVERY_OFFSET_2,                0x01);//0x01);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_22_CLOCK_RECOVERY_OFFSET_1,                0x5d);//0x5d);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_23_CLOCK_RECOVERY_OFFSET_0,                0x86);//0x86);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_24_CLOCK_RECOVERY_TIMING_LOOP_GAIN_1,      0x06);//0x03);		// clock recovery timing
			RFM22B_RegisterWrite(RFM22B_REGISTER_25_CLOCK_RECOVERY_TIMING_LOOP_GAIN_0,      0xfb);//0x7e);		// clock recovery timing
				
			RFM22B_RegisterWrite(RFM22B_REGISTER_2A_AFC_LIMITER,                            0x50);//3c);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2C_OOK_COUNTER_VALUE_1,                    0x28);//28);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2D_OOK_COUNTER_VALUE_2,                    0x09);//13);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2E_SLICER_PEAK_HOLD,                       0x28);//29);
				
			RFM22B_RegisterWrite(RFM22B_REGISTER_30_DATA_ACCESS_CONTROL,                    0xa8);

			RFM22B_RegisterWrite(RFM22B_REGISTER_32_HEADER_CONTROL_1,                       0x8c);
			RFM22B_RegisterWrite(RFM22B_REGISTER_33_HEADER_CONTROL_2,						(0<<7 | 0x0e));

			RFM22B_RegisterWrite(RFM22B_REGISTER_34_PREAMBLE_LENGTH,                        this->PREAMBLE_LENGTH);
			RFM22B_RegisterWrite(RFM22B_REGISTER_35_PREAMBLE_DETECTION_CONTROL,             0x2a);

			RFM22B_RegisterWrite(RFM22B_REGISTER_36_SYNC_WORD_3,                            this->SYNC_WORD_3);		// synchronize word
			RFM22B_RegisterWrite(RFM22B_REGISTER_37_SYNC_WORD_2,                            this->SYNC_WORD_2);
			RFM22B_RegisterWrite(RFM22B_REGISTER_38_SYNC_WORD_1,                            this->SYNC_WORD_1);
			RFM22B_RegisterWrite(RFM22B_REGISTER_39_SYNC_WORD_0,                            this->SYNC_WORD_0);

			RFM22B_RegisterWrite(RFM22B_REGISTER_3A_TRANSMIT_HEADER_3,                      this->TX_HEADER_3);		// set tx header 3
			RFM22B_RegisterWrite(RFM22B_REGISTER_3B_TRANSMIT_HEADER_2,                      this->TX_HEADER_2);		// set tx header 2
			RFM22B_RegisterWrite(RFM22B_REGISTER_3C_TRANSMIT_HEADER_1,                      this->TX_HEADER_1);		// set tx header 1
			RFM22B_RegisterWrite(RFM22B_REGISTER_3D_TRANSMIT_HEADER_0,                      this->TX_HEADER_0);		// set tx header 0
			//RFM22B_RegisterWrite(0x3E, 17);		// set packet length to 17 bytes (max size: 255 bytes)
			//	RFM22B_setTransmitPacketSize(PKTSIZE);	// set packet length to PKTSIZE bytes (max size: 255 bytes)
			RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 (this->packetSize));//+1 - переменная длина пакета
			//    RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 PKTSIZE+1);//+1 - переменная длина пакета
				
			RFM22B_RegisterWrite(RFM22B_REGISTER_3F_CHECK_HEADER_3,                         0x00);		// set rx header
			RFM22B_RegisterWrite(RFM22B_REGISTER_40_CHECK_HEADER_2,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_41_CHECK_HEADER_1,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_42_CHECK_HEADER_0,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_43_HEADER_ENABLE_3,                        0xFF);		// check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_44_HEADER_ENABLE_2,                        0xFF);		// Check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_45_HEADER_ENABLE_1,                        0xFF);		// check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_46_HEADER_ENABLE_0,                        0xFF);		// Check all bits


			//TX DATA RATE
			RFM22B_RegisterWrite(0x58, 0xC0);
			RFM22B_RegisterWrite(0x69, 0x60);
			RFM22B_RegisterWrite(RFM22B_REGISTER_6E_TX_DATA_RATE_1,                         0x20);//<-128kbps 10);		// TX data rate 1
			RFM22B_RegisterWrite(RFM22B_REGISTER_6F_TX_DATA_RATE_0,                         0xc5);//<-128kbps 62);		// TX data rate 0
				
			RFM22B_RegisterWrite(RFM22B_REGISTER_6D_TX_POWER,                               (RFM22B_LNA_SW | this->txPower));		// Tx power to max
				
			RFM22B_RegisterWrite(RFM22B_REGISTER_70_MODULATION_MODE_CONTROL_1,              0x0c);
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x22);//FSK
			RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x23);//GFSK
			RFM22B_RegisterWrite(RFM22B_REGISTER_72_FREQUENCY_DEVIATION,                    0x50);		// Frequency deviation setting to 50K=80*625

			//	RFM22B_RegisterWrite(RFM22B_REGISTER_73_FREQUENCY_OFFSET_1,                     0x00);		// No frequency offset
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_74_FREQUENCY_OFFSET_2,                     0x00);		// No frequency offset

			RFM22B_RegisterWrite(RFM22B_REGISTER_75_FREQUENCY_BAND_SELECT,                  0x54);		// frequency set to 446MHz
			RFM22B_RegisterWrite(RFM22B_REGISTER_76_NOMINAL_CARRIER_FREQUENCY_1,            0x96);		// frequency set to 446MHz
			RFM22B_RegisterWrite(RFM22B_REGISTER_77_NOMINAL_CARRIER_FREQUENCY_0,            0x00);		// frequency set to 446Mhz
			}
		void Driver_AnoRadRarioModule::RFM22B_init128kbps30khz(void)
			{
			RFM22B_RegisterWrite(RFM22B_REGISTER_1C_IF_FILTER_BANDWIDTH,                    0x96);
			RFM22B_RegisterWrite(RFM22B_REGISTER_1D_AFC_LOOP_GEARSHIFT_OVERRIDE,            0x44);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_1E_AFC_TIMING_CONTROL,						0x0A);
			RFM22B_RegisterWrite(RFM22B_REGISTER_1F_CLOCK_RECOVERY_GEARSHIFT_OVERRIDE,		0x03);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_20_CLOCK_RECOVERY_OVERSAMPLING_RATIO,      0x2F);//0x5e);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_21_CLOCK_RECOVERY_OFFSET_2,                0x02);//0x01);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_22_CLOCK_RECOVERY_OFFSET_1,                0xBB);//0x5d);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_23_CLOCK_RECOVERY_OFFSET_0,                0x0D);//0x86);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_24_CLOCK_RECOVERY_TIMING_LOOP_GAIN_1,      0x07);//0x03);		// clock recovery timing
			RFM22B_RegisterWrite(RFM22B_REGISTER_25_CLOCK_RECOVERY_TIMING_LOOP_GAIN_0,      0xFF);//0x7e);		// clock recovery timing
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_2A_AFC_LIMITER,                            0x48);//3c);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2C_OOK_COUNTER_VALUE_1,                    0x28);//28);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2D_OOK_COUNTER_VALUE_2,                    0x09);//13);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2E_SLICER_PEAK_HOLD,                       0x28);//29);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_30_DATA_ACCESS_CONTROL,                    0xa8);

			RFM22B_RegisterWrite(RFM22B_REGISTER_32_HEADER_CONTROL_1,                       0x8c);
			RFM22B_RegisterWrite(RFM22B_REGISTER_33_HEADER_CONTROL_2,						(0<<7 | 0x0e));

			RFM22B_RegisterWrite(RFM22B_REGISTER_34_PREAMBLE_LENGTH,                        this->PREAMBLE_LENGTH);
			RFM22B_RegisterWrite(RFM22B_REGISTER_35_PREAMBLE_DETECTION_CONTROL,             0x2a);

			RFM22B_RegisterWrite(RFM22B_REGISTER_36_SYNC_WORD_3,                            this->SYNC_WORD_3);		// synchronize word
			RFM22B_RegisterWrite(RFM22B_REGISTER_37_SYNC_WORD_2,                            this->SYNC_WORD_2);
			RFM22B_RegisterWrite(RFM22B_REGISTER_38_SYNC_WORD_1,                            this->SYNC_WORD_1);
			RFM22B_RegisterWrite(RFM22B_REGISTER_39_SYNC_WORD_0,                            this->SYNC_WORD_0);

			RFM22B_RegisterWrite(RFM22B_REGISTER_3A_TRANSMIT_HEADER_3,                      this->TX_HEADER_3);		// set tx header 3
			RFM22B_RegisterWrite(RFM22B_REGISTER_3B_TRANSMIT_HEADER_2,                      this->TX_HEADER_2);		// set tx header 2
			RFM22B_RegisterWrite(RFM22B_REGISTER_3C_TRANSMIT_HEADER_1,                      this->TX_HEADER_1);		// set tx header 1
			RFM22B_RegisterWrite(RFM22B_REGISTER_3D_TRANSMIT_HEADER_0,                      this->TX_HEADER_0);		// set tx header 0
			//RFM22B_RegisterWrite(0x3E, 17);		// set packet length to 17 bytes (max size: 255 bytes)
			//	RFM22B_setTransmitPacketSize(PKTSIZE);	// set packet length to PKTSIZE bytes (max size: 255 bytes)
			RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 (this->packetSize));//+1 - переменная длина пакета
			//    RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 PKTSIZE+1);//+1 - переменная длина пакета
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_3F_CHECK_HEADER_3,                         0x00);		// set rx header
			RFM22B_RegisterWrite(RFM22B_REGISTER_40_CHECK_HEADER_2,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_41_CHECK_HEADER_1,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_42_CHECK_HEADER_0,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_43_HEADER_ENABLE_3,                        0xFF);		// check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_44_HEADER_ENABLE_2,                        0xFF);		// Check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_45_HEADER_ENABLE_1,                        0xFF);		// check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_46_HEADER_ENABLE_0,                        0xFF);		// Check all bits


			//TX DATA RATE
			RFM22B_RegisterWrite(0x58, 0xC0);
			RFM22B_RegisterWrite(0x69, 0x60);
			RFM22B_RegisterWrite(RFM22B_REGISTER_6E_TX_DATA_RATE_1,                         0x20);//<-128kbps 10);		// TX data rate 1
			RFM22B_RegisterWrite(RFM22B_REGISTER_6F_TX_DATA_RATE_0,                         0xc5);//<-128kbps 62);		// TX data rate 0
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_6D_TX_POWER,                               (RFM22B_LNA_SW | this->txPower));		// Tx power to max
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_70_MODULATION_MODE_CONTROL_1,              0x0c);
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x22);//FSK
			RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x23);//GFSK
			RFM22B_RegisterWrite(RFM22B_REGISTER_72_FREQUENCY_DEVIATION,                    0x30);		// Frequency deviation setting to 50K=80*625

			//	RFM22B_RegisterWrite(RFM22B_REGISTER_73_FREQUENCY_OFFSET_1,                     0x00);		// No frequency offset
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_74_FREQUENCY_OFFSET_2,                     0x00);		// No frequency offset

			RFM22B_RegisterWrite(RFM22B_REGISTER_75_FREQUENCY_BAND_SELECT,                  0x54);		// frequency set to 446MHz
			RFM22B_RegisterWrite(RFM22B_REGISTER_76_NOMINAL_CARRIER_FREQUENCY_1,            0x96);		// frequency set to 446MHz
			RFM22B_RegisterWrite(RFM22B_REGISTER_77_NOMINAL_CARRIER_FREQUENCY_0,            0x00);		// frequency set to 446Mhz			}
			}
		void Driver_AnoRadRarioModule::RFM22B_init128kbps40khz(void)
			{
			RFM22B_RegisterWrite(RFM22B_REGISTER_1C_IF_FILTER_BANDWIDTH,                    0x9A);
			RFM22B_RegisterWrite(RFM22B_REGISTER_1D_AFC_LOOP_GEARSHIFT_OVERRIDE,            0x44);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_1E_AFC_TIMING_CONTROL,						0x0A);
			RFM22B_RegisterWrite(RFM22B_REGISTER_1F_CLOCK_RECOVERY_GEARSHIFT_OVERRIDE,		0x03);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_20_CLOCK_RECOVERY_OVERSAMPLING_RATIO,      0x2F);//0x5e);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_21_CLOCK_RECOVERY_OFFSET_2,                0x02);//0x01);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_22_CLOCK_RECOVERY_OFFSET_1,                0xBB);//0x5d);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_23_CLOCK_RECOVERY_OFFSET_0,                0x0D);//0x86);		// clock recovery
			RFM22B_RegisterWrite(RFM22B_REGISTER_24_CLOCK_RECOVERY_TIMING_LOOP_GAIN_1,      0x07);//0x03);		// clock recovery timing
			RFM22B_RegisterWrite(RFM22B_REGISTER_25_CLOCK_RECOVERY_TIMING_LOOP_GAIN_0,      0xFF);//0x7e);		// clock recovery timing
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_2A_AFC_LIMITER,                            0x48);//3c);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2C_OOK_COUNTER_VALUE_1,                    0x28);//28);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2D_OOK_COUNTER_VALUE_2,                    0x09);//13);
			RFM22B_RegisterWrite(RFM22B_REGISTER_2E_SLICER_PEAK_HOLD,                       0x28);//29);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_30_DATA_ACCESS_CONTROL,                    0xa8);

			RFM22B_RegisterWrite(RFM22B_REGISTER_32_HEADER_CONTROL_1,                       0x8c);
			RFM22B_RegisterWrite(RFM22B_REGISTER_33_HEADER_CONTROL_2,						(0<<7 | 0x0e));

			RFM22B_RegisterWrite(RFM22B_REGISTER_34_PREAMBLE_LENGTH,                        this->PREAMBLE_LENGTH);
			RFM22B_RegisterWrite(RFM22B_REGISTER_35_PREAMBLE_DETECTION_CONTROL,             0x2a);

			RFM22B_RegisterWrite(RFM22B_REGISTER_36_SYNC_WORD_3,                            this->SYNC_WORD_3);		// synchronize word
			RFM22B_RegisterWrite(RFM22B_REGISTER_37_SYNC_WORD_2,                            this->SYNC_WORD_2);
			RFM22B_RegisterWrite(RFM22B_REGISTER_38_SYNC_WORD_1,                            this->SYNC_WORD_1);
			RFM22B_RegisterWrite(RFM22B_REGISTER_39_SYNC_WORD_0,                            this->SYNC_WORD_0);

			RFM22B_RegisterWrite(RFM22B_REGISTER_3A_TRANSMIT_HEADER_3,                      this->TX_HEADER_3);		// set tx header 3
			RFM22B_RegisterWrite(RFM22B_REGISTER_3B_TRANSMIT_HEADER_2,                      this->TX_HEADER_2);		// set tx header 2
			RFM22B_RegisterWrite(RFM22B_REGISTER_3C_TRANSMIT_HEADER_1,                      this->TX_HEADER_1);		// set tx header 1
			RFM22B_RegisterWrite(RFM22B_REGISTER_3D_TRANSMIT_HEADER_0,                      this->TX_HEADER_0);		// set tx header 0
			//RFM22B_RegisterWrite(0x3E, 17);		// set packet length to 17 bytes (max size: 255 bytes)
			//	RFM22B_setTransmitPacketSize(PKTSIZE);	// set packet length to PKTSIZE bytes (max size: 255 bytes)
			RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 (this->packetSize));//+1 - переменная длина пакета
			//    RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 PKTSIZE+1);//+1 - переменная длина пакета
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_3F_CHECK_HEADER_3,                         0x00);		// set rx header
			RFM22B_RegisterWrite(RFM22B_REGISTER_40_CHECK_HEADER_2,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_41_CHECK_HEADER_1,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_42_CHECK_HEADER_0,                         0x00);
			RFM22B_RegisterWrite(RFM22B_REGISTER_43_HEADER_ENABLE_3,                        0xFF);		// check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_44_HEADER_ENABLE_2,                        0xFF);		// Check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_45_HEADER_ENABLE_1,                        0xFF);		// check all bits
			RFM22B_RegisterWrite(RFM22B_REGISTER_46_HEADER_ENABLE_0,                        0xFF);		// Check all bits


			//TX DATA RATE
			RFM22B_RegisterWrite(0x58, 0xC0);
			RFM22B_RegisterWrite(0x69, 0x60);
			RFM22B_RegisterWrite(RFM22B_REGISTER_6E_TX_DATA_RATE_1,                         0x20);//<-128kbps 10);		// TX data rate 1
			RFM22B_RegisterWrite(RFM22B_REGISTER_6F_TX_DATA_RATE_0,                         0xc5);//<-128kbps 62);		// TX data rate 0
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_6D_TX_POWER,                               (RFM22B_LNA_SW | this->txPower));		// Tx power to max
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_70_MODULATION_MODE_CONTROL_1,              0x0c);
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x22);//FSK
			RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x23);//GFSK
			RFM22B_RegisterWrite(RFM22B_REGISTER_72_FREQUENCY_DEVIATION,                    0x40);		// Frequency deviation setting to 50K=80*625

			//	RFM22B_RegisterWrite(RFM22B_REGISTER_73_FREQUENCY_OFFSET_1,                     0x00);		// No frequency offset
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_74_FREQUENCY_OFFSET_2,                     0x00);		// No frequency offset

			RFM22B_RegisterWrite(RFM22B_REGISTER_75_FREQUENCY_BAND_SELECT,                  0x54);		// frequency set to 446MHz
			RFM22B_RegisterWrite(RFM22B_REGISTER_76_NOMINAL_CARRIER_FREQUENCY_1,            0x96);		// frequency set to 446MHz
			RFM22B_RegisterWrite(RFM22B_REGISTER_77_NOMINAL_CARRIER_FREQUENCY_0,            0x00);		// frequency set to 446Mhz			}
			}
		/************************************************************************
		FUNCTION: to_rx_mode()
		DESCRIPTION:  This function prepares the RFM22B module to receive - 
			1. Turn on Rx antenna circuitry
			2. Clear FIFO
			3. Set mode to receive
			4. Turn on RFM22B Packet Received Interrupt
		*************************************************************************/
		void Driver_AnoRadRarioModule::RFM22B_rxMode(void)
			{
			//	unsigned char i;
//			this->clearRXBuf();//так лучше...
			
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, 0x01);	// to ready mode
			RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, (0x01 | 1<<6));	// to ready mode
			
			//	i = read(0x03);		// read interrupt vector
			//	i = read(0x04);		// read interrupt vector
			RFM22B_RegisterRead(RFM22B_REGISTER_03_INTERRUPT_STATUS_1);		// read interrupt vector
			RFM22B_RegisterRead(RFM22B_REGISTER_04_INTERRUPT_STATUS_2);		// read interrupt vector

			//	cbi(PORTC,TXANT);	// Turn off Tx Antenna select input pin
			//	sbi(PORTC,RXANT);	// Turn on Rx Antenna select input pin
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_7E_RX_FIFO_CONTROL, this->packetSize);	// set RX FIFO almost full threshold
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_08_OPERATING_FUNCTION_CONTROL_2, 0x03);	// clear contents of FIFO - reset FIFO
			RFM22B_RegisterWrite(RFM22B_REGISTER_08_OPERATING_FUNCTION_CONTROL_2, 0x00);	// clear contents of FIFO - clear FIFO
			
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, 5);		// RX on, Ready mode
//			RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, (5 | 0x40));		// RX on, Ready mode
			RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, (5 | 1<<6));		// RX on, Ready mode, LowBat
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_05_INTERRUPT_ENABLE_1, 1<<1);		// Valid Packet Received interrupt enabled
//			RFM22B_RegisterWrite(RFM22B_REGISTER_05_INTERRUPT_ENABLE_1, 1<<0);		// CRC Error interrupt enabled

			//this->RXState	= CURRENT_RX_STATES::CURRENT_RX_STATE_AWAITING_RSSI;

			//#warning remove this
			//RFM22B_RegisterWrite(RFM22B_REGISTER_06_INTERRUPT_ENABLE_2, (1<<7));	//Enable Sync Word Detected.
//			RFM22B_RegisterWrite(RFM22B_REGISTER_06_INTERRUPT_ENABLE_2, (1<<6));	//Enable Valid Preamble Detected.
			//#warning remove this


			//	RFM22B_RegisterWrite(RFM22B_REGISTER_05_INTERRUPT_ENABLE_1, 0);		//
			//	RFM22B_RegisterWrite(RFM22B_REGISTER_06_INTERRUPT_ENABLE_2, 64);	// Valid preamble
			}
/************************************************************************
	FUNCTION: RFM22B_txMode()
	DESCRIPTION:  This function prepares the RFM22B module to transmit - 
		1. Turn on Tx antenna circuitry
		2. Clear FIFO
		3. Send data to be transmitted
		4. Enable Packet Sent Interrupt
		5. Set mode to transmit - RFM22B transmits contents of FIFO
		4. Wait for transmit complete (Packet Sent Interrupt)
		6. Set mode to ready mode.
*************************************************************************/
		void Driver_AnoRadRarioModule::RFM22B_txMode(void)
			{
			this->ModeReady();
			//RFM22B_readyMode();	// To ready mode
			//RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, 0);
			//	cbi(PORTC, RXANT);
			//	sbi(PORTC, TXANT);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_08_OPERATING_FUNCTION_CONTROL_2, 0x03);	// FIFO reset
			RFM22B_RegisterWrite(RFM22B_REGISTER_08_OPERATING_FUNCTION_CONTROL_2, 0x00);	// Clear FIFO
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_34_PREAMBLE_LENGTH, this->PREAMBLE_LENGTH);//64);	// preamble = 64nibble
			RFM22B_setTransmitPacketSize(this->packetSize);	// packet length = 17bytes - DOES THIS NEED TO BE HERE????? - ALREADY SET IN init_RFM22()



			//    RFM22B_RegisterWrite(RFM22B_REGISTER_7F_FIFO_ACCESS, PKTSIZE);
			for (uint8_t i=0; i<this->packetSize; i++)
				{
				RFM22B_RegisterWrite(RFM22B_REGISTER_7F_FIFO_ACCESS, this->txBuffer[i]);	// send payload to the FIFO
				}

			RFM22B_RegisterWrite(RFM22B_REGISTER_05_INTERRUPT_ENABLE_1, 0x04);	// enable packet sent interrupt
			//	i = read(0x03);		// Read Interrupt status1 register
			//	i = read(0x04);
			RFM22B_RegisterRead(RFM22B_REGISTER_03_INTERRUPT_STATUS_1);		// Read Interrupt status1 register
			RFM22B_RegisterRead(RFM22B_REGISTER_04_INTERRUPT_STATUS_2);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, 9 | 1<<6 );		// Start TX
			
//			while ((RFM22B_NIRQ_PIN & (1<<RFM22B_NIRQ_BIT)) != 0)
			while (RFM22B_PinNIRQ::IsPinHigh())
			// wait for packet sent interrupt (NIRQ goes low)
			;
			
			//RFM22B_readyMode();
			RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, 0);
			
			//	cbi(PORTC, RXANT);
			//	cbi(PORTC, TXANT);
			}
		void Driver_AnoRadRarioModule::sendBufferToRM(void)
			{
			//RFM22B_readyMode();	// To ready mode
			this->ModeReady();
//			RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, 0);
			//	cbi(PORTC, RXANT);
			//	sbi(PORTC, TXANT);
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_08_OPERATING_FUNCTION_CONTROL_2, 0x03);	// FIFO reset
			RFM22B_RegisterWrite(RFM22B_REGISTER_08_OPERATING_FUNCTION_CONTROL_2, 0x00);	// Clear FIFO
			
			RFM22B_RegisterWrite(RFM22B_REGISTER_34_PREAMBLE_LENGTH, this->PREAMBLE_LENGTH);	// preamble = 64nibble
			RFM22B_setTransmitPacketSize(this->packetSize);	// packet length = 17bytes - DOES THIS NEED TO BE HERE????? - ALREADY SET IN init_RFM22()



	//    RFM22B_RegisterWrite(RFM22B_REGISTER_7F_FIFO_ACCESS, PKTSIZE);
	for (uint8_t i=0; i<this->packetSize; i++)
		{
		RFM22B_RegisterWrite(RFM22B_REGISTER_7F_FIFO_ACCESS, this->txBuffer[i]);	// send payload to the FIFO
		}

	RFM22B_RegisterWrite(RFM22B_REGISTER_05_INTERRUPT_ENABLE_1, 0x04);	// enable packet sent interrupt
	//	i = read(0x03);		// Read Interrupt status1 register
	//	i = read(0x04);
	RFM22B_RegisterRead(RFM22B_REGISTER_03_INTERRUPT_STATUS_1);		// Read Interrupt status1 register
	RFM22B_RegisterRead(RFM22B_REGISTER_04_INTERRUPT_STATUS_2);
	}
uint8_t Driver_AnoRadRarioModule::startTX(void)
	{
	if (!this->isTXBufInit)
		{
		return Class_HAL::ERROR_RM0_TX_BUF_NOT_INIT;
		}
	if (!this->isRMInit)
		{
		return Class_HAL::ERROR_RM0_NOT_INIT;
		}
	/*while(1)
		{
		wdt_reset();
		PORTD	^= 1<<6;
		_delay_ms(10);
		}*/
	RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, 9 | 1<<6 );		// Start TX
	//PORTD	^= 1<<6;
	return Class_HAL::ERROR_NO_ERRORS;
	}
/************************************************************************
	FUNCTION: RFM22B_reset() 
	DESCRIPTION:  This function performs a hardware reset of the RFM22B 
*************************************************************************/
void Driver_AnoRadRarioModule::RFM22B_reset(void)
	{

//	sbi(PORTB,SDN);		// enable RFM22B Shutdown pin (turn RFM22B off)
//	sbi(SDN_PORT,SDN_BIT);		// enable RFM22B Shutdown pin (turn RFM22B off)
    RFM22B_POWER_OFF;
	_delay_ms(5);		// wait 5 ms
//	cbi(PORTB,SDN);		// disable shutdown (turn RFM22B back on)
//	cbi(SDN_PORT,SDN_BIT);		// disable shutdown (turn RFM22B back on)
    RFM22B_POWER_ON;
	while(1)
		{
//		if(!(RFM22B_NIRQ_PIN & (1<<RFM22B_NIRQ_BIT)))
		if(RFM22B_PinNIRQ::IsPinHigh())
			{
			_delay_ms(25);		//delay some time before re-initialization of the module
			
			break;
			}	
		}
	RFM22B_RegisterRead(0x03);				// clear interrupts by reading register
	RFM22B_RegisterRead(0x04);				// clear interrupts
	//sbi(RFM22B_SPI_PORT, RFM22B_NSEL);		// Disable chip select line
	RFM22B_PinNSEL::SetOutHigh();			// Disable chip select line
//	cbi(PORTC,TXANT);		// Ensure transmit antenna circuitry is off
//	cbi(PORTC,RXANT);		// Ensure receive antenna circuitry is off
	RFM22B_init();			// Initialize all RFM22 registers
	//this->RXState	= Driver_AnoRadRarioModule::CURRENT_RX_STATES::CURRENT_RX_STATE_NONE;
	}
/*
bool Driver_AnoRadRarioModule::packetReceived1(void)
	{
//	return (RFM22B_NIRQ_PIN & (1<<RFM22B_NIRQ_BIT)) == 0;
	return RFM22B_PinNIRQ::isPinLow();
	}
*/
//void TXMode(void);
void Driver_AnoRadRarioModule::IOInit(void)
	{
	RFM22B_ioinit();
	}
void Driver_AnoRadRarioModule::fetchPacket(void)//должен вызываться ТОЛЬКО из прерывания
	{
	for (uint8_t i=0; i<this->packetSize; i++)
		{
		HACK_packetContainer[i]	= RFM22B_RegisterRead(RFM22B_REGISTER_7F_FIFO_ACCESS );
		}
	}
void Driver_AnoRadRarioModule::getPacket(void)
	{
	memcpy(this->rxBuffer, this->HACK_packetContainer, packetSize);
	/*if (this->m_isPacketReceived)
		{
		return;
		}*/
	/*
	if (this->RXState != Driver_AnoRadRarioModule::CURRENT_RX_STATES::CURRENT_RX_STATE_RSSI_RECEIVED)//we need to rcv RSSI first
		{
		//some strange error =(
		#ifdef DEBUG_USART_CODES
			USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_ANORAD_RM_STRANGTE_ERROR);
		#endif // DEBUG_USART_CODES
		return;
		}
	//#warning "make private SPILocked"
	//while(SPILocked);//ждёмс, если заблокировано
	//SPILocked=true;
	//this->m_isPacketReceived	= true;
	this->fetchPacket();
	this->RXState	= Driver_AnoRadRarioModule::CURRENT_RX_STATES::CURRENT_RX_STATE_PACKET_RECEIVED;
	//SPILocked=false;
	*/
	}
void Driver_AnoRadRarioModule::TXMode(void)
	{
	//this->m_isPacketReceived	= false;
	//this->RXState	= Driver_AnoRadRarioModule::CURRENT_RX_STATES::CURRENT_RX_STATE_NONE;
	this->RFM22B_txMode();
	}
uint8_t Driver_AnoRadRarioModule::fetchRSSIRaw(void)
	{
	//if (this->RXState != Driver_AnoRadRarioModule::CURRENT_RX_STATES::CURRENT_RX_STATE_AWAITING_RSSI)
		//{
		//strange error
		//return 0;
		//}
	//this->RXState	= Driver_AnoRadRarioModule::CURRENT_RX_STATES::CURRENT_RX_STATE_RSSI_RECEIVED;
	return RFM22B_RegisterRead(RFM22B_REGISTER_26_RSSI);
	}
uint8_t Driver_AnoRadRarioModule::getRSSIRaw(void)
	{
	return this->globalRSSI;
	}
void Driver_AnoRadRarioModule::receiveBegin(void)
	{
	#ifdef DEBUG_USART_CODES
		USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_ANORAD_RM_RECEIVE_BEGIN);
	#endif // DEBUG_USART_CODES
	//this->m_isPacketReceived	= false;
	this->isEnvPacketReceived	= false;
	//HACK_RCV_RESTART;
	Hack_RcvMayStuckTimer_Reload();
	//this->RXState	= Driver_AnoRadRarioModule::CURRENT_RX_STATES::CURRENT_RX_STATE_AWAITING_RSSI;
	//GICR|=(1<<INT1) | (0<<INT0);
	//this->RSSIReceived	= false;
	this->RFM22B_rxMode();
	}
void Driver_AnoRadRarioModule::ClearFifo(void)
	{
	#warning "[T] TODO Driver_AnoRadRarioModule::ClearFifo (RFM23)"
	}
void Driver_AnoRadRarioModule::RSSI_ISR(void)
	{
	uint8_t RM_Freeze_timer=100;
	
	#ifdef DEBUG_USART_CODES
		USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_ISR_RSSI_RECEIVED_ENTERING);
	#endif // DEBUG_USART_CODES
	
	//Driver_AnoRadRarioModule EnvironmentRarioModule
	HAL.EnvironmentRarioModule.globalRSSI			= HAL.EnvironmentRarioModule.fetchRSSIRaw();
	//_delay_us(10);
	sei();
	while (RFM22B_PinNIRQ::IsPinLow() == false)//100&10us=1ms
		{
		#ifdef DEBUG_USART_CODES
			USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_ISR_RSSI_WAIT_TICK);
		#endif // DEBUG_USART_CODES
		
		_delay_us(10);
		if (--RM_Freeze_timer == 0)//should be never happen
			{
			#ifdef DEBUG_USART_CODES
				USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_ISR_RSSI_WAIT_ERROR);
			#endif // DEBUG_USART_CODES
			HAL.EnvironmentRarioModule.receiveBegin();//restart rcv
			return;
			}
		}
	cli();
	HAL.EnvironmentRarioModule.fetchPacket();
	
	UNION_UINT16_LITTLE_ENDIAN crc;

	crc.value_int	= CRC16_INIT_VALUE;
	for (uint8_t i=0;i<Class_StalkerLayer0::STRUCTURE_DATA_SIZE;i++)
		{
		crc.value_int	= Crc16Update(crc.value_int, HAL.EnvironmentRarioModule.HACK_packetContainer[i]);
		}
	if (crc.byte_field.h == HAL.EnvironmentRarioModule.HACK_packetContainer[Class_StalkerLayer0::STRUCTURE_0X04_CRC16_H] && crc.byte_field.l == HAL.EnvironmentRarioModule.HACK_packetContainer[Class_StalkerLayer0::STRUCTURE_0X05_CRC16_L])
		{
		this->isEnvPacketReceived	= true;
		#ifdef DEBUG_USART_CODES
			USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_ISR_RSSI_CRC_OK);
			USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_ISR_RSSI_GOOD_PACKET_RECEIVED);
		#endif // DEBUG_USART_CODES
		return;
		//return true;
		}
	#ifdef DEBUG_USART_CODES
		USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_ISR_RSSI_CRC_FAIL);
	#endif // DEBUG_USART_CODES
	HAL.EnvironmentRarioModule.receiveBegin();//restart rcv
	this->isEnvPacketReceived	= false;
	}
volatile bool Driver_AnoRadRarioModule::isPacketReceived(void)
	{
	//return this->m_isPacketReceived;
	return this->isEnvPacketReceived;
	/*
	if (this->RXState == Driver_AnoRadRarioModule::CURRENT_RX_STATES::CURRENT_RX_STATE_RSSI_RECEIVED)
		{
		return RFM22B_PinGPIO0::isPinLow();
		}
	return false;
	*/
	/*
	//if ((RFM22B_GPIO0_PIN & 1<<RFM22B_GPIO0_BIT) == 0)
//	if (RFM22B_PinGPIO0::isPinLow())
	if (this->packetReceived() && !SPILocked)
		{
		SPILocked=true;
		if ((RFM22B_getStatus() & Driver_AnoRadRarioModule::STATUS_STATE_RX) == 0)
			{
			SPILocked=false;
			return true;
			}
		}
	SPILocked=false;
	return false;
	*/
	}
//void Driver_AnoRadRarioModule::PacketProcessed(void)
//	{
//	this->RSSIReceived			= false;
//	SPILocked					= false;
//	}
Driver_AnoRadRarioModule::TRX_STATE Driver_AnoRadRarioModule::getState(void)
	{
//	switch (RFM22B_getStatus() & 0b00)1
	switch (RFM22B_getStatus() & 0b11)
		{
		case STATUS_STATE_IDLE:
			{
			return this->TRX_STATE_IDLE;
			}
		break;

		case STATUS_STATE_RX:
			{
			return this->TRX_STATE_RECEIVING;
			}
		break;

		case STATUS_STATE_TX:
			{
			return this->TRX_STATE_TRANSMITTING;
			}
		break;
		}
	return this->TRX_STATE_UNKNOWN;
	}
void Driver_AnoRadRarioModule::deviceEnable(void)
	{
	
	}
void Driver_AnoRadRarioModule::deviceDisable(void)
	{
	
	}
void Driver_AnoRadRarioModule::waitModeReady(void)
	{
	
	}
void Driver_AnoRadRarioModule::ModeReady(void)
	{
	//this->RXState	= Driver_AnoRadRarioModule::CURRENT_RX_STATES::CURRENT_RX_STATE_NONE;
	RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, 0x01);	// to ready mode
	}
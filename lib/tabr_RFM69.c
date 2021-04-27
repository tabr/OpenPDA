// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//TODO: прерывания и блокировка прерываний
unsigned char RFM69_SPI_send(unsigned char data)
{
	//	unsigned char tmp=0;
	RFM69_SPI.DATA	= data;
	while (!(RFM69_SPI.STATUS & SPI_IF_bm))
	{
		//		++tmp;
		//		PORTQ_OUTTGL	= (1<<PIN0_bp);
	}        //Wait Interrupt
	return RFM69_SPI.DATA;
	//	if (tmp == 0)
	//		{
	//		while(1) {};
	//		}
//	return data;
}
/*
unsigned char RFM69_ReadTemperature()//TODO: Не корректно работает блеааа!!!!!!
	{
	RFM69_Mode_standby();
	RFM69_WriteReg(RFM69_REGISTER_4E_TEMP1,1<<3);
	while (RFM69_ReadReg(RFM69_REGISTER_4E_TEMP1) & (1<<2) == 0){}//Toggles back to 0 when the measurement has completed.
	return RFM69_ReadReg(RFM69_REGISTER_4F_TEMP2);
	}
*/
unsigned char RFM69_GetMode()
	{
	unsigned char tmp;
	tmp	= RFM69_ReadReg(RFM69_REGISTER_01_OPMODE) & 0b00011100;
	tmp = tmp>>2;
	return tmp;
	}
unsigned char RFM69_ReadReg(unsigned char addr)
{
	RFM69_ACTIVATE;
	RFM69_SPI_send(addr & 0x7F);
	addr	= RFM69_SPI_send(0);
	RFM69_DEACTIVATE;
	return addr;//tmp=)
}
void RFM69_WriteReg(unsigned char addr, unsigned char value)
{
	RFM69_ACTIVATE;
	//	select();
	RFM69_SPI_send(addr | 0x80);
	RFM69_SPI_send(value);
	RFM69_DEACTIVATE;
	//	unselect();
}

void RFM69_SetBitrate(uint32_t f)//т.к. эти функции буду вызываться только при инициализации, не обязательно их оптимизировать
	{
	UNION_UINT16 registerData;
	registerData.value_int	= 32000000/f;
	RFM69_WriteReg(RFM69_REGISTER_05_FDEVMSB,registerData.byte_field.h);
	RFM69_WriteReg(RFM69_REGISTER_06_FDEVLSB,registerData.byte_field.l);
	}
uint32_t RFM69_GetBitrate()//т.к. эти функции буду вызываться только при инициализации, не обязательно их оптимизировать
	{
	UNION_UINT16 registerData;
//	regieterData.value_int	= 32000000/f;
	registerData.byte_field.h	= RFM69_ReadReg(RFM69_REGISTER_05_FDEVMSB);
	registerData.byte_field.l	= RFM69_ReadReg(RFM69_REGISTER_06_FDEVLSB);
	return 32000000/registerData.value_int;
	}
void RFM69_SetFrequencyDeviation(uint32_t fdev)//т.к. эти функции буду вызываться только при инициализации, не обязательно их оптимизировать
	{
	UNION_UINT16 registerData;
	registerData.value_int	= fdev/RFM69_CONSTANTS_FSTREP;
	RFM69_WriteReg(RFM69_REGISTER_05_FDEVMSB,		registerData.byte_field.h); //default:5khz
	RFM69_WriteReg(RFM69_REGISTER_06_FDEVLSB,		registerData.byte_field.l);
	}
uint32_t RFM69_GetFrequencyDeviation()//т.к. эти функции буду вызываться только при инициализации, не обязательно их оптимизировать
	{
	UNION_UINT16 registerData;
	registerData.byte_field.h	= RFM69_ReadReg(RFM69_REGISTER_05_FDEVMSB);
	registerData.byte_field.l	= RFM69_ReadReg(RFM69_REGISTER_06_FDEVLSB);
	return registerData.value_int*RFM69_CONSTANTS_FSTREP;
	}
void RFM69_SetFrequencyCarrier(uint32_t freq)//т.к. эти функции буду вызываться только при инициализации, не обязательно их оптимизировать
	{
	UNION_UINT32 registerData;
	registerData.value_int	= freq/RFM69_CONSTANTS_FSTREP;
	RFM69_WriteReg(RFM69_REGISTER_07_FRFMSB,		registerData.byte_field.mh);
	RFM69_WriteReg(RFM69_REGISTER_08_FRFMID,		registerData.byte_field.ml);
	RFM69_WriteReg(RFM69_REGISTER_09_FRFLSB,		registerData.byte_field.l);
	}
uint32_t RFM69_GetFrequencyCarrier()//т.к. эти функции буду вызываться только при инициализации, не обязательно их оптимизировать
	{
	UNION_UINT32 registerData;
	registerData.byte_field.h	= 0;
	registerData.byte_field.mh	= RFM69_ReadReg(RFM69_REGISTER_07_FRFMSB);
	registerData.byte_field.ml	= RFM69_ReadReg(RFM69_REGISTER_08_FRFMID);
	registerData.byte_field.l	= RFM69_ReadReg(RFM69_REGISTER_09_FRFLSB);
	return registerData.value_int*RFM69_CONSTANTS_FSTREP;
	}
void RFM69_setHighPower()
	{
//	_isRFM69HW = onOff;
	//TODO: блядство какое-то
//	writeReg(RFM69_REGISTER_13_OCP, _isRFM69HW ? RF_OCP_OFF : RF_OCP_ON);
	RFM69_WriteReg(RFM69_REGISTER_13_OCP, _isRFM69HW ? (RFM69_REGISTER_13_OCP_4_OCP_ON_OCP_DISABLED | 0x0F) : (RFM69_REGISTER_13_OCP_4_OCP_ON_OCP_ENABLED | RFM69_REGISTER_13_OCP_30_OCP_TRIM_DEFAULT));
//	if (_isRFM69HW) //turning ON
#ifdef _isRFM69HW
	RFM69_WriteReg(RFM69_REGISTER_11_PALEVEL, (RFM69_ReadReg(RFM69_REGISTER_11_PALEVEL) & RFM69_REGISTER_11_PALEVEL_40_OUTPUT_POWER_MASK) | RFM69_REGISTER_11_PALEVEL_6_PA_1_ON_SETON | RFM69_REGISTER_11_PALEVEL_5_PA_2_ON_SETON); //enable P1 & P2 amplifier stages
#else
//	writeReg(RFM69_REGISTER_11_PALEVEL, RFM69_REGISTER_11_PALEVEL_7_PA_0_ON_SETON | RFM69_REGISTER_11_PALEVEL_6_PA_1_ON_SETOFF | RFM69_REGISTER_11_PALEVEL_5_PA_2_ON_SETOFF | _powerLevel); //enable P0 only
writeReg(RFM69_REGISTER_11_PALEVEL, RFM69_REGISTER_11_PALEVEL_7_PA_0_ON_SETON | RFM69_REGISTER_11_PALEVEL_6_PA_1_ON_SETOFF | RFM69_REGISTER_11_PALEVEL_5_PA_2_ON_SETOFF | 0b11111); //enable P0 only
#endif
	}

void RFM69_setHighPowerRegs(bool onOff)
	{
	RFM69_WriteReg(RFM69_REGISTER_5A_TESTPA1, onOff ? 0x5D : 0x55);
	RFM69_WriteReg(RFM69_REGISTER_5C_TESTPA2, onOff ? 0x7C : 0x70);
	}

void RFM69_Mode_transmitter()
	{
	RFM69_WriteReg(RFM69_REGISTER_01_OPMODE, RFM69_CONFIG_OPMODE_START | RFM69_REGISTER_01_OPMODE_42_MODE_TRANSMITTER);
	}
void RFM69_Mode_receiver()
	{
	RFM69_WriteReg(RFM69_REGISTER_01_OPMODE, RFM69_CONFIG_OPMODE_START | RFM69_REGISTER_01_OPMODE_42_MODE_RECEIVER);
	}
void RFM69_Mode_synthesizer()
	{
	RFM69_WriteReg(RFM69_REGISTER_01_OPMODE, RFM69_CONFIG_OPMODE_START | RFM69_REGISTER_01_OPMODE_42_MODE_FREQUENCY_SYNTHESIZER);
	}
void RFM69_Mode_standby()
	{
	RFM69_WriteReg(RFM69_REGISTER_01_OPMODE, RFM69_CONFIG_OPMODE_START | RFM69_REGISTER_01_OPMODE_42_MODE_STANDBY);
	}
void RFM69_Mode_sleep()
	{
	RFM69_WriteReg(RFM69_REGISTER_01_OPMODE, RFM69_CONFIG_OPMODE_START | RFM69_REGISTER_01_OPMODE_42_MODE_SLEEP);
	}
void RFM69_Init()
	{
	//unsigned char tmp19,tmp2,tmp3;
	//		sbi(RFM_RST_DDR,	RFM_RST_PIN);
	//		sbi(RFM_DC_DDR,		RFM_DC_PIN);
	SetInput(RFM69_MISO_DDR,		RFM69_MISO_PIN);
	SetOutput(RFM69_SS_DDR,			RFM69_SS_PIN);
	SetOutput(RFM69_MOSI_DDR,		RFM69_MOSI_PIN);
	SetOutput(RFM69_CLK_DDR,		RFM69_CLK_PIN);
	cbi(RFM69_CLK_PORT,				RFM69_CLK_PIN);
	SetInput(RFM69_DIO0_DDR,		RFM69_DIO0_PIN);
	cbi(RFM69_DIO0_DDR,				RFM69_DIO0_PIN);//какого-то члена не работает, если врубить подтяжку....
	//					  [double CLK]	[enable][DORD] [master][transfer mode][clk prescaller]
	RFM69_SPI.CTRL		= 1<<7			| 1<<6	| 0<<5 | 1<<4 | (0<<3 | 0<<2) | (0<<1 | 0<<0);
	//	RFM_SPI.CTRL	= 0<<7			| 1<<6	| 0<<5 | 1<<4 | (0<<3 | 0<<2) | (1<<1 | 1<<0);
	RFM69_SPI.INTCTRL = SPI_INTLVL_OFF_gc ; // no interrupt

//	не очень понятный ритуал
  do RFM69_WriteReg(RFM69_REGISTER_2F_SYNCVALUE1, 0xaa); while (RFM69_ReadReg(RFM69_REGISTER_2F_SYNCVALUE1) != 0xaa);
  do RFM69_WriteReg(RFM69_REGISTER_2F_SYNCVALUE1, 0x55); while (RFM69_ReadReg(RFM69_REGISTER_2F_SYNCVALUE1) != 0x55);



	RFM69_WriteReg(RFM69_REGISTER_01_OPMODE,		0<<RFM69_REGISTER_01_OPMODE_7_SEQUENCER_OFF | 0<<RFM69_REGISTER_01_OPMODE_6_LISTEN_ON | RFM69_REGISTER_01_OPMODE_42_MODE_STANDBY);
	RFM69_WriteReg(RFM69_REGISTER_02_DATAMODUL,		RFM69_REGISTER_02_DATAMODUL_65_DATAMODE_PACKET | RFM69_REGISTER_02_DATAMODUL_43_MODULATION_TYPE_FCK | RFM69_REGISTER_02_DATAMODUL_10_MODULATION_SHAPING_FCK_NO_SHAPING ); //no shaping
//	RFM69_WriteReg(RFM69_REGISTER_03_BITRATEMSB,	RF_BITRATEMSB_55555); //default:4.8 KBPS
//	RFM69_WriteReg(RFM69_REGISTER_04_BITRATELSB,	RF_BITRATELSB_55555);
	RFM69_SetBitrate(55555);
//	RFM69_WriteReg(RFM69_REGISTER_05_FDEVMSB,		RF_FDEVMSB_50000); //default:5khz, (FDEV + BitRate/2 <= 500Khz)
//	RFM69_WriteReg(RFM69_REGISTER_06_FDEVLSB,		RF_FDEVLSB_50000);
	RFM69_SetFrequencyDeviation(50000);
/*
	switch (freqBand)
		{
		case RF69_315MHZ:
		tmp1	= RF_FRFMSB_315;
		tmp2	= RF_FRFMID_315;
		tmp3	= RF_FRFLSB_315;
		break;

		case RF69_433MHZ:
		tmp1	= RF_FRFMSB_433;
		tmp2	= RF_FRFMID_433;
		tmp3	= RF_FRFLSB_433;
		break;

		case RF69_868MHZ:
		tmp1	= RF_FRFMSB_868;
		tmp2	= RF_FRFMID_868;
		tmp3	= RF_FRFLSB_868;
		default:
		break;
		}

	RFM69_WriteReg(RFM69_REGISTER_07_FRFMSB, tmp1);
	RFM69_WriteReg(RFM69_REGISTER_08_FRFMID, tmp2);
	RFM69_WriteReg(RFM69_REGISTER_09_FRFLSB, tmp3);
*/	
	RFM69_SetFrequencyCarrier(433*MHZ);

    // looks like PA1 and PA2 are not implemented on RFM69W, hence the max output power is 13dBm
    // +17dBm and +20dBm are possible on RFM69HW
    // +13dBm formula: Pout=-18+OutputPower (with PA0 or PA1**)
    // +17dBm formula: Pout=-14+OutputPower (with PA1 and PA2)**
    // +20dBm formula: Pout=-11+OutputPower (with PA1 and PA2)** and high power PA settings (section 3.3.7 in datasheet)
    /// 0x11 / { REG_PALEVEL, RF_PALEVEL_PA0_ON | RF_PALEVEL_PA1_OFF | RF_PALEVEL_PA2_OFF | RF_PALEVEL_OUTPUTPOWER_11111},
    /// 0x13 / { REG_OCP, RF_OCP_ON | RF_OCP_TRIM_95 }, //over current protection (default is 95mA)	
	// RXBW defaults are { REG_RXBW, RF_RXBW_DCCFREQ_010 | RF_RXBW_MANT_24 | RF_RXBW_EXP_5} (RxBw: 10.4khz)




//	RFM69_WriteReg(RFM69_REGISTER_19_RXBW,			RFM69_REGISTER_19_RXBW_75_DCC_FREQ_DEFAULT_4PERCENT | RFM69_REGISTER_19_RXBW_43_RX_BW_MANT_16 | RF_RXBW_EXP_2 ); //(BitRate < 2 * RxBw)
	RFM69_WriteReg(RFM69_REGISTER_19_RXBW,			RFM69_REGISTER_19_RXBW_75_DCC_FREQ_DEFAULT_4PERCENT | RFM69_REGISTER_19_RXBW_43_RX_BW_MANT_16 | RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT16_1250KHZ ); //(BitRate < 2 * RxBw)
//	RFM69_WriteReg(RFM69_REGISTER_25_DIOMAPPING1,	RF_DIOMAPPING1_DIO0_01 ); //DIO0 is the only IRQ we're using
//TODO Ебанутая таблица!!!
	RFM69_WriteReg(RFM69_REGISTER_25_DIOMAPPING1,	0b01<<6 ); //DIO0 is the only IRQ we're using
//TODO: разобраться...

	RFM69_WriteReg(RFM69_REGISTER_29_RSSITHRESH,	220 ); //must be set to dBm = (-Sensitivity / 2) - default is 0xE4=228 so -114dBm);
	// 0x2d -->
	// { RFM69_REGISTER_2D_PREAMBLELSB, RF_PREAMBLESIZE_LSB_VALUE } // default 3 preamble bytes 0xAAAAAA
	RFM69_WriteReg(RFM69_REGISTER_2E_SYNCCONFIG,	RFM69_REGISTER_2E_SYNCCONFIG_7_SYNC_ON_TURN_ON | RFM69_REGISTER_2E_SYNCCONFIG_6_FIFO_FILL_CONDITION_INTERRUPT | 0b001<<RFM69_REGISTER_2E_SYNCCONFIG_53_SYNC_SIZE_PLUS_1 | 0b000<<RFM69_REGISTER_2E_SYNCCONFIG_20_SYNC_TOL );
	RFM69_WriteReg(RFM69_REGISTER_2F_SYNCVALUE1,	0x2D );      //attempt to make this compatible with sync1 byte of RFM12B lib
	RFM69_WriteReg(RFM69_REGISTER_30_SYNCVALUE2,	NETWORK_ID ); //NETWORK ID
	RFM69_WriteReg(RFM69_REGISTER_37_PACKETCONFIG1, RFM69_REGISTER_37_PACKETCONFIG1_7_PACKET_FORMAT_VARIABLE | RFM69_REGISTER_37_PACKETCONFIG1_65_PACKET_FORMAT_DC_FREE_NONE | RFM69_REGISTER_37_PACKETCONFIG1_4_CRC_ON_TURN_ON | RFM69_REGISTER_37_PACKETCONFIG1_3_CRC_AUTO_CREAR_OFF_CLEAR_FIFO_RESTART_PRCV | RFM69_REGISTER_37_PACKETCONFIG1_21_ADDRESS_FILTERING_NONE );
	RFM69_WriteReg(RFM69_REGISTER_38_PAYLOADLENGTH, 61 ); //in variable length mode: the max frame size, not used in TX
    // 0x39 ->>
	// { REG_NODEADRS, nodeID }, //turned off because we're not using address filtering
	RFM69_WriteReg(RFM69_REGISTER_3C_FIFOTHRESH,	RFM69_REGISTER_3C_FIFOTHRESH_7_TX_START_CONDITION_FIFO_NOT_EMPTY | RFM69_REGISTER_3C_FIFOTHRESH_60_FIFO_THRESHOLD_DEFAULT ); //TX on FIFO not empty

	RFM69_WriteReg(RFM69_REGISTER_3D_PACKETCONFIG2,	RFM69_REGISTER_3D_PACKETCONFIG2_74_INTER_PACKET_RX_DELAY_2_BIT | RFM69_REGISTER_3D_PACKETCONFIG2_1_AUTO_RESTART_RX_ON_SETON | RFM69_REGISTER_3D_PACKETCONFIG2_0_AES_ON_SETOFF ); //RXRESTARTDELAY must match transmitter PA ramp-down time (bitrate dependent)
	RFM69_WriteReg(RFM69_REGISTER_6F_TESTDAGC,		RFM69_REGISTER_6F_TESTDAGC_70_CONTINUOUS_DAGC_IMPROVED_ALBO0 );  // run DAGC continuously in RX mode, recommended default for AfcLowBetaOn=0

//writeReg(RFM69_REGISTER_3D_PACKETCONFIG2, (readReg(RFM69_REGISTER_3D_PACKETCONFIG2) & 0xFE));
//  setHighPower(_isRFM69HW); //called regardless if it's a RFM69W or RFM69HW
  RFM69_setHighPower(); //called regardless if it's a RFM69W or RFM69HW
  RFM69_Mode_standby();
  while ((RFM69_ReadReg(RFM69_REGISTER_27_IRQFLAGS1) & RFM69_REGISTER_27_IRQFLAGS1_7_MODE_READY_SET) == 0x00); // Wait for ModeReady
  //TODO: attachInterrupt(0, RFM69::isr0, RISING);



//	RFM69_WriteReg();
//	RFM69_WriteReg();
//	RFM69_WriteReg();
}
void RFM69_SendFrame()
	{
	unsigned char toAddress=255;
	unsigned char myAddress=1;
	RFM69_Mode_standby();//turn off receiver to prevent reception while filling fifo
//	while ((RFM69_GetMode() & ( RFM69_REGISTER_27_IRQFLAGS1_5_TX_READY | RFM69_REGISTER_27_IRQFLAGS1_4_PLL_LOCK)) == 0 )
//		{
//		sprintf (lcd_buf, "[%d]", RFM69_GetMode());
//		LcdString(1,LCD_LINE_2);
//		LcdUpdate();
//		} //TODO: разобраться, зачем PLL_LOCK
	while ((RFM69_ReadReg(RFM69_REGISTER_27_IRQFLAGS1) & 0x80) == 0){}// Wait for ModeReady //TODO...
	RFM69_WriteReg(RFM69_REGISTER_25_DIOMAPPING1, 0);// DIO0 is "Packet Sent" //TODO: с нулём разобраться - добавить символьную кончтанту
	RFM69_ACTIVATE;
	RFM69_SPI_send(RFM69_REGISTER_00_FIFO | 0x80);//TODO: зачем 0x80???
	RFM69_SPI_send(RFM69_CONFIG_BUFFER_SIZE + 3);//TODO: зачем +3??
	RFM69_SPI_send(toAddress);
	RFM69_SPI_send(myAddress);
	RFM69_SPI_send(0x00);//TODO: зачем???
	for (unsigned char i = 0; i < RFM69_CONFIG_BUFFER_SIZE; i++)
		{
		RFM69_SPI_send(((unsigned char*)RFM69_buffer)[i]);
		}
	RFM69_DEACTIVATE;

	RFM69_Mode_transmitter();
	while ((RFM69_DIO0_IN & 1<<RFM69_DIO0_PIN) == 0){}; //wait for DIO0 to turn HIGH signalling transmission finish
	
//	delay_ms(2000);
	RFM69_Mode_standby();
	}
// --> Переключение режимов...
//	// we are using packet mode, so this check is not really needed
//	// but waiting for mode ready is necessary when going from sleep because the FIFO may not be immediately available from previous mode
//	while (_mode == RF69_MODE_SLEEP && (readRFM69_REGISTER_(RFM69_REGISTER__IRQFLAGS1) & RF_IRQFLAGS1_MODEREADY) == 0x00); // Wait for ModeReady
//
//	_mode = newMode;

void RFM69_ReceiveBegin(void)//TODO: преобразовать числа в константы....
	{
	if (RFM69_ReadReg(RFM69_REGISTER_28_IRQFLAGS2) & 0x04)
		RFM69_WriteReg(RFM69_REGISTER_3D_PACKETCONFIG2, (RFM69_ReadReg(RFM69_REGISTER_3D_PACKETCONFIG2) & 0xFB) | 0x04 );// avoid RX deadlocks
	RFM69_WriteReg(RFM69_REGISTER_25_DIOMAPPING1, 0x40);//set DIO0 to "PAYLOADREADY" in receive mode
	RFM69_Mode_receiver();
	}
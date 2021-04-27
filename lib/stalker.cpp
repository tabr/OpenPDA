// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

/*
void STALKER::Init(void)
	{
	System.usart_init();
	LcdInit();
	
	//	radio.initialize(FREQUENCY,NODEID,NETWORKID);
	radio.initialize(NODEID,NETWORKID);
	//	radio.encrypt(ENCRYPTKEY);
	radio.encrypt(0);
	radio.promiscuous(promiscuousMode);
	
	}
*/
/*
void STALKER::NewPacketAccepted()
		{
		uint16_t itmp;
//		newPacketReceived=1;
		switch (radio._RXBuffer[PACKET_RADIOMARK_TYPE])
			{
			case RADIOMARK_TYPE_RADIATION_ANOMALY:
			if (radio._RXBuffer[RADIOMARK_PACKET_STRUCT_RADANO_RAD_MULTIPLIER] > 0)
				{
				itmp	= radio._RXBuffer[RADIOMARK_PACKET_STRUCT_RADANO_RAD_MULTIPLIER] * radio._SIGNAL_POWER;//multiplier * [rssi/2]
				if (itmp> 255)
					itmp=255;
				Env.RadLevelSetFilter((uint8_t)itmp);
				}
			else
				{
				Env.RadLevelSetFilter(0);
				}
			//обработка аномалии (1 ступень)
			if (radio._RXBuffer[RADIOMARK_PACKET_STRUCT_RADANO_ANO_TYPE] > 0)
				{
				Anomaly.setLevelType_Filter(radio._SIGNAL_POWER, radio._RXBuffer[RADIOMARK_PACKET_STRUCT_RADANO_ANO_TYPE], radio._RXBuffer[RADIOMARK_PACKET_STRUCT_RADANO_ANO_SKIP_LEVEL], radio._RXBuffer[RADIOMARK_PACKET_STRUCT_RADANO_ANO_KILL_LEVEL] );
				}
			break;

			case RADIOMARK_TYPE_PSY:
				Env.setPsyLevelFilter(radio._SIGNAL_POWER);
			break;

			case RADIOMARK_TYPE_TIME:
				if (timeUpdateTimer == 0)
					{
					Time.hour		= radio._RXBuffer[PACKET_RADIOMARK_TYPE_PARAM0];
					Time.minute		= radio._RXBuffer[PACKET_RADIOMARK_TYPE_PARAM1];
					Time.second		= radio._RXBuffer[PACKET_RADIOMARK_TYPE_PARAM2];
					timeSecond		= Time.second;
					timeMinute		= Time.minute;
					timeHour		= Time.hour;
					timeUpdateTimer	= 255;
					}
			break;

			case RADIOMARK_TYPE_ADM_ACTION:
				
			break;

			case RADIOMARK_TYPE_SAFE_ZONE:
				IsSafeZoneDetected=1;
			break;

			case RADIOMARK_TYPE_QUEST:
				switch (radio._RXBuffer[RADIOMARK_PACKET_STRUCT_QUEST_ACTION])
					{
					case RADIOMARK_TYPE_QUEST_ACTION_COMPLETE:
						Quest.completeQuest(radio._RXBuffer[RADIOMARK_PACKET_STRUCT_QUEST_ID]);
					break;

					case RADIOMARK_TYPE_QUEST_ACTION_GIVE:
						Quest.giveQuest(radio._RXBuffer[RADIOMARK_PACKET_STRUCT_QUEST_ID]);
					break;

					case RADIOMARK_TYPE_QUEST_ACTION_FAIL:
						Quest.failQuest(radio._RXBuffer[RADIOMARK_PACKET_STRUCT_QUEST_ID]);
					break;
					}
				
			break;
			//Todo...
			}

		}
*/
void STALKER::InitRTC(void)
	{
	//->rtc
	//OSC.XOSCCTRL= OSC_XOSCSEL_32KHz_gc;/* 32kHz TOSC - 32K CLK */
	//OSC.XOSCCTRL= OSC_XOSCSEL_EXTCLK_gc;
	//CCP		= CCP_IOREG_gc;
	//OSC.CTRL|=OSC_XOSCEN_bm;//External Oscillator
	//	CLK.RTCCTRL	= CLK_RTCSRC_RCOSC_gc|CLK_RTCEN_bm;
	//	CLK.RTCCTRL	= CLK_RTCSRC_TOSC32_gc|CLK_RTCEN_bm;
	CLK.RTCCTRL	= CLK_RTCSRC_TOSC_gc|CLK_RTCEN_bm;
	//	CLK.RTCCTRL	= CLK_RTCSRC_EXTCLK_gc|CLK_RTCEN_bm;
	RTC.CTRL	= RTC_PRESCALER_DIV1024_gc;
	//	RTC.CTRL	= RTC_PRESCALER_DIV512_gc;
	RTC.CNT=0;
	RTC.PER=0;
	//	RTC.COMP=32-1;
	RTC.COMP=0;
	while(!(OSC.STATUS&OSC_XOSCRDY_bm));
	//RTC.INTCTRL	|= RTC_OVFINTLVL_HI_gc;
	RTC.INTCTRL	|= RTC_COMPINTLVL_HI_gc;
	//<-rtc
	}
void STALKER::InitInterrupts(void)
	{
/*
	//	PORTA_OUTSET	= PIN5_bm;
	PORTA.PIN5CTRL	= PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc;
	//	PORTA.INTCTRL	= (PORTA.INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) | PORT_INT1LVL_OFF_gc | PORT_INT0LVL_LO_gc;
	PORTA.INT0MASK	= PIN5_bm;
*/
	//	PORTA_OUTSET	= PIN4_bm;
	//	PORTA.PIN4CTRL	= PORT_OPC_TOTEM_gc | PORT_ISC_FALLING_gc;
//	PORTA.PIN2CTRL	= PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc;
//	PORTA.INTCTRL	= (PORTA.INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) | PORT_INT1LVL_LO_gc | PORT_INT0LVL_LO_gc;
//	PORTA.INT1MASK	= PIN2_bm;

	//		TCC0.CTRLA		= ( TCC0.CTRLA & ~TC0_CLKSEL_gm ) | TC_CLKSEL_DIV1024_gc;
	//		TCC0.PER		= 3125; //было "...-1"
	//		-> ~16kHz
	TIMER_DAC.CTRLA		= ( TIMER_DAC.CTRLA & ~TC0_CLKSEL_gm ) |  TC_CLKSEL_DIV1024_gc;
	//TIMER_DAC.CTRLA		= ( TIMER_DAC.CTRLA & ~TC0_CLKSEL_gm ) |  TC_TC0_CLKSEL_enum::TC_TC0_CLKSEL_DIV1024_gc;

//	TIMER_DAC.CTRLA		= ( TCC0.CTRLA & ~TC0_CLKSEL_gm ) | TC_CLKSEL_DIV256_gc;
	TIMER_DAC.PER		= 2-1; //15625 Hz
//	TIMER_DAC.INTCTRLA	= TC_OVFINTLVL_LO_gc; // уровень прерываний таймера low
	TIMER_DAC.INTCTRLA	= TC_OVFINTLVL_OFF_gc;
	//TIMER_DAC.INTCTRLA	= TC_TC0_OVFINTLVL_enum::TC_TC0_OVFINTLVL_OFF_gc;

	TIMER_DEATH_SOUND.CTRLA		= ( TIMER_DEATH_SOUND.CTRLA & ~TC1_CLKSEL_gm ) | TC_CLKSEL_DIV1024_gc;
//	TIMER_DEATH_SOUND.CTRLA		= ( TIMER_DEATH_SOUND.CTRLA & ~TC1_CLKSEL_gm ) | TC_TC1_CLKSEL_enum::TC_TC1_CLKSEL_DIV1024_gc;
	TIMER_DEATH_SOUND.PER		= 8-1;
	TIMER_DEATH_SOUND.INTCTRLA	= TC_OVFINTLVL_OFF_gc; // уровень прерываний таймера low
//	TIMER_DEATH_SOUND.INTCTRLA	= TC_TC1_OVFINTLVL_enum::TC_TC1_OVFINTLVL_OFF_gc; // уровень прерываний таймера low


	//timers C,D,E,F

//	TCD0.CTRLA		= ( TCD0.CTRLA & ~TC0_CLKSEL_gm ) | TC_CLKSEL_DIV1024_gc;
//	TCD0.PER		= 3125-1;//10Hz
//	TCD0.INTCTRLA	= TC_OVFINTLVL_LO_gc;

	
	TCE0.CTRLA		= ( TCE0.CTRLA & ~TC0_CLKSEL_gm ) | TC_CLKSEL_DIV256_gc;
//	TCE0.CTRLA		= ( TCE0.CTRLA & ~TC0_CLKSEL_gm ) | TC_TC0_CLKSEL_enum::TC_TC0_CLKSEL_DIV256_gc;
	TCE0.PER		= 1250-1;//100Hz => 10ms
	TCE0.INTCTRLA	= TC_OVFINTLVL_LO_gc;
//	TCE0.INTCTRLA	= TC_TC0_OVFINTLVL_enum::TC_TC0_OVFINTLVL_LO_gc;

	//		sei();
	//		__enable_iterrupt();

	PMIC.CTRL |= PMIC_MEDLVLEX_bm;
	PMIC.CTRL |= PMIC_LOLVLEN_bm;
	PMIC.CTRL |= PMIC_HILVLEN_bm;
	}
/*
void STALKER::programmStart(void)
	{
	}*/
/*
void STALKER::checkEnvironmentPacketAcception(void)
	{
	StalkerLayer1.EnvironmentLookAround();
	
	
	}
*/
void STALKER::PlayPlayerDeathSound(void)
	{
	//uint8_t i;
	PDASound.startSoundsHiFi();
	PDASound.deathSoundPtr	= &deathSound[0];
	TIMER_DEATH_SOUND.INTCTRLA	= TC_OVFINTLVL_LO_gc;
//	TIMER_DEATH_SOUND.INTCTRLA	= TC_TC1_OVFINTLVL_enum::TC_TC1_OVFINTLVL_LO_gc;
	//PDASound.stopSoundsHiFi(); //ПЕРЕНЕСЕНО В ПРЕРЫВАНИЕ
	//_delay_ms(10000);
	/*for (i=0;i<30;i++)
		{
		sprintf (lcd_buf,"%03d",(*deathSoundPtr));
		LcdString(12,LCD_LINE_2);
		LcdUpdate();
		_delay_ms(100);
		}*/
	

	//_delay_ms(1000);
	/*
	//TCC1.INTCTRLA	= TC_OVFINTLVL_LO_gc;
	for (i=0;i<512;i++)
		{
		SOUND_HIFI_DAC_CHANNEL^=127;
		delay_us(250);
		}
	//_delay_ms(128);
	//TCC1.INTCTRLA	= TC_OVFINTLVL_OFF_gc;
	delay_ms(1000);
	for (i=512;i>0;i++)
		{
		SOUND_HIFI_DAC_CHANNEL^=127;
		delay_us(250);
		}
	delay_ms(1200);
	//	for (i=0;i<512;i++)
	for (i=(1<<9);i > 0 ;i--)
		{
		SOUND_HIFI_DAC_CHANNEL^=127;
		delay_us(250);
		}
	delay_ms(1400);
	//	for (i=0;i<32767;i++)
	for (i=(1<<15);i > 0 ;i--)
		{
		//		 #asm("wdr");//КАКОГО ХУЯ?!?!?!?!?!?!?!
		SOUND_HIFI_DAC_CHANNEL^=127;
		delay_us(250);
		}
	*/
	//PDASound.stopSoundsHiFi();
	}
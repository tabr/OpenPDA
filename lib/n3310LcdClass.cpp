// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//#ifndef N3310_WITHOUT_DMA
//	#define N3310_WITH_DMA
//#endif

void n3310LcdClass::ActivateDisplay(void)
	{
	LcdPinSCE::SetOutLow();
	}
void n3310LcdClass::DeactivateDisplay(void)
	{
	TODO("this is hack: //LcdPinSCE::SetOutHigh()");
	//LcdPinSCE::SetOutHigh();
	}
void n3310LcdClass::IOInit(void)
	{
	LcdPinCLK::SetDirOut();
	LcdPinSDIN::SetDirOut();
	LcdPinDC::SetDirOut();
	LcdPinSCE::SetDirOut();
	LcdPinRST::SetDirOut();
    LcdPinRST::SetPullUp();
//while (1) {BeepPin::SetOutLow();RedLEDPin::SetOutToggle();delay_ms(1000);}
	
	LcdPinCLK::SetOutLow();//1
	LcdPinSDIN::SetOutHigh();//1
	LcdPinDC::SetOutLow();
	LcdPinSCE::SetOutHigh();//High - disabled
	LcdPinRST::SetOutHigh();
	/*
	LCD_SPI_PORT.REMAP	= PORT_SPI_bm;
	SPI_SimpleInit((void*)&LCD_SPI);
	*/
			
	//PORTE.PIN5CTRL &= ~(PORT_INVEN_bm);
	//PORTE.PIN5CTRL	= PORT_INVEN_bm;
			
	//USARTE1.BAUDCTRLA = 159;
	//USARTE1.BAUDCTRLB = 0;
	//unsigned char ucBaudCtrl;
	//ucBaudCtrl = ( F_CPU / ( 2 * 460800UL ) ) - 1;

//#ifndef N3310_WITHOUT_DMA
        
        LcdSPIInit();
//#endif
	}
void n3310LcdClass::DMA_Initialization(void)
	{
#ifdef N3310_WITH_DMA
	DMA.CTRL			= DMA_ENABLE_bm;     // Включение DMA
	//DMA.CH0.REPCNT		= 1;
	//DMA.CH0.CTRLA		= DMA_CH_BURSTLEN0_bm | DMA_CH_REPEAT_bm; // Настройка на повторяющуюся передачу 1 байтными пакетами
	DMA.CH0.CTRLA		= DMA_CH_BURSTLEN_1BYTE_gc | DMA_CH_SINGLE_bm; // Настройка на повторяющуюся передачу 1 байтными пакетами
	//DMA.CH0.CTRLA		= DMA_CH_SINGLE_bm; // Настройка на повторяющуюся передачу 1 байтными пакетами
	//DMA.CH0.CTRLB		= DMA_CH_TRNIF_bm | DMA_CH_TRNINTLVL0_bm;
	DMA.CH0.CTRLB		= DMA_CH_TRNINTLVL0_bm;
	//DMA.CH0.ADDRCTRL	= DMA_CH_SRCRELOAD_gm |DMA_CH_SRCDIR0_bm | DMA_CH_DESTRELOAD_gm | DMA_CH_DESTDIR0_bm; // Установка инкрементации адресов после каждой передачи и обновление адресов по окончанию передачи
	//DMA.CH0.ADDRCTRL	= DMA_CH_SRCRELOAD_BURST_gc | DMA_CH_SRCDIR_INC_gc | DMA_CH_DESTRELOAD_BURST_gc | DMA_CH_DESTDIR_FIXED_gc; // Установка инкрементации адресов после каждой передачи и обновление адресов по окончанию передачи
	//DMA.CH0.ADDRCTRL	= DMA_CH_SRCRELOAD_BURST_gc | DMA_CH_SRCDIR_FIXED_gc | DMA_CH_DESTRELOAD_BURST_gc | DMA_CH_DESTDIR_FIXED_gc; // Установка инкрементации адресов после каждой передачи и обновление адресов по окончанию передачи
	//DMA.CH0.ADDRCTRL	= DMA_CH_SRCRELOAD_NONE_gc | DMA_CH_SRCDIR_INC_gc | DMA_CH_DESTRELOAD_NONE_gc | DMA_CH_DESTDIR_FIXED_gc; // Установка инкрементации адресов после каждой передачи и обновление адресов по окончанию передачи
	DMA.CH0.ADDRCTRL	= DMA_CH_SRCRELOAD_TRANSACTION_gc | DMA_CH_SRCDIR_INC_gc | DMA_CH_DESTRELOAD_NONE_gc | DMA_CH_DESTDIR_FIXED_gc; // Установка инкрементации адресов после каждой передачи и обновление адресов по окончанию передачи
//	DMA.CH0.TRIGSRC		= DMA_CH_TRIGSRC_USARTE1_DRE_gc;
	DMA.CH0.TRIGSRC		= DMA_CH_TRIGSRC_OFF_gc;
	DMA.CH0.TRFCNT		= LCD_CACHE_SIZE;                  // Установка счетчика передачи на 40 байтов (т.к. int = 2 байтом)
	DMA.CH0.REPCNT		= 1;

	//DMA.CH0.SRCADDR0 = (uint16_t)&LcdCache;     // Настройка адреса источника на массив massIn
	//DMA.CH0.SRCADDR1 = (uint16_t)&LcdCache>>8;
	DMA.CH0.SRCADDR0 = (uintptr_t)&LcdCache;     // Настройка адреса источника на массив massIn
	DMA.CH0.SRCADDR1 = (uintptr_t)&LcdCache>>8;
	DMA.CH0.SRCADDR2 = 0;

	//DMA.CH0.DESTADDR0 = (int)&LcdCache1;  // Настройка адреса приемника на массив massOut
	//DMA.CH0.DESTADDR1 = (int)&LcdCache1>>8;
	//DMA.CH0.DESTADDR2 = 0;

	DMA.CH0.DESTADDR0 = (((uintptr_t) &USARTE1.DATA) >>(0*8))&0xFF;
	DMA.CH0.DESTADDR1 = (((uintptr_t) &USARTE1.DATA) >>(1*8))&0xFF;
	DMA.CH0.DESTADDR2 = 0;//(((uint16_t) &USARTE1.DATA) >>2*8)&0xFF;


	//DMA.CH0.CTRLA |= DMA_CH_ENABLE_bm;   // разрешение работы канала 0 DMA

	//DMA.CH0.CTRLA &= ~DMA_CH_ENABLE_bm;
#endif //N3310_WITH_DMA
	}
void n3310LcdClass::Reset20MS(void)
	{
	LcdPinRST::SetOutLow();
	_delay_ms(20);
	LcdPinRST::SetOutHigh();
	}
void n3310LcdClass::HardwareInitialization(void)
	{
	DeactivateDisplay();
#ifdef N3310_WITH_DMA
	LCDstartDMA			= false;
	DMA_Initialization();
#endif
//	LCDpendingHWBufRST	= false;
	
	
	Reset20MS();
	//DeactivateDisplay();
	/*
	LcdSendData( 0b00100001, LCD_CMD );							//LCD Extended Commands
	LcdSendData( 0b00000100+LCD_TEMP_CONTROL, LCD_CMD );		//Set Temp coefficent
	//PORTF.OUTSET	= 1<<4;
	#ifdef china
		LcdSendData( 0b00001000|LCD_SPI_INVERT<<3, LCD_CMD );                     //??????? ????? ? SPI
	#endif
	//return;
	LcdSendData( 0b00010000+LCD_BIAS, LCD_CMD );                         //LCD bias mode 1:48
	#ifdef china
		LcdSendData( 0b01000000+LCD_SHIFT, LCD_CMD );                         //?????? ?????? ???? ??????, ?????????? ?? ??????
	#endif
	LcdSendData( 0b10000000+LCD_VOP, LCD_CMD );                         //Set LCD Vop (Contrast)
			
	#ifdef china
	//    LcdSend( 0x20|LCD_X_MIRROR<<4|LCD_Y_MIRROR<<3|power_down<<2, LCD_CMD );            //LCD Standard Commands
		LcdSendData( 0x20|LCD_X_MIRROR<<4|LCD_Y_MIRROR<<3|0<<2, LCD_CMD );            //LCD Standard Commands
	#endif
	//        LcdSend( 0x20|power_down<<2|LCD_ADDRESSING<<1, LCD_CMD );                //LCD Standard Commands
	LcdSendData( 0x20|0<<2|LCD_ADDRESSING<<1, LCD_CMD );                //LCD Standard Commands
	LcdSendData( 0b00001000|((LCD_DISP_CONFIG<<1|LCD_DISP_CONFIG)&0b00000101), LCD_CMD );     //LCD mode
	//        LcdClear();
	LcdClearUpdate();
	*/
			
	// Отправляем команды дисплею
	//LcdSendCommand( 0x21); // Включаем расширенный набор команд (LCD Extended Commands)
	//LcdSendCommand( 0xC8); // Установка контрастности (LCD Vop)
	//LcdSendCommand( 0x06); // Установка температурного коэффициента (Temp coefficent)
	//LcdSendCommand( 0x13); // Настройка питания (LCD bias mode 1:48)
	//LcdSendCommand( 0x20); // Включаем стандартный набор команд и горизонтальную адресацию (LCD Standard Commands,Horizontal addressing mode)
	//LcdSendCommand( 0x0C); // Нормальный режим (LCD in normal mode)
			
	uint8_t commandPacket[]=
		{
		COMMAND_FUNCTION_SET__EXTENDED_INSTRUCTION_SET | COMMAND_FUNCTION_SET__POWER_DOWN_DEACTIVATE,//0b00100001,//0x21,//
		COMMAND_H1_SET_VOP_INSTRUCTION | (70 & COMMAND_H1_SET_VOP_MASK),//0b11001000,//0xc8,//
		COMMAND_H1_TEMPERATURE_CONTROL__COEFFICIENT_0,//0b00000110,//0x06,//temperature compensation for liquid crystals
		COMMAND_H1_BIAS_SYSTEM_INSTRUCTION | (2 & COMMAND_H1_BIAS_SYSTEM_MASK),//0b00010011,//0x13,//
		COMMAND_FUNCTION_SET__BASIC_INSTRUCTION_SET | COMMAND_FUNCTION_SET__HORIZONTAL_ADDRESSING | COMMAND_FUNCTION_SET__POWER_DOWN_DEACTIVATE,//0b00100000,//0x20,//
		COMMAND_H0_DISPLAY_CONTROL__NORMAL_MODE,//0b00001100,//0x0c,//
		COMMAND_H0_SET_Y_ADDRESS_RAM_INSTRUCTION | (0 & Y_ADDRESS_MASK),//0b10000000,//0x80,//
		COMMAND_H0_SET_X_ADDRESS_RAM_INSTRUCTION | (0 & X_ADDRESS_MASK),//0b01000000,//0x40,//
		};
	LcdSendCommandPacket(sizeof(commandPacket), commandPacket);

	ActivateDisplay();
	//LcdPinDC::SetOutHigh();//data next - only data
	n3310LcdClass::SetData();

	// Первичная очистка дисплея
	LcdClearUpdate();
	}
//#ifndef N3310_WITHOUT_DMA
void n3310LcdClass::StopDMATransaction(void)
	{
#ifdef N3310_WITH_DMA
	DMA.CH0.TRIGSRC		= DMA_CH_TRIGSRC_OFF_gc;
	DMA.CH0.CTRLA &= ~DMA_CH_ENABLE_bm;
#endif //N3310_WITH_DMA
	}
void n3310LcdClass::TryStartDMATransaction(void)//calling from interrupt
	{
#ifdef N3310_WITH_DMA
	if ((DMA.STATUS & (DMA_CH0PEND_bm | DMA_CH0BUSY_bm)) == 0)
		{
		if (LCDstartDMA)
			{
			DMA.CH0.CTRLA		|= DMA_CH_ENABLE_bm;
			DMA.CH0.TRIGSRC		= DMA_CH_TRIGSRC_USARTE1_DRE_gc;
			LCDstartDMA			= false;
			}
		}
#endif //N3310_WITH_DMA
	}
//#endif // N3310_WITHOUT_DMA
//void n3310LcdClass::RequestHardwareBufferReset(void)
//	{
//	LCDpendingHWBufRST	= true;
//	}
void n3310LcdClass::SetData(void)
	{
	LcdPinDC::SetOutHigh();//data
	}
void n3310LcdClass::SetCommand(void)
	{
	LcdPinDC::SetOutLow();//command
	}
void n3310LcdClass::ResetHardwareBufferPointer(void)
	{
	uint8_t commandPacket[]={0x80, 0x40};
	n3310LcdClass::LcdSendCommandPacket(sizeof(commandPacket), commandPacket);
	n3310LcdClass::SetData();
	}
void n3310LcdClass::DMAActivate(void)
	{
#ifdef N3310_WITH_DMA
	LCD_DMA_Activated	= true;
#endif //N3310_WITH_DMA
	}
void n3310LcdClass::DMADeactivate(void)
	{
#ifdef N3310_WITH_DMA
	LCD_DMA_Activated	= false;
#endif //N3310_WITH_DMA
	}
bool n3310LcdClass::isDMAActivated(void)
	{
#ifdef N3310_WITH_DMA
	//return false;
	return LCD_DMA_Activated;
	//return LCD_DMA_Activated & BackLight.isBacklightONInverted;
#else //WITHOUT DMA
	return false;
#endif //N3310_WITH_DMA
	}
bool n3310LcdClass::isDMANotActivated(void)
	{
	return !(n3310LcdClass::isDMAActivated());
	}
void n3310LcdClass::RequestUpdate(void)
//static void RequestUpdate(uint16_t length, uint8_t* packet)
	{
#ifdef N3310_WITH_DMA
	if (n3310LcdClass::isDMANotActivated())
///	if (RunLevel < RUNLEVEL_INTERRUPTS_ALREADY_ENABLED || PowerManager.isInSleepMode())
		{
#endif //N3310_WITH_DMA
		TODO("IS IT HACK?");
		//TryStartDMATransaction();
		n3310LcdClass::ResetHardwareBufferPointer();
		ActivateDisplay();
		for (uint16_t i=0;i<LCD_CACHE_SIZE;i++)
			{
			SPI_TXData(LcdCache[i]);
			}
		DeactivateDisplay();
                LcdCacheChanged = false;
#ifdef N3310_WITH_DMA
		}
	else
		{
		n3310LcdClass::ResetHardwareBufferPointer();
		LCDstartDMA	= true;
		}
#endif //N3310_WITH_DMA
//#endif
	//uint8_t commandPacket[]={0x80, 0x40};
	//n3310LcdClass::LcdSendCommandPacket(sizeof(commandPacket), commandPacket);
//	LcdPinDC::SetOutHigh();//data
//	for (uint16_t i=0;i<LCD_CACHE_SIZE;i++)
//		{
//		USARTE1.DATA	= LcdCache[i];
//		while (!(USARTE1.STATUS & USART_TXCIF_bm));
//		USARTE1.STATUS |= USART_TXCIF_bm;
//		}
//	if ((DMA.STATUS & (DMA_CH0PEND_bm | DMA_CH0BUSY_bm)) == 0)
//		{
//		DMA.CH0.TRIGSRC		= DMA_CH_TRIGSRC_OFF_gc;
//		DMA.CH0.CTRLA &= ~DMA_CH_ENABLE_bm;
//		}
	//if ((DMA.STATUS & (DMA_CH0PEND_bm | DMA_CH0BUSY_bm)) == 0)
		//{
		//DMA.CH0.TRIGSRC		= DMA_CH_TRIGSRC_OFF_gc;
		//DMA.CH0.CTRLA &= ~DMA_CH_ENABLE_bm;

		//uint8_t commandPacket[]={0x80, 0x40};
		//n3310LcdClass::LcdSendCommandPacket(sizeof(commandPacket), commandPacket);
		//ActivateDisplay();
		//LcdPinDC::SetOutHigh();//data

				

		//DMA.CH0.CTRLA &= ~DMA_CH_ENABLE_bm;
		//DMA.INTFLAGS=0;
		//DMA.CH0.CTRLA	= DMA_CH_RESET_bm;
		//while (DMA.CH0.CTRLA & DMA_CH_RESET_bm);
				
				
		//DMA.CH0.CTRLA |= DMA_CH_ENABLE_bm;
		//DMA.CH0.TRIGSRC		= DMA_CH_TRIGSRC_USARTE1_DRE_gc;
				
				
		//while (DMA.STATUS & (DMA_CH0PEND_bm | DMA_CH0BUSY_bm));
		//DMA.CH0.TRIGSRC		= DMA_CH_TRIGSRC_OFF_gc;
		//DMA.CH0.CTRLA &= ~DMA_CH_ENABLE_bm;
		//DMA.CH0.SRCADDR0 = (uintptr_t)packet;     // Настройка адреса источника на массив massIn
		//DMA.CH0.SRCADDR1 = (uintptr_t)packet>>8;
		//DMA.CH0.SRCADDR2 = 0;
		//DeactivateDisplay();
		//}
	/*
	for (uint16_t i=0;i<length;i++)
		{
		USARTE1.DATA	= packet[i];
		while (!(USARTE1.STATUS & USART_TXCIF_bm));
		USARTE1.STATUS |= USART_TXCIF_bm;
		}
	*/
	//DeactivateDisplay();
	}
//#ifdef N3310_WITH_DMA
void n3310LcdClass::SPI_TXData(uint8_t data)
	{
        LcdSPITXData(data);
	}
/*
#else //WITHOUT DMA
void n3310LcdClass::SPI_TXData(uint8_t data) //SOFTWARE_SPI
	{
	uint8_t i, mask = 128;
	for (i=0;i<8;i++)
		{
		if ((data&mask)!=0)
			{
			LcdPinSDIN::SetOutHigh();
			}
		else
			{
			LcdPinSDIN::SetOutLow();
			}
		//            mask = mask/2;// >>1 ???
		mask = mask>>1;// /2 ???
		LcdPinCLK::SetOutHigh();
		_delay_us(1);
		LcdPinCLK::SetOutLow();
		}
	}

#endif
*/
void n3310LcdClass::LcdSendCommandPacket(uint16_t length, uint8_t* packet)
	{
	n3310LcdClass::ActivateDisplay();
	//LcdPinDC::SetOutLow();
	n3310LcdClass::SetCommand();

	for (uint16_t i=0;i<length;i++)
		{
		n3310LcdClass::SPI_TXData(packet[i]);
		//USARTE1.DATA	= packet[i];
		//while (!(USARTE1.STATUS & USART_TXCIF_bm));
		//USARTE1.STATUS |= USART_TXCIF_bm;
		}
	n3310LcdClass::DeactivateDisplay();
	}

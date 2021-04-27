// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

void Driver_Clock::SelectMaxExternal(void)
	{
	this->select_16x2_MHZExternal();
	}
void Driver_Clock::select_16x2_MHZExternal()
	{
	OSC.XOSCCTRL = OSC_FRQRANGE_12TO16_gc | OSC_XOSCSEL_XTAL_256CLK_gc; // configure the XTAL input
	OSC.CTRL |= OSC_XOSCEN_bm; // start XTAL
	while (!(OSC.STATUS & OSC_XOSCRDY_bm))//; // wait until ready
		{
		/*#ifdef DEBUG_BUILD
		sprintf (lcd_buf, "1: %05d", rand());
		LcdString(1,LCD_LINE_3);
		LcdUpdate();
		#endif*/
		}
	_delay_us(100*16);
	OSC.PLLCTRL = OSC_PLLSRC_XOSC_gc | 0x2; // XTAL->PLL, 2x multiplier
	OSC.CTRL |= OSC_PLLEN_bm; // start PLL
	while (!(OSC.STATUS & OSC_PLLRDY_bm))//; // wait until ready
		{
		/*#ifdef DEBUG_BUILD
		sprintf (lcd_buf, "2: %05d", rand());
		LcdString(1,LCD_LINE_3);
		LcdUpdate();
		#endif*/
		}
	_delay_us(100*16);
	CCP = CCP_IOREG_gc; // allow changing CLK.CTRL
	//_delay_ms(100/16);//нужна задержка. Сколько - хз =)
		/*#ifdef DEBUG_BUILD
		sprintf (lcd_buf, "3: %05d", rand());
		LcdString(1,LCD_LINE_3);
		LcdUpdate();
		#endif*/
	CLK.CTRL = CLK_SCLKSEL_PLL_gc; // use PLL output as system clock
	//_delay_ms(100/16);
	
		/*#ifdef DEBUG_BUILD
		sprintf (lcd_buf, "4: %05d", rand());
		LcdString(1,LCD_LINE_3);
		LcdUpdate();
		#endif*/
	this->FREQUENCY_MHZ	= 32;
	}
void Driver_Clock::init_32MHZ_oscillator()
	{
	// enable 32Mhz internal oscillator
	OSC.CTRL |= OSC_RC32MEN_bm;
	// wait for it to be stable
	while (!(OSC.STATUS & OSC_RC32MRDY_bm));
	// tell the processor we want to change a protected register
	CCP=CCP_IOREG_gc;
	// and start using the 32Mhz oscillator
	CLK.CTRL=CLK_SCLKSEL_RC32M_gc;
	// disable the default 2Mhz oscillator
	OSC.CTRL&=(~OSC_RC2MEN_bm);
	// enable 32kHz calibrated internal oscillator
	OSC.CTRL|= OSC_RC32KEN_bm;
	while (!(OSC.STATUS & OSC_RC32KRDY_bm));
	// set bit to 0 to indicate we use the internal 32kHz
	// callibrated oscillator as auto-calibration source
	// for our 32Mhz oscillator
	//OSC.DFLLCTRL = OSC_RC32MCREF_RC32K_gc; //Table 7-8. 32MHz oscillator reference selection.: 00 => RC32K => 32.768kHz internal oscillator
	// enable auto-calibration for the 32Mhz oscillator
	DFLLRC32M.CTRL |= DFLL_ENABLE_bm;
	this->FREQUENCY_MHZ	= 16;
	}
Driver_Clock::Driver_Clock (void)
	{
	this->FREQUENCY_MHZ	= 32;
	}

// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef FM_DISABLED
void fm_search (void)
	{
	uint8_t fmReadData[5];
	uint8_t ADCLevel;
	
	return;
	
//	fmInitData[1]	= FMvar;
	twi_write_fm(fm,fmInitData);
	twi_read_fm(fm,fmReadData);
	ADCLevel	= ((fmReadData[3]&0b11110000) >> 4);

	if (ADCLevel > TEA5767_ADC_THREASHOD && (PDASettings.isParameterSet(ConfigClass::RADIO_ON)))
		{
		cbi(fmInitData[0],TEA5767_WRITEBYTE1_BIT_MUTE);
//		cbi(fmInitData[0],TEA5767_WRITEBYTE1_BIT_SEARCH_MODE);
		}
	else
		{
		sbi(fmInitData[0],TEA5767_WRITEBYTE1_BIT_MUTE);
		}
	}
void fm_mute(void)
	{
	uint8_t fmReadData[5];
	twi_read_fm(fm,fmReadData);
	sbi(fmInitData[0],TEA5767_WRITEBYTE1_BIT_MUTE);
	twi_write_fm(fm,fmInitData);
	}

#endif
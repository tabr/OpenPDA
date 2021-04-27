#ifndef FM_CLASS_H
#define FM_CLASS_H
//TWI on XMEGA [Solved] -> http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&t=106223&view=next
#define TWI_BAUDRATE		400000
//#define TWI_BAUDRATE		100000
#define TWI_BAUD(F_SYS, F_TWI) ((F_SYS / (2 * F_TWI)) - 5)
#define TWI_BAUDSETTING TWI_BAUD(F_CPU, TWI_BAUDRATE)

/******************************************************************/

//TWI_t * fm = &TWIE;
TWI_t * fm = &TWIC;

#define TEA5767_WRITEBYTE1_BIT_MUTE				7
#define TEA5767_WRITEBYTE1_BIT_SEARCH_MODE		6

#define TEA5767_WRITEBYTE3_BIT7_SUD				7
#define TEA5767_WRITEBYTE3_BIT6_SSL1			6
#define TEA5767_WRITEBYTE3_BIT5_SSL0			5
#define TEA5767_WRITEBYTE3_BIT4_HLSI			4
#define TEA5767_WRITEBYTE3_BIT3_MS				3
#define TEA5767_WRITEBYTE3_BIT2_MR				2
#define TEA5767_WRITEBYTE3_BIT1_ML				1
#define TEA5767_WRITEBYTE3_BIT0_SWP1			0

#define TEA5767_WRITEBYTE4_BIT7_SWP2			7
#define TEA5767_WRITEBYTE4_BIT6_STBY			6
#define TEA5767_WRITEBYTE4_BIT5_BL				5
#define TEA5767_WRITEBYTE4_BIT4_XTAL			4
#define TEA5767_WRITEBYTE4_BIT3_SMUTE			3
#define TEA5767_WRITEBYTE4_BIT2_HCC				2
#define TEA5767_WRITEBYTE4_BIT1_SNC				1
#define TEA5767_WRITEBYTE4_BIT0_SI				0

#define TEA5767_ADC_THREASHOD					5




/****************************************************/

void twi_init(TWI_t * twiname){

	
	twiname->MASTER.CTRLB = TWI_MASTER_SMEN_bm;
	twiname->MASTER.BAUD = TWI_BAUDSETTING;
	twiname->MASTER.CTRLA = TWI_MASTER_ENABLE_bm;
	twiname->MASTER.STATUS = TWI_MASTER_BUSSTATE_IDLE_gc;

	

	return;
}









/****************************************************/
void twi_write_fm(TWI_t *twiname, uint8_t *writeData)
{
	//	http://www.electronicsblog.net/arduino-fm-receiver-with-tea5767/
	uint8_t i;
	
	twiname->MASTER.ADDR = 0xC0;  // write to FM
	while(!(twiname->MASTER.STATUS&TWI_MASTER_WIF_bm));
	//twiname->MASTER.DATA = 0x00;       // write word addr
	//while(!(twiname->MASTER.STATUS&TWI_MASTER_WIF_bm));
	for(i=0;i<5;i++)
	{
		twiname->MASTER.DATA =writeData[i];
		while(!(twiname->MASTER.STATUS&TWI_MASTER_WIF_bm));
	}


	return;
}

void twi_read_fm(TWI_t *twiname, uint8_t *readData)
	{
	// read from RTC
	uint8_t i;
	uint8_t address = 0xC0;

	address |= 0x01;
	twiname->MASTER.ADDR = 0xC0;
	while(!(twiname->MASTER.STATUS&TWI_MASTER_WIF_bm));
//	twiname->MASTER.DATA = 0x00;       // write word addrpointer first
	twiname->MASTER.ADDR = address;    // send read command
	for(i=0;i<5;i++)
		{                  // read date and time
		while(!(twiname->MASTER.STATUS&TWI_MASTER_RIF_bm));
		readData[i] = twiname->MASTER.DATA;
		}


	return;
	}

/*
void twi_write_rtc(TWI_t *twiname, uint8_t *writeData)
	{

	uint8_t i;
	
	twiname->MASTER.ADDR = RTC_SLAVE_ADDRESS;  // write to RTC
	while(!(twiname->MASTER.STATUS&TWI_MASTER_WIF_bm));
	twiname->MASTER.DATA = 0x00;       // write word addr
	while(!(twiname->MASTER.STATUS&TWI_MASTER_WIF_bm));
	for(i=0;i<7;i++)
		{                  // write date and time
		twiname->MASTER.DATA =writeData[i];
		while(!(twiname->MASTER.STATUS&TWI_MASTER_WIF_bm));
		}


	return;
	}


void twi_read_rtc(TWI_t *twiname, uint8_t *readData)
	{
	// read from RTC
	uint8_t i;
	uint8_t address = RTC_SLAVE_ADDRESS;

	address |= 0x01;
	twiname->MASTER.ADDR = RTC_SLAVE_ADDRESS;
	while(!(twiname->MASTER.STATUS&TWI_MASTER_WIF_bm));
	twiname->MASTER.DATA = 0x00;       // write word addrpointer first
	twiname->MASTER.ADDR = address;    // send read command
	for(i=0;i<7;i++)
		{                  // read date and time
		while(!(twiname->MASTER.STATUS&TWI_MASTER_RIF_bm));
		readData[i] = twiname->MASTER.DATA;
		}


	return;
	}
*/
/****************************************************/
//byte FMvar							= 200;
uint8_t fmInitData[5]=
	{
//0,
	//¿’“”Õ√!!! +0.5 Ã√ˆ
	1<<TEA5767_WRITEBYTE1_BIT_MUTE | //1<<TEA5767_WRITEBYTE1_BIT_SEARCH_MODE |
//	41, 214,//212 //87.5
//	51, 94, //107.5
	50, 209, //’ËÚ ‘Ã 106.4
	1<<TEA5767_WRITEBYTE3_BIT3_MS | 1<<TEA5767_WRITEBYTE3_BIT2_MR ,//| 1<<TEA5767_WRITEBYTE3_BIT7_SUD | 1<<TEA5767_WRITEBYTE3_BIT5_SSL0 | 1<<TEA5767_WRITEBYTE3_BIT6_SSL1,
	1<<TEA5767_WRITEBYTE4_BIT4_XTAL | 1<<TEA5767_WRITEBYTE4_BIT3_SMUTE | 1<<TEA5767_WRITEBYTE4_BIT2_HCC | 1<<TEA5767_WRITEBYTE4_BIT0_SI,
	0x00
	};


/*
#define TEA5767_FREQ				87.5
#define TEA5767_FREQ_B				4*(TEA5767_FREQ*1000000+225000)/32768 //calculating PLL word
#define TEA5767_FREQ_H				TEA5767_FREQ_B>>8
#define TEA5767_FREQ_L				TEA5767_FREQ_B&0XFF;
*/
void fm_search (void);
void fm_mute (void);
#endif
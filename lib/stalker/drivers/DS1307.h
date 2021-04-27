//TWI on XMEGA [Solved] -> http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&t=106223&view=next
#define CPU_SPEED 32000000
#define TWI_BAUDRATE    400000
//#define TWI_BAUDRATE    100000
#define TWI_BAUD(F_SYS, F_TWI) ((F_SYS / (2 * F_TWI)) - 5)
#define TWI_BAUDSETTING TWI_BAUD(CPU_SPEED, TWI_BAUDRATE)

#define RTC_SLAVE_ADDRESS 0xD0; // already shifted !!!!

#define DS1307_ADDRESS_SECONDS		0//0-59[10|1]
#define DS1307_ADDRESS_MINUTES		1//0-59[10|1]
#define DS1307_ADDRESS_HOURS		2//0-12+1/0-24[10|1]
#define DS1307_ADDRESS_DAYOFWEEK	3//1-7
#define DS1307_ADDRESS_DATE			4//1-28(29)30-31[10|1]
#define DS1307_ADDRESS_MONTH		5//01-12[10|1]
#define DS1307_ADDRESS_YEAR			6//00-99[10|1]
#define DS1307_ADDRESS_CONTROL		7//OUT,0,0,SQWE,0,0,RS1,RS2
void twi_write_rtc(TWI_t *twiname, uint8_t *writeData);
void twi_read_rtc(TWI_t *twiname, uint8_t *readData);
/******************************************************************/

TWI_t * rtc = &TWIE;

//uint8_t twitest[7]={40, 41, (22), 0x08, 0x25, 0x45, 0x65}; // only some test bytes

void rtcSetDateTime(TWI_t * twiname,uint8_t Y,uint8_t M,uint8_t D,uint8_t H,uint8_t I,uint8_t S)
	{
//	H	|= (1<<6);//24קאסמגמי פמנלאע
	uint8_t sendData[8];
	uint8_t tmp;
	tmp									= S%10;//לכאהרטי נאחנÿה
	sendData[DS1307_ADDRESS_SECONDS]	= ((S-tmp)<<4)/10 | (tmp);
	tmp									= I%10;//לכאהרטי נאחנÿה
	sendData[DS1307_ADDRESS_MINUTES]	= ((I-tmp)<<4)/10 | (tmp);
	tmp									= H%10;//לכאהרטי נאחנÿה
	sendData[DS1307_ADDRESS_HOURS]		= ((H-tmp)<<4)/10 | (tmp) | (0<<6);//24קאסמגמי פמנלאע
	sendData[DS1307_ADDRESS_DAYOFWEEK]	= 0;
	tmp									= D%10;//לכאהרטי נאחנÿה
	sendData[DS1307_ADDRESS_DATE]		= ((D-tmp)<<4)/10 | (tmp);
	tmp									= M%10;//לכאהרטי נאחנÿה
	sendData[DS1307_ADDRESS_MONTH]		= ((M-tmp)<<4)/10 | (tmp);
	tmp									= Y%10;//לכאהרטי נאחנÿה
	sendData[DS1307_ADDRESS_YEAR]		= ((Y-tmp)<<4)/10 | (tmp);
	sendData[DS1307_ADDRESS_CONTROL]	= 0;
	twi_write_rtc(twiname, sendData);
	}
void rtcGetDateTime(TWI_t * twiname, uint8_t *readData)
	{
	uint8_t tmp;
	twi_read_rtc(twiname, readData);
	tmp									= readData[DS1307_ADDRESS_SECONDS] & 0b11110000;
	tmp									= tmp >> 4;
	readData[DS1307_ADDRESS_SECONDS]	&= 0b00001111;
	readData[DS1307_ADDRESS_SECONDS]	+= tmp*10;

	tmp									= readData[DS1307_ADDRESS_MINUTES] & 0b11110000;
	tmp									= tmp >> 4;
	readData[DS1307_ADDRESS_MINUTES]	&= 0b00001111;
	readData[DS1307_ADDRESS_MINUTES]	+= tmp*10;
	
	tmp									= readData[DS1307_ADDRESS_HOURS] & 0b00110000;
	tmp									= tmp >> 4;
	readData[DS1307_ADDRESS_HOURS]		&= 0b00001111;
	readData[DS1307_ADDRESS_HOURS]		+= tmp*10;

	tmp									= readData[DS1307_ADDRESS_DATE] & 0b00110000;
	tmp									= tmp >> 4;
	readData[DS1307_ADDRESS_DATE]		&= 0b00001111;
	readData[DS1307_ADDRESS_DATE]		+= tmp*10;
	
	tmp									= readData[DS1307_ADDRESS_MONTH] & 0b00110000;
	tmp									= tmp >> 4;
	readData[DS1307_ADDRESS_MONTH]		&= 0b00001111;
	readData[DS1307_ADDRESS_MONTH]		+= tmp*10;
	
	tmp									= readData[DS1307_ADDRESS_YEAR] & 0b00110000;
	tmp									= tmp >> 4;
	readData[DS1307_ADDRESS_YEAR]		&= 0b00001111;
	readData[DS1307_ADDRESS_YEAR]		+= tmp*10;
	
	}


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


void twi_write_rtc(TWI_t *twiname, uint8_t *writeData){

	uint8_t i;
	
	twiname->MASTER.ADDR = RTC_SLAVE_ADDRESS;  // write to RTC
	while(!(twiname->MASTER.STATUS&TWI_MASTER_WIF_bm));
	twiname->MASTER.DATA = 0x00;       // write word addr
	while(!(twiname->MASTER.STATUS&TWI_MASTER_WIF_bm));
	for(i=0;i<7;i++){                  // write date and time
		twiname->MASTER.DATA =writeData[i];
		while(!(twiname->MASTER.STATUS&TWI_MASTER_WIF_bm));
	}


	return;
}

/****************************************************/

void twi_read_rtc(TWI_t *twiname, uint8_t *readData){
	// read from RTC
	uint8_t i;
	uint8_t address = RTC_SLAVE_ADDRESS;

	address |= 0x01;
	twiname->MASTER.ADDR = RTC_SLAVE_ADDRESS;
	while(!(twiname->MASTER.STATUS&TWI_MASTER_WIF_bm));
	twiname->MASTER.DATA = 0x00;       // write word addrpointer first
	twiname->MASTER.ADDR = address;    // send read command
	for(i=0;i<7;i++){                  // read date and time
		while(!(twiname->MASTER.STATUS&TWI_MASTER_RIF_bm));
		readData[i] = twiname->MASTER.DATA;
	}


	return;
}

/****************************************************/

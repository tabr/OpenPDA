// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
ВНИМАНИЕ!!! Чтобы перезаписать это блядство, нужно сначала СТЕРЕТЬ сектор/булк!!!
*/

#define M25P05_SPI									SPIC

#define M25P05_CLK_PORT								PORTC_OUT
#define M25P05_CLK_DDR								PORTC_DIR
#define M25P05_CLK_PIN								PIN7_bp

#define M25P05_MISO_PORT							PORTC_OUT
#define M25P05_MISO_DDR								PORTC_DIR
#define M25P05_MISO_PIN								PIN6_bp
#define M25P05_MISO_CTRL							PORTC.PIN6CTRL

#define M25P05_MOSI_PORT							PORTC_OUT
#define M25P05_MOSI_DDR								PORTC_DIR
#define M25P05_MOSI_PIN								PIN5_bp

#define M25P05_SS_PORT								PORTC_OUT
#define M25P05_SS_DDR								PORTC_DIR
//#define M25P05_SS_IN								PORTC_IN
#define M25P05_SS_PIN								PIN4_bp

//#define M25P05_LED_PORT								PORTH_OUT
//#define M25P05_LED_DDR								PORTH_DIR
//#define M25P05_LED_PIN								PIN0_bp


#define M25P05_ACTIVATE								cbi(M25P05_SS_PORT, M25P05_SS_PIN);
#define M25P05_DEACTIVATE							sbi(M25P05_SS_PORT, M25P05_SS_PIN);

//#define ARTEFACT01_PRESENTS

#define STATUS_REGISTER_BIT00_BUSY					0 //ERASE or WRITE in progress
#define STATUS_REGISTER_BIT01_WEL					1 //Write enable latch
#define STATUS_REGISTER_BIT02_BP0					2 //Block protect bits (non-volatile)
#define STATUS_REGISTER_BIT03_BP1					3 //Block protect bits (non-volatile)
#define STATUS_REGISTER_BIT04_BP2					4 //Block protect bits (non-volatile)
#define STATUS_REGISTER_BIT05_TB					5 //TOP/BOTTOM WRITE protect (non-volatile)
#define STATUS_REGISTER_BIT06_R						6 //RESERVED
#define STATUS_REGISTER_BIT07_SRP					7 //STATUS REGISTER PROTECT (non-volatile)



void M25P05_Init()
	{
	cbi(M25P05_MISO_DDR,	M25P05_MISO_PIN);
	//cbi(M25P05_MISO_PORT,	M25P05_MISO_PIN);

	sbi(M25P05_SS_DDR,		M25P05_SS_PIN);
	sbi(M25P05_SS_PORT,		M25P05_SS_PIN);

	sbi(M25P05_MOSI_DDR,	M25P05_MOSI_PIN);

	sbi(M25P05_CLK_DDR,		M25P05_CLK_PIN);
	cbi(M25P05_CLK_PORT,	M25P05_CLK_PIN);
	//PORTE.REMAP	= 1<<5;//spi
//	sbi(M25P05_LED_DDR,		M25P05_LED_PIN);//светодиод
	//PORTE.DIRSET
	//					  [double CLK]	[enable][DORD] [master][transfer mode][clk prescaller]
	M25P05_SPI.CTRL		= 1<<7			| 1<<6	| 0<<5 | 1<<4 | (0<<3 | 0<<2) | (0<<1 | 0<<0);
	//	M25P05_SPI.CTRL	= 0<<7			| 1<<6	| 0<<5 | 1<<4 | (0<<3 | 0<<2) | (1<<1 | 1<<0);
	M25P05_SPI.INTCTRL	= SPI_INTLVL_OFF_gc ; // no interrupt
	M25P05_MISO_CTRL	= PORT_OPC_PULLDOWN_gc;//подтяжка к низу
	}
uint8_t M25P05_SPI_send(uint8_t data)
	{
	M25P05_SPI.DATA	= data;
	while (!(M25P05_SPI.STATUS & SPI_IF_bm))
	{
		//		++tmp;
		//		PORTQ_OUTTGL	= (1<<PIN0_bp);
	}        //Wait Interrupt
	return M25P05_SPI.DATA;
	}
uint8_t M25P05_Read_Status_Register()
	{
	uint8_t tmp;
	M25P05_ACTIVATE;
	M25P05_SPI_send(M25P05_INSTRUCTION_READ_STATUS_REGISTER);
	tmp	= M25P05_SPI_send(0);
	M25P05_DEACTIVATE;
	return tmp;
	}
void M25P05_Write_Status_Register(uint8_t data)
	{
	M25P05_ACTIVATE;
	M25P05_SPI_send(M25P05_INSTRUCTION_WRITE_STATUS_REGISTER);
	M25P05_SPI_send(data);
	M25P05_DEACTIVATE;
	}
uint8_t M25P05_Read_DataByte(uint8_t H,uint8_t M, uint8_t L)
	{
	uint8_t tmp;
	M25P05_ACTIVATE;
	M25P05_SPI_send(M25P05_INSTRUCTION_READ_DATA_BYTES);
	M25P05_SPI_send(H);
	M25P05_SPI_send(M);
	M25P05_SPI_send(L);
	tmp	= M25P05_SPI_send(0);
	M25P05_DEACTIVATE;
	return tmp;
	}
void M25P05_Read(uint8_t H,uint8_t M, uint8_t L, uint8_t size, uint8_t *data)
	{
	M25P05_ACTIVATE;
	M25P05_SPI_send(M25P05_INSTRUCTION_READ_DATA_BYTES);
	M25P05_SPI_send(H);
	M25P05_SPI_send(M);
	M25P05_SPI_send(L);
	for (uint8_t i=0;i<size;i++)
		{
		data[i]	= M25P05_SPI_send(0);
		//_delay_ms(10);
		}
	M25P05_DEACTIVATE;
	}
uint8_t M25P05_Read_RDID()//не робить
	{
	uint8_t tmp;
	M25P05_ACTIVATE;
	M25P05_SPI_send(M25P05_INSTRUCTION_READ_IDENTIFICATION);
	tmp	 = M25P05_SPI_send(0);
	tmp	 = M25P05_SPI_send(0);
	tmp	 = M25P05_SPI_send(0);
	M25P05_DEACTIVATE;
	return tmp;
	}
void M25P05_Write_disable()
	{
	M25P05_ACTIVATE;
	M25P05_SPI_send(M25P05_INSTRUCTION_WRITE_DISABLE);
	M25P05_DEACTIVATE;
	}
void M25P05_Write_enable()
	{
	M25P05_ACTIVATE;
	M25P05_SPI_send(M25P05_INSTRUCTION_WRITE_ENABLE);
	M25P05_DEACTIVATE;
	}
void M25P05_BulkErase()
	{
	M25P05_ACTIVATE;
	M25P05_SPI_send(M25P05_INSTRUCTION_BULK_ERASE);
	M25P05_DEACTIVATE;
	}

void M25P05_SectorErase(bool sector)
	{
	//The sector erase (SE) instruction is entered by driving Chip Select (S) Low, followed by the
	//instruction code, and three address bytes on Serial Data input (D).
	M25P05_ACTIVATE;
	M25P05_SPI_send(M25P05_INSTRUCTION_SECTOR_ERASE);
	M25P05_SPI_send(sector);
	M25P05_SPI_send(0);
	M25P05_SPI_send(0);
	M25P05_DEACTIVATE;
	}
void M25P05_ByteProgram(const uint8_t H, const uint8_t M, const uint8_t L, const uint8_t byte)
	{
		//uint8_t i;
//	M25P05_Write_enable();
	M25P05_ACTIVATE;
//	M25P05_SPI_send(M25P05_INSTRUCTION_WRITE_ENABLE);
	M25P05_SPI_send(M25P05_INSTRUCTION_PAGE_PROGRAM);
//	delay_ms(5);
	M25P05_SPI_send(H);
//	delay_ms(5);
	M25P05_SPI_send(M);
//	delay_ms(5);
	M25P05_SPI_send(L);
//	delay_ms(5);
	M25P05_SPI_send(byte);
//	for (i=0;i<255;i++)
//		M25P05_SPI_send(2);
//	M25P05_SPI_send(0);
//	M25P05_SPI_send(1);
//	M25P05_SPI_send(2);
//	M25P05_SPI_send(3);
//	M25P05_SPI_send(5);
//	delay_ms(5);
//	M25P05_SPI_send(byte);
	M25P05_DEACTIVATE;
	}
void M25P05_PageProgram(uint8_t H,uint8_t M, uint8_t L, uint8_t *data, uint8_t size)
	{
		//uint8_t i;
//	M25P05_Write_enable();
	M25P05_ACTIVATE;
	M25P05_SPI_send(M25P05_INSTRUCTION_PAGE_PROGRAM);
	M25P05_SPI_send(H);
	M25P05_SPI_send(M);
	M25P05_SPI_send(L);
	for (uint8_t i=0;i<size;i++)
		{
		M25P05_SPI_send(data[i]);
		}
	M25P05_DEACTIVATE;
	}
void M25P05_DeepPowerDown()
	{
	M25P05_ACTIVATE;
	M25P05_SPI_send(M25P05_INSTRUCTION_DEEP_POWER_DOWN);
	M25P05_DEACTIVATE;
	}
uint8_t M25P05_RES()
	{
	uint8_t tmp;
	M25P05_ACTIVATE;
	M25P05_SPI_send(M25P05_INSTRUCTION_RELEASE_FROM_DPD);
	M25P05_SPI_send(0);
	M25P05_SPI_send(0);
	M25P05_SPI_send(0);
	tmp	= M25P05_SPI_send(0);
	M25P05_DEACTIVATE;
	return tmp;
	}

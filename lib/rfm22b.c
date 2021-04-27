// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef RFM22B_C
#define RFM22B_C
/************************************************************************
*********************** EWS_RFM22B_CHAT_EXAMPLE *************************
*************************************************************************

	DESCRIPTION:  This program acts as both transmitter and receiver
		for the RFM22B, allowing users to enter a character message 
		via a UART terminal program (such as Hyperterminal), which is sent 
		wirelessly to another RFM22B/ATMEGA pair.  This program is a 
		simple, basic demonstration of use of the RFM22B wireless 
		transceiver module.  
		This program is adapted from example RFM22B applications on the 
		manufacturer's website (www.hoperf.com) and Sparkfun Electronics' 
		website (www.sparkfun.com).
		
	SPECIFICATIONS:
	- Radio: RFM22B - 433MHz
	- Antenna: Wire (17.1cm)
	- Hardware: ATMEL ATMEGA328P, 3.3V
	- IDE: AVRStudio 4.19 (build 730) -or- WINAVR
	- Programmer: AVRISP MKII -or- optiboot (arduino) bootloader
	- Data Rate: 9600 baud
	- Hardware connections:
	
	RFM22B		|  ATMEGA328P  	| Other Hardware
	------------------------------------------------------------
		GND		|	 GND		|
		3.3V	|	 3.3V		|
		GPIO0	|	 NC			|
		GPIO1	|	 NC			|
		GPIO2	|	 NC			|
		
		NIRQ	|	 PC0		|
//		TXANT	|	 PC1		|
//		RXANT	|	 PC2		|
		SDN		|	 PC3		|
		
		NSEL	|	 PB2		|
		SCK		|	 PB5		|
		SDI		|	 PB3		|
		SDO		|	 PB4		|
		
				| 	 PB0		|	Green LED circuit
				|	 PB1		|	Red LED circuit
		
By: Embedded Wireless Solutions LLC, 2012 (http://www.goEWS.com)
Modified by: tabr, 2012-2013
***********************************************************************/
/*
#define RFM22B_GPIO0_PORT       PORTD
#define RFM22B_GPIO0_PIN        PIND
#define RFM22B_GPIO0_BIT        2
#define RFM22B_NIRQ_PORT        PORTB
#define RFM22B_NIRQ_PIN         PINB
#define RFM22B_NIRQ_DDR         DDRB
#define RFM22B_NIRQ_BIT         1
//#define TXANT                 3		// PC3	(Transmit enable pin)
//#define RXANT                 2		// PC2	(Receive enable pin)
#define RFM22B_SDN_PORT         PORTB
#define RFM22B_SDN_PIN          PINB
#define RFM22B_SDN_DDR          DDRB
#define RFM22B_SDN_BIT          0

#define RFM22B_SPI_PORT         PORTB
#define RFM22B_SPI_PIN          PINB
#define RFM22B_SPI_DDR          DDRB
#define RFM22B_SCK              5 		// PB5	(SPI clock)
#define RFM22B_SDI              3 		// PB3	(MOSI)
#define RFM22B_SDO              4 		// PB4	(MISO)
#define RFM22B_NSEL             2 		// PB2	(Chip select)
*/



//===============DEFINES ================
//#define RFM22B_CHOOSE_TRANSMITTER   1
//#define RFM22B_CHOOSE_RECEIVER      1


#define NIRQ_LOW                    ((RFM22B_NIRQ_PIN & (1<<RFM22B_NIRQ_BIT)) == 0)
#define NIRQ_HI                     ((RFM22B_NIRQ_PIN & (1<<RFM22B_NIRQ_BIT)) != 0)
#define RFM22B_POWER_ON             cbi(RFM22B_SDN_PORT,RFM22B_SDN_BIT)
#define RFM22B_POWER_OFF            sbi(RFM22B_SDN_PORT,RFM22B_SDN_BIT)


//#define PKTSIZE 64	// size of packet to be transmitted (max 64 bytes for this example program - RFM22B is capable of 255 bytes max)
#define PKTSIZE         12  	// size of packet to be transmitted (max 64 bytes for this example program - RFM22B is capable of 255 bytes max)
#define PACKET_SIZE     PKTSIZE
//======================================

//=======FUNCTION DECLARATIONS==========
void RFM22B_setTransmitPacketSize(unsigned char size);
void RFM22B_SPI_TXData(unsigned char data);
void RFM22B_RegisterWrite(unsigned char address, unsigned char data);
void RFM22B_init(void);
void RFM22B_ioinit(void);
#ifdef RFM22B_CHOOSE_TRANSMITTER
void RFM22B_txMode();
#endif
#ifdef RFM22B_CHOOSE_RECEIVER
void RFM22B_rxMode();
#endif
void RFM22B_readyMode();
void RFM22B_reset(void);
void RFM22B_setTransmitPacketSize(unsigned char size);
unsigned char RFM22B_RegisterRead(unsigned char address);
unsigned char RFM22B_SPI_RXData(void);
unsigned char RFM22B_batteryVoltageRaw();
unsigned char RFM22B_getRSSI();
unsigned char RFM22B_getTXPower();
unsigned char RFM22B_getStatus();
unsigned char RFM22B_getVersion();
//======================================

//============Global Variables==========
#ifdef RFM22B_CHOOSE_TRANSMITTER
//unsigned char volatile TX_BUF[PKTSIZE]; 	// Transmit buffer
unsigned char TX_BUF[PKTSIZE]; 	// Transmit buffer
void RFM22B_clearTXBuf(void)
    {   
    unsigned char i;
    for (i=0;i<PKTSIZE;i++)
        {
        TX_BUF[i]   = 0;
        }
    }
#endif
#ifdef RFM22B_CHOOSE_RECEIVER
//unsigned char volatile RX_BUF[PKTSIZE];		// Receive buffer
unsigned char RX_BUF[PKTSIZE];		// Receive buffer
void RFM22B_clearRXBuf(void)
    {   
    unsigned char i;
    for (i=0;i<PKTSIZE;i++)
        {
        RX_BUF[i]   = 0;
        }
    }
#endif


/************************************************************************
	FUNCTION: RFM22B_init() 
	DESCRIPTION:  This function initializes the RFM22B for use, by 
		setting all applicable internal register values.
*************************************************************************/
void RFM22B_init(void)
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
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_33_HEADER_CONTROL_2,                       0x0e);
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_34_PREAMBLE_LENGTH,                        0x06);
	RFM22B_RegisterWrite(RFM22B_REGISTER_35_PREAMBLE_DETECTION_CONTROL,             0x32);

	RFM22B_RegisterWrite(RFM22B_REGISTER_36_SYNC_WORD_3,                            0x59);		// synchronize word
	RFM22B_RegisterWrite(RFM22B_REGISTER_37_SYNC_WORD_2,                            0xa6);
	RFM22B_RegisterWrite(RFM22B_REGISTER_38_SYNC_WORD_1,                            0xa6);
	RFM22B_RegisterWrite(RFM22B_REGISTER_39_SYNC_WORD_0,                            0x65);

	RFM22B_RegisterWrite(RFM22B_REGISTER_3A_TRANSMIT_HEADER_3,                      0x00);		// set tx header 3
	RFM22B_RegisterWrite(RFM22B_REGISTER_3B_TRANSMIT_HEADER_2,                      0x00);		// set tx header 2
	RFM22B_RegisterWrite(RFM22B_REGISTER_3C_TRANSMIT_HEADER_1,                      0x00);		// set tx header 1
	RFM22B_RegisterWrite(RFM22B_REGISTER_3D_TRANSMIT_HEADER_0,                      0x00);		// set tx header 0
	//RFM22B_RegisterWrite(0x3E, 17);		// set packet length to 17 bytes (max size: 255 bytes)
//	RFM22B_setTransmitPacketSize(PKTSIZE);	// set packet length to PKTSIZE bytes (max size: 255 bytes)
    RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 PKTSIZE);//+1 - переменна€ длина пакета
//    RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 PKTSIZE+1);//+1 - переменна€ длина пакета
	
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
	
#ifdef TX_POWER
	RFM22B_RegisterWrite(RFM22B_REGISTER_6D_TX_POWER,                               (RFM22B_LNA_SW | (TX_POWER & 7)));
#else
	RFM22B_RegisterWrite(RFM22B_REGISTER_6D_TX_POWER,                               (RFM22B_LNA_SW | 7));		// Tx power to max
#endif	
	
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
void RFM22B_init_backup(void)
{
	RFM22B_RegisterWrite(RFM22B_REGISTER_1C_IF_FILTER_BANDWIDTH,                    0x95);
	RFM22B_RegisterWrite(RFM22B_REGISTER_1D_AFC_LOOP_GEARSHIFT_OVERRIDE,            0x40);
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_20_CLOCK_RECOVERY_OVERSAMPLING_RATIO,      0x6c);		// clock recovery
	RFM22B_RegisterWrite(RFM22B_REGISTER_21_CLOCK_RECOVERY_OFFSET_2,                0x01);		// clock recovery
	RFM22B_RegisterWrite(RFM22B_REGISTER_22_CLOCK_RECOVERY_OFFSET_1,                0x2f);		// clock recovery
	RFM22B_RegisterWrite(RFM22B_REGISTER_23_CLOCK_RECOVERY_OFFSET_0,                0x68);		// clock recovery
	RFM22B_RegisterWrite(RFM22B_REGISTER_24_CLOCK_RECOVERY_TIMING_LOOP_GAIN_1,      0x02);		// clock recovery timing
	RFM22B_RegisterWrite(RFM22B_REGISTER_25_CLOCK_RECOVERY_TIMING_LOOP_GAIN_0,      0xa4);		// clock recovery timing
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_2A_AFC_LIMITER,                            0x3c);
	RFM22B_RegisterWrite(RFM22B_REGISTER_2C_OOK_COUNTER_VALUE_1,                    0x28);
	RFM22B_RegisterWrite(RFM22B_REGISTER_2D_OOK_COUNTER_VALUE_2,                    0x16);
	RFM22B_RegisterWrite(RFM22B_REGISTER_2E_SLICER_PEAK_HOLD,                       0x29);
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_30_DATA_ACCESS_CONTROL,                    0xa8);
	RFM22B_RegisterWrite(RFM22B_REGISTER_32_HEADER_CONTROL_1,                       0x00);
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_33_HEADER_CONTROL_2,                       0x0e);
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_34_PREAMBLE_LENGTH,                        0x06);
	RFM22B_RegisterWrite(RFM22B_REGISTER_35_PREAMBLE_DETECTION_CONTROL,             0x32);

	RFM22B_RegisterWrite(RFM22B_REGISTER_36_SYNC_WORD_3,                            0x59);		// synchronize word
	RFM22B_RegisterWrite(RFM22B_REGISTER_37_SYNC_WORD_2,                            0xa6);
	RFM22B_RegisterWrite(RFM22B_REGISTER_38_SYNC_WORD_1,                            0xa6);
	RFM22B_RegisterWrite(RFM22B_REGISTER_39_SYNC_WORD_0,                            0x65);

	RFM22B_RegisterWrite(RFM22B_REGISTER_3A_TRANSMIT_HEADER_3,                      0x00);		// set tx header 3
	RFM22B_RegisterWrite(RFM22B_REGISTER_3B_TRANSMIT_HEADER_2,                      0x00);		// set tx header 2
	RFM22B_RegisterWrite(RFM22B_REGISTER_3C_TRANSMIT_HEADER_1,                      0x00);		// set tx header 1
	RFM22B_RegisterWrite(RFM22B_REGISTER_3D_TRANSMIT_HEADER_0,                      0x00);		// set tx header 0
	//RFM22B_RegisterWrite(0x3E, 17);		// set packet length to 17 bytes (max size: 255 bytes)
//	RFM22B_setTransmitPacketSize(PKTSIZE);	// set packet length to PKTSIZE bytes (max size: 255 bytes)
    RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 PKTSIZE+6);
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_3F_CHECK_HEADER_3,                         0x00);		// set rx header
	RFM22B_RegisterWrite(RFM22B_REGISTER_40_CHECK_HEADER_2,                         0x00);
	RFM22B_RegisterWrite(RFM22B_REGISTER_41_CHECK_HEADER_1,                         0x00);
	RFM22B_RegisterWrite(RFM22B_REGISTER_42_CHECK_HEADER_0,                         0x00);
	RFM22B_RegisterWrite(RFM22B_REGISTER_43_HEADER_ENABLE_3,                        0xFF);		// check all bits
	RFM22B_RegisterWrite(RFM22B_REGISTER_44_HEADER_ENABLE_2,                        0xFF);		// Check all bits
	RFM22B_RegisterWrite(RFM22B_REGISTER_45_HEADER_ENABLE_1,                        0xFF);		// check all bits
	RFM22B_RegisterWrite(RFM22B_REGISTER_46_HEADER_ENABLE_0,                        0xFF);		// Check all bits




//TX DATA RATE
	RFM22B_RegisterWrite(RFM22B_REGISTER_6E_TX_DATA_RATE_1,                         0x0e);		// TX data rate 1
	RFM22B_RegisterWrite(RFM22B_REGISTER_6F_TX_DATA_RATE_0,                         0x39);		// TX data rate 0
	
#ifdef TX_POWER
	RFM22B_RegisterWrite(RFM22B_REGISTER_6D_TX_POWER,                               (RFM22B_LNA_SW | (TX_POWER & 7)));
#else
	RFM22B_RegisterWrite(RFM22B_REGISTER_6D_TX_POWER,                               (RFM22B_LNA_SW | 7));		// Tx power to max
#endif	
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_70_MODULATION_MODE_CONTROL_1,              0x0c);
	RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x22);
	RFM22B_RegisterWrite(RFM22B_REGISTER_72_FREQUENCY_DEVIATION,                    0x50);		// Frequency deviation setting to 50K=80*625
	
//	RFM22B_RegisterWrite(RFM22B_REGISTER_73_FREQUENCY_OFFSET_1,                     0x00);		// No frequency offset
//	RFM22B_RegisterWrite(RFM22B_REGISTER_74_FREQUENCY_OFFSET_2,                     0x00);		// No frequency offset
    
	RFM22B_RegisterWrite(RFM22B_REGISTER_75_FREQUENCY_BAND_SELECT,                  0x54);		// frequency set to 446MHz
	RFM22B_RegisterWrite(RFM22B_REGISTER_76_NOMINAL_CARRIER_FREQUENCY_1,            0x96);		// frequency set to 446MHz
	RFM22B_RegisterWrite(RFM22B_REGISTER_77_NOMINAL_CARRIER_FREQUENCY_0,            0x00);		// frequency set to 446Mhz
	
	
}



/************************************************************************
	FUNCTION: RFM22B_RegisterWrite() 
	DESCRIPTION:  This function sends a byte to the RFM22B
*************************************************************************/
void RFM22B_RegisterWrite(unsigned char address, unsigned char data)
{
	//write any data byte to any single address
	//adds a 1 to the MSB of the address byte (WRITE mode)
	
	address |= 0x80;

	cbi(RFM22B_SPI_PORT, RFM22B_NSEL);
//	delay_ms(1);
	RFM22B_SPI_TXData(address);
//	delay_ms(1);
	RFM22B_SPI_TXData(data);
//	delay_ms(1);
	sbi(RFM22B_SPI_PORT, RFM22B_NSEL);
}

/************************************************************************
	FUNCTION: read() 
	DESCRIPTION:  This function reads a byte from the RFM22B and returns it
*************************************************************************/
unsigned char RFM22B_RegisterRead(unsigned char address)
{
	//returns the contents of any 1 byte register from any address
	//sets the MSB for every address byte (READ mode)

	unsigned char byte;
	
	address &= 0x7F;

	cbi(RFM22B_SPI_PORT, RFM22B_NSEL);
	RFM22B_SPI_TXData(address);
	byte = RFM22B_SPI_RXData();
	sbi(RFM22B_SPI_PORT, RFM22B_NSEL);

	return byte;
}

/************************************************************************
	FUNCTION: rxdata() 
	DESCRIPTION:  This function receives a byte via SPI communication
		and returns it.
*************************************************************************/
unsigned char RFM22B_SPI_RXData(void)
{
	SPDR = 0x55;
	while((SPSR&0x80) == 0x00);

	return SPDR;
}

/************************************************************************
	FUNCTION: txdata() 
	DESCRIPTION:  This function sends a byte via SPI communication
*************************************************************************/
void RFM22B_SPI_TXData(char data)
{
	SPDR = data;
	while((SPSR&0x80) == 0x00);
}

/************************************************************************
	FUNCTION: ioinit() 
	DESCRIPTION:  This function prepares the ATMEGA for use: 
		1. Initialize on I/O ports
		2. Initialize SPI port
		3. Initialize UART1 port
*************************************************************************/
void RFM22B_ioinit(void)
{
/*
#define NIRQ 4//0		// PC0	(Interrupt pin)
//#define TXANT 3		// PC3	(Transmit enable pin)
//#define RXANT 2		// PC2	(Receive enable pin)
#define SDN 1		// PC1  (Shutdown)
#define SCK 5 		// PB5	(SPI clock)
#define SDI 3 		// PB3	(MOSI)
#define SDO 4 		// PB4	(MISO)
#define NSEL 2 		// PB2	(Chip select)

*/
	// Initialize PORTB & PORTC
    //1 = output, 0 = input
//    DDRB |= (1<<SDN) | (1<<SCK) | (1<<SDI) | (1<<NSEL);
    RFM22B_SDN_DDR     |= (1<<RFM22B_SDN_BIT);
//    RFM22B_NIRQ_PORT   |= (1<<RFM22B_NIRQ_BIT);
//    RFM22B_GPIO0_PORT  |= (1<<RFM22B_GPIO0_BIT);//подт€гивающий резистор
    cbi(RFM22B_GPIO0_PORT,RFM22B_GPIO0_BIT);//вход
    sbi(RFM22B_GPIO0_PORT,RFM22B_GPIO0_BIT);//подт€гивающий резистор

    RFM22B_SPI_DDR     |= (1<<RFM22B_SCK) | (1<<RFM22B_SDI) | (1<<RFM22B_NSEL);//выходы
    cbi(RFM22B_SPI_PORT,RFM22B_SCK);
    cbi(RFM22B_SPI_PORT,RFM22B_SDI);
    cbi(RFM22B_SPI_PORT,RFM22B_NSEL);

    sbi(RFM22B_NIRQ_PORT,   RFM22B_NIRQ_BIT);//подт€гивающий резистор
    cbi(RFM22B_NIRQ_DDR,    RFM22B_NIRQ_BIT);//вход
//    PORTB |= (1<<SD0) | (1<<NIRQ);

//    DDRB = 0b11101111; // MISO (PB4) input, otherwise outputs
//	DDRC = 0b11111110; // NIRQ (PB0) input, otherwise outputs
	
	// Initialize SPI port
//	SPCR = 0b01010011;		// Fosc/128 (83) (64+16+2+1)
//	SPCR = 0b01010011;		// Fosc/128
//	SPSR = 0x01;
//    SPSR=0x01;
//SPCR Ц SPI Control Register
//Bit 7 Ц SPIE: SPI Interrupt Enable
//Bit 6 Ц SPE: SPI Enable
//Bit 5 Ц DORD: Data Order
//Bit 4 Ц MSTR: Master/Slave Select
//Bit 3 Ц CPOL: Clock Polarity
//Bit 2 Ц CPHA: Clock Phase
//Bits 1, 0 Ц SPR1, SPR0: SPI Clock Rate Select 1 and 0
//SPI2X SPR1    SPR0 SCK Frequency
//0     0       0 fosc/4
//0     0       1 fosc/16
//0     1       0 fosc/64
//0     1       1 fosc/128
//1     0       0 fosc/2
//1     0       1 fosc/8
//1     1       0 fosc/32
//1     1       1 fosc/64
//SPCR=0x50;//5mhz
//SPCR=1<<6 | 1<<4;//5mhz
SPCR=1<<SPE | 1<<MSTR;//5mhz
SPSR=0x01;//x2
//SPSR=0;
	
///	// Initialize UART0
//	UCSR0B |= (1 << RXEN0) | (1 << TXEN0); // Turn on the transmission and reception circuitry
//	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01); // Use 8-bit character sizes
//	UBRR0L = (unsigned char)BAUD_PRESCALE; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register
//	UBRR0H = (unsigned char)(BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
//
//	UCSR0B |= (1 << RXCIE0); // Enable the USART Receive Complete interrupt (USART_RXC)

//	cbi(PORTC, TXANT);	// Turn off Tx Antenna select input pin
//	cbi(PORTC, RXANT);	// Turn off Rx Antenna select input pin
}


/************************************************************************
	FUNCTION: RFM22B_reset() 
	DESCRIPTION:  This function performs a hardware reset of the RFM22B 
*************************************************************************/
void RFM22B_reset(void)
{

//	sbi(PORTB,SDN);		// enable RFM22B Shutdown pin (turn RFM22B off)
//	sbi(SDN_PORT,SDN_BIT);		// enable RFM22B Shutdown pin (turn RFM22B off)
    RFM22B_POWER_OFF;
	delay_ms(5);		// wait 5 ms
//	cbi(PORTB,SDN);		// disable shutdown (turn RFM22B back on)
//	cbi(SDN_PORT,SDN_BIT);		// disable shutdown (turn RFM22B back on)
    RFM22B_POWER_ON;
	while(1)
	{
		if(!(RFM22B_NIRQ_PIN & (1<<RFM22B_NIRQ_BIT)))
		{
			delay_ms(25);		//delay some time before re-initialization of the module
			break;
		}	
	}
	RFM22B_RegisterRead(0x03);				// clear interrupts by reading register
	RFM22B_RegisterRead(0x04);				// clear interrupts
	sbi(RFM22B_SPI_PORT, RFM22B_NSEL);		// Disable chip select line
//	cbi(PORTC,TXANT);		// Ensure transmit antenna circuitry is off
//	cbi(PORTC,RXANT);		// Ensure receive antenna circuitry is off
	RFM22B_init();			// Initialize all RFM22 registers
}
/*
void RFM22B_setRSSI()//TODO: ’ј 
    {
//    RFM22B_RSSIValue = RFM22B_RegisterRead(RFM22B_REGISTER_26_RSSI);
    rssi = RFM22B_RegisterRead(RFM22B_REGISTER_26_RSSI);
    }
*/
unsigned char RFM22B_getRSSI()
    {
    //[80-120++]
    return RFM22B_RegisterRead(RFM22B_REGISTER_26_RSSI);
    }
unsigned char RFM22B_getTXPower()
    {
    return RFM22B_RegisterRead(RFM22B_REGISTER_6D_TX_POWER);;
    }
unsigned char RFM22B_getStatus()
    {
    return RFM22B_RegisterRead(RFM22B_REGISTER_02_DEVICE_STATUS);;
    }
unsigned char RFM22B_batteryVoltageRaw()
    {
    return RFM22B_RegisterRead(RFM22B_REGISTER_1B_BATTERY_VOLTAGE_LEVEL);;
    }
unsigned char RFM22B_getVersion()
    {
    return RFM22B_RegisterRead(RFM22B_REGISTER_01_DEVICE_VERSION);;
    }
void RFM22B_readyMode()
    {
    RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, 0x01);	// to ready mode
    }
void RFM22B_setTransmitPacketSize(unsigned char size)
    {
    RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH, size);
    }
#ifdef RFM22B_CHOOSE_RECEIVER
/************************************************************************
	FUNCTION: to_rx_mode()
	DESCRIPTION:  This function prepares the RFM22B module to receive - 
		1. Turn on Rx antenna circuitry
		2. Clear FIFO
		3. Set mode to receive
		4. Turn on RFM22B Packet Received Interrupt
*************************************************************************/
void RFM22B_rxMode(void)
{
//	unsigned char i;
	RFM22B_clearRXBuf();//так лучше...
	
//	RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, 0x01);	// to ready mode
	RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, (0x01 | 1<<6));	// to ready mode
	
//	i = read(0x03);		// read interrupt vector
//	i = read(0x04);		// read interrupt vector
	RFM22B_RegisterRead(RFM22B_REGISTER_03_INTERRUPT_STATUS_1);		// read interrupt vector
	RFM22B_RegisterRead(RFM22B_REGISTER_04_INTERRUPT_STATUS_2);		// read interrupt vector

//	cbi(PORTC,TXANT);	// Turn off Tx Antenna select input pin
//	sbi(PORTC,RXANT);	// Turn on Rx Antenna select input pin
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_7E_RX_FIFO_CONTROL, PKTSIZE);	// set RX FIFO almost full threshold
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_08_OPERATING_FUNCTION_CONTROL_2, 0x03);	// clear contents of FIFO - reset FIFO
	RFM22B_RegisterWrite(RFM22B_REGISTER_08_OPERATING_FUNCTION_CONTROL_2, 0x00);	// clear contents of FIFO - clear FIFO
	
//	RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, 5);		// RX on, Ready mode
	RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, (5 | 0x40));		// RX on, Ready mode
	RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, (5 | 1<<6));		// RX on, Ready mode
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_05_INTERRUPT_ENABLE_1, 2);		// Valid Packet Received interrupt enabled


//	RFM22B_RegisterWrite(RFM22B_REGISTER_05_INTERRUPT_ENABLE_1, 0);		// 
//	RFM22B_RegisterWrite(RFM22B_REGISTER_06_INTERRUPT_ENABLE_2, 64);	// Valid preamble
}
#endif
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
#ifdef RFM22B_CHOOSE_TRANSMITTER
void RFM22B_txMode()
    {
	unsigned char i;
	
	RFM22B_readyMode();	// To ready mode
//	cbi(PORTC, RXANT);
//	sbi(PORTC, TXANT);
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_08_OPERATING_FUNCTION_CONTROL_2, 0x03);	// FIFO reset
	RFM22B_RegisterWrite(RFM22B_REGISTER_08_OPERATING_FUNCTION_CONTROL_2, 0x00);	// Clear FIFO
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_34_PREAMBLE_LENGTH, 64);	// preamble = 64nibble
	RFM22B_setTransmitPacketSize(PKTSIZE);	// packet length = 17bytes - DOES THIS NEED TO BE HERE????? - ALREADY SET IN init_RFM22()



//    RFM22B_RegisterWrite(RFM22B_REGISTER_7F_FIFO_ACCESS, PKTSIZE);
	for (i=0; i<PKTSIZE; i++)
    	{
		RFM22B_RegisterWrite(RFM22B_REGISTER_7F_FIFO_ACCESS, TX_BUF[i]);	// send payload to the FIFO
	    }

	RFM22B_RegisterWrite(RFM22B_REGISTER_05_INTERRUPT_ENABLE_1, 0x04);	// enable packet sent interrupt
//	i = read(0x03);		// Read Interrupt status1 register
//	i = read(0x04);
	RFM22B_RegisterRead(RFM22B_REGISTER_03_INTERRUPT_STATUS_1);		// Read Interrupt status1 register
	RFM22B_RegisterRead(RFM22B_REGISTER_04_INTERRUPT_STATUS_2);
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, 9 | 1<<6 );		// Start TX
	
	while ((RFM22B_NIRQ_PIN & (1<<RFM22B_NIRQ_BIT)) != 0)
		// wait for packet sent interrupt (NIRQ goes low)
		;
	
	RFM22B_readyMode();
	
//	cbi(PORTC, RXANT);	
//	cbi(PORTC, TXANT);
    }

void RFM22B_txModeFast1()
    {
	unsigned char i;
	
	RFM22B_readyMode();

	RFM22B_RegisterWrite(RFM22B_REGISTER_08_OPERATING_FUNCTION_CONTROL_2, 0x03);	// FIFO reset
	RFM22B_RegisterWrite(RFM22B_REGISTER_08_OPERATING_FUNCTION_CONTROL_2, 0x00);	// Clear FIFO
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_34_PREAMBLE_LENGTH, 64);	// preamble = 64nibble
	RFM22B_setTransmitPacketSize(PKTSIZE);	// packet length = 17bytes - DOES THIS NEED TO BE HERE????? - ALREADY SET IN init_RFM22()



//    RFM22B_RegisterWrite(RFM22B_REGISTER_7F_FIFO_ACCESS, PKTSIZE);
	for (i=0; i<PKTSIZE; i++)
    	{
		RFM22B_RegisterWrite(RFM22B_REGISTER_7F_FIFO_ACCESS, TX_BUF[i]);	// send payload to the FIFO
	    }

	RFM22B_RegisterWrite(RFM22B_REGISTER_05_INTERRUPT_ENABLE_1, 0x04);	// enable packet sent interrupt
//	i = read(0x03);		// Read Interrupt status1 register
//	i = read(0x04);
	RFM22B_RegisterRead(RFM22B_REGISTER_03_INTERRUPT_STATUS_1);		// Read Interrupt status1 register
	RFM22B_RegisterRead(RFM22B_REGISTER_04_INTERRUPT_STATUS_2);
    }
void RFM22B_txModeFast2()
    {
	RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, 9 | 1<<6 );		// Start TX
	
	while ((RFM22B_NIRQ_PIN & (1<<RFM22B_NIRQ_BIT)) != 0)
		// wait for packet sent interrupt (NIRQ goes low)
		;
	
	
//	cbi(PORTC, RXANT);	
//	cbi(PORTC, TXANT);
    }
void RFM22B_txModeFast3()
    {
    }
#endif

#endif
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef RFM22B_HAL_C
#define RFM22B_HAL_C
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
//#define RFM22B_POWER_ON             cbi(RFM22B_SDN_PORT,RFM22B_SDN_BIT)
//#define RFM22B_POWER_OFF            sbi(RFM22B_SDN_PORT,RFM22B_SDN_BIT)
#define RFM22B_POWER_ON             RFM22B_PinSDN::SetOutLow();
#define RFM22B_POWER_OFF            RFM22B_PinSDN::SetOutHigh();


//======================================

//=======FUNCTION DECLARATIONS==========
void RFM22B_setTransmitPacketSize(unsigned char size);
/************************************************************************
	FUNCTION: txdata() 
	DESCRIPTION:  This function sends a byte via SPI communication
*************************************************************************/
volatile void RFM22B_SPI_TXData(char data)
	{
	SPDR = data;
	while((SPSR&0x80) == 0x00);
	}
void RFM22B_RegisterWrite(unsigned char address, unsigned char data);
//void RFM22B_init(void);
void RFM22B_ioinit(void);
void RFM22B_txMode();
void RFM22B_rxMode();
//void RFM22B_readyMode();
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


/************************************************************************
	FUNCTION: RFM22B_RegisterWrite() 
	DESCRIPTION:  This function sends a byte to the RFM22B
*************************************************************************/
void RFM22B_RegisterWrite(unsigned char address, unsigned char data)
{
	//write any data byte to any single address
	//adds a 1 to the MSB of the address byte (WRITE mode)
	
	address |= 0x80;

	//cbi(RFM22B_SPI_PORT, RFM22B_NSEL);
	RFM22B_PinNSEL::SetOutLow();
	
//	delay_ms(1);
	RFM22B_SPI_TXData(address);
//	delay_ms(1);
	RFM22B_SPI_TXData(data);
//	delay_ms(1);
	//sbi(RFM22B_SPI_PORT, RFM22B_NSEL);
	RFM22B_PinNSEL::SetOutHigh();
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

	//cbi(RFM22B_SPI_PORT, RFM22B_NSEL);
	RFM22B_PinNSEL::SetOutLow();
	RFM22B_SPI_TXData(address);
	byte = RFM22B_SPI_RXData();
	//sbi(RFM22B_SPI_PORT, RFM22B_NSEL);
	RFM22B_PinNSEL::SetOutHigh();

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
//    RFM22B_SDN_DDR     |= (1<<RFM22B_SDN_BIT);
	RFM22B_PinSDN::SetDirOut();
	RFM22B_POWER_ON;
//    RFM22B_NIRQ_PORT   |= (1<<RFM22B_NIRQ_BIT);
//    RFM22B_GPIO0_PORT  |= (1<<RFM22B_GPIO0_BIT);//подт€гивающий резистор
    //cbi(RFM22B_GPIO0_PORT,RFM22B_GPIO0_BIT);//вход
    //sbi(RFM22B_GPIO0_PORT,RFM22B_GPIO0_BIT);//подт€гивающий резистор
	RFM22B_PinGPIO0::SetDirIn();
	RFM22B_PinGPIO0::SetPullUp();

//    RFM22B_SPI_DDR     |= (1<<RFM22B_SCK) | (1<<RFM22B_SDI) | (1<<RFM22B_NSEL);//выходы
    //cbi(RFM22B_SPI_PORT,RFM22B_SCK);
    //cbi(RFM22B_SPI_PORT,RFM22B_SDI);
    //cbi(RFM22B_SPI_PORT,RFM22B_NSEL);
	RFM22B_PinSCK::SetDirOut();
	RFM22B_PinSCK::SetOutLow();

	RFM22B_PinSDO::SetDirIn();
	RFM22B_PinSDO::SetPullUp();

	RFM22B_PinSDI::SetDirOut();
	RFM22B_PinSDI::SetOutLow();

	RFM22B_PinNSEL::SetDirOut();
	RFM22B_PinNSEL::SetOutLow();

    //sbi(RFM22B_NIRQ_PORT,   RFM22B_NIRQ_BIT);//подт€гивающий резистор
    //cbi(RFM22B_NIRQ_DDR,    RFM22B_NIRQ_BIT);//вход
	RFM22B_PinNIRQ::SetDirIn();
	RFM22B_PinNIRQ::SetPullUp();
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
/*
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
*/
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
/*
void RFM22B_readyMode()
    {
	this->RXState	= Driver_AnoRadRarioModule::CURRENT_RX_STATES::CURRENT_RX_STATE_NONE;
    RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1, 0x01);	// to ready mode
    }
*/
void RFM22B_setTransmitPacketSize(unsigned char size)
    {
    RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH, size);
    }

#endif
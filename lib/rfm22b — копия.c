// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
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
#define PKTSIZE 8	// size of packet to be transmitted (max 64 bytes for this example program - RFM22B is capable of 255 bytes max)
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


void RFM22B_selectFrequency(void)
    {
//	RFM22B_RegisterWrite(RFM22B_REGISTER_75_FREQUENCY_BAND_SELECT,                  0x52);		// frequency set to 420MHz
//	RFM22B_RegisterWrite(RFM22B_REGISTER_76_NOMINAL_CARRIER_FREQUENCY_1,            0x00);		// frequency set to 420MHz
//	RFM22B_RegisterWrite(RFM22B_REGISTER_77_NOMINAL_CARRIER_FREQUENCY_0,            0x00);		// frequency set to 420Mhz
	
//	RFM22B_RegisterWrite(RFM22B_REGISTER_75_FREQUENCY_BAND_SELECT,                  0x53);		// frequency set to 434MHz
//	RFM22B_RegisterWrite(RFM22B_REGISTER_76_NOMINAL_CARRIER_FREQUENCY_1,            0x64);		// frequency set to 434MHz
//	RFM22B_RegisterWrite(RFM22B_REGISTER_77_NOMINAL_CARRIER_FREQUENCY_0,            0x00);		// frequency set to 434Mhz

//	RFM22B_RegisterWrite(RFM22B_REGISTER_75_FREQUENCY_BAND_SELECT,                  0x53);		// frequency set to 435MHz
//	RFM22B_RegisterWrite(RFM22B_REGISTER_76_NOMINAL_CARRIER_FREQUENCY_1,            0x7D);		// frequency set to 435MHz
//	RFM22B_RegisterWrite(RFM22B_REGISTER_77_NOMINAL_CARRIER_FREQUENCY_0,            0x00);		// frequency set to 435Mhz
	
//	RFM22B_RegisterWrite(RFM22B_REGISTER_75_FREQUENCY_BAND_SELECT,                  0x53);		// frequency set to 436MHz
//	RFM22B_RegisterWrite(RFM22B_REGISTER_76_NOMINAL_CARRIER_FREQUENCY_1,            0x96);		// frequency set to 436MHz
//	RFM22B_RegisterWrite(RFM22B_REGISTER_77_NOMINAL_CARRIER_FREQUENCY_0,            0x00);		// frequency set to 436Mhz
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_75_FREQUENCY_BAND_SELECT,                  0x54);		// frequency set to 446MHz
	RFM22B_RegisterWrite(RFM22B_REGISTER_76_NOMINAL_CARRIER_FREQUENCY_1,            0x96);		// frequency set to 446MHz
	RFM22B_RegisterWrite(RFM22B_REGISTER_77_NOMINAL_CARRIER_FREQUENCY_0,            0x00);		// frequency set to 446Mhz

//	RFM22B_RegisterWrite(RFM22B_REGISTER_75_FREQUENCY_BAND_SELECT,                  0x55);		// frequency set to 450MHz
//	RFM22B_RegisterWrite(RFM22B_REGISTER_76_NOMINAL_CARRIER_FREQUENCY_1,            0x00);		// frequency set to 450MHz
//	RFM22B_RegisterWrite(RFM22B_REGISTER_77_NOMINAL_CARRIER_FREQUENCY_0,            0x00);		// frequency set to 450Mhz

//	RFM22B_RegisterWrite(RFM22B_REGISTER_75_FREQUENCY_BAND_SELECT,                  0x73);		// frequency set to 868MHz
//	RFM22B_RegisterWrite(RFM22B_REGISTER_76_NOMINAL_CARRIER_FREQUENCY_1,            0x64);		// frequency set to 868MHz
//	RFM22B_RegisterWrite(RFM22B_REGISTER_77_NOMINAL_CARRIER_FREQUENCY_0,            0x00);		// frequency set to 868Mhz
    }

/************************************************************************
	FUNCTION: RFM22B_init() 
	DESCRIPTION:  This function initializes the RFM22B for use, by 
		setting all applicable internal register values.
*************************************************************************/

void RFM22B_initOld(void)
{
	RFM22B_RegisterWrite(RFM22B_REGISTER_06_INTERRUPT_ENABLE_2,                     0x00);		// Disable all interrupts
	RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1,           0x01);		// Set READY mode
	RFM22B_RegisterWrite(RFM22B_REGISTER_09_CRYSTAL_OSCILLATOR_LOAD_CAPACITANCE,    0x7F);		// Cap = 12.5pF
//	RFM22B_RegisterWrite(RFM22B_REGISTER_0A_MICROCONTROLLER_OUTPUT_CLOCK,           0x05);		// Clk output is 2MHz
//	RFM22B_RegisterWrite(RFM22B_REGISTER_0A_MICROCONTROLLER_OUTPUT_CLOCK,           0x02);		// Clk output is 10MHz
	RFM22B_RegisterWrite(RFM22B_REGISTER_0A_MICROCONTROLLER_OUTPUT_CLOCK,           0b010);		// Clk output is 10MHz
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_0B_GPIO_0_CONFIGURATION,                   0xF4);		// GPIO0 is for RX data output
	RFM22B_RegisterWrite(RFM22B_REGISTER_0C_GPIO_1_CONFIGURATION,                   0xEF);		// GPIO1 is TX/RX data CLK output
	RFM22B_RegisterWrite(RFM22B_REGISTER_0D_GPIO_2_CONFIGURATION,                   0x00);		// GPIO2 for MCLK output
	RFM22B_RegisterWrite(RFM22B_REGISTER_0E_IO_PORT_CONFIGURATION,                  0x00);		// GPIO port use default value
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_0F_ADC_CONFIGURATION,                      0x70);		// NO ADC used
	RFM22B_RegisterWrite(RFM22B_REGISTER_10_ADC_SENSOR_AMPLIFIER_OFFSET,            0x00);		// no ADC used
	RFM22B_RegisterWrite(RFM22B_REGISTER_12_TEMPERATURE_SENSOR_CONTROL,             0x00);		// No temp sensor used
	RFM22B_RegisterWrite(RFM22B_REGISTER_13_TEMPERATURE_VALUE_OFFSET,               0x00);		// no temp sensor used
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_70_MODULATION_MODE_CONTROL_1,              0x20);		// No manchester code, no data whiting, data rate < 30Kbps
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_1C_IF_FILTER_BANDWIDTH,                    0x1D);		// IF filter bandwidth
	RFM22B_RegisterWrite(RFM22B_REGISTER_1D_AFC_LOOP_GEARSHIFT_OVERRIDE,            0x40);		// AFC Loop
	//RFM22B_RegisterWrite(RFM22B_REGISTER_1E_AFC_TIMING_CONTROL, 0x0A);	// AFC timing
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_20_CLOCK_RECOVERY_OVERSAMPLING_RATIO,      0xA1);		// clock recovery
	RFM22B_RegisterWrite(RFM22B_REGISTER_21_CLOCK_RECOVERY_OFFSET_2,                0x20);		// clock recovery
	RFM22B_RegisterWrite(RFM22B_REGISTER_22_CLOCK_RECOVERY_OFFSET_1,                0x4E);		// clock recovery
	RFM22B_RegisterWrite(RFM22B_REGISTER_23_CLOCK_RECOVERY_OFFSET_0,                0xA5);		// clock recovery
	RFM22B_RegisterWrite(RFM22B_REGISTER_24_CLOCK_RECOVERY_TIMING_LOOP_GAIN_1,      0x00);		// clock recovery timing
	RFM22B_RegisterWrite(RFM22B_REGISTER_25_CLOCK_RECOVERY_TIMING_LOOP_GAIN_0,      0x0A);		// clock recovery timing
	
	//RFM22B_RegisterWrite(RFM22B_REGISTER_2A_AFC_LIMITER, 0x18);
	RFM22B_RegisterWrite(RFM22B_REGISTER_2C_OOK_COUNTER_VALUE_1,                    0x00);
	RFM22B_RegisterWrite(RFM22B_REGISTER_2D_OOK_COUNTER_VALUE_2,                    0x00);
	RFM22B_RegisterWrite(RFM22B_REGISTER_2E_SLICER_PEAK_HOLD,                       0x00);
	

//TX DATA RATE
	RFM22B_RegisterWrite(RFM22B_REGISTER_6E_TX_DATA_RATE_1,                         0x27);		// TX data rate 1
	RFM22B_RegisterWrite(RFM22B_REGISTER_6F_TX_DATA_RATE_0,                         0x52);		// TX data rate 0
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_30_DATA_ACCESS_CONTROL,                    0x8C);		// Data access control
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_32_HEADER_CONTROL_1,                       0xFF);		// Header control
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_33_HEADER_CONTROL_2,                       0x42);		// Header 3, 2, 1, 0 used for head length, fixed packet length, synchronize word length 3, 2,
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_34_PREAMBLE_LENGTH,                        64);		// 64 nibble = 32 byte preamble
	RFM22B_RegisterWrite(RFM22B_REGISTER_35_PREAMBLE_DETECTION_CONTROL,             0x20);		// 0x35 need to detect 20bit preamble

	RFM22B_RegisterWrite(RFM22B_REGISTER_36_SYNC_WORD_3,                            0x2D);		// synchronize word
	RFM22B_RegisterWrite(RFM22B_REGISTER_37_SYNC_WORD_2,                            0xD4);
	RFM22B_RegisterWrite(RFM22B_REGISTER_38_SYNC_WORD_1,                            0x00);
	RFM22B_RegisterWrite(RFM22B_REGISTER_39_SYNC_WORD_0,                            0x00);
/*
	RFM22B_RegisterWrite(RFM22B_REGISTER_36_SYNC_WORD_3, 0x2D);		// synchronize word
	RFM22B_RegisterWrite(RFM22B_REGISTER_37_SYNC_WORD_2, 0xD4);
	RFM22B_RegisterWrite(RFM22B_REGISTER_38_SYNC_WORD_1, 0xAA);
	RFM22B_RegisterWrite(RFM22B_REGISTER_39_SYNC_WORD_0, 0xAA);
*/
	RFM22B_RegisterWrite(RFM22B_REGISTER_3A_TRANSMIT_HEADER_3,                      '*');		// set tx header 3
	RFM22B_RegisterWrite(RFM22B_REGISTER_3B_TRANSMIT_HEADER_2,                      'E');		// set tx header 2
	RFM22B_RegisterWrite(RFM22B_REGISTER_3C_TRANSMIT_HEADER_1,                      'W');		// set tx header 1
	RFM22B_RegisterWrite(RFM22B_REGISTER_3D_TRANSMIT_HEADER_0,                      'S');		// set tx header 0
	//RFM22B_RegisterWrite(0x3E, 17);		// set packet length to 17 bytes (max size: 255 bytes)
//	RFM22B_setTransmitPacketSize(PKTSIZE);	// set packet length to PKTSIZE bytes (max size: 255 bytes)
    RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 PKTSIZE);
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_3F_CHECK_HEADER_3,                         '*');		// set rx header
	RFM22B_RegisterWrite(RFM22B_REGISTER_40_CHECK_HEADER_2,                         'E');
	RFM22B_RegisterWrite(RFM22B_REGISTER_41_CHECK_HEADER_1,                         'W');
	RFM22B_RegisterWrite(RFM22B_REGISTER_42_CHECK_HEADER_0,                         'S');
	RFM22B_RegisterWrite(RFM22B_REGISTER_43_HEADER_ENABLE_3,                        0xFF);		// check all bits
	RFM22B_RegisterWrite(RFM22B_REGISTER_44_HEADER_ENABLE_2,                        0xFF);		// Check all bits
	RFM22B_RegisterWrite(RFM22B_REGISTER_45_HEADER_ENABLE_1,                        0xFF);		// check all bits
	RFM22B_RegisterWrite(RFM22B_REGISTER_46_HEADER_ENABLE_0,                        0xFF);		// Check all bits
	
	RFM22B_RegisterWrite(0x56, 0x01);//hmm....
	
//	RFM22B_RegisterWrite(RFM22B_REGISTER_TX_POWER,                                    0x07);		// Tx power to max
#ifdef TX_POWER
	RFM22B_RegisterWrite(RFM22B_REGISTER_6D_TX_POWER,                               (RFM22B_LNA_SW | (TX_POWER & 7)));
#else
	RFM22B_RegisterWrite(RFM22B_REGISTER_6D_TX_POWER,                               (RFM22B_LNA_SW | 7));		// Tx power to max
#endif	
	RFM22B_RegisterWrite(RFM22B_REGISTER_79_FREQUENCY_HOPPING_CHANNEL_SELECT,       0x00);		// no frequency hopping
	RFM22B_RegisterWrite(RFM22B_REGISTER_7A_FREQUENCY_HOPPING_STEP_SIZE,            0x00);		// no frequency hopping
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x22);		// GFSK, fd[8]=0, no invert for TX/RX data, FIFO mode, txclk-->gpio
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_72_FREQUENCY_DEVIATION,                    0x48);		// Frequency deviation setting to 45K=72*625
//	RFM22B_RegisterWrite(RFM22B_REGISTER_72_FREQUENCY_DEVIATION,                    80);		// Frequency deviation setting to 50K=80*625
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_73_FREQUENCY_OFFSET_1,                     0x00);		// No frequency offset
	RFM22B_RegisterWrite(RFM22B_REGISTER_74_FREQUENCY_OFFSET_2,                     0x00);		// No frequency offset
    
    RFM22B_selectFrequency();
	
	
	RFM22B_RegisterWrite(0x5A, 0x7F);//hmmm...
	RFM22B_RegisterWrite(0x59, 0x40);//hmmm...
	RFM22B_RegisterWrite(0x58, 0x80);//hmmm...
	
	RFM22B_RegisterWrite(0x6A, 0x0B);//hmmm...
	RFM22B_RegisterWrite(0x68, 0x04);//hmmm...
	RFM22B_RegisterWrite(RFM22B_REGISTER_1F_CLOCK_RECOVERY_GEARSHIFT_OVERRIDE,      0x03);
}
void RFM22B_initOOK(void)
{
	RFM22B_RegisterWrite(RFM22B_REGISTER_1C_IF_FILTER_BANDWIDTH,                    0x91);		// IF filter bandwidth
	RFM22B_RegisterWrite(RFM22B_REGISTER_1D_AFC_LOOP_GEARSHIFT_OVERRIDE,            0x40);		// AFC Loop
	//RFM22B_RegisterWrite(RFM22B_REGISTER_1E_AFC_TIMING_CONTROL, 0x0A);	// AFC timing

	RFM22B_RegisterWrite(RFM22B_REGISTER_20_CLOCK_RECOVERY_OVERSAMPLING_RATIO,      0xBC);		// clock recovery
	RFM22B_RegisterWrite(RFM22B_REGISTER_21_CLOCK_RECOVERY_OFFSET_2,                0x00);		// clock recovery
	RFM22B_RegisterWrite(RFM22B_REGISTER_22_CLOCK_RECOVERY_OFFSET_1,                0xAE);		// clock recovery
	RFM22B_RegisterWrite(RFM22B_REGISTER_23_CLOCK_RECOVERY_OFFSET_0,                0xC3);		// clock recovery
	RFM22B_RegisterWrite(RFM22B_REGISTER_24_CLOCK_RECOVERY_TIMING_LOOP_GAIN_1,      0x00);		// clock recovery timing
	RFM22B_RegisterWrite(RFM22B_REGISTER_25_CLOCK_RECOVERY_TIMING_LOOP_GAIN_0,      0xB0);		// clock recovery timing
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_2A_AFC_LIMITER,                            0x2c);
	RFM22B_RegisterWrite(RFM22B_REGISTER_2C_OOK_COUNTER_VALUE_1,                    0x28);
	RFM22B_RegisterWrite(RFM22B_REGISTER_2D_OOK_COUNTER_VALUE_2,                    0x27);
	RFM22B_RegisterWrite(RFM22B_REGISTER_2E_SLICER_PEAK_HOLD,                       0x29);

	RFM22B_RegisterWrite(RFM22B_REGISTER_30_DATA_ACCESS_CONTROL,                    0xac);		// Data access control
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_32_HEADER_CONTROL_1,                       0x8c);		// Header control
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_33_HEADER_CONTROL_2,                       0x02);		// 
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_34_PREAMBLE_LENGTH,                        64);		// 64 nibble = 32 byte preamble
	RFM22B_RegisterWrite(RFM22B_REGISTER_35_PREAMBLE_DETECTION_CONTROL,             0x2a);		// 

	RFM22B_RegisterWrite(RFM22B_REGISTER_36_SYNC_WORD_3,                            0x2D);		// synchronize word
	RFM22B_RegisterWrite(RFM22B_REGISTER_37_SYNC_WORD_2,                            0xD4);
	RFM22B_RegisterWrite(RFM22B_REGISTER_38_SYNC_WORD_1,                            0x00);
	RFM22B_RegisterWrite(RFM22B_REGISTER_39_SYNC_WORD_0,                            0x00);
/*
	RFM22B_RegisterWrite(RFM22B_REGISTER_36_SYNC_WORD_3, 0x2D);		// synchronize word
	RFM22B_RegisterWrite(RFM22B_REGISTER_37_SYNC_WORD_2, 0xD4);
	RFM22B_RegisterWrite(RFM22B_REGISTER_38_SYNC_WORD_1, 0xAA);
	RFM22B_RegisterWrite(RFM22B_REGISTER_39_SYNC_WORD_0, 0xAA);
*/
	RFM22B_RegisterWrite(RFM22B_REGISTER_3A_TRANSMIT_HEADER_3,                      '*');		// set tx header 3
	RFM22B_RegisterWrite(RFM22B_REGISTER_3B_TRANSMIT_HEADER_2,                      'E');		// set tx header 2
	RFM22B_RegisterWrite(RFM22B_REGISTER_3C_TRANSMIT_HEADER_1,                      'W');		// set tx header 1
	RFM22B_RegisterWrite(RFM22B_REGISTER_3D_TRANSMIT_HEADER_0,                      'S');		// set tx header 0
	//RFM22B_RegisterWrite(0x3E, 17);		// set packet length to 17 bytes (max size: 255 bytes)
//	RFM22B_setTransmitPacketSize(PKTSIZE);	// set packet length to PKTSIZE bytes (max size: 255 bytes)
    RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 PKTSIZE);
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_3F_CHECK_HEADER_3,                         '*');		// set rx header
	RFM22B_RegisterWrite(RFM22B_REGISTER_40_CHECK_HEADER_2,                         'E');
	RFM22B_RegisterWrite(RFM22B_REGISTER_41_CHECK_HEADER_1,                         'W');
	RFM22B_RegisterWrite(RFM22B_REGISTER_42_CHECK_HEADER_0,                         'S');
	RFM22B_RegisterWrite(RFM22B_REGISTER_43_HEADER_ENABLE_3,                        0xFF);		// check all bits
	RFM22B_RegisterWrite(RFM22B_REGISTER_44_HEADER_ENABLE_2,                        0xFF);		// Check all bits
	RFM22B_RegisterWrite(RFM22B_REGISTER_45_HEADER_ENABLE_1,                        0xFF);		// check all bits
	RFM22B_RegisterWrite(RFM22B_REGISTER_46_HEADER_ENABLE_0,                        0xFF);		// Check all bits

//TX DATA RATE
	RFM22B_RegisterWrite(RFM22B_REGISTER_6E_TX_DATA_RATE_1,                         0x08);		// TX data rate 1
	RFM22B_RegisterWrite(RFM22B_REGISTER_6F_TX_DATA_RATE_0,                         0x31);		// TX data rate 0

	RFM22B_RegisterWrite(RFM22B_REGISTER_70_MODULATION_MODE_CONTROL_1,              0x0c);		// 
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x21);		// 
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_72_FREQUENCY_DEVIATION,                    0x50);		// 


    RFM22B_selectFrequency();
/////////////////


	RFM22B_RegisterWrite(RFM22B_REGISTER_06_INTERRUPT_ENABLE_2,                     0x00);		// Disable all interrupts
	RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1,           0x01);		// Set READY mode
	RFM22B_RegisterWrite(RFM22B_REGISTER_09_CRYSTAL_OSCILLATOR_LOAD_CAPACITANCE,    0x7F);		// Cap = 12.5pF
//	RFM22B_RegisterWrite(RFM22B_REGISTER_0A_MICROCONTROLLER_OUTPUT_CLOCK,           0x05);		// Clk output is 2MHz
//	RFM22B_RegisterWrite(RFM22B_REGISTER_0A_MICROCONTROLLER_OUTPUT_CLOCK,           0x02);		// Clk output is 10MHz
	RFM22B_RegisterWrite(RFM22B_REGISTER_0A_MICROCONTROLLER_OUTPUT_CLOCK,           0b010);		// Clk output is 10MHz
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_0B_GPIO_0_CONFIGURATION,                   0xF4);		// GPIO0 is for RX data output
	RFM22B_RegisterWrite(RFM22B_REGISTER_0C_GPIO_1_CONFIGURATION,                   0xEF);		// GPIO1 is TX/RX data CLK output
	RFM22B_RegisterWrite(RFM22B_REGISTER_0D_GPIO_2_CONFIGURATION,                   0x00);		// GPIO2 for MCLK output
	RFM22B_RegisterWrite(RFM22B_REGISTER_0E_IO_PORT_CONFIGURATION,                  0x00);		// GPIO port use default value
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_0F_ADC_CONFIGURATION,                      0x70);		// NO ADC used
	RFM22B_RegisterWrite(RFM22B_REGISTER_10_ADC_SENSOR_AMPLIFIER_OFFSET,            0x00);		// no ADC used
	RFM22B_RegisterWrite(RFM22B_REGISTER_12_TEMPERATURE_SENSOR_CONTROL,             0x00);		// No temp sensor used
	RFM22B_RegisterWrite(RFM22B_REGISTER_13_TEMPERATURE_VALUE_OFFSET,               0x00);		// no temp sensor used
	
	
	

	


	
	RFM22B_RegisterWrite(0x56, 0x01);//hmm....
	
//	RFM22B_RegisterWrite(RFM22B_REGISTER_TX_POWER,                                    0x07);		// Tx power to max
#ifdef TX_POWER
	RFM22B_RegisterWrite(RFM22B_REGISTER_6D_TX_POWER,                               (RFM22B_LNA_SW | (TX_POWER & 7)));
#else
	RFM22B_RegisterWrite(RFM22B_REGISTER_6D_TX_POWER,                               (RFM22B_LNA_SW | 7));		// Tx power to max
#endif	
	RFM22B_RegisterWrite(RFM22B_REGISTER_79_FREQUENCY_HOPPING_CHANNEL_SELECT,       0x00);		// no frequency hopping
	RFM22B_RegisterWrite(RFM22B_REGISTER_7A_FREQUENCY_HOPPING_STEP_SIZE,            0x00);		// no frequency hopping
	
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_73_FREQUENCY_OFFSET_1,                     0x00);		// No frequency offset
	RFM22B_RegisterWrite(RFM22B_REGISTER_74_FREQUENCY_OFFSET_2,                     0x00);		// No frequency offset
    
	
	
	RFM22B_RegisterWrite(0x5A, 0x7F);//hmmm...
	RFM22B_RegisterWrite(0x59, 0x40);//hmmm...
	RFM22B_RegisterWrite(0x58, 0x80);//hmmm...
	
	RFM22B_RegisterWrite(0x6A, 0x0B);//hmmm...
	RFM22B_RegisterWrite(0x68, 0x04);//hmmm...
	RFM22B_RegisterWrite(RFM22B_REGISTER_1F_CLOCK_RECOVERY_GEARSHIFT_OVERRIDE,      0x03);
}

void RFM22B_init(void)//GFCK
{
	RFM22B_RegisterWrite(RFM22B_REGISTER_1C_IF_FILTER_BANDWIDTH,                    0x82);		// IF filter bandwidth
	RFM22B_RegisterWrite(RFM22B_REGISTER_1D_AFC_LOOP_GEARSHIFT_OVERRIDE,            0x40);		// AFC Loop
	//RFM22B_RegisterWrite(RFM22B_REGISTER_1E_AFC_TIMING_CONTROL, 0x0A);	// AFC timing

	RFM22B_RegisterWrite(RFM22B_REGISTER_20_CLOCK_RECOVERY_OVERSAMPLING_RATIO,      0x5E);		// clock recovery
	RFM22B_RegisterWrite(RFM22B_REGISTER_21_CLOCK_RECOVERY_OFFSET_2,                0x01);		// clock recovery
	RFM22B_RegisterWrite(RFM22B_REGISTER_22_CLOCK_RECOVERY_OFFSET_1,                0x5D);		// clock recovery
	RFM22B_RegisterWrite(RFM22B_REGISTER_23_CLOCK_RECOVERY_OFFSET_0,                0x86);		// clock recovery
	RFM22B_RegisterWrite(RFM22B_REGISTER_24_CLOCK_RECOVERY_TIMING_LOOP_GAIN_1,      0x06);		// clock recovery timing
	RFM22B_RegisterWrite(RFM22B_REGISTER_25_CLOCK_RECOVERY_TIMING_LOOP_GAIN_0,      0xFB);		// clock recovery timing
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_2A_AFC_LIMITER,                            0x50);
	RFM22B_RegisterWrite(RFM22B_REGISTER_2C_OOK_COUNTER_VALUE_1,                    0x28);      //This setting is relevant only in OOK???
	RFM22B_RegisterWrite(RFM22B_REGISTER_2D_OOK_COUNTER_VALUE_2,                    0x09);      //This setting is relevant only in OOK???
	RFM22B_RegisterWrite(RFM22B_REGISTER_2E_SLICER_PEAK_HOLD,                       0x28);      //This setting is relevant only in OOK???

	RFM22B_RegisterWrite(RFM22B_REGISTER_30_DATA_ACCESS_CONTROL,                    0xAC);		// Data access control
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_32_HEADER_CONTROL_1,                       0x8C);		// Header control
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_33_HEADER_CONTROL_2,                       0x02);		// 
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_34_PREAMBLE_LENGTH,                        64);		// 64 nibble = 32 byte preamble
	RFM22B_RegisterWrite(RFM22B_REGISTER_35_PREAMBLE_DETECTION_CONTROL,             0x2A);		// 

	RFM22B_RegisterWrite(RFM22B_REGISTER_36_SYNC_WORD_3,                            0x2D);		// synchronize word
	RFM22B_RegisterWrite(RFM22B_REGISTER_37_SYNC_WORD_2,                            0xD4);
	RFM22B_RegisterWrite(RFM22B_REGISTER_38_SYNC_WORD_1,                            0x00);
	RFM22B_RegisterWrite(RFM22B_REGISTER_39_SYNC_WORD_0,                            0x00);
/*
	RFM22B_RegisterWrite(RFM22B_REGISTER_36_SYNC_WORD_3, 0x2D);		// synchronize word
	RFM22B_RegisterWrite(RFM22B_REGISTER_37_SYNC_WORD_2, 0xD4);
	RFM22B_RegisterWrite(RFM22B_REGISTER_38_SYNC_WORD_1, 0xAA);
	RFM22B_RegisterWrite(RFM22B_REGISTER_39_SYNC_WORD_0, 0xAA);
*/
	RFM22B_RegisterWrite(RFM22B_REGISTER_3A_TRANSMIT_HEADER_3,                      '*');		// set tx header 3
	RFM22B_RegisterWrite(RFM22B_REGISTER_3B_TRANSMIT_HEADER_2,                      'E');		// set tx header 2
	RFM22B_RegisterWrite(RFM22B_REGISTER_3C_TRANSMIT_HEADER_1,                      'W');		// set tx header 1
	RFM22B_RegisterWrite(RFM22B_REGISTER_3D_TRANSMIT_HEADER_0,                      'S');		// set tx header 0
	//RFM22B_RegisterWrite(0x3E, 17);		// set packet length to 17 bytes (max size: 255 bytes)
//	RFM22B_setTransmitPacketSize(PKTSIZE);	// set packet length to PKTSIZE bytes (max size: 255 bytes)
    RFM22B_RegisterWrite(RFM22B_REGISTER_3E_TRANSMIT_PACKET_LENGTH,                 PKTSIZE);
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_3F_CHECK_HEADER_3,                         '*');		// set rx header
	RFM22B_RegisterWrite(RFM22B_REGISTER_40_CHECK_HEADER_2,                         'E');
	RFM22B_RegisterWrite(RFM22B_REGISTER_41_CHECK_HEADER_1,                         'W');
	RFM22B_RegisterWrite(RFM22B_REGISTER_42_CHECK_HEADER_0,                         'S');
	RFM22B_RegisterWrite(RFM22B_REGISTER_43_HEADER_ENABLE_3,                        0xFF);		// check all bits
	RFM22B_RegisterWrite(RFM22B_REGISTER_44_HEADER_ENABLE_2,                        0xFF);		// Check all bits
	RFM22B_RegisterWrite(RFM22B_REGISTER_45_HEADER_ENABLE_1,                        0xFF);		// check all bits
	RFM22B_RegisterWrite(RFM22B_REGISTER_46_HEADER_ENABLE_0,                        0xFF);		// Check all bits

//TX DATA RATE
	RFM22B_RegisterWrite(RFM22B_REGISTER_6E_TX_DATA_RATE_1,                         0x20);		// TX data rate 1
	RFM22B_RegisterWrite(RFM22B_REGISTER_6F_TX_DATA_RATE_0,                         0xC5);		// TX data rate 0

	RFM22B_RegisterWrite(RFM22B_REGISTER_70_MODULATION_MODE_CONTROL_1,              0x0C);		// 
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_71_MODULATION_MODE_CONTROL_2,              0x23);		// 
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_72_FREQUENCY_DEVIATION,                    0x50);		// 


    RFM22B_selectFrequency();
/////////////////


	RFM22B_RegisterWrite(RFM22B_REGISTER_06_INTERRUPT_ENABLE_2,                     0x00);		// Disable all interrupts
	RFM22B_RegisterWrite(RFM22B_REGISTER_07_OPERATING_FUNCTION_CONTROL_1,           0x01);		// Set READY mode
	RFM22B_RegisterWrite(RFM22B_REGISTER_09_CRYSTAL_OSCILLATOR_LOAD_CAPACITANCE,    0x7F);		// Cap = 12.5pF
//	RFM22B_RegisterWrite(RFM22B_REGISTER_0A_MICROCONTROLLER_OUTPUT_CLOCK,           0x05);		// Clk output is 2MHz
//	RFM22B_RegisterWrite(RFM22B_REGISTER_0A_MICROCONTROLLER_OUTPUT_CLOCK,           0x02);		// Clk output is 10MHz
	RFM22B_RegisterWrite(RFM22B_REGISTER_0A_MICROCONTROLLER_OUTPUT_CLOCK,           RFM22B_MC_CLK_10MHZ);		// Clk output is 10MHz
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_0B_GPIO_0_CONFIGURATION,                   0xF4);		// GPIO0 is for RX data output
	RFM22B_RegisterWrite(RFM22B_REGISTER_0C_GPIO_1_CONFIGURATION,                   0xEF);		// GPIO1 is TX/RX data CLK output
	RFM22B_RegisterWrite(RFM22B_REGISTER_0D_GPIO_2_CONFIGURATION,                   0x00);		// GPIO2 for MCLK output
	RFM22B_RegisterWrite(RFM22B_REGISTER_0E_IO_PORT_CONFIGURATION,                  0x00);		// GPIO port use default value
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_0F_ADC_CONFIGURATION,                      0x70);		// NO ADC used
	RFM22B_RegisterWrite(RFM22B_REGISTER_10_ADC_SENSOR_AMPLIFIER_OFFSET,            0x00);		// no ADC used
	RFM22B_RegisterWrite(RFM22B_REGISTER_12_TEMPERATURE_SENSOR_CONTROL,             0x00);		// No temp sensor used
	RFM22B_RegisterWrite(RFM22B_REGISTER_13_TEMPERATURE_VALUE_OFFSET,               0x00);		// no temp sensor used
	
	
	

	


	
	RFM22B_RegisterWrite(0x56, 0x01);//hmm....
	
//	RFM22B_RegisterWrite(RFM22B_REGISTER_TX_POWER,                                    0x07);		// Tx power to max
#ifdef TX_POWER
	RFM22B_RegisterWrite(RFM22B_REGISTER_6D_TX_POWER,                               (RFM22B_LNA_SW | (TX_POWER & 7)));
#else
	RFM22B_RegisterWrite(RFM22B_REGISTER_6D_TX_POWER,                               (RFM22B_LNA_SW | 7));		// Tx power to max
#endif	
	RFM22B_RegisterWrite(RFM22B_REGISTER_79_FREQUENCY_HOPPING_CHANNEL_SELECT,       0x00);		// no frequency hopping
	RFM22B_RegisterWrite(RFM22B_REGISTER_7A_FREQUENCY_HOPPING_STEP_SIZE,            0x00);		// no frequency hopping
	
	
	RFM22B_RegisterWrite(RFM22B_REGISTER_73_FREQUENCY_OFFSET_1,                     0x00);		// No frequency offset
	RFM22B_RegisterWrite(RFM22B_REGISTER_74_FREQUENCY_OFFSET_2,                     0x00);		// No frequency offset
    
	
	
	RFM22B_RegisterWrite(0x5A, 0x7F);//hmmm...
	RFM22B_RegisterWrite(0x59, 0x40);//hmmm...
	RFM22B_RegisterWrite(0x58, 0x80);//hmmm...
	
	RFM22B_RegisterWrite(0x6A, 0x0B);//hmmm...
	RFM22B_RegisterWrite(0x68, 0x04);//hmmm...
	RFM22B_RegisterWrite(RFM22B_REGISTER_1F_CLOCK_RECOVERY_GEARSHIFT_OVERRIDE,      0x03);
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
	delay_ms(1);
	RFM22B_SPI_TXData(address);
	delay_ms(1);
	RFM22B_SPI_TXData(data);
	delay_ms(1);
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
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
//LCD->

#define LCD_CLK_PORT            PORTC    // ������������ SPI, ������ ���� ��������������� ��� ����������� SPI, ���� �� ������������
#define LCD_CLK_DDR             DDRC
#define LCD_CLK_PIN             5

#define LCD_MOSI_PORT           PORTC    // ����� ������ SPI, ������ ���� ��������������� ��� ����������� SPI, ���� �� ������������
#define LCD_MOSI_DDR            DDRC
#define LCD_MOSI_PIN            4

#define LCD_DC_PORT             PORTC    // ����� �������-������; ����� ��� ������ �����
#define LCD_DC_DDR              DDRC
#define LCD_DC_PIN              3

#define LCD_CPORT               PORTC    // Chip-Select; ����� ��� ������ �����
#define LCD_CDDR                DDRC
#define LCD_CPIN                2

#define LCD_SS_PORT             PORTC    // ChipSelect SPI, ������ ���� ��������������� ��� ����������� SPI � �������� �� �����
#define LCD_SS_DDR              DDRC
#define LCD_SS_PIN              2

#define LCD_RST_PORT            PORTC    // ����� ������; ����� ��� ������ �����
#define LCD_RST_DDR             DDRC
#define LCD_RST_PIN             1

//typedef Driver_IO_Pin(PORTC, 4) LcdPinBacklight;
typedef Driver_IO_Pin<IOPINC_ADDR, 5> LcdPinCLK;
typedef Driver_IO_Pin<IOPINC_ADDR, 4> LcdPinSDIN;
typedef Driver_IO_Pin<IOPINC_ADDR, 3> LcdPinDC;
typedef Driver_IO_Pin<IOPINC_ADDR, 2> LcdPinSCE;
typedef Driver_IO_Pin<IOPINC_ADDR, 1> LcdPinRST;

//#define LCD_SPI									SPIE
//#define LCD_SPI_PORT							PORTE
uint8_t nullVar;
#define LCD_SPI nullVar		//��� ������
//TODO("HACK BLYAAA");
//TODO("warning sprintf can overwrite data over the buffer!");


///////////////////////////////////////////////////////////////////////////////////////////////////
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
typedef Driver_IO_Pin<IOPIND_ADDR, 3> RFM22B_PinGPIO0;

//typedef Driver_IO_Pin<IOPIND_ADDR, 6> LED;
typedef Driver_IO_Pin<IOPIND_ADDR, 6> RedLEDPin;
typedef Driver_IO_Pin<IOPIND_ADDR, 4> GreenLEDPin;
typedef Driver_IO_Pin<IOPIND_ADDR, 2> Button0;
typedef Driver_IO_Pin<IOPIND_ADDR, 5> Button1;
typedef Driver_IO_Pin<IOPIND_ADDR, 7> Button2;

typedef Driver_IO_Pin<IOPINB_ADDR, 0> RFM22B_PinSDN;
typedef Driver_IO_Pin<IOPINB_ADDR, 5> RFM22B_PinSCK;
typedef Driver_IO_Pin<IOPINB_ADDR, 3> RFM22B_PinSDI;
typedef Driver_IO_Pin<IOPINB_ADDR, 4> RFM22B_PinSDO;
typedef Driver_IO_Pin<IOPINB_ADDR, 2> RFM22B_PinNSEL;
typedef Driver_IO_Pin<IOPINB_ADDR, 1> RFM22B_PinNIRQ;

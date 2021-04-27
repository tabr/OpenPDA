//#include "iopins.h"
//#include "pinlist.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
//LCD->
/*
#define LCD_CLK_PORT            PORTC    // тактирование SPI, должен быть соответствующий пин аппаратного SPI, если он используется
#define LCD_CLK_DDR             DDRC
#define LCD_CLK_PIN             5

#define LCD_MOSI_PORT           PORTC    // выход данных SPI, должен быть соответствующий пин аппаратного SPI, если он используется
#define LCD_MOSI_DDR            DDRC
#define LCD_MOSI_PIN            4

#define LCD_DC_PORT             PORTC    // выбор команда-данные; любой пин любого порта
#define LCD_DC_DDR              DDRC
#define LCD_DC_PIN              3

#define LCD_CPORT               PORTC    // Chip-Select; любой пин любого порта
#define LCD_CDDR                DDRC
#define LCD_CPIN                2

#define LCD_SS_PORT             PORTC    // ChipSelect SPI, должен быть соответствующий пин аппаратного SPI и настроен на выход
#define LCD_SS_DDR              DDRC
#define LCD_SS_PIN              2

#define LCD_RST_PORT            PORTC    // сброс экрана; любой пин любого порта
#define LCD_RST_DDR             DDRC
#define LCD_RST_PIN             1
*/
uint8_t nullVar;

#define LCD_SPI nullVar		//ХАК блеааа

typedef Driver_IO_Pin<IOPINC_ADDR, 5> LcdPinCLK;
typedef Driver_IO_Pin<IOPINC_ADDR, 4> LcdPinSDIN;
typedef Driver_IO_Pin<IOPINC_ADDR, 3> LcdPinDC;
typedef Driver_IO_Pin<IOPINC_ADDR, 2> LcdPinSCE;
typedef Driver_IO_Pin<IOPINC_ADDR, 1> LcdPinRST;
/*
using namespace IO;
#define LCD_PIN_CLK								Pc5
#define LCD_PIN_SDIN							Pc4
#define LCD_PIN_DC								Pc3
#define LCD_PIN_SCE								Pc2
#define LCD_PIN_RST								Pc1
//#define LCD_PIN_LED								Pc0

typedef PinList<LCD_PIN_CLK, LCD_PIN_SDIN, LCD_PIN_DC, LCD_PIN_SCE, LCD_PIN_RST> n3310Pins;
*/
typedef Driver_IO_Pin<IOPINC_ADDR, 0> LCD_LEDPin;

//#define BUZZER_PIN								Pd1
//#define LCD_SPI									SPIE
//#define LCD_SPI_PORT							PORTE




///////////////////////////////////////////////////////////////////////////////////////////////////
/*
#define RFM22B_GPIO0_PORT       PORTD
#define RFM22B_GPIO0_DDR        DDRD
#define RFM22B_GPIO0_PIN        PIND
#define RFM22B_GPIO0_BIT        4
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

typedef Driver_IO_Pin<IOPINB_ADDR, 0> RFM22B_PinSDN;
typedef Driver_IO_Pin<IOPINB_ADDR, 5> RFM22B_PinSCK;
typedef Driver_IO_Pin<IOPINB_ADDR, 3> RFM22B_PinSDI;
typedef Driver_IO_Pin<IOPINB_ADDR, 4> RFM22B_PinSDO;
typedef Driver_IO_Pin<IOPINB_ADDR, 2> RFM22B_PinNSEL;
typedef Driver_IO_Pin<IOPINB_ADDR, 1> RFM22B_PinNIRQ;
typedef Driver_IO_Pin<IOPINC_ADDR, 4> BuzzerPin;
typedef Driver_IO_Pin<IOPINC_ADDR, 5> BuzzerPin_H;
typedef Driver_IO_Pin<IOPIND_ADDR, 2> DeviceAlivePin;	
typedef Driver_IO_Pin<IOPIND_ADDR, 6> RedLEDPin;
typedef Driver_IO_Pin<IOPIND_ADDR, 6> StatusLedPin;
typedef Driver_IO_Pin<IOPIND_ADDR, 4> GreenLEDPin;


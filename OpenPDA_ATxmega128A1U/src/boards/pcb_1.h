/*
 * pcb_1.h
 *
 * Created: 2015-02-18 01:30:04
 *  Author: tabr
 */ 


#ifndef PCB_H_
#define PCB_H_


#define PCB_REVISION              1

#include <avr/io.h>
#include "TODOmacro.h"
#include "stalker/drivers/Driver_IO_xmega128a1u.hpp"
#include "compiler_defines.h"
/*
//neiverio
#include "iopins.h"
#include "pinlist.h"
using namespace IO;
*/


/*
#define TWI_EEPROM_TWI_ADDRESS        0b10100000
#define TWI_EEPROM_SPEED_KHZ        400
#define TWI_EEPROM_SIZE_IN_BYTES      32768
#define TWI_EEPROM_SIZE_IN_USB_PAYLOADS    (TWI_EEPROM_SIZE_IN_BYTES/USB_PAYLOAD_SIZE)
#define TWI_EEPROM_WRITE_PAGE_SIZE      64
#define TWI_EEPROM_WRITE_DELAY_MS      10//5
*/

/* Virtual Port Mapping */

//typedef enum PORTCFG_VP0MAP_enum
//{
//  PORTCFG_VP0MAP_PORTA_gc = (0x00<<0),  /* Mapped To PORTA */
//  PORTCFG_VP0MAP_PORTB_gc = (0x01<<0),  /* Mapped To PORTB */
//  PORTCFG_VP0MAP_PORTC_gc = (0x02<<0),  /* Mapped To PORTC */
//  PORTCFG_VP0MAP_PORTD_gc = (0x03<<0),  /* Mapped To PORTD */
//  PORTCFG_VP0MAP_PORTE_gc = (0x04<<0),  /* Mapped To PORTE */
//  PORTCFG_VP0MAP_PORTF_gc = (0x05<<0),  /* Mapped To PORTF */
//  PORTCFG_VP0MAP_PORTG_gc = (0x06<<0),  /* Mapped To PORTG */
//  PORTCFG_VP0MAP_PORTH_gc = (0x07<<0),  /* Mapped To PORTH */
//} PORTCFG_VP0MAP_t;

/* Virtual Port Mapping */
//typedef enum PORTCFG_VP1MAP_enum
//{
//  PORTCFG_VP1MAP_PORTA_gc = (0x00<<4),  /* Mapped To PORTA */
//  PORTCFG_VP1MAP_PORTB_gc = (0x01<<4),  /* Mapped To PORTB */
//  PORTCFG_VP1MAP_PORTC_gc = (0x02<<4),  /* Mapped To PORTC */
//  PORTCFG_VP1MAP_PORTD_gc = (0x03<<4),  /* Mapped To PORTD */
//  PORTCFG_VP1MAP_PORTE_gc = (0x04<<4),  /* Mapped To PORTE */
//  PORTCFG_VP1MAP_PORTF_gc = (0x05<<4),  /* Mapped To PORTF */
//  PORTCFG_VP1MAP_PORTG_gc = (0x06<<4),  /* Mapped To PORTG */
//  PORTCFG_VP1MAP_PORTH_gc = (0x07<<4),  /* Mapped To PORTH */
//} PORTCFG_VP1MAP_t;

/* Virtual Port Mapping */
//typedef enum PORTCFG_VP2MAP_enum
//{
//  PORTCFG_VP2MAP_PORTJ_gc = (0x08<<0),  /* Mapped To PORTJ */
//  PORTCFG_VP2MAP_PORTK_gc = (0x09<<0),  /* Mapped To PORTK */
//  PORTCFG_VP2MAP_PORTL_gc = (0x0A<<0),  /* Mapped To PORTL */
//  PORTCFG_VP2MAP_PORTM_gc = (0x0B<<0),  /* Mapped To PORTM */
//  PORTCFG_VP2MAP_PORTN_gc = (0x0C<<0),  /* Mapped To PORTN */
//  PORTCFG_VP2MAP_PORTP_gc = (0x0D<<0),  /* Mapped To PORTP */
//  PORTCFG_VP2MAP_PORTQ_gc = (0x0E<<0),  /* Mapped To PORTQ */
//  PORTCFG_VP2MAP_PORTR_gc = (0x0F<<0),  /* Mapped To PORTR */
//} PORTCFG_VP2MAP_t;

/* Virtual Port Mapping */
//typedef enum PORTCFG_VP3MAP_enum
//{
//  PORTCFG_VP3MAP_PORTJ_gc = (0x08<<4),  /* Mapped To PORTJ */
//  PORTCFG_VP3MAP_PORTK_gc = (0x09<<4),  /* Mapped To PORTK */
//  PORTCFG_VP3MAP_PORTL_gc = (0x0A<<4),  /* Mapped To PORTL */
//  PORTCFG_VP3MAP_PORTM_gc = (0x0B<<4),  /* Mapped To PORTM */
//  PORTCFG_VP3MAP_PORTN_gc = (0x0C<<4),  /* Mapped To PORTN */
//  PORTCFG_VP3MAP_PORTP_gc = (0x0D<<4),  /* Mapped To PORTP */
//  PORTCFG_VP3MAP_PORTQ_gc = (0x0E<<4),  /* Mapped To PORTQ */
//  PORTCFG_VP3MAP_PORTR_gc = (0x0F<<4),  /* Mapped To PORTR */
//} PORTCFG_VP3MAP_t;

//#define Assert (exp) 
//cbi();
#define ARTEFACTS_SPI              SPIF
#define ARTEFACTS_SPI_PORT            PORTF
#define ARTEFACTS_SLOTS_NUM            5

//#define HW_SLOT_CHIPS_SELECT_PIN_START      Driver_IO::PK0
//#define HW_SLOT_ARTEFACT_LEDS_PIN_START      Driver_IO::PH0
/*
typedef Driver_IO_Pin(PORTK, 0) ArtefactsPinSS00;
typedef Driver_IO_Pin(PORTK, 1) ArtefactsPinSS01;
typedef Driver_IO_Pin(PORTK, 2) ArtefactsPinSS02;
typedef Driver_IO_Pin(PORTK, 3) ArtefactsPinSS03;
typedef Driver_IO_Pin(PORTK, 4) ArtefactsPinSS04;
typedef Driver_IO_Pin(PORTH, 0) ArtefactsPinLED00;
typedef Driver_IO_Pin(PORTH, 1) ArtefactsPinLED01;
typedef Driver_IO_Pin(PORTH, 2) ArtefactsPinLED02;
typedef Driver_IO_Pin(PORTH, 3) ArtefactsPinLED03;
typedef Driver_IO_Pin(PORTH, 4) ArtefactsPinLED04;
*/

typedef Driver_IO_Pin(PORTH, 0) ArtefactsPinSS00;
typedef Driver_IO_Pin(PORTH, 1) ArtefactsPinLED00;
typedef Driver_IO_Pin(PORTK, 0) ArtefactsPinSS01;
typedef Driver_IO_Pin(PORTK, 1) ArtefactsPinLED01;
typedef Driver_IO_Pin(PORTK, 2) ArtefactsPinSS02;
typedef Driver_IO_Pin(PORTK, 3) ArtefactsPinLED02;
typedef Driver_IO_Pin(PORTK, 4) ArtefactsPinSS03;
typedef Driver_IO_Pin(PORTK, 5) ArtefactsPinLED03;
typedef Driver_IO_Pin(PORTK, 6) ArtefactsPinSS04;
typedef Driver_IO_Pin(PORTK, 7) ArtefactsPinLED04;

typedef Driver_IO_Pin(PORTB, 6) VA_SDN;



typedef Driver_IO_Pin(PORTF, 7) ArtefactsClkPin;
typedef Driver_IO_Pin(PORTF, 6) ArtefactsMisoPin;
typedef Driver_IO_Pin(PORTF, 5) ArtefactsMosiPin;
typedef Driver_IO_Pin(PORTF, 4) ArtefactsSSPin;//Ёто говно должно быть настроено на выход!!!//иначе не работает бло!!!!

/*neiverio
typedef Ph0 ArtefactsPinSS00;
typedef Ph1 ArtefactsPinLED00;
typedef Pk0 ArtefactsPinSS01;
typedef Pk1 ArtefactsPinLED01;
typedef Pk2 ArtefactsPinSS02;
typedef Pk3 ArtefactsPinLED02;
typedef Pk4 ArtefactsPinSS03;
typedef Pk5 ArtefactsPinLED03;
typedef Pk6 ArtefactsPinSS04;
typedef Pk7 ArtefactsPinLED04;



typedef Pf7 ArtefactsClkPin;
typedef Pf6 ArtefactsMisoPin;
typedef Pf5 ArtefactsMosiPin;
typedef Pf4 ArtefactsSSPin;//Ёто говно должно быть настроено на выход!!!//иначе не работает бло!!!!
*/


#define TIMER_DAC                TCC0
#define TIMER_DEATH_SOUND            TCC1
#define TIMER_PSY                TCD1
#define TIMER_PSY_VECTOR            TCD1_OVF_vect

#define AR1010_TWI                TWIC
#define AR1010_SLAVE_ADDRESS          0x20
#define AR1010_TWI_SPEED_KHZ          400

#define ExternalEEPROM_TWI            TWIC
#define ExternalEEPROM_SLAVE_ADDRESS      0b10100000
#define ExternalEEPROM_SPEED_KHZ        400

#define UsableItem_TWI              TWIE
#define UsableItem_SLAVE_ADDRESS        0b10100000
#define UsableItem_SPEED_KHZ          400

typedef Driver_IO_TWI(UsableItem_TWI, UsableItem_SLAVE_ADDRESS, UsableItem_SPEED_KHZ) UsableItemTWI;
typedef Driver_IO_TWI(ExternalEEPROM_TWI, ExternalEEPROM_SLAVE_ADDRESS, ExternalEEPROM_SPEED_KHZ) ExternalEEPROMTWI;
typedef Driver_IO_TWI(AR1010_TWI, AR1010_SLAVE_ADDRESS, AR1010_TWI_SPEED_KHZ) Ar1010TWI;




typedef Driver_IO_Pin(PORTB, 0) vibroPin;
typedef Driver_IO_Pin(PORTH, 3) UsableItemLedPin;
typedef Driver_IO_Pin(PORTH, 2) UsableItemItemConnectedPin;
typedef Driver_IO_Pin(PORTA, 5) StatusLedPin;

typedef Driver_IO_Pin(PORTB, 1) psyPin;
#define SOUND_HIFI_DAC              DACB
#define SOUND_HIFI_DAC_CHANNEL          SOUND_HIFI_DAC.CH0DATAH

#define RFM69_SPI                SPIC
typedef Driver_IO_Pin(PORTC, 4) RFM69SPI_SS_Pin;//ј’“”Ќ√! низз€ убирать, т.к. без него SPI не робить
typedef Driver_IO_Pin(PORTC, 7) RFM69ClkPin;
typedef Driver_IO_Pin(PORTC, 6) RFM69MisoPin;
typedef Driver_IO_Pin(PORTC, 5) RFM69MosiPin;
typedef Driver_IO_Pin(PORTD, 1) RFM69SSPin;
typedef Driver_IO_Pin(PORTD, 0) RFM69Dio5Pin;
TODO("warning RFM69Dio5Pin is bugged!");

typedef Driver_IO_Pin(PORTC, 7) MediaFlashPinClk;
typedef Driver_IO_Pin(PORTC, 6) MediaFlashPinMiso;
typedef Driver_IO_Pin(PORTC, 5) MediaFlashPinMosi;
typedef Driver_IO_Pin(PORTC, 4) MediaFlashPinSS;
typedef Driver_IO_SPI(SPIC, PORTC, 4) MediaFlashSPI;
typedef Driver_IO_SPI(ARTEFACTS_SPI, PORTH, 0) ArtefactFlash00SPI;
typedef Driver_IO_SPI(ARTEFACTS_SPI, PORTK, 0) ArtefactFlash01SPI;
typedef Driver_IO_SPI(ARTEFACTS_SPI, PORTK, 2) ArtefactFlash02SPI;
typedef Driver_IO_SPI(ARTEFACTS_SPI, PORTK, 4) ArtefactFlash03SPI;
typedef Driver_IO_SPI(ARTEFACTS_SPI, PORTK, 6) ArtefactFlash04SPI;


typedef Driver_IO_Pin(PORTA, 0) PinButtonDown_Enter;
//ButtonMenuPin;
typedef Driver_IO_Pin(PORTA, 1) PinButtonRight;
//ButtonSelectPin;
typedef Driver_IO_Pin(PORTA, 2) PinButtonCenter_Menu;
//ButtonUsePin;
typedef Driver_IO_Pin(PORTA, 3) PinButtonLeft;
//ButtonMenuPrevPin;
typedef Driver_IO_Pin(PORTA, 4) PinButtonUp_Esc;
//ButtonMenuPrevPin;





typedef Driver_IO_Pin(PORTD, 2) ChargerPinCE;
typedef Driver_IO_Pin(PORTD, 3) ChargerPinCharging;
typedef Driver_IO_Pin(PORTD, 4) ChargerPinStandby;
typedef Driver_IO_Pin(PORTD, 5) VBUSPin;

typedef Driver_IO_Pin(PORTJ, 7) LcdBacklightInvertedPin;

typedef Driver_IO_Pin(PORTF, 4) LcdPinBacklight;
typedef Driver_IO_Pin(PORTE, 5) LcdPinCLK;//because UART
typedef Driver_IO_Pin(PORTE, 7) LcdPinSDIN;//because UART
typedef Driver_IO_Pin(PORTE, 4) LcdPinDC;
typedef Driver_IO_Pin(PORTE, 3) LcdPinSCE;
typedef Driver_IO_Pin(PORTE, 2) LcdPinRST;

/*
neiverio
typedef Pb0 vibroPin;
typedef Ph3 UsableItemLedPin;
typedef Ph2 UsableItemItemConnectedPin;
typedef Pa5 StatusLedPin;

typedef Pb1 psyPin;
#define SOUND_HIFI_DAC              DACB
#define SOUND_HIFI_DAC_CHANNEL          SOUND_HIFI_DAC.CH0DATAH


#define RFM69_SPI                SPIC
typedef Pc4 RFM69SPI_SS_Pin;//ј’“”Ќ√! низз€ убирать, т.к. без него SPI не робить
typedef Pc7 RFM69ClkPin;
typedef Pc6 RFM69MisoPin;
typedef Pc5 RFM69MosiPin;
typedef Pd1 RFM69SSPin;
typedef Pd0 RFM69Dio5Pin;
TODO("warning RFM69Dio5Pin is bugged!");

typedef Pc7 MediaFlashPinClk;
typedef Pc6 MediaFlashPinMiso;
typedef Pc5 MediaFlashPinMosi;
typedef Pc4 MediaFlashPinSS;
typedef Driver_IO_SPI(SPIC, Pc4) MediaFlashSPI;
typedef Driver_IO_SPI(ARTEFACTS_SPI, Ph0) ArtefactFlash00SPI;
typedef Driver_IO_SPI(ARTEFACTS_SPI, Pk0) ArtefactFlash01SPI;
typedef Driver_IO_SPI(ARTEFACTS_SPI, Pk2) ArtefactFlash02SPI;
typedef Driver_IO_SPI(ARTEFACTS_SPI, Pk4) ArtefactFlash03SPI;
typedef Driver_IO_SPI(ARTEFACTS_SPI, Pk6) ArtefactFlash04SPI;

typedef Pa0 PinButtonDown_Enter;
//ButtonMenuPin;
typedef Pa1 PinButtonRight;
//ButtonSelectPin;
typedef Pa2 PinButtonCenter_Menu;
//ButtonUsePin;
typedef Pa3 PinButtonLeft;
//ButtonMenuPrevPin;
typedef Pa4 PinButtonUp_Esc;
//ButtonMenuPrevPin;


typedef Pd2 ChargerPinCE;
typedef Pd3 ChargerPinCharging;
typedef Pd4 ChargerPinStandby;
typedef Pd5 VBUSPin;

typedef Pj7 LcdBacklightInvertedPin;
typedef Pf4 LcdPinBacklight;
typedef Pe7 LcdPinCLK;
typedef Pe5 LcdPinSDIN;
typedef Pe4 LcdPinDC;
typedef Pe3 LcdPinSCE;
typedef Pe2 LcdPinRST;

//IO::Pe2::IsPinLow();
//IO::Pe0::IsPinLow();
*/
#define LCD_SPI                  SPIE
#define LCD_SPI_PORT              PORTE

#define BATTERY_ADC_CHANNEL            ADCA
#define BATTERY_ADC_PORT            PORTA
#define BATTERY_ADC_PIN              7
//#define BATTERY_ADC_RESULT_REGISTER        BATTERY_ADC_CHANNEL.CH0.RESL
#define BATTERY_ADC_RESULT_REGISTER        BATTERY_ADC_CHANNEL.CH0.RES

/*
using namespace IO;
#define LCD_PIN_CLK                Pe7
#define LCD_PIN_SDIN              Pe5
#define LCD_PIN_DC                Pe4
#define LCD_PIN_SCE                Pe3
#define LCD_PIN_RST                Pe2
#define LCD_SPI                  SPIE
#define LCD_SPI_PORT              PORTE

typedef PinList<LCD_PIN_CLK, LCD_PIN_SDIN, LCD_PIN_DC, LCD_PIN_SCE, LCD_PIN_RST> n3310Pins;
*/







#endif /* PCB_H_ */
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/************************************************************************/
/* Отличия RFM69 от RFM22/23B                                           */
/************************************************************************/
//http://forum.rcdesign.ru/blogs/39565/blog18257.html

//https://github.com/LowPowerLab/RFM69/blob/master/RFM69.cpp

// **********************************************************************************
// Driver definition for HopeRF RFM69W/RFM69HW, Semtech SX1231/1231H
// **********************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CCSA license:
// http://creativecommons.org/licenses/by-sa/3.0/
// 2013-06-14 (C) felix@lowpowerlab.com
// **********************************************************************************
#include "RFM69_HAL.hpp"
#include "RFM69registers.h"
//#include <SPI.h>

volatile uint8_t RFM69::DATA[MAX_DATA_LEN];
volatile uint8_t RFM69::_mode;       // current transceiver state
volatile uint8_t RFM69::DATALEN;
volatile uint8_t RFM69::SENDERID;
volatile uint8_t RFM69::TARGETID; //should match _address
volatile uint8_t RFM69::PAYLOADLEN;
//volatile uint8_t RFM69::ACK_REQUESTED;
//volatile uint8_t RFM69::ACK_RECEIVED; /// Should be polled immediately after sending a packet with ACK request
volatile uint8_t RFM69::RSSI_RAW; //most accurate RSSI during reception (closest to the reception)
volatile int16_t RFM69::RSSI; //most accurate RSSI during reception (closest to the reception)

//volatile uint8_t RFM69::_SIGNAL_POWER;
//volatile uint8_t RFM69::_RXBuffer[PACKET_SIZE];
//volatile uint8_t RFM69::_TXBuffer[PACKET_SIZE];

//RFM69* RFM69::selfPointer;


unsigned char RFM69_SPI_send(unsigned char data)
{
  //  unsigned char tmp=0;
  RFM69_SPI.DATA  = data;
  while (!(RFM69_SPI.STATUS & SPI_IF_bm))
  {
    //    ++tmp;
    //    PORTQ_OUTTGL  = (1<<PIN0_bp);
  }        //Wait Interrupt
  return RFM69_SPI.DATA;
  //  if (tmp == 0)
  //    {
  //    while(1) {};
  //    }
  //  return data;
}
void RFM69_WriteReg(unsigned char addr, unsigned char value)
{
  //RFM69_ACTIVATE;
  radio.select();
  //  select();
  RFM69_SPI_send(addr | 0x80);
  RFM69_SPI_send(value);
  //RFM69_DEACTIVATE;
  radio.unselect();
  //  unselect();
}

//volatile uint8_t SPI_RFM69::_SSPin;
//SPI_RFM69* SPI_RFM69::selfPointer;
SPI_RFM69 SPI;
void SPI_RFM69::select(void)
  {
  //RFM69_ACTIVATE;
  RFM69SSPin::SetOutLow();
  }
void SPI_RFM69::unselect(void)
  {
//  RFM69_DEACTIVATE;
  RFM69SSPin::SetOutHigh();
  }
/*
void SPI_RFM69::initialize(void)
  {

//  SetInput(RFM69_MISO_DDR,    RFM69_MISO_PIN);
//  SetOutput(RFM69_SS_DDR,      RFM69_SS_PIN);
//  SetOutput(RFM69_MOSI_DDR,    RFM69_MOSI_PIN);
//  SetOutput(RFM69_CLK_DDR,    RFM69_CLK_PIN);
//  cbi(RFM69_CLK_PORT,        RFM69_CLK_PIN);
//  SetInput(RFM69_DIO0_DDR,    RFM69_DIO0_PIN);
//  cbi(RFM69_DIO0_DDR,        RFM69_DIO0_PIN);//какого-то члена не работает, если врубить подтяжку....

  IOPort.setDirIn(RFM69_MISO_PORT_t,    RFM69_MISO_PIN);
  IOPort.setDirOut(RFM69_SS_PORT_t,    RFM69_SS_PIN);
  IOPort.setDirOut(RFM69_MOSI_PORT_t,    RFM69_MOSI_PIN);
  IOPort.setDirOut(RFM69_CLK_PORT_t,    RFM69_CLK_PIN);
  IOPort.setOutLow(RFM69_CLK_PORT_t,    RFM69_CLK_PIN);
  IOPort.setDirIn(RFM69_DIO0_PORT_t,    RFM69_DIO0_PIN);
//  IOPort.setOutLow(RFM69_DIO0_PORT_t,    RFM69_DIO0_PIN);


  //            [double CLK]  [enable][DORD] [master][transfer mode][clk prescaller]
  RFM69_SPI.CTRL    = 1<<7      | 1<<6  | 0<<5 | 1<<4 | (0<<3 | 0<<2) | (0<<1 | 0<<0);
//  RFM69_SPI.CTRL  = 0<<7      | 1<<6  | 0<<5 | 1<<4 | (0<<3 | 0<<2) | (1<<1 | 1<<0);
  RFM69_SPI.INTCTRL = SPI_INTLVL_OFF_gc ; // no interrupt
  }
*/
uint8_t SPI_RFM69::transfer(unsigned char data)
  {
  RFM69_SPI.DATA  = data;
  while (!(RFM69_SPI.STATUS & SPI_IF_bm))
  {
    //    ++tmp;
    //    PORTQ_OUTTGL  = (1<<PIN0_bp);
  }        //Wait Interrupt
  return RFM69_SPI.DATA;
  }
//RFM69* RFM69::selfPointer;
#ifdef HUINYA

/*
  Name  : CRC-16 CCITT
  Poly  : 0x1021    x^16 + x^12 + x^5 + 1
  Init  : 0xFFFF
  Revert: false
  XorOut: 0x0000
  Check : 0x29B1 ("123456789")
  MaxLen: 4095 байт (32767 бит) - обнаружение
    одинарных, двойных, тройных и всех нечетных ошибок
*/
/*
const unsigned short Crc16Table[256] = {
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
    0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
    0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
    0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
    0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
    0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
    0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
    0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
    0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
    0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
    0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
    0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
    0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
    0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
    0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
    0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
    0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
    0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
    0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
    0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
    0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
    0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
    0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
    0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};
*/
unsigned short RFM69::Crc16(unsigned char * pcBlock, unsigned short len)
{
    unsigned short crc = 0xFFFF;
 
    while (len--)
        crc = (crc << 8) ^ Crc16Table[(crc >> 8) ^ *pcBlock++];
 
    return crc;
}
unsigned short RFM69::Crc16Update(unsigned short crc, unsigned char data)
    {
    crc = (crc << 8) ^ Crc16Table[(crc >> 8) ^ data];
 
    return crc;
    }

unsigned short RFM69::crc_ccitt_update (unsigned short crc, unsigned char data)
{
  unsigned short t;
  data ^= crc&255;
  data ^= data << 4;
  t = (((unsigned short)data << 8) | ((crc>>8)&255));
  t^=(unsigned char)(data >> 4);
  t^= ((unsigned short)data << 3);
  return t;
}

UNION_UINT16 crc;

bool RFM69::checkCRC(void)
  {
  UNION_UINT16 crc;
  crc.value_int  = 0xFFFF;
  for (unsigned char i=0;i<PACKET_SIZE-2;i++)
    {
//    crc.value_int  = this->crc_ccitt_update(crc.value_int, this->_RXBuffer[i]);
    crc.value_int  = this->Crc16Update(crc.value_int, this->_RXBuffer[i]);
    }
//        sprintf (lcd_buf,"%06d %03d%03d", (unsigned short)crc.value_int, crc.byte_field.h, crc.byte_field.l);
//        LcdString(1,LCD_LINE_4);
  if (crc.byte_field.h == this->_RXBuffer[PACKET_RADIOMARK_CRC16_H] && crc.byte_field.l == this->_RXBuffer[PACKET_RADIOMARK_CRC16_L])
    {
    return true;
    }
  return false;
  }
void RFM69::receivePacket(void)
  {
  uint8_t tmp;
  setMode(RF69_MODE_STANDBY);
  this->select();
  SPI.transfer(REG_FIFO & 0x7f);
  for (uint8_t i= 0; i < PACKET_SIZE; i++)
    {
    _RXBuffer[i] = SPI.transfer(0);
    }
  this->unselect();
  //radio.setMode(RF69_MODE_RX);
//  tmp  = (~readRSSI_RAW());
  this->RSSI_RAW  = readRSSI_RAW();
  tmp = ~this->RSSI_RAW;
  if (tmp > 64)//removing [0..64]
    tmp-=64;
  else
    tmp=0;

  if (tmp >127)
    tmp  = 127;
  _SIGNAL_POWER+=tmp;//filter [(a1+a2)/2]
  if (_SIGNAL_POWER > 0)
    {
    _SIGNAL_POWER >>=1;
    }
      
  }

//bool RFM69::initialize(uint8_t freqBand, uint8_t nodeID, uint8_t networkID)
bool RFM69::initialize(uint8_t nodeID, uint8_t networkID)
{
  SPI.initialize();
  const uint8_t CONFIG[][2] =
  {
    /* 0x01 */ { REG_OPMODE, RF_OPMODE_SEQUENCER_ON | RF_OPMODE_LISTEN_OFF | RF_OPMODE_STANDBY },
//    /* 0x02 */ { REG_DATAMODUL, RF_DATAMODUL_DATAMODE_PACKET | RF_DATAMODUL_MODULATIONTYPE_FSK | RF_DATAMODUL_MODULATIONSHAPING_00 }, //no shaping
    /* 0x02 */ { REG_DATAMODUL, RF_DATAMODUL_DATAMODE_PACKET | RF_DATAMODUL_MODULATIONTYPE_FSK | RF_DATAMODUL_MODULATIONSHAPING_01 }, //no shaping
//    /* 0x03 */ { REG_BITRATEMSB, RF_BITRATEMSB_55555}, //default:4.8 KBPS
//    /* 0x04 */ { REG_BITRATELSB, RF_BITRATELSB_55555}, //FREQ=32MHZ/RF[15:0]
//    /* 0x05 */ { REG_FDEVMSB, RF_FDEVMSB_50000}, //default:5khz, (FDEV + BitRate/2 <= 500Khz)
//    /* 0x06 */ { REG_FDEVLSB, RF_FDEVLSB_50000},
//    /* 0x07 */ { REG_FRFMSB, (freqBand==RF69_315MHZ ? RF_FRFMSB_315 : (freqBand==RF69_433MHZ ? RF_FRFMSB_433 : (freqBand==RF69_868MHZ ? RF_FRFMSB_868 : RF_FRFMSB_915))) },
//    /* 0x08 */ { REG_FRFMID, (freqBand==RF69_315MHZ ? RF_FRFMID_315 : (freqBand==RF69_433MHZ ? RF_FRFMID_433 : (freqBand==RF69_868MHZ ? RF_FRFMID_868 : RF_FRFMID_915))) },
//    /* 0x09 */ { REG_FRFLSB, (freqBand==RF69_315MHZ ? RF_FRFLSB_315 : (freqBand==RF69_433MHZ ? RF_FRFLSB_433 : (freqBand==RF69_868MHZ ? RF_FRFLSB_868 : RF_FRFLSB_915))) },

//    /* 0x03 */ { REG_BITRATEMSB, RFM69_RF_BITRATEMSB_FROM_BITRATE(55555)},
//    /* 0x04 */ { REG_BITRATELSB, RFM69_RF_BITRATELSB_FROM_BITRATE(55555)},
//    /* 0x03 */ { REG_BITRATEMSB, RFM69_RF_BITRATEMSB_FROM_BITRATE(64000)},
//    /* 0x04 */ { REG_BITRATELSB, RFM69_RF_BITRATELSB_FROM_BITRATE(64000)},
    /* 0x03 */ { REG_BITRATEMSB, RFM69_RF_BITRATEMSB_FROM_BITRATE(128000)},
    /* 0x04 */ { REG_BITRATELSB, RFM69_RF_BITRATELSB_FROM_BITRATE(128000)},
    /* 0x05 */ { REG_FDEVMSB, RFM69_FDEVMSB_FROM_FREQ(50000)}, //default:5khz, (FDEV + BitRate/2 <= 500Khz)
    /* 0x06 */ { REG_FDEVLSB, RFM69_FDEVLSB_FROM_FREQ(50000)},
    /* 0x07 */ { REG_FRFMSB, RFM69_FRFMSB_FROM_FREQ(RFM69_FREQUENCY) },
    /* 0x08 */ { REG_FRFMID, RFM69_FRFMID_FROM_FREQ(RFM69_FREQUENCY) },
    /* 0x09 */ { REG_FRFLSB, RFM69_FRFLSB_FROM_FREQ(RFM69_FREQUENCY) },
    
    // looks like PA1 and PA2 are not implemented on RFM69W, hence the max output power is 13dBm
    // +17dBm and +20dBm are possible on RFM69HW
    // +13dBm formula: Pout=-18+OutputPower (with PA0 or PA1**)
    // +17dBm formula: Pout=-14+OutputPower (with PA1 and PA2)**
    // +20dBm formula: Pout=-11+OutputPower (with PA1 and PA2)** and high power PA settings (section 3.3.7 in datasheet)
    ///* 0x11 */ { REG_PALEVEL, RF_PALEVEL_PA0_ON | RF_PALEVEL_PA1_OFF | RF_PALEVEL_PA2_OFF | RF_PALEVEL_OUTPUTPOWER_11111},
    ///* 0x13 */ { REG_OCP, RF_OCP_ON | RF_OCP_TRIM_95 }, //over current protection (default is 95mA)
    
    ///* 0x18*/ { REG_LNA,  RF_LNA_ZIN_200 | RF_LNA_CURRENTGAIN }, //as suggested by mav here: http://lowpowerlab.com/forum/index.php/topic,296.msg1571.html
    
    // RXBW defaults are { REG_RXBW, RF_RXBW_DCCFREQ_010 | RF_RXBW_MANT_24 | RF_RXBW_EXP_5} (RxBw: 10.4khz)
    /* 0x19 */ { REG_RXBW, RF_RXBW_DCCFREQ_010 | RF_RXBW_MANT_16 | RF_RXBW_EXP_2 }, //(BitRate < 2 * RxBw)
    /* 0x25 */ { REG_DIOMAPPING1, RF_DIOMAPPING1_DIO0_01 }, //DIO0 is the only IRQ we're using
    /* 0x29 */ { REG_RSSITHRESH, 220 }, //must be set to dBm = (-Sensitivity / 2) - default is 0xE4=228 so -114dBm
    ///* 0x2d */ { REG_PREAMBLELSB, RF_PREAMBLESIZE_LSB_VALUE } // default 3 preamble bytes 0xAAAAAA
//    /* 0x2e */ { REG_SYNCCONFIG, RF_SYNC_ON | RF_SYNC_FIFOFILL_AUTO | RF_SYNC_SIZE_2 | RF_SYNC_TOL_0 },
//    /* 0x2f */ { REG_SYNCVALUE1, 0x2D },      //attempt to make this compatible with sync1 byte of RFM12B lib
//    /* 0x30 */ { REG_SYNCVALUE2, networkID }, //NETWORK ID

    /* 0x2e */ { REG_SYNCCONFIG, RF_SYNC_ON | RF_SYNC_FIFOFILL_AUTO | RF_SYNC_SIZE_4 | RF_SYNC_TOL_0 },
    /* 0x2f */ { REG_SYNCVALUE1, 0x59 },      //attempt to make this compatible with sync1 byte of RFM12B lib
    /* 0x30 */ { REG_SYNCVALUE2, 0xa6 }, //NETWORK ID
    /* 0x30 */ { REG_SYNCVALUE3, 0xa6 },
    /* 0x30 */ { REG_SYNCVALUE4, 0x65 },


//    /* 0x37 */ { REG_PACKETCONFIG1, RF_PACKET1_FORMAT_VARIABLE | RF_PACKET1_DCFREE_OFF | RF_PACKET1_CRC_ON | RF_PACKET1_CRCAUTOCLEAR_ON | RF_PACKET1_ADRSFILTERING_OFF },
//    /* 0x38 */ { REG_PAYLOADLENGTH, 66 }, //in variable length mode: the max frame size, not used in TX
//    /* 0x37 */ { REG_PACKETCONFIG1, RF_PACKET1_FORMAT_FIXED | RF_PACKET1_DCFREE_OFF | RF_PACKET1_CRC_ON  | RF_PACKET1_CRCAUTOCLEAR_ON  | RF_PACKET1_ADRSFILTERING_OFF },
    /* 0x37 */ { REG_PACKETCONFIG1, RF_PACKET1_FORMAT_FIXED | RF_PACKET1_DCFREE_OFF | RF_PACKET1_CRC_OFF | RF_PACKET1_CRCAUTOCLEAR_OFF | RF_PACKET1_ADRSFILTERING_OFF },
//    /* 0x37 */ { REG_PACKETCONFIG1, RF_PACKET1_FORMAT_FIXED | RF_PACKET1_DCFREE_OFF | RF_PACKET1_CRC_ON  | RF_PACKET1_CRCAUTOCLEAR_OFF | RF_PACKET1_ADRSFILTERING_OFF },
    /* 0x38 */ { REG_PAYLOADLENGTH, 12 }, //in variable length mode: the max frame size, not used in TX
    //* 0x39 */ { REG_NODEADRS, nodeID }, //turned off because we're not using address filtering
    /* 0x3C */ { REG_FIFOTHRESH, RF_FIFOTHRESH_TXSTART_FIFONOTEMPTY | RF_FIFOTHRESH_VALUE }, //TX on FIFO not empty
    /* 0x3d */ { REG_PACKETCONFIG2, RF_PACKET2_RXRESTARTDELAY_2BITS | RF_PACKET2_AUTORXRESTART_ON | RF_PACKET2_AES_OFF }, //RXRESTARTDELAY must match transmitter PA ramp-down time (bitrate dependent)
    /* 0x6F */ { REG_TESTDAGC, RF_DAGC_IMPROVED_LOWBETA0 }, // run DAGC continuously in RX mode, recommended default for AfcLowBetaOn=0
    {255, 0}
  };

//  pinMode(_slaveSelectPin, OUTPUT);
  
//  SPI.setDataMode(SPI_MODE0);
//  SPI.setBitOrder(MSBFIRST);
//  SPI.setClockDivider(SPI_CLOCK_DIV2); //max speed, except on Due which can run at system clock speed
//  SPI.begin();
  
  do writeReg(REG_SYNCVALUE1, 0xaa); while (readReg(REG_SYNCVALUE1) != 0xaa);
  do writeReg(REG_SYNCVALUE1, 0x55); while (readReg(REG_SYNCVALUE1) != 0x55);
  
  for (uint8_t i = 0; CONFIG[i][0] != 255; i++)
  writeReg(CONFIG[i][0], CONFIG[i][1]);

//  RFM69_SetFrequencyCarrier(432750592);

  // Encryption is persistent between resets and can trip you up during debugging.
  // Disable it during initialization so we always start from a known state.
  encrypt(0);

  setHighPower(_isRFM69HW); //called regardless if it's a RFM69W or RFM69HW
  setMode(RF69_MODE_STANDBY);
  while ((readReg(REG_IRQFLAGS1) & RF_IRQFLAGS1_MODEREADY) == 0x00); // Wait for ModeReady
/*
  //attachInterrupt(0, RFM69::isr0, RISING);
    {
    PORTD.PIN3CTRL  = PORT_OPC_TOTEM_gc | PORT_ISC_RISING_gc;
    PORTD.INTCTRL  = (PORTD.INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) | PORT_INT1LVL_OFF_gc | PORT_INT0LVL_MED_gc;
    PORTD.INT0MASK  = 1<<RFM69_DIO0_PIN;
//    PORTD.IN    |= 1<<RFM69_DIO0_PIN;
    }
*/
//  selfPointer = this;
  _address = nodeID;
  return true;
}
#endif
void RFM69::setFrequency(uint32_t FRF)
{
  writeReg(REG_FRFMSB, FRF >> 16);
  writeReg(REG_FRFMID, FRF >> 8);
  writeReg(REG_FRFLSB, FRF);
}

void RFM69::setMode(uint8_t newMode)
{
  if (newMode == _mode) return; //TODO: can remove this?

  switch (newMode) {
    case RF69_MODE_TX:
    writeReg(REG_OPMODE, (readReg(RFM69_REGISTER_01_OPMODE) & 0xE3) | RF_OPMODE_TRANSMITTER);
    if (_isRFM69HW) setHighPowerRegs(true);
    break;
    case RF69_MODE_RX:
    writeReg(REG_OPMODE, (readReg(RFM69_REGISTER_01_OPMODE) & 0xE3) | RF_OPMODE_RECEIVER);
    if (_isRFM69HW) setHighPowerRegs(false);
    break;
    case RF69_MODE_SYNTH:
    writeReg(REG_OPMODE, (readReg(RFM69_REGISTER_01_OPMODE) & 0xE3) | RF_OPMODE_SYNTHESIZER);
    break;
    case RF69_MODE_STANDBY:
    writeReg(REG_OPMODE, (readReg(RFM69_REGISTER_01_OPMODE) & 0xE3) | RF_OPMODE_STANDBY);
    break;
    case RF69_MODE_SLEEP:
    writeReg(REG_OPMODE, (readReg(RFM69_REGISTER_01_OPMODE) & 0xE3) | RF_OPMODE_SLEEP);
    break;
    default: return;
  }

  // we are using packet mode, so this check is not really needed
  // but waiting for mode ready is necessary when going from sleep because the FIFO may not be immediately available from previous mode
  while (_mode == RF69_MODE_SLEEP && (readReg(REG_IRQFLAGS1) & RF_IRQFLAGS1_MODEREADY) == 0x00); // Wait for ModeReady

  _mode = newMode;
}

void RFM69::modeSleep() {
  setMode(RF69_MODE_SLEEP);
}

void RFM69::setAddress(uint8_t addr)
{
  _address = addr;
  writeReg(REG_NODEADRS, _address);
}

// set output power: 0=min, 31=max
// this results in a "weaker" transmitted signal, and directly results in a lower RSSI at the receiver
void RFM69::setPowerLevel(uint8_t powerLevel)
{
  _powerLevel = powerLevel;
  //writeReg(REG_PALEVEL, (readReg(REG_PALEVEL) & 0xE0) | (_powerLevel > 31 ? 31 : _powerLevel));
  if (powerLevel > 31)
    powerLevel  = 31;
  writeReg(REG_PALEVEL, (readReg(REG_PALEVEL) & 0xE0) | powerLevel );
}

bool RFM69::canSend() //!!! Очень непонятно НАХЕРА она ваще нужна!!!
{
//  if (_mode == RF69_MODE_RX && PAYLOADLEN == 0 && readRSSI() < CSMA_LIMIT) //if signal stronger than -100dBm is detected assume channel activity
  if (_mode == RF69_MODE_RX && PAYLOADLEN == 0) //if signal stronger than -100dBm is detected assume channel activity
  {
    setMode(RF69_MODE_STANDBY);
    return true;
  }
  return false;
}

//void RFM69::send(uint8_t toAddress, const void* buffer, uint8_t bufferSize, bool requestACK)
void RFM69::send(uint8_t toAddress, const void* buffer, uint8_t bufferSize)
{
  writeReg(REG_PACKETCONFIG2, (readReg(REG_PACKETCONFIG2) & 0xFB) | RF_PACKET2_RXRESTART); // avoid RX deadlocks
  while (!canSend()) receiveDone();
//  sendFrame(toAddress, buffer, bufferSize, requestACK, false);
  sendFrame(toAddress, buffer, bufferSize);
}

/*
// to increase the chance of getting a packet across, call this function instead of send
// and it handles all the ACK requesting/retrying for you :)
// The only twist is that you have to manually listen to ACK requests on the other side and send back the ACKs
// The reason for the semi-automaton is that the lib is ingterrupt driven and
// requires user action to read the received data and decide what to do with it
// replies usually take only 5-8ms at 50kbps@915Mhz
bool RFM69::sendWithRetry(uint8_t toAddress, const void* buffer, uint8_t bufferSize, uint8_t retries, uint8_t retryWaitTime) {
//  long sentTime;
  for (uint8_t i=0; i<=retries; i++)
  {
    send(toAddress, buffer, bufferSize, true);
//    sentTime = millis();
//    while (millis()-sentTime<retryWaitTime)
    {
      if (ACKReceived(toAddress))
      {
        //Serial.print(" ~ms:");Serial.print(millis()-sentTime);
        return true;
      }
    delay_ms(15);
    }
    //Serial.print(" RETRY#");Serial.println(i+1);
  }
  return false;
}
/// Should be polled immediately after sending a packet with ACK request
bool RFM69::ACKReceived(uint8_t fromNodeID) {
  if (receiveDone())
  return (SENDERID == fromNodeID || fromNodeID == RF69_BROADCAST_ADDR) && ACK_RECEIVED;
  return false;
}
/// Should be called immediately after reception in case sender wants ACK
void RFM69::sendACK(const void* buffer, uint8_t bufferSize) {
  uint8_t sender = SENDERID;
  while (!canSend()) receiveDone();
  sendFrame(sender, buffer, bufferSize, false, true);
}
*/


//void RFM69::sendFrame(uint8_t toAddress, const void* buffer, uint8_t bufferSize, bool requestACK, bool sendACK)
void RFM69::sendFrame(uint8_t toAddress, const void* buffer, uint8_t bufferSize)
{
  setMode(RF69_MODE_STANDBY); //turn off receiver to prevent reception while filling fifo
  while ((readReg(REG_IRQFLAGS1) & RF_IRQFLAGS1_MODEREADY) == 0x00); // Wait for ModeReady
  writeReg(REG_DIOMAPPING1, RF_DIOMAPPING1_DIO0_00); // DIO0 is "Packet Sent"
  if (bufferSize > MAX_DATA_LEN) bufferSize = MAX_DATA_LEN;

  //write to FIFO
  select();
  SPI.transfer(REG_FIFO | 0x80);
  SPI.transfer(bufferSize + 3);
  SPI.transfer(toAddress);
  SPI.transfer(_address);
  
  //control byte
//  if (sendACK)
//  SPI.transfer(0x80);
//  else if (requestACK)
//  SPI.transfer(0x40);
//  else
  // SPI.transfer(0x00);
  
  for (uint8_t i = 0; i < bufferSize; i++)
  SPI.transfer(((uint8_t*)buffer)[i]);
  unselect();

  /* no need to wait for transmit mode to be ready since its handled by the radio */
  setMode(RF69_MODE_TX);
//  while (digitalRead(_interruptPin) == 0); //wait for DIO0 to turn HIGH signalling transmission finish
//  while ((RFM69_DIO0_IN & 1<<RFM69_DIO0_PIN) == 0); //wait for DIO0 to turn HIGH signalling transmission finish
  //while (HAL.IO.IsPinLow(RFM69_DIO5_PIN_HAL)); //wait for DIO0 to turn HIGH signalling transmission finish
  while(RFM69Dio5Pin::IsPinLow()); //wait for DIO0 to turn HIGH signalling transmission finish
  //while (readReg(REG_IRQFLAGS2) & RF_IRQFLAGS2_PACKETSENT == 0x00); // Wait for ModeReady
  setMode(RF69_MODE_STANDBY);
}

/*
void RFM69::interruptHandler() {
  //pinMode(4, OUTPUT);
  //digitalWrite(4, 1);
//  ++aaaHIGH;
  if (_mode == RF69_MODE_RX && (readReg(REG_IRQFLAGS2) & RF_IRQFLAGS2_PAYLOADREADY))
  {
    setMode(RF69_MODE_STANDBY);
    select();
    SPI.transfer(REG_FIFO & 0x7f);
    PAYLOADLEN  = PACKET_SIZE;
    DATALEN    = PACKET_SIZE;
//    PAYLOADLEN = SPI.transfer(0);
//    PAYLOADLEN = PAYLOADLEN > 66 ? 66 : PAYLOADLEN; //precaution
//    if (PAYLOADLEN > 66)
//      PAYLOADLEN  = 66;
//    TARGETID = SPI.transfer(0);
//    if(!(_promiscuousMode || TARGETID==_address || TARGETID==RF69_BROADCAST_ADDR)) //match this node's address, or broadcast address or anything in promiscuous mode
//    if(!(_promiscuousMode ) //match this node's address, or broadcast address or anything in promiscuous mode
//    {
//      PAYLOADLEN = 0;
//      unselect();
//      //digitalWrite(4, 0);
//      return;
//    }
//    DATALEN = PAYLOADLEN;
//    DATALEN = PAYLOADLEN - 3;
//    SENDERID = SPI.transfer(0);
//    uint8_t CTLbyte = SPI.transfer(0);
    
//    ACK_RECEIVED = CTLbyte & 0x80; //extract ACK-requested flag
//    ACK_REQUESTED = CTLbyte & 0x40; //extract ACK-received flag
    
    for (uint8_t i= 0; i < DATALEN; i++)
    {
      DATA[i] = SPI.transfer(0);
    }
    unselect();
    setMode(RF69_MODE_RX);
  }
  RSSI_RAW  = readRSSI_RAW();
  RSSI = -RSSI_RAW;
  RSSI >>= 1;
  //RSSI = readRSSI();
  //digitalWrite(4, 0);
}
*/

//void RFM69::isr0() { selfPointer->interruptHandler(); }
void RFM69::receiveBegin() {
  DATALEN = 0;
  SENDERID = 0;
  TARGETID = 0;
  PAYLOADLEN = 0;
//  ACK_REQUESTED = 0;
//  ACK_RECEIVED = 0;
  RSSI = 0;
  if (readReg(REG_IRQFLAGS2) & RF_IRQFLAGS2_PAYLOADREADY)
    {
    writeReg(REG_PACKETCONFIG2, (readReg(REG_PACKETCONFIG2) & 0xFB) | RF_PACKET2_RXRESTART); // avoid RX deadlocks
    }
  writeReg(REG_DIOMAPPING1, RF_DIOMAPPING1_DIO0_01); //set DIO0 to "PAYLOADREADY" in receive mode
  //writeReg(REG_DIOMAPPING1, 0);
  setMode(RF69_MODE_RX);
}

bool RFM69::receiveDone() {
  // ATOMIC_BLOCK(ATOMIC_FORCEON)
  // {
  //noInterrupts(); //re-enabled in unselect() via setMode() or via receiveBegin()
//  cli();
  if (_mode == RF69_MODE_RX && PAYLOADLEN>0)
  {
    setMode(RF69_MODE_STANDBY); //enables interrupts
//    sei();
    return true;
  }
  else if (_mode == RF69_MODE_RX)  //already in RX no payload yet
  {
    //interrupts(); //explicitly re-enable interrupts
//    sei();
    return false;
  }
  this->receiveBegin();
//  sei();
  return false;
  //}
}

// To enable encryption: radio.encrypt("ABCDEFGHIJKLMNOP");
// To disable encryption: radio.encrypt(null) or radio.encrypt(0)
// KEY HAS TO BE 16 bytes !!!
void RFM69::encrypt(const char* key) {
  setMode(RF69_MODE_STANDBY);
  if (key!=0)
  {
    select();
    SPI.transfer(REG_AESKEY1 | 0x80);
    for (uint8_t i = 0; i<16; i++)
    SPI.transfer(key[i]);
    unselect();
  }
  writeReg(REG_PACKETCONFIG2, (readReg(REG_PACKETCONFIG2) & 0xFE) | (key ? 1 : 0));
}
/*
int RFM69::readRSSI(bool forceTrigger) {
  int rssi = 0;
  if (forceTrigger)
  {
    //RSSI trigger not needed if DAGC is in continuous mode
    writeReg(REG_RSSICONFIG, RF_RSSI_START);
    while ((readReg(REG_RSSICONFIG) & RF_RSSI_DONE) == 0x00); // Wait for RSSI_Ready
  }
  rssi = -readReg(REG_RSSIVALUE);
  rssi >>= 1;
  return rssi;
}
*/
volatile uint8_t RFM69::readRSSI_RAW(bool forceTrigger)
  {
  if (forceTrigger)
  {
    //RSSI trigger not needed if DAGC is in continuous mode
    writeReg(REG_RSSICONFIG, RF_RSSI_START);
    while ((readReg(REG_RSSICONFIG) & RF_RSSI_DONE) == 0x00); // Wait for RSSI_Ready
  }
  return readReg(REG_RSSIVALUE);
  }

uint8_t RFM69::readReg(uint8_t addr)
{
  select();
  SPI.transfer(addr & 0x7F);
  uint8_t regval = SPI.transfer(0);
  unselect();
  return regval;
}

void RFM69::writeReg(uint8_t addr, uint8_t value)
{
  select();
  SPI.transfer(addr | 0x80);
  SPI.transfer(value);
  unselect();
}

/// Select the transceiver
void RFM69::select()
  {
  //noInterrupts();
//  cli();
  //digitalWrite(_slaveSelectPin, LOW);
  SPI.select();
  }

/// UNselect the transceiver chip
void RFM69::unselect()
  {
  //digitalWrite(_slaveSelectPin, HIGH);
  SPI.unselect();
  //interrupts();
//  sei();
  }

// ON  = disable filtering to capture all frames on network
// OFF = enable node+broadcast filtering to capture only frames sent to this/broadcast address
void RFM69::promiscuous(bool onOff) {
  _promiscuousMode=onOff;
  //writeReg(REG_PACKETCONFIG1, (readReg(REG_PACKETCONFIG1) & 0xF9) | (onOff ? RF_PACKET1_ADRSFILTERING_OFF : RF_PACKET1_ADRSFILTERING_NODEBROADCAST));
}

void RFM69::setHighPower(bool onOff) {
  _isRFM69HW = onOff;
  writeReg(REG_OCP, _isRFM69HW ? RF_OCP_OFF : RF_OCP_ON);
  if (_isRFM69HW) //turning ON
    writeReg(REG_PALEVEL, (readReg(REG_PALEVEL) & 0x1F) | RF_PALEVEL_PA1_ON | RF_PALEVEL_PA2_ON); //enable P1 & P2 amplifier stages
  else
    writeReg(REG_PALEVEL, RF_PALEVEL_PA0_ON | RF_PALEVEL_PA1_OFF | RF_PALEVEL_PA2_OFF | _powerLevel); //enable P0 only
}

void RFM69::setHighPowerRegs(bool onOff)
  {
//  writeReg(REG_TESTPA1, onOff ? 0x5D : 0x55);
//  writeReg(REG_TESTPA2, onOff ? 0x7C : 0x70);
  if (onOff)
    {
    writeReg(REG_TESTPA1, 0x5D);
    writeReg(REG_TESTPA2, 0x7C);
    }
  else
    {
    writeReg(REG_TESTPA1, 0x55);
    writeReg(REG_TESTPA2, 0x70);
    }
  }
/*
void RFM69::setCS(uint8_t newSPISlaveSelect) {
  _slaveSelectPin = newSPISlaveSelect;
  pinMode(_slaveSelectPin, OUTPUT);
}

//for debugging
void RFM69::readAllRegs()
{
  uint8_t regVal;
  
  for (uint8_t regAddr = 1; regAddr <= 0x4F; regAddr++)
  {
    select();
    SPI.transfer(regAddr & 0x7f);  // send address + r/w bit
    regVal = SPI.transfer(0);
    unselect();

    Serial.print(regAddr, HEX);
    Serial.print(" - ");
    Serial.print(regVal,HEX);
    Serial.print(" - ");
    Serial.println(regVal,BIN);
  }
  unselect();
}

uint8_t RFM69::readTemperature(uint8_t calFactor)  //returns centigrade
{
  setMode(RF69_MODE_STANDBY);
  writeReg(REG_TEMP1, RF_TEMP1_MEAS_START);
  while ((readReg(REG_TEMP1) & RF_TEMP1_MEAS_RUNNING)) Serial.print('*');
  return ~readReg(REG_TEMP2) + COURSE_TEMP_COEF + calFactor; //'complement'corrects the slope, rising temp = rising val
}                               // COURSE_TEMP_COEF puts reading in the ballpark, user can add additional correction
*/

void RFM69::rcCalibration()
{
  writeReg(REG_OSC1, RF_OSC1_RCCAL_START);
  while ((readReg(REG_OSC1) & RF_OSC1_RCCAL_DONE) == 0x00);
}

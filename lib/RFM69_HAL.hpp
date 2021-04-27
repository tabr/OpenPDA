#ifndef RFM_69_HAL_H
#define RFM_69_HAL_H
// **********************************************************************************
// Driver definition for HopeRF RFM69W/RFM69HW, Semtech SX1231/1231H
// **********************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// http://creativecommons.org/licenses/by-sa/3.0/
// 2013-06-14 (C) felix@lowpowerlab.com
// **********************************************************************************
//#include <Arduino.h>            //assumes Arduino IDE v1.0 or greater




//мои происки!!!
#define MHZ										1000000
#define RFM69_CONSTANTS_FXO						(32*MHZ)
//#define RFM69_CONSTANTS_FSTREP					61 // или "61,03515625" ??!
#define RFM69_CONSTANTS_FSTREP					61.03515625
//#define RFM69_ACTIVATE		cbi(RFM69_SS_PORT, RFM69_SS_PIN);
//#define RFM69_DEACTIVATE	sbi(RFM69_SS_PORT, RFM69_SS_PIN);
//#define RFM69_ACTIVATE		HAL.IO.setOutLow(RFM69_SS_PIN_HAL);
//#define RFM69_DEACTIVATE	HAL.IO.setOutHigh(RFM69_SS_PIN_HAL);



#define RFM69_RF_BITRATEMSB_FROM_BITRATE(BITRATE) (((RFM69_CONSTANTS_FXO/(BITRATE))>>8)&0xFF)
#define RFM69_RF_BITRATELSB_FROM_BITRATE(BITRATE) (((RFM69_CONSTANTS_FXO/(BITRATE))>>0)&0xFF)

#define RFM69_FRFMSB_FROM_FREQ(FREQ) ((((uint32_t)((FREQ)/RFM69_CONSTANTS_FSTREP))>>16)&0xFF)
#define RFM69_FRFMID_FROM_FREQ(FREQ) ((((uint32_t)((FREQ)/RFM69_CONSTANTS_FSTREP))>>8)&0xFF)
#define RFM69_FRFLSB_FROM_FREQ(FREQ) ((((uint32_t)((FREQ)/RFM69_CONSTANTS_FSTREP))>>0)&0xFF)

#define RFM69_FDEVMSB_FROM_FREQ(FREQ) ((((uint32_t)((FREQ)/RFM69_CONSTANTS_FSTREP))>>8)&0xFF)
#define RFM69_FDEVLSB_FROM_FREQ(FREQ) ((((uint32_t)((FREQ)/RFM69_CONSTANTS_FSTREP))>>0)&0xFF)




#define MAX_DATA_LEN			61 // to take advantage of the built in AES/CRC we want to limit the frame size to the internal FIFO size (66 bytes - 3 bytes overhead)
//#define SPI_CS               SS // SS is the SPI slave select pin, for instance D10 on atmega328
//#define RF69_IRQ_PIN          2 // INT0 on AVRs should be connected to DIO0 (ex on Atmega328 it's D2)
#define CSMA_LIMIT				-90 // upper RX signal sensitivity threshold in dBm for carrier sense access
#define CSMA_LIMIT_RAW			180
#define RF69_MODE_SLEEP			0 // XTAL OFF
#define	RF69_MODE_STANDBY		1 // XTAL ON
#define RF69_MODE_SYNTH			2 // PLL ON
#define RF69_MODE_RX			3 // RX MODE
#define RF69_MODE_TX			4 // TX MODE

//available frequency bands
#define RF69_315MHZ     31  // non trivial values to avoid misconfiguration
#define RF69_433MHZ     43
#define RF69_868MHZ     86
#define RF69_915MHZ     91

#define null                  0
#define COURSE_TEMP_COEF    -90 // puts the temperature reading in the ballpark, user can fine tune the returned value
#define RF69_BROADCAST_ADDR 255

//#define RFM69_DIO0_HIGH		RFM69_DIO0_IN & (1<<RFM69_DIO0_PIN)
//#define RFM69_DIO0_HIGH		HAL.IO.IsPinHigh(RFM69_DIO5_PIN_HAL)
//#define RFM69_DIO0_HIGH		RFM69Dio5Pin.IsPinHigh();


class SPI_RFM69
  {
  public:
    static volatile uint8_t SPI_ADDR;
//    void initialize(void);
    void select(void);
    void unselect(void);
    uint8_t transfer(unsigned char data);
//    static volatile uint8_t _SSPin;
//  SPI_RFM69(uint8_t slaveSelectPin)
//    {
//    _SSPin=slaveSelectPin;
//    }
  protected:
//    static SPI_RFM69* selfPointer;
	};
class RFM69 {
  public:
    static volatile uint8_t DATA[MAX_DATA_LEN];          // recv/xmit buf, including hdr & crc bytes
    static volatile uint8_t DATALEN;
    static volatile uint8_t SENDERID;
    static volatile uint8_t TARGETID; //should match _address
    static volatile uint8_t PAYLOADLEN;
//    static volatile uint8_t ACK_REQUESTED;
//    static volatile uint8_t ACK_RECEIVED; /// Should be polled immediately after sending a packet with ACK request
    static volatile int16_t RSSI; //most accurate RSSI during reception (closest to the reception)
    static volatile uint8_t RSSI_RAW; //most accurate RSSI during reception (closest to the reception)
    static volatile uint8_t _mode; //should be protected?

//volatile uint8_t _RXBuffer[PACKET_SIZE];
//volatile uint8_t _TXBuffer[PACKET_SIZE];

    
//    RFM69(uint8_t slaveSelectPin=SPI_CS, uint8_t interruptPin=RF69_IRQ_PIN, bool isRFM69HW=false) {
  RFM69(bool isRFM69HW=false)
    {
//      _slaveSelectPin = slaveSelectPin;
//      _interruptPin = interruptPin;
    _mode               = RF69_MODE_STANDBY;
    _promiscuousMode    = false;
    _powerLevel         = 31;
    _isRFM69HW          = isRFM69HW;
    _SIGNAL_POWER       = 0;
    _address            = 0;
    }
  static bool isPacketReceivedHigh(void)
    {
    return RFM69Dio5Pin::IsPinHigh();
    }

//	bool checkCRC(void);
//	unsigned short Crc16(unsigned char * pcBlock, unsigned short len);
//	unsigned short Crc16Update(unsigned short crc, unsigned char data);

//	unsigned short crc_ccitt_update (unsigned short crc, unsigned char data);
//	void receivePacket(void);
//    bool initialize(uint8_t freqBand, uint8_t ID, uint8_t networkID=1);
    bool initialize(uint8_t ID, uint8_t networkID=1);
    void setAddress(uint8_t addr);
    bool canSend();
//    void send(uint8_t toAddress, const void* buffer, uint8_t bufferSize, bool requestACK=false);
    void send(uint8_t toAddress, const void* buffer, uint8_t bufferSize);
    bool sendWithRetry(uint8_t toAddress, const void* buffer, uint8_t bufferSize, uint8_t retries=2, uint8_t retryWaitTime=15);
    bool receiveDone();
//    bool ACKReceived(uint8_t fromNodeID);
//    void sendACK(const void* buffer = "", uint8_t bufferSize=0);
    void setFrequency(uint32_t FRF);
    void encrypt(const char* key);
    void setCS(uint8_t newSPISlaveSelect);
//    int readRSSI(bool forceTrigger=false);
    volatile uint8_t readRSSI_RAW(bool forceTrigger=false);
    void promiscuous(bool onOff=true);
    void setHighPower(bool onOFF=true); //have to call it after initialize for RFM69HW
    void setPowerLevel(uint8_t level); //reduce/increase transmit power level
    uint8_t readTemperature(uint8_t calFactor=0); //get CMOS temperature (8bit)
    void rcCalibration(); //calibrate the internal RC oscillator for use in wide temperature variations - see datasheet section [4.3.5. RC Timer Accuracy]

    // allow hacking registers by making these public
    uint8_t readReg(uint8_t addr);
    void writeReg(uint8_t addr, uint8_t val);
    void readAllRegs();
//    void virtual interruptHandler();
	void setMode(uint8_t mode);
    void modeSleep();
    void select();
    void unselect();
    void receiveBegin();

    bool _isRFM69HW;
    void setHighPowerRegs(bool onOff);

  protected:
//    static void isr0();
//    void virtual interruptHandler(); //убрано наверх
//    void sendFrame(uint8_t toAddress, const void* buffer, uint8_t size, bool requestACK=false, bool sendACK=false);
    void sendFrame(uint8_t toAddress, const void* buffer, uint8_t size);

//    static RFM69* selfPointer;
//    uint8_t _slaveSelectPin;
//    uint8_t _interruptPin;
    uint8_t _address;
    bool _promiscuousMode;
    uint8_t _powerLevel;
    uint8_t _SIGNAL_POWER;

    //void setMode(uint8_t mode);
};

#endif

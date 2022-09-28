class STM8S_SPI{
public:
  enum REGISTER_CR1{
    REGISTER_CR1_CPHA,//Bit 0 CPHA: Clock phase
    REGISTER_CR1_CPOL,//Clock polarity
    REGISTER_CR1_MSTR,//Master selection
    REGISTER_CR1_BR,//Baud rate control
    REGISTER_CR1_BR2_DO_NOT_USE,//4
    REGISTER_CR1_BR3_DO_NOT_USE,//5
    REGISTER_CR1_SPE,//SPI enable
    REGISTER_CR1_LSBFIRST,
  };
  enum REGISTER_CR2{
    REGISTER_CR2_SSI,//Internal slave select (This bit has effect only when SSM bit is set. The value of this bit is forced onto the NSS pin and the I/O value of the NSS pin is ignored.)
    REGISTER_CR2_SSM,//Software slave management
    REGISTER_CR2_RXONLY,//Receive only (This bit combined with BDM bit selects the direction of transfer in 2 line uni-directional mode This bit is also useful in a multi-slave system in which this particular slave is not accessed, the output from the accessed slave is not corrupted.)
    REGISTER_CR2_RESERVED,
    REGISTER_CR2_CRCNEXT,//Transmit CRC next
    REGISTER_CR2_CRCEN,//Hardware CRC calculation enable
    REGISTER_CR2_BDOE,//Input/Output enable in bidirectional mode (This bit selects the direction of transfer in bidirectional mode when BDM is set to 1.) In master mode, the MOSI pin is used and in slave mode, the MISO pin is used.
    REGISTER_CR2_BDM,//Bidirectional data mode enable
  };
  enum REGISTER_ICR{//SPI interrupt control register
    REGISTER_ICR_RESERVED0,
    REGISTER_ICR_RESERVED1,
    REGISTER_ICR_RESERVED2,
    REGISTER_ICR_RESERVED3,
    REGISTER_ICR_WKIE,//Wakeup interrupt enable
    REGISTER_ICR_ERRIE,//Error interrupt enable
    REGISTER_ICR_RXIE,//RX buffer not empty interrupt enable
    REGISTER_ICR_TXIE,//Tx buffer empty interrupt enable
  };
  
  enum REGISTER_SR{//SPI status register
    REGISTER_SR_RXNE,//Receive buffer not empty
    REGISTER_SR_TXE,//Transmit buffer empty
    REGISTER_SR_RESERVED,
    REGISTER_SR_WKUP,//Wakeup flag
    REGISTER_SR_CRCERR,//CRC error flag
    REGISTER_SR_MODF,//Mode fault
    REGISTER_SR_OVR,//Overrun flag
    REGISTER_SR_BSY,//Busy flag
  };
  //SPI data register (SPI_DR) - Byte received or to be transmitted. The data register is split into 2 buffers - one for writing (Transmit buffer) and another one for reading (Receive buffer). A write to the data register will write into the Tx buffer and a read from the data register will return the value held in the Rx buffer.
  //SPI CRC polynomial register (SPI_CRCPR) - This register contains the polynomial for the CRC calculation. The CRC polynomial (0x07) is the reset value of this register. You can configure an other polynomial as required for your application.
  //SPI Rx CRC register (SPI_RXCRCR) - When CRC calculation is enabled, the RxCRC[7:0] bits contain the computed CRC value of the subsequently received bytes. This register is reset when the CRCEN bit in SPI_CR2 register is written to 1. The CRC is calculated serially using the polynomial programmed in the SPI_CRCPR register. Note: A read to this register when the BSY Flag is set could return an incorrect value.
  //SPI Tx CRC register (SPI_TXCRCR) - When CRC calculation is enabled, the TxCRC[7:0] bits contain the computed CRC value of the subsequently transmitted bytes. This register is reset when the CRCEN bit of SPI_CR2 is written to 1. The CRC is calculated serially using the polynomial programmed in the SPI_CRCPR register. Note: A read to this register when the BSY flag is set could return a incorrect value

  const static uint8_t REGISTER_CR1_CPHA__FIRST_EDGE                            = 0<<REGISTER_CR1_CPHA;//The first clock transition is the first data capture edge
  const static uint8_t REGISTER_CR1_CPHA__SECOND_EDGE                           = 1<<REGISTER_CR1_CPHA;//The second clock transition is the first data capture edge
  const static uint8_t REGISTER_CR1_CPOL__SCK_TO_0                              = 0<<REGISTER_CR1_CPOL;//SCK to 0 when idle
  const static uint8_t REGISTER_CR1_CPOL__SCK_TO_1                              = 1<<REGISTER_CR1_CPOL;//SCK to 1 when idle (SPI_CLOCKPOLARITY_HIGH)
  const static uint8_t REGISTER_CR1_MSTR__SLAVE                                 = 0<<REGISTER_CR1_MSTR;//Slave configuration
  const static uint8_t REGISTER_CR1_MSTR__MASTER                                = 1<<REGISTER_CR1_MSTR;//Master configuration
  const static uint8_t REGISTER_CR1_BR__BAUNDRATE_DIV_2                         = 0<<REGISTER_CR1_BR;//fMASTER/2
  const static uint8_t REGISTER_CR1_BR__BAUNDRATE_DIV_4                         = 1<<REGISTER_CR1_BR;//fMASTER/4
  const static uint8_t REGISTER_CR1_BR__BAUNDRATE_DIV_8                         = 2<<REGISTER_CR1_BR;//fMASTER/8
  const static uint8_t REGISTER_CR1_BR__BAUNDRATE_DIV_16                        = 3<<REGISTER_CR1_BR;//fMASTER/16
  const static uint8_t REGISTER_CR1_BR__BAUNDRATE_DIV_32                        = 4<<REGISTER_CR1_BR;//fMASTER/32
  const static uint8_t REGISTER_CR1_BR__BAUNDRATE_DIV_64                        = 5<<REGISTER_CR1_BR;//fMASTER/64
  const static uint8_t REGISTER_CR1_BR__BAUNDRATE_DIV_128                       = 6<<REGISTER_CR1_BR;//fMASTER/128
  const static uint8_t REGISTER_CR1_BR__BAUNDRATE_DIV_256                       = 7<<REGISTER_CR1_BR;//fMASTER/256
  const static uint8_t REGISTER_CR1_SPE__SPI_DISABLE                            = 0<<REGISTER_CR1_SPE;//Peripheral disabled
  const static uint8_t REGISTER_CR1_SPE__SPI_ENABLE                             = 1<<REGISTER_CR1_SPE;//Peripheral enabled
  const static uint8_t REGISTER_CR1_LSBFIRST__MSB                               = 0<<REGISTER_CR1_LSBFIRST;//MSB is transmitted first
  const static uint8_t REGISTER_CR1_LSBFIRST__LSB                               = 1<<REGISTER_CR1_LSBFIRST;//LSB is transmitted first

  const static uint8_t REGISTER_CR2_SSI__SLAVE_MODE                             = 0<<REGISTER_CR2_SSI;//Slave mode
  const static uint8_t REGISTER_CR2_SSI__MASTER_MODE                            = 1<<REGISTER_CR2_SSI;//Master mode
  const static uint8_t REGISTER_CR2_SSM__SSM_DISABLED                           = 0<<REGISTER_CR2_SSM;//Software slave management disabled
  const static uint8_t REGISTER_CR2_SSM__SSM_ENABLED                            = 1<<REGISTER_CR2_SSM;//Software slave management enabled
  const static uint8_t REGISTER_CR2_RXONLY__FULL_DUPLEX                         = 0<<REGISTER_CR2_RXONLY;//Full duplex (Transmit and receive)
  const static uint8_t REGISTER_CR2_RXONLY__OUTPUT_DISABLED                     = 1<<REGISTER_CR2_RXONLY;//Output disabled (Receive only mode)
  const static uint8_t REGISTER_CR2_CRCNEXT__NEXT_TX_FROM_TXB                   = 0<<REGISTER_CR2_CRCNEXT;//Next transmit value is from Tx buffer
  const static uint8_t REGISTER_CR2_CRCNEXT__NEXT_TX_FROM_CRC                   = 1<<REGISTER_CR2_CRCNEXT;//Next transmit value is from Tx CRC register
  const static uint8_t REGISTER_CR2_CRCEN__CRC_DISABLED                         = 0<<REGISTER_CR2_CRCEN;//CRC calculation disabled
  const static uint8_t REGISTER_CR2_CRCEN__CRC_ENABLED                          = 1<<REGISTER_CR2_CRCEN;//CRC calculation Enabled
  const static uint8_t REGISTER_CR2_BDOE__INPUT_ENABLED                         = 0<<REGISTER_CR2_BDOE;//Input enabled (receive-only mode)
  const static uint8_t REGISTER_CR2_BDOE__OUTPUT_ENABLED                        = 1<<REGISTER_CR2_BDOE;//Output enabled (transmit-only mode)
  const static uint8_t REGISTER_CR2_BDM__TWO_LINE_UNI_D_MODE                    = 0<<REGISTER_CR2_BDM;//2-line unidirectional data mode selected
  const static uint8_t REGISTER_CR2_BDM__ONE_LINE_BI_D_MODE                     = 1<<REGISTER_CR2_BDM;//1-line bidirectional data mode selected

  const static uint8_t REGISTER_ICR_WKIE__WAKEUP_INTERRUPT_MASKED               = 0<<REGISTER_ICR_WKIE;//Wakeup interrupt masked
  const static uint8_t REGISTER_ICR_WKIE__WAKEUP_INTERRUPT_ENABLED              = 1<<REGISTER_ICR_WKIE;//Wakeup interrupt enabled. This allows an interrupt request to be generated when the WKUP flag is set.
  const static uint8_t REGISTER_ICR_ERRIE__ERROR_INTERRUPT_MASKED               = 0<<REGISTER_ICR_ERRIE;//Error interrupt is masked
  const static uint8_t REGISTER_ICR_ERRIE__ERROR_INTERRUPT_ENABLED              = 1<<REGISTER_ICR_ERRIE;//Error interrupt is enabled. This allows an interrupt request to be generated when an error condition occurs (CRCERR, OVR, MODF)
  const static uint8_t REGISTER_ICR_RXIE__RXBUFFER_NOT_EMPTY_INTERRUPT_MASKED   = 0<<REGISTER_ICR_RXIE;//RXNE interrupt masked
  const static uint8_t REGISTER_ICR_RXIE__RXBUFFER_NOT_EMPTY_INTERRUPT_ENABLED  = 1<<REGISTER_ICR_RXIE;//RXNE interrupt not masked. This allows an interrupt request to be generated when the RXNE flag is set.
  const static uint8_t REGISTER_ICR_TXIE__TXBUFFER_NOT_EMPTY_INTERRUPT_MASKED   = 0<<REGISTER_ICR_TXIE;//TXNE interrupt masked
  const static uint8_t REGISTER_ICR_TXIE__TXBUFFER_NOT_EMPTY_INTERRUPT_ENABLED  = 1<<REGISTER_ICR_TXIE;//TXE interrupt not masked. This allows an interrupt request to be generated when the TXE flag is set.
  
  static void InitTXMaxspeedMaster(void){
    SPI->CR1 = STM8S_SPI::REGISTER_CR1_CPHA__SECOND_EDGE | 
               STM8S_SPI::REGISTER_CR1_CPOL__SCK_TO_1 | 
               STM8S_SPI::REGISTER_CR1_MSTR__MASTER | 
               STM8S_SPI::REGISTER_CR1_BR__BAUNDRATE_DIV_2 | 
               STM8S_SPI::REGISTER_CR1_SPE__SPI_ENABLE | 
               STM8S_SPI::REGISTER_CR1_LSBFIRST__MSB;
    SPI->CR2 = STM8S_SPI::REGISTER_CR2_SSI__MASTER_MODE | 
               STM8S_SPI::REGISTER_CR2_SSM__SSM_DISABLED | 
               STM8S_SPI::REGISTER_CR2_RXONLY__FULL_DUPLEX | 
               STM8S_SPI::REGISTER_CR2_CRCNEXT__NEXT_TX_FROM_TXB | 
               STM8S_SPI::REGISTER_CR2_CRCEN__CRC_DISABLED | 
               STM8S_SPI::REGISTER_CR2_BDOE__OUTPUT_ENABLED | 
               STM8S_SPI::REGISTER_CR2_BDM__ONE_LINE_BI_D_MODE;
  }
  static void SPIEnable(void){
    sbi(SPI->CR1, REGISTER_CR1_SPE);
  }
  static void SPIDisable(void){
    cbi(SPI->CR1, REGISTER_CR1_SPE);
  }
  static void SPI_SendData(uint8_t Data){
    SPI->DR = Data; /* Write in the DR register the data to be sent*/
  }
};
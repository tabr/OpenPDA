#ifndef HAL_H
#define HAL_H


//#include "stalker/AirPacketClass.h"

/*
class HAL_SPIClass
  {
  public:
    uint8_t SendData(uint8_t data)
      {
      this->pSPI->DATA  = data;
      while (!(this->pSPI->STATUS & SPI_IF_bm))
        {
        //    ++tmp;
        //    PORTQ_OUTTGL  = (1<<PIN0_bp);
        }        //Wait Interrupt
      return this->pSPI->DATA;
      }
    HAL_SPIClass (SPI_t* SPI)
      {
      this->pSPI  = SPI;
      }
  protected:
  private:
    SPI_t* pSPI;
  };
//HAL_SPIClass a = HAL_SPIClass(&SPIE);
*/

class Class_HAL
  {
  public:
    enum ERRORS
      {
      ERROR_NO_ERRORS,
      ERROR_RM0_NOT_INIT,
      ERROR_RM0_TX_BUF_NOT_INIT,
      ERROR_RM0_RX_BUF_NOT_INIT,
      ERROR_RM0_PACKET_SIZE_NOT_SET,
      ERROR_RM0_INIT_FAILED 
      };
    //const static uint8_t ERROR_NO_ERRORS          = 0x00;
    //const static uint8_t ERROR_RM0_NOT_INIT          = 0x01;
    //const static uint8_t ERROR_RM0_TX_BUF_NOT_INIT      = 0x02;
    //const static uint8_t ERROR_RM0_RX_BUF_NOT_INIT      = 0x03;
    //const static uint8_t ERROR_RM0_PACKET_SIZE_NOT_SET    = 0x04;
    const static uint8_t MAX_ENV_PACKETS_IN_TRANSACTION    = 15;//каждые 10мс - проверка на получение данных, каждые 10x5=50мс - обработка
    const static uint32_t CLOCK_FREQUENCY          = F_CPU;
    
    Driver_AnoRadRarioModule EnvironmentRarioModule;
    //Driver_IO IO;
//    Driver_Clock Clock;
    
    void IOInit(void);
    void HardwareInitialization(void);
    /*void SPI_SimpleInit(void* parameters)
      {
      SPI_SimpleInit(parameters);
      }*/
/*
    void setClock (void)
      {
      this->Clock.selectMaxExternal();
      }
*/    /*
    static inline void usart_init()//убрать
      {
      
      //  #define BAUDRATE 115200
      // enable clock out on port PC7
      //  PORTCFG.CLKOUT = (PORTCFG.CLKOUT & ~PORTCFG_CLKOUTSEL_gm) | PORTCFG_CLKOUT_PC7_gc;
      //  PORTCFG.CLKOUT = (PORTCFG.CLKOUT & ~PORTCFG_CLKOUTSEL_gm) | PORTCFG_CLKOUT_PD1_gc;
      //PORTCFG.
      // set PC7 as output
      //  PORTC.DIRSET = PIN7_bm;
      //  PORTD.DIRSET = PIN1_bm;

      // set PD7 as output for TX0
      //  PORTD.DIRSET = PIN7_bm;
      //  PORTD.OUTSET = PIN7_bm;
//      PORTD.DIRSET = PIN3_bm;
//      PORTD.OUTSET = PIN3_bm;
//      PORTD.PIN2CTRL          = PORT_OPC_PULLDOWN_gc;//подтяжка к низу
      
      this->IO.setDirOut(Driver_IO::PinD3);
      this->IO.setOutHigh(Driver_IO::PinD3);
      this->IO.setPullUp(Driver_IO::PinD3);
      // remap USARTD0 to PD[7-4]
      //  PORTD.REMAP |= PORT_USART0_bm;
      // set baud rate 9600: BSEL=12, BSCALE=4
      // as found in table in
      //Atmel-42005-8-and-16-bit-AVR-Microcontrollers-XMEGA-E_Manual.pdf
      //Table 21-5. USART baud rate.
      //Atmel-8331-8-and-16-bit-AVR-Microcontroller-XMEGA-AU_Manual
      //Table 23-5. USART baud rate.

      //  USARTD0.BAUDCTRLA = 12; // BSEL
      //  USARTD0.BAUDCTRLB = 4 << USART_BSCALE_gp; // BSCALE
      // disable 2X
      //  USARTD0.CTRLB = USARTD0.CTRLB & ~USART_CLK2X_bm;

      //->114285.71428571
      USARTD0.BAUDCTRLA = 34; // BSEL
      USARTD0.BAUDCTRLB = 0 << USART_BSCALE_gp; // BSCALE
      USARTD0.CTRLB = USARTD0.CTRLB  | USART_CLK2X_bm;

      //  USARTD0.BAUDCTRLA = 0; // BSEL
      //  USARTD0.BAUDCTRLB = 0 << USART_BSCALE_gp; // BSCALE
      //  USARTD0.CTRLB = USARTD0.CTRLB & ~USART_CLK2X_bm;
      
      // enable RX and TX
      USARTD0.CTRLB = USARTD0.CTRLB | USART_RXEN_bm | USART_TXEN_bm;
      // enable async UART 8N1
      USARTD0.CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
      USARTD0.CTRLC &= ~USART_SBMODE_bm;
      //USARTD0.CTRLD = 0; // No LUT
      //  USARTD0.

      // set interrupt level for RX
      USARTD0.CTRLA = (USARTD0.CTRLA & ~USART_RXCINTLVL_gm) | USART_RXCINTLVL_LO_gc;
      
      }*/
    
    /*static inline void usart_SPIinit()//убрать
      {
      #define UCPHA                           1
      #define INVEN                           7
      #define CMODE0                          6
      #define CMODE1                          7
      #define FERR                            4
      #define BUFOVF                          3
      #define PERR                            2
      #define TXCIF                           6
      
      PORTE.OUTSET  = 1<<7;//1;
      PORTE.OUTSET  = 1<<5;//3;
      PORTE.DIRSET  = 1<<7;
      PORTE.DIRSET  = 1<<5;
      PORTE.REMAP  = 1<<5;
      
      
      //PORTE.PIN3CTRL  &= ~(1 << INVEN);
      //  #define BAUDRATE 115200
      // enable clock out on port PC7
      //  PORTCFG.CLKOUT = (PORTCFG.CLKOUT & ~PORTCFG_CLKOUTSEL_gm) | PORTCFG_CLKOUT_PC7_gc;
      //  PORTCFG.CLKOUT = (PORTCFG.CLKOUT & ~PORTCFG_CLKOUTSEL_gm) | PORTCFG_CLKOUT_PD1_gc;
      //PORTCFG.
      // set PC7 as output
      //  PORTC.DIRSET = PIN7_bm;
      //  PORTD.DIRSET = PIN1_bm;

      // set PD7 as output for TX0
      //  PORTD.DIRSET = PIN7_bm;
      //  PORTD.OUTSET = PIN7_bm;
//      PORTD.DIRSET = PIN3_bm;
//      PORTD.OUTSET = PIN3_bm;
//      PORTD.PIN2CTRL          = PORT_OPC_PULLDOWN_gc;//подтяжка к низу
      
////////      this->IO.setDirOut(Driver_IO::PinD3);
////////      this->IO.setOutHigh(Driver_IO::PinD3);
////////      this->IO.setPullUp(Driver_IO::PinD3);
      // remap USARTD0 to PD[7-4]
      //  PORTD.REMAP |= PORT_USART0_bm;
      // set baud rate 9600: BSEL=12, BSCALE=4
      // as found in table in
      //Atmel-42005-8-and-16-bit-AVR-Microcontrollers-XMEGA-E_Manual.pdf
      //Table 21-5. USART baud rate.
      //Atmel-8331-8-and-16-bit-AVR-Microcontroller-XMEGA-AU_Manual
      //Table 23-5. USART baud rate.

      //  USARTD0.BAUDCTRLA = 12; // BSEL
      //  USARTD0.BAUDCTRLB = 4 << USART_BSCALE_gp; // BSCALE
      // disable 2X
      //  USARTD0.CTRLB = USARTD0.CTRLB & ~USART_CLK2X_bm;

      //->114285.71428571
      USARTE1.BAUDCTRLA = 34; // BSEL
      USARTE1.BAUDCTRLB = 0 << USART_BSCALE_gp; // BSCALE
      USARTE1.CTRLB = USARTE1.CTRLB  | USART_CLK2X_bm;

      //  USARTD0.BAUDCTRLA = 0; // BSEL
      //  USARTD0.BAUDCTRLB = 0 << USART_BSCALE_gp; // BSCALE
      //  USARTD0.CTRLB = USARTD0.CTRLB & ~USART_CLK2X_bm;
      
      // enable RX and TX
//      USARTF0.CTRLB = USARTF0.CTRLB | USART_RXEN_bm | USART_TXEN_bm;
      USARTE1.CTRLB = USARTE1.CTRLB | USART_TXEN_bm;
      // enable async UART 8N1
//      USARTF0.CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
//      USARTF0.CTRLC &= ~USART_SBMODE_bm;
      //USARTE1.CTRLC  = (1 << CMODE0) | (1 << CMODE1) | (1 << UCPHA);//+
      USARTE1.CTRLC  = USART_CMODE_MSPI_gc;
      //USARTD0.CTRLD = 0; // No LUT
      //  USARTD0.

      // set interrupt level for RX
//////      USARTD0.CTRLA = (USARTD0.CTRLA & ~USART_RXCINTLVL_gm) | USART_RXCINTLVL_LO_gc;
      
      }*/
    Interface_Driver_Clock* GetClock(void);
    Class_HAL(Interface_Driver_Clock* c);
  protected:
  private:
    Interface_Driver_Clock* Clock;
//    uint8_t lastOperationError;
  };


#endif
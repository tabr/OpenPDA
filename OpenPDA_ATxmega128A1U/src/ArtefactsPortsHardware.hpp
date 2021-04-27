/*
  *  ArtefactsPortsHardware.h
  *
  *  Created:  2015-03-10  07:47:59
  *    Author:  tabr
  */  


#ifndef  ARTEFACTSPORTSHARDWARE_H_
#define  ARTEFACTSPORTSHARDWARE_H_

#include  "boards/pcb_1.h"

class  ArtefactsPortsHardwareClass
  {
  public:
    const static uint8_t  MAX_SLOTS            =  ARTEFACTS_SLOTS_NUM;

    void  IOInit(void)
      {
      ArtefactsPinSS00::SetDirIn();
      ArtefactsPinSS00::SetOutLow();
      ArtefactsPinSS00::SetPullDown();
      ArtefactsPinLED00::SetDirOut();
      ArtefactsPinLED00::SetOutLow();

      ArtefactsPinSS01::SetDirIn();
      ArtefactsPinSS01::SetOutLow();
      ArtefactsPinSS01::SetPullDown();
      ArtefactsPinLED01::SetDirOut();
      ArtefactsPinLED01::SetOutLow();

      ArtefactsPinSS02::SetDirIn();
      ArtefactsPinSS02::SetOutLow();
      ArtefactsPinSS02::SetPullDown();
      ArtefactsPinLED02::SetDirOut();
      ArtefactsPinLED02::SetOutLow();

      ArtefactsPinSS03::SetDirIn();
      ArtefactsPinSS03::SetOutLow();
      ArtefactsPinSS03::SetPullDown();
      ArtefactsPinLED03::SetDirOut();
      ArtefactsPinLED03::SetOutLow();

      ArtefactsPinSS04::SetDirIn();
      ArtefactsPinSS04::SetOutLow();
      ArtefactsPinSS04::SetPullDown();
      ArtefactsPinLED04::SetDirOut();
      ArtefactsPinLED04::SetOutLow();

      #if  (ARTEFACTS_SLOTS_NUM  !=  5)  
        #error  "error=)"
      #endif
      }
    void  HardwareInitialization(void)
      {
      ArtefactsClkPin::SetDirOut();
      ArtefactsClkPin::SetOutLow();
      ArtefactsMosiPin::SetDirOut();
      ArtefactsMisoPin::SetDirIn();
      ArtefactsMisoPin::SetPullDown();
      ArtefactsSSPin::SetDirOut();
      
      //                      [double  CLK]    [enable]      [DORD]        [master]      [transfer  mode]  [clk  prescaller]
      //  ARTEFACTS_SPI.CTRL          =  1<<7      |  1<<6        |  0<<5        |  1<<4        |  (0<<3  |  0<<2)  |  (0<<1  |  0<<0);//max  SPI  speed  -  16MHz
//      ARTEFACTS_SPI.CTRL          =  0<<7        |  1<<6        |  0<<5        |  1<<4        |  (0<<3  |  0<<2)  |  (1<<1  |  1<<0);
      //ARTEFACTS_SPI.CTRL          =  0<<SPI_CLK2X_bp  |  1<<SPI_ENABLE_bp  |  0<<SPI_DORD_bp  |  1<<SPI_MASTER_bp  |  SPI_MODE_0_gc  |  SPI_PRESCALER_DIV128_gc;
      ARTEFACTS_SPI.CTRL          =  1<<SPI_CLK2X_bp  |  1<<SPI_ENABLE_bp  |  0<<SPI_DORD_bp  |  1<<SPI_MASTER_bp  |  SPI_MODE_0_gc  |  SPI_PRESCALER_DIV4_gc;
      ARTEFACTS_SPI_PORT.REMAP      =  PORT_SPI_bm;
      ARTEFACTS_SPI.INTCTRL        =  SPI_INTLVL_OFF_gc  ;  //  no  interrupt
      }
    uint8_t  SPI_send(uint8_t  data)
      {
      ARTEFACTS_SPI.DATA  =  data;
      while  (!(ARTEFACTS_SPI.STATUS  &  SPI_IF_bm))
        {
        //    ++tmp;
        //    PORTQ_OUTTGL  =  (1<<PIN0_bp);
        }    //Wait  Interrupt
      return  ARTEFACTS_SPI.DATA;
      }
  protected:
  private:
  };


#endif  /*  ARTEFACTSPORTSHARDWARE_H_  */

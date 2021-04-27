/*
  *  AES_Support_XMEGA.h
  *
  *  Created:  2015-06-08  17:57:31
  *    Author:  tabr
  */  


#ifndef  AES_SUPPORT_XMEGA_H_
#define  AES_SUPPORT_XMEGA_H_

typedef  uint8_t  irqflags_t;
#    define  cpu_irq_enable()          sei()
#    define  cpu_irq_disable()        cli()
//#define  barrier()  asm  ("")
/*
enum  sysclk_port_id  {
  SYSCLK_PORT_GEN,      //!<  Devices  not  associated  with  a  specific  port.
  SYSCLK_PORT_A,          //!<  Devices  on  PORTA
  SYSCLK_PORT_B,          //!<  Devices  on  PORTB
  SYSCLK_PORT_C,          //!<  Devices  on  PORTC
  SYSCLK_PORT_D,          //!<  Devices  on  PORTD
  SYSCLK_PORT_E,          //!<  Devices  on  PORTE
  SYSCLK_PORT_F,          //!<  Devices  on  PORTF
};
*/
/*!  \name  Clocks  not  associated  with  any  port
  *
  *  \note  See  the  datasheet  for  available  modules  in  the  device.
  */
//@{
#define  SYSCLK_DMA                PR_DMA_bm          //!<  DMA  Controller
#define  SYSCLK_EDMA              PR_EDMA_bm        //!<  EDMA  Controller
#define  SYSCLK_EVSYS            PR_EVSYS_bm      //!<  Event  System
#define  SYSCLK_RTC                PR_RTC_bm          //!<  Real-Time  Counter
#define  SYSCLK_EBI                PR_EBI_bm          //!<  Ext  Bus  Interface
#define  SYSCLK_AES                PR_AES_bm          //!<  AES  Module
#define  SYSCLK_USB                PR_USB_bm          //!<  USB  Module
#define  SYSCLK_XCL                PR_XCL_bm          //!<  USB  Module
//@}

/*!  \name  Clocks  on  PORTA  and  PORTB
  *
  *  \note  See  the  datasheet  for  available  modules  in  the  device.
  */
//@{
#define  SYSCLK_AC                  PR_AC_bm            //!<  Analog  Comparator
#define  SYSCLK_ADC                PR_ADC_bm          //!<  A/D  Converter
#define  SYSCLK_DAC                PR_DAC_bm          //!<  D/A  Converter
//@}

/*!  \name  Clocks  on  PORTC,  PORTD,  PORTE  and  PORTF
  *
  *  \note  See  the  datasheet  for  available  modules  in  the  device.
  */
//@{
#define  SYSCLK_TC0                PR_TC0_bm            //!<  Timer/Counter  0
#define  SYSCLK_TC1                PR_TC1_bm            //!<  Timer/Counter  1
#define  SYSCLK_TC4                PR_TC4_bm            //!<  Timer/Counter  0
#define  SYSCLK_TC5                PR_TC5_bm            //!<  Timer/Counter  1
#define  SYSCLK_HIRES            PR_HIRES_bm        //!<  Hi-Res  Extension
#define  SYSCLK_SPI                PR_SPI_bm            //!<  SPI  controller
#define  SYSCLK_USART0          PR_USART0_bm      //!<  USART  0
#define  SYSCLK_USART1          PR_USART1_bm      //!<  USART  1
#define  SYSCLK_TWI                PR_TWI_bm            //!<  TWI  controller
//@}
/*
static  inline  irqflags_t  cpu_irq_save(void)
{
  irqflags_t  flags  =  SREG;
  cpu_irq_disable();
  return  flags;
}
static  inline  void  cpu_irq_restore(irqflags_t  flags)
{
  barrier();
  SREG  =  flags;
}
void  sysclk_enable_module(enum  sysclk_port_id  port,  uint8_t  id)
{
  irqflags_t  flags  =  cpu_irq_save();

  *((uint8_t  *)&PR.PRGEN  +  port)  &=  ~id;

  cpu_irq_restore(flags);
}
*/



#endif  /*  AES_SUPPORT_XMEGA_H_  */

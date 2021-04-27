/*
 * USBBoot.h
 *
 * Created: 01.05.2018 10:44:03
 *  Author: tabr
 */ 


#ifndef USBBOOT_H_
#define USBBOOT_H_

#include <avr/io.h>
#include <asf.h>
#include <util/delay.h>
#include "conf_usb.hpp"
#include "USBBootClass.hpp"
//#include "stalker/Class_StalkerLayer2.hpp"

extern USBBootClass* USBBootClassInstance;
extern Class_HAL HAL;
extern udd_ctrl_request_t* udd_g_ctrlreq;
#ifndef LOAD_SOUNDS

int USBBoot(void)
	{
  /*
	PORTA.DIRSET	= 0xff;
	PORTB.DIRSET	= 0xff;
	PORTC.DIRSET	= 0xff;
	PORTD.DIRSET	= 0xff;
	PORTE.DIRSET	= 0xff;
	PORTF.DIRSET	= 0xff;
	PORTH.DIRSET	= 0xff;
	PORTJ.DIRSET	= 0xff;
	PORTK.DIRSET	= 0xff;
	PORTQ.DIRSET	= 0xff;

	PORTA.OUTCLR	= 0xff;
	PORTB.OUTCLR	= 0xff;
	PORTC.OUTCLR	= 0xff;
	PORTD.OUTCLR	= 0xff;
	PORTE.OUTCLR	= 0xff;
	PORTF.OUTCLR	= 0xff;
	PORTH.OUTCLR	= 0xff;
	PORTJ.OUTCLR	= 0xff;
	PORTK.OUTCLR	= 0xff;
	PORTQ.OUTCLR	= 0xff;
  */
    #warning "[T] V506 Pointer to local variable 'L2' is stored outside the scope of this variable. Such a pointer will become invalid."
  Class_StalkerLayer2 L2;
  StalkerLayer2 = &L2; //-V506
  L2.HardwareInitialization();
  //StalkerLayer2.HardwareInitialization();
  USBBootClassInstance = new USBBootClass;
  udd_g_ctrlreq = &USBBootClassInstance->udd_g_ctrlreq;

	irq_initialize_vectors();
	cpu_irq_enable();
	// Initialize the sleep manager
	sleepmgr_init();

	//#if !SAM0

	sysclk_init();

//      LcdStringUpdate(1,LCD_LINE_2, (char*)"ccc");
//      _delay_ms(3000);
//  RuntimeClass::Level0();
  //HAL.GetClock()->SelectMaxExternal();

	//board_init();
	//while(1);
	//#else
	//	system_init();
	//#endif
	//ui_init();
    //ui_powerdown();

	// Start USB stack to authorize VBus monitoring
    udc_start();
    udc_attach(); //подсоединяемся к хосту
    sysclk_enable_module(SYSCLK_PORT_C, SYSCLK_TC0); // включение тактирования таймера ТС0
    sysclk_enable_module(SYSCLK_PORT_C, SYSCLK_TWI);
    sysclk_enable_module(SYSCLK_PORT_C, SYSCLK_SPI);
    sysclk_enable_module(SYSCLK_PORT_E, SYSCLK_SPI);
    sysclk_enable_module(SYSCLK_PORT_E, SYSCLK_USART1);
    LcdStringUpdate(1,LCD_LINE_1,(char*)"[USB]HELLO!");
    while (1) //-V776
        {
        USBBootClassInstance->CommandProcess();
        sleepmgr_enter_sleep();
        }
    }
#endif
#endif /* USBBOOT_H_ */
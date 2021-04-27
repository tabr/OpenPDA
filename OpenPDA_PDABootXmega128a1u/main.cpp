// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/* 
 * This file is part of the OpenPDA distribution https://github.com/tabr/OpenPDA
 * Copyright (c) 2010-2021 Mateshko Andrei (tabr).
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 2.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
 /*
 * PDABootXmega128a1u.cpp
 *
 * Created: 2015-01-28 18:25:57
 *  Author: tabr
 */ 

//#define F_CPU 32000000UL
//#include <util/delay.h>
#include <avr/io.h>
#include "asf.h"

uint8_t report[64];
uint8_t ui_hid_report [64];

ISR(TCE0_OVF_vect)
	{
	PORTE.OUTTGL	= 1<<2;
	}
int main(void)
	{
	for (uint8_t i=0;i<64;i++)
		{
		ui_hid_report[i]=i;
		}
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
	//irqflags_t flags = cpu_irq_save();
	sysclk_init();
	sysclk_enable_module(SYSCLK_PORT_E, SYSCLK_TC0);
	//cpu_irq_restore(flags);
	/*
	OSC.XOSCCTRL = OSC_FRQRANGE_12TO16_gc | OSC_XOSCSEL_XTAL_256CLK_gc; // configure the XTAL input
	OSC.CTRL |= OSC_XOSCEN_bm; // start XTAL
	while (!(OSC.STATUS & OSC_XOSCRDY_bm)); // wait until ready
	//_delay_ms(100/2);

	OSC.PLLCTRL = OSC_PLLSRC_XOSC_gc | 0x2; // XTAL->PLL, 2x multiplier
	OSC.CTRL |= OSC_PLLEN_bm; // start PLL
	while (!(OSC.STATUS & OSC_PLLRDY_bm)); // wait until ready
	//_delay_ms(100/2);
	CCP = CCP_IOREG_gc; // allow changing CLK.CTRL
	CLK.CTRL = CLK_SCLKSEL_PLL_gc; // use PLL output as system clock
	*/

	//PMIC.CTRL = 255;
	ccp_write_io((uint8_t*)&PMIC.CTRL, PMIC_IVSEL_bm | PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm);//	irq_initialize_vectors(); <-almost the same
	cpu_irq_enable();

	TCE0.INTCTRLA = TC_OVFINTLVL_HI_gc;
	TCE0.CTRLA = TC_CLKSEL_DIV256_gc;
	TCE0.PER	= 10000;
	//while(1)
		{
		//PORTE.OUTTGL	= 1<<2;
		}
	
	
	//while(1);
	//irq_initialize_vectors();
	// Map interrupt vectors table in bootloader section
	//ccp_write_io((uint8_t*)&PMIC.CTRL, PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm);
	//ccp_write_io((uint8_t*)&PMIC.CTRL, PMIC_IVSEL_bm | PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm);//	irq_initialize_vectors(); <-almost the same
	//PMIC.CTRL	= (PMIC_IVSEL_bm | PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm);
	//ccp_write_io((uint8_t*)&PMIC.CTRL, PMIC_IVSEL_bm);
	//pmic_set_vector_location(PMIC_VEC_BOOT);
	
	//cpu_irq_enable();
//	PMIC.CTRL = 255;
	//sei();
	//PORTE.OUTSET	= 1<<2;
	//while(1);
	//sei();
	udc_start();
	//_delay_ms(1000);
	udc_attach(); //подсоединяемся к хосту
	//-Wl,--section-start=.text=0x20000
    while(1)
		{
        //udi_hid_generic_send_report_in(ui_hid_report);
		//PORTE.OUTTGL	= 1<<2;
		}
	}
void my_callback_generic_report_out(uint8_t *data)
	{
	for (uint8_t i = 0; i < 64; i++)
		{
		report [i] = data[i];
		}
	// теперь в массиве report находятся данные полученные в сообщении
	}
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef BACKLIGHT_CLASS_CPP
#define BACKLIGHT_CLASS_CPP

//#include <avr/io.h>

#include "BackLightClass.hpp"
#include "boards/pcb_1.h"

void BackLightClass::turnONFor5sec(void)
	{
	this->turnON();
	this->turnOnTimer	= 5;
	}
void BackLightClass::TimerUpdateEvent (uint8_t msPassed)
	{
	static uint16_t oneSecTimer=0;
	oneSecTimer += msPassed;
	if (oneSecTimer > 1000)
		{
		oneSecTimer -= 1000;
		}
	else
		{
		return;
		}
	if (turnOnTimer > 0)
		{
		if (--turnOnTimer == 1)
			{
			this->turnOFF();
			}
		}
	}

void BackLightClass::turnON(void)
	{
	if (this->isBacklightONInverted())
		{
		LcdPinBacklight::SetOutLow();
		}
	else
		{
		LcdPinBacklight::SetOutHigh();
		}
	}
void BackLightClass::turnOFF(void)
	{
	if (this->isBacklightONInverted())
		{
		LcdPinBacklight::SetOutHigh();
		}
	else
		{
		LcdPinBacklight::SetOutLow();
		}
	}
void BackLightClass::IOInit(void)
	{
	LcdPinBacklight::SetDirOut();
	LcdBacklightInvertedPin::SetDirIn();
	LcdBacklightInvertedPin::SetPullUp();
	_delay_us(10);
	//if (LcdBacklightInvertedPin::IsPinHigh())
	//	{
	//	this->isBacklightONInverted	= true;
	//	}
	this->DefaultState();
	}
void BackLightClass::DefaultState(void){
	this->turnOFF();
}
bool BackLightClass::isBacklightONInverted(void){
	return DeviceConfig.GetBL();
}
#endif
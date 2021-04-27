// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//#ifndef VIBRO_CLASS_CPP
//#define VIBRO_CLASS_CPP


#include "VibroClass.hpp"
//#include "stalker/drivers/Driver_IO_xmega128a1u.h"


/*void VibroClass::VibroClassTask1::Task(void)
	{
	//Vibro.updateState();
	((VibroClass*)this->GetLinkedObject())->updateState();
	}*/

VibroClass::VibroClass(void)
	{
	//this->TaskUpdateState.SetLinkedObject(this);
	}

void VibroClass::TimerUpdateEvent (uint8_t msPassed)
	{
	static uint16_t updateState_msCounter=0;
	updateState_msCounter+=msPassed;
	if (updateState_msCounter >= 40)
		{
		updateState_msCounter -= 40;
		this->updateState();
		}
	}
void VibroClass::IOInit(void)
	{
	vibroPin::SetDirOut();
	this->deactivate();
	}
void VibroClass::updateState(void)
	{
	if (this->timer > 0)
		{
		if (--this->timer == 0)
			{
			vibroPin::SetOutLow();
			}
		else
			{
			vibroPin::SetOutHigh();
			}
		}
	}
void VibroClass::activate(uint8_t ticks40ms)
	{
	this->timer	= ticks40ms;
	}
void VibroClass::deactivate(void)
	{
	#ifdef DEBUG_USART_FUNCTION_CALL
		sendString((char*)"[VibroClass::deactivate]");
	#endif
	this->timer	= 0;
	vibroPin::SetOutLow();
	}
//#endif
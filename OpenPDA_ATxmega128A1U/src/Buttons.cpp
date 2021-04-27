// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Buttons.hpp"
/*
void ButtonsClass::ButtonsTask1::Task(void)
	{
	//Buttons.scanForPressed();
	((ButtonsClass*)this->GetLinkedObject())->scanForPressed();
	}
void ButtonsClass::ButtonsTask2::Task(void)
	{
	//sButtons.tryUnlockButton(BUTTON_UNLOCK_TIMINGS_100MS);
	((ButtonsClass*)this->GetLinkedObject())->tryUnlockButton(BUTTON_UNLOCK_TIMINGS_100MS);
	}*/
void ButtonsClass::IOInit(void)
	{
	PinButtonDown_Enter::SetDirIn();
	PinButtonRight::SetDirIn();
	PinButtonCenter_Menu::SetDirIn();
	PinButtonLeft::SetDirIn();
	PinButtonUp_Esc::SetDirIn();

	PinButtonDown_Enter::SetPullUp();
	PinButtonRight::SetPullUp();
	PinButtonCenter_Menu::SetPullUp();
	PinButtonLeft::SetPullUp();
	PinButtonUp_Esc::SetPullUp();

	//ButtonMenuPin::SetDirIn();
	//ButtonMenuPrevPin::SetDirIn();
	//ButtonSelectPin::SetDirIn();
	//ButtonUsePin::SetDirIn();
	//ButtonMenuPin::SetPullUp();
	//ButtonMenuPrevPin::SetPullUp();
	//ButtonSelectPin::SetPullUp();
	//ButtonUsePin::SetPullUp();
	}
void ButtonsClass::TimerUpdateEvent (uint8_t msPassed)
	{
	static uint16_t scanForPressed_msCounter=0;
	//static uint16_t TryUnlockButton_msCounter=0;

	scanForPressed_msCounter+=msPassed;
	//TryUnlockButton_msCounter+=msPassed;

	if (scanForPressed_msCounter >= 10)
		{
		scanForPressed_msCounter -= 10;
		this->scanForPressed();
		}
	//try unlock
	for (uint8_t i=0;i<BUTTONS_NUM;i++)
		{
		if (this->lockTimers[i] > 0)
			{
			if (this->lockTimers[i] < msPassed)
				{
				this->lockTimers[i]	= 0;
				}
			else
				{
				this->lockTimers[i]-=msPassed;
				}
			}
		}
	/*if (TryUnlockButton_msCounter >= 100)
		{
		TryUnlockButton_msCounter	-=100;
		this->tryUnlockButton(BUTTON_UNLOCK_TIMINGS_100MS);
		}*/
	}
ButtonsClass::ButtonsClass (void)
	{
	memset(this->lockTimers, 0, sizeof(lockTimers));
	memset(this->state, BUTTON_STATE_RELEASED, sizeof(this->state));
	//this->TaskScanForPressed.SetLinkedObject(this);
	//this->TaskTryUnlockButton.SetLinkedObject(this);
/*
	for (uint8_t i = this->FIRST_PIN; i <= this->LAST_PIN; i++)
		{
		//cbi (BUTTONS_PORT.OUT,i);//вход
		//IOPort.SetDirIn(BUTTONS_PORT,i);
		HAL.IO.SetDirIn(i);
		HAL.IO.SetPullUp(i);
		}
*/
	//Timer.registerUserFunction(static_cast<Runnable*>(&this->Task1));
/*
	if (this->NUM > 0)
		BUTTONS_PORT.PIN0CTRL	= PORT_OPC_PULLUP_gc;
//		IOPort.SetPullUp(BUTTONS_PORT,0);
	if (this->NUM > 1)
		BUTTONS_PORT.PIN1CTRL	= PORT_OPC_PULLUP_gc;
	if (this->NUM > 2)
		BUTTONS_PORT.PIN2CTRL	= PORT_OPC_PULLUP_gc;
	if (this->NUM > 3)
		BUTTONS_PORT.PIN3CTRL	= PORT_OPC_PULLUP_gc;
	if (this->NUM > 4)
		BUTTONS_PORT.PIN4CTRL	= PORT_OPC_PULLUP_gc;
	if (this->NUM > 5)
		BUTTONS_PORT.PIN5CTRL	= PORT_OPC_PULLUP_gc;
	if (this->NUM > 6)
		BUTTONS_PORT.PIN6CTRL	= PORT_OPC_PULLUP_gc;
	if (this->NUM > 7)
		BUTTONS_PORT.PIN7CTRL	= PORT_OPC_PULLUP_gc;
//	Timer.registerUserFunction(&ButtonsScanForPressed, TimerClass::TIME_40MS);
*/
	}
bool ButtonsClass::isButtonLocked(ButtonsClass::BUTTONS button)
	{
	return (this->lockTimers[button] > 0);
	}
bool ButtonsClass::isButtonUnlocked(ButtonsClass::BUTTONS button)
	{
	return !this->isButtonLocked(button);
	}
bool ButtonsClass::isButtonDown(ButtonsClass::BUTTONS button)
	{
	switch(button)
		{
		case ButtonsClass::BUTTONS::BUTTON_CENTER_MENU:
			{
			return PinButtonCenter_Menu::IsPinLow();
			}
		break;
		
		case ButtonsClass::BUTTONS::BUTTON_DOWN_ENTER:
			{
			return PinButtonDown_Enter::IsPinLow();
			}
		break;
		
		case ButtonsClass::BUTTONS::BUTTON_LEFT:
			{
			return PinButtonLeft::IsPinLow();
			}
		break;

		case ButtonsClass::BUTTONS::BUTTON_RIGHT:
			{
			return PinButtonRight::IsPinLow();
			}
		break;

		case ButtonsClass::BUTTONS::BUTTON_UP_ESC:
			{
			return PinButtonUp_Esc::IsPinLow();
			}
		break;
		
		case ButtonsClass::BUTTONS::BUTTONS_NUM://to avoid warnings
			{
			
			}
		break;
		}
	return false;
	}
void ButtonsClass::lockButton (ButtonsClass::BUTTONS button)
	{
	this->lockTimers[button]	= this->LOCK_TIME_MS;
	}
/*
void ButtonsClass::tryUnlockButton(BUTTON_UNLOCK_TIMINGS timePassed)
	{
	if (this->lockTimer > 0)
		{
		if (timePassed == BUTTON_UNLOCK_TIMINGS_100MS)
			{
			this->lockTimer--;
			}
		}
	}
*/
/*
void ButtonsClass::eventUsePressed (void)
	{
	if (Player.isDead())//не жмёт мёртвый на кнопки на данный момент
		{
		return;
		}
	this->eventButtonPressed();
	}
void ButtonsClass::eventMenuPressed (void)
	{
	this->eventButtonPressed();
	if (this->isButtonDown(BUTTON_SELECT))
		{
		PDAMenu.selectMenuID(PDAMenu_MainInterface::MENUID_SELECT_PREV);
		}
	else
		{
		PDAMenu.selectMenuID(PDAMenu_MainInterface::MENUID_SELECT_NEXT);
		}
	}
void ButtonsClass::eventMenuPrevPressed (void)
	{
	this->eventButtonPressed();
	PDAMenu.selectMenuID(PDAMenu_MainInterface::MENUID_SELECT_PREV);
	}
void ButtonsClass::eventSelectPressed (void)
	{
	this->eventButtonPressed();
	}*/
void ButtonsClass::eventButtonPressed (ButtonsClass::BUTTONS button)
	{
	if (PDASettings.isParameterSet(ConfigClass::SETTINGS::SETTINGS_NIGHT_MODE))
		{
		BackLight.turnONFor5sec();
		}
	PDAMenu.buttonPressed(button);
	/*
	switch(button)
		{
		case ButtonsClass::BUTTONS::BUTTON_CENTER_MENU:
			{
			
			}
		break;
		
		case ButtonsClass::BUTTONS::BUTTON_DOWN_ENTER:
			{
			
			}
		break;
		
		case ButtonsClass::BUTTONS::BUTTON_LEFT:
			{
			PDAMenu.selectMenuID(PDAMenu_MainInterface::MENUID_SELECT_PREV);
			}
		break;

		case ButtonsClass::BUTTONS::BUTTON_RIGHT:
			{
			PDAMenu.selectMenuID(PDAMenu_MainInterface::MENUID_SELECT_NEXT);
			}
		break;

		case ButtonsClass::BUTTONS::BUTTON_UP_ESC:
			{
			
			}
		break;
		
		case ButtonsClass::BUTTONS::BUTTONS_NUM://to avoid warnings
			{
			
			}
		break;
		}
	*/
	}
/*
ButtonsClass::BUTTONS ButtonsClass::getOnePressed(void)
	{
	if (PinButtonCenter_Menu::IsPinLow())
		{
		return BUTTON_CENTER_MENU;
		}
	if (PinButtonDown_Enter::IsPinLow())
		{
		return BUTTON_DOWN_ENTER;
		}
	if (PinButtonLeft::IsPinLow())
		{
		return BUTTON_LEFT;
		}
	if (PinButtonRight::IsPinLow())
		{
		return BUTTON_RIGHT;
		}
	if (PinButtonUp_Esc::IsPinLow())
		{
		return BUTTON_UP_ESC;
		}
	}*/
ButtonsClass::BUTTON_STATES ButtonsClass::getState(ButtonsClass::BUTTONS button)
	{
	return this->state[button];
	}
void ButtonsClass::setState(ButtonsClass::BUTTONS button, BUTTON_STATES state)
	{
	this->state[button]	= state;
	}
void ButtonsClass::stateChanged(ButtonsClass::BUTTONS button)
	{
	TODO("make buttons stateChanged() works");
	}
void ButtonsClass::scanForPressed(void)
	{
	for (uint8_t i=0;i<BUTTONS_NUM;i++)//iterate each button
		{
		ButtonsClass::BUTTONS btn	= static_cast<ButtonsClass::BUTTONS>(i);
		switch (this->getState(btn))//prev state
			{
			case BUTTON_STATE_PRESSED:
				{
				if (this->isButtonUnlocked(btn))
					{
					if (!this->isButtonDown(btn))
						{
						this->setState(btn, BUTTON_STATES::BUTTON_STATE_RELEASED);
						this->lockButton(btn);
						}
					}
				}
			break;
			
			case BUTTON_STATE_RELEASED:
				{
				if (this->isButtonUnlocked(btn))
					{
					if (this->isButtonDown(btn))
						{
						this->setState(btn, BUTTON_STATES::BUTTON_STATE_PRESSED);
						this->lockButton(btn);
						this->eventButtonPressed(btn);
						}
					}
				}
			break;
			}
		}
	/*
	if (this->isButtonLocked())
		{
		return;
		}

	if (ButtonMenuPin::IsPinLow())
		{
		PDAMenu.buttonPressed(ButtonsClass::BUTTON_MENU);
		this->eventMenuPressed();
		this->lockButton(BUTTON_LOCK_TIMINGS_50MS);
		}
	else if (ButtonMenuPrevPin::IsPinLow())
		{
		PDAMenu.buttonPressed(ButtonsClass::BUTTON_MENU_PREV);
		this->eventMenuPrevPressed();
		this->lockButton(BUTTON_LOCK_TIMINGS_50MS);
		}
	else if (ButtonSelectPin::IsPinLow())
		{
		PDAMenu.buttonPressed(ButtonsClass::BUTTON_SELECT);
		this->eventSelectPressed();
		this->lockButton(BUTTON_LOCK_TIMINGS_50MS);
		}
	else if (ButtonUsePin::IsPinLow())
		{
		PDAMenu.buttonPressed(ButtonsClass::BUTTON_USE);
		this->eventUsePressed();
		this->lockButton(BUTTON_LOCK_TIMINGS_50MS);
		}
	*/
	}

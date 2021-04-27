// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * ConfigClass.cpp
 *
 * Created: 2015-08-03 15:03:19
 *  Author: tabr
 */ 
#include "ConfigClass.hpp"

ConfigClass::ConfigClass(void)
	{
	this->settings			= this->SETTINGS_EMPTY;
	}
void ConfigClass::loadDefaultSettings(void)
	{
	this->setParameter(SETTINGS::SETTINGS_VIBRO_ON);
	this->setParameter(SETTINGS::SETTINGS_SWITCH_TO_CONNECTED_ITEM);
	this->setParameter(SETTINGS::SETTINGS_SWITCH_TO_CONNECTED_ARTEFACT);
	this->setParameter(SETTINGS::SETTINGS_ARTEFACTS_LEDS_ON);
	this->clearParameter(SETTINGS::SETTINGS_RADIO_ON);
	this->clearParameter(SETTINGS::SETTINGS_BACKLIGHT_ON);
	this->clearParameter(SETTINGS::SETTINGS_NIGHT_MODE);
//	this->clearParameter(ITEMS_USE_IMMIDIATELY);
	}
bool ConfigClass::isParameterSet(uint8_t parameter)
	{
	return (this->settings & (1<<parameter));
	}
void ConfigClass::switchParameter(uint8_t parameter)
	{
	this->settings	^= 1<<parameter;
	this->parameterUpdated(parameter);
	}
void ConfigClass::clearParameter(uint8_t parameter)
	{
	cbi(this->settings, parameter);
	this->parameterUpdated(parameter);
	}
void ConfigClass::setParameter(uint8_t parameter)
	{
	sbi(this->settings, parameter);
	this->parameterUpdated(parameter);
	}
void ConfigClass::parameterUpdated(uint8_t parameter)
	{
	if (this->isParameterSet(ConfigClass::SETTINGS::SETTINGS_BACKLIGHT_ON))
		{
		BackLight.turnON();
		}
	else
		{
		BackLight.turnOFF();
		}
	if (this->isParameterSet(ConfigClass::SETTINGS::SETTINGS_RADIO_ON))
		{
		//Ar1010.hmuteOFF();
		Ar1010.deviceEnable();
		}
	else
		{
		//Ar1010.hmuteON();
		//Ar1010.isDisabled	= true;
		Ar1010.deviceDisable();
		}
	}

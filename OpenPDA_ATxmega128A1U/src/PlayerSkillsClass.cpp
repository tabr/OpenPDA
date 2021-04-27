// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * PlayerSkillsClass.cpp
 *
 * Created: 2015-07-17 23:58:30
 *  Author: tabr
 */ 

//#include "PlayerSkillsClass.h"

//uint8_t* PlayerSkillsClass::container	= &EEPROM_Data.data[EEPROM_STRUCT_PLAYER_SKILLS];


bool PlayerSkillsClass::setValue(SkillID_t SID, uint8_t value)
	{
		
	if (SID >= this->SKILLS_NUM)
		{
		return false;
		}
	if (value > this->MAX_VALUE)
		{
		return false;
		}
	if (this->isSkillUnknown(SID) && this->isMaxSkillsReached())
		{
		return false;
		}
	//sprintf (lcd_buf, "%05u %05u %d",MemoryManager.POOL_SIZE, MemoryManager.pointerTop, MemoryManager.fail);LcdString(1,LCD_LINE_6);LcdUpdate();while(1);
	//this->setValue(SID, value);
	this->container[SID]	= value;
	return true;
	}
bool PlayerSkillsClass::increaseValue(SkillID_t SID, uint8_t value)
	{
/*
	if (SID >= this->SKILLS_NUM)
		{
		return false;
		}
	if (this->container[SID] == this->MAX_VALUE)
		{
		return false;
		}
	if (this->isSkillUnknown(SID) && this->isMaxSkillsReached())
		{
		return false;
		}
*/		

	if (value > this->MAX_VALUE)
		{
		value	= MAX_VALUE;
		}
	if (this->getValue(SID) > (this->MAX_VALUE - value))
		{
		value	= this->MAX_VALUE;
		}
	return this->setValue(SID, (this->getValue(SID) + value));
//	this->container[SID]	+= value;
//	return true;
	}
bool PlayerSkillsClass::isMaxSkillsReached(void)
	{
	uint8_t numSkills	= 0;
	for (uint8_t i=0;i<this->SKILLS_NUM;i++)
		{
		if (this->getValue(i) > 0)
			{
			if (++numSkills >= this->MAX_SKILLS)
				{
				return true;
				}
			}
		}
	return false;
	}
bool PlayerSkillsClass::isSkillKnown(SkillID_t SID)
	{
	return (this->getValue(SID) > 0);
	}
bool PlayerSkillsClass::setSkillKnown(SkillID_t SID)
	{
	if (this->isSkillKnown(SID))
		{
		return false;
		}
	if (this->isMaxSkillsReached())
		{
		return false;
		}
	this->container[SID]=1;
	return true;
	}
bool PlayerSkillsClass::isSkillUnknown(SkillID_t SID)
	{
	return !(this->isSkillKnown(SID));
	}
uint8_t PlayerSkillsClass::getSkills(uint8_t* data)
	{
	uint8_t numSkills	= 0;
	uint8_t j			= 0;
	for (uint8_t i = 0; i < this->SKILLS_NUM; i++)
		{
		if (this->getValue(i) > 0)
			{
			if (++numSkills > this->MAX_SKILLS)//if more then need
				{
				--numSkills;//делаю не больше MAX_SKILLS
				this->setValue(i, 0);
				}
			else
				{
				data[j]	= this->getValue(i);
				}
			}
		}
	return numSkills;
	}
uint8_t PlayerSkillsClass::getValue(SkillID_t SID)
	{
	return this->container[SID];
	}
char* PlayerSkillsClass::getName(SkillID_t SID)
	{
	switch (SID)
		{
		case this->SKILL_BREAKING:
			{
			return (char*)"ВзломЗамков";
			}
		break;

		case this->SKILL_CHEMICAL:
			{
			return (char*)"Химия      ";
			}
		break;

		case this->SKILL_COMPUTER:
			{
			return (char*)"Комп.взлом ";
			}
		break;

		case this->SKILL_DOCTOR:
			{
			return (char*)"Доктор     ";
			}
		break;

		case this->SKILL_FARMER:
			{
			return (char*)"Фермер     ";
			}
		break;

		case this->SKILL_FIRST_AID:
			{
			return (char*)"Перв.пом   ";
			}
		break;

		case this->SKILL_MELE_WEAPON:
			{
			return (char*)"Хол.оружие ";
			}
		break;

		case this->SKILL_RANGE_WEAPON:
			{
			return (char*)"Огн. оружие";
			}
		break;

		case this->SKILL_TECH:
			{
			return (char*)"Техник     ";
			}
		break;

		case this->SKILL_ENERGY_WEAPON:
			{
			return (char*)"Энер.оружие";
			}
		break;

		/*case this->:
			{
			return (char*)"";
			}
		break;*/
		}
	return (char*)"неизв";
	}
void PlayerSkillsClass::EEPROM_init(void)
	{
	this->container	= EEPROM_Data.getParameterAddr(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_SKILLS);
	}
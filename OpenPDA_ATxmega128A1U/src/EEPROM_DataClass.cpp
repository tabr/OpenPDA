// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * EEPROM_DataClass.cpp
 *
 * Created: 30.10.2015 17:59:48
 *  Author: tabr
 */ 
#include "EEPROM_DataClass.hpp"

bool EEPROM_DataClass::save(void)
	{
	//!!!SAVE CURRENT SUITE!!!
	return true;
	/*
	QuestInstance* qContainer	= Quest.getContainer();
	for (uint8_t QID=1;QID<TemporaryClass::QUESTS_NUM;QID++)
		{
		this->data[EEPROM_STRUCT_PLAYER_QUESTS + QID]	= qContainer[QID].getStatus();
		}

	eeprom_busy_wait();
	eeprom_write_block(this->data, 0, EEPROM_STRUCT_SIZE);*/
	}
bool EEPROM_DataClass::load(void)
	{
	//!!!LOAD CURRENT SUITE!!!
	if (this->data == NULL)
		{
		//LcdClearCache();LcdStringUpdate(1,LCD_LINE_1, (char*)"bug[4]");while(1);
		return false;
		}	//char name[TemporaryClass::PLAYER_NAME_LENGTH];
	//memset(name,0,)
	this->setParameter(EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_VARS, EEPROM_DataClass::PLAYER_VARS::PLAYER_VAR_CURRENT_HP,	90);
	this->setParameter(EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_VARS, EEPROM_DataClass::PLAYER_VARS::PLAYER_VAR_MAX_HP,		100);
	this->setParameter(EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_VARS, EEPROM_DataClass::PLAYER_VARS::PLAYER_VAR_REGEN_TIME,	120);
	this->setParameter(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_VARS, EEPROM_DataClass::PLAYER_VARS::PLAYER_VAR_FACTION_ID, 2);
	/*
	this->data[EEPROM_STRUCT_PLAYER_DEFENCE_RADIATION_EXT_SELF]	= 0;
	this->data[EEPROM_STRUCT_PLAYER_DEFENCE_RADIATION_INT_SELF]	= 0;
	this->data[EEPROM_STRUCT_PLAYER_DEFENCE_GRAVY_SELF]			= 0;
	this->data[EEPROM_STRUCT_PLAYER_DEFENCE_ELECTRO_SELF]		= 0;
	this->data[EEPROM_STRUCT_PLAYER_DEFENCE_FIRE_SELF]			= 0;
	this->data[EEPROM_STRUCT_PLAYER_DEFENCE_CHEMICAL_SELF]		= 0;
	this->data[EEPROM_STRUCT_PLAYER_DEFENCE_PSY_SELF]			= 0;
	this->data[EEPROM_STRUCT_PLAYER_DEFENCE_BIO_SELF]			= 0;
	this->data[EEPROM_STRUCT_PLAYER_RADIATION_DOSE]				= 0;
	this->data[EEPROM_STRUCT_PLAYER_CURRENT_HEALTH]				= 90;//GameCFG.getStartPlayerHealth();
	this->data[EEPROM_STRUCT_PLAYER_MAX_HEALTH]					= 100;
	this->data[EEPROM_STRUCT_PLAYER_REGEN_TIME]					= GameCFG.getDefaultRegenValue();
	this->data[EEPROM_STRUCT_PLAYER_CURRENT_SUITE_ID]			= TemporaryClass::SUITE_ID_NONE;
	this->data[EEPROM_STRUCT_PLAYER_CURRENT_SUITE_DURABILITY_H]	= 0;
	this->data[EEPROM_STRUCT_PLAYER_CURRENT_SUITE_DURABILITY_L]	= 1;
	*/
	//memcpy(this->data, this->data2, EEPROM_STRUCTURE_SIZE);
	
	//memcpy (&this->data[EEPROM_STRUCT_PLAYER_NAME],"υσι",4);
	//Player.SetFactionID(TemporaryClass::FACTION_NONE);
	//Quest.GiveQuest(TemporaryClass::QID_FIRST);
	//#warning removed PlayerLoad()
	TODO("restore removed PlayerLoad()");
	/*
	eeprom_busy_wait();
	eeprom_read_block(this->data, 0, EEPROM_STRUCT_SIZE);
	
	
	QuestInstance* qContainer	= Quest.getContainer();
	for (uint8_t QID=1;QID<TemporaryClass::QUESTS_NUM;QID++)
		{
		qContainer[QID].setStatus(this->data[EEPROM_STRUCT_PLAYER_QUESTS + QID]);
		//Quest.container[QID].setStatus(this->data[EEPROM_STRUCT_PLAYER_QUESTS + QID]);
		}
	*/
	return true;
	}
void EEPROM_DataClass::setDataSize(EEPROM_DataClass::EEPROM_STRUCTURE parameter, EEPROM_DataSize_t size)
	{
	this->dataSize[parameter]	= size;
	}
bool EEPROM_DataClass::setDataSize(uint8_t parameter, EEPROM_DataSize_t size)
	{
	if (parameter < EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_SIZE)
		{
		this->dataSize[static_cast<EEPROM_DataClass::EEPROM_STRUCTURE>(parameter)]	= size;
		return true;
		}
	return false;
	}
PlayerDefenceValue_t* EEPROM_DataClass::getParameterAddr(EEPROM_DataClass::EEPROM_STRUCTURE parameter)
	{
	if (this->data == NULL)
		{
		return NULL;
		//LcdClearCache();LcdStringUpdate(1,LCD_LINE_1, (char*)"bug[1]");while(1);
		}
	return this->dataAddress[parameter];
	}
PlayerDefenceValue_t* EEPROM_DataClass::getParameterAddr(EEPROM_DataClass::EEPROM_STRUCTURE parameter, uint8_t subParameter)
	{
	if (this->data == NULL)
		{
		return NULL;
		//LcdClearCache();LcdStringUpdate(1,LCD_LINE_1, (char*)"bug[2]");while(1);
		}
	return this->dataAddress[parameter] + subParameter;
	}
bool EEPROM_DataClass::finishConfiguration(void)
	{
	uint16_t addrCounter=0;
	TODO('add checks here');
	if (this->data != NULL)
		{
		return false;
		//LcdClearCache();LcdStringUpdate(1,LCD_LINE_1, (char*)"bug[5]");while(1);
		}
	for (uint8_t i=0; i<EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_SIZE ; i++)
		{
		addrCounter+=this->dataSize[i];
		}
	this->data	= new uint8_t[addrCounter];
	memset(this->data,0,addrCounter);
	addrCounter	= 0;
	for (uint8_t i=0; i<EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_SIZE ; i++)
		{
		this->dataAddress[i]	= this->data + addrCounter;
		addrCounter+=this->dataSize[i];
		}
	
	Player.EEPROM_init();
	return true;
	}
bool EEPROM_DataClass::setParameter (EEPROM_DataClass::EEPROM_STRUCTURE section, uint8_t subParameter, uint8_t value)
	{
	if (this->data == NULL)
		{
		//LcdClearCache();LcdStringUpdate(1,LCD_LINE_1, (char*)"bug[3]");while(1);
		return false;
		}
	uint8_t *ptr	= this->getParameterAddr(section) + subParameter;
	*ptr			= value;
	return true;
	}
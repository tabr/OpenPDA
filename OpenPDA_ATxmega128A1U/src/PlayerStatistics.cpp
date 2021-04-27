// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * PlayerStatistics.cpp
 *
 * Created: 2015-04-12 20:27:38
 *  Author: tabr
 */ 
//#include "src/playerStatistics.h"
PlayerStatisticsClass::PlayerStatisticsClass (void)
	{
//	this->playerDeathNum	= &EEPROM_Data.data[EEPROM_STRUCT_PLAYER_STATISTICS_DEATH];
//	this->itemsUsed			= &EEPROM_Data.data[EEPROM_STRUCT_PLAYER_STATISTICS_ITEMS_USED];
	};
void PlayerStatisticsClass::playerDeathIncrement(void)
	{
	if (*this->playerDeathNum == 0xFF)
		{
		return;
		}
	(*this->playerDeathNum)++;
	}
void PlayerStatisticsClass::playerMedicamentUseIncrement(uint8_t medicament)
	{
	if (this->itemsUsed[medicament] == 0xFF)
		{
		return;
		}
	this->itemsUsed[medicament]++;
	}
void PlayerStatisticsClass::EEPROM_init(void)
	{
	this->playerDeathNum	= EEPROM_Data.getParameterAddr(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_STATISTICS, 0);
	this->itemsUsed			= EEPROM_Data.getParameterAddr(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_STATISTICS, 1);
	}
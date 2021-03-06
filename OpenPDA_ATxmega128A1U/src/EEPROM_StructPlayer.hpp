/*
  *  EEPROM_StructPlayer.h
  *
  *  Created:  2015-04-11  21:38:49
  *    Author:  tabr
  */  


#ifndef  EEPROM_STRUCTPLAYER_H_
#define  EEPROM_STRUCTPLAYER_H_

#include  "GameTemplate_TemporaryClass.hpp"
#include  "PlayerSkillsClass.hpp"
#include  "typedefs.h"



/*
enum  EEPROM_STRUCT_PLAYER
  {
  EEPROM_STRUCT_VERSION_H,
  EEPROM_STRUCT_VERSION_L,
  EEPROM_STRUCT_PLAYER_DEFENCE_NONE,
  EEPROM_STRUCT_PLAYER_DEFENCE_GENERIC,
  EEPROM_STRUCT_PLAYER_DEFENCE_RADIATION_EXT_SELF,
  EEPROM_STRUCT_PLAYER_DEFENCE_RADIATION_INT_SELF,
  EEPROM_STRUCT_PLAYER_DEFENCE_FIRE_SELF,
  EEPROM_STRUCT_PLAYER_DEFENCE_ELECTRO_SELF,
  EEPROM_STRUCT_PLAYER_DEFENCE_CHEMICAL_SELF,
  EEPROM_STRUCT_PLAYER_DEFENCE_GRAVY_SELF,
  EEPROM_STRUCT_PLAYER_DEFENCE_PSY_SELF,
  EEPROM_STRUCT_PLAYER_DEFENCE_BIO_SELF,
  EEPROM_STRUCT_PLAYER_DEFENCE_BLOWOUT_SELF,
  EEPROM_STRUCT_PLAYER_NAME,
  EEPROM_STRUCT_PLAYER_STATISTICS_DEATH  =  EEPROM_STRUCT_PLAYER_NAME  +  TemporaryClass::PLAYER_NAME_LENGTH,
  EEPROM_STRUCT_PLAYER_STATISTICS_ITEMS_USED,
  EEPROM_STRUCT_PLAYER_SKILLS        =  EEPROM_STRUCT_PLAYER_STATISTICS_ITEMS_USED+  TemporaryClass::ITEMS_NUM,
  EEPROM_STRUCT_PLAYER_QUESTS        =  EEPROM_STRUCT_PLAYER_SKILLS  +  PlayerSkillsClass::SKILLS_NUM,
  EEPROM_STRUCT_PLAYER_ID          =  EEPROM_STRUCT_PLAYER_QUESTS  +  TemporaryClass::QUESTS_NUM,
  EEPROM_STRUCT_PLAYER_FACTION,
  EEPROM_STRUCT_PLAYER_CURRENT_HEALTH,
  EEPROM_STRUCT_PLAYER_RADIATION_DOSE,
  EEPROM_STRUCT_PLAYER_MAX_HEALTH,
  EEPROM_STRUCT_PLAYER_REGEN_TIME,
  EEPROM_STRUCT_PLAYER_CURRENT_SUITE_ID,
  EEPROM_STRUCT_PLAYER_CURRENT_SUITE_DURABILITY_H,
  EEPROM_STRUCT_PLAYER_CURRENT_SUITE_DURABILITY_L,
  EEPROM_STRUCT_SIZE,
  };
*/
//#define  PLAYER_ID  EEPROM_Data.data[EEPROM_STRUCT_PLAYER_ID]

#endif  /*  EEPROM_STRUCTPLAYER_H_  */

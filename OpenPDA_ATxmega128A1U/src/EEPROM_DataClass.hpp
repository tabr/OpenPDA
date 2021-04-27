/*
 * EEPROM_DataClass.h
 *
 * Created: 30.10.2015 17:59:39
 *  Author: tabr
 */ 


#ifndef EEPROM_DATACLASS_H_
#define EEPROM_DATACLASS_H_

#include "GameConfig.hpp"
#include "GameTemplate_TemporaryClass.hpp"
#include "QuestClass.hpp"
#include "PlayerClass.hpp"
#include "typedefs.h"

extern QuestClass Quest;
//extern PlayerClass Player;

class EEPROM_DataClass
  {
  public:
    enum EEPROM_STRUCTURE
      {
      EEPROM_STRUCTURE_VERSION,        //16bit value
      EEPROM_STRUCTURE_PLAYER_DEFENCE_SELF,  //array
      EEPROM_STRUCTURE_PLAYER_NAME,      //char[14]
      EEPROM_STRUCTURE_PLAYER_STATISTICS,    //array
      EEPROM_STRUCTURE_PLAYER_SKILLS,
      EEPROM_STRUCTURE_QUESTS,        //array
      EEPROM_STRUCTURE_PLAYER_VARS,      //array [id,faction,currHP,maxHP,regenTime,currentSuite,currentRadDose...]
      EEPROM_STRUCTURE_PLAYER_ACTIVE_EFFECTS,  //array
      EEPROM_STRUCTURE_SIZE
      };
    enum PLAYER_VARS//in bytes
      {
      PLAYER_VAR_PLAYER_ID,    //1
      PLAYER_VAR_FACTION_ID,    //1
      PLAYER_VAR_CURRENT_HP,    //1
      PLAYER_VAR_CURRENT_RAD_DOSE,
      PLAYER_VAR_MAX_HP,      //1
      PLAYER_VAR_REGEN_TIME,    //1
      PLAYER_VAR_CURRENT_SUITE_ID,
      PLAYER_VAR_CURRENT_SUITE_DURABILITY_H,
      PLAYER_VAR_CURRENT_SUITE_DURABILITY_L,
      PLAYER_VARS_SIZE
      };
    
    //uint8_t playerName[TemporaryClass::PLAYER_NAME_LENGTH];
    //uint8_t playerDefenceRadiationSelf;
    //uint8_t playerResistantRadiationSelf;
    //uint8_t playerDefenceGravySelf;
    //uint8_t playerDefenceElectroSelf;
    //uint8_t playerDefenceFireSelf;
    //uint8_t playerDefenceChemicalSelf;
    //uint8_t playerDefencePsySelf;
    //uint8_t playerDefenceBio;
    //uint8_t playerRadiationDose;
    //uint8_t playerCurrentHealth;
    //uint8_t playerMaxHealth;
    //uint8_t playerRegenTime;
    //uint8_t playerSuiteParameters[TemporaryClass::SUITE_PARAMETERS_NUM];
    
    bool load(void);
    bool save(void);
    PlayerDefenceValue_t* getParameterAddr(EEPROM_DataClass::EEPROM_STRUCTURE parameter);
    PlayerDefenceValue_t* getParameterAddr(EEPROM_DataClass::EEPROM_STRUCTURE parameter, uint8_t subParameter);
    void setDataSize(EEPROM_DataClass::EEPROM_STRUCTURE parameter, EEPROM_DataSize_t size);
    bool setDataSize(uint8_t parameter, EEPROM_DataSize_t size);
    bool finishConfiguration(void);            //calculate addresses
    bool setParameter (EEPROM_DataClass::EEPROM_STRUCTURE section, uint8_t subParameter, uint8_t value);
    EEPROM_DataClass(void)
      {
      memset(this->dataSize, 0, sizeof(this->dataSize));
      //memset(this->dataAddress, nullptr, sizeof(this->dataAddress));
      //this->data  = new uint8_t[100];
      //memset(this->data,0,100);
      //this->data    = (uint8_t*)MemoryManager.allocate(100);
      //memset(this->data,0,EEPROM_STRUCT_SIZE);
      
      //memset(this->data,0,EEPROM_STRUCT_SIZE); moved to finishConfiguration
      }
  protected:
  private:
    EEPROM_DataSize_t dataSize[EEPROM_STRUCTURE::EEPROM_STRUCTURE_SIZE];
    uint8_t* dataAddress[EEPROM_STRUCTURE::EEPROM_STRUCTURE_SIZE];
    //uint8_t& prt  = dataSize[1];
    //uint8_t data[EEPROM_STRUCT_SIZE];
    uint8_t* data  = nullptr;//(uint8_t*)MemoryManager.allocate(EEPROM_STRUCT_SIZE);
  } ;




#endif /* EEPROM_DATACLASS_H_ */
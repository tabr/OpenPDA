/*
 * typedefs.h
 *
 * Created: 24.01.2016 23:57:47
 *  Author: tabr
 */ 

#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

//#include <avr/pgmspace.h>
typedef uint8_t MemoryPool_t;
#ifndef TEMPORARY_CLASS_H
#include "GameTemplate_TemporaryClass.hpp"
#endif
typedef uint8_t ArtefactID_t;
//typedef const char* ArtefactName;
typedef char* ArtefactName_t;
typedef char* DamageSourceName_t;
typedef uint8_t ArtefactsSize_t;
typedef uint8_t TWI_Data_t;
typedef uint16_t TimerMS_t;
typedef uint8_t Percent_t;
typedef uint16_t PlayerHealth_t;
typedef uint8_t PlayerRegenTime_t;
typedef uint8_t RadiationDose_t;
typedef uint8_t PlayerDefenceValue_t;
typedef uint8_t FactionID_t;
typedef uint8_t FactionCounter_t;
typedef char* FactionName_t;
typedef uint8_t PlayerID_t;
typedef uint16_t PlayerDeathTimer_t;
typedef uint8_t EffectID_t;
typedef uint8_t PlayerEffectsPoolSize_t;
typedef uint8_t PlayerEffectsDefenceValue_t;
typedef uint8_t SkillID_t;
typedef uint8_t EEPROM_DataSize_t;
typedef uint16_t SuitDurabiluty_t;
typedef uint8_t SuitID_t;
typedef uint8_t SuitContainersNum_t;
typedef uint8_t SuitsContainerSize_t;
//typedef const char* SuitName;
typedef char* SuitName_t;
typedef char* PlayerName_t;
typedef uint8_t DamageDefenceValue_t;
typedef uint8_t DamageSourceCounter_t;
typedef uint8_t DamageSourceValuer_t;
#ifdef TEMPORARY_CLASS_H
typedef TemporaryClass::DamageSource DamageSource_t;
#endif // TEMPORARY_CLASS_H
typedef uint8_t DamageSourceNew_t;
typedef uint8_t DamageSourceNewID_t;

typedef uint16_t DamageValue_t;
typedef uint16_t CharacteristicsValue_t;
typedef uint8_t CharacteristicsBitLength_t;
typedef uint8_t DamageSourcesNum_t;

typedef uint8_t RadiomarkContainer_t;
typedef uint8_t RadiomarkRSSI_t;
typedef uint8_t RadiomarkID_t;
typedef uint8_t RadiomarkType_t;
typedef uint8_t RadiomarkParameter_t;


typedef char* ItemName_t;
typedef uint8_t RM_SignalPower_t;
typedef uint8_t ItemID_t;
typedef uint8_t EepromDataSize_t;
typedef EepromDataSize_t EepromItemArray_t;

typedef uint8_t ConnectedItemArray_t;
typedef uint8_t ItemsNum_t;
typedef uint8_t ItemType_t;
typedef uint8_t ItemChargesNum_t;
typedef uint8_t RepairKitPCS_t;
typedef uint8_t ResourcePCS_t;
typedef uint8_t SuicideTimer_t;
typedef uint8_t PlayerStatus_t;
typedef uint16_t Milivolts_t;

typedef uint8_t AnomalyID_t;
typedef uint8_t AnomaliesNum_t;
typedef char* AnomalyName_t;
//typedef uint8_t PlayerAggressor;
//typedef uint8_t damageSource;
typedef uint8_t AnomalyType_t;
typedef uint8_t DeviceID_t;



typedef uint8_t ResourceID_t;
typedef uint8_t ResourcesNum_t;
typedef uint8_t ResourceRelValue_t;
typedef uint8_t ResourceGroupID_t;
typedef uint8_t ResourceTechLevel_t;
typedef char* ResourceName_t;

typedef uint8_t RecipeID_t;
typedef uint8_t EquipmentID_t;
typedef char* EquipmentName_t;
typedef uint16_t EquipmentList_BitField_t;

typedef uint8_t EffectsStorageID_t;
typedef uint8_t PlayerEffectGUID_t;
typedef char* EffectName_t;
typedef uint8_t PE_CFG_t;
typedef uint8_t TimeHour_t;
typedef uint8_t TimeMinute_t;
typedef uint8_t TimeSecond_t;
typedef uint8_t PE_RepeatTimes_t;
typedef uint8_t TimeUpdate_t;

typedef const PROGMEM char* FLASH_VAR_t;
//typedef FLASH_VAR_t ItemTypeName_t;
//typedef STR_POS ItemTypeName_t;

typedef uint8_t NodeProcessorID_t;
typedef uint8_t NodeExtendedID_t;

enum QUEST_STATUS
  {
  QUEST_STATUS_UNKNOWN,
  QUEST_STATUS_INCOMPLETE,
  QUEST_STATUS_COMPLETE,
  QUEST_STATUS_FAILED,
  QUEST_STATUS_NUM_STATUSES
  };
typedef uint8_t playableSample;

typedef uint8_t QuestID_t;
//typedef uint8_t QuestStatus_t;
typedef QUEST_STATUS QuestStatus_t;
typedef uint8_t QuestNum_t;
typedef uint8_t QuestNameLength_t;
typedef char* QuestName_t;
//typedef const PROGMEM char* ItemTypeName1_t;
typedef FLASH_VAR_t QuestStatusName_t;

#endif /* TYPEDEFS_H_ */
/*
 * Suits.h
 *
 * Created: 2015-02-21 19:05:06
 *  Author: tabr
 */ 


#ifndef SUITS_H_
#define SUITS_H_
/*
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <avr/io.h>
#include <string.h>

#include "boards/compiler_defines.h"
#include <util/delay.h>

#include "TODOmacro.h"


*/
#include "MemoryManager.hpp"
#include "PlayerSuitClass.hpp"
#include "GameCharacteristicsClass.hpp"
#include "typedefs.h"
//extern MemoryManagerClass MemoryManager;


#warning "[T] make register suit inside constructor!"
class SuitTemplateInstance : public GameCharacteristicsInterface, public NodeExtended
  {
  public:
    //SuitDurabiluty maxDurability;
    //SuitContainersNum containers;

    const static uint8_t SUIT_NAME_MAX_LENGTH        = 14+1;//16 chars + 1 empty string
//    void setProperties(char* tmpName, SuitDurabiluty suitMaxDurability, uint8_t containers, PlayerDefenceValue* defences);
    //void setProperties(char* tmpName, SuitDurabiluty suitMaxDurability, uint8_t containers, PlayerDefenceValue* defences);
    //void setProperties(char* tmpName, PlayerDefenceValue_t* defences, GameCharacteristicsClass* c);
    DamageSourceContainerClass* GetDefences(void);
    SuitName_t GetName(void);
    SuitID_t GetID(void);
//    GameCharacteristicsClass* GetCharacteristics(void);
    SuitTemplateInstance(SuitID_t id, char* tmpName, DamageSourceContainerClass*  SuitDef, GameCharacteristicsClass* c);
  protected:
  private:
    SuitID_t ID                    = 0;
    SuitName_t Name                  = NULL;
    DamageSourceContainerClass* DefenceContainer  = NULL;
//    GameCharacteristicsClass* GameCharacteristics=NULL;
  };




#endif /* SUITS_H_ */
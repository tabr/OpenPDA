#ifndef ARTEFACT_CLASS_H
#define ARTEFACT_CLASS_H

#include <stdio.h>

#include "MemoryManager.hpp"
#include "typedefs.h"
#include "PlayerEffectsInterface.hpp"

//extern MemoryManagerClass MemoryManager;

class ArtefactClass
  {
  public:

//    const static char NAMES[TemporaryClass::ARTEFACTS_NUM][11];//ниже

    
    //const uint8_t nameArray[ARTEFACTS_NUM][8] PROGMEM = {}
    //const uint8_t nameArray[8] PROGMEM = {sprintf()}


    ArtefactClass(void);
    void setArtefactRAW(ArtefactID_t AID);        //задать артефакт
//    void applyEffects(void);            //применить эффекты заданного арта
//    void removeEffects(void);            //снять эффекты заданного арта
    void connect(void);                //TODO
    void disconnect(void);              //отключить арт
    bool isArtefactValid(ArtefactID_t AID);      //проверяем валидность арта =)
    bool isArtefactValid(void);            //проверяем валидность арта =)
    bool isEmpty(void);                //проверяем Пуст ли арт=)
    bool isNotEmpty(void);                //проверяем Пуст ли арт=)
//    ArtefactName getArtefactName(ArtefactID AID);
    ArtefactName_t getArtefactName(void);
    ArtefactID_t getArtefactID(void);
  protected:
  private:
    ArtefactID_t m_ID=0;
    ArtefactID_t SID=0;
  };
class GameTemplate_ArtefactInstanceClass : public NodeExtended
  {
  public:
    GameTemplate_ArtefactInstanceClass(ArtefactID_t AID,ArtefactName_t tmpName, PlayerEffects_Interface* PlayerEffect);
    GameTemplate_ArtefactInstanceClass(void);
    void Init(ArtefactID_t AID,ArtefactName_t tmpName, PlayerEffects_Interface* PlayerEffect);
    ArtefactName_t GetName(void);
    ArtefactID_t GetID(void);
    PlayerEffects_Interface* GetEffect(void);

  protected:
  private:
    ArtefactName_t Name=NULL;
    PlayerEffects_Interface* m_PlayerEffect;
    ArtefactID_t ID=0;
  };
class GameTemplate_ArtefactsContainerClass : public NodeProcessor
  {
  public:
    const static uint8_t ARTEFACTID_NONE      = 0;

    //void setContainerSize(ArtefactsSize_t size);//нулевой тоже нужно указывать
    void RegisterNew(ArtefactID_t AID, ArtefactName_t tmpName, PlayerEffects_Interface* PlayerEffect);
    GameTemplate_ArtefactsContainerClass(void);
    void setSize_full(uint8_t size);
    uint8_t getSize_Full(void);
    uint8_t getSize_UserConfigured(void);
    uint8_t getMaximumArtefactId(void);
    ArtefactName_t getName(ArtefactID_t AID);
    GameTemplate_ArtefactInstanceClass* GetArtefactInstance(ArtefactID_t AID);
    GameTemplate_ArtefactInstanceClass* GetContainer(void);
  protected:
  private:
    ArtefactsSize_t m_sizeFull;
    ArtefactsSize_t m_registeredArtefactsCounter;
    GameTemplate_ArtefactInstanceClass container;
    
  };

#endif
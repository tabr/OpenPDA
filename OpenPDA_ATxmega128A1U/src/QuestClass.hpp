#ifndef  QUEST_CLASS_H
#define  QUEST_CLASS_H

#include  <stdint.h>
#include  <stddef.h>
#include  <stdio.h>
#include  <avr/io.h>
#include  <string.h>
#include "strings.h"


//#include  "MemoryManager.h"
//#include  "stalker/LcdClass.h"
//#include  "Sounds.h"
//extern  MemoryManagerClass  MemoryManager;
//extern  LcdClass  Lcd;
//extern  Sound  PDASound;

#include  "typedefs.h"
#include  "Node.hpp"

class  QuestInstance : public NodeExtended
  {
  public:
    QuestName_t  GetName(void);
//    void  SetProperties(QuestName_t  tmpName);
//    void  SetProperties(QuestInstance  src);
//    QuestNameLength_t  GetNameLength(void);
    QuestStatus_t  GetStatus(void);
    void  SetStatus(QuestStatus_t  status);
    QuestInstance(void);
    QuestInstance(QuestID_t  QID,  QuestName_t  N,  QuestID_t  nextQuest=0);
    QuestID_t  GetID(void);
    QuestID_t  GetNextQuestID(void);
  protected:
  private:
    QuestStatus_t  Status  =  QuestStatus_t::QUEST_STATUS_UNKNOWN;
    QuestName_t  Name    =  NULL;
//    QuestNameLength_t  NameLength;
    QuestID_t  ID      =  0;
    QuestID_t  next      =  0;
  };

class  QuestClass : public NodeProcessor
  {
  public:
    const static uint8_t  QID_NONE        =  0;

//    const static uint8_t  QUESTS_NUM        =  3;
/*
    enum  QUEST_STATUS
      {
      QUEST_STATUS_UNKNOWN,
      QUEST_STATUS_INCOMPLETE,
      QUEST_STATUS_COMPLETE,
      QUEST_STATUS_FAILED,
      };
*/
    //const static uint8_t  STATUS_UNKNOWN      =  0;
    //const static uint8_t  STATUS_INCOMPLETE    =  1;
    //const static uint8_t  STATUS_COMPLETE    =  2;
    //const static uint8_t  STATUS_FAILED      =  3;
    const static uint8_t  QUEST_NAME_LENGTH    =  28;

//    const static uint8_t  PARAMETER_ID      =  0;
//    const static uint8_t  PARAMETER_STATUS    =  1;
//    const static uint8_t  PARAMETERS_NUM    =  2;

//    uint8_t  QuestList[QuestClass::QUESTS_NUM][QuestClass::PARAMETERS_NUM];
//    uint8_t  QuestList[QuestClass::QUESTS_NUM];//status

//    void  SetNewQuestState(QuestID_t  QID);
    void  FailQuest  (QuestID_t  QID);
    void  GiveQuest  (QuestID_t  QID);
    void  CompleteQuest(QuestID_t  QID);
    void  RemoveQuest(QuestID_t  QID);
    QuestNum_t  GetRegisteredQuestsNum(void);
    QuestNum_t  GetKnownList(QuestInstance  *data[]);
    bool  IsKnown(uint8_t  questID);
    bool  IsInProgress(QuestID_t  QID);
    QuestStatus_t  GetStatus(QuestID_t  QID);
    QuestStatus_t  StatusFromInt(uint8_t  intStatus);
    void  GetQuestStatusName(QuestStatus_t  status, char* buffer);
    STR_POS  GetQuestStatusNamePOS(QuestStatus_t  status);
    QuestName_t  GetQuestName(QuestID_t  QID);
    QuestNameLength_t  GetNameLength(QuestID_t  QID);

    void  RegisterNew(QuestID_t  QID,  QuestName_t  tmpName,  QuestID_t  nextQuest=0);
    NodeExtended*  GetContainer(void);
    QuestInstance*  GetQuestInstance(QuestID_t  QID);
    QuestClass(void);
  protected:
  private:
    void  SetIncomplete(QuestID_t  QID);
    void  SetComplete(QuestID_t  QID);
    void  SetFailed(QuestID_t  QID);
    void  SetUnknown(QuestID_t  QID);
    void  SetStatus(QuestID_t  QID,  QuestStatus_t  status);
//    QuestNum_t  GetContainerSize(void);

    QuestInstance  container;
//    QuestInstance  QuestNone;
    //QuestNum_t  Num;
    QuestNum_t  registeredQuestCounter=0;
  };
#endif
#ifndef  ANOMALY_CLASS_H
#define  ANOMALY_CLASS_H

#include  "DamageClass.hpp"
#include  "typedefs.h"
#include  "Node.hpp"

class  AnomalyInstance : public NodeExtended
  {
  public:

//    void  setProperties(AnomalyName  tmpName,  damageSource  dmgSrc)  //ВНИМАНИЕ!!!  Сначала  нужно  задать  размер  массива  контейнера!!!  Вызывать  ЕДИНОЖДЫ!!!
//    void  setProperties(AnomalyName  tmpName,  DamageClass::DamageSource  dmgSrc);  //ВНИМАНИЕ!!!  Сначала  нужно  задать  размер  массива  контейнера!!!  Вызывать  ЕДИНОЖДЫ!!!
//    void  setProperties(AnomalyName  tmpName,  DamageSource_t  dmgSrc);  //ВНИМАНИЕ!!!  Сначала  нужно  задать  размер  массива  контейнера!!!  Вызывать  ЕДИНОЖДЫ!!!
//    void  setProperties(AnomalyInstance  src);
    DamageSource_t  GetDamageSource(void);
    AnomalyName_t  GetName(void);
    AnomalyInstance*  GetNextNode(void);
    AnomalyID_t  GetID(void);

    AnomalyInstance(AnomalyID_t  AID,  AnomalyName_t  tmpName,  DamageSource_t  dmgSrc);  //ВНИМАНИЕ!!!  Сначала  нужно  задать  размер  массива  контейнера!!!  Вызывать  ЕДИНОЖДЫ!!!
    AnomalyInstance(AnomalyInstance*  src);
    AnomalyInstance(void);
  protected:
  private:
    AnomalyID_t  ID;
    char  *Name;
    DamageSource_t  Source;
    
  };

class  AnomalyClass : public ITimerListener,  public  NodeProcessor
  {
  public:
    const  static  AnomalyType_t  AID_NONE            =  0;
    const  static  AnomalyType_t  MAX_ANOMALY_LEVEL        =  100;
	//const  static uint8_t ANOMALY_STRENGHT_MIN_LEVEL = 4;
    const static uint16_t  ANOMALY_SOUND_THRESHOLD      =  120;
  

//    static  char  NAMES[AnomalyClass::ANOMALY_NUM][14];//ниже
    
//    AnomalyInstance  *m_AnomalyCountainer;
//    AnomalyInstance  AnomalyCountainer[7];
    //#warning  NEED  ANOMALY  NUM  FIX
    
    AnomalyClass(void);

    void TimerUpdateEvent (uint8_t msPassed);
    
    void  process(void);                                            //should  run  right  after  EnvironmentProcess()          //вызывается  каждые  40мс(tickTime)  для  обхода  очереди  аномалий
    void  processDamage(void);                                        //TODO:  обработка  урона  от  аномалии
    void  setLevelType_Filter  (uint8_t  level,  AnomalyID_t  AID,  uint8_t  skipLevel,  uint8_t  killLevel);
    void  setLevelType_FilterNone(void);
    void  CleanFilter(void);
    AnomalyName_t  getAnomalyName(AnomalyID_t  AID);
    AnomalyName_t  getLastMeetAnomalyName(void);
    AnomalyID_t  getLastMeetAnomalyID(void);
    //void  setAnomaliesNum(AnomaliesNum  size);                                //ВНИМАНИЕ!!!  Задаётся  нулевая  аномалия
//    void  registerNew(AnomalyName  tmpName,  damageSource  dmgSrc);
    void  RegisterNew(AnomalyID_t  AID,  AnomalyName_t  tmpName,  DamageSource_t  dmgSrc);          //ВНИМАНИЕ!!!  Нулевая  аномалия  уже  определена,  нумерацию  начинать  с  "1"!!!
    DamageSource_t  getDamageSource(AnomalyID_t  AID);
    DamageSource_t  getDamageSource(void);
    AnomaliesNum_t  getAnomaiesNum(void);
    AnomalyInstance*  GetAnomaly(AnomalyID_t  AID);
    //AnomalyInstance*  GetLastAnomaly(AnomalyID_t  AID);
	
    NodeExtended*  GetContainer(void);
    uint8_t  m_strength            =  0;
  protected:
  private:
//    AnomaliesNum  getContainerSize(void);
  
    AnomalyInstance  m_AnomalyContainer;

    uint8_t  m_skipLevel            =  0;
    uint8_t  m_killLevel            =  0;
    uint8_t  m_lastMeetType          =  0;
//    uint8_t  m_strength            =  0;
    //AnomaliesNum  m_Num            =  0;
    uint16_t  m_soundCounter          =  0;
    uint16_t  m_damageSum          =  0;
    uint8_t  m_damageCounter          =  0;
    uint8_t  m_registeredAnomalyCounter    =  0;
    AnomalyID_t  m_AID            =  AnomalyClass::AID_NONE;
  };
#endif
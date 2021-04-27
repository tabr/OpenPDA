// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef  ANOMALY_CLASS_CPP
#define  ANOMALY_CLASS_CPP

/*void  AnomalyClass::AnomalyClassTask1::Task(void)
  {
  Anomaly.process();
  }
uint8_t  AnomalyClass::AnomalyClassTask1::getRepeatTime(void)
  {
  return  TimerClass::TIME_50MS;
  }*/

void  AnomalyClass::TimerUpdateEvent (uint8_t msPassed)
  {
  static  uint16_t  process_msCounter=0;

  process_msCounter+=msPassed;

  if  (process_msCounter  >=  50)
    {
    process_msCounter  -=  50;
    this->process();
    }
  }

AnomalyName_t  AnomalyInstance::GetName(void)
  {
  return  this->Name;
  }
AnomalyInstance*  AnomalyInstance::GetNextNode(void)
  {
  return  static_cast<AnomalyInstance*>(Node::GetNextNode());
  }
DamageSource_t  AnomalyInstance::GetDamageSource(void)
  {
  return  this->Source;
  }
AnomalyInstance::AnomalyInstance(void)
  {
  this->ID    =  0;
  this->Name    =  RAM_STR_UNDEFINED;
  this->Source  =  DamageSource_t::DAMAGE_SOURCE_NONE;
  }
AnomalyInstance::AnomalyInstance(AnomalyInstance*  src)
  {
  this->Source  =  src->Source;
  this->Name    =  src->Name;
  this->ID    =  src->ID;
  }
AnomalyInstance::AnomalyInstance(AnomalyID_t  AID,  AnomalyName_t  aName,  DamageSource_t  dmgSrc)  //ВНИМАНИЕ!!!  Сначала  нужно  задать  размер  массива  контейнера!!!  Вызывать  ЕДИНОЖДЫ!!!
  {
  this->Source  =  dmgSrc;
  /*
  //this->Type    =  type;
  //this->Name    =  (char*)malloc((1  +  strlen(tmpName))  *  sizeof(char));
  this->Name    =  (char*)MemoryManager.allocate((1  +  strlen(tmpName))  *  sizeof(char));
  sprintf(this->Name,  tmpName);
  */
  this->ID  =  AID;
  this->Name  =  LcdStringCopy.CopyFrom(aName);
  }
AnomalyID_t  AnomalyInstance::GetID(void)
  {
  return  this->ID;
  }
/////////////////////////////////////////////
AnomalyClass::AnomalyClass(void)
  {
//  this->m_strength          =  0;
//  this->m_AID              =  0;
//  this->m_soundCounter        =  0;
//  this->m_damageCounter        =  0;
//  this->m_damageSum          =  0;
//  this->m_skipLevel          =  0;
//  this->m_killLevel          =  0;
//  this->m_lastMeetType        =  0;
//  this->m_registeredAnomalyCounter  =  0;
//  this->m_Num            =  0;
  //this->m_AnomalyNone.setProperties((char*)"-",      TemporaryClass::DAMAGE_SOURCE_NONE);
  
  }
void  AnomalyClass::CleanFilter(void)
  {
  this->m_strength  =  0;
  this->m_skipLevel  =  0;
  this->m_killLevel  =  0;
  }
void  AnomalyClass::setLevelType_FilterNone(void)
  {
  this->setLevelType_Filter(0,AnomalyClass::AID_NONE,0,0);
  }
void  AnomalyClass::setLevelType_Filter  (uint8_t  level,  AnomalyID_t  AID,  uint8_t  skipLevel,  uint8_t  killLevel)
  {
  if  (AID  !=  this->m_AID  &&  level  !=  0)//значит,  другая  аномалия,  проверка  на  level    чтобы  если  левел=0  не  сбрасывалось  мгновенно  в  нуль
    {
    this->m_strength  =  0;
    }

  if  (AID  !=  AnomalyClass::AID_NONE)
    {
    this->m_lastMeetType  =  AID;
    }
/*
  sprintf  (lcd_buf,"%03d%03d  %03d%03d",  radio._RXBuffer[0],  radio._RXBuffer[1],  radio._RXBuffer[2],  radio._RXBuffer[3]);
  LcdString(1,LCD_LINE_4);
  sprintf  (lcd_buf,"%03d%03d  %03d%03d",  radio._RXBuffer[4],  radio._RXBuffer[5],  radio._RXBuffer[6],  radio._RXBuffer[7]);
  LcdString(1,LCD_LINE_5);
  sprintf  (lcd_buf,"%03d%03d  %03d%03d",  radio._RXBuffer[8],  radio._RXBuffer[9],  radio._RXBuffer[10],  radio._RXBuffer[11]);
  LcdString(1,LCD_LINE_6);
  LcdUpdate();
//  delay_ms(10);
*/
  this->m_strength    =  (level  +  this->m_strength)  /  2;
//  this->m_strength    =  (this->m_strength>>1);
  this->m_AID        =  AID;
  this->m_skipLevel    =  skipLevel;
  this->m_killLevel    =  killLevel;
  }
void  AnomalyClass::process(void)
  {
  uint8_t  strengthForPlayer  =  0;
  if  (Player.IsDead())
    {
    return;
    }
//  uint8_t  defence  =  0;

  this->m_soundCounter+=this->m_strength;
  if  (this->m_soundCounter  >  this->ANOMALY_SOUND_THRESHOLD)
    {
    this->m_soundCounter-=this->ANOMALY_SOUND_THRESHOLD;
    PDASound.PlaylistAdd(Sound::SID_ANOMALY_BEEP);
    }
  if  (this->m_strength  ==  0  ||  this->m_AID  ==  AID_NONE)//todo  можно  сделать  "^"
    {
    return;
    }

  if  (this->m_skipLevel  >  this->m_strength)
    {
    strengthForPlayer  =  0;
    }
  else
    {
    strengthForPlayer  =  this->m_strength  -  this->m_skipLevel;
    }
  if  (strengthForPlayer  >=  this->m_killLevel)
    {
    Player.Kill(this->getDamageSource());
    return;
    }
  this->m_damageSum  +=  strengthForPlayer;
  /*
  defence  =  Player.getDefenceFrom(this->getDamageSource(this->m_AID));
  defence  +=  this->m_skipLevel;
  
  if  (defence  >=  this->m_strength)
    return;

  strengthForPlayer  =  this->m_strength  -  defence;
  if  (strengthForPlayer  >=  this->m_killLevel)
    {
    Player.Kill(PlayerClass::AGRESSOR_TYPE_ANOMALY);
    }
  this->m_damageSum    +=  strengthForPlayer;
  */
  
  if  (this->m_damageSum  >  TemporaryClass::ANOMALY_DAMAGE_THRESHOLD)//TODO
    {
    this->m_damageSum  -=  TemporaryClass::ANOMALY_DAMAGE_THRESHOLD;
//    Player.dealDamage(1,  Anomaly.getDamageSource(this->m_AID),  PlayerClass::AGRESSOR_TYPE_ANOMALY,  this->m_AID,  DamageClass::AGGRESSOR_SOURCE_EXTERNAL);//AGGRESSOR_SUBTYPE_EXTERNAL??!
    Player.DealDamage({value: TemporaryClass::ANOMALY_DAMAGE_MULTIPLIER,  damageSource:this->getDamageSource(),  aggressorSource:DamageClass::AGGRESSOR_SOURCE_EXTERNAL});//AGGRESSOR_SUBTYPE_EXTERNAL??!
    }
  }
void  AnomalyClass::processDamage(void)
  {
  //TODOs
  }
AnomalyName_t  AnomalyClass::getAnomalyName(AnomalyID_t  AID)
  {
  //return  this->m_AnomalyCountainer[AID].getName();
  //return  this->NAMES[id];
  return  this->GetAnomaly(AID)->GetName();
  }
AnomalyName_t  AnomalyClass::getLastMeetAnomalyName(void)
  {
  return  this->getAnomalyName(this->m_lastMeetType);
  }
/*
void  AnomalyClass::setAnomaliesNum(AnomaliesNum  size)
  {
  this->m_Num          =  size;
  //this->m_AnomalyCountainer    =  (AnomalyInstance*)malloc  (this->getContainerSize()  *  sizeof(AnomalyInstance));          //+1  -  нулевая  аномалия!!!
  this->m_AnomalyCountainer    =  (AnomalyInstance*)MemoryManager.allocate  (this->getContainerSize()  *  sizeof(AnomalyInstance));          //+1  -  нулевая  аномалия!!!
//  this->AnomalyCountainer[this->AID_NONE].setProperties((char*)"-",      DamageClass::DAMAGE_SOURCE_NONE);  //Именно  тут,  т.к.  дожен  быть  определён  массив  классов!!!
  this->m_AnomalyCountainer[this->AID_NONE].setProperties(this->m_AnomalyNone);
  }
*/
AnomalyInstance*  AnomalyClass::GetAnomaly(AnomalyID_t  AID)
  {
  return  static_cast<AnomalyInstance*>(this->GetNode(AID));
  }
void  AnomalyClass::RegisterNew(AnomalyID_t  AID,  AnomalyName_t  aName,  DamageSource_t  dmgSrc)
  {
  /*
  if  (AID  >  this->getAnomaiesNum())  //ШОП  не  выходить  за  пределы
    {
    AID  =  this->getAnomaiesNum();
    }
//  if  (AID  ==  this->AID_NONE)    //не  стоит  переопределять  нулевую  аномалию
//    return;
//  this->AnomalyCountainer[this->registeredAnomalyCounter].setProperties(tmpName,dmgSrc);
  this->m_AnomalyCountainer[AID].setProperties(tmpName,dmgSrc);
  */
  this->m_AnomalyContainer.AddNode(new  AnomalyInstance  (AID,  aName,  dmgSrc));
  this->m_registeredAnomalyCounter++;
  }

DamageSource_t  AnomalyClass::getDamageSource(AnomalyID_t  AID)
  {
  //return  this->m_AnomalyCountainer[AID].getDamageSource();
  return  this->GetAnomaly(AID)->GetDamageSource();
  }
DamageSource_t  AnomalyClass::getDamageSource(void)
  {
  return  this->getDamageSource(this->m_AID);
  }
AnomaliesNum_t  AnomalyClass::getAnomaiesNum(void)
  {
  return  this->m_registeredAnomalyCounter;
  }
/*
AnomaliesNum  AnomalyClass::getContainerSize(void)
  {
  return  this->getAnomaiesNum()  +  1;
  }
*/
NodeExtended*  AnomalyClass::GetContainer(void)
  {
  return  &this->m_AnomalyContainer;
  }
#endif
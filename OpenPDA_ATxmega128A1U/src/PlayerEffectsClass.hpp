/*
  *  PlayerEffectsClass.h
  *
  *  Created:  20.05.2017  23:56:21
  *    Author:  tabr
  */  


#ifndef  PLAYEREFFECTSCLASS_H_
#define  PLAYEREFFECTSCLASS_H_

#include  "typedefs.h"
#include  "PlayerEffectsInterface.hpp"


class  PlayerEffect_NullEffectClass : public PlayerEffectsStoragableClass
  {
  public:
    void  OnTick(void);
    void  OnApply(void);
    void  OnRemove(void);
    EffectID_t  GetID(void);
    //PlayerEffect_NullEffectClass() : PlayerEffectsInterface(0,  0,  0){};
  protected:
  private:
  };

class  PlayerEffectsClass : public ITimerListener//, public NodeExtended
  {
  public:
    enum  EFFECTIDS
      {
      EFFECTID_NONE,
      EFFECTID_MOD_HEALTH,
      EFFECTID_MOD_RAD_DOSE,
      EFFECTID_DEAL_DAMAGE,
      EFFECTID_HEAL,
      EFFECTID_DEF_DAMAGE_SOURCE,
      EFFECTID_COMBINED,
      EFFECTID_NO_ACTION,
      EFFECTID_SAFE_SHELTER,
      EFFECTID_FOOD,
      EFFECTID_DEATH_TIMER,
      };
    struct  PEParametersStruct
      {
      TimeSecond_t  repeatPeriodCounter;
      PE_RepeatTimes_t  repeatTimesCounter;
      PlayerEffects_Interface* Effect;
      };
    
    const static uint8_t  STORAGE_SIZE  =  32;
    
    EffectsStorageID_t  GetActiveEffects(EFFECTIDS  EID,  PlayerEffects_Interface*  result[]);
    EffectsStorageID_t  GetActiveVisibleEffects(EFFECTIDS  EID,  PlayerEffects_Interface*  result[]);

    //PlayerEffectsDefenceValue_t  GetDefenceFrom(DamageSource_t  dmgSrc);
    PlayerEffectsDefenceValue_t  GetDefenceFrom(DamageClass  Damage);
    void TimerUpdateEvent (uint8_t msPassed);
    void  OneSecTick(void);
    //PlayerEffects_Interface* GetEffect(PlayerEffectGUID_t EGUID);
    EffectsStorageID_t IsEffectActive(PlayerEffects_Interface*  Effect);
    //EffectsStorageID_t IsEffectActive(PlayerEffectGUID_t EGUID);
    void  PlayerDie(void);
    void  RemoveEffect(EffectsStorageID_t  SID);
    uint16_t GetRemainTimeSec(PlayerEffects_Interface*  Effect);
    EffectsStorageID_t RenewEffectInstance(PlayerEffects_Interface*  Effect);//apply  new  or  reload  counters
//    EffectsStorageID_t RenewEffectInstance(PlayerEffectGUID_t EGUID);        //apply  new  or  reload  counters
    EffectsStorageID_t ApplyEffectInstance(PlayerEffects_Interface*  Effect);
//    EffectsStorageID_t ApplyEffectInstance(PlayerEffectGUID_t EGUID);
    PlayerEffects_Interface*  FromStorageID(  EffectsStorageID_t  SID  );
    bool  IsSIDValid(  EffectsStorageID_t  SID  );
    PlayerEffectsClass(void);

    //variables
    PlayerEffect_NullEffectClass  PlayerEffect_NullEffect;
  protected:
  private:
    void  CleanEffect(EffectsStorageID_t  SID);
    void  CleanAllEffects(void);
    bool  IsSIDEmpty(EffectsStorageID_t  SID);
    bool  IsSIDNotEmpty(EffectsStorageID_t  SID);
    EffectsStorageID_t  GetFreeStorageID(void);
    //PlayerEffects_Interface*  storage[STORAGE_SIZE];

    //variables
    PEParametersStruct  parameters[STORAGE_SIZE];
  };


class  PlayerEffect_DealDamageClass : public PlayerEffectsStoragableClass
  {
  public:
    void  OnTick(void);
    void  OnApply(void);
    void  OnRemove(void);
    EffectID_t  GetID(void);
    PlayerEffect_DealDamageClass(PE_CFG_t  CFG,TimeSecond_t  repeatPeriodSec,  PE_RepeatTimes_t  repeatTimes, PlayerEffectGUID_t EGUID, EffectName_t tmpName) : PlayerEffectsStoragableClass(CFG,  repeatPeriodSec,  repeatTimes, EGUID, tmpName){};
    PlayerEffect_DealDamageClass() : PlayerEffectsStoragableClass(){};

    void  SetDamage(DamageClass*  dmg);
  protected:
  private:
    DamageClass*  m_dmg = nullptr;
  };

class  PlayerEffect_ModRadDoseClass : public PlayerEffectsStoragableClass
  {
  public:
    void  OnTick(void);
    void  OnApply(void);
    void  OnRemove(void);
    EffectID_t  GetID(void);
    PlayerEffect_ModRadDoseClass(PE_CFG_t  CFG,TimeSecond_t  repeatPeriodSec,  PE_RepeatTimes_t  repeatTimes, PlayerEffectGUID_t EGUID, EffectName_t tmpName) : PlayerEffectsStoragableClass(CFG,  repeatPeriodSec,  repeatTimes, EGUID, tmpName){};
    PlayerEffect_ModRadDoseClass() : PlayerEffectsStoragableClass(){};

    void  SetDoseValue(int8_t  value);
  protected:
  private:

    int8_t  m_value = 0;
  };

class  PlayerEffect_ModHealthClass : public PlayerEffectsStoragableClass
  {
  public:
    void  OnTick(void);
    void  OnApply(void);
    void  OnRemove(void);
    EffectID_t  GetID(void);
    PlayerEffect_ModHealthClass(PE_CFG_t  CFG,TimeSecond_t  repeatPeriodSec,  PE_RepeatTimes_t  repeatTimes, PlayerEffectGUID_t EGUID, EffectName_t tmpName) : PlayerEffectsStoragableClass(CFG,  repeatPeriodSec,  repeatTimes, EGUID, tmpName){};
    PlayerEffect_ModHealthClass() : PlayerEffectsStoragableClass(){};

    void  SetModHealthValue(int8_t  value);
  protected:
  private:
    int8_t  m_value = 0;
  };


class  PlayerEffect_HealClass : public PlayerEffectsStoragableClass
  {
  public:
    void  OnTick(void);
    void  OnApply(void);
    void  OnRemove(void);
    EffectID_t  GetID(void);
    PlayerEffect_HealClass(PE_CFG_t  CFG,TimeSecond_t  repeatPeriodSec,  PE_RepeatTimes_t  repeatTimes, PlayerEffectGUID_t EGUID, EffectName_t tmpName) : PlayerEffectsStoragableClass(CFG,  repeatPeriodSec,  repeatTimes, EGUID, tmpName){};
    PlayerEffect_HealClass() : PlayerEffectsStoragableClass(){};

    void  SetHealValue(uint8_t  value);
  protected:
  private:

    uint8_t  m_value = 0;
  };

class  PlayerEffect_DefDamageSourceClass : public PlayerEffectsStoragableClass
  {
  public:
    void OnTick(void);
    void OnApply(void);
    void OnRemove(void);
    EffectID_t  GetID(void);
    PlayerEffect_DefDamageSourceClass(PE_CFG_t  CFG,TimeSecond_t  repeatPeriodSec,  PE_RepeatTimes_t  repeatTimes, PlayerEffectGUID_t EGUID, EffectName_t tmpName) : PlayerEffectsStoragableClass(CFG,  repeatPeriodSec,  repeatTimes, EGUID, tmpName){};
    PlayerEffect_DefDamageSourceClass() : PlayerEffectsStoragableClass(){};

    void SetDmgSrc(DamageSource_t  dmgSrc,  PlayerEffectsDefenceValue_t  value);
    DamageSource_t GetDmgSrc(void);
    PlayerEffectsDefenceValue_t GetValue(void);
    void SetValue(PlayerEffectsDefenceValue_t val);
  protected:
  private:

    uint8_t  m_value = 0;
    DamageSource_t  m_dmgSrc = DamageSource_t::DAMAGE_SOURCE_NONE;
  };

class  PlayerEffect_CombinedClass : public PlayerEffectsStoragableClass
  {
  public:
    void  OnTick(void);
    void  OnApply(void);
    void  OnRemove(void);
    EffectID_t  GetID(void);
    PlayerEffect_CombinedClass(PE_CFG_t  CFG,TimeSecond_t  repeatPeriodSec,  PE_RepeatTimes_t  repeatTimes, PlayerEffectGUID_t EGUID, EffectName_t tmpName) : PlayerEffectsStoragableClass(CFG,  repeatPeriodSec,  repeatTimes, EGUID, tmpName){};
    PlayerEffect_CombinedClass() : PlayerEffectsStoragableClass(){};

    void  SetCombined(PlayerEffects_Interface**  array,  uint8_t  num);
  protected:
  private:

    uint8_t  m_num = 0;
    PlayerEffects_Interface**  m_array = nullptr;
    uint8_t*  SID_Array = nullptr;
  };

class  PlayerEffect_NoActionClass : public PlayerEffectsStoragableClass
  {
  public:
    void  OnTick(void)
      {
      
      }
    void  OnApply(void)
      {
      
      }
    void  OnRemove(void)
      {
      
      }
    EffectID_t  GetID(void);
    PlayerEffect_NoActionClass(PE_CFG_t  CFG,TimeSecond_t  repeatPeriodSec,  PE_RepeatTimes_t  repeatTimes, PlayerEffectGUID_t EGUID, EffectName_t tmpName) : PlayerEffectsStoragableClass(CFG,  repeatPeriodSec,  repeatTimes, EGUID, tmpName){};
    PlayerEffect_NoActionClass() : PlayerEffectsStoragableClass(){};

    void  SetProperty(uint8_t  property);
    uint8_t  GetProperty(void);
  protected:
  private:
    uint8_t  m_property = 0;
  };
class  PlayerEffect_SafeShelterClass : public PlayerEffectsStoragableClass
  {
  public:
    void  OnTick(void);
    void  OnApply(void);
    void  OnRemove(void);
    EffectID_t  GetID(void);
    PlayerEffect_SafeShelterClass(PE_CFG_t  CFG,TimeSecond_t  repeatPeriodSec,  PE_RepeatTimes_t  repeatTimes, PlayerEffectGUID_t EGUID, EffectName_t tmpName) : PlayerEffectsStoragableClass(CFG,  repeatPeriodSec,  repeatTimes, EGUID, tmpName){};
    PlayerEffect_SafeShelterClass() : PlayerEffectsStoragableClass(){};

  protected:
  private:
  };

class  PlayerEffect_FoodClass : public PlayerEffectsStoragableClass
  {
  public:
    void  OnTick(void);
    void  OnApply(void);
    void  OnRemove(void);
    EffectID_t  GetID(void);
    PlayerEffect_FoodClass(PE_CFG_t  CFG,TimeSecond_t  repeatPeriodSec,  PE_RepeatTimes_t  repeatTimes, PlayerEffectGUID_t EGUID, EffectName_t tmpName) : PlayerEffectsStoragableClass(CFG,  repeatPeriodSec,  repeatTimes, EGUID, tmpName){};
    PlayerEffect_FoodClass() : PlayerEffectsStoragableClass(){};

  protected:
  private:
  };

class  PlayerEffect_DeathTimerClass : public PlayerEffectsStoragableClass
  {
  public:
    void  OnTick(void);
    void  OnApply(void);
    void  OnRemove(void);
    EffectID_t  GetID(void);
    PlayerEffect_DeathTimerClass(PE_CFG_t  CFG,TimeSecond_t  repeatPeriodSec,  PE_RepeatTimes_t  repeatTimes, PlayerEffectGUID_t EGUID, EffectName_t tmpName) : PlayerEffectsStoragableClass(CFG,  repeatPeriodSec,  repeatTimes, EGUID, tmpName){this->m_kill_DamageSource  =  DamageSource_t::DAMAGE_SOURCE_GENERIC;};
    PlayerEffect_DeathTimerClass() : PlayerEffectsStoragableClass(){this->m_kill_DamageSource  =  DamageSource_t::DAMAGE_SOURCE_GENERIC;};
    void  SetDmgSrc(DamageSource_t  dmgSrc);

  protected:
  private:
    DamageSource_t  m_kill_DamageSource;
  };

#endif  /*  PLAYEREFFECTSCLASS_H_  */

#ifndef  PLAYER_H
#define  PLAYER_H

#include  <stdint.h>
#include  <stddef.h>
#include  <avr/io.h>

#include  <avr/eeprom.h>
#include  "boards/compiler_defines.h"
#include  "typedefs.h"
#include  "DamageClass.hpp"
#include  "ActionsClass.hpp"
#include  "GameConfig.hpp"
#include  "PlayerSkillsClass.hpp"
#include  "EEPROM_StructPlayer.hpp"
#include  "stalker/TimerClass.hpp"
#include  "stalker/Environment.hpp"
#include  "n3310_new.h"
#include  <stalker/LcdClass.hpp>
#include  "images.h"
#include  "TODOmacro.h"
#include  "VibroClass.hpp"
#include  "stalker.hpp"
#include  "RandomPseudo.hpp"
#include  "QuestClass.hpp"
#include  "PlayerSuitClass.hpp"
//#include  "PlayerEffectsOld.hpp"
#include  "playerStatistics.hpp"
#include  "PlayerSkillsClass.hpp"
#include  "EEPROM_DataClass.hpp"
#include  "DamageClass.hpp"
#include  "pdamenu.hpp"
#include  "strings.h"
#include  "ArtefactPorts.hpp"
#include  <PlayerInterface.hpp>
#include "EventSystemClass.hpp"
/*

extern  Environment  Env;
extern  GameConfig  GameCFG;
extern  LcdClass  Lcd;
extern  VibroClass  Vibro;
extern  RandomPseudoClass  RandomPseudo;
extern  QuestClass  Quest;
//extern  PlayerEffectsClass  PlayerEffects;
//extern  PlayerSuitClass  PlayerSuit;
//extern  PlayerStatisticsClass  PlayerStatistics;
extern  PlayerSkillsClass  PlayerSkills;
extern  DamageClass  PlayerDamage;
extern  PDAMenuClass  PDAMenu;
extern  EEPROM_DataClass  EEPROM_Data;
*/
/*
enum  PLAYER_ENVIRONMENT_ACTIONS
  {
  PLAYER_ENVIRONMENT_ACTION_NONE,
  PLAYER_ENVIRONMENT_ACTION_SUITE_SET_MAX_DURABILITY,
  PLAYER_ENVIRONMENT_ACTION_APPLY_EFFECT,
  PLAYER_ENVIRONMENT_ACTION_PLAYER_SET_MAX_HP,
  PLAYER_ENVIRONMENT_ACTION_PLAYER_RAD_DOSE_INCREASE,
  PLAYER_ENVIRONMENT_ACTION_PLAYER_RAD_DOSE_DECREASE,
  PLAYER_ENVIRONMENT_ACTION_PLAYER_HEALTH_INCREASE,
  PLAYER_ENVIRONMENT_ACTION_PLAYER_HEALTH_DECREASE,
  PLAYER_ENVIRONMENT_ACTION_ADD_DEFENCE_PARAMETER,
  PLAYER_ENVIRONMENT_ACTION_DELETE_DEFENCE_PARAMETER,
  };
*/
//TODO("HACK")
//class PlayerEffect_ModHealthClass;
class  PlayerClass : public ITimerListener,  public  PlayerInterface, public EventArrivedInterface
  {
  public:
    const  static  PlayerStatus_t  PLAYER_STATUS_ALIVE      =  1<<0;
    const  static  PlayerStatus_t  PLAYER_STATUS_ZOMBIE      =  1<<1;

    
    enum  LOSE_DURABILITY
      {
      LOSE_DURABILITY_NO,
      LOSE_DURABILITY_YES,
      };
    
    void EventArrived(EventSystemSpace::EVIDS evID, void* parameters);

    PlayerClass(void);
    void  TimerUpdateEvent  (TimeUpdate_t  msPassed);
    
    bool  IsInSafeZone(void);
    void  SetInSafeZone(bool  value);

//    PlayerDefenceValue_t  GetSelfDefenceFrom(DamageSource_t  dmgSrc);
    PlayerDefenceValue_t  GetSelfDefenceFrom(DamageClass  damage);
    /*PlayerDefenceValue_t  GetComplexDefenceFrom(DamageSource_t  dmgSrc);
    PlayerDefenceValue_t  GetComplexDefenceFrom(DamageSourceClass  dmgSrcC);
    PlayerDefenceValue_t  GetComplexDefenceFrom(DamageClass*  damage);*/
    PlayerDefenceValue_t  GetComplexDefenceFrom(DamageClass  damage);

    PlayerRegenTime_t  GetRegenTime(void);
    PlayerHealth_t  GetCurrentHealth(void);
    PlayerHealth_t  GetMaxHealth(void);                              //максимум,  персональный  для  игрока  (может  изменяться  в  процессе  игры)
    Percent_t  GetHealthPercent(void);                            //ХП  в  процентах,  независимо  от  максимальных

    RadiationDose_t  GetRadiationDose(void);
    RadiationDose_t  GetMaxRadiationDose(void);
    Percent_t  GetRadiationDosePercent(void);
    bool  IsRadiationDoseMaximimReached(void);
    bool  IsSick(void);
    void  DoSelfRegen(void);

    void  SetRadiationDose(RadiationDose_t  value);
    void  Revive(void);                                  //воскресить  игрока  -  должно  обрабатьываться  ВСЁ  для  нормального  воскрешения
    void  Kill(DamageSource_t  damageSrc);
    void  Save(void);                                  //сохранить  в  (еепром)
    void  Load(void);                                  //загрузить  из  (еепром)
    void  PlayDeathSound(void);
//    void  DealDamage(DamageClass  *damage,  bool  noclean=false);                        //в  случае  смерти,  вызоветься  метод  Die()
//    void  DealDamage(DamageClass  damage,  bool  noclean=false);                        //в  случае  смерти,  вызоветься  метод  Die()
    void  DealDamage(DamageClass  damage);                        //в  случае  смерти,  вызоветься  метод  Die()
//    void  DealDamage(DamageValue_t  value,  DamageSource_t  damageSrc,  DamageClass::AGGRESSOR_SOURCE  aggressorSrc);    //в  случае  смерти,  вызоветься  метод  Die()
    void  PlayDelayedHitSound(void);
    void  HealthIncrase(PlayerHealth_t  value);
    void  RadDoseDecrase(RadiationDose_t  value);
    void  RadDoseIncrase(RadiationDose_t  value);
//    void  RadDoseMod(int8_t value);
    void  RadDoseToHealthProcess(void);                          //вызывается  извне
    void  PsyToHealthProcess(void);
    void  processSuicideCounter(void);
    void  oneSecondPassed(void);                              //вызывается  извне.  Используется,  напрмер,  для  сохранения  игрока
    void  EEPROM_init(void);

    bool  IsDead(void);
    bool  IsAlive(void);
    bool  IsZombie(void);
    bool  IsDamaged(void);
    bool  IsAwaitingGraveyard(void);
    void  RenewDeathTimer(void);
    void  SetZombie(bool  status);
    PlayerName_t  GetName(void);
    FactionID_t  GetFactionID(void);
//    const  char*  PROGMEM  getFactionName(void);
    FactionName_t  GetFactionName(void);
    void  SetFactionID(FactionID_t  FID);
    PlayerID_t  GetID(void);
    
    PlayerDeathTimer_t  GetDeathTimeRemain(void);
    bool  SetDeathTimeRemain(PlayerDeathTimer_t  time);
    PlayerDeathTimer_t  GetZombieTimeRemain(void);
    
    PlayerSkillsClass*  GetSkills(void);
    //PlayerEffectsOldClass*  GetEffects1(void);
    PlayerStatisticsClass*  GetStatistics(void);
    PlayerSuitClass*  GetSuit(void);
    ArtefactPortsClass*  GetArtefactPorts(void);
    



    SuicideTimer_t  GetSuicideTimer(void);
    bool  StartSuicideCounter(void);
    bool  StopSuicideCounter(void);
    
    DamageSource_t  lastDamagerSource    =  TemporaryClass::DamageSource::DAMAGE_SOURCE_NONE;
  protected:
  private:
  friend PlayerEffect_ModHealthClass;

    void  SetHealth(PlayerHealth_t  value);
    void  HealthDecrase(PlayerHealth_t  value);
    void  Die(void);
    void  SetStatusAlive(void);
    void  SetStatusDead(void);

    bool  m_isInsideSafeZone          =  false;
    bool  playDelayedHitSound        =  false;
    uint16_t  playerSaveTimer        =  0;
    SuicideTimer_t  m_selfSuicideCounter    =  0;
    uint8_t  selfRegenTimer          =  0;

    uint8_t  radDoseToHealthCollector    =  0;
    PlayerStatus_t  playerStatus        =  0;
    
    PlayerDeathTimer_t  deathTimer;
    PlayerDeathTimer_t  zombieTimer;

    //PlayerEffectsOldClass  m_Effects1;
    PlayerSuitClass  m_Suit;
    ArtefactPortsClass  m_ArtefactPorts;
    PlayerStatisticsClass  m_Statistics;
    PlayerSkillsClass  m_Skills;

    const  static  PlayerDeathTimer_t  DEATH_TIMER_MAX  =  0xFFFF;
  };

#endif
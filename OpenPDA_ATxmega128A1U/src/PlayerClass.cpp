// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//CP1251!!!

#include "PlayerClass.hpp"

/*void PlayerClass::PlayerClassTask1::Task(void)
  {
  //Player.oneSecondPassed(); //TODO: хак же!
  ((PlayerClass*)this->GetLinkedObject())->oneSecondPassed();
  }*/
/*
uint8_t * PlayerClass::EEPROM_TRANSLATION[MYEEPROM_SIZE]  = 
  {
  &PlayerSpecs.defenceRadiationSelf,
  &PlayerSpecs.resistantRadiationSelf,
  &PlayerSpecs.defenceGravySelf,
  &PlayerSpecs.defenceFireSelf,
  &PlayerSpecs.defenceChemicalSelf,
  &PlayerSpecs.defenceElectroSelf,
  &PlayerSpecs.defencePsySelf,

  &PlayerSpecs.maxHealth,
  &PlayerSpecs.currentHealth,
  &PlayerSpecs.defenceBio,
  &PlayerSpecs.radiationDose,
  &PlayerSpecs.regenTime,
  &Player.playerStatus,
  &Player.lastAgressorType,
  };
*/
void PlayerClass::EventArrived(EventSystemSpace::EVIDS evID, void* parameters)
  {
  this->GetSuit()->damageTaken((DamageClass*)parameters);
  }
void PlayerClass::TimerUpdateEvent (TimeUpdate_t msPassed)
  {
  static uint16_t oneSecondPassed_msCounter=0;
  #ifdef DEBUG_USART_FUNCTION_CALL
    sprintf (USARTBuffer,"[PlayerClass::TimerUpdateEvent(%03u)]", msPassed);
    sendString(USARTBuffer);
  #endif

  oneSecondPassed_msCounter+=msPassed;

  if (oneSecondPassed_msCounter >= 1000)
    {
    oneSecondPassed_msCounter -= 1000;
    this->oneSecondPassed();
    //EEPROM_Data.setParameter(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_VARS, EEPROM_DataClass::PLAYER_VARS::PLAYER_VAR_CURRENT_HP, rand()%100);
    //this->dealDamage(1,TemporaryClass::DAMAGE_SOURCE_GENERIC, AGRESSOR_TYPE_GENERIC, 0, DamageClass::AGGRESSOR_SOURCE_EXTERNAL);
    /*LcdClearCache();
    sprintf (Lcd.lcd_buf,"%05d=%05d", &EEPROM_Data.data[EEPROM_STRUCT_PLAYER_REGEN_TIME], (EEPROM_Data.getDefenceParametersAddr(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_VARS) + EEPROM_DataClass::PLAYER_VARS::PLAYER_VAR_REGEN_TIME));
    LcdString(1,LCD_LINE_1);
    LcdUpdate();
    while(1);*/
    //return EEPROM_Data.data[EEPROM_STRUCT_PLAYER_REGEN_TIME];
    //return *(EEPROM_Data.getDefenceParametersAddr(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_VARS) + EEPROM_DataClass::PLAYER_VARS::PLAYER_VAR_REGEN_TIME);
    }
  }
PlayerClass::PlayerClass(void)
  {
  this->deathTimer  = 0;
  this->zombieTimer  = 0;
  //EventSystem.RegisterUserEvent(EventSystemSpace::EVID_DAMAGE_TAKEN, this);
  
  //EEPROM_Data.load();
  
//  this->TaskOneSecondPassed.SetLinkedObject(this);
  
  /*EEPROM_Data.playerDefenceRadiationSelf    = 0;
  EEPROM_Data.playerResistantRadiationSelf  = 0;
  EEPROM_Data.playerDefenceGravySelf      = 0;
  EEPROM_Data.playerDefenceElectroSelf    = 0;
  EEPROM_Data.playerDefenceFireSelf      = 0;
  EEPROM_Data.playerDefenceChemicalSelf    = 0;
  EEPROM_Data.playerDefencePsySelf      = 0;*/
  /*
  
  //PlayerSpecs.defenceBio          = 0;
  //PlayerSpecs.radiationDose        = 0;
//  PlayerSpecs.currentHealth        = GameCFG.getStartPlayerHealth();
//  PlayerSpecs.regenTime          = GameCFG.getDefaultRegenValue();
//  PlayerSpecs.maxHealth          = GameCFG.MAXIMUM_PLAYER_HEALTH;
  this->radDoseToHealthCollector      = 0;
  this->playerStatus            = 0;
//  this->Inventory.selectedItem      = this->Inventory.ITEMID_FIRST_ITEM;
  playerRegenTimer            = GameCFG.getDefaultRegenValue();
//  this->healthIncrementCouter        = 0;
//  this->radiationDoseDecrementCouter    = 0;
  this->playerSaveTimer          = this->SAVE_TIMER;
  */
  }
/*
PlayerDefenceValue_t PlayerClass::GetSelfDefenceFrom(DamageClass damage)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::getSelfDefenceFrom(DamageClass* damage)]");
  #endif
  return this->GetSelfDefenceFrom(damage.GetSource()->Get());
  }
PlayerDefenceValue_t PlayerClass::GetSelfDefenceFrom(DamageSource_t dmgSrc)
*/
PlayerDefenceValue_t PlayerClass::GetSelfDefenceFrom(DamageClass damage)
  {
  DamageSource_t dmgSrc = damage.GetSource()->Get();
  #ifdef DEBUG_USART_FUNCTION_CALL
    sprintf (USARTBuffer,"[PlayerClass::getSelfDefenceFrom(%03u)]", dmgSrc);
    sendString(USARTBuffer);
  #endif
  //return 0;
  return *(EEPROM_Data.getParameterAddr(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_DEFENCE_SELF, dmgSrc));
  /*
  switch (dmgSrc)
    {
    case TemporaryClass::DAMAGE_SOURCE_GENERIC:
      {
      
      }
    break;
    
    case TemporaryClass::DAMAGE_SOURCE_RADIATION_EXTERNAL:
      {
      //return EEPROM_Data.data[EEPROM_STRUCT_PLAYER_DEFENCE_RADIATION_EXT_SELF];
      //return *(EEPROM_Data.getDefenceParametersAddr(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_DEFENCE_SELF) + sizeof(DamageSource_t)*dmgSrc - 2);
      //resultDefence  += PlayerSuit.getDefenceRadiation();
      //resultDefence  += Player.getEffects()->getDefenceRadiation();
      }
    break;
    
    case TemporaryClass::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL:
      {
      //return  Player.getResistanceRadiation();
      return EEPROM_Data.data[EEPROM_STRUCT_PLAYER_DEFENCE_RADIATION_INT_SELF];
      }
    break;

    case TemporaryClass::DAMAGE_SOURCE_FIRE:
      {
      return EEPROM_Data.data[EEPROM_STRUCT_PLAYER_DEFENCE_FIRE_SELF];
      //resultDefence  += PlayerSuit.getDefenceFire();
      //resultDefence  += Player.getEffects()->getDefenceFire();
      }
    break;
    
    case TemporaryClass::DAMAGE_SOURCE_ELECTRICITY:
      {
      return EEPROM_Data.data[EEPROM_STRUCT_PLAYER_DEFENCE_ELECTRO_SELF];
      //resultDefence  += PlayerSuit.getDefenceElectro();
      //resultDefence  += Player.getEffects()->getDefenceElectro();
      }
    break;

    case TemporaryClass::DAMAGE_SOURCE_CHEMICAL:
      {
      return EEPROM_Data.data[EEPROM_STRUCT_PLAYER_DEFENCE_CHEMICAL_SELF];
      //resultDefence  += PlayerSuit.getDefenceChemical();
      //resultDefence  += Player.getEffects()->getDefenceChemical();
      }
    break;

    case TemporaryClass::DAMAGE_SOURCE_GRAVY:
      {
      return EEPROM_Data.data[EEPROM_STRUCT_PLAYER_DEFENCE_GRAVY_SELF];
      //resultDefence  += PlayerSuit.getDefenceGravy();
      //resultDefence  += Player.getEffects()->getDefenceGravy();
      }
    break;

    case TemporaryClass::DAMAGE_SOURCE_PSY:
      {
      return EEPROM_Data.data[EEPROM_STRUCT_PLAYER_DEFENCE_PSY_SELF];
      //resultDefence  += PlayerSuit.getDefencePsy();
      //resultDefence  += Player.getEffects()->getDefencePsy();
      //if (resultDefence > Environment::MAX_LEVEL_PSY)
      //  resultDefence  = Environment::MAX_LEVEL_PSY;
      }
    break;

    case TemporaryClass::DAMAGE_SOURCE_BIO:
      {
      return EEPROM_Data.data[EEPROM_STRUCT_PLAYER_DEFENCE_BIO_SELF];
      }
    break;
    
    default:
    break;
    }
  return 0;
  */
  }
PlayerDefenceValue_t PlayerClass::GetComplexDefenceFrom(DamageClass damage)
//PlayerDefenceValue_t PlayerClass::GetComplexDefenceFrom(DamageSource_t dmgSrc)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sprintf (USARTBuffer,"[PlayerClass::GetComplexDefenceFrom(DamageSource_t dmgSrc): %03u]\r\n", damage.GetSource()->Get());
    sendString(USARTBuffer);
  #endif
  PlayerDefenceValue_t resultDefence  = 0;
//  DamageSource_t dmgSrc        = dmgSrcC.Get();
  resultDefence  += this->GetSelfDefenceFrom(damage);
  #ifdef DEBUG_USART_DEFENCE
    sprintf (USARTBuffer,"resultDefence1: %03d\r\n",resultDefence);
    sendString(USARTBuffer);
  #endif // DEBUG_USART_DEFENCE
  resultDefence  += this->GetSuit()->GetDefenceFrom(damage);
  #ifdef DEBUG_USART_DEFENCE
    sprintf (USARTBuffer,"resultDefence2: %03d\r\n",resultDefence);
    sendString(USARTBuffer);
  #endif // DEBUG_USART_DEFENCE
//  resultDefence  += this->GetEffects()->getDefenceFrom(dmgSrc.Get());
  resultDefence  += PlayerEffects.GetDefenceFrom(damage);
  #ifdef DEBUG_USART_DEFENCE
    sprintf (USARTBuffer,"resultDefence3: %03d\r\n",resultDefence);
    sendString(USARTBuffer);
  #endif // DEBUG_USART_DEFENCE
  return resultDefence;
  }
/*
PlayerDefenceValue_t PlayerClass::GetComplexDefenceFrom(DamageClass* damage)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sprintf (USARTBuffer,"[PlayerClass::GetComplexDefenceFrom(DamageClass* damage): %03u]\r\n", damage->GetSource()->Get());
    sendString(USARTBuffer);
  #endif
  return this->GetComplexDefenceFrom(damage->GetSource()->Get());
  }
PlayerDefenceValue_t PlayerClass::GetComplexDefenceFrom(DamageSourceClass dmgSrc)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sprintf (USARTBuffer,"[PlayerClass::GetComplexDefenceFrom(DamageSourceClass dmgSrc): %03u]\r\n", dmgSrc.Get());
    sendString(USARTBuffer);
  #endif
  return this->GetComplexDefenceFrom(dmgSrc.Get());
  }
*/
/*
uint8_t PlayerClass::getDefencePsy(void)
  {
  uint8_t resultDefence=0;
    
  resultDefence  += PlayerSpecs.defencePsySelf;
    
  resultDefence  += PlayerSuit.getDefencePsy();
  
  resultDefence  += Player.getEffects()->getDefencePsy();

//  if (Player.getEffects()->isEffectActive(PlayerEffectsClass::EFFECTID_ARTEFACT_LUN_SVET))
//    resultDefence  += 3;

//  if (Player.getEffects()->isEffectActive(PlayerEffectsClass::EFFECTID_ARTEFACT_KAM_CVETOK))
//    resultDefence  += 10;

//  if (Player.getEffects()->isEffectActive(PlayerEffectsClass::EFFECTID_ITEM_PSY_BLOKADA))
//    resultDefence  += 10;

  if (resultDefence > Environment::MAX_LEVEL_PSY)
    return Environment::MAX_LEVEL_PSY;

  return resultDefence;
  }
uint8_t PlayerClass::getDefenceFire(void)
  {
  uint8_t resultDefence=0;
    
  resultDefence  += PlayerSpecs.defenceFireSelf;
    
  resultDefence  += PlayerSuit.getDefenceFire();
  
  resultDefence  += Player.getEffects()->getDefenceFire();

//  if (Player.getEffects()->isEffectActive(PlayerEffectsClass::EFFECTID_ARTEFACT_OGN_SHAR))
//    resultDefence  += 6;

  return resultDefence;
  }
uint8_t PlayerClass::getDefenceElectro(void)
  {
  uint8_t resultDefence=0;
    
  resultDefence  += PlayerSpecs.defenceElectroSelf;
    
  resultDefence  += PlayerSuit.getDefenceElectro();

  resultDefence  += Player.getEffects()->getDefenceElectro();

//  if (Player.getEffects()->isEffectActive(PlayerEffectsClass::EFFECTID_ARTEFACT_VSPYSHKA))
//    resultDefence  += 10;

  return resultDefence;
  }
uint8_t PlayerClass::getDefenceChemical(void)
  {
  uint8_t resultDefence=0;
    
  resultDefence  += PlayerSpecs.defenceChemicalSelf;
    
  resultDefence  += PlayerSuit.getDefenceChemical();

  resultDefence  += Player.getEffects()->getDefenceChemical();

//  if (Player.getEffects()->isEffectActive(PlayerEffectsClass::EFFECTID_ARTEFACT_PLENKA))
//    resultDefence  += 6;

  return resultDefence;
  }
uint8_t PlayerClass::getDefenceGravy(void)
  {
  uint8_t resultDefence=0;
  
  resultDefence  += PlayerSpecs.defenceGravySelf;
  
  resultDefence  += PlayerSuit.getDefenceGravy();

  resultDefence  += Player.getEffects()->getDefenceGravy();

//  if (Player.getEffects()->isEffectActive(PlayerEffectsClass::EFFECTID_ARTEFACT_PRUZHINA))
//    resultDefence  += 30;

  return resultDefence;
  }
uint8_t PlayerClass::getDefenceRadiation(void)
  {
  uint8_t resultDefence=0;
  
  resultDefence  += PlayerSpecs.defenceRadiationSelf;
  
  resultDefence  += PlayerSuit.getDefenceRadiation();

  resultDefence  += Player.getEffects()->getDefenceRadiation();

//  if (Player.getEffects()->isEffectActive(PlayerEffectsClass::EFFECTID_ITEM_RAD_PROTECTOR))
//    resultDefence  += 30;

  return resultDefence;
  }
uint8_t PlayerClass::getResistanceRadiation(void)
  {
  return EEPROM_Data.data[EEPROM_STRUCT_PLAYER_DEFENCE_RADIATION_INT_SELF];
  }
*/
//uint8_t PlayerClass::getDefenceRadiationSelf(void)
//  {
//  return EEPROM_Data.PlayerDefenceRadiationSelf;
//  }
uint8_t PlayerClass::GetRegenTime(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::getRegenTime(void)]");
  #endif
  //return EEPROM_Data.data[EEPROM_STRUCT_PLAYER_REGEN_TIME];
  return *(EEPROM_Data.getParameterAddr(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_VARS, EEPROM_DataClass::PLAYER_VARS::PLAYER_VAR_REGEN_TIME));
  }
PlayerHealth_t PlayerClass::GetCurrentHealth(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::getCurrentHealth(void)]");
  #endif
  //return EEPROM_Data.data[EEPROM_STRUCT_PLAYER_CURRENT_HEALTH];
  return (PlayerHealth_t)(*(EEPROM_Data.getParameterAddr(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_VARS, EEPROM_DataClass::PLAYER_VARS::PLAYER_VAR_CURRENT_HP)));
  }
PlayerHealth_t PlayerClass::GetMaxHealth(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::getMaxHealth(void)]");
  #endif
  //return PlayerSpecs.maxHealth;
//  return GameCFG.getMaxmumPlayerHealth();
  return (PlayerHealth_t)(*(EEPROM_Data.getParameterAddr(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_VARS, EEPROM_DataClass::PLAYER_VARS::PLAYER_VAR_MAX_HP)));
  }
Percent_t PlayerClass::GetHealthPercent(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::getHealthPercent(void)]");
  #endif
  return ((uint32_t)this->GetCurrentHealth()*100)/this->GetMaxHealth();
  }
uint8_t PlayerClass::GetRadiationDose(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::getRadiationDose(void)]");
  #endif
  //return EEPROM_Data.data[EEPROM_STRUCT_PLAYER_RADIATION_DOSE];
  return *(EEPROM_Data.getParameterAddr(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_VARS, EEPROM_DataClass::PLAYER_VARS::PLAYER_VAR_CURRENT_RAD_DOSE));
  }
uint8_t PlayerClass::GetMaxRadiationDose(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::getMaxRadiationDose(void)]");
  #endif
  return GameCFG.GetMaxumumPlayerRadDose();
  }
uint8_t PlayerClass::GetRadiationDosePercent(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::getRadiationDosePercent(void)]");
  #endif
  return this->GetRadiationDose()*100/this->GetMaxRadiationDose();
  }
bool PlayerClass::IsRadiationDoseMaximimReached(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::isRadiationDoseMaximimReached(void)]");
  #endif
  if (this->GetRadiationDose() >= this->GetMaxRadiationDose())
    {
    return true;
    }
  return false;
  }
bool PlayerClass::IsSick()
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::isSick(void)]");
  #endif
  if (this->GetRadiationDose() >= TemporaryClass::RADIATION_DOSE_SICK)
    {
    return true;
    }
  return false;
  }

void PlayerClass::PlayDeathSound()
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::PlayDeathSound(void)]");
  #endif
  STALKER::PlayPlayerDeathSound();
  }
void PlayerClass::SetHealth(PlayerHealth_t value)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sprintf (USARTBuffer,"[PlayerClass::SetHealth(%03u)]", value);
    sendString(USARTBuffer);
  #endif
  if (value > this->GetMaxHealth())
    {
    value=this->GetMaxHealth();
    }
  //EEPROM_Data.data[EEPROM_STRUCT_PLAYER_CURRENT_HEALTH]    = value;
  EEPROM_Data.setParameter(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_VARS, EEPROM_DataClass::PLAYER_VARS::PLAYER_VAR_CURRENT_HP, value);
  Lcd.IsPlayerHealthNeedRedraw  = true;
  if (this->GetCurrentHealth() == 0 && this->IsAlive())
    {
    this->Die();
    }
  }

bool PlayerClass::IsZombie(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::isZombie(void)]");
  #endif
  return (this->playerStatus & this->PLAYER_STATUS_ZOMBIE) == this->PLAYER_STATUS_ZOMBIE;
  }
bool PlayerClass::IsDead(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::isDead(void)]");
  #endif
  return !this->IsAlive();
  }
bool PlayerClass::IsAlive(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::isAlive(void)]");
  #endif
  return (this->playerStatus & this->PLAYER_STATUS_ALIVE) == this->PLAYER_STATUS_ALIVE;
  /*
  if (this->playerStatus & this->PLAYER_STATUS_ALIVE)
    return true;
  return false;*/
  }
void PlayerClass::SetZombie(bool status)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sprintf (USARTBuffer,"[PlayerClass::setZombie(%01u)]", status);
    sendString(USARTBuffer);
  #endif
  if (status)
    {
    this->playerStatus  |= this->PLAYER_STATUS_ZOMBIE;
    }
  else
    {
    this->playerStatus  &=~(this->PLAYER_STATUS_ZOMBIE);
    }
  }
void PlayerClass::SetStatusAlive(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::SetStatusAlive(void)]");
  #endif
  Lcd.IsPlayerHealthNeedRedraw  = true;
  this->playerStatus  |= this->PLAYER_STATUS_ALIVE;
  
  }
void PlayerClass::SetStatusDead(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::SetStatusDead(void)]");
  #endif
  Lcd.IsPlayerHealthNeedRedraw  = true;
  this->playerStatus  &=~(this->PLAYER_STATUS_ALIVE);
  }
void PlayerClass::Save(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::save(void)]");
  #endif
  EEPROM_Data.save();
  /*
  for (uint8_t i=0;i<EEPROM.SIZE;i++)
    {
    EEPROM.data[i]  = *(EEPROM_TRANSLATION[i]);
    }
  EEPROM.save();
  */
  }
void PlayerClass::Load(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::load(void)]");
  #endif
  TODO("place here wear() is hack!");
  this->GetSuit()->Wear(0,0);
  EEPROM_Data.load();
  /*
  EEPROM.load();
  if (EEPROM.loadAndMask == 0xFF)
    return;
  for (uint8_t i=0;i<EEPROM.SIZE;i++)
    {
    *(EEPROM_TRANSLATION[i])  = EEPROM.data[i];
    }
  */
  }
void PlayerClass::Revive(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::Revive(void)]");
  #endif
  this->SetStatusAlive();
  this->SetZombie(false);
  this->SetHealth(this->GetMaxHealth());
  PDAMenu.SelectDefaultMenu();
  }
void PlayerClass::Die(void)
  {
  if (this->IsDead())
    {
    TODO ("can't die if player is dead");
    return;
    }
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::Die(void)]");
  #endif
  //uint16_t sec=GameCFG.getPlayerDeathTime();
  /*
  #warning remove this!
  if (this->getFactionID() == PlayerClass::FACTION_BANDIT)
    {
    sec-=(15*60);
    }
  else if (this->getFactionID() == PlayerClass::FACTION_SCI)
    {
    sec+=(15*60);
    }
  */
  Vibro.deactivate();
  //#ifndef FM_DISABLED
  //  fm_mute();
  //#endif
  PDASound.stopAllSounds();
//  PDASound.stopSounsPsy();
  Lcd.IsPlayerHealthNeedRedraw  = true;
  this->SetStatusDead();
  this->SetHealth(0);
  this->SetRadiationDose(0);
  //Player.GetEffects()->removeAll();
  PlayerEffects.PlayerDie();
  Env.cleanRadFilter();
  Env.cleanPsyFilter();
  Anomaly.CleanFilter();
  Player.GetStatistics()->playerDeathIncrement();
  this->Save();

  if (this->lastDamagerSource == TemporaryClass::DAMAGE_SOURCE_PSY)
    {
    this->SetZombie(true);
    }


  PDAMenu.SelectDefaultMenu();
  /*
  #warning "RAM strings"
  switch (this->lastDamagerSource)
    {
    case TemporaryClass::DamageSource::DAMAGE_SOURCE_BIO:
      {
      sprintf (Lcd.lcd_buf, "био");
      LcdString(1, LCD_LINE_1);
      }
    break;
    case TemporaryClass::DamageSource::DAMAGE_SOURCE_CHEMICAL:
      {
      sprintf (Lcd.lcd_buf, "химия");
      LcdString(10, LCD_LINE_1);
      }
    break;
    case TemporaryClass::DamageSource::DAMAGE_SOURCE_ELECTRICITY:
      {
      sprintf (Lcd.lcd_buf, "элект");
      LcdString(1, LCD_LINE_1);
      sprintf (Lcd.lcd_buf, "рич");
      LcdString(1, LCD_LINE_2);
      }
    break;
    case TemporaryClass::DamageSource::DAMAGE_SOURCE_FIRE:
      {
      sprintf (Lcd.lcd_buf, "огонь");
      LcdString(1, LCD_LINE_1);
      }
    break;
    case TemporaryClass::DamageSource::DAMAGE_SOURCE_GRAVY:
      {
      sprintf (Lcd.lcd_buf, "грави");
      LcdString(1, LCD_LINE_1);
      sprintf (Lcd.lcd_buf, "тация");
      LcdString(1, LCD_LINE_2);
      }
    break;

    case TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL:
    case TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL:
      {
      sprintf (Lcd.lcd_buf, "радиа");
      LcdString(1, LCD_LINE_1);
      sprintf (Lcd.lcd_buf, "ция");
      LcdString(1, LCD_LINE_2);
      }
    break;

    case TemporaryClass::DamageSource::DAMAGE_SOURCE_SELF:
      {
      sprintf (Lcd.lcd_buf, "сам");
      LcdString(1, LCD_LINE_1);
      }
    break;

    case TemporaryClass::DamageSource::DAMAGE_SOURCE_GRENADE:
      {
      sprintf (Lcd.lcd_buf, "гран");
      LcdString(1, LCD_LINE_1);
      sprintf (Lcd.lcd_buf, "ата");
      LcdString(1, LCD_LINE_2);
      }
    break;

    case TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC:
    {
	    sprintf (Lcd.lcd_buf, "gene");
	    LcdString(1, LCD_LINE_1);
	    sprintf (Lcd.lcd_buf, "ric");
	    LcdString(1, LCD_LINE_2);
    }
    break;

    case TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT:
    {
	    sprintf (Lcd.lcd_buf, "выб");
	    LcdString(1, LCD_LINE_1);
	    sprintf (Lcd.lcd_buf, "рос");
	    LcdString(1, LCD_LINE_2);
    }
    break;

    case TemporaryClass::DamageSource::DAMAGE_SOURCE_NONE:
    case TemporaryClass::DamageSource::DAMAGE_SOURCE_NUM:
//    case TemporaryClass::DamageSource::DAMAGE_SOURCE:
    default:
      {
      sprintf (Lcd.lcd_buf, "хз");
      LcdString(1, LCD_LINE_1);
      sprintf (Lcd.lcd_buf, "%02d", this->lastDamagerSource);
      LcdString(1, LCD_LINE_2);
      }
    break;
    }
    //sprintf (Lcd.lcd_buf, "%02d", this->lastDamagerSource);
    //LcdString(12, LCD_LINE_4);
	*/
  
  n3310LcdClass::RequestUpdate();
  //_delay_ms(1000);
  /*
  if (this->isZombie())
    {
    LcdImage(ImageZombie);
    }
  else
    {
    LcdImage(ImageSkull);
    //PDAMenu.deathScreen();
    }

  switch (this->lastAgressorType)
  {
    case PlayerClass::AGRESSOR_TYPE_GENERIC:
    sprintf (lcd_buf, "хз");
    LcdString(10, LCD_LINE_1);
    sprintf (lcd_buf, "что");
    break;

    case PlayerClass::AGRESSOR_TYPE_RADIATION:
    sprintf (lcd_buf, "радиа");
    LcdString(10, LCD_LINE_1);
    sprintf (lcd_buf, "ция");
    break;

    case PlayerClass::AGRESSOR_TYPE_ANOMALY:
    sprintf (lcd_buf, "анома");
    LcdString(10, LCD_LINE_1);
    sprintf (lcd_buf, "лия");
    break;

    //    case PlayerClass::AGRESSOR_TYPE_ADDICTION:
    //    sprintf (lcd_buf, "завис");
    //    LcdString(10, 1);
    //    sprintf (lcd_buf, "имос");
    //    break;

    case PlayerClass::AGRESSOR_TYPE_PSY:
    sprintf (lcd_buf, "ПСИ");
    LcdString(10, LCD_LINE_1);
    sprintf (lcd_buf, "изл");
    break;

    case PlayerClass::AGRESSOR_TYPE_VODKA:
    sprintf (lcd_buf, "Водоч");
    LcdString(10, LCD_LINE_1);
    sprintf (lcd_buf, "ка");
    break;

    case PlayerClass::AGRESSOR_TYPE_SUICIDE:
    sprintf (lcd_buf, "Суици");
    LcdString(10, LCD_LINE_1);
    sprintf (lcd_buf, "дник");
    break;


    case PlayerClass::AGRESSOR_TYPE_CHEATER:
    sprintf (lcd_buf, "читер!");
    LcdString(9, LCD_LINE_1);
    sprintf (lcd_buf, " :(");
    break;

    case PlayerClass::AGRESSOR_TYPE_MASTER:
    sprintf (lcd_buf, "мастер");
    LcdString(9, LCD_LINE_1);
    sprintf (lcd_buf, " :) ");
    break;
  }
  LcdString(11, LCD_LINE_2);
  LcdUpdate();
  */

  this->PlayDeathSound();
  if (GameCFG.IsGameUseParameter(GameConfig::CFG_CONFIGURATION_BITS_DEATH_COUNTER_STARTS_ONLY_AT_GRAVEYARD))
    {
    this->deathTimer  = DEATH_TIMER_MAX;
    }
  else
    {
    this->RenewDeathTimer();
    }
  
  
  if (this->IsZombie())
    {
    this->zombieTimer  = GameCFG.GetPlayerZombieTime();
    }
  /*
  if (this->lastAgressorType == PlayerClass::AGRESSOR_TYPE_PSY)
    {
    LcdImage(ImageZombie);
    LcdUpdate();
    }*/
  /*
  while (sec > 0)
    {
    --sec;
    if (this->isZombie())
      {
      sprintf (lcd_buf, "%04uс",(GameCFG.getPlayerZombieTime()-(GameCFG.getPlayerDeathTime()-sec)));
      if(GameCFG.getPlayerDeathTime() - GameCFG.getPlayerZombieTime() == sec)//TODO оптоимизировать, например, добавив счетчик?
        {
        Vibro.activate(20);
        this->PlayDeathSound();
        this->setZombie(false);
        LcdImage(ImageSkull);
        sprintf (lcd_buf, "ПСИ");
        LcdString(10, LCD_LINE_1);
        sprintf (lcd_buf, "изл");
        LcdString(11, LCD_LINE_2);
        }
      }
    else
      {
      sprintf (lcd_buf, "%04uс",sec);
      }
    LcdString(1, LCD_LINE_3);
    LcdUpdate();
    if (sec < 10)
      {
      Vibro.activate(4);
      }
    delay_ms(999);
    }
  this->Revive();
  return;
  */
  }
void PlayerClass::Kill(DamageSource_t dmgSrc)
  {
  if (this->IsDead())
    {
    TODO ("can't kill if player is dead");
    return;
    }
  #ifdef IDDQD
    return;
  #endif // IDDQD
  #ifdef DEBUG_USART_FUNCTION_CALL
    sprintf (USARTBuffer,"[PlayerClass::Kill(%03u)]", dmgSrc);
    sendString(USARTBuffer);
  #endif
  this->lastDamagerSource  = dmgSrc;
  this->Die();
  }
//void PlayerClass::DealDamage(DamageClass* damage, bool noclean)
//void PlayerClass::DealDamage(DamageClass damage)
//  {
//  this->DealDamage(damage, false);
//  }
//void PlayerClass::DealDamage(DamageClass damage, bool noclean)
void PlayerClass::DealDamage(DamageClass damage)
  {
  if (this->IsDead())
    {
    TODO ("can't deal damage if player is dead");
    return;
    }
  #ifdef IDDQD
    return;
  #endif // IDDQD
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::dealDamage(DamageClass* damage)]");
  #endif
  
  uint16_t defence  = 0;
  DamageValue_t dmgValue  = damage.GetValue();
  
  if (dmgValue == 0)
    {
    return;
    }
  
  //1 - "PlayerEffects" - внешняя защита
  //defence  = Player.GetEffects()->getDefenceFrom(damage);
  defence  = PlayerEffects.GetDefenceFrom(damage);
  
  if (defence > 0)
    {
    if (defence >= RandomPseudo.getAsPercent())
      {
      /*if (noclean == false)
        {
        damage.CleanDamage();
        }*/
      return;
      }
    }
  

  //2 - Защита костюма
  PlayerSuitClass* PlayerSuit = Player.GetSuit();
  defence  = PlayerSuit->GetDefenceFrom(damage);
  
  /*LcdClearCache();
  sprintf (lcd_buf, "%03u %03u",defence, damage->getDamageSource());
  LcdString(1,LCD_LINE_1);
  LcdUpdate();
  while(1);*/
  if (defence > 0)
    {
    if ((defence/2) > (RandomPseudo.getAsPercent() + dmgValue))//урон заблокирован бронёй без потери прочности
      {
      #ifdef DEBUG_USART_SUIT_DAMAGE
        sendString ((char*)"урон заблокирован бронёй без потери прочности\r\n");
      #endif // asdas
      /*if (noclean == false)
        {
        damage.CleanDamage();
        }*/
      return;
      }
    PlayerSuit->loseDurability(dmgValue);
    if (defence > ((Percent_t) (RandomPseudo.getAsPercent() / 2) ))//урон прошел по броне
      {
      //PlayerSuit->loseDurability(dmgValue);
      damage.CleanDamage();

      #ifdef DEBUG_USART_SUIT_DAMAGE
        sprintf (USARTBuffer,"урон прошел по броне [%03d] ост.прочность:[%05d]\r\n", dmgValue, PlayerSuit->getDurability());
        sendString(USARTBuffer);
      #endif

      return;
      }
    else //фэйл, броня не защитила
      {
      #ifdef DEBUG_USART_SUIT_DAMAGE
        sendString ((char*)"фэйл, броня не защитила...\r\n");
      #endif
      PlayerSuit->loseDurability(dmgValue);
      }
    }
	if(GameCFG.IsGameUseParameter(GameConfig::CFG_CONFIGURATION_BITS_SUTE_USE_PU)){
		if (defence >= dmgValue){
			damage.CleanDamage();
			return;
		}
		dmgValue -= defence;
	}

  Vibro.activate(3);
  this->PlayDelayedHitSound();
  
  //3 - "PlayerEffects" - собственная защита
  defence  = this->GetSelfDefenceFrom(damage);
  
  if (defence > 0)
    {
    if (defence >= RandomPseudo.getAsPercent())
      {
      /*if (noclean == false)
        {
        damage.CleanDamage();
        }
      return;*/
      }
    }
  
  //EventSystem.eventArrived(EventSystemClass::EVID_DAMAGE_TAKEN, (void*)damage);
  /*if (damage->getValue() == 0) //we don't needbecause check it on start
    {
    damage->cleanDamage();
    return;
    }*/
//РАЗОБРАТЬСЯ С СИСТЕМОЙ ПОВРЕЖДЕНИЯ!!!!!
  this->lastDamagerSource  = damage.GetSource()->Get();

  if (damage.GetValue() >= this->GetCurrentHealth())
    {
    this->Die();
    }
  else
    {
    //EEPROM_Data.playerCurrentHealth-=value;
    this->SetHealth(this->GetCurrentHealth() - damage.GetValue());
    
    //LcdClearCache();
    //sprintf (lcd_buf, "%03d %03d",this->getCurrentHealth(), damage->getValue());
    //LcdString(1,LCD_LINE_1);
    //LcdUpdate();
    //while(1);
    }
  Lcd.IsPlayerHealthNeedRedraw  = true;
  /*if (noclean == false)
    {
    damage.CleanDamage();
    }*/
  }
/*
//void PlayerClass::dealDamage(DamageValue_t value, DamageSource_t damageSrc, AGRESSOR_TYPE agressorType, TemporaryClass::AGGRESSOR_SUBTYPE aggressorSubType, DamageClass::AGGRESSOR_SOURCE aggressorSrc)
void PlayerClass::DealDamage(DamageValue_t value, DamageSource_t dmgSrc, DamageClass::AGGRESSOR_SOURCE aggressorSrc)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sprintf (USARTBuffer,"[PlayerClass::dealDamage(%03u, %03u, %03u)]", value, dmgSrc, aggressorSrc);
    sendString(USARTBuffer);
  #endif
  this->lastDamagerSource  = dmgSrc;
  //Vibro.activate(3);
//  PlayerDamage.setNewDamage(aggressorSrc, damageSrc, agressorType, aggressorSubType, value);
  //PlayerDamage.SetNewDamage(aggressorSrc, dmgSrc, value);
  //PlayerDamage.cleanDamage();
  //PlayerDamage.setFinalValue(value);
  //PlayerDamage.setAgressorType(agressorType);
  //PlayerDamage.setAgressorSubType(aggressorSubType);
  //PlayerDamage.setAgressorSource(aggressorSrc);
  this->DealDamage({value: value, damageSource:dmgSrc, aggressorSource: aggressorSrc});
  }
*/
void PlayerClass::PlayDelayedHitSound(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::PlayDelayedHitSound]");
  #endif
  this->playDelayedHitSound  = true;
  }
/*void PlayerClass::DealDamage(AGRESSOR_TYPE agressor, DamageValue_t damageValue, DamageClass::DamageSource damageSrc, AGRESSOR_TYPE agressorType, LOSE_DURABILITY loseDurability)
  {
  this->lastAgressorType  = agressorType;
  PlayerDamage.setNewDamage(aggressorSrc, damageSrc, agressorType, aggressorSubType, value);
  this->dealDamage(&PlayerDamage);
  }*/
/*
void PlayerClass::HealthMod(int8_t value)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::HealthMod]");
  #endif
  int16_t  resultHealth  = this->GetCurrentHealth() + value;
  if (resultHealth < 0)
    {
    resultHealth  = 0;
    }
  else if (resultHealth > this->GetMaxHealth())
    {
    resultHealth  = GetMaxHealth();
    }
  else // nothing
    {
    
    }
  this->SetHealth(resultHealth);
  Lcd.IsPlayerHealthNeedRedraw  = true;
  }
*/
void PlayerClass::HealthIncrase(PlayerHealth_t value)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::HealthIncrase]");
  #endif
  //this->HealthMod(value);
  
  if ((this->GetCurrentHealth() + value) > this->GetMaxHealth())
    {
    //EEPROM_Data.playerCurrentHealth  = this->getMaxHealth();
    this->SetHealth(this->GetMaxHealth());
    }
  else
    {
    //EEPROM_Data.playerCurrentHealth  += value;
    this->SetHealth(this->GetCurrentHealth() + value);
    }
  Lcd.IsPlayerHealthNeedRedraw  = true;
  }
void PlayerClass::HealthDecrase(PlayerHealth_t value)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::HealthDecrase]");
  #endif
  //this->HealthMod(0-value);
  
  if (value >= this->GetMaxHealth())
    {
    this->SetHealth(0);
    }
  else
    {
    this->SetHealth(this->GetCurrentHealth()-value);
    }
  Lcd.IsPlayerRadDoseNeedRedraw  = true;
  
  }
/*
void PlayerClass::HealthIncrement(void)
  {
  if (this->getCurrentHealth() >= this->getMaxHealth())
    return;
  //EEPROM_Data.playerCurrentHealth++;
  this->SetHealth(this->getCurrentHealth() + 1);
  Lcd.IsPlayerHealthNeedRedraw  = true;
  }
*/
/*
void PlayerClass::RadDoseDecrement(void)
  {
  if (this->getRadiationDose() == 0)
    return;
  this->SetRadiationDose(this->getRadiationDose()-1);
  Lcd.IsPlayerRadDoseNeedRedraw  = true;
  }
void PlayerClass::RadDoseIncrement(void)
  {
  if (this->getRadiationDose() >= this->getMaxRadiationDose())
    return;
  this->SetRadiationDose(this->getRadiationDose()+1);
  Lcd.IsPlayerRadDoseNeedRedraw  = true;
  }
*/
void PlayerClass::RadDoseDecrase(uint8_t value)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::RadDoseDecrase]");
  #endif
  
  if (value >= this->GetRadiationDose())
    {
    this->SetRadiationDose(0);
    }
  else
    {
    //EEPROM_Data.playerRadiationDose-=value;
    this->SetRadiationDose(this->GetRadiationDose()-value);
    }
  Lcd.IsPlayerRadDoseNeedRedraw  = true;
  
  }
void PlayerClass::RadDoseIncrase(uint8_t value)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::RadDoseIncrase]");
  #endif
  
  if ((this->GetRadiationDose() + value) >= this->GetMaxRadiationDose())
    {
    this->SetRadiationDose(GetMaxRadiationDose());
    }
  else
    {
    //EEPROM_Data.playerRadiationDose  += value;
    this->SetRadiationDose(this->GetRadiationDose() + value);
    }
  Lcd.IsPlayerRadDoseNeedRedraw  = true;
  
  //this->RadDoseMod(value);
  }
/*
void PlayerClass::RadDoseMod(int8_t value)
  {
  int16_t  resultDose  = this->GetRadiationDose() + value;
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::RadDoseMod]");
  #endif
  if (resultDose < 0)
    {
    resultDose  = 0;
    }
  else if (resultDose > this->GetMaxRadiationDose())
    {
    resultDose  = GetMaxRadiationDose();
    }
  else // nothing
    {
    
    }
  this->SetRadiationDose(resultDose);
  Lcd.IsPlayerRadDoseNeedRedraw  = true;
  }
*/
void PlayerClass::PsyToHealthProcess(void)
  {
  uint8_t effectivePSY;//,dmg=0;
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::PsyToHealthProcess]");
  #endif
  //тоесть если нету дозы    или  сопротивление больше накопленной дозы
//  if (Env.getPsyLevel() == 0 || Player.getDefencePsy() >= Env.getPsyLevel())
  if (Env.GetPsyLevel() == 0 || this->GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_PSY}) >= Env.GetPsyLevel())
    {
    return;
    }
  #ifdef MONOLIT_PSY_IMMUNE
  if (this->GetFactionID() == TemporaryClass::FACTION_MONOLIT)
    {
    return;
    }
  #endif
  effectivePSY  =  this->GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_PSY}) - Env.GetPsyLevel();
  while (effectivePSY > 0)
    {
    effectivePSY  = effectivePSY>>1;
    //dmg++;
//    this->dealDamage(1, TemporaryClass::DAMAGE_SOURCE_PSY, this->AGRESSOR_TYPE_PSY, this->AGGRESSOR_SUBTYPE_NONE, DamageClass::AGGRESSOR_SOURCE_EXTERNAL);
    this->DealDamage({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_PSY, aggressorSource:DamageClass::AGGRESSOR_SOURCE_EXTERNAL});
    }
  //if (dmg > 0)
  //  {
  //  Player.dealDamage(dmg,this->AGRESSOR_TYPE_PSY, 0);
  //  }
  }
void PlayerClass::RadDoseToHealthProcess(void)
  {
  uint8_t effectiveDoseInverted,effectiveRadLevel;
  uint16_t dmg=0;
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::RadDoseToHealthProcess]");
  #endif
  //тоесть если нету дозы    или  сопротивление больше накопленной дозы
  if (this->GetRadiationDose() == 0 || this->GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL}) >= this->GetRadiationDose())
    {
    return;
    }
  
  effectiveDoseInverted  = this->GetMaxRadiationDose() - (this->GetRadiationDose() - this->GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL}));
  if (effectiveDoseInverted <= this->radDoseToHealthCollector || (this->GetRadiationDose() >= GameCFG.GetRadDoseDoubleDamage() && effectiveDoseInverted <= (this->radDoseToHealthCollector<<1)))
    {
    this->radDoseToHealthCollector=0;
    dmg  = GameCFG.GetRadDoseDamage();
    }
  else
    {
    this->radDoseToHealthCollector++;
    }
	//обработка нейтронного потока (не ионизирует)
	if (Env.GetRadiationNeutronFluxLevel() > this->GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_RADIATION_EXTERNAL})){
		effectiveRadLevel  = Env.GetRadiationNeutronFluxLevel()  - this->GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_RADIATION_EXTERNAL});
		dmg += effectiveRadLevel;
	}
  //тоесть, если уровень радиации - максимальный, дополнительно дамажу
//  if (Env.radiationLevel > Player.getDefenceRadiation())
  if (Env.GetRadiationLevel() > this->GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_RADIATION_EXTERNAL}))
    {
//    effectiveRadLevel  = Env.radiationLevel  - Player.getDefenceRadiation();
    effectiveRadLevel  = Env.GetRadiationLevel()  - this->GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_RADIATION_EXTERNAL});
    if (effectiveRadLevel >= Env.MAX_RAD_LEVEL/2)
      {
      //Player.dealDamage(GameConfig::RAD_DOSE_DAMAGE, PlayerClass::AGRESSOR_TYPE_RADIATION, 0);
      dmg += GameCFG.GetRadDoseDamage();
      if (this->GetRadiationDose() >= this->GetMaxRadiationDose())
        {
        //Player.dealDamage(GameConfig::RAD_DOSE_DAMAGE, PlayerClass::AGRESSOR_TYPE_RADIATION, 0);
        dmg += GameCFG.GetRadDoseDamage();
        }
      }
    if (effectiveRadLevel >= Env.MAX_RAD_LEVEL-1)
      {
      //Player.dealDamage(GameConfig::RAD_DOSE_DAMAGE, PlayerClass::AGRESSOR_TYPE_RADIATION, 0);
      dmg += GameCFG.GetRadDoseDamage();
      if (this->GetRadiationDose() >= this->GetMaxRadiationDose())
        {
        //Player.dealDamage(GameConfig::RAD_DOSE_DAMAGE, PlayerClass::AGRESSOR_TYPE_RADIATION, 0);
        dmg += GameCFG.GetRadDoseDamage();
        }
      }
    }
  if (dmg > 0){
	  if (dmg > 255){
		  dmg = 255;
	  }
//    this->dealDamage(dmg, TemporaryClass::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL, PlayerClass::AGRESSOR_TYPE_RADIATION, this->AGGRESSOR_SUBTYPE_NONE, DamageClass::AGGRESSOR_SOURCE_INTERNAL);
    this->DealDamage({value: dmg, damageSource:TemporaryClass::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL, aggressorSource:DamageClass::AGGRESSOR_SOURCE_INTERNAL});
    }
  }
/*
void PlayerClass::healthIncrementCouterAdd(uint8_t value)
  {
  if (255 - value < PlayerSpecs.currentHealth)
    this->healthIncrementCouter  = 255;
  else
    this->healthIncrementCouter  = value;
  }
void PlayerClass::radiationDoseDecrementCouterAdd(uint8_t value)
  {
  if (255 - value < PlayerSpecs.radiationDose)
    this->radiationDoseDecrementCouter  = 255;
  else
    this->radiationDoseDecrementCouter  = value;
  }
*/
void PlayerClass::SetRadiationDose(uint8_t value)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::SetRadiationDose]");
  #endif
  if (value > this->GetMaxRadiationDose())
    {
    value  = this->GetMaxRadiationDose();
    }
  //EEPROM_Data.data[EEPROM_STRUCT_PLAYER_RADIATION_DOSE]=value;
  EEPROM_Data.setParameter(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_VARS, EEPROM_DataClass::PLAYER_VARS::PLAYER_VAR_CURRENT_RAD_DOSE, value);
  }
void PlayerClass::processSuicideCounter(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::processSuicideCounter]");
  #endif
  if (this->m_selfSuicideCounter > 0)
    {
    if (++this->m_selfSuicideCounter == ActionsClass::SUICIDE_DELAY_SEC)//при значении 255 произойдёт переполнение и будет == 0 =)
      {
      this->m_selfSuicideCounter=255;
      this->Kill(TemporaryClass::DAMAGE_SOURCE_SELF);
      }
    }
  }
void PlayerClass::EEPROM_init(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::EEPROM_init]");
  #endif
  this->m_Suit.EEPROM_init();
  this->m_Skills.EEPROM_init();
  this->m_Statistics.EEPROM_init();
  }
void PlayerClass::oneSecondPassed(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::oneSecondPassed]");
  #endif
  if ((this->deathTimer > 0) && (this->deathTimer != DEATH_TIMER_MAX))
    {
    this->deathTimer--;
    }
  if (this->zombieTimer > 0)
    {
    this->zombieTimer--;
    }
  if (this->IsDead())
    {
    if (this->IsZombie())
      {
      //        if(GameCFG.getPlayerDeathTime() - GameCFG.getPlayerZombieTime() == Player.getDeathTimeRemain())//TODO оптоимизировать, например, добавив счетчик?
      if(this->GetZombieTimeRemain() == 0)
        {
        PDAMenu.SelectDefaultMenu();
        Vibro.activate(20);
        this->PlayDeathSound();
        this->SetZombie(false);
        //LcdImage(ImageSkull);
        //PDAMenu.DrawImg(PDAImagesClass::IMAGES::IMG_SKULL);
		SelectedSkin->DrawPlayerDead();
        sprintf (Lcd.lcd_buf, "ПСИ");
        LcdString(10, LCD_LINE_1);
        sprintf (Lcd.lcd_buf, "изл");
        LcdString(11, LCD_LINE_2);
        }
      }
    if (this->GetDeathTimeRemain() < 10)
      {
      Vibro.activate(4);
      }
    if (this->GetDeathTimeRemain() == 0)
      {
      this->Revive();
      }
    return;
    }//if (this->isDead())
  //alive->
  //нет ничего для мёртвых дальше
  #ifdef SLOWLY_KILL
    this->DealDamage(1, DamageSource_t::DAMAGE_SOURCE_GENERIC, DamageClass::AGGRESSOR_SOURCE_INTERNAL);
  #endif // SLOWLY_KILL
  if (this->GetCurrentHealth() == 0)
    {
    TODO("0 hp and alive - BUG");
    //this->SetStatusDead();
    }
  if (--this->playerSaveTimer == 0)
    {
    this->playerSaveTimer  = TemporaryClass::PLAYER_SAVE_TIMER;
    this->Save();
    }

  this->PsyToHealthProcess();
  this->RadDoseToHealthProcess();
  this->processSuicideCounter();

  if (this->playDelayedHitSound)
    {
    this->playDelayedHitSound  = false;
    Sound::SIDS tmpSID;
    switch (rand()%12)
      {
      case 0:
      case 1:
      case 2:
        {
        tmpSID  = Sound::SID_HIT_1;
        }
      break;
      case 3:
      case 4:
      case 5:
        {
        tmpSID  = Sound::SID_HIT_2;
        }
      break;
      case 6:
      case 7:
      case 8:
        {
        tmpSID  = Sound::SID_HIT_3;
        }
      break;
      case 9:
      case 10:
        {
        tmpSID  = Sound::SID_HIT_4;
        }
      break;
      case 11:
      default:
        {
        if (this->GetHealthPercent() < 50)
          {
          tmpSID  = Sound::SID_HIT_5;
          }
        else
          {
          tmpSID  = Sound::SID_HIT_1;
          }
        }
      break;
      }
    PDASound.PlaylistAdd(tmpSID);
    }
  if (this->IsInSafeZone() && this->selfRegenTimer > 3)
    {
    this->SetInSafeZone(false);
    if (GameCFG.IsGameUseParameter(GameConfig::CFG_CONFIGURATION_BITS_REGEN_X3_IN_SAFE_ZONE))
      {
      this->selfRegenTimer  -=2;
      }
    }
  if (--this->selfRegenTimer == 0)
    {
    this->selfRegenTimer=this->GetRegenTime();
    this->DoSelfRegen();
    }
  //this->dealDamage(2, DamageClass::DAMAGE_SOURCE_RADIATION, AGRESSOR_TYPE_RADIATION, AGGRESSOR_SUBTYPE_NONE, DamageClass::AGGRESSOR_SOURCE_EXTERNAL);
  }
/*
Не регенерирует, если болен
Однако, эффект "ЕДА" восстанавливает ХП при болезни
*/
void PlayerClass::DoSelfRegen(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::DoSelfRegen]");
  #endif
  if (!this->IsSick())
    {
    this->HealthIncrase(1);//TODO: не регенерировать, если болен
    }
  //if (Player.GetEffects()->IsEffectActiveInPool(PlayerEffectsOldClass::EFFECTID_ITEM_FOOD))
  /*if (PlayerEffects.IsEffectActive(EffectFood))
    {
    this->HealthIncrase(1);//TODO: не регенерировать, если болен
    }*/
  }
PlayerName_t PlayerClass::GetName(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::getName]");
  #endif
  //return (char*)&EEPROM_Data.data[EEPROM_STRUCT_PLAYER_NAME];
  char* name  = (char*)EEPROM_Data.getParameterAddr(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_NAME);
  if (name[0] == '\0')//if (strlen(name) == 0)
    {
//    name  = RAM_STR_NAME_UNNAMED;
    name  = RAM_STR_UNDEFINED;
    }
  return name;
  }
FactionID_t PlayerClass::GetFactionID(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::getFactionID]");
  #endif
  //return EEPROM_Data.data[EEPROM_STRUCT_PLAYER_FACTION];
  return *EEPROM_Data.getParameterAddr(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_VARS, EEPROM_DataClass::PLAYER_VARS::PLAYER_VAR_FACTION_ID);
  }
//const char* PROGMEM PlayerClass::getFactionName(void)
FactionName_t PlayerClass::GetFactionName(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::getFactionName]");
  #endif
  FactionID_t FID  = this->GetFactionID();
  if (FID > 0)
    {
    return GameCFG.GetFaction(FID)->GetName();
    }
//  return RAM_STR_FACTION_NO_FACTION;
  return RAM_STR_UNDEFINED;
  /*
  switch (this->getFactionID())
    {

    case FACTION_MILITARY:
      {
      return FactionMilitary;
      }
    break;

    case FACTION_BANDIT:
      {
      return FactionBandit;
      }
    break;

    case FACTION_MONOLIT:
      {
      return FactionMonolit;
      }
    break;

    case FACTION_SCI:
      {
      return FactionSCI;
      }
    break;
    
    case FACTION_TRAIDER:
      {
      return FactionTrader;
      }
    break;

    case FACTION_NONE:
      {
      return FactionNone;
      }
    break;
    
    default:
    case FACTION_UNDEFINED:
      {
      return FactionUndefined;
      }
    break;
    }*/
  }
void PlayerClass::SetFactionID(FactionID_t FID)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::setFactionID]");
  #endif
  //EEPROM_Data.data[EEPROM_STRUCT_PLAYER_FACTION]  = FID;
  EEPROM_Data.setParameter(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_VARS, EEPROM_DataClass::PLAYER_VARS::PLAYER_VAR_FACTION_ID, FID);
  }
FactionID_t PlayerClass::GetID(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::getID]");
  #endif
  //return EEPROM_Data.data[EEPROM_STRUCT_PLAYER_ID];
  return *EEPROM_Data.getParameterAddr(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_VARS, EEPROM_DataClass::PLAYER_VARS::PLAYER_VAR_PLAYER_ID);
  }
PlayerDeathTimer_t PlayerClass::GetDeathTimeRemain(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::GetDeathTimeRemain]");
  #endif
  return this->deathTimer;
  }
bool PlayerClass::SetDeathTimeRemain(PlayerDeathTimer_t time)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::SetDeathTimeRemain]");
  #endif
  if (time > DEATH_TIMER_MAX) //-V547
    {
    return false;
    }
  this->deathTimer  = time;
  return true;
  }
PlayerDeathTimer_t PlayerClass::GetZombieTimeRemain(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::getZombieTimeRemain]");
  #endif
  return this->zombieTimer;
  }
PlayerSkillsClass* PlayerClass::GetSkills(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::getSkills]");
  #endif
  return &this->m_Skills;
  }
/*PlayerEffectsOldClass* PlayerClass::GetEffects1(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::getEffects]");
  #endif
  return &this->m_Effects1;
  }*/
PlayerStatisticsClass* PlayerClass::GetStatistics(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::getStatistics]");
  #endif
  return &this->m_Statistics;
  }
PlayerSuitClass* PlayerClass::GetSuit(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::getSuit]");
  #endif
  return &this->m_Suit;
  }
ArtefactPortsClass* PlayerClass::GetArtefactPorts(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::getArtefactPorts](void)");
  #endif
  return &this->m_ArtefactPorts;
  }
bool PlayerClass::IsInSafeZone(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::IsInSafeZone(void)]");
  #endif
  return this->m_isInsideSafeZone;
  }
void PlayerClass::SetInSafeZone(bool value)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::SetInSafeZone]");
  #endif
  this->m_isInsideSafeZone  = value;
  }
bool PlayerClass::IsDamaged(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::isDamaged(void)]");
  #endif
  return (this->GetCurrentHealth() < this->GetMaxHealth());
  }
SuicideTimer_t PlayerClass::GetSuicideTimer(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::GetSuicideTimer(void)]");
  #endif
  return this->m_selfSuicideCounter;
  }
bool PlayerClass::StartSuicideCounter(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::StartSuicideCounter(void)]");
  #endif
  this->m_selfSuicideCounter  = ActionsClass::SUICIDE_START_COUNTER;
  return true;
  }
bool PlayerClass::StopSuicideCounter(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[PlayerClass::StopSuicideCounter](void)");
  #endif
  this->m_selfSuicideCounter  = ActionsClass::SUICIDE_STOP_COUNTER;
  return true;
  }
bool PlayerClass::IsAwaitingGraveyard(void)
  {
  return (this->GetDeathTimeRemain() == DEATH_TIMER_MAX);
  }
void PlayerClass::RenewDeathTimer(void)
  {
  this->deathTimer  = GameCFG.GetPlayerDeathTime();
  }

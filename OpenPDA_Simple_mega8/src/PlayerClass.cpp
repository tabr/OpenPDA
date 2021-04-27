// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * PlayerClass.cpp
 *
 * Created: 09.11.2015 0:56:11
 *  Author: tabr
 */ 

void PlayerSimpleClass::TimerUpdateEvent (uint8_t msPassed)
	{
	static uint16_t oneSecondCounter=0;
	oneSecondCounter+=msPassed;
	if (oneSecondCounter >= 1000)
		{
		oneSecondCounter-=1000;
		this->oneSecondPassed();
		}
	}
PlayerEffectsSimpleClass* PlayerSimpleClass::GetEffects(void)
	{
	return &this->m_Effects;;
	}
void PlayerSimpleClass::Kill(DamageSource_t damageSrc)
	{
	#ifdef DEBUG_USART_CODES
		USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_ENTER_PLAYER_KILL);
	#endif // DEBUG_USART_CODES
  if (this->IsAlive())
    {
  	#ifdef DEBUG_USART_CODES
	  	USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_ENTER_PLAYER_KILL_PLAYER_ALIVE_SETTING_HP_0);
	  #endif // DEBUG_USART_CODES
    this->SetHealth(0);
	  //this->DealSimpleDamage(this->GetCurrentHealth(),damageSrc);
    }
	}
bool PlayerSimpleClass::IsInSafeZone(void)
	{
	//return (PlayerInSafeShelterTimer > 0);
	return (this->inSafeShelterTimer > 0);
	}
bool PlayerSimpleClass::IsLeavingSafeZone(void)
	{
	return (this->inSafeShelterTimer == (SAFE_SHELTER_TIMER/2));
	}
bool PlayerSimpleClass::IsInSafeShelterNearTransmitter(void)
	{
	return (this->inSafeShelterTimer > (SAFE_SHELTER_TIMER/2));
	}
void PlayerSimpleClass::SetInSafeZone(bool value)
	{
	this->inSafeShelterTimer	= SAFE_SHELTER_TIMER;
	}
bool PlayerSimpleClass::IsAlive()
	{
	return !(this->IsDead());
	}
bool PlayerSimpleClass::IsDead()
	{
	return (this->GetCurrentHealth() == 0);
	}
void PlayerSimpleClass::HealthIncrase(uint8_t value)
	{
	if (this->GetCurrentHealth() > (this->GetMaxHealth() - value))
		{
		this->SetHealth(this->GetMaxHealth());
		}
	else
		{
		this->SetHealth(this->GetCurrentHealth() + value);
		}
	}
void PlayerSimpleClass::SetHealth(uint16_t value)
	{
  bool wasAlive = this->IsAlive();
 	#ifdef DEBUG_USART_CODES
  	USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_ENTER_PLAYER_SETHEALTH);
  #endif // DEBUG_USART_CODES
	#ifdef IDDQD
		this->m_health	= this->GetMaxHealth();
		return;
	#endif // IDDQD
	if (value > this->GetMaxHealth())
		{
		value=this->GetMaxHealth();
		}
	this->m_health	= value;
	if (wasAlive && value == 0)
		{
   	#ifdef DEBUG_USART_CODES
 	    USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_ENTER_PLAYER_SETHEALTH_CALLING_DIE);
 	  #endif // DEBUG_USART_CODES
//    if (killedByTimeSync == false && killedByTimeSync == false)
    if (killedByTimeSync == false)
      {
		  this->Die(TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC);
      }
		}
	}
void PlayerSimpleClass::HealthDecrase(uint8_t value)
	{
  if (this->IsDead())
    {
    return;
    }
	if (this->GetCurrentHealth() > (value + this->GetMaxHealth()))
		{
		this->SetHealth(0);
//    this->Die(TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC);
		}
	else
		{
		this->SetHealth(this->GetCurrentHealth() - value);
		}
	}
uint16_t PlayerSimpleClass::GetMaxHealth(void)
	{
	#ifdef IS_MONOLYTH
	return this->MAX_HEALTH * 5;
	#else
	return this->MAX_HEALTH;
	#endif
	}
void PlayerSimpleClass::RenewDeathTimer(void)
	{
	this->deathTimer	= GameCFG.GetPlayerDeathTime();
	}
void PlayerSimpleClass::Die(DamageSource_t damageSrc)
	{
 	#ifdef DEBUG_USART_CODES
  	USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_ENTER_PLAYER_DIE);
 	#endif // DEBUG_USART_CODES
	#ifdef IDDQD
		return;
	#endif // IDDQD
//  if (this->IsDead())// && !(this->IsZombie()))
//    {
//    return;
//    }
//	this->SetHealth(0);
	if (GameCFG.IsGameUseParameter(GameConfig::CFG_CONFIGURATION_BITS_DEATH_COUNTER_STARTS_ONLY_AT_GRAVEYARD))
		{
		this->deathTimer	= DEATH_TIMER_MAX;
//    this->RenewDeathTimer();
 	  #ifdef DEBUG_USART_CODES
 	    USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_ENTER_PLAYER_DIE_SET_GO_GRAVEYARD);
   	#endif // DEBUG_USART_CODES
		}
	else
		{
 	  #ifdef DEBUG_USART_CODES
 	    USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_ENTER_PLAYER_DIE_RENEW_DEATH_TIMER);
   	#endif // DEBUG_USART_CODES
		this->RenewDeathTimer();
		}
  GreenLEDPin::SetOutLow();
	if (damageSrc == TemporaryClass::DamageSource::DAMAGE_SOURCE_PSY)
		{
		this->zombieTimer	= GameCFG.GetPlayerZombieTime();
		}
  else
    {
    this->zombieTimer = 0;
    }
  this->inSafeShelterTimer = 0;
	RedLEDPin::SetOutLow();
	GreenLEDPin::SetOutLow();
	PlayDeathSound();
	//GreenLEDPin::setOutLow();
	wdt_reset();
	}
void PlayerSimpleClass::Revive(void)
	{
	#ifdef DEBUG_USART_REVIVE
	USART_startTX((char*)"[PlayerClass::Revive] enter\r\n");
	#endif
  /*
  static uint8_t a=0;
  if (a > 0)
    {
    return;
    }
	a++;
  */
	BuzzerOff();
	/*
	while (1)
		{
		//ждем ватчдог
		BuzzerPin::setOutToggle();
		BuzzerPin_H::setOutToggle();
		_delay_ms(100);
		}
	*/
	this->SetHealth(this->GetMaxHealth());
	this->deathTimer			= 0;
	this->zombieTimer			= 0;
	this->inSafeShelterTimer	= 0;

	//beepCounter	= 5*3;//150ms
	BuzzerActivate(150);
//	char zzz[]	= ;
	RedLEDPin::SetOutLow();
	GreenLEDPin::SetOutLow();
	#ifdef DEBUG_USART_CODES
		USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_PLAYER_REVIVED);
	#endif // DEBUG_USART_CODES
	if (this->IsDead())
		{
		#ifdef DEBUG_USART_CODES
			USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_PLAYER_REVIVED);
		#endif // DEBUG_USART_CODES
		}
	}
bool PlayerSimpleClass::IsZombie()
	{
	return (this->GetZombieTimeRemain() != 0);
	}
/*
void PlayerSimpleClass::DealDamage(uint8_t value, DamageSource_t damageSrc, DamageClass::AGGRESSOR_SOURCE internal_external)
	{
	this->DealSimpleDamage(value, damageSrc);
	}*/
/*
void PlayerSimpleClass::DealSimpleDamage(uint8_t value, DamageSource_t damageSrc)
	{
	if (value == 0)
		{
		return;
		}
  if (this->IsDead())
    {
    return;
    }
	
	#ifdef DEBUG_USART_CODES
		USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_PLAYER_DAMAGE_TAKEN);
	#endif // DEBUG_USART_CODES
	#ifdef DEBUG_USART_DAMAGE
		sprintf(USARTBuffer, "[PlayerClass::DealSimpleDamage(%03u)]\r\n", value);
		USART_startTX(strlen(USARTBuffer));
	#endif
	if (this->GetCurrentHealth()  < value)
		{
		value = this->GetCurrentHealth();
		}

	this->HealthDecrase(value);
	BuzzerActivate(50);
	}
*/
void PlayerSimpleClass::DealDamage(DamageClass dmg)
	{
	if (dmg.GetValue() == 0)
		{
		return;
		}
  if (this->IsDead())
    {
    return;
    }
	
	#ifdef DEBUG_USART_CODES
		USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_PLAYER_DAMAGE_TAKEN);
	#endif // DEBUG_USART_CODES
	#ifdef DEBUG_USART_DAMAGE
		sprintf(USARTBuffer, "[PlayerClass::DealSimpleDamage(%03u)]\r\n", value);
		USART_startTX(strlen(USARTBuffer));
	#endif
	if (this->GetCurrentHealth()  <= dmg.GetValue())
		{
		//value = this->GetCurrentHealth();
    #ifdef DEBUG_USART_CODES
      USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_DEAL_DAMAGE_DMG_HIGH_KILLING);
    #endif // DEBUG_USART_CODES
    this->Kill(dmg.GetSource()->Get());
		}
  else
    {
	  this->HealthDecrase(dmg.GetValue());
    }
	BuzzerActivate(50);
	}

uint8_t PlayerSimpleClass::GetHealthPercent(void)
	{
	return ((uint32_t)this->GetCurrentHealth()*100)/this->GetMaxHealth();
	}
uint16_t PlayerSimpleClass::GetCurrentHealth(void)
	{
	return this->m_health;
	}
bool PlayerSimpleClass::IsDamaged(void)
	{
	return (this->GetCurrentHealth() < this->GetMaxHealth());
	}
void PlayerSimpleClass::oneSecondPassed(void)
	{
	//oneSecPassed	= true;
	//USART_startTX("[PlayerClass::oneSecondPassed]\r\n");
	//self-regen->
	if (this->IsAlive())
		{
		if (this->IsDamaged())
			{
			if (TimeRTC.second & 1)//раз в 2 сек реген
				{
				this->HealthIncrase(1);
				}
			}
		}
	if (this->IsZombie())
		{
		#ifdef DEBUG_USART_CODES
			USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_PLAYER_IS_ZOMBIE);
		#endif // DEBUG_USART_CODES
		if (soundDeathStage == 0)//death sound stops beep
			{
			BuzzerActivate(20);
			}
		//PlayerZombieTimer--;
		if (--this->zombieTimer == 0)
			{
			PlayDeathSound();
			}
		//beepCounter	= 2;
		}
	//else if (isPlayerDead)
	else if (this->IsDead())
		{
		//auto-revive->
		if(this->IsAwaitingGraveyard())
      {
      //should go to graveyard mo make countdown works
      }
    else
      {
      if (this->deathTimer == 0)
		  	{
		  	//USART_startTX("[PlayerClass::oneSecondPassed] reviving...\r\n");
		  	#ifdef DEBUG_USART_CODES
		  		USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_REVIVE_BY_DEATH_TIMER);
		  	#endif // DEBUG_USART_CODES
		  	this->Revive();
        }
		  else
			  {
			  if (--this->deathTimer < 10)
			  	{
			  	#ifdef DEBUG_USART_CODES
			  		USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_PLAYER_REVIVE_10_SEC);
			  	#endif // DEBUG_USART_CODES
			  	//beepCounter	= 2;
			  	BuzzerActivate(20);
			  	/*
			  	if (this->deathTimer == 0)
			  		{
			  		this->Revive();
			  		}*/
			  	}
			  if (killedByTimeSync == true && TimeUpdate.IsTimeSyncReceivedAtLastOnce())
			  	{
			  	#ifdef DEBUG_USART_CODES
			  		USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_SLEEP_REVIVE);
			  	#endif // DEBUG_USART_CODES
			  	this->Revive();
			  	killedByTimeSync	= false;
			  	}
			  /*if (killedBySleepEvt == true && InGameEvent_SleepTimer == 0)
			  	{
			  	killedBySleepEvt	= false;
			  	this->Revive();
			  	}*/
			  }
			}
		}
	else//Player Alive
		{
		//if (PlayerInSafeShelterTimer > 0)//таймер пребывания в безопасном убежище
		if (inSafeShelterTimer > 0)//таймер пребывания в безопасном убежище
			{
			//PlayerInSafeShelterTimer--;
			this->inSafeShelterTimer--;
			}
		}
	}

PlayerSimpleClass::PlayerSimpleClass(void)
	{
	#ifdef DEBUG_USART_CODES
		USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_INITIAL_REVIVE);
	#endif // DEBUG_USART_CODES
	this->Revive();
	}
uint16_t PlayerSimpleClass::GetDeathTimeRemain(void)
	{
	return this->deathTimer;
	}
void PlayerSimpleClass::SetDeathTimeRemain(uint16_t t)
	{
	this->deathTimer = t;
	}
uint16_t PlayerSimpleClass::GetZombieTimeRemain(void)
	{
	return this->zombieTimer;
	}
bool PlayerSimpleClass::IsAwaitingGraveyard(void)
	{
	return (this->GetDeathTimeRemain() == DEATH_TIMER_MAX);
	}
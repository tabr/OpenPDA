// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
PlayerEffectsDefenceValue_t PlayerEffectsClass::GetDefenceFrom(DamageClass Damage)
	{
	PlayerEffects_Interface* tmp[STORAGE_SIZE];
	PlayerEffectsDefenceValue_t result=0;
	uint8_t num	= this->GetActiveEffects(EFFECTID_DEF_DAMAGE_SOURCE, tmp);
	if (num == 0)//no effects
		{
		return result;
		}
	for (EffectsStorageID_t i=0;i<num;i++)
		{
		PlayerEffect_DefDamageSourceClass* Effect	= static_cast<PlayerEffect_DefDamageSourceClass*>(tmp[i]);
		if (Effect->GetDmgSrc() == Damage.GetSource()->Get())
			{
			result+= Effect->GetValue();
			}
		}
	return result;
	}
EffectsStorageID_t  PlayerEffectsClass::GetActiveEffects(EFFECTIDS  EID,  PlayerEffects_Interface*  result[])
  {
  EffectsStorageID_t  j=0;
  for  (EffectsStorageID_t  i=1;i<STORAGE_SIZE;i++)
    {
    if  ( (EID == 0 || this->parameters[i].Effect->GetID()  ==  EID) && this->parameters[i].Effect->GetID() != 0)
      {
      result[j++]  =  this->parameters[i].Effect;
      }
    }
  return  j;
  }
EffectsStorageID_t  PlayerEffectsClass::GetActiveVisibleEffects(EFFECTIDS  EID,  PlayerEffects_Interface*  result[])
  {
  EffectsStorageID_t  j=0;
  for  (EffectsStorageID_t  i=1;i<STORAGE_SIZE;i++)
    {
    if  ( ( EID == 0 || this->parameters[i].Effect->GetID() == EID ) &&  this->parameters[i].Effect->IsVisible() && this->parameters[i].Effect->GetID() != 0)
      {
      result[j++]  =  this->parameters[i].Effect;
      }
    }
  return  j;
  }

void  PlayerEffectsClass::TimerUpdateEvent (uint8_t msPassed)
  {
  static  uint16_t  timerSec=0;
  timerSec+=msPassed;
  if  (timerSec  >=  1000)  //one  sec
    {
    timerSec-=1000;
    this->OneSecTick();
    }
  }
void  PlayerEffectsClass::OneSecTick(void)
  {
  for  (auto i=1;i<STORAGE_SIZE;i++)
    {
    if  (this->IsSIDNotEmpty(i))
      {
      if  (this->parameters[i].repeatPeriodCounter  >  0)
        {
        if  (--(this->parameters[i].repeatPeriodCounter)  ==  0)
          {
          //tick  &  reload
          this->parameters[i].Effect->OnTick();
          PlayerEffects_Interface*  Effect  =  this->parameters[i].Effect;
          if  (  (this->parameters[i].repeatTimesCounter  >  0)  ||  (Effect->GetCFG()  &  (1<<PE_CFG_TICK_INFINILTY_UNTIL_DIE)))  //reload  timer
            {
            this->parameters[i].repeatPeriodCounter  =  Effect->GetRepeatPeriodSec();
            if  (Effect->GetCFG()  &  (1<<PE_CFG_TICK_INFINILTY_UNTIL_DIE))
              {
              //nothing?
              }
            else
              {
              this->parameters[i].repeatTimesCounter--;
              }
            }//reload timer
          else  //stop  timer
            {
            //this->storage[i]  =  &this->PlayerEffect_NullEffect;
            //this->parameters[i]  =  {0,0};
            this->RemoveEffect(i);
            }//else reload timer
          }// == 0
        }// > 0
      }//not empty
    }//cycle
  }
/*
PlayerEffects_Interface* PlayerEffectsClass::GetEffect(PlayerEffectGUID_t EGUID)
  {
  return GameCFG.GetPlayerEffect(EGUID);
  }
*/
/*
EffectsStorageID_t PlayerEffectsClass::IsEffectActive(PlayerEffectGUID_t EGUID)
  {
  PlayerEffects_Interface* Effect = GameCFG.GetPlayerEffect(EGUID);
  return this->IsEffectActive(Effect);
  }
*/
EffectsStorageID_t PlayerEffectsClass::IsEffectActive(PlayerEffects_Interface*  Effect)
  {
  for  (EffectsStorageID_t  i=1;i<STORAGE_SIZE;i++)//renew  if  already  applied
    {
    if  (this->parameters[i].Effect->GetID()  ==  Effect->GetID())
      {
      return  i;
      }
    }
  return  0;
  }
void  PlayerEffectsClass::PlayerDie(void)
  {
  this->CleanAllEffects();
  }
void  PlayerEffectsClass::RemoveEffect(EffectsStorageID_t  SID)
  {
  PlayerEffects_Interface*  Effect  =  this->FromStorageID(SID);
  
  if  (Effect  ==  NULL)
    {
    return;
    }
  if  (Effect->GetID()  ==  EFFECTID_NONE)
    {
    return;
    }
  Effect->OnRemove();
  //PlayerEffect_NullEffect.OnRemove();
  //this->FromStorageID(SID)->OnRemove();
  //this->storage[SID]->OnTick();
  this->CleanEffect(SID);
  }
uint16_t PlayerEffectsClass::GetRemainTimeSec(PlayerEffects_Interface*  Effect)
  {
  for  (EffectsStorageID_t  i=1;i<STORAGE_SIZE;i++)
    {
    //if  (this->storage[i]->GetID()  ==  Effect->GetID())
    if  (this->parameters[i].Effect  ==  Effect)
      {
      
      uint16_t retData  = (this->parameters[i].repeatTimesCounter * this->parameters[i].repeatPeriodCounter);
      return  retData;
      }
    }
  
  return  0;
  }
/*
EffectsStorageID_t PlayerEffectsClass::RenewEffectInstance(PlayerEffectGUID_t EGUID)
  {
  PlayerEffects_Interface* Effect = GameCFG.GetPlayerEffect(EGUID);
  return this->RenewEffectInstance(Effect);
  }
*/
EffectsStorageID_t PlayerEffectsClass::RenewEffectInstance(PlayerEffects_Interface*  Effect)//apply  new  or  reload  counters
  {
  for  (EffectsStorageID_t  i=1;i<STORAGE_SIZE;i++)//renew  if  already  applied
    {
//    if  (this->parameters[i].Effect->GetID()  ==  Effect->GetID())
    if  (this->parameters[i].Effect  ==  Effect)
      {
      this->parameters[i].repeatPeriodCounter  =  Effect->GetRepeatPeriodSec();
      this->parameters[i].repeatTimesCounter  =  Effect->GetRepeatTimes();
      return  i;
      }
    }
  //apply  new  if  not  applied
  return  this->ApplyEffectInstance(Effect);
  }
/*
EffectsStorageID_t  PlayerEffectsClass::ApplyEffectInstance(PlayerEffectGUID_t EGUID)
  {
  PlayerEffects_Interface* Effect = GameCFG.GetPlayerEffect(EGUID);
  return this->ApplyEffectInstance(Effect);
  }
*/
EffectsStorageID_t PlayerEffectsClass::ApplyEffectInstance(PlayerEffects_Interface*  Effect)
  {
  EffectsStorageID_t  SID  =  this->GetFreeStorageID();
  if  (SID  ==  0)
    {
    return  0;
    //while(1);
    }
  //Effect->SetStorageID(SID);
  this->parameters[SID].Effect                =  Effect;
  this->parameters[SID].repeatPeriodCounter   =  Effect->GetRepeatPeriodSec();
  this->parameters[SID].repeatTimesCounter    =  Effect->GetRepeatTimes();
  Effect->OnApply();
  return  SID;
  }
PlayerEffects_Interface* PlayerEffectsClass::FromStorageID(  EffectsStorageID_t  SID  )
  {
  if  (IsSIDValid(SID))
    {
    return  this->parameters[SID].Effect;
    }
  return  NULL;
  }
bool PlayerEffectsClass::IsSIDValid( EffectsStorageID_t SID )
  {
  return  ((SID  <  this->STORAGE_SIZE)  &&  (SID  >  0));
  }
PlayerEffectsClass::PlayerEffectsClass(void)
  {
  this->CleanAllEffects();
  }
void  PlayerEffectsClass::CleanEffect(EffectsStorageID_t  SID)
  {
  this->parameters[SID].Effect              =  &this->PlayerEffect_NullEffect;
  this->parameters[SID].repeatPeriodCounter  =  0;
  this->parameters[SID].repeatTimesCounter  =  0;
  }
void  PlayerEffectsClass::CleanAllEffects(void)
  {
  for  (uint8_t  i=0;i<STORAGE_SIZE;i++)
    {
    //this->storage[i]  =  &this->PlayerEffect_NullEffect;
    //this->parameters[i]  =  {0,0};
    this->CleanEffect(i);
    }
  }
bool  PlayerEffectsClass::IsSIDEmpty(EffectsStorageID_t  SID)
  {
  return  (this->parameters[SID].Effect->GetID()  ==  PlayerEffectsClass::EFFECTIDS::EFFECTID_NONE);
  }
bool  PlayerEffectsClass::IsSIDNotEmpty(EffectsStorageID_t  SID)
  {
  return  !(this->IsSIDEmpty(SID));
  }
EffectsStorageID_t  PlayerEffectsClass::GetFreeStorageID(void)  
  {
  for  (uint8_t  i=1;i<STORAGE_SIZE;i++)
    {
    if  (this->IsSIDEmpty(i))
      {
      return  i;
      }
    }
  return  0;
  }



/////////////////////////////////////////////////////////////////////////////
void PlayerEffect_NullEffectClass::OnTick(void)
	{
	//nothing
	}
void PlayerEffect_NullEffectClass::OnApply(void)
	{
	//nothing
	}
void PlayerEffect_NullEffectClass::OnRemove(void)
	{
	//nothing
	}
EffectID_t PlayerEffect_NullEffectClass::GetID(void)
	{
	return PlayerEffectsClass::EFFECTIDS::EFFECTID_NONE;
	}
/////////////////////////////////////////////////////////////////////////////

void PlayerEffect_DealDamageClass::SetDamage(DamageClass* dmg)
	{
	this->m_dmg				= dmg;
	}

void PlayerEffect_DealDamageClass::OnTick(void)
	{
//	Player.DealDamage(*this->m_dmg, true);
	Player.DealDamage(*this->m_dmg);
  #warning "[T] CleanDamage removed"
	}
void PlayerEffect_DealDamageClass::OnApply(void)
	{
	
	}
void PlayerEffect_DealDamageClass::OnRemove(void)
	{
	
	}
EffectID_t PlayerEffect_DealDamageClass::GetID(void)
	{
	return PlayerEffectsClass::EFFECTIDS::EFFECTID_DEAL_DAMAGE;
	}
/////////////////////////////////////////////////////////////////////////////
void PlayerEffect_ModHealthClass::SetModHealthValue(int8_t value)
	{
	this->m_value	= value;
	}
void PlayerEffect_ModHealthClass::OnTick(void)
	{
    TODO("V547 Expression 'this->m_value < 0' is always false. Unsigned type value is never < 0. playereffectsclass.cpp 294");
	//Player.HealthMod(this->m_value);
  if (this->m_value > 0)
    {
    Player.HealthIncrase(this->m_value);
    }
  else if (this->m_value < 0) //-V547
    {
    Player.HealthDecrase(abs(this->m_value));
    }
  //else 0, do nothing
	}
void PlayerEffect_ModHealthClass::OnApply(void)
	{
	
	}
void PlayerEffect_ModHealthClass::OnRemove(void)
	{
	
	}
EffectID_t PlayerEffect_ModHealthClass::GetID(void)
	{
	return PlayerEffectsClass::EFFECTIDS::EFFECTID_MOD_HEALTH;
	}
/////////////////////////////////////////////////////////////////////////////
void PlayerEffect_ModRadDoseClass::SetDoseValue(int8_t value)
	{
	this->m_value	= value;
	}
void PlayerEffect_ModRadDoseClass::OnTick(void)
	{
	//Player.RadDoseMod(this->m_value);
  if (this->m_value > 0)
    {
    Player.RadDoseIncrase(this->m_value);
    }
  else if (this->m_value < 0) //-V547
    {
    Player.RadDoseDecrase(abs(this->m_value));
    }
    //else 0, do nothing
	}
void PlayerEffect_ModRadDoseClass::OnApply(void)
	{
	
	}
void PlayerEffect_ModRadDoseClass::OnRemove(void)
	{
	
	}
EffectID_t PlayerEffect_ModRadDoseClass::GetID(void)
	{
	return PlayerEffectsClass::EFFECTIDS::EFFECTID_MOD_RAD_DOSE;
	}
/////////////////////////////////////////////////////////////////////////////
void PlayerEffect_HealClass::SetHealValue(uint8_t value)
	{
	this->m_value	= value;
	}
void PlayerEffect_HealClass::OnTick(void)
	{
	Player.HealthIncrase(this->m_value);
//	Player.HealthIncrase(1);
	}
void PlayerEffect_HealClass::OnApply(void)
	{
	
	}
void PlayerEffect_HealClass::OnRemove(void)
	{
	
	}
EffectID_t PlayerEffect_HealClass::GetID(void)
	{
	return PlayerEffectsClass::EFFECTIDS::EFFECTID_HEAL;
	}
/////////////////////////////////////////////////////////////////////////////
void PlayerEffect_DefDamageSourceClass::SetDmgSrc(DamageSource_t dmgSrc, PlayerEffectsDefenceValue_t value)
	{
	this->m_value	= value;
	this->m_dmgSrc	= dmgSrc;
	}
void PlayerEffect_DefDamageSourceClass::OnTick(void)
	{
	//Player.HealthIncrase(this->m_value);
	}
void PlayerEffect_DefDamageSourceClass::OnApply(void)
	{
	
	}
void PlayerEffect_DefDamageSourceClass::OnRemove(void)
	{
	
	}
EffectID_t PlayerEffect_DefDamageSourceClass::GetID(void)
	{
	return PlayerEffectsClass::EFFECTIDS::EFFECTID_DEF_DAMAGE_SOURCE;
	}
DamageSource_t PlayerEffect_DefDamageSourceClass::GetDmgSrc(void)
	{
	return this->m_dmgSrc;
	}
void PlayerEffect_DefDamageSourceClass::SetValue(PlayerEffectsDefenceValue_t val)
  {
  this->m_value = val;
  }
PlayerEffectsDefenceValue_t PlayerEffect_DefDamageSourceClass::GetValue(void)
	{
	return this->m_value;
	}
/////////////////////////////////////////////////////////////////////////////
void PlayerEffect_CombinedClass::SetCombined(PlayerEffects_Interface** array, uint8_t num)
	{
	this->m_array   = array;
	this->m_num     = num;
	this->SID_Array = new uint8_t[num];
	}
void PlayerEffect_CombinedClass::OnTick(void)
	{
	}
void PlayerEffect_CombinedClass::OnApply(void)
	{
	for (uint8_t i=0;i<this->m_num;i++)
		{
		this->SID_Array[i]	= PlayerEffects.ApplyEffectInstance(this->m_array[i]);
		}
	}
void PlayerEffect_CombinedClass::OnRemove(void)
	{
	for (uint8_t i=0;i<this->m_num;i++)
		{
		PlayerEffects.RemoveEffect(this->SID_Array[i]);
		}
	}
EffectID_t PlayerEffect_CombinedClass::GetID(void)
	{
	return PlayerEffectsClass::EFFECTIDS::EFFECTID_COMBINED;
	}
/////////////////////////////////////////////////////////////////////////////
void PlayerEffect_NoActionClass::SetProperty(uint8_t property)
	{
	this->m_property	= property;
	}
uint8_t PlayerEffect_NoActionClass::GetProperty(void)
	{
	return this->m_property;
	}
EffectID_t PlayerEffect_NoActionClass::GetID(void)
	{
	return PlayerEffectsClass::EFFECTIDS::EFFECTID_NO_ACTION;
	}
/////////////////////////////////////////////////////////////////////////////
void PlayerEffect_SafeShelterClass::OnTick(void)
	{
	}
void PlayerEffect_SafeShelterClass::OnApply(void)
	{
	}
void PlayerEffect_SafeShelterClass::OnRemove(void)
	{
	}
EffectID_t PlayerEffect_SafeShelterClass::GetID(void)
	{
	return PlayerEffectsClass::EFFECTIDS::EFFECTID_SAFE_SHELTER;
	}
/////////////////////////////////////////////////////////////////////////////
void PlayerEffect_FoodClass::OnTick(void)
	{
	}
void PlayerEffect_FoodClass::OnApply(void)
	{
	}
void PlayerEffect_FoodClass::OnRemove(void)
	{
	}
EffectID_t PlayerEffect_FoodClass::GetID(void)
	{
	return PlayerEffectsClass::EFFECTIDS::EFFECTID_FOOD;
	}
/////////////////////////////////////////////////////////////////////////////
void PlayerEffect_DeathTimerClass::OnTick(void)
	{
	}
void PlayerEffect_DeathTimerClass::OnApply(void)
	{
	}
void PlayerEffect_DeathTimerClass::OnRemove(void)
	{
	Player.Kill(this->m_kill_DamageSource);
	}
EffectID_t PlayerEffect_DeathTimerClass::GetID(void)
	{
	return PlayerEffectsClass::EFFECTIDS::EFFECTID_DEATH_TIMER;
	}
void PlayerEffect_DeathTimerClass::SetDmgSrc(DamageSource_t dmgSrc)
	{
	this->m_kill_DamageSource	= dmgSrc;
	}
/////////////////////////////////////////////////////////////////////////////
//PlayerEffectsDefenceValue_t PlayerEffectsClass::GetDefenceFrom(DamageSource_t dmgSrc)

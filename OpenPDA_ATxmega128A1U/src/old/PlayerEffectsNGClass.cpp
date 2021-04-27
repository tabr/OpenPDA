// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * PlayerEffectsNGClass.cpp
 *
 * Created: 2015-07-17 15:54:39
 *  Author: tabr
 */ 
void PlayerEffectsNGClass::PlayerEffectsNGClassTask1::Task(void)
	{
	PlayerEffectsNG.oneSecondPassed();
	}

void PlayerEffectsNGClass::tickEffect(uint8_t pool_idx)
	{
	switch (this->pool[pool_idx].getID())
		{
		case PlayerEffectInstanceClass::EFFECTID_INCREASE_HEALTH_1:
			{
			Player.HealthIncrement();
			}
		break;

		/*case PlayerEffectInstanceClass::EFFECTID_DECREASE_HEALTH_1:
			{
			Player.healthd();
			}
		break;*/

		case PlayerEffectInstanceClass::EFFECTID_INCREASE_RADDOSE_1:
			{
			Player.RadDoseIncrement();
			}
		break;

		case PlayerEffectInstanceClass::EFFECTID_DECREASE_RADDOSE_1:
			{
			Player.RadDoseDecrement();
			}
		break;

		}
	}
void PlayerEffectsNGClass::oneSecondPassed(void)//every 1sec
	{
	for (uint8_t i=0; i < this->POOL_SIZE; i++)
		{
		if (this->pool[i].isActive())
			{
			if (this->pool[i].tick())
				{
				this->tickEffect(i);
				}
			}
		}
	}
bool PlayerEffectsNGClass::remove(PlayerEffectsDescriptor effect)
	{
	if (effect->isActive())
		{
		effect->cleanEffect();
		return true;
		}
	return false;
	}
PlayerEffectsDescriptor PlayerEffectsNGClass::apply(PlayerEffectInstanceClass::EFFECTIDS EID, PlayerEffectInstanceClass::EFFECT_TIMINGS time, uint8_t repeatPeriod_sec, uint8_t repeatCounter)//returns link to a class or NULL
	{
	for (uint8_t i=0;i<POOL_SIZE;i++)
		{
		if (this->pool[i].isInactive())
			{
			this->pool[i].setEffect(EID, time, repeatPeriod_sec, repeatCounter);
			return &(this->pool[i]);
			}
		}
	return NULL;
	//return new PlayerEffectsInstance(EID);
	}



















bool PlayerEffectInstanceClass::tick(void)//return true is should process effect. effects processing outside
	{
	switch (this->m_cfg_time)
		{
		case EFFECT_TIMINGS_ONCE:
			{
			this->cleanEffect();
			return true;
			}
		break;
		
		case EFFECT_TIMINGS_UNTILL_COUNTER_UNTILL_DIE:
			{
			if (Player.isDead())
				{
				this->cleanEffect();
				return false;
				}
			if (this->m_repeatTimes == 0)
				{
				this->cleanEffect();
				return false;
				}
			if ((--(this->m_secCounter)) == 0)
				{
				this->m_secCounter	= this->m_cfg_repeatPeriod_sec;
				this->m_repeatTimes--;
				return true;
				}
			return false;
			}
		break;
		
		case EFFECT_TIMINGS_UNTILL_DIE:
			{
			if (Player.isDead())
				{
				this->cleanEffect();
				return false;
				}
			if ((--(this->m_secCounter)) == 0)
				{
			hui++;
				this->m_secCounter	= this->m_cfg_repeatPeriod_sec;
				this->m_repeatTimes--;
				return true;
				}
			return false;
			}
		break;

		case EFFECT_TIMINGS_PERMANENT:
			{
			if ((--(this->m_secCounter)) == 0)
				{
				this->m_secCounter	= this->m_cfg_repeatPeriod_sec;
				this->m_repeatTimes--;
				return true;
				}
			return false;
			}
		break;

		case EFFECT_TIMINGS_EXPIRED:
		default:
			{
			
			}
		break;
		}
	return false;
	}
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * InGameEvent_RadStormClass.cpp
 *
 * Created: 27.09.2017 3:00:29
 *  Author: tabr
 */ 
#include "InGameEvent_RadStormClass.hpp"

void InGameEvent_RadStormClass::Task (void)
	{
	if (Player.IsDead())
		{
		return;
		}
	BlowoutTimer=BLOWOUT_SAFE_TIME_SEC;
	//if (PlayerEffects.IsEffectActive(TemporaryClass::PLAYEREFFECT_SAFE_SHELTER))
  if (PlayerEffects.IsEffectActive(EffectSafeShelterHack))
  
		{
		//TODO
		}
	else
		{
		//Player.DealDamage(1, TemporaryClass::DAMAGE_SOURCE_RADIATION_EXTERNAL, DamageClass::AGGRESSOR_SOURCE_EXTERNAL);
    //Env.RadLevelSet1(75);
    Env.RadLevelSetFilter(85);
    Env.RadLevelSetFilter(85);
		}
	/*
  if (this->RadStormSoundTimer == 0)
		{
		PDASound.PlaylistAdd(Sound::SID_BLOWOUT_HIT_2);
		this->RadStormSoundTimer = 5+(rand()%30);
		}
	else
		{
		--this->RadStormSoundTimer;
		}
  */
	}
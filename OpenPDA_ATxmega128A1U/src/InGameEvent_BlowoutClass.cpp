// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * BlowoutEventClass.cpp
 *
 * Created: 25.10.2015 23:16:37
 *  Author: tabr
 */ 
#include "inGameEvent_BlowoutClass.hpp"

void InGameEvent_BlowoutClass::Task (void)
	{
	if (Player.IsDead())
		{
		return;
		}
	BlowoutTimer=BLOWOUT_SAFE_TIME_SEC;
	//if (Player.GetEffects()->IsEffectActiveInPool(PlayerEffectsOldClass::EFFECTID_SAFE_SHELTER))
	//if (PlayerEffects.IsEffectActive(TemporaryClass::PLAYEREFFECT_SAFE_SHELTER))
	if (PlayerEffects.IsEffectActive(EffectSafeShelterHack))
		{
		//TODO
		}
	else
		{
		Player.DealDamage({value: 7, damageSource:TemporaryClass::DAMAGE_SOURCE_BLOWOUT, aggressorSource:DamageClass::AGGRESSOR_SOURCE_EXTERNAL});
		}
	if (this->BlowoutSoundTimer == 0)
		{
		PDASound.PlaylistAdd(Sound::SID_BLOWOUT_HIT_2);
		this->BlowoutSoundTimer = 5+(rand()%30);
		}
	else
		{
		--this->BlowoutSoundTimer;
		}
	}

void InGameEvent_BlowoutPrepareClass::Task (void)
	{
	if (Player.IsDead())
		{
		return;
		}
	if (this->BlowoutSoundTimer == 0xFF){
		this->BlowoutSoundTimer = 5;
		//PDASound.PlaylistAdd(Sound::SID_KOALSKY_2);
		//PDASound.PlaylistAdd(Sound::SID_KOALSKY_4);
	}
	if (this->BlowoutSoundTimer == 0)
		{
		PDASound.PlaylistAdd(Sound::SID_BLOWOUT_HIT_2);
		this->BlowoutSoundTimer = 5+(rand()%30);
		}
	else
		{
		--this->BlowoutSoundTimer;
		}
	}
		
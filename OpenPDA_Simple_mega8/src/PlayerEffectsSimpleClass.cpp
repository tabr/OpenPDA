// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * PlayerEffectsSimpleClass.cpp
 *
 * Created: 21.09.2017 0:50:38
 *  Author: tabr
 */ 
void PlayerEffectsSimpleClass::RenewEffect(EffectID_t EID)
	{
	if (EID == EffectSafeShelterHack)
		{
		Player.SetInSafeZone(true);
		}
	}
void PlayerEffectsSimpleClass::RenewEffectInstance(EffectsStorageID_t EID)
  {
  this->RenewEffect(EID);
  }

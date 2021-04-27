// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * GrenadeClass.cpp
 *
 * Created: 24.12.2017 2:03:24
 *  Author: tabr
 */ 
void GrenadeClass::TimerUpdateEvent (uint8_t msPassed)
  {
  static uint16_t oneSecond_msCounter=0;
  oneSecond_msCounter+=msPassed;
  if (oneSecond_msCounter < 1000)
    {
    return;
    }
  if (this->delayHackTimer > 0)
    {
    delayHackTimer--;
    }
  }
void GrenadeClass::ProcessSignal(uint8_t signalPower)
  {
  #warning "[T] need to finish GRENADE"
  if (delayHackTimer > 0)
    {
    return;
    }
  delayHackTimer  = 2;
	//RadiomarkGrenadeClass RGrenade	= RadiomarkGrenadeClass (selectedRadiomark);
	uint16_t grenadeDamage	= signalPower*5*TemporaryClass::GRENADE_DAMAGE_MULTIPLIER;
	Player.DealDamage({value: grenadeDamage, damageSource:DamageSource_t::DAMAGE_SOURCE_GRENADE, aggressorSource:DamageClass::AGGRESSOR_SOURCE::AGGRESSOR_SOURCE_EXTERNAL});
	//while(1);
	//_delay_ms(1000);
	
	//switch (RGrenade.GetType())
	//{
	//case GrenadeClass::G_TYPE_PLASMA
	//}

  }
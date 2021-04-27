/*
 * PlayerEffectsSimpleClass.h
 *
 * Created: 21.09.2017 0:49:31
 *  Author: tabr
 */ 


#ifndef PLAYEREFFECTSSIMPLECLASS_H_
#define PLAYEREFFECTSSIMPLECLASS_H_

#include "PlayerEffectsInterface.hpp"

#warning "PlayerEffectsSimpleClass unimplemented"
class PlayerEffectsSimpleClass //: public ITimerListener
	{
	public:
	void RenewEffect(EffectsStorageID_t EID);
	void RenewEffectInstance(EffectsStorageID_t EID);
	EffectsStorageID_t ApplyEffect(PlayerEffects_Interface* i)
		{
		return 0;
		}
  EffectsStorageID_t ApplyEffectInstance(PlayerEffects_Interface*  Effect)
    {
    return 0;
    }
	void RemoveEffect(EffectsStorageID_t e)
		{
		
		}
	PlayerEffects_Interface* FromStorageID( EffectsStorageID_t SID )
		{
		return &(this->PlayerEffect_NullEffect);
		}
	PlayerEffect_NullEffectDummyClass PlayerEffect_NullEffect;
};



#endif /* PLAYEREFFECTSSIMPLECLASS_H_ */
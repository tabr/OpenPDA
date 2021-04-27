/*
 * PlayerClass.h
 *
 * Created: 09.11.2015 0:54:42
 *  Author: tabr
 */ 


#ifndef PLAYERCLASS_H_
#define PLAYERCLASS_H_

#include <PlayerInterface.hpp>
class PlayerSimpleClass : public ITimerListener//, public PlayerInterface
	{
	public:
		
		void TimerUpdateEvent (uint8_t msPassed);
	
		bool IsInSafeZone(void);
		bool IsLeavingSafeZone(void);
		bool IsInSafeShelterNearTransmitter(void);
		void SetInSafeZone(bool value);
		
		bool IsAlive();
		bool IsDead();
		bool IsZombie();
		bool IsDamaged(void);
		bool IsAwaitingGraveyard(void);
		void HealthIncrase(uint8_t value);
		void HealthDecrase(uint8_t value);
		void SetHealth(uint16_t value);
		uint8_t GetHealthPercent(void);	
		uint16_t GetCurrentHealth(void);
		uint16_t GetMaxHealth(void);
		uint16_t GetDeathTimeRemain(void);
		void SetDeathTimeRemain(uint16_t t);
		uint16_t GetZombieTimeRemain(void);
//		void DealSimpleDamage(uint8_t value, DamageSource_t damageSrc);
//		void DealDamage(uint8_t value, DamageSource_t damageSrc, DamageClass::AGGRESSOR_SOURCE internal_external);
		void DealDamage(DamageClass dmg);
		void Kill(DamageSource_t damageSrc);
		void Revive(void);
		void oneSecondPassed(void);
		void RenewDeathTimer(void);
		PlayerEffectsSimpleClass* GetEffects(void);
		PlayerSimpleClass(void);
		
	protected:
	private:
		void Die(DamageSource_t damageSrc);
		const static uint16_t MAX_HEALTH	= 600;//0;
		uint16_t m_health;
		uint16_t deathTimer;
		uint16_t zombieTimer;
		uint8_t inSafeShelterTimer;
		PlayerEffectsSimpleClass m_Effects;
		const static PlayerDeathTimer_t DEATH_TIMER_MAX	= 0xFFFF;
	};


#endif /* PLAYERCLASS_H_ */
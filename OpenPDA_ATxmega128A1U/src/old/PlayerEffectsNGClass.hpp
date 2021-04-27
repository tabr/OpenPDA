/*
 * PlayerEffectsNGClass.h
 *
 * Created: 2015-07-17 13:49:17
 *  Author: tabr
 */ 


#ifndef PLAYEREFFECTSNGCLASS_H_
#define PLAYEREFFECTSNGCLASS_H_

//typedef PlayerEffectInstanceClass* PlayerEffectsDescriptor;

class PlayerEffectInstanceClass
	{
	public:
		enum EFFECTIDS
			{
			EFFECTID_NONE,
			EFFECTID_INCREASE_HEALTH_1,
			EFFECTID_INCREASE_RADDOSE_1,
			EFFECTID_DECREASE_RADDOSE_1,
//			EFFECTID_DECREASE_HEALTH_1,
			};
		enum EFFECT_TIMINGS
			{
			EFFECT_TIMINGS_EXPIRED,
			EFFECT_TIMINGS_ONCE,
			EFFECT_TIMINGS_UNTILL_COUNTER_UNTILL_DIE,
			EFFECT_TIMINGS_UNTILL_DIE,
			EFFECT_TIMINGS_PERMANENT,
			};
		PlayerEffectInstanceClass(void)
			{
			
			}
		bool isActive(void)
			{
			if (this->m_EID == this->EFFECTID_NONE)
				{
				return false;
				}
			return true;
			}
		bool isInactive(void)
			{
			return !(this->isActive());
			}
		void setEffect(EFFECTIDS EID, EFFECT_TIMINGS time, uint8_t repeatPeriod_sec, uint8_t repeatTimes)
			{
			this->m_EID						= EID;
			this->m_cfg_repeatTimes			= repeatTimes;
			this->m_cfg_repeatPeriod_sec	= repeatPeriod_sec;
			this->m_cfg_time				= time;
			
			this->m_secCounter				= this->m_cfg_repeatPeriod_sec;
			this->m_repeatTimes				= this->m_cfg_repeatTimes;
			}
		void cleanEffect(void)
			{
			this->m_EID						= EFFECTID_NONE;
			this->m_cfg_repeatTimes			= 0;
			this->m_cfg_repeatPeriod_sec	= 0;
			}
		EffectID_t getID(void)
			{
			return this->m_EID;
			}
		bool tick(void);//return true is should process effect. effects processing outside
	protected:
	private:
		EFFECTIDS m_EID;
		uint8_t m_cfg_repeatPeriod_sec;
		uint8_t m_cfg_repeatTimes;
		EFFECT_TIMINGS m_cfg_time;

		uint8_t m_repeatTimes;
		uint8_t m_secCounter;
	};
/*
class PlayerEffectsNGClass
	{
	public:
		class PlayerEffectsNGClassTask1: public Runnable
			{
			void Task (void);
			uint8_t getRepeatTime(void)
				{
				return TimerClass::TIME_1000MS;
				}
			} TaskPlayerEffectsNGOneSecondTick;
		const static uint8_t POOL_SIZE	= 32;

		//TODO: может случиться так, что ссылка на Expired эффект будет ссылаться на другой активный эффект
		PlayerEffectsDescriptor apply(PlayerEffectInstanceClass::EFFECTIDS EID, PlayerEffectInstanceClass::EFFECT_TIMINGS time, uint8_t repeatPeriod_sec, uint8_t repeatCounter);//returns link to a class or NULL
		bool remove(PlayerEffectsDescriptor effect);
		void oneSecondPassed(void);//every 1sec


		PlayerEffectInstanceClass pool[POOL_SIZE];
	protected:
	private:
		void tickEffect(uint8_t pool_idx);
	};
*/


#endif /* PLAYEREFFECTSNGCLASS_H_ */
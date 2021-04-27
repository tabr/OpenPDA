/*
 * AnomalySimpleClass.h
 *
 * Created: 21.09.2017 0:53:27
 *  Author: tabr
 */ 


#ifndef ANOMALYSIMPLECLASS_H_
#define ANOMALYSIMPLECLASS_H_

class AnomalySimpleClass //: public ITimerListener
	{
	public:
		void setLevelType_Filter (uint8_t level, AnomalyID_t AID, uint8_t skipLevel, uint8_t killLevel);
		void setLevelType_FilterNone(void);
		DamageSource_t getDamageSource(AnomalyID_t AID)
			{
			return DamageSource_t::DAMAGE_SOURCE_GENERIC;
			}
	};





#endif /* ANOMALYSIMPLECLASS_H_ */
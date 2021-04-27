/*
 * SimpleClasses.h
 *
 * Created: 20.09.2017 18:06:55
 *  Author: tabr
 */ 


#ifndef DUMMYCLASSES_H_
#define DUMMYCLASSES_H_

#include "PlayerEffectsInterface.hpp"
#include "RadiomarkClass.hpp"
#include "strings.h"

class PDAMenuDummyClass
	{
	public:
		void DeathScreen(void)
			{
			
			}
	protected:
	private:
	};
class SoundDummyClass
{
public:
  void stopSoundsPsy(void)  {};
protected:
private:
};
class PlayerEffect_NullEffectDummyClass : public PlayerEffects_Interface
	{
	public:
	void OnTick(void) {};
	void OnApply(void) {};
	void OnRemove(void) {};
	EffectID_t GetID(void) {return 0;};


  PE_CFG_t GetCFG(void)                       {return 0;};
  TimeSecond_t GetRepeatPeriodSec(void)       {return 0;};
  PE_RepeatTimes_t GetRepeatTimes(void)       {return 0;};
  bool IsVisible(void)                        {return false;};
  EffectName_t GetName(void)                  {return RAM_STR_UNDEFINED;};

	//PlayerEffect_NullEffectClass() : PlayerEffectsInterface(0, 0, 0){};
	protected:
	private:
	};
class EnvironmentDummyClass //: public ITimerListener
	{
	public:
	void RadLevelSetFilter(uint8_t value);
	void setPsyLevelFilter(uint8_t value);
	};
class QuestDummyClass
	{
	public:
		void FailQuest (uint8_t QID)
			{
			
			}
		void GiveQuest (uint8_t QID)
			{
			
			}
		void CompleteQuest(uint8_t QID)
			{
			
			}
		void RemoveQuest(uint8_t QID)
			{
			
			}
	};
#include "stalker/drivers/Interface_Driver_Clock.hpp"
class Driver_ClockDummy : public Interface_Driver_Clock
	{
	public:
		void SelectMaxExternal(void)
			{
			
			}
	//void Select_16x2_MHZExternal();
	protected:
	private:
	};
class EmissionInstanceDetectorDummyClass
{
public:
  void ProcessSignal(RadiomarkInstanceClass* selectedRadiomark){};
protected:
private:
};
///////////////////////



#endif /* DUMMYCLASSES_H_ */
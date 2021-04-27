#pragma once
#include "typedefs.h"
//#include "PlayerEffectsClass.hpp"
#include "Node.hpp"
enum PE_CFG //bit field
	{
	PE_CFG_TICK_INFINILTY_UNTIL_DIE,
	PE_CFG_INVISIBLE,
//	PE_CFG_UNTICKABLE,//do i deed it? Bacause i'll call check instead of call empty method
//	PE_CFG_,
	};
class PlayerEffects_Interface
	{
	public:
		virtual void OnTick(void)						                = 0;
		virtual void OnApply(void)						              = 0;
		virtual void OnRemove(void)						              = 0;
		virtual EffectID_t GetID(void)					            = 0;
		virtual PE_CFG_t GetCFG(void)                       = 0;
		virtual TimeSecond_t GetRepeatPeriodSec(void)       = 0;
		virtual PE_RepeatTimes_t GetRepeatTimes(void)       = 0;
		virtual bool IsVisible(void)                        = 0;
    virtual EffectName_t GetName(void)                  = 0;
//    virtual uint16_t GetRemainSeconds(void)             = 0;
    };
class PlayerEffectsStoragableClass : public PlayerEffects_Interface, public NodeExtended
	{
	public:
		virtual void OnTick(void)
      {
      }
		virtual void OnApply(void)
      {
      }
		virtual void OnRemove(void)
      {
      }
		virtual EffectID_t GetID(void)
      {
      //return PlayerEffectsClass::EFFECTIDS::EFFECTID_NO_ACTION;
      return this->EGUID;
      }
    virtual EffectName_t GetName(void)
      {
      return this->Name;
      }
		virtual PE_CFG_t GetCFG(void)
			{
			return this->m_CFG;
			}
		virtual TimeSecond_t GetRepeatPeriodSec(void)
			{
			return this->m_repeatPeriodSec;
			}
		virtual PE_RepeatTimes_t GetRepeatTimes(void)
			{
			return this->m_repeatTimes;
			}
		virtual bool IsVisible(void)
			{
//			return ((this->GetCFG() & PE_CFG::PE_CFG_INVISIBLE) == 0);
			return ((this->GetCFG() & PE_CFG_INVISIBLE) == 0);
			}
    /*virtual uint16_t GetRemainSeconds(void)
      {
      return 
      }*/

		PlayerEffectsStoragableClass();
		PlayerEffectsStoragableClass(PE_CFG_t tmpCFG,TimeSecond_t repeatPeriodSec, PE_RepeatTimes_t repeatTimes, PlayerEffectGUID_t EGUID=0, EffectName_t tmpName=NULL);
		void Clean(void);
	protected:
	private:
		PE_CFG_t m_CFG                  = 0;
		TimeSecond_t m_repeatPeriodSec  = 0;
		PE_RepeatTimes_t m_repeatTimes  = 0;
    PlayerEffectGUID_t EGUID        = 0;
    EffectName_t Name               = NULL;
//		StorageID_t m_StorageID=0;
		};

/*
class PlayerEffectsStorageClass : public NodeProcessorT<PlayerEffectsStoragableClass>
  {
  public:
  protected:
  private:
  };
*/
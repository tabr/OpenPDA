/*
 * RadiomarkClass.h
 *
 * Created: 28.01.2016 17:52:35
 *  Author: tabr
 */ 


#ifndef RADIOMARKCLASS_H_
#define RADIOMARKCLASS_H_
//#include "typedefs.h"
/*
RADIOMARK_TYPE_QUEST
1 - action (complete/fail/etc)
2 - Quest ID
3 - sensetivity threshold


*/
#include "stalker/TimerClass.hpp"

class RadiomarkInstanceClass : public NodeExtended
	{
	public:

		enum RADIOMARK_TYPE
			{
			RADIOMARK_TYPE_NONE,              //web
			RADIOMARK_TYPE_TIME,              //web
			RADIOMARK_TYPE_RADIATION_ANOMALY, //web
			RADIOMARK_TYPE_PSY,               //web
			RADIOMARK_TYPE_SAFE_ZONE,         //web
			RADIOMARK_TYPE_QUEST,             //web
			RADIOMARK_TYPE_TURRET,            //web
			RADIOMARK_TYPE_REVIVE,            //web
			RADIOMARK_TYPE_SAFE_SHELTER,      //web
			RADIOMARK_TYPE_ARTEFACT,          //web
			RADIOMARK_TYPE_GRENADE,           //new
			RADIOMARK_TYPE_GRAVEYARD,         //new
			RADIOMARK_TYPE_UNDERTAKER,        //new
			RADIOMARK_TYPE_MAGIC,             //new
			RADIOMARK_TYPE_DETECTOR,             //new
//			RADIOMARK_TYPE_ADM_ACTION,
			};
		
		RadiomarkID_t GetID(void);
		RadiomarkID_t GetType(void);
		RadiomarkParameter_t GetParameter1(void);
		RadiomarkParameter_t GetParameter2(void);
		RadiomarkParameter_t GetParameter3(void);
		RadiomarkParameter_t GetParameter4(void);
    void SetSignalPower(RM_SignalPower_t newSignalPower);
    RM_SignalPower_t GetSignalPower(void);
    Percent_t GetSignalPowerPercent(void);
		RadiomarkInstanceClass(void);
		RadiomarkInstanceClass(RadiomarkID_t RID, RadiomarkType_t RType, RadiomarkParameter_t RP1, RadiomarkParameter_t RP2, RadiomarkParameter_t RP3, RadiomarkParameter_t RP4);

		RadiomarkID_t RID             = 0;
		RadiomarkType_t RType         = 0;
		RadiomarkParameter_t RP1      = 0;
		RadiomarkParameter_t RP2      = 0;
		RadiomarkParameter_t RP3      = 0;
		RadiomarkParameter_t RP4      = 0;
    RM_SignalPower_t SignalPower  = 0;
	protected:
	private:
		//RadiomarkContainer_t m_container[R_PARAMETERS_NUM+1];
	};
//template <RadiomarkInstanceClass m_>
class RadiomarkRadiationAnomayClass
	{
	public:
    //const static uint8_t SIGNAL_TYPE_RADIATION  = 1<<0;
    //const static uint8_t SIGNAL_TYPE_ANOMALY    = 1<<1;

    void ProcessSignal(uint8_t signalPower);
    bool IsRadiationReceived(void);
    bool IsAnomalyReceived(void);
		RadiomarkParameter_t GetRadiationMultiplier(void)
			{
			return this->m_R->GetParameter1();
			}
		RadiomarkParameter_t GetAnomalyID(void)
			{
			return this->m_R->GetParameter2();
			}
		RadiomarkParameter_t GetAnomalySkipLevel(void)
			{
			return this->m_R->GetParameter3();
			}
		RadiomarkParameter_t GetAnomalyKillLevel(void)
			{
			return this->m_R->GetParameter4();
			}
		RadiomarkRadiationAnomayClass (RadiomarkInstanceClass* R)
			{
			this->m_R           = R;
      //this->typeOfSignal  = 0;
			}
	protected:
	private:
		RadiomarkInstanceClass* m_R;
    //uint8_t typeOfSignal;
	};
class RadiomarkQuestClass
	{
	public:
    void ProcessSignal(uint8_t signalPower);

		RadiomarkParameter_t GetQuestAction(void)
			{
			return this->m_R->GetParameter1();
			}
		RadiomarkParameter_t GetQuestID(void)
			{
			return this->m_R->GetParameter2();
			}
		RadiomarkParameter_t GetSensetivityThreshold(void)
			{
			return this->m_R->GetParameter3();
			}
		RadiomarkQuestClass (RadiomarkInstanceClass* R)
			{
			this->m_R	= R;
			}
	protected:
	private:
		RadiomarkInstanceClass* m_R;
	};
class RadiomarkPsyClass
	{
	public:
    void ProcessSignal(uint8_t signalPower);

		RadiomarkParameter_t GetPsyMultiplier(void)
			{
			return this->m_R->GetParameter1();
			}
		RadiomarkPsyClass (RadiomarkInstanceClass* R)
			{
			this->m_R	= R;
			}
	protected:
	private:
		RadiomarkInstanceClass* m_R;
	};

class RadiomarkGrenadeClass
	{
	public:
		RadiomarkParameter_t GetDamageMultiplier(void)
			{
			return this->m_R->GetParameter1();
			}
		RadiomarkParameter_t GetType(void)
			{
			return this->m_R->GetParameter2();
			}
		RadiomarkGrenadeClass (RadiomarkInstanceClass* R)
			{
			this->m_R	= R;
			}
	protected:
	private:
		RadiomarkInstanceClass* m_R;
	};

class EmissionInstanceDetectorClass : public ITimerListener//, public NodeExtended
  {
    //TODO
  public:
    void ProcessSignal(RadiomarkInstanceClass* selectedRadiomark);
    void TimerUpdateEvent (uint8_t msPassed);
    Percent_t GetSignalPowerPercent(void);
    uint8_t GetSignalID(void);
//    NodeProcessorID_t GetID(void)
//      {
//      return static_cast<NodeProcessorID_t>(this->RType);
//      }
//    EmissionInstanceClass(void)
//      {
//      this->RType = static_cast<RadiomarkInstanceClass::RADIOMARK_TYPE>(NULL);
//      }
//    EmissionInstanceClass(RadiomarkInstanceClass::RADIOMARK_TYPE ERType)
//      {
//      this->RType = ERType;
//      }
  protected:
  private:
//    RadiomarkInstanceClass::RADIOMARK_TYPE RType;
   	uint8_t msCounter                 = 0;
    bool signalArrived                = false;
    uint8_t storedSignalPowerPercent  = 0;
    uint8_t signalID                  = 0;
  };

#endif /* RADIOMARKCLASS_H_ */
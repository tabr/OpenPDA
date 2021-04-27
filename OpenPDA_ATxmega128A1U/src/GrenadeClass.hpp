/*
 * GrenadeClass.h
 *
 * Created: 24.12.2017 1:53:50
 *  Author: tabr
 */ 


#ifndef GRENADECLASS_H_
#define GRENADECLASS_H_

class GrenadeClass : public ITimerListener
  {
  public:
    enum GRENADE_TYPES {
      GRENADE_TYPE_GENERIC,
      GRENADE_TYPE_PLASMA,
      };
    void TimerUpdateEvent (uint8_t msPassed);
    void ProcessSignal(uint8_t signalPower);
  protected:
  private:
    uint8_t delayHackTimer=0;
  };



#endif /* GRENADECLASS_H_ */
#ifndef  BACKLIGHT_CLASS_H
#define  BACKLIGHT_CLASS_H
class  BackLightClass : public ITimerListener
  {
  public:
  void TimerUpdateEvent (uint8_t msPassed);
  void  turnONFor5sec(void);
  void  turnON(void);
  void  turnOFF(void);
  void  IOInit(void);
  void  DefaultState(void);
  bool  isBacklightONInverted(void);
  protected:
  private:
    uint8_t  turnOnTimer=0;
  };
#endif
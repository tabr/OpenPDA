/*
 * TimeUpdateClass.h
 *
 * Created: 24.12.2017 1:34:35
 *  Author: tabr
 */ 


#ifndef TIMEUPDATECLASS_H_
#define TIMEUPDATECLASS_H_

class TimeUpdateClass : public ITimerListener
  {
  public:
    const static TimeUpdate_t TIMER_RELOAD_VALUE  = 255;

    void TimerUpdateEvent (uint8_t msPassed);
    void RequestUpdate (TimeHour_t h, TimeMinute_t m, TimeSecond_t s);
    bool IsTimeSyncReceivedAtLastOnce(void);
  protected:
  private:
    TimeUpdate_t updateTimer=0;
    #ifdef TIMESYNC_BYPASS
      bool timeSyncReceivedAtLastOnce=true;
    #else
      bool timeSyncReceivedAtLastOnce=false;
    #endif //TIMESYNC_BYPASS
  };



#endif /* TIMEUPDATECLASS_H_ */
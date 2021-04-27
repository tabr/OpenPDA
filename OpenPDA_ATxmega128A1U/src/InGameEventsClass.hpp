/*
  *  InGameEventsClass.h
  *
  *  Created:  2015-10-15  22:43:41
  *    Author:  tabr
  */  


#ifndef INGAMEEVENTSCLASS_H_
#define INGAMEEVENTSCLASS_H_

#include <stdint.h>
#include <stddef.h>
#include <avr/io.h>

typedef uint8_t EventsPeriod_t;
typedef uint8_t EventsParemeter_t;
typedef uint8_t EventID_t;

#define EVENT_PERIOD_ONE_SEC  1

class InGameEventsClass : public ITimerListener
  {
  public:
    const static uint8_t POOL_SIZE = 16;
    enum  PARAMETERS
      {
      PARAMETER_PERIOD,
      PARAMETER_START_H,
      PARAMETER_START_M,
      PARAMETER_END_H,
      PARAMETER_END_M,
      PARAMETERS_NUM
      };
    enum EVENT_STATE
      {
      EVENT_STATE_INACTIVE,
      EVENT_STATE_ACTIVE,
      };
    enum IN_GAME_EVENT_TEMPLATE
      {
      IN_GAME_EVENT_NONE,      //web
      IN_GAME_EVENT_BLOWOUT,    //web
      IN_GAME_EVENT_SLEEPTIME,  //web
      IN_GAME_EVENT_SIZE      //web
      };

    void TimerUpdateEvent (uint8_t  msPassed);
    void checkState(void);
    void setState(EventID_t EID, EVENT_STATE s);
    EVENT_STATE getState(EventID_t EID);
    bool isEventTimeArrived(EventID_t EID);
    EventID_t registerNew(uint8_t startH, uint8_t startM, uint8_t endH, uint8_t endM, EventsPeriod_t periodSec, Runnable& callback);
//    InGameEventsClass(void);
    EventsPeriod_t* getParameters(EventID_t EID);
  protected:
  private:
  class InGameEventPoolStruct
    {
    public:
      Runnable* callback = nullptr;
      EVENT_STATE state = EVENT_STATE_INACTIVE;
      EventsPeriod_t periodCounter = 0;
      EventsParemeter_t parameters[PARAMETERS_NUM];
      void ReInit(void)
        {
        this->periodCounter	= this->parameters[PARAMETER_PERIOD];
        }
      InGameEventPoolStruct(void)
        {
        memset(this->parameters, 0, sizeof(this->parameters));
        }
    protected:
    private:
    };
  InGameEventPoolStruct pool[POOL_SIZE];
    /*
  #warning "make one struct"
    Runnable*  pool[POOL_SIZE];
    EVENT_STATE  state[POOL_SIZE];
    EventsPeriod_t  period[POOL_SIZE];
//    void*  pool[POOL_SIZE][PARAMETERS_NUM];
    EventsParemeter_t  parameters[POOL_SIZE][PARAMETERS_NUM];
    */
    uint8_t registered=0;
  };


#endif  /*  INGAMEEVENTSCLASS_H_  */

/*
  *  GameEvent_SleepTimeClass.h
  *
  *  Created:  02.05.2016  14:46:15
  *    Author:  tabr
  */  


#ifndef  INGAMEEVENT_SLEEPTIMECLASS_H_
#define  INGAMEEVENT_SLEEPTIMECLASS_H_


class  InGameEvent_SleepTimeClass : public Runnable
  {
  public:
    void  Task  (void);
    uint8_t  getRepeatTime(void)
      {
      return  0;
      }
  protected:
  private:
  };


#endif  /*  INGAMEEVENT_SLEEPTIMECLASS_H_  */

/*
  *  InGameEvent_RadStormClass.h
  *
  *  Created:  27.09.2017  2:59:03
  *    Author:  tabr
  */  


#ifndef  INGAMEEVENT_RADSTORMCLASS_H_
#define  INGAMEEVENT_RADSTORMCLASS_H_


class  InGameEvent_RadStormClass : public Runnable
  {
  public:
    void  Task  (void);
    uint8_t  getRepeatTime(void)
      {
      return  0;
      }
  protected:
  private:
  uint8_t  RadStormSoundTimer  =  0;
  };



#endif  /*  INGAMEEVENT_RADSTORMCLASS_H_  */

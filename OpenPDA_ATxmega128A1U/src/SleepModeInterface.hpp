/*
  *  SleepModeInterface.h
  *
  *  Created:  21.02.2016  4:40:04
  *    Author:  tabr
  */  


#ifndef  SLEEPMODEINTERFACE_H_
#define  SLEEPMODEINTERFACE_H_


class  SleepModeInterface
  {
  public:
    virtual  void  EnterSleepMode(void)=0;
    virtual  void  EnterNormalMode(void)=0;
  protected:
  private:
  };


#endif  /*  SLEEPMODEINTERFACE_H_  */

/*
  *  BlowoutEventClass.h
  *
  *  Created:  25.10.2015  23:14:28
  *    Author:  tabr
  */  


#ifndef  INGAMEEVENT_BLOWOUTCLASS_H_
#define  INGAMEEVENT_BLOWOUTCLASS_H_

#include  <stdint.h>
#include  <stddef.h>
#include  <avr/io.h>

//#include  "TemporaryClass.h"
//#include  "PlayerSkillsClass.h"
//#include  "PlayerClass.h"

//extern  PlayerClass  Player;

class  InGameEvent_BlowoutClass : public Runnable
  {
  public:
    void  Task  (void);
    uint8_t  getRepeatTime(void)
      {
      return  0;
      }
  protected:
  private:
  uint8_t  BlowoutSoundTimer  =  0;
  };
class  InGameEvent_BlowoutPrepareClass : public Runnable
{
	public:
	void  Task  (void);
	uint8_t  getRepeatTime(void)
	{
		return  0;
	}
	protected:
	private:
	uint8_t  BlowoutSoundTimer  =  0xFF;
};



#endif  /*  INGAMEEVENT_BLOWOUTCLASS_H_  */

#ifndef  VIBRO_CLASS_H
#define  VIBRO_CLASS_H
/*
Вибромотор

*/
//using  namespace  IO;

#include  <stdint.h>
#include  <stddef.h>
#include  <avr/io.h>

#include  "boards/pcb_1.h"
#include  "stalker/TimerClass.hpp"

class  VibroClass : public ITimerListener
  {
  public:
    void TimerUpdateEvent (uint8_t msPassed);

    void updateState(void);
    void activate(uint8_t  ticks40ms);
    void deactivate(void);
    void IOInit(void);
    VibroClass(void);

  protected:
  private:
    uint8_t  timer  =  0;
  };
#endif
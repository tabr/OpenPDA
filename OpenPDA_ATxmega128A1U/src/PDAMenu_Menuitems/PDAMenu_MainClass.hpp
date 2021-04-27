/*
  *  PDAMenu_MainClass.h
  *
  *  Created:  27.04.2017  1:51:37
  *    Author:  tabr
  */  


#ifndef PDAMENU_MAINCLASS_H_
#define PDAMENU_MAINCLASS_H_

#include "EventSystemClass.hpp"

class PDAMenu_MainClass : public PDAMenu_MainInterface, public EventArrivedInterface
  {
  public:
    void Update(uint8_t msPassed);
    void EventArrived(EventSystemSpace::EVIDS evID, void* parameters);
    
    void JustSelected(void);
    PDAMenu_MainInterface::MENUIDS getID(void);
    void buttonPressed(ButtonsClass::BUTTONS btn);
    void ChargeStateChanged(PowerManagerClass::CHARGE_STATES state);
    PDAMenu_MainClass(void);
  protected:
  private:
    uint16_t timerUpdate = 0;
    static const uint16_t TIMER_UPDATE_VALUE  = 1000;
    //#ifndef  DEBUG_BUILD
      //uint8_t  chargeDotsRest  =  0;
      //LcdPixelMode  mode    =  PIXEL_ON;
      //uint8_t  prevDots    =  0;
    //#endif
  };




#endif  /*  PDAMENU_MAINCLASS_H_  */

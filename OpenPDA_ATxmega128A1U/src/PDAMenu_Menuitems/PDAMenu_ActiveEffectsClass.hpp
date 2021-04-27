/*
  *  PDAMenu_ActiveEffectsClass.h
  *
  *  Created:  27.04.2017  2:03:24
  *    Author:  tabr
  */  


#ifndef  PDAMENU_ACTIVEEFFECTSCLASS_H_
#define  PDAMENU_ACTIVEEFFECTSCLASS_H_

class  PDAMenu_ActiveEffectsClass : public PDAMenu_MainInterface
  {
  public:
    void  Update(uint8_t  msPassed);
    void  JustSelected(void);
    PDAMenu_MainInterface::MENUIDS  getID(void);
    void  buttonPressed(ButtonsClass::BUTTONS  btn);
  protected:
  private:
    uint8_t  scroll=0;
    uint16_t  updateCounter=0;
  };




#endif  /*  PDAMENU_ACTIVEEFFECTSCLASS_H_  */

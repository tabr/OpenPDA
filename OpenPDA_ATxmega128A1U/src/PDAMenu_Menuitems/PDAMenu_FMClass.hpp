/*
  *  PDAMenu_FMClass.h
  *
  *  Created:  27.04.2017  2:05:21
  *    Author:  tabr
  */  


#ifndef  PDAMENU_FMCLASS_H_
#define  PDAMENU_FMCLASS_H_


class  PDAMenu_FMClass : public PDAMenu_MainInterface
  {
  public:
    void  Update(uint8_t  msPassed);
    void  JustSelected(void);
    PDAMenu_MainInterface::MENUIDS  getID(void);
    void  buttonPressed(ButtonsClass::BUTTONS  btn);
  protected:
  private:
    uint8_t  freqencyDiff=0;
    uint16_t  updateCounter=0;
  };



#endif  /*  PDAMENU_FMCLASS_H_  */

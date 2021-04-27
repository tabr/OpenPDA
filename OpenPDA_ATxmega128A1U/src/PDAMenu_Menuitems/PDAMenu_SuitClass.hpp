/*
  *  PDAMenuSuitClass.h
  *
  *  Created:  27.04.2017  1:56:17
  *    Author:  tabr
  */  


#ifndef  PDAMENU_SUITCLASS_H_
#define  PDAMENU_SUITCLASS_H_


class  PDAMenu_SuitClass : public PDAMenu_MainInterface
  {
  public:
    void  Update(uint8_t  msPassed);
    void  JustSelected(void);
    PDAMenu_MainInterface::MENUIDS  getID(void);
    void  buttonPressed(ButtonsClass::BUTTONS  btn);
  protected:
  private:
  };



#endif  /*  PDAMENU_SUITCLASS_H_  */

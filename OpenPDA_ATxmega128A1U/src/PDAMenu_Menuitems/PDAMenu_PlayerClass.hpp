/*
  *  PDAMenuPlayerClass.h
  *
  *  Created:  27.04.2017  1:56:43
  *    Author:  tabr
  */  


#ifndef  PDAMENU_PLAYERCLASS_H_
#define  PDAMENU_PLAYERCLASS_H_


class  PDAMenu_PlayerInfoClass : public PDAMenu_MainInterface
  {
  public:
    void  Update(uint8_t  msPassed);
    void  JustSelected(void);
    PDAMenu_MainInterface::MENUIDS  getID(void);
    void  buttonPressed(ButtonsClass::BUTTONS  btn);
  protected:
  private:
  };



#endif  /*  PDAMENU_PLAYERCLASS_H_  */

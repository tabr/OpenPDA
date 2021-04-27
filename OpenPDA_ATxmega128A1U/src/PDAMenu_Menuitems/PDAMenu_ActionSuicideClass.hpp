/*
  *  PDAMenuActionSuicideClass.h
  *
  *  Created:  27.04.2017  1:55:13
  *    Author:  tabr
  */  


#ifndef  PDAMENU_ACTIONSUICIDECLASS_H_
#define  PDAMENU_ACTIONSUICIDECLASS_H_

class  PDAMenu_ActionSuicideClass : public PDAMenu_MainInterface
  {
  public:
    void  Update(uint8_t  msPassed);
    void  JustSelected(void);
    PDAMenu_MainInterface::MENUIDS  getID(void);
    void  buttonPressed(ButtonsClass::BUTTONS  btn);
    bool  isUsable()
      {
      return  true;
      }
  protected:
  private:
  };




#endif  /*  PDAMENU_ACTIONSUICIDECLASS_H_  */

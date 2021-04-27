/*
  *  PDAMenu_ArtefactsConnectedClass.h
  *
  *  Created:  27.04.2017  1:52:44
  *    Author:  tabr
  */  


#ifndef  PDAMENU_ARTEFACTSCONNECTEDCLASS_H_
#define  PDAMENU_ARTEFACTSCONNECTEDCLASS_H_


class  PDAMenu_ArtefactsConnectedClass : public PDAMenu_MainInterface
  {
  public:
    void  Update(uint8_t  msPassed);
    void  JustSelected(void);
    PDAMenu_MainInterface::MENUIDS  getID(void);
    void  buttonPressed(ButtonsClass::BUTTONS  btn){}
  protected:
  private:
  };



#endif  /*  PDAMENU_ARTEFACTSCONNECTEDCLASS_H_  */

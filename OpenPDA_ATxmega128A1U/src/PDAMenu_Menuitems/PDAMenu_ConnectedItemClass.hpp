/*
  *  PDAMenu_ConnectedItemClass.h
  *
  *  Created:  27.04.2017  1:53:29
  *    Author:  tabr
  */  


#ifndef  PDAMENU_CONNECTEDITEMCLASS_H_
#define  PDAMENU_CONNECTEDITEMCLASS_H_



class  PDAMenu_ConnectedItemClass : public PDAMenu_MainInterface
  {
  public:
    void  Update(uint8_t  msPassed);
    void  JustSelected(void);
    PDAMenu_MainInterface::MENUIDS  getID(void);
    void  buttonPressed(ButtonsClass::BUTTONS  btn);
    void  itemJustConnectedOrDisconnected(UsableItemClass::CONNECTION_STATE  state);
    bool  isUsable(void)
      {
      return  true;
      }
  protected:
  private:
    uint16_t  timerUpdate=0;
  };



#endif  /*  PDAMENU_CONNECTEDITEMCLASS_H_  */

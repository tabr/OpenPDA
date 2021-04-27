/*
  *  PDAMenu_ComputerHackClass.h
  *
  *  Created:  27.04.2017  2:02:51
  *    Author:  tabr
  */  


#ifndef  PDAMENU_COMPUTERHACKCLASS_H_
#define  PDAMENU_COMPUTERHACKCLASS_H_


class  PDAMenu_ComputerHackClass : public PDAMenu_MainInterface
  {
  public:
    void  Update(uint8_t  msPassed);
    void  JustSelected(void);
    PDAMenu_MainInterface::MENUIDS  getID(void);
    void  buttonPressed(ButtonsClass::BUTTONS  btn);
  protected:
  private:
    uint8_t  selectedAction=0;
    uint8_t  connectedComputerStatus=0;
    uint8_t  connectedComputerLevel=0;
    uint16_t  updateCounter=0;
  };



#endif  /*  PDAMENU_COMPUTERHACKCLASS_H_  */

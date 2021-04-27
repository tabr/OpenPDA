/*
  *  PDAMenu_QuestsClass.h
  *
  *  Created:  27.04.2017  1:54:28
  *    Author:  tabr
  */  


#ifndef  PDAMENU_QUESTSCLASS_H_
#define  PDAMENU_QUESTSCLASS_H_


class  PDAMenu_QuestsClass : public PDAMenu_MainInterface
  {
  public:
    void  Update(uint8_t  msPassed);
    void  JustSelected(void);
    PDAMenu_MainInterface::MENUIDS  getID(void);
    void  buttonPressed(ButtonsClass::BUTTONS  btn);
  protected:
  private:
    uint8_t  selectedQuest  =  0;
    uint16_t  updateCounter  =  0;
  };



#endif  /*  PDAMENU_QUESTSCLASS_H_  */

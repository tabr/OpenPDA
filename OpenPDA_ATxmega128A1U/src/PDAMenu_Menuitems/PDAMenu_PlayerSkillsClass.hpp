/*
  *  PDAMenu_PlayerSkillsClass.h
  *
  *  Created:  27.04.2017  2:02:18
  *    Author:  tabr
  */  


#ifndef  PDAMENU_PLAYERSKILLSCLASS_H_
#define  PDAMENU_PLAYERSKILLSCLASS_H_


class  PDAMenu_PlayerSkillsClass : public PDAMenu_MainInterface
  {
  public:
    void  Update(uint8_t  msPassed);
    void  JustSelected(void);
    PDAMenu_MainInterface::MENUIDS  getID(void);
    void  buttonPressed(ButtonsClass::BUTTONS  btn);
  protected:
  private:
    uint8_t  scroll=0;
  };



#endif  /*  PDAMENU_PLAYERSKILLSCLASS_H_  */

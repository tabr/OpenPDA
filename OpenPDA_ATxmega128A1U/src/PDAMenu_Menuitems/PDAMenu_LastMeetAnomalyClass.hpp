/*
  *  PDAMenuLastMeetAnomalyClass.h
  *
  *  Created:  27.04.2017  1:55:47
  *    Author:  tabr
  */  


#ifndef  PDAMENU_LASTMEETANOMALYCLASS_H_
#define  PDAMENU_LASTMEETANOMALYCLASS_H_


class  PDAMenu_LastMeetAnomalyClass : public PDAMenu_MainInterface
  {
  public:
    void  Update(uint8_t  msPassed);
    void  JustSelected(void);
    PDAMenu_MainInterface::MENUIDS  getID(void);
    void  buttonPressed(ButtonsClass::BUTTONS  btn);
  protected:
  private:
    //uint8_t  specs  =  1;  
  };



#endif  /*  PDAMENU_LASTMEETANOMALYCLASS_H_  */

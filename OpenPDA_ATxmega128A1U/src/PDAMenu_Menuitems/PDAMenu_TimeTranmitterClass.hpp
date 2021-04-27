/*
  *  PDAMenu_TimeTranmitterClass.h
  *
  *  Created:  27.04.2017  2:04:44
  *    Author:  tabr
  */  


#ifndef  PDAMENU_TIMETRANMITTERCLASS_H_
#define  PDAMENU_TIMETRANMITTERCLASS_H_


class  PDAMenu_TimeTranmitterClass : public PDAMenu_MainInterface
  {
  public:
    void  Update(uint8_t  msPassed);
    void  JustSelected(void);
    PDAMenu_MainInterface::MENUIDS  getID(void);
    void  buttonPressed(ButtonsClass::BUTTONS  btn);
  protected:
  private:
    uint8_t  scroll=0;
    uint16_t  updateCounter=0;
//    TimeClass  time;
    uint8_t  position=0;
    bool  txOn=false;
    bool  hackFirstTxPass=false;
  };



#endif  /*  PDAMENU_TIMETRANMITTERCLASS_H_  */

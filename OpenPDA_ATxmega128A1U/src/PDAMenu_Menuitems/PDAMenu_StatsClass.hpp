/*
  *  PDAMenuStatsClass.h
  *
  *  Created:  27.04.2017  2:01:46
  *    Author:  tabr
  */  


#ifndef  PDAMENU_STATSCLASS_H_
#define  PDAMENU_STATSCLASS_H_

class  PDAMenu_StatsClass : public PDAMenu_MainInterface
  {
  public:
    void  Update(uint8_t  msPassed);
    void  JustSelected(void);
    PDAMenu_MainInterface::MENUIDS  getID(void);
    void  buttonPressed(ButtonsClass::BUTTONS  btn);
    bool  isScrollable(void)
      {
      return  true;
      }
  protected:
  private:
    uint8_t  scroll=0;
    uint16_t  updateCounter=0;
  };




#endif  /*  PDAMENU_STATSCLASS_H_  */

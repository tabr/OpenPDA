/*
  *  PDAMenu_MASTERClass.h
  *
  *  Created:  27.04.2017  2:07:21
  *    Author:  tabr
  */  


#ifndef  PDAMENU_MASTERCLASS_H_
#define  PDAMENU_MASTERCLASS_H_


class  PDAMenu_MASTER_ItemClass : public PDAMenu_MainInterface
  {
  public:
    void  Update(uint8_t  msPassed);
    void  JustSelected(void);
    PDAMenu_MainInterface::MENUIDS  getID(void);
    void  buttonPressed(ButtonsClass::BUTTONS  btn);
    bool  isSelectable(void)
      {
      return  true;
      }
    bool  isUsable(void)
      {
      return  false;
      }
  protected:
  private:
    uint8_t  changeSubject=0;
//    ArtefactID_t  art_mod=0;
  };



#endif  /*  PDAMENU_MASTERCLASS_H_  */

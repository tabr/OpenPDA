/*
  *  PDAMenu_MASTER_ArtefactClass.h
  *
  *  Created:  24.09.2017  3:14:58
  *    Author:  tabr
  */  


#ifndef  PDAMENU_MASTER_ARTEFACTCLASS_H_
#define  PDAMENU_MASTER_ARTEFACTCLASS_H_

class  PDAMenu_MASTER_ArtefactClass : public PDAMenu_MainInterface
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
    ArtefactID_t  art_mod=0;
  };



#endif  /*  PDAMENU_MASTER_ARTEFACTCLASS_H_  */

/*
  *  PDAMenu_UndertakerClass.h
  *
  *  Created:  27.09.2017  12:54:15
  *    Author:  tabr
  */  


#ifndef  PDAMENU_UNDERTAKERCLASS_H_
#define  PDAMENU_UNDERTAKERCLASS_H_


class  PDAMenu_UndertakerClass : public PDAMenu_MainInterface
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
    uint8_t  position=0;
    uint8_t  PDANum=0;
    bool  txOn  =  false;
    bool  hackFirstTxPass  =  false;
    uint16_t  updateCounter=0;
    
  };


#endif  /*  PDAMENU_UNDERTAKERCLASS_H_  */

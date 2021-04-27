#ifndef  PDAMENU_MAGICCLASS_H_
#define  PDAMENU_MAGICCLASS_H_


class  PDAMenu_MagicClass : public PDAMenu_MainInterface
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


#endif  /*  PDAMENU_MAGICCLASS_H_  */

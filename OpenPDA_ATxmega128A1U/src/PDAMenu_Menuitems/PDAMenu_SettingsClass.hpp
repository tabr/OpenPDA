/*
  *  PDAMenu_SettingsClass.h
  *
  *  Created:  27.04.2017  1:57:17
  *    Author:  tabr
  */  


#ifndef  PDAMENU_SETTINGSCLASS_H_
#define  PDAMENU_SETTINGSCLASS_H_


class  PDAMenu_SettingsClass : public PDAMenu_MainInterface
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
      return  true;
      }
    PDAMenu_SettingsClass(void)
      {
      this->selectedSettings  =  0;
      }
  protected:
  private:
    uint8_t  selectedSettings;
  };



#endif  /*  PDAMENU_SETTINGSCLASS_H_  */

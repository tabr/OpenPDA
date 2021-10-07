/*
  *  PDAMenu_MainInterface.h
  *
  *  Created:  2015-08-03  11:37:02
  *    Author:  tabr
  */  


#ifndef  PDAMENU_MAININTERFACE_H_
#define  PDAMENU_MAININTERFACE_H_

#include  "Buttons.hpp"
#include  "boards/compiler_defines.h"

#warning "[T] Cleanup this virtual/pure virtual garbage, learn 'virtual'"
class  PDAMenu_MainInterface
  {
  public:
    enum  MENU_SPECS_BIT
      {
      MENU_SPECS_BIT__BUTTON_INTERCEPTION,
      };
    #warning "[T] comment it!"
    enum  MENUIDS
    {
      MENUID_MAIN,
      MENUID_ARTEFACTS_CONNECTED,
      MENUID_CONNECTED_ITEM,
      MENUID_QUESTS,
      MENUID_ACTIONS,
      MENUID_ACTION_SUICIDE,
      MENUID_STATS,
      MENUID_LAST_MEET_ANOMALY,
      MENUID_SUIT,
      MENUID_PLAYER_INFO,
      MENUID_SETTINGS,
      MENUID_SKILLS,
      MENUID_COMPUTER_HACK,
      MENUID_ACTIVE_EFFECTS,
      MENUID_SIGNAL_SCANNER,
      MENUID_ANOMALY_SCANNER,
//      MENUID_,
      //      MENUID_SPECS,
      MENUID_NUM,
      
      MENUID_UNDEFINED,
      MENUID_SELECT_NEXT,
      MENUID_SELECT_PREV
    };
//      virtual  void  Select(void);
    virtual  void  Update(uint8_t  msPassed);
    virtual  void  JustSelected(void);
    virtual  PDAMenu_MainInterface::MENUIDS  getID(void);
    bool  hasSubmenu(void);
    void  InsertBefore(PDAMenu_MainInterface*  item);
    void  insertAfterThis(PDAMenu_MainInterface*  item);
    virtual  void  buttonPressed(ButtonsClass::BUTTONS  btn);
    virtual  bool  isScrollable(void);
    virtual  bool  isUsable(void);
    virtual  bool  isSelectable(void);
    virtual  uint8_t  getSpecs(void);
    void  addSubMenu(PDAMenu_MainInterface*  item);
    PDAMenu_MainInterface*  GetPrev(void);
    PDAMenu_MainInterface(void);
    bool  hasParent(void)
      {
      return  this->GetParentMenu()  !=  NULL;
      }
    PDAMenu_MainInterface* GetParentMenu(void)
      {
      return this->parentMenu;
      }
    void SetParentMenu(PDAMenu_MainInterface* m)
      {
      this->parentMenu  = m;
      }

    void SetSelectedSubMenu(PDAMenu_MainInterface* m)
      {
      this->selectedSubMenu  = m;
      }
    PDAMenu_MainInterface* GetSelectedSubMenu(void)
      {
      return this->selectedSubMenu;
      }

    void SetNext(PDAMenu_MainInterface* m)
      {
      this->next  = m;
      }
    PDAMenu_MainInterface* GetNext(void)
      {
      return this->next;
      }

    bool  hasSpecs(void);
    bool  hasSpec(uint8_t  s);
  protected:
  private:
    PDAMenu_MainInterface*  parentMenu;
    PDAMenu_MainInterface*  next;
    PDAMenu_MainInterface*  selectedSubMenu;
  };
class  PDAMenuDummyClass : public PDAMenu_MainInterface
  {
  public:
    void  Update(uint8_t  msPassed){}
    void  JustSelected(void){}
    PDAMenu_MainInterface::MENUIDS  getID(void){return  PDAMenu_MainInterface::MENUIDS::MENUID_UNDEFINED;}
    void  buttonPressed(ButtonsClass::BUTTONS  btn){}
  protected:
  private:
  };


#endif  /*  PDAMENU_MAININTERFACE_H_  */

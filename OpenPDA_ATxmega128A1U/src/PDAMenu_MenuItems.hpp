/*
  *  PDAMenu_MenuItems.h
  *
  *  Created:  2015-08-03  11:39:34
  *    Author:  tabr
  */  


#ifndef  PDAMENU_MENUITEMS_H_
#define  PDAMENU_MENUITEMS_H_

#include  "boards/compiler_defines.h"
#include  "Buttons.hpp"
#include  "n3310_new.h"
#include  <TimeClass.hpp>
#include  "UsableItemClass.hpp"
#include  "PowerManager.hpp"
//#include  "pdamenu.h"

/*class  PDAMenuActionsClass : public PDAMenu_MainInterface
  {
  public:
    void  Update(void);
    void  JustSelected(void);
    uint8_t  getID(void);
    void  buttonPressed(ButtonsClass::BUTTONS  btn);
  protected:
  private:
  };*/
#include  "PDAMenu_Menuitems\PDAMenu_MainClass.hpp"
#include  "PDAMenu_Menuitems\PDAMenu_ArtefactsConnectedClass.hpp"
#include  "PDAMenu_Menuitems\PDAMenu_ConnectedItemClass.hpp"
#include  "PDAMenu_Menuitems\PDAMenu_QuestsClass.hpp"
#include  "PDAMenu_Menuitems\PDAMenu_ActionSuicideClass.hpp"
#include  "PDAMenu_Menuitems\PDAMenu_LastMeetAnomalyClass.hpp"
#include  "PDAMenu_Menuitems\PDAMenu_SuitClass.hpp"
#include  "PDAMenu_Menuitems\PDAMenu_PlayerClass.hpp"
#include  "PDAMenu_Menuitems\PDAMenu_SettingsClass.hpp"
#include  "PDAMenu_Menuitems\PDAMenu_StatsClass.hpp"
#include  "PDAMenu_Menuitems\PDAMenu_PlayerSkillsClass.hpp"
#include  "PDAMenu_Menuitems\PDAMenu_ComputerHackClass.hpp"
#include  "PDAMenu_Menuitems\PDAMenu_ActiveEffectsClass.hpp"
#include  "PDAMenu_Menuitems\PDAMenu_DebugClass.hpp"
#include  "PDAMenu_Menuitems\PDAMenu_TimeTranmitterClass.hpp"
#include  "PDAMenu_Menuitems\PDAMenu_FMClass.hpp"
#include  "PDAMenu_Menuitems\PDAMenu_GameSnakeClass.hpp"
#include  "PDAMenu_Menuitems\PDAMenu_GamesClass.hpp"
#include  "PDAMenu_Menuitems\PDAMenu_MASTER_ItemClass.hpp"
#include  "PDAMenu_Menuitems\PDAMenu_MASTER_ArtefactClass.hpp"
#include  "PDAMenu_Menuitems\PDAMenu_MASTER_ReviveActionClass.hpp"
#include  "PDAMenu_Menuitems\PDAMenu_UndertakerClass.hpp"
#include  "PDAMenu_Menuitems\PDAMenu_MagicClass.hpp"
#include  "PDAMenu_Menuitems\PDAMenu_SignalScannerClass.hpp"





#endif  /*  PDAMENU_MENUITEMS_H_  */

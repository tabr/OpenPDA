#ifndef GAME_TAMPLE_PDAMENU_H
#define GAME_TAMPLE_PDAMENU_H

//PDAMenu.SetDefaultMenu(&PDAMenu.PDAMenu_Main);




PDAMenu_MainInterface* Menu = &(PDAMenu.PDAMenu_Main);
//PDAMenu_MainInterface* Menu = new PDAMenu_MainClass;
//PDAMenu_MainInterface* PDAMenu_Dummy0 = new PDAMenuDummyClass;

//PDAMenu.SetDefaultMenu(Menu);
//Menu->InsertBefore(PDAMenu_Dummy0);
PDASettings.setParameter(ConfigClass::SETTINGS_NIGHT_MODE);//hack
Menu->InsertBefore(new PDAMenu_SignalScannerClass(1, 1,7,8,2,3,9));
Menu->InsertBefore(new PDAMenu_SignalScannerClass(2, 2,8,9,3,4,0));
Menu->InsertBefore(new PDAMenu_SignalScannerClass(3, 3,9,0,4,5,6));
//Menu->InsertBefore(new PDAMenu_ConnectedItemClass);
//Menu->InsertBefore(new PDAMenu_ActiveEffectsClass);

//PDAMenu.PDAMenu_Main.InsertBefore(&PDAMenu.PDAMenu_ArtefactsConnected);

//Menu->InsertBefore(new PDAMenu_QuestsClass);
//Menu->InsertBefore(new PDAMenu_Dummy1Class);
//Menu->InsertBefore(new PDAMenu_ComputerHackClass);  --DISABLED
//Menu->InsertBefore(new PDAMenu_SettingsClass);
Menu->InsertBefore(new PDAMenu_GamesClass);
//Menu->InsertBefore(new PDAMenu_UndertakerClass);
//Menu->InsertBefore(new PDAMenu_ActionSuicideClass);
#ifdef MASTER_PDA
  {
  Menu->InsertBefore(new PDAMenu_DebugClass);
  Menu->InsertBefore(new PDAMenu_TimeTranmitterClass);
//  Menu->InsertBefore(new PDAMenu_FMClass);
  Menu->InsertBefore(new PDAMenu_MASTER_ItemClass);
  Menu->InsertBefore(new PDAMenu_MASTER_ArtefactClass);
//  Menu->InsertBefore(new PDAMenu_MASTER_ArtefactClass);
  Menu->InsertBefore(new PDAMenu_MASTER_ReviveActionClass);
  Menu->InsertBefore(new PDAMenu_MagicClass);
  }
#endif // MASTER_PDA

//PDAMenu.PDAMenu_Dummy0.insertAfterThis(new PDAMenu_ArtefactsConnectedClass);

//PDAMenu.PDAMenu_ArtefactsConnected.insertAfterThis(new PDAMenu_ConnectedItemClass);
//PDAMenu.PDAMenu_ConnectedItem.insertAfterThis(new PDAMenu_QuestsClass);
////PDAMenu.PDAMenu_Quests.insertAfterThis(new PDAMenu_ActionsClass);
//PDAMenu.PDAMenu_Quests.insertAfterThis(new PDAMenu_Dummy1Class);
//PDAMenu.PDAMenu_Dummy1.insertAfterThis(new PDAMenu_SettingsClass);

//PDAMenu_Dummy0->addSubMenu(new PDAMenu_StatsClass);
//PDAMenu_Dummy0addSubMenu(new PDAMenu_ActiveEffectsClass);
//PDAMenu_Dummy0->addSubMenu(new PDAMenu_LastMeetAnomalyClass);
//PDAMenu_Dummy0->addSubMenu(new PDAMenu_SuitClass);
//PDAMenu_Dummy0->addSubMenu(new PDAMenu_PlayerInfoClass);
//PDAMenu_Dummy0->addSubMenu(new PDAMenu_PlayerSkillsClass);  --DISABLED



//->incedentDefault
/*
//PDAMenu.selectMenu(PDAMenuClass::MENUID_SUIT);
PDAMenu.defaultMenu      = new PDAMenu_Main;
Menu->insertAfterThis(new PDAMenu_Dummy0);
PDAMenu.PDAMenu_Dummy0.insertAfterThis(new PDAMenu_ArtefactsConnected);
PDAMenu.PDAMenu_ArtefactsConnected.insertAfterThis(new PDAMenu_ConnectedItem);
PDAMenu.PDAMenu_ConnectedItem.insertAfterThis(new PDAMenu_Quests);
PDAMenu.PDAMenu_Quests.insertAfterThis(new PDAMenu_Actions);
PDAMenu.PDAMenu_Actions.insertAfterThis(new PDAMenu_Settings);
    
PDAMenu.PDAMenu_Actions.addSubMenu(new PDAMenu_ActionSuicide);
PDAMenu.PDAMenu_Dummy0.addSubMenu(new PDAMenu_Stats);
PDAMenu.PDAMenu_Dummy0.addSubMenu(new PDAMenu_LastMeetAnomaly);
PDAMenu.PDAMenu_Dummy0.addSubMenu(new PDAMenu_Suite);
PDAMenu.PDAMenu_Dummy0.addSubMenu(new PDAMenu_Player);
*/
/*
Menu->next  = new PDAMenu_ArtefactsConnected;
Menu->prev  = new PDAMenu_ConnectedItem;

PDAMenu.PDAMenu_ArtefactsConnected.next  = new PDAMenu_ConnectedItem;
PDAMenu.PDAMenu_ArtefactsConnected.prev  = new PDAMenu_Main;

PDAMenu.PDAMenu_ConnectedItem.next  = new PDAMenu_Main;
PDAMenu.PDAMenu_ConnectedItem.prev  = new PDAMenu_ArtefactsConnected;
*/

PDAMenu.SelectDefaultMenu();

#endif
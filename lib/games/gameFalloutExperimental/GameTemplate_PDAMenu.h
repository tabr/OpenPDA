#ifndef GAME_TAMPLE_PDAMENU_H
#define GAME_TAMPLE_PDAMENU_H

//PDAMenu.selectMenu(PDAMenuClass::MENUID_SUIT);
PDAMenu.defaultMenu			= &PDAMenu.PDAMenu_Main;
PDAMenu.PDAMenu_Main.insertBefore(&PDAMenu.PDAMenu_Dummy0);
//PDAMenu.PDAMenu_Main.insertBefore(&PDAMenu.PDAMenu_ArtefactsConnected);
PDAMenu.PDAMenu_Main.insertBefore(&PDAMenu.PDAMenu_ConnectedItem);
PDAMenu.PDAMenu_Main.insertBefore(&PDAMenu.PDAMenu_Quests);
PDAMenu.PDAMenu_Main.insertBefore(&PDAMenu.PDAMenu_Dummy1);
PDAMenu.PDAMenu_Main.insertBefore(&PDAMenu.PDAMenu_ComputerHack);
PDAMenu.PDAMenu_Main.insertBefore(&PDAMenu.PDAMenu_Settings);

/*
PDAMenu.PDAMenu_Main.insertAfterThis(&PDAMenu.PDAMenu_Dummy0);
PDAMenu.PDAMenu_Dummy0.insertAfterThis(&PDAMenu.PDAMenu_ArtefactsConnected);
PDAMenu.PDAMenu_ArtefactsConnected.insertAfterThis(&PDAMenu.PDAMenu_ConnectedItem);
PDAMenu.PDAMenu_ConnectedItem.insertAfterThis(&PDAMenu.PDAMenu_Quests);
//PDAMenu.PDAMenu_Quests.insertAfterThis(&PDAMenu.PDAMenu_Actions);
PDAMenu.PDAMenu_Quests.insertAfterThis(&PDAMenu.PDAMenu_Dummy1);
PDAMenu.PDAMenu_Dummy1.insertAfterThis(&PDAMenu.PDAMenu_Settings);
*/
PDAMenu.PDAMenu_Dummy0.addSubMenu(&PDAMenu.PDAMenu_Stats);
//PDAMenu.PDAMenu_Dummy0.addSubMenu(&PDAMenu.PDAMenu_LastMeetAnomaly);
PDAMenu.PDAMenu_Dummy0.addSubMenu(&PDAMenu.PDAMenu_Suite);
PDAMenu.PDAMenu_Dummy0.addSubMenu(&PDAMenu.PDAMenu_PlayerInfo);
PDAMenu.PDAMenu_Dummy0.addSubMenu(&PDAMenu.PDAMenu_PlayerSkills);
PDAMenu.PDAMenu_Dummy1.addSubMenu(&PDAMenu.PDAMenu_ActionSuicide);

//PDAMenu.selectDefaultMenu();

#endif
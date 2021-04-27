#ifndef GAME_TAMPLE_PDAMENU_H
#define GAME_TAMPLE_PDAMENU_H


//PDAMenu.selectMenu(PDAMenuClass::MENUID_SUIT);
//PDAMenu.defaultMenu			= &PDAMenu.PDAMenu_Main;
PDAMenu.SetDefaultMenu(&PDAMenu.PDAMenu_Main);
//PDAMenu.PDAMenu_Main.insertBefore(&PDAMenu.PDAMenu_Dummy0);
//PDAMenu.PDAMenu_Main.insertBefore(&PDAMenu.PDAMenu_ArtefactsConnected);
PDAMenu.PDAMenu_Main.insertBefore(&PDAMenu.PDAMenu_ConnectedItem);
//PDAMenu.PDAMenu_Main.insertBefore(&PDAMenu.PDAMenu_Quests);
PDAMenu.PDAMenu_Main.insertBefore(&PDAMenu.PDAMenu_Dummy1);
//PDAMenu.PDAMenu_Main.insertBefore(&PDAMenu.PDAMenu_ComputerHack);	--DISABLED
PDAMenu.PDAMenu_Main.insertBefore(&PDAMenu.PDAMenu_Settings);
PDAMenu.PDAMenu_Main.insertBefore(&PDAMenu.PDAMenu_Games);
PDAMenu.PDAMenu_Main.insertBefore(&PDAMenu.PDAMenu_Quests);
#ifdef MASTER_PDA
	{
	PDAMenu.PDAMenu_Main.insertBefore(&PDAMenu.PDAMenu_Debug);
	PDAMenu.PDAMenu_Main.insertBefore(&PDAMenu.PDAMenu_TimeStranmitter);
	PDAMenu.PDAMenu_Main.insertBefore(&PDAMenu.PDAMenu_FM);
	PDAMenu.PDAMenu_Main.insertBefore(&PDAMenu.PDAMenu_MASTER_ItemArtefact);
	PDAMenu.PDAMenu_Main.insertBefore(&PDAMenu.PDAMenu_MASTER_ReviveAction);
	}
#endif // MASTER_PDA
//PDAMenu.PDAMenu_Main.insertBefore(&PDAMenu.PDAMenu_MASTER_ReviveAction);

//PDAMenu.PDAMenu_Main.insertAfterThis(&PDAMenu.PDAMenu_Dummy0);
//PDAMenu.PDAMenu_Dummy0.insertAfterThis(&PDAMenu.PDAMenu_ArtefactsConnected);

//PDAMenu.PDAMenu_ArtefactsConnected.insertAfterThis(&PDAMenu.PDAMenu_ConnectedItem);
//PDAMenu.PDAMenu_Quests.insertAfterThis(&PDAMenu.PDAMenu_Actions);
//PDAMenu.PDAMenu_Quests.insertAfterThis(&PDAMenu.PDAMenu_Dummy1);
//PDAMenu.PDAMenu_Dummy1.insertAfterThis(&PDAMenu.PDAMenu_Settings);

//PDAMenu.PDAMenu_Dummy0.addSubMenu(&PDAMenu.PDAMenu_Stats);
//PDAMenu.PDAMenu_Dummy0.addSubMenu(&PDAMenu.PDAMenu_ActiveEffects);
//PDAMenu.PDAMenu_Dummy0.addSubMenu(&PDAMenu.PDAMenu_LastMeetAnomaly);
//PDAMenu.PDAMenu_Dummy0.addSubMenu(&PDAMenu.PDAMenu_Suite);
//PDAMenu.PDAMenu_Dummy0.addSubMenu(&PDAMenu.PDAMenu_PlayerInfo);
//PDAMenu.PDAMenu_Dummy0.addSubMenu(&PDAMenu.PDAMenu_PlayerSkills);	--DISABLED
PDAMenu.PDAMenu_Dummy1.addSubMenu(&PDAMenu.PDAMenu_ActionSuicide);

//PDAMenu.selectDefaultMenu();

//->incedentDefault
/*
//PDAMenu.selectMenu(PDAMenuClass::MENUID_SUIT);
PDAMenu.defaultMenu			= &PDAMenu.PDAMenu_Main;
PDAMenu.PDAMenu_Main.insertAfterThis(&PDAMenu.PDAMenu_Dummy0);
PDAMenu.PDAMenu_Dummy0.insertAfterThis(&PDAMenu.PDAMenu_ArtefactsConnected);
PDAMenu.PDAMenu_ArtefactsConnected.insertAfterThis(&PDAMenu.PDAMenu_ConnectedItem);
PDAMenu.PDAMenu_ConnectedItem.insertAfterThis(&PDAMenu.PDAMenu_Quests);
PDAMenu.PDAMenu_Quests.insertAfterThis(&PDAMenu.PDAMenu_Actions);
PDAMenu.PDAMenu_Actions.insertAfterThis(&PDAMenu.PDAMenu_Settings);
		
PDAMenu.PDAMenu_Actions.addSubMenu(&PDAMenu.PDAMenu_ActionSuicide);
PDAMenu.PDAMenu_Dummy0.addSubMenu(&PDAMenu.PDAMenu_Stats);
PDAMenu.PDAMenu_Dummy0.addSubMenu(&PDAMenu.PDAMenu_LastMeetAnomaly);
PDAMenu.PDAMenu_Dummy0.addSubMenu(&PDAMenu.PDAMenu_Suite);
PDAMenu.PDAMenu_Dummy0.addSubMenu(&PDAMenu.PDAMenu_Player);
*/
/*
PDAMenu.PDAMenu_Main.next	= &PDAMenu.PDAMenu_ArtefactsConnected;
PDAMenu.PDAMenu_Main.prev	= &PDAMenu.PDAMenu_ConnectedItem;

PDAMenu.PDAMenu_ArtefactsConnected.next	= &PDAMenu.PDAMenu_ConnectedItem;
PDAMenu.PDAMenu_ArtefactsConnected.prev	= &PDAMenu.PDAMenu_Main;

PDAMenu.PDAMenu_ConnectedItem.next	= &PDAMenu.PDAMenu_Main;
PDAMenu.PDAMenu_ConnectedItem.prev	= &PDAMenu.PDAMenu_ArtefactsConnected;
*/

PDAMenu.selectDefaultMenu();

#endif
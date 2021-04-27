#ifndef GAMETEMPLATE_ITEMS_H_
#define GAMETEMPLATE_ITEMS_H_

	#ifdef DEBUG_BUILD
		LcdStringUpdate(1,LCD_LINE_2, (char*)"Items         ");
	#endif
	GameCFG.ItemTemplate.setItemsNum(TemporaryClass::ITEMS_NUM - 1);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_FIRST_AID,			(char*)"�������",		PlayerEffectsOldClass::EFFECTID_ITEM_FIRST_AID);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_BANDAGE,			(char*)"����",			PlayerEffectsOldClass::EFFECTID_ITEM_BANDAGE);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_ANTIRAD,			(char*)"�������",		PlayerEffectsOldClass::EFFECTID_ITEM_ANTIRAD);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_VODKA,				(char*)"�����",			PlayerEffectsOldClass::EFFECTID_ITEM_VODKA);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_PSY_BLOKADA,		(char*)"���-�������",	PlayerEffectsOldClass::EFFECTID_ITEM_PSY_BLOKADA);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_RAD_PROTECTOR,		(char*)"���-�������",	PlayerEffectsOldClass::EFFECTID_ITEM_RAD_PROTECTOR);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_FOOD,				(char*)"��������",		PlayerEffectsOldClass::EFFECTID_ITEM_FOOD);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_REPAIR_KIT,			(char*)"�����������",	PlayerEffectsOldClass::EFFECTID_ITEM_REPAIR_KIT);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_DETAILS,			(char*)"������",		PlayerEffectsOldClass::EFFECTID_NONE);
#endif //GAMETEMPLATE_ITEMS_H_
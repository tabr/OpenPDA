#ifndef GAME_ITEMS_H
#define GAME_ITEMS_H
	#ifdef DEBUG_BUILD
	LcdStringUpdate(1,LCD_LINE_2, (char*)"Items         ");
	#endif
	Items.setItemsNum(TemporaryClass::ITEMS_NUM - 1);
	Items.registerNew(TemporaryClass::ITEMID_FIRST_AID,			(char*)"�������",		PlayerEffectsClass::EFFECTID_ITEM_FIRST_AID);
//	Items.registerNew(TemporaryClass::ITEMID_BANDAGE,			(char*)"����",			PlayerEffectsClass::EFFECTID_ITEM_BANDAGE);
	Items.registerNew(TemporaryClass::ITEMID_ANTIRAD,			(char*)"�������",		PlayerEffectsClass::EFFECTID_ITEM_ANTIRAD);
	Items.registerNew(TemporaryClass::ITEMID_VODKA,				(char*)"�����",			PlayerEffectsClass::EFFECTID_ITEM_VODKA);
//	Items.registerNew(TemporaryClass::ITEMID_PSY_BLOKADA,		(char*)"���-�������",	PlayerEffectsClass::EFFECTID_ITEM_PSY_BLOKADA);
//	Items.registerNew(TemporaryClass::ITEMID_RAD_PROTECTOR,		(char*)"���-�������",	PlayerEffectsClass::EFFECTID_ITEM_RAD_PROTECTOR);
//	Items.registerNew(TemporaryClass::ITEMID_FOOD,				(char*)"��������",		PlayerEffectsClass::EFFECTID_ITEM_FOOD);
	Items.registerNew(TemporaryClass::ITEMID_REPAIR_KIT,		(char*)"�����������",	PlayerEffectsClass::EFFECTID_ITEM_REPAIR_KIT);
//	Items.registerNew(TemporaryClass::ITEMID_DETAILS,			(char*)"������",		PlayerEffectsClass::EFFECTID_NONE);
#endif

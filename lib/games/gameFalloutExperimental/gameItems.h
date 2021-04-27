	#ifdef DEBUG_BUILD
		LcdStringUpdate(1,LCD_LINE_2, (char*)"Items         ");
	#endif
	Items.setItemsNum(TemporaryClass::ITEMS_NUM - 1);
//	Items.setItemsNum(5);
	Items.registerNew(TemporaryClass::ITEMID_FIRST_AID,			(char*)"аптечка",		PlayerEffectsClass::EFFECTID_ITEM_FIRST_AID);
	Items.registerNew(TemporaryClass::ITEMID_ANTIRAD,			(char*)"антирадин",		PlayerEffectsClass::EFFECTID_ITEM_ANTIRAD);
	Items.registerNew(TemporaryClass::ITEMID_REPAIR_KIT,		(char*)"ремкомплект",	PlayerEffectsClass::EFFECTID_ITEM_REPAIR_KIT);
	Items.registerNew(TemporaryClass::ITEMID_RADX,				(char*)"RAD-X",			PlayerEffectsClass::EFFECTID_ITEM_RAD_PROTECTOR);
	#ifdef DEBUG_BUILD
		LcdStringUpdate(1,LCD_LINE_2, (char*)"Items [ok]    ");
	#endif

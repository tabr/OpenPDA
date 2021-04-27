#ifndef GAMETEMPLATE_ITEMS_H_
#define GAMETEMPLATE_ITEMS_H_

	#ifdef DEBUG_BUILD
		LcdStringUpdate(1,LCD_LINE_2, (char*)"Items         ");
	#endif

	/*
	GameCFG.ItemTemplate.setItemsNum(TemporaryClass::ITEMS_NUM - 1);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_FIRST_AID,			(char*)"�������",		Item_FirstAidKit);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_BANDAGE,			(char*)"����",			&PlayerEffects.PlayerEffect_NullEffect);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_ANTIRAD,			(char*)"�������",		Item_Antirad);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_VODKA,				(char*)"�����",			&PlayerEffects.PlayerEffect_NullEffect);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_PSY_BLOKADA,		(char*)"���-�������",	Item_PsyBlok);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_RAD_PROTECTOR,		(char*)"���-�������",	Item_Radioprotector);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_FOOD,				(char*)"��������",		EffectFood);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_REPAIR_KIT,			(char*)"�����������",	&PlayerEffects.PlayerEffect_NullEffect);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_DETAILS,			(char*)"������",		&PlayerEffects.PlayerEffect_NullEffect);
	*/
//GameCFG.ItemTemplate.setItemsNum(41);
GameCFG.ItemTemplate.RegisterNew(1,     (char*)"����",				&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(2,     (char*)"���������",			&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(3,     (char*)"����������",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(4,     (char*)"��������������",	&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(5,     (char*)"��������",			&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(6,     (char*)"������ �����",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(7,     (char*)"���� �������",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(8,     (char*)"����.������",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(9,     (char*)"����.�����",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(10,    (char*)"�����",				&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(11,    (char*)"��������",			&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(12,    (char*)"������ �����",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(13,    (char*)"�����.��������",	&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(14,    (char*)"����",				&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(15,    (char*)"�������",			Item_StimPack),
GameCFG.ItemTemplate.RegisterNew(16,    (char*)"���������",			Item_Antiradin),
GameCFG.ItemTemplate.RegisterNew(17,    (char*)"���-�",				Item_Rad_X),
GameCFG.ItemTemplate.RegisterNew(18,    (char*)"�����",				&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(19,    (char*)"������ ��.",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(20,    (char*)"������",			&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(21,    (char*)"������ (�����)",	&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(22,    (char*)"��������������",	&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(23,    (char*)"��������",			&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(24,    (char*)"������",			&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(25,    (char*)"�������",			&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(26,    (char*)"����-����",			&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(27,    (char*)"������� ����",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(28,    (char*)"������ ����",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(29,    (char*)"�����",				&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(30,    (char*)"��������������",	&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(31,    (char*)"�������",			&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(32,    (char*)"���",				&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(33,    (char*)"��������",			&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(34,    (char*)"������� �����",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(35,    (char*)"����������",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(36,    (char*)"������ ��.",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(37,    (char*)"�� �����������",	&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(38,    (char*)"�� �����������",	&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(39,    (char*)"��� ������� 30",    Item_EnclaveChip30);
GameCFG.ItemTemplate.RegisterNew(40,    (char*)"��� ������� 45",    Item_EnclaveChip45);
GameCFG.ItemTemplate.RegisterNew(41,    (char*)"��� ������� 60",    Item_EnclaveChip60);
#endif //GAMETEMPLATE_ITEMS_H_
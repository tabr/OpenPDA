	#ifdef DEBUG_BUILD
	sprintf (lcd_buf, "Suites        ");
	LcdString(1,LCD_LINE_2);
	LcdUpdate();
	#endif
	//!!!!!!!!!!!������!!! ������ ����������� ������ ������������� �� 0�00
	//	GameCFG.load();
	//														���							[����.���������]	[���.���]	[���.���]	[���.�������]	[���.�����]	[���.���]	[���.����]	[����.�����������]
	GameCFG.SuitsContainer.setContainerSize(12);
	GameCFG.SuitsContainer.container[0].setProperties((char*)("(�����)"),			0,					0,			0,			0,				0,			0,			0,			1);
	GameCFG.SuitsContainer.container[1].setProperties((char*)("����"),				1000,				5,			50,			50,				50,			50,			25,			4);
	GameCFG.SuitsContainer.container[2].setProperties((char*)("����"),				2000,				10,			70,			90,				80,			90,			50,			5);
	GameCFG.SuitsContainer.container[3].setProperties((char*)("������.�������"),	1250,				10,			50,			60,				50,			50,			25,			2);
	GameCFG.SuitsContainer.container[4].setProperties((char*)("�������"),			1000,				0,			10,			10,				10,			5,			0,			2);
	GameCFG.SuitsContainer.container[5].setProperties((char*)("�������*"),			1500,				5,			30,			30,				30,			30,			10,			3);
	GameCFG.SuitsContainer.container[6].setProperties((char*)("����.������"),		900,				0,			10,			10,				10,			5,			0,			2);
	GameCFG.SuitsContainer.container[7].setProperties((char*)("����.������*"),		1250,				5,			40,			40,				40,			40,			15,			3);
	GameCFG.SuitsContainer.container[8].setProperties((char*)("���-99 ������"),		1000,				10,			90,			90,				90,			90,			50,			5);
	GameCFG.SuitsContainer.container[9].setProperties((char*)("������-5�"),			2000,				10,			30,			30,				30,			30,			20,			2);
	GameCFG.SuitsContainer.container[10].setProperties((char*)("���.����������"),	1500,				0,			10,			10,				10,			10,			0,			2);
	GameCFG.SuitsContainer.container[11].setProperties((char*)("�����.�����"),		400,				5,			30,			30,				30,			30,			5,			2);

	#ifdef DEBUG_BUILD
	sprintf (lcd_buf, "Anomalies     ");
	LcdString(1,LCD_LINE_2);
	LcdUpdate();
	#endif
	Anomaly.setAnomaliesNum(6);
	//	Anomaly.registerNew(TemporaryClass::ANOMALY_TYPE_NONE,		(char*)"(���)",			DamageClass::DAMAGE_SOURCE_NONE);
	Anomaly.registerNew(TemporaryClass::ANOMALY_TYPE_JARKA,		(char*)"�����",			DamageClass::DAMAGE_SOURCE_FIRE);
	Anomaly.registerNew(TemporaryClass::ANOMALY_TYPE_ELECTRA,	(char*)"�������",		DamageClass::DAMAGE_SOURCE_ELECTRO);
	Anomaly.registerNew(TemporaryClass::ANOMALY_TYPE_HOLODEC,	(char*)"�������",		DamageClass::DAMAGE_SOURCE_CHEMICAL);
	Anomaly.registerNew(TemporaryClass::ANOMALY_TYPE_KISEL,		(char*)"������",		DamageClass::DAMAGE_SOURCE_CHEMICAL);
	Anomaly.registerNew(TemporaryClass::ANOMALY_TYPE_KARUSEL,	(char*)"��������",		DamageClass::DAMAGE_SOURCE_GRAVY);
	Anomaly.registerNew(TemporaryClass::ANOMALY_TYPE_TRAMPLIN,	(char*)"��������",		DamageClass::DAMAGE_SOURCE_GRAVY);

	#ifdef DEBUG_BUILD
	sprintf (lcd_buf, "Items         ");
	LcdString(1,LCD_LINE_2);
	LcdUpdate();
	#endif
	Items.setItemsNum(TemporaryClass::ITEMS_NUM - 1);
	Items.registerNew(TemporaryClass::ITEMID_FIRST_AID,			(char*)"�������",		PlayerEffectsClass::EFFECTID_ITEM_FIRST_AID);
	Items.registerNew(TemporaryClass::ITEMID_BANDAGE,			(char*)"����",			PlayerEffectsClass::EFFECTID_ITEM_BANDAGE);
	Items.registerNew(TemporaryClass::ITEMID_ANTIRAD,			(char*)"�������",		PlayerEffectsClass::EFFECTID_ITEM_ANTIRAD);
	Items.registerNew(TemporaryClass::ITEMID_VODKA,				(char*)"�����",			PlayerEffectsClass::EFFECTID_ITEM_VODKA);
	Items.registerNew(TemporaryClass::ITEMID_PSY_BLOKADA,		(char*)"���-�������",	PlayerEffectsClass::EFFECTID_ITEM_PSY_BLOKADA);
	Items.registerNew(TemporaryClass::ITEMID_RAD_PROTECTOR,		(char*)"���-�������",	PlayerEffectsClass::EFFECTID_ITEM_RAD_PROTECTOR);
	Items.registerNew(TemporaryClass::ITEMID_FOOD,				(char*)"��������",		PlayerEffectsClass::EFFECTID_ITEM_FOOD);
	Items.registerNew(TemporaryClass::ITEMID_REPAIR_KIT,		(char*)"�����������",	PlayerEffectsClass::EFFECTID_ITEM_REPAIR_KIT);
	Items.registerNew(TemporaryClass::ITEMID_DETAILS,			(char*)"������",		PlayerEffectsClass::EFFECTID_NONE);
	
	//	char* tmp	= (char*)MemoryManager.allocate(32);
	//	sprintf(tmp,"����� �� ����");
	#ifdef DEBUG_BUILD
	sprintf (lcd_buf, "Quests        ");
	LcdString(1,LCD_LINE_2);
	LcdUpdate();
	#endif
	Quest.setQuestsNum(TemporaryClass::QUESTS_NUM - 1);
	Quest.registerNew(TemporaryClass::QID_FIND_BAR,				(char*)"����� �� ����");
	//	Quest.registerNew(TemporaryClass::QID_FIND_BAR,				tmp);
	Quest.registerNew(TemporaryClass::QID_FIND_KEY,				(char*)"����� ���� �� ����");
	//	Quest.registerNew(TemporaryClass::QID_FIND_BARMAN,			(char*)"����� ���������� �������");
	//	sprintf(tmp,"����� ���������� �������");
	//	Quest.registerNew(TemporaryClass::QID_FIND_BAR,				tmp);
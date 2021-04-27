// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef RUNLEVELS_C
#define RUNLEVELS_C
/*
 * runlevels.c
 *
 * Created: 2015-02-03 18:34:28
 *  Author: tabr
 */ 
void runlevel_0(void)//system just started
	{
	//extern LcdDisplay;
	LcdDisplay.IOInit();
	LcdDisplay.HardwareInitialization();
	#ifdef DEBUG_BUILD
		sprintf (lcd_buf, "runlevel 0");
		LcdString(1,LCD_LINE_1);
		LcdUpdate();
	#endif
	HAL.Clock.selectMaxExternal();
	/*
	sysclk_enable_module(SYSCLK_PORT_GEN, SYSCLK_RTC);
	//sysclk_enable_module(SYSCLK_PORT_GEN, SYSCLK_AES);
	
	sysclk_enable_module(SYSCLK_PORT_B, SYSCLK_DAC);

	sysclk_enable_module(SYSCLK_PORT_C, SYSCLK_TWI);
	sysclk_enable_module(SYSCLK_PORT_C, SYSCLK_SPI);
	sysclk_enable_module(SYSCLK_PORT_C, SYSCLK_TC0);

	sysclk_enable_module(SYSCLK_PORT_D, SYSCLK_TC1);

	sysclk_enable_module(SYSCLK_PORT_E, SYSCLK_TWI);
	sysclk_enable_module(SYSCLK_PORT_E, SYSCLK_SPI);
	sysclk_enable_module(SYSCLK_PORT_E, SYSCLK_TC0);


	sysclk_enable_module(SYSCLK_PORT_F, SYSCLK_SPI);
	*/
	}
void runlevel_1(void)//IO init
	{
	#ifdef DEBUG_BUILD
		sprintf (lcd_buf, "runlevel 1");
		LcdString(1,LCD_LINE_1);
		LcdUpdate();
	#endif
	HAL.IOInit();
	Vibro.IOInit();
	BackLight.IOInit();
	ArtefactPorts.IOInit();
	Buttons.IOInit();
	
	MediaFlashPinClk::setDirOut();
	MediaFlashPinClk::setOutHigh();

	MediaFlashPinMiso::setDirIn();

	MediaFlashPinMosi::setDirOut();
	MediaFlashPinMosi::setOutHigh();

	MediaFlashPinSS::setDirOut();
	MediaFlashPinSS::setOutHigh();//deactivate
	
	ChargerPinCE::setDirOut();
	ChargerPinCE::setOutHigh();
	ChargerPinCharging::setDirIn();
	ChargerPinCharging::setPullUp();
	ChargerPinStandby::setDirIn();
	ChargerPinStandby::setPullUp();

	
	VBUSPin::setDirIn();
	VBUSPin::setPullDown();
	}
void runlevel_2(void)//Hardware initialization
	{
	#ifdef DEBUG_BUILD
		sprintf (lcd_buf, "runlevel 2");
		LcdString(1,LCD_LINE_1);
		LcdUpdate();
	#endif
	#ifdef DEBUG_BUILD
		sprintf (lcd_buf, "stralker layer");
		LcdString(1,LCD_LINE_2);
		LcdUpdate();
	#endif
	StalkerLayer2.HardwareInitialization();
	#ifdef DEBUG_BUILD
		sprintf (lcd_buf, "RTC");
		LcdString(1,LCD_LINE_2);
		LcdUpdate();
	#endif
	Stalker.InitRTC();
	#ifdef DEBUG_BUILD
		sprintf (lcd_buf, "Interrupts    ");
		LcdString(1,LCD_LINE_2);
		LcdUpdate();
	#endif
	Stalker.InitInterrupts();
	#ifdef DEBUG_BUILD
		sprintf (lcd_buf, "DAC init      ");
		LcdString(1,LCD_LINE_2);
		LcdUpdate();
	#endif
	PDASound.DAC_init();
	#ifdef DEBUG_BUILD
		sprintf (lcd_buf, "PrgStart...   ");
		LcdString(1,LCD_LINE_2);
		LcdUpdate();
	#endif
	StalkerLayer2.programmStart();

	/*#ifndef FM_DISABLED
		#ifdef DEBUG_BUILD
			sprintf (lcd_buf, "FM module     ");
			LcdString(1,LCD_LINE_2);
			LcdUpdate();
		#endif
		//twi_init(fm);
	#endif*/
	#ifdef DEBUG_BUILD
		sprintf (lcd_buf, "FM module AR10");
		LcdString(1,LCD_LINE_2);
		LcdUpdate();
	#endif
	Ar1010.HardwareInitialization();




	}

void runlevel_3(void)//Tasks & interrupts
	{
	#ifdef DEBUG_BUILD
		sprintf (lcd_buf, "runlevel 3");
		LcdString(1,LCD_LINE_1);
		sprintf (lcd_buf, "              ");
		LcdString(1,LCD_LINE_2);
		LcdUpdate();
	#endif
	EventSystem.registerUserEvent(&damageTaken,							EventSystemClass::EVID_DAMAGE_TAKEN);
	
	
	Timer.addTask(Anomaly.Task1);				//01
	Timer.addTask(StalkerLayer2.Task1);			//02
	Timer.addTask(StalkerLayer2.Task2);			//03
	Timer.addTask(ArtefactPorts.Task1);			//04
	Timer.addTask(ArtefactPorts.Task2);			//05
	Timer.addTask(PDAMenu.Task1);				//06
	Timer.addTask(Env.Task1);					//07
	Timer.addTask(UsableItem.Task1);			//08
	Timer.addTask(UsableItem.Task2);			//08
//	Timer.addTask(userFunction100msTask);		//10
	Timer.addTask(userFunction1000msTask);		//10
	Timer.addTask(Player.Task1);				//11
	Timer.addTask(Buttons.Task1);				//12
	Timer.addTask(Buttons.Task2);				//13
	Timer.addTask(PlayerEffects.Task1);			//14
	Timer.addTask(Vibro.Task1);					//15
	sei();
	#ifdef DEBUG_BUILD
		sprintf (lcd_buf, "Completed     ");
		LcdString(1,LCD_LINE_2);
		LcdUpdate();
	#endif
	}
	
void runlevel_4(void)//periphery init and data load
	{
	#ifdef DEBUG_BUILD
		sprintf (lcd_buf, "runlevel 4");
		LcdString(1,LCD_LINE_1);
		sprintf (lcd_buf, "              ");
		LcdString(1,LCD_LINE_2);
		LcdUpdate();
	#endif
	//							имя				[макс.прочность]	[защ.пси]	[защ.хим]	[защ.электро]	[защ.огонь]	[защ.рад]	[защ.грав]	[макс.контейнеров]
//	GameCFG.SuitsContainer.registerNew("(пусто)",		0,					0,			0,			0,				0,			0,			0,			1);
//	GameCFG.SuitsContainer.registerNew("к.сталкера",	100,				0,			25,			25,				25,			25,			25,			3);
//	GameCFG.SuitsContainer.registerNew("сева",			150,				10,			70,			90,				80,			90,			50,			5);

//	char string0[DeviceConfigClass::ITEM_NAME_CHAR_ARRAY_LENGTH];
	/*
	//eeprom_write_block(string0,(void *)128,15);
//	strcpy(string0, "(пусто)");
	eeprom_read_block(string0,(void *)128,15);
	if (string0[0] == 0xFF)
		{
		char tmp[15]	= "(пусто)       ";
		eeprom_write_block(tmp,(void *)128,15);
		sprintf(tmp,"к.сталкера    ");
		eeprom_write_block(tmp,(void *)(128+15),15);
		sprintf(tmp,"сева          ");
		eeprom_write_block(tmp,(void *)(128+30),15);


		sprintf (lcd_buf,"ЕЕПРОМ обновлён");
		LcdString(1,LCD_LINE_5);
		LcdUpdate();
		while (1);
		}
	*/
//	char string0[15]="сева";
	//eeprom_read_block(string0,(void *)128,15);
//	sprintf(string0,	"(пусто)       ");
//														имя							[макс.прочность]	[защ.пси]	[защ.хим]	[защ.электро]	[защ.огонь]	[защ.рад]	[защ.грав]	[макс.контейнеров]
//	GameCFG.SuitsContainer.registerNew(new SuitExample((char*)("(пусто)"),			0,					0,			0,			0,				0,			0,			0,			1));
	//eeprom_read_block(string0,(void *)(128+15),15);
//	sprintf(string0,	"к.сталкера    ");
//	GameCFG.SuitsContainer.registerNew(new SuitExample((char*)("к.сталкера"),		100,				0,			25,			25,				25,			25,			25,			3));
	//eeprom_read_block(string0,(void *)(128+30),15);
//	sprintf(string0,	"сева          ");
//	GameCFG.SuitsContainer.registerNew(new SuitExample((char*)("сева"),				150,				10,			70,			90,				80,			90,			50,			5));

	#ifdef DEBUG_BUILD
		sprintf (lcd_buf, "Containers    ");
		LcdString(1,LCD_LINE_2);
		LcdUpdate();
	#endif
//!!!!!!!!!!!АХТУНГ!!! строка ОБЯЗАТЕЛЬНО должна заканчиваться на 0х00
//	GameCFG.load();
//														имя							[макс.прочность]	[защ.пси]	[защ.хим]	[защ.электро]	[защ.огонь]	[защ.рад]	[защ.грав]	[макс.контейнеров]
	GameCFG.SuitsContainer.setContainerSize(12);
	GameCFG.SuitsContainer.container[0].setProperties((char*)("(пусто)"),			0,					0,			0,			0,				0,			0,			0,			1);
	GameCFG.SuitsContainer.container[1].setProperties((char*)("Заря"),				1000,				5,			50,			50,				50,			50,			25,			4);
	GameCFG.SuitsContainer.container[2].setProperties((char*)("Сева"),				2000,				10,			70,			90,				80,			90,			50,			5);
	GameCFG.SuitsContainer.container[3].setProperties((char*)("комбез.Монолит"),	1250,				10,			50,			60,				50,			50,			25,			2);
	GameCFG.SuitsContainer.container[4].setProperties((char*)("Кожанка"),			1000,				0,			10,			10,				10,			5,			0,			2);
	GameCFG.SuitsContainer.container[5].setProperties((char*)("Кожанка*"),			1500,				5,			30,			30,				30,			30,			10,			3);
	GameCFG.SuitsContainer.container[6].setProperties((char*)("Банд.куртка"),		900,				0,			10,			10,				10,			5,			0,			2);
	GameCFG.SuitsContainer.container[7].setProperties((char*)("Банд.куртка*"),		1250,				5,			40,			40,				40,			40,			15,			3);
	GameCFG.SuitsContainer.container[8].setProperties((char*)("ССП-99 Эколог"),		1000,				10,			90,			90,				90,			90,			50,			5);
	GameCFG.SuitsContainer.container[9].setProperties((char*)("Берилл-5М"),			2000,				10,			30,			30,				30,			30,			20,			2);
	GameCFG.SuitsContainer.container[10].setProperties((char*)("Арм.Бронежилет"),	1500,				0,			10,			10,				10,			10,			0,			2);
	GameCFG.SuitsContainer.container[11].setProperties((char*)("Научн.Халат"),		400,				5,			30,			30,				30,			30,			5,			2);

	#ifdef DEBUG_BUILD
		sprintf (lcd_buf, "Anomalies     ");
		LcdString(1,LCD_LINE_2);
		LcdUpdate();
	#endif
	Anomaly.setAnomaliesNum(6);
//	Anomaly.registerNew(TemporaryClass::ANOMALY_TYPE_NONE,		(char*)"(нет)",			DamageClass::DAMAGE_SOURCE_NONE);
	Anomaly.registerNew(TemporaryClass::ANOMALY_TYPE_JARKA,		(char*)"жарка",			DamageClass::DAMAGE_SOURCE_FIRE);
	Anomaly.registerNew(TemporaryClass::ANOMALY_TYPE_ELECTRA,	(char*)"электра",		DamageClass::DAMAGE_SOURCE_ELECTRO);
	Anomaly.registerNew(TemporaryClass::ANOMALY_TYPE_HOLODEC,	(char*)"холодец",		DamageClass::DAMAGE_SOURCE_CHEMICAL);
	Anomaly.registerNew(TemporaryClass::ANOMALY_TYPE_KISEL,		(char*)"кисель",		DamageClass::DAMAGE_SOURCE_CHEMICAL);
	Anomaly.registerNew(TemporaryClass::ANOMALY_TYPE_KARUSEL,	(char*)"карусель",		DamageClass::DAMAGE_SOURCE_GRAVY);
	Anomaly.registerNew(TemporaryClass::ANOMALY_TYPE_TRAMPLIN,	(char*)"трамплин",		DamageClass::DAMAGE_SOURCE_GRAVY);

	#ifdef DEBUG_BUILD
		sprintf (lcd_buf, "Items         ");
		LcdString(1,LCD_LINE_2);
		LcdUpdate();
	#endif
	Items.setItemsNum(TemporaryClass::ITEMS_NUM - 1);
	Items.registerNew(TemporaryClass::ITEMID_FIRST_AID,			(char*)"аптечка",		PlayerEffectsClass::EFFECTID_ITEM_FIRST_AID);
	Items.registerNew(TemporaryClass::ITEMID_BANDAGE,			(char*)"бинт",			PlayerEffectsClass::EFFECTID_ITEM_BANDAGE);
	Items.registerNew(TemporaryClass::ITEMID_ANTIRAD,			(char*)"антирад",		PlayerEffectsClass::EFFECTID_ITEM_ANTIRAD);
	Items.registerNew(TemporaryClass::ITEMID_VODKA,				(char*)"водка",			PlayerEffectsClass::EFFECTID_ITEM_VODKA);
	Items.registerNew(TemporaryClass::ITEMID_PSY_BLOKADA,		(char*)"пси-блокада",	PlayerEffectsClass::EFFECTID_ITEM_PSY_BLOKADA);
	Items.registerNew(TemporaryClass::ITEMID_RAD_PROTECTOR,		(char*)"рад-протект",	PlayerEffectsClass::EFFECTID_ITEM_RAD_PROTECTOR);
	Items.registerNew(TemporaryClass::ITEMID_FOOD,				(char*)"консервы",		PlayerEffectsClass::EFFECTID_ITEM_FOOD);
	Items.registerNew(TemporaryClass::ITEMID_REPAIR_KIT,		(char*)"ремкомплект",	PlayerEffectsClass::EFFECTID_ITEM_REPAIR_KIT);
	Items.registerNew(TemporaryClass::ITEMID_DETAILS,			(char*)"детали",		PlayerEffectsClass::EFFECTID_NONE);
	
//	char* tmp	= (char*)MemoryManager.allocate(32);
//	sprintf(tmp,"дойти до бара");
	#ifdef DEBUG_BUILD
		sprintf (lcd_buf, "Quests        ");
		LcdString(1,LCD_LINE_2);
		LcdUpdate();
	#endif
	Quest.setQuestsNum(TemporaryClass::QUESTS_NUM - 1);
	Quest.registerNew(TemporaryClass::QID_FIND_BAR,				(char*)"дойти до бара");
//	Quest.registerNew(TemporaryClass::QID_FIND_BAR,				tmp);
	Quest.registerNew(TemporaryClass::QID_FIND_KEY,				(char*)"найти ключ от лабы");
//	Quest.registerNew(TemporaryClass::QID_FIND_BARMAN,			(char*)"найти пропавшего бармена");
//	sprintf(tmp,"найти пропавшего бармена");
//	Quest.registerNew(TemporaryClass::QID_FIND_BAR,				tmp);

	#ifdef DEBUG_BUILD

		sprintf (lcd_buf, "wrt Art Erase ");
		LcdString(1,LCD_LINE_2);
		LcdUpdate();
		ArtefactPorts.M25P05_BulkErase(0);

		sprintf (lcd_buf, "wrt Art Write ");
		LcdString(1,LCD_LINE_2);
		LcdUpdate();
		//																	subtype																				param [0-3][charges,value,delay]
		//[EXCLUDED]uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_MEDICAMENTS,	0,		ItemsClass::ITEMID_FIRST_AID,			ArtefactPortsClass::DEVICE_STATUS_OK,	0b11111111, 15,	50,0};
		//[EXCLUDED]uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_MEDICAMENTS,	0,		ItemsClass::ITEMID_ANTIRAD,				ArtefactPortsClass::DEVICE_STATUS_OK,	0, 4,	0,0};
		//[EXCLUDED]uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_MEDICAMENTS,	0,		ItemsClass::ITEMID_PSY_BLOKADA,			ArtefactPortsClass::DEVICE_STATUS_OK,	0b11111111, 0,	0,0};
		//[EXCLUDED]uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_MEDICAMENTS,	0,		ItemsClass::ITEMID_RAD_PROTECOR,		ArtefactPortsClass::DEVICE_STATUS_OK,	0b11111111, 0,	0,0};
		//[EXCLUDED]uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_MEDICAMENTS,	0,		ItemsClass::ITEMID_VODKA,				ArtefactPortsClass::DEVICE_STATUS_OK,	0b11111111, 0,	0,0};
		//[EXCLUDED]uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_SUIT,			0,		PlayerSuitClass::SUIT_ID_SEVA,			ArtefactPortsClass::DEVICE_STATUS_OK,	100, 0,	0,0};
		//[EXCLUDED]uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_SUIT,			0,		PlayerSuitClass::SUIT_ID_STALKER_SUIT,	ArtefactPortsClass::DEVICE_STATUS_OK,	100, 0,	0,0};


		//uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_ARTEFACT,		0,		ArtefactClass::ARTEFACT_PLENKA, 0,0, 0, 0, 0};
		//uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_ARTEFACT,		0,		ArtefactClass::ARTEFACT_OGN_SHAR, 0,0, 0, 0, 0};
		//uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_ARTEFACT,		0,		ArtefactClass::ARTEFACT_LUN_SVET, 0,0, 0, 0, 0};
		//uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_ARTEFACT,		0,		ArtefactClass::ARTEFACT_VSPYSHKA, 0,0, 0, 0, 0};
//		uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_ARTEFACT,		0,		ArtefactClass::ARTEFACT_MEDUSA, 0,0, 0, 0, 0};
		//uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_ARTEFACT,		0,		ArtefactClass::ARTEFACT_DUWA, 0,0, 0, 0, 0};
//		uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_ARTEFACT,		0,		ArtefactClass::ARTEFACT_KAM_CVETOK, 0,0, 0, 0, 0};
		uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_ARTEFACT,		0,		ArtefactClass::ARTEFACT_PUSTIWKA, 0,0, 0, 0, 0};
		ArtefactPorts.M25P05_wholeItemWrite(0, item);

		sprintf (lcd_buf, "4.5");
		LcdString(1,LCD_LINE_1);
		LcdUpdate();
		
		UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_MEDICAMENTS, UsableItemClass::ITEM_SUBTYPE_NONE, TemporaryClass::ITEMID_FIRST_AID, UsableItemClass::DEVICE_STATUS_OK, 8, 0, 0, 0);
		//UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_MEDICAMENTS, UsableItemClass::ITEM_SUBTYPE_NONE, TemporaryClass::ITEMID_BANDAGE, UsableItemClass::DEVICE_STATUS_OK, 10, 0, 0, 0);
		//UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_MEDICAMENTS, UsableItemClass::ITEM_SUBTYPE_NONE, TemporaryClass::ITEMID_ANTIRAD, UsableItemClass::DEVICE_STATUS_OK, 8, 0, 0, 0);
		//UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_MEDICAMENTS, UsableItemClass::ITEM_SUBTYPE_NONE, TemporaryClass::ITEMID_VODKA, UsableItemClass::DEVICE_STATUS_OK, 100, 0, 0, 0);
		//UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_MEDICAMENTS, UsableItemClass::ITEM_SUBTYPE_NONE, TemporaryClass::ITEMID_RAD_PROTECTOR, UsableItemClass::DEVICE_STATUS_OK, 100, 0, 0, 0);
		//UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_MEDICAMENTS, UsableItemClass::ITEM_SUBTYPE_NONE, ItemsClass::ITEMID_PSY_BLOKADA, UsableItemClass::DEVICE_STATUS_OK, 130, 0, 0, 0);
		//UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_ELSE, UsableItemClass::ITEM_SUBTYPE_NONE, TemporaryClass::ITEMID_REPAIR_KIT, UsableItemClass::DEVICE_STATUS_OK, 255, 0, 0, 0);
		//UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_SUIT, UsableItemClass::ITEM_SUBTYPE_NONE, GameConfig::SUIT_ID_SEVA, UsableItemClass::DEVICE_STATUS_OK, 100, 0, 0, 0);
		//UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_SUIT, UsableItemClass::ITEM_SUBTYPE_NONE, GameConfig::SUIT_ID_STALKER, UsableItemClass::DEVICE_STATUS_OK, 100, 0, 0, 0);
		//UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_SUIT, UsableItemClass::ITEM_SUBTYPE_NONE, GameConfig::SUIT_ID_NONE, UsableItemClass::DEVICE_STATUS_OK, 0, 0, 0, 0);
		//UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_INFORMATION, UsableItemClass::ITEM_SUBTYPE_NONE, ItemInformationClass::ID_FOUND_SEVA, UsableItemClass::DEVICE_STATUS_OK, 0, 0, 0, 0);
		//UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_INFORMATION, UsableItemClass::ITEM_SUBTYPE_NONE, ItemInformationClass::ID_CODE, UsableItemClass::DEVICE_STATUS_OK, 0, 0, 0, 0);
		//UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_INFORMATION, UsableItemClass::ITEM_SUBTYPE_NONE, ItemInformationClass::ID_GOOUT, UsableItemClass::DEVICE_STATUS_OK, 0, 0, 0, 0);
		//UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_INFORMATION, UsableItemClass::ITEM_SUBTYPE_NONE, ItemInformationClass::ID_NONE, UsableItemClass::DEVICE_STATUS_OK, 8, 0, 0, 0);
		
		//UsableItem.setConnectedItem(1, 2, 3, 4, 5, 6, 7, 8);
		UsableItem.writeConnectedItem();
		UsableItem.cleanConnectedItem();
		/*
		char tmp[9];
		sprintf(tmp, "сталкер ");//последняя отбросится
		UsableItem.hardware.writeToDevice(UsableItemClass::ITEM_INFORMATION_HEAD_PAGE, (uint8_t*)tmp);
		sprintf(tmp, "'ЗЕТ':");
		UsableItem.twi_write_page(UsableItemClass::ITEM_INFORMATION_HEAD_PAGE+1, (uint8_t*)tmp);
		*/
		/*
		sprintf(tmp, "Нашел СЕ");//последняя отбросится
		UsableItem.twi_write_page(UsableItemClass::ITEM_INFORMATION_DATA_PAGE, (uint8_t*)tmp);
		sprintf(tmp, "ВУ. ЭТО ");
		UsableItem.twi_write_page(UsableItemClass::ITEM_INFORMATION_DATA_PAGE+1, (uint8_t*)tmp);
		sprintf(tmp, "оставлю ");//последняя отбросится
		UsableItem.twi_write_page(UsableItemClass::ITEM_INFORMATION_DATA_PAGE+2, (uint8_t*)tmp);
		sprintf(tmp, "тут.    ");
		UsableItem.hardware.writeToDevice .twi_write_page(UsableItemClass::ITEM_INFORMATION_DATA_PAGE+3, (uint8_t*)tmp);
		sprintf(tmp, "12345678");//последняя отбросится
		UsableItem.twi_write_page(UsableItemClass::ITEM_INFORMATION_DATA_PAGE+4, (uint8_t*)tmp);
		sprintf(tmp, "90abcdef");
		UsableItem.twi_write_page(UsableItemClass::ITEM_INFORMATION_DATA_PAGE+5, (uint8_t*)tmp);
		sprintf(tmp, "qwertyui");//последняя отбросится
		UsableItem.twi_write_page(UsableItemClass::ITEM_INFORMATION_DATA_PAGE+6, (uint8_t*)tmp);
		sprintf(tmp, "asdfghjk");
		UsableItem.twi_write_page(UsableItemClass::ITEM_INFORMATION_DATA_PAGE+7, (uint8_t*)tmp);
		*/
	#endif

	}
void runlevel_5(void)//All data loaded, ready to start
	{
	#ifdef DEBUG_BUILD
		sprintf (lcd_buf, "runlevel 5");
		LcdString(1,LCD_LINE_1);
		LcdUpdate();
		_delay_ms(500);
	#endif

	#ifdef DEBUG_BUILD
		sprintf (lcd_buf, "PlayerLoad    ");
		LcdString(1,LCD_LINE_2);
		LcdUpdate();
	#endif
	Player.load();

	//if (HAL.IO.isPinLow(ButtonsClass::PIN_MENU_HAL))
	if (ButtonMenuPin::isPinLow())
		{
		while(1)
			{
			if (StalkerLayer2.L1.L0.isNewEnvPacketReceived())
				{
				StalkerLayer2.L1.L0.getEnvPacketAndRSSI();

				sprintf (lcd_buf,"%03d%03d %03d%03d", StalkerLayer2.L1.L0.SignalPower, StalkerLayer2.L1.L0.RSSI, StalkerLayer2.L1.L0.RSSIRaw, StalkerLayer2.L1.L0.i);
				//				StalkerLayer0.i=3;
				LcdString(1,LCD_LINE_1);
				sprintf (lcd_buf,"%03d%03d %03d%03d", StalkerLayer2.L1.L0.packetContainer[0], StalkerLayer2.L1.L0.packetContainer[1], StalkerLayer2.L1.L0.packetContainer[2], StalkerLayer2.L1.L0.packetContainer[3]);
				LcdString(1,LCD_LINE_2);
				sprintf (lcd_buf,"%03d%03d", StalkerLayer2.L1.L0.packetContainer[4], StalkerLayer2.L1.L0.packetContainer[5]);
				LcdString(1,LCD_LINE_3);
				//				sprintf (lcd_buf,"%03d%03d %03d%03d", StalkerLayer0.packetContainer[4], StalkerLayer0.packetContainer[5], StalkerLayer0.packetContainer[6], StalkerLayer0.packetContainer[7]);
				//				LcdString(1,LCD_LINE_3);
				//				sprintf (lcd_buf,"%03d%03d %03d%03d", StalkerLayer0.packetContainer[8], StalkerLayer0.packetContainer[9], StalkerLayer0.packetContainer[10], StalkerLayer0.packetContainer[11]);
				//				LcdString(1,LCD_LINE_4);
				//				sprintf (lcd_buf,"%33d%03d %03d%03d", radio._RXBuffer[12], radio._RXBuffer[13], radio._RXBuffer[14], radio._RXBuffer[15]);
				//				LcdString(1,LCD_LINE_5);
				sprintf (lcd_buf,"%01d", StalkerLayer2.L1.L0.checkReceivedPacketCRC());
				LcdString(1,LCD_LINE_6);
				LcdUpdate();
				//radio.receiveBegin();
				StalkerLayer2.L1.L0.receiveBegin();
				delay_ms(40);
				}
			else
				{
				LcdClearUpdate();
				}
			}
		}
//	Quest.giveQuest(TemporaryClass::QID_FIND_BAR);
//	Quest.giveQuest(TemporaryClass::QID_FIND_BARMAN);
	
//	Quest.

	#ifdef DEBUG_BUILD
		//Player.SetRadDose(20);
		//EEPROM_Data.load();
		//USABLE_ITEM_ITEM_CONNECTED_PORT.PIN6CTRL	= PORT_OPC_PULLUP_gc;
		//USABLE_ITEM_ITEM_CONNECTED_PORT.OUTSET		= 1<<6;
		sprintf (lcd_buf, "starting...");
		LcdString(1,LCD_LINE_1);
		LcdUpdate();

		//LcdString(1,LCD_LINE_2, Anomaly.getAnomalyName(1));
		//LcdString(1,LCD_LINE_3, Anomaly.getAnomalyName(2));
		//LcdUpdate();
		//delay_ms(5000);
		
		
		//delay_ms(500);
		//		while(1);
		//PlayerSuit.wear(TemporaryClass::SUIT_ID_SEVA, 99);
		
//		PlayerSuit.wear(TemporaryClass::SUIT_ID_STALKER, PlayerSuitClass::DURABILITY_FULL);
		//PDAMenu.selectMenu(PDAMenuClass::MENUID_SUIT);
		PDAMenu.selectMenu(PDAMenuClass::MENUID_MAIN);
//		PDAMenu.selectMenu(PDAMenuClass::MENUID_EFFECTS);
		//PDAMenu.selectMenu(PDAMenuClass::MENUID_QUESTS);
		//PDAMenu.selectMenu(PDAMenuClass::MENUID_ARTEFACTS_CONNECTED);
		//PDAMenu.selectMenu(PDAMenuClass::MENUID_CONNECTED_ITEM);
		//PDAMenu.selectMenu(PDAMenuClass::MENUID_SUIT);
		//PDAMenu.selectMenu(PDAMenuClass::MENUID_SPECS);
		//PDAMenu.selectMenu(PDAMenuClass::MENUID_ACTIONS);
		//Player.SetHealth(80);


		//		PORTK.DIRCLR	= 1<<5;
		//		PORTK.PIN6CTRL	= PORT_OPC_PULLUP_gc;
	#else
		//Player.SetHealth(90);
		PDAMenu.selectMenu(PDAMenuClass::MENUID_MAIN);
	#endif

	Vibro.activate(10);
	//Quest.completeQuest(QuestClass::QID_FIND_BAR);
	//Quest.completeQuest(QuestClass::QID_FIND_BARMAN);
	}
#endif
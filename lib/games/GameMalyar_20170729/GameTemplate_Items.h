#ifndef GAMETEMPLATE_ITEMS_H_
#define GAMETEMPLATE_ITEMS_H_

	#ifdef DEBUG_BUILD
		LcdStringUpdate(1,LCD_LINE_2, (char*)"Items         ");
	#endif

	/*
	GameCFG.ItemTemplate.setItemsNum(TemporaryClass::ITEMS_NUM - 1);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_FIRST_AID,			(char*)"аптечка",		Item_FirstAidKit);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_BANDAGE,			(char*)"бинт",			&PlayerEffects.PlayerEffect_NullEffect);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_ANTIRAD,			(char*)"антирад",		Item_Antirad);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_VODKA,				(char*)"водка",			&PlayerEffects.PlayerEffect_NullEffect);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_PSY_BLOKADA,		(char*)"пси-блокада",	Item_PsyBlok);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_RAD_PROTECTOR,		(char*)"рад-протект",	Item_Radioprotector);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_FOOD,				(char*)"консервы",		EffectFood);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_REPAIR_KIT,			(char*)"ремкомплект",	&PlayerEffects.PlayerEffect_NullEffect);
	GameCFG.ItemTemplate.registerNew(TemporaryClass::ITEMID_DETAILS,			(char*)"детали",		&PlayerEffects.PlayerEffect_NullEffect);
	*/
//GameCFG.ItemTemplate.setItemsNum(41);
GameCFG.ItemTemplate.RegisterNew(1,     (char*)"Уран",				&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(2,     (char*)"Картофель",			&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(3,     (char*)"Металлолом",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(4,     (char*)"ОтхЭлектроники",	&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(5,     (char*)"Химикаты",			&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(6,     (char*)"Пустой Шприц",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(7,     (char*)"Мясо Брамина",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(8,     (char*)"Брам.Дерьмо",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(9,     (char*)"Брам.Стейк",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(10,    (char*)"Чипсы",				&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(11,    (char*)"Изолента",			&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(12,    (char*)"Чистая Книга",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(13,    (char*)"Ядерн.материал",	&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(14,    (char*)"Винт",				&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(15,    (char*)"Стимпак",			Item_StimPack),
GameCFG.ItemTemplate.RegisterNew(16,    (char*)"Антирадин",			Item_Antiradin),
GameCFG.ItemTemplate.RegisterNew(17,    (char*)"Рад-Х",				Item_Rad_X),
GameCFG.ItemTemplate.RegisterNew(18,    (char*)"Порох",				&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(19,    (char*)"Патрон об.",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(20,    (char*)"Журнал",			&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(21,    (char*)"Журнал (копия)",	&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(22,    (char*)"ЯдернаяБатарея",	&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(23,    (char*)"Консервы",			&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(24,    (char*)"Рецепт",			&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(25,    (char*)"Баффаут",			&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(26,    (char*)"Нюка-Кола",			&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(27,    (char*)"Грязная Вода",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(28,    (char*)"Чистая Вода",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(29,    (char*)"Мусор",				&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(30,    (char*)"Химлаборатория",	&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(31,    (char*)"Верстак",			&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(32,    (char*)"Раб",				&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(33,    (char*)"Мутфрукт",			&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(34,    (char*)"Участок земли",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(35,    (char*)"Антисептик",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(36,    (char*)"Патрон сн.",		&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(37,    (char*)"Яд нейротоксин",	&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(38,    (char*)"Яд смертельный",	&PlayerEffects.PlayerEffect_NullEffect);
GameCFG.ItemTemplate.RegisterNew(39,    (char*)"Чип Анклава 30",    Item_EnclaveChip30);
GameCFG.ItemTemplate.RegisterNew(40,    (char*)"Чип Анклава 45",    Item_EnclaveChip45);
GameCFG.ItemTemplate.RegisterNew(41,    (char*)"Чип Анклава 60",    Item_EnclaveChip60);
#endif //GAMETEMPLATE_ITEMS_H_
#ifndef GAME_SUITES_H
#define GAME_SUITES_H
	#ifdef DEBUG_BUILD
	LcdStringUpdate(1,LCD_LINE_2, (char*)"Suites        ");
	#endif
	//!!!!!!!!!!!АХТУНГ!!! строка ОБЯЗАТЕЛЬНО должна заканчиваться на 0х00
	//	GameCFG.load();
	//														имя														[макс.прочность]		[защ.пси]	[защ.хим]	[защ.электро]	[защ.огонь]	[защ.рад]	[защ.грав]	[макс.контейнеров]
	GameCFG.SuitsContainer.setContainerSize(TemporaryClass::SUITE_ID_SIZE);
	GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_NONE].setProperties((char*)("(пусто)"),				1,						0,			0,			0,				0,			0,			0,			1);
	GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_ZARYA].setProperties((char*)("Заря"),					100,					5,			0,			0,				0,			50,			0,			4);
	GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_MONOLIT].setProperties((char*)("комбез.Монолит"),		100,					50,			0,			0,				0,			50,			0,			2);
	GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_KOZH].setProperties((char*)("Кожанка"),				100,					5,			0,			0,				0,			5,			0,			2);
	GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_BANDOS].setProperties((char*)("Банд.куртка"),			100,					0,			0,			0,				0,			5,			0,			2);
	GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_ECOLOG].setProperties((char*)("ССП-99 Эколог"),		100,					50,			0,			0,				0,			90,			0,			5);
	GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_BERYL].setProperties((char*)("Берилл-5М"),				100,					10,			0,			0,				0,			30,			0,			2);
	GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_ARM_BRONE].setProperties((char*)("Арм.Бронежилет"),	100,					5,			0,			0,				0,			10,			0,			2);
	GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_EXO].setProperties((char*)("Экзоскелет"),				100,					50,			0,			0,				0,			70,			0,			4);
	

#endif
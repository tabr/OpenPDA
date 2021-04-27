#ifndef GAME_SUITS_H
#define GAME_SUITS_H

#ifdef DEBUG_BUILD
	LcdStringUpdate(1,LCD_LINE_2, (char*)"Suites        ");
#endif
//!!!!!!!!!!!АХТУНГ!!! строка ОБЯЗАТЕЛЬНО должна заканчиваться на 0х00
//	GameCFG.load();
//														имя														[макс.прочность]	[защ.пси]	[защ.хим]	[защ.электро]	[защ.огонь]	[защ.рад]	[защ.грав]	[макс.контейнеров]
GameCFG.SuitsContainer.setContainerSize(TemporaryClass::SUITE_ID_SIZE);
//GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_NONE].setProperties((char*)("(пусто)"),				0,					0,			0,			0,				0,			0,			0,			1);
GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_NONE)->setProperties((char*)("(пусто)"),				0,					0,			0,			0,				0,			0,			0,			1);
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_ZARYA)->setProperties((char*)("Заря"),					1000,				5,			50,			50,				50,			50,			25,			4);
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_SEVA)->setProperties((char*)("Сева"),					2000,				10,			70,			90,				80,			90,			50,			5);
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_MONOLIT).setProperties((char*)("комбез.Монолит"),		1250,				10,			50,			60,				50,			50,			25,			2);
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_KOZH).setProperties((char*)("Кожанка"),				1000,				0,			10,			10,				10,			5,			0,			2);
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_KOZH1).setProperties((char*)("Кожанка*"),				1500,				5,			30,			30,				30,			30,			10,			3);
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_BANDOS).setProperties((char*)("Банд.куртка"),			900,				0,			10,			10,				10,			5,			0,			2);
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_BANDOS1).setProperties((char*)("Банд.куртка*"),		1250,				5,			40,			40,				40,			40,			15,			3);
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_ECOLOG).setProperties((char*)("ССП-99 Эколог"),		1000,				10,			90,			90,				90,			90,			50,			5);
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_BERYL).setProperties((char*)("Берилл-5М"),			2000,				10,			30,			30,				30,			30,			20,			2);
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_BRONE).setProperties((char*)("Арм.Бронежилет"),		1500,				0,			10,			10,				10,			10,			0,			2);
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_HALAT).setProperties((char*)("Научн.Халат"),			400,				5,			30,			30,				30,			30,			5,			2);
//DamageListStruct dmg	= {.DamageRadiation=0, .DamageElectromagnetic=0,};
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_NONE).setProperties((char*)("(пусто)"),				0,					0, dmg);

#endif

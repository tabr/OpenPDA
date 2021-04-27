#ifndef GAME_SUITS_H
#define GAME_SUITS_H

#ifdef DEBUG_BUILD
	LcdStringUpdate(1,LCD_LINE_2, (char*)"Suits        ");
#endif
//!!!!!!!!!!!АХТУНГ!!! строка ОБЯЗАТЕЛЬНО должна заканчиваться на 0х00
//	GameCFG.load();
//														имя														[макс.прочность]	[макс.контейнеров]	[защ.пси]	[защ.хим]	[защ.электро]	[защ.огонь]	[защ.рад]	[защ.грав]
//GameCFG.SuitsContainer.setContainerSize(TemporaryClass::SUIT_ID_SIZE);
GameCFG.SuitsContainer.setContainerSize(5);//include "0"
DamageDefenceValue defTmp[GameCFG.GetDamageSourceNum()];
GameCharacteristicsClass c(0);

c	= GameCharacteristicsClass(1<<GameCharacteristicsClass::CHARACTERISTIC_DURABILITY | 1<<GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS);
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_NONE]					= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC]					= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL]		= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL]	= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_FIRE]					= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_ELECTRICITY]				= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_CHEMICAL]				= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_GRAVY]					= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_PSY]						= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_BIO]						= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT]					= 0;
c.Set(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY, 0);
c.Set(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS, 0);
GameCFG.SuitsContainer.container[TemporaryClass::SUIT_ID_NONE].setProperties((char*)("(пусто)"),	defTmp,	&c);

defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_NONE]					= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC]					= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL]		= 30;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL]	= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_FIRE]					= 30;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_ELECTRICITY]				= 30;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_CHEMICAL]				= 30;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_GRAVY]					= 10;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_PSY]						= 5;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_BIO]						= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT]					= 0;
c.Set(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY, 300);
c.Set(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS, 3);
GameCFG.SuitsContainer.container[TemporaryClass::SUIT_ID_ZARYA].setProperties((char*)("Заря"),		defTmp,	&c);

defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_NONE]					= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC]					= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL]		= 90;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL]	= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_FIRE]					= 80;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_ELECTRICITY]				= 90;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_CHEMICAL]				= 70;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_GRAVY]					= 50;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_PSY]						= 10;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_BIO]						= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT]					= 0;
c.Set(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY, 600);
c.Set(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS, 5);
GameCFG.SuitsContainer.container[TemporaryClass::SUIT_ID_SEVA].setProperties((char*)("Сева"),		defTmp,	&c);

defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_NONE]					= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC]					= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL]		= 60;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL]	= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_FIRE]					= 80;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_ELECTRICITY]				= 90;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_CHEMICAL]				= 70;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_GRAVY]					= 50;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_PSY]						= 40;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_BIO]						= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT]					= 0;
c.Set(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY, 600);
c.Set(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS, 4);
GameCFG.SuitsContainer.container[TemporaryClass::SUIT_ID_EXO].setProperties((char*)("Экзоскелет"),		defTmp,	&c);

defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_NONE]					= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC]					= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL]		= 90;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL]	= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_FIRE]					= 80;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_ELECTRICITY]				= 90;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_CHEMICAL]				= 70;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_GRAVY]					= 50;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_PSY]						= 60;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_BIO]						= 0;
defTmp[TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT]					= 0;
c.Set(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY, 600);
c.Set(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS, 4);
GameCFG.SuitsContainer.container[TemporaryClass::SUIT_ID_MONOLIT_EXO].setProperties((char*)("Монол.Экзо"),		defTmp,	&c);

/*
//														имя														[макс.прочность]	[защ.пси]	[защ.хим]	[защ.электро]	[защ.огонь]	[защ.рад]	[защ.грав]	[макс.контейнеров]
GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_NONE].setProperties((char*)("(пусто)"),				0,					0,			0,			0,				0,			0,			0,			0);
GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_ZARYA].setProperties((char*)("Заря"),					1000,				5,			50,			50,				50,			50,			25,			4);

GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_SEVA].setProperties((char*)("Сева"),					2000,				10,			70,			90,				80,			90,			50,			5);
GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_MONOLIT].setProperties((char*)("комбез.Монолит"),		1250,				10,			50,			60,				50,			50,			25,			2);
GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_KOZH].setProperties((char*)("Кожанка"),				1000,				0,			10,			10,				10,			5,			0,			2);
GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_KOZH1].setProperties((char*)("Кожанка*"),				1500,				5,			30,			30,				30,			30,			10,			3);
GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_BANDOS].setProperties((char*)("Банд.куртка"),			900,				0,			10,			10,				10,			5,			0,			2);
GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_BANDOS1].setProperties((char*)("Банд.куртка*"),		1250,				5,			40,			40,				40,			40,			15,			3);
GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_ECOLOG].setProperties((char*)("ССП-99 Эколог"),		1000,				10,			90,			90,				90,			90,			50,			5);
GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_BERYL].setProperties((char*)("Берилл-5М"),			2000,				10,			30,			30,				30,			30,			20,			2);
GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_BRONE].setProperties((char*)("Арм.Бронежилет"),		1500,				0,			10,			10,				10,			10,			0,			2);
GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_HALAT].setProperties((char*)("Научн.Халат"),			400,				5,			30,			30,				30,			30,			5,			2);
*/
#endif

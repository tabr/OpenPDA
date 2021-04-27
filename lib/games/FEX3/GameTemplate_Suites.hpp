#ifndef GAME_SUITS_H
#define GAME_SUITS_H

#ifdef DEBUG_BUILD
	LcdStringUpdate(1,LCD_LINE_2, (char*)"Suits        ");
#endif
//!!!!!!!!!!!АХТУНГ!!! строка ОБЯЗАТЕЛЬНО должна заканчиваться на 0х00
//	GameCFG.load();
//														имя														[макс.прочность]	[макс.контейнеров]	[защ.пси]	[защ.хим]	[защ.электро]	[защ.огонь]	[защ.рад]	[защ.грав]
//GameCFG.SuitsContainer.setContainerSize(TemporaryClass::SUIT_ID_SIZE);
//GameCFG.SuitsContainer.setContainerSize(6);//include "0"
//DamageDefenceValue_t defTmp[GameCFG.GetDamageSourceNum()];
//GameCharacteristicsClass c(0);
//c	= GameCharacteristicsClass(1<<GameCharacteristicsClass::CHARACTERISTIC_DURABILITY | 1<<GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS);
//c.SetUsingCharacteristic(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY);
//c.SetUsingCharacteristic(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS);

DamageSourceContainerClass*	SuitDef		= NULL;
GameCharacteristicsClass*	Suitc		= NULL;
SuitTemplateInstance* Suit				= NULL;
/*
SuitDef		= new DamageSourceContainerClass(GameCFG.GetDamageSourceNum());
Suitc		= new GameCharacteristicsClass();
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_NONE,						11);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC,					12);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL,			13);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL,	14);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_FIRE,						15);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_ELECTRICITY,				16);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_CHEMICAL,					17);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GRAVY,						18);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_PSY,						19);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BIO,						20);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT,					21);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY, 101);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS, 1);
Suit		= new SuitTemplateInstance(TemporaryClass::SUIT_ID::SUIT_ID_NONE, (char*)("(пусто)"),	SuitDef,	Suitc);
GameCFG.SuitsContainer.RegisterNew(Suit);



SuitDef		= new DamageSourceContainerClass(GameCFG.GetDamageSourceNum());
Suitc		= new GameCharacteristicsClass();
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_NONE,						31);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC,					32);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL,			33);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL,	34);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_FIRE,						35);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_ELECTRICITY,				36);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_CHEMICAL,					37);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GRAVY,						38);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_PSY,						39);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BIO,						40);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT,					41);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY, 102);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS, 3);
Suit		= new SuitTemplateInstance(TemporaryClass::SUIT_ID::SUIT_ID_ZARYA, (char*)("Заря"),	SuitDef,	Suitc);
GameCFG.SuitsContainer.RegisterNew(Suit);
*/


SuitDef		= new DamageSourceContainerClass(GameCFG.GetDamageSourceNum());
Suitc		= new GameCharacteristicsClass();
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_NONE,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC,					0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL,			0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL,	0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_FIRE,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_ELECTRICITY,				0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_CHEMICAL,					0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GRAVY,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_PSY,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BIO,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT,					0);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY, 0);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS, 0);
Suit		= new SuitTemplateInstance(TemporaryClass::SUIT_ID::SUIT_ID_NONE, (char*)("(пусто)"),	SuitDef,	Suitc);
GameCFG.SuitsContainer.RegisterNew(Suit);


SuitDef		= new DamageSourceContainerClass();
Suitc		= new GameCharacteristicsClass();
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_NONE,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC,					0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL,			30);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL,	0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_FIRE,						30);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_ELECTRICITY,				30);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_CHEMICAL,					30);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GRAVY,						10);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_PSY,						5);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BIO,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT,					0);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY, 301);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS, 3);
Suit	= new SuitTemplateInstance(TemporaryClass::SUIT_ID::SUIT_ID_ZARYA, (char*)("Заря"),	SuitDef,	Suitc);
GameCFG.SuitsContainer.RegisterNew(Suit);

SuitDef		= new DamageSourceContainerClass();
Suitc		= new GameCharacteristicsClass();
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_NONE,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC,					0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL,			90);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL,	0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_FIRE,						80);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_ELECTRICITY,				90);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_CHEMICAL,					70);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GRAVY,						50);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_PSY,						10);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BIO,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT,					0);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY, 602);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS, 5);
Suit	= new SuitTemplateInstance(TemporaryClass::SUIT_ID::SUIT_ID_SEVA, (char*)("Сева"),	SuitDef,	Suitc);
GameCFG.SuitsContainer.RegisterNew(Suit);

SuitDef		= new DamageSourceContainerClass();
Suitc		= new GameCharacteristicsClass();
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_NONE,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC,					0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL,			60);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL,	0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_FIRE,						80);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_ELECTRICITY,				90);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_CHEMICAL,					70);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GRAVY,						50);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_PSY,						40);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BIO,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT,					0);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY, 603);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS, 4);
Suit	= new SuitTemplateInstance(TemporaryClass::SUIT_ID::SUIT_ID_EXO, (char*)("Экзоскелет"),	SuitDef,	Suitc);
GameCFG.SuitsContainer.RegisterNew(Suit);

SuitDef		= new DamageSourceContainerClass();
Suitc		= new GameCharacteristicsClass();
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_NONE,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC,					0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL,			90);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL,	0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_FIRE,						80);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_ELECTRICITY,				90);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_CHEMICAL,					70);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GRAVY,						50);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_PSY,						60);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BIO,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT,					0);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY, 604);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS, 4);
Suit	= new SuitTemplateInstance(TemporaryClass::SUIT_ID::SUIT_ID_MONOLIT_EXO, (char*)("Монол.Экзо"),	SuitDef,	Suitc);
GameCFG.SuitsContainer.RegisterNew(Suit);

SuitDef		= new DamageSourceContainerClass();
Suitc		= new GameCharacteristicsClass();
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_NONE,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC,					0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL,			10);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL,	0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_FIRE,						10);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_ELECTRICITY,				10);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_CHEMICAL,					10);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GRAVY,						5);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_PSY,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BIO,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT,					0);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY, 605);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS, 1);
Suit	= new SuitTemplateInstance(TemporaryClass::SUIT_ID::SUIT_ID_NEWBE, (char*)("Кост.Новичка"),	SuitDef,	Suitc);
GameCFG.SuitsContainer.RegisterNew(Suit);



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

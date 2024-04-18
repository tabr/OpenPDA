#ifndef GAME_SUITS_H
#define GAME_SUITS_H

#ifdef DEBUG_BUILD
	LcdStringUpdate(1,LCD_LINE_2, (char*)"Suits        ");
#endif

DamageSourceContainerClass*	SuitDef		= NULL;
GameCharacteristicsClass*	Suitc		= NULL;
SuitTemplateInstance* Suit				= NULL;


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
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL,			10);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL,	0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_FIRE,						10);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_ELECTRICITY,				10);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_CHEMICAL,					10);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GRAVY,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_PSY,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BIO,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT,					0);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY, 300);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS, 1);
Suit	= new SuitTemplateInstance(TemporaryClass::SUIT_ID::SUIT_ID_ZARYA, (char*)("Заря"),	SuitDef,	Suitc);
GameCFG.SuitsContainer.RegisterNew(Suit);

SuitDef		= new DamageSourceContainerClass();
Suitc		= new GameCharacteristicsClass();
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_NONE,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC,					0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL,			80);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL,	0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_FIRE,						50);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_ELECTRICITY,				60);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_CHEMICAL,					60);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GRAVY,						30);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_PSY,						30);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BIO,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT,					0);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY, 500);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS, 5);
Suit	= new SuitTemplateInstance(TemporaryClass::SUIT_ID::SUIT_ID_SEVA, (char*)("Сева"),	SuitDef,	Suitc);
GameCFG.SuitsContainer.RegisterNew(Suit);

SuitDef		= new DamageSourceContainerClass();
Suitc		= new GameCharacteristicsClass();
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_NONE,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC,					0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL,			10);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL,	0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_FIRE,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_ELECTRICITY,				0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_CHEMICAL,					0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GRAVY,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_PSY,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BIO,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT,					0);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY, 300);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS, 1);
Suit	= new SuitTemplateInstance(TemporaryClass::SUIT_ID::SUIT_ID_EXO, (char*)("Куртка бандита"),	SuitDef,	Suitc);
GameCFG.SuitsContainer.RegisterNew(Suit);

#endif

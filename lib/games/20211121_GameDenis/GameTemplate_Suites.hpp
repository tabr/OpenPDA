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
Suit		= new SuitTemplateInstance(TemporaryClass::SUIT_ID::SUIT_ID_NONE, (char*)("(ÔÛÒÚÓ)"),	SuitDef,	Suitc);
GameCFG.SuitsContainer.RegisterNew(Suit);


SuitDef		= new DamageSourceContainerClass();
Suitc		= new GameCharacteristicsClass();
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_NONE,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC,					0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL,			50);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL,	0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_FIRE,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_ELECTRICITY,				0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_CHEMICAL,					0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GRAVY,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_PSY,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BIO,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT,					0);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY, 10000);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS, 0);
Suit	= new SuitTemplateInstance(TemporaryClass::SUIT_ID::SUIT_ID_RHBZ_50, (char*)("–’¡« 50"),	SuitDef,	Suitc);
GameCFG.SuitsContainer.RegisterNew(Suit);

SuitDef		= new DamageSourceContainerClass();
Suitc		= new GameCharacteristicsClass();
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_NONE,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC,					0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL,			75);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL,	0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_FIRE,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_ELECTRICITY,				0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_CHEMICAL,					0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GRAVY,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_PSY,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BIO,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT,					0);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY, 10000);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS, 0);
Suit	= new SuitTemplateInstance(TemporaryClass::SUIT_ID::SUIT_ID_RHBZ_75, (char*)("–’¡« 75"),	SuitDef,	Suitc);
GameCFG.SuitsContainer.RegisterNew(Suit);

SuitDef		= new DamageSourceContainerClass();
Suitc		= new GameCharacteristicsClass();
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_NONE,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC,					0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL,			90);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL,	0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_FIRE,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_ELECTRICITY,				0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_CHEMICAL,					0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GRAVY,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_PSY,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BIO,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT,					0);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY, 10000);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS, 0);
Suit	= new SuitTemplateInstance(TemporaryClass::SUIT_ID::SUIT_ID_RHBZ_90, (char*)("–’¡« 90"),	SuitDef,	Suitc);
GameCFG.SuitsContainer.RegisterNew(Suit);

SuitDef		= new DamageSourceContainerClass();
Suitc		= new GameCharacteristicsClass();
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_NONE,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC,					0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL,			99);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL,	0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_FIRE,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_ELECTRICITY,				0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_CHEMICAL,					0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GRAVY,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_PSY,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BIO,						0);
SuitDef->SetDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_BLOWOUT,					0);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY, 10000);
Suitc->Set(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS, 0);
Suit	= new SuitTemplateInstance(TemporaryClass::SUIT_ID::SUIT_ID_RHBZ_99, (char*)("–’¡« 99"),	SuitDef,	Suitc);
GameCFG.SuitsContainer.RegisterNew(Suit);


#endif

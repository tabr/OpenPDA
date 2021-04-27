// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*void PlayerEffectsClass::PlayerEffectsClassTask1::Task(void)
	{
	//PlayerEffects.process();
	((PlayerEffectsClass*)this->GetLinkedObject())->process();
	}*/
void PlayerEffectsOldClass::TimerUpdateEvent (uint8_t msPassed)
	{
	static uint16_t process_msCounter=0;

	process_msCounter+=msPassed;

	if (process_msCounter >= 1000)
		{
		process_msCounter -= 1000;
		this->process();
		}
	}
const uint8_t PlayerEffectsOldClass::effectsTimings[PlayerEffectsOldClass::EFFECTS_NUM][EFFECTS_PARAMETERS_NUM]=
	{
	//PERIOD_SEC, TICKCS
	{0,  TIMER_VALUE_EXPIRED},//none
	{2,  TIMER_VALUE_INFINITY},//медуза
	{3,  TIMER_VALUE_INFINITY},//кам.цветок
	{1,  TIMER_VALUE_INFINITY},//вспышка
	{3,  TIMER_VALUE_INFINITY},//огн.шар
	{5,  TIMER_VALUE_INFINITY},//пленка
	{3,  TIMER_VALUE_INFINITY},//пустышка
	{3,  TIMER_VALUE_INFINITY},//лун.свет
	{5,  TIMER_VALUE_INFINITY},//кристалл
	{5,  TIMER_VALUE_INFINITY},//морской ёж
	{5,  TIMER_VALUE_INFINITY},//душа
	{1,  30},//аптечка
	{0,  TIMER_VALUE_EXPIRED},//бандаж
	{1,  30},//антирад
	{1,  TIMER_VALUE_EXPIRED},//водка
	{60, 10},//60х10 = 10мин - ПСИ блокада
	{60, 20},//60х20 = 20мин - Радио Протектор
	{60, 10},//60х10 = 10мин - ЕДА
	{0,  TIMER_VALUE_EXPIRED},//ремкомплект
	{0,  TIMER_VALUE_EXPIRED},//детали
	{15, 1},//SAFE_SHELTER 60x1 = 1мин
	};
PlayerEffectsOldClass::PlayerEffectsOldClass(void)
	{
	this->ActiveEffects		= 0;
	//			effectsTimings123={1,2};
	//			for (uint8_t i=0;i<this->EFFECTS_NUM;i++)
	for (uint8_t currentPoolID=0;currentPoolID<this->EFFECTS_NUM;currentPoolID++)
		{
		//				this->List[i][this->PARAMETER_TIMER]							= 0;
		//				this->List[i][this->PARAMETER_POWER]							= 0;
		//				this->List[i][this->PARAMETER_DELAY]							= 0;

		//				this->List[i][this->PARAMETER_TICKS]							= 0;//кол-во тиков
		//				this->List[i][this->PARAMETER_DELAY_COUNTER]					= 0;//задержка между тиками
		//				this->List[i][this->PARAMETER_DELAY_COUNTER]					= 0;//задержка между тиками

		this->EffectsPool[currentPoolID][this->PARAMETER_TICKS]			= 0;//кол-во тиков
		this->EffectsPool[currentPoolID][this->PARAMETER_DELAY_COUNTER]	= 0;//задержка между тиками
		this->EffectsPool[currentPoolID][this->PARAMETER_DELAY_COUNTER]	= 0;//задержка между тиками
		}
	//this->TaskPlayerEffectsProcess.SetLinkedObject(this);
	}

uint8_t PlayerEffectsOldClass::GetActiveVisibleList(uint8_t *data)
	{
	uint8_t num=0,effectID=0;
//	for (uint8_t effectID=0; effectID<this->EFFECTS_NUM; effectID++)
	for (uint8_t curentPoolID=0; curentPoolID<this->POOL_SIZE; curentPoolID++)
		{
		if (this->IsEffectPoolActive(curentPoolID))
			{
			effectID	= this->EffectsPool[curentPoolID][this->PARAMETER_EFFECT_ID];
			if (this->IsVisible(effectID))
				{
				data[num++]	= effectID;
				}
			}
		}
	return num;
	}

bool PlayerEffectsOldClass::IsVisible (uint8_t effectID)
	{
	if (effectID <= TemporaryClass::EFFECTID_ITEM_SHIFT)
		{
		return false;
		}
	//			if (effectID == this->EFFECTID_ITEM_BANDAGE)
	//				return false;
	//			if (effectID == this->EFFECTID_ITEM_VODKA)
	//				return false;
	return true;
	}

bool PlayerEffectsOldClass::IsEffectPoolActive (uint8_t poolID)
	{
	return (this->EffectsPool[poolID][this->PARAMETER_EFFECT_ID] != this->EFFECTID_NONE);
	}
bool PlayerEffectsOldClass::CanBeApplied(EffectID_t EID)
	{
	return !(this->IsEffectActiveInPool(EID));
	}
//bool PlayerEffectsClass::isEffectActive (uint8_t effectID, uint8_t source)
bool PlayerEffectsOldClass::IsEffectActiveInPool (EffectID_t EID)
	{
	uint8_t tmp;
	return this->IsEffectActiveInPool(EID, tmp);
	}
//bool PlayerEffectsClass::isEffectActiveInPool (EffectID EID, uint8_t* poolID)
bool PlayerEffectsOldClass::IsEffectActiveInPool (EffectID_t EID, uint8_t& poolID)
	{
//	return (this->List[effectID][this->PARAMETER_STATUS] & this->EFFECT_STATUS_APPLIED_bm);
	for (uint8_t currentPoolID=0;currentPoolID < this->POOL_SIZE;currentPoolID++)
		{
		if (this->EffectsPool[currentPoolID][PARAMETER_EFFECT_ID] == EID)
			{
//			if (poolID!= NULL)
//				{
//				*poolID	= currentPoolID;
//				}
			poolID	= currentPoolID;
			return true;
			}
		}
	return false;
	}
uint8_t PlayerEffectsOldClass::getFreePoolID(void)
	{
//	for (uint8_t currentPoolID=this->;currentPoolID<this->POOL_SIZE;currentPoolID++)
	for (uint8_t currentPoolID=this->SOURCE_ARTEFACT_SLOT_MAX+1; currentPoolID < this->POOL_SIZE; currentPoolID++)
		{
		if (this->EffectsPool[currentPoolID][PARAMETER_EFFECT_ID] == this->EFFECTID_NONE)
			{
			return currentPoolID;
			}
		}
	return 0;//Error
	}
void PlayerEffectsOldClass::renewEffect(EffectID_t EID)
	{
	uint8_t poolID=0;
	if (this->IsEffectActiveInPool(EID, poolID))
//	if (this->isEffectActiveInPool(EID, &poolID))
		{
		this->EffectsPool[poolID][this->PARAMETER_TICKS]			= this->effectsTimings[EID][EFFECTS_PARAMETER_TICKS];
		this->EffectsPool[poolID][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EID][EFFECTS_PARAMETER_DELAY];
		}
	else
		{
		this->applyEffect(EID, EFFECT_SOURCE_ANY);
		}
	}
void PlayerEffectsOldClass::applyEffect (EffectID_t EID, EFFECT_SOURCE selectedEffectSource)
	{
	uint8_t effectSource	= selectedEffectSource;
	//uint8_t	freePoolID;
//	Все эффекты обрабатываются в "PlayerClass::getDefence[Psy/Rad/...](void)"
//	if (this->isEffectActive(effectID))
//		{
//		return;
//		}
	this->ActiveEffects++;
	if (effectSource > this->SOURCE_ARTEFACT_SLOT_MAX)
		{
		effectSource	= this->getFreePoolID();//на глюке сэкономил переменную=)))
		}
//	else
//		{
//		freePoolID	= source;
//		}

	//sbi(this->List[effectID][this->PARAMETER_STATUS],this->EFFECT_STATUS_APPLIED_bp);
	this->EffectsPool[effectSource][this->PARAMETER_EFFECT_ID]	= EID;
	
//	if (this->List[effectID][this->PARAMETER_TICKS] < this->TIMER_VALUE_MAX)
//	if (this->EffectsPool[effectSource][this->PARAMETER_TICKS] < this->TIMER_VALUE_MAX)
		{
//						sprintf (lcd_buf, "234");
//						LcdString(1,LCD_LINE_1);
//						LcdUpdate();
//						delay_ms(1000);
		switch (this->EffectsPool[effectSource][this->PARAMETER_EFFECT_ID])
			{
			case EFFECTID_ARTEFACT_MEDUSA:
//				this->List[effectID][this->PARAMETER_TICKS]						= this->TIMER_VALUE_INFINITY;
//				this->List[effectID][this->PARAMETER_DELAY_COUNTER]				= this->effectsTimings[EFFECTID_ARTEFACT_MEDUSA];//каждые 1 сек  -2 ед дозы радиации
				this->EffectsPool[effectSource][this->PARAMETER_TICKS]			= this->effectsTimings[EFFECTID_ARTEFACT_MEDUSA][EFFECTS_PARAMETER_TICKS];
				this->EffectsPool[effectSource][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ARTEFACT_MEDUSA][EFFECTS_PARAMETER_DELAY];//каждые 2 сек  -1 ед дозы радиации
			break;

			case EFFECTID_ARTEFACT_KAM_CVETOK:
//				this->List[effectID][this->PARAMETER_TICKS]						= this->TIMER_VALUE_INFINITY;
//				this->List[effectID][this->PARAMETER_DELAY_COUNTER]				= this->effectsTimings[EFFECTID_ARTEFACT_KAM_CVETOK];//каждые 1 сек 1 ед дозы радиации
				this->EffectsPool[effectSource][this->PARAMETER_TICKS]			= this->TIMER_VALUE_INFINITY;
				this->EffectsPool[effectSource][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ARTEFACT_KAM_CVETOK][EFFECTS_PARAMETER_DELAY];//каждые 1 сек 1 ед дозы радиации
			break;

			case EFFECTID_ARTEFACT_VSPYSHKA:
//				this->List[effectID][this->PARAMETER_TICKS]						= this->TIMER_VALUE_INFINITY;
//				this->List[effectID][this->PARAMETER_DELAY_COUNTER]				= this->effectsTimings[EFFECTID_ARTEFACT_VSPYSHKA];//каждые 1 сек 2 ед дозы радиации
				this->EffectsPool[effectSource][this->PARAMETER_TICKS]			= this->TIMER_VALUE_INFINITY;
				this->EffectsPool[effectSource][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ARTEFACT_VSPYSHKA][EFFECTS_PARAMETER_DELAY];//каждые 1 сек 2 ед дозы радиации
			break;

			case EFFECTID_ARTEFACT_OGN_SHAR:
//				this->List[effectID][this->PARAMETER_TICKS]						= this->TIMER_VALUE_INFINITY;
//				this->List[effectID][this->PARAMETER_DELAY_COUNTER]				= this->effectsTimings[EFFECTID_ARTEFACT_OGN_SHAR];//каждые 1 сек 2 ед дозы радиации
				this->EffectsPool[effectSource][this->PARAMETER_TICKS]			= this->TIMER_VALUE_INFINITY;
				this->EffectsPool[effectSource][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ARTEFACT_OGN_SHAR][EFFECTS_PARAMETER_DELAY];//каждые 1 сек 2 ед дозы радиации
			break;

			case EFFECTID_ARTEFACT_PLENKA:
//				this->List[effectID][this->PARAMETER_TICKS]						= this->TIMER_VALUE_INFINITY;
//				this->List[effectID][this->PARAMETER_DELAY_COUNTER]				= this->effectsTimings[EFFECTID_ARTEFACT_PLENKA];//каждые 1 сек 2 ед дозы радиации
				this->EffectsPool[effectSource][this->PARAMETER_TICKS]			= this->TIMER_VALUE_INFINITY;
				this->EffectsPool[effectSource][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ARTEFACT_PLENKA][EFFECTS_PARAMETER_DELAY];//каждые 1 сек 2 ед дозы радиации
			break;

			case EFFECTID_ARTEFACT_PUSTIWKA:
//				this->List[effectID][this->PARAMETER_TICKS]					= this->TIMER_VALUE_EXPIRED;
//				this->EffectsPool[effectSource][this->PARAMETER_TICKS]			= this->TIMER_VALUE_EXPIRED;
				this->EffectsPool[effectSource][this->PARAMETER_TICKS]			= this->TIMER_VALUE_INFINITY;
				this->EffectsPool[effectSource][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ARTEFACT_PUSTIWKA][EFFECTS_PARAMETER_DELAY];//каждые 1 сек 2 ед дозы радиации
			break;

			case EFFECTID_ARTEFACT_LUN_SVET:
				this->EffectsPool[effectSource][this->PARAMETER_TICKS]			= this->TIMER_VALUE_INFINITY;
				this->EffectsPool[effectSource][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ARTEFACT_LUN_SVET][EFFECTS_PARAMETER_DELAY];//каждые 1 сек 4 ед дозы радиации
			break;

			case EFFECTID_ARTEFACT_KRYSTAL:
				this->EffectsPool[effectSource][this->PARAMETER_TICKS]			= this->TIMER_VALUE_INFINITY;
				this->EffectsPool[effectSource][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ARTEFACT_KRYSTAL][EFFECTS_PARAMETER_DELAY];
			break;

			case EFFECTID_ARTEFACT_MORSKOI_EZH:
				this->EffectsPool[effectSource][this->PARAMETER_TICKS]			= this->TIMER_VALUE_INFINITY;
				this->EffectsPool[effectSource][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ARTEFACT_MORSKOI_EZH][EFFECTS_PARAMETER_DELAY];
			break;

			case EFFECTID_ARTEFACT_DUWA:
//				this->List[effectID][this->PARAMETER_TICKS]						= this->TIMER_VALUE_INFINITY;
//				this->List[effectID][this->PARAMETER_DELAY_COUNTER]				= this->effectsTimings[EFFECTID_ARTEFACT_DUWA];
				this->EffectsPool[effectSource][this->PARAMETER_TICKS]			= this->TIMER_VALUE_INFINITY;
				this->EffectsPool[effectSource][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ARTEFACT_DUWA][EFFECTS_PARAMETER_DELAY];
			break;

			case EFFECTID_ITEM_FIRST_AID:
				/*sprintf (lcd_buf, "[%03d]", this->EffectsPool[effectSource][this->PARAMETER_TICKS]);
				LcdString(1,LCD_LINE_6);
				LcdUpdate();*/
//				this->List[effectID][this->PARAMETER_TICKS]						= 30+(++randomPseudo%16);
//				this->List[effectID][this->PARAMETER_DELAY_COUNTER]				= this->effectsTimings[EFFECTID_ITEM_FIRST_AID];
				this->EffectsPool[effectSource][this->PARAMETER_TICKS]			= 30+(RandomPseudo.get()%20);
				this->EffectsPool[effectSource][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ITEM_FIRST_AID][EFFECTS_PARAMETER_DELAY];
				/*sprintf (lcd_buf, "t=[%03d%03d]", this->EffectsPool[0][this->PARAMETER_TICKS], effectSource);
				LcdString(6,LCD_LINE_6);
				LcdUpdate();
				delay_ms(1000);
				while(1);*/
			break;

			case EFFECTID_ITEM_BANDAGE:
//				this->List[effectID][this->PARAMETER_TICKS]						= this->TIMER_VALUE_EXPIRED;
				this->EffectsPool[effectSource][this->PARAMETER_TICKS]			= this->TIMER_VALUE_EXPIRED;
				Player.HealthIncrase(6+(RandomPseudo.get()%4));
			break;

			case EFFECTID_ITEM_ANTIRAD:
//				this->List[effectID][this->PARAMETER_TICKS]						= 30+(++randomPseudo%16);
//				this->List[effectID][this->PARAMETER_DELAY_COUNTER]				= this->effectsTimings[EFFECTID_ITEM_ANTIRAD];
				this->EffectsPool[effectSource][this->PARAMETER_TICKS]			= 30+(RandomPseudo.get()%20);
				this->EffectsPool[effectSource][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ITEM_ANTIRAD][EFFECTS_PARAMETER_DELAY];
			break;

			case EFFECTID_ITEM_VODKA:
//				this->List[effectID][this->PARAMETER_TICKS]						= this->TIMER_VALUE_EXPIRED;
				this->EffectsPool[effectSource][this->PARAMETER_TICKS]			= this->TIMER_VALUE_EXPIRED;
				/*#warning remove this!
				if (Player.getFactionID() == PlayerClass::FACTION_BANDIT)
					Player.dealDamage(TemporaryClass::VODKA_DAMAGE/2, DamageClass::DAMAGE_SOURCE_GENERIC, PlayerClass::AGRESSOR_TYPE_VODKA, PlayerClass::AGGRESSOR_SUBTYPE_NONE, DamageClass::AGGRESSOR_SOURCE_INTERNAL);
				else
				*/
					Player.DealDamage(TemporaryClass::VODKA_DAMAGE,   TemporaryClass::DAMAGE_SOURCE_GENERIC, DamageClass::AGGRESSOR_SOURCE::AGGRESSOR_SOURCE_INTERNAL);
				Player.RadDoseDecrase(TemporaryClass::VODKA_RAD_DECRASE);
			break;

			case EFFECTID_ITEM_PSY_BLOKADA:
//				this->List[effectID][this->PARAMETER_TICKS]						= 5;
//				this->List[effectID][this->PARAMETER_DELAY_COUNTER]				= this->effectsTimings[EFFECTID_ITEM_PSY_BLOKADA];
				this->EffectsPool[effectSource][this->PARAMETER_TICKS]			= 10;
				this->EffectsPool[effectSource][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ITEM_PSY_BLOKADA][EFFECTS_PARAMETER_DELAY];
			break;

			case EFFECTID_ITEM_RAD_PROTECTOR:
//				this->List[effectID][this->PARAMETER_TICKS]						= 5;
//				this->List[effectID][this->PARAMETER_DELAY_COUNTER]				= this->effectsTimings[EFFECTID_ITEM_RAD_PROTECTOR];
				this->EffectsPool[effectSource][this->PARAMETER_TICKS]			= 20;
				this->EffectsPool[effectSource][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ITEM_RAD_PROTECTOR][EFFECTS_PARAMETER_DELAY];
			break;

			case EFFECTID_ITEM_FOOD:
				this->EffectsPool[effectSource][this->PARAMETER_TICKS]			= 10;
				this->EffectsPool[effectSource][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ITEM_FOOD][EFFECTS_PARAMETER_DELAY];
			break;

			case EFFECTID_SAFE_SHELTER:
				this->EffectsPool[effectSource][this->PARAMETER_TICKS]			= 1;
				this->EffectsPool[effectSource][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_SAFE_SHELTER][EFFECTS_PARAMETER_DELAY];
			break;

			}
		}
	}
void PlayerEffectsOldClass::removeFromPool(uint8_t poolID)
	{
	this->ActiveEffects--;
	this->EffectsPool[poolID][this->PARAMETER_EFFECT_ID]		= this->EFFECTID_NONE;
	this->EffectsPool[poolID][this->PARAMETER_TICKS]			= 0;
	this->EffectsPool[poolID][this->PARAMETER_DELAY_COUNTER]	= 0;
	}
void PlayerEffectsOldClass::tickPool(uint8_t poolID)
	{
	/*sprintf (lcd_buf, "tickPool[%03d]", poolID);
	LcdString(1,LCD_LINE_5);
	LcdUpdate();
	while(1);*/
	switch (this->EffectsPool[poolID][this->PARAMETER_EFFECT_ID])
		{
		case EFFECTID_ARTEFACT_MEDUSA:
//			this->List[effectID][this->PARAMETER_DELAY_COUNTER]			= this->effectsTimings[EFFECTID_ARTEFACT_MEDUSA];
			this->EffectsPool[poolID][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ARTEFACT_MEDUSA][EFFECTS_PARAMETER_DELAY];
			Player.RadDoseDecrase(1);
			//Player.PlayerInvironmentAction(PLAYER_ENVIRONMENT_ACTION_PLAYER_RAD_DOSE_DECREASE, 1);
		break;

		case EFFECTID_ARTEFACT_KAM_CVETOK:
			//обновить счетчик
//			this->List[effectID][this->PARAMETER_DELAY_COUNTER]			= this->effectsTimings[EFFECTID_ARTEFACT_KAM_CVETOK];
			this->EffectsPool[poolID][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ARTEFACT_KAM_CVETOK][EFFECTS_PARAMETER_DELAY];
			Player.RadDoseIncrase(1);
			//Player.PlayerInvironmentAction(PLAYER_ENVIRONMENT_ACTION_PLAYER_RAD_DOSE_INCREASE, 1);
		break;

		case EFFECTID_ARTEFACT_VSPYSHKA:
//			this->List[effectID][this->PARAMETER_DELAY_COUNTER]			= this->effectsTimings[EFFECTID_ARTEFACT_VSPYSHKA];
			this->EffectsPool[poolID][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ARTEFACT_VSPYSHKA][EFFECTS_PARAMETER_DELAY];
			Player.RadDoseIncrase(1);
			//Player.PlayerInvironmentAction(PLAYER_ENVIRONMENT_ACTION_PLAYER_RAD_DOSE_INCREASE, 1);
		break;

		case EFFECTID_ARTEFACT_OGN_SHAR:
//			this->List[effectID][this->PARAMETER_DELAY_COUNTER]			= this->effectsTimings[EFFECTID_ARTEFACT_OGN_SHAR];
			this->EffectsPool[poolID][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ARTEFACT_OGN_SHAR][EFFECTS_PARAMETER_DELAY];
			Player.RadDoseIncrase(1);
			//Player.PlayerInvironmentAction(PLAYER_ENVIRONMENT_ACTION_PLAYER_RAD_DOSE_INCREASE, 1);
		break;

		case EFFECTID_ARTEFACT_PLENKA:
//			this->List[effectID][this->PARAMETER_DELAY_COUNTER]			= this->effectsTimings[EFFECTID_ARTEFACT_PLENKA];
			this->EffectsPool[poolID][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ARTEFACT_PLENKA][EFFECTS_PARAMETER_DELAY];
			Player.RadDoseIncrase(1);
			//Player.PlayerInvironmentAction(PLAYER_ENVIRONMENT_ACTION_PLAYER_RAD_DOSE_INCREASE, 1);
		break;

		case EFFECTID_ARTEFACT_PUSTIWKA:
//			this->List[effectID][this->PARAMETER_DELAY_COUNTER]			= this->effectsTimings[EFFECTID_ARTEFACT_PLENKA];
			this->EffectsPool[poolID][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ARTEFACT_PUSTIWKA][EFFECTS_PARAMETER_DELAY];
			Player.RadDoseIncrase(1);
			//Player.PlayerInvironmentAction(PLAYER_ENVIRONMENT_ACTION_PLAYER_RAD_DOSE_INCREASE, 1);
		break;

		case EFFECTID_ARTEFACT_LUN_SVET:
			this->EffectsPool[poolID][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ARTEFACT_LUN_SVET][EFFECTS_PARAMETER_DELAY];
			Player.RadDoseIncrase(2);
			//Player.PlayerInvironmentAction(PLAYER_ENVIRONMENT_ACTION_PLAYER_RAD_DOSE_INCREASE, 2);
		break;

		case EFFECTID_ARTEFACT_KRYSTAL:
			this->EffectsPool[poolID][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ARTEFACT_KRYSTAL][EFFECTS_PARAMETER_DELAY];
			Player.RadDoseDecrase(1);
			Player.HealthIncrase(1);
			//Player.PlayerInvironmentAction(PLAYER_ENVIRONMENT_ACTION_PLAYER_RAD_DOSE_DECREASE, 1);
			//Player.PlayerInvironmentAction(PLAYER_ENVIRONMENT_ACTION_PLAYER_HEALTH_INCREASE, 1);
		break;

		case EFFECTID_ARTEFACT_MORSKOI_EZH:
			this->EffectsPool[poolID][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ARTEFACT_MORSKOI_EZH][EFFECTS_PARAMETER_DELAY];
			Player.RadDoseIncrase(1);
			Player.HealthIncrase(1);
			//Player.PlayerInvironmentAction(PLAYER_ENVIRONMENT_ACTION_PLAYER_RAD_DOSE_INCREASE, 1);
			//Player.PlayerInvironmentAction(PLAYER_ENVIRONMENT_ACTION_PLAYER_HEALTH_INCREASE, 1);
		break;

		case EFFECTID_ARTEFACT_DUWA:
//			this->List[effectID][this->PARAMETER_DELAY_COUNTER]			= this->effectsTimings[EFFECTID_ARTEFACT_DUWA];
			this->EffectsPool[poolID][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ARTEFACT_DUWA][EFFECTS_PARAMETER_DELAY];
			Player.RadDoseIncrase(1);
			Player.HealthIncrase(1);
			//Player.PlayerInvironmentAction(PLAYER_ENVIRONMENT_ACTION_PLAYER_RAD_DOSE_INCREASE, 1);
			//Player.PlayerInvironmentAction(PLAYER_ENVIRONMENT_ACTION_PLAYER_HEALTH_INCREASE, 1);
		break;

		case EFFECTID_ITEM_FIRST_AID:
//			this->List[effectID][this->PARAMETER_DELAY_COUNTER]			= this->effectsTimings[EFFECTID_ITEM_FIRST_AID];
			this->EffectsPool[poolID][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ITEM_FIRST_AID][EFFECTS_PARAMETER_DELAY];
			Player.HealthIncrase(1);
			//Player.PlayerInvironmentAction(PLAYER_ENVIRONMENT_ACTION_PLAYER_HEALTH_INCREASE, 1);
		break;

		case EFFECTID_ITEM_BANDAGE:
			//none
		break;

		case EFFECTID_ITEM_ANTIRAD:
//			this->List[effectID][this->PARAMETER_DELAY_COUNTER]			= this->effectsTimings[EFFECTID_ITEM_ANTIRAD];
			this->EffectsPool[poolID][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ITEM_ANTIRAD][EFFECTS_PARAMETER_DELAY];
			Player.RadDoseDecrase(1);
			//Player.PlayerInvironmentAction(PLAYER_ENVIRONMENT_ACTION_PLAYER_RAD_DOSE_DECREASE, 1);
		break;

		case EFFECTID_ITEM_VODKA:
			//none
		break;

		case EFFECTID_ITEM_PSY_BLOKADA:
//			this->List[effectID][this->PARAMETER_DELAY_COUNTER]			= this->effectsTimings[EFFECTID_ITEM_PSY_BLOKADA];
			this->EffectsPool[poolID][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ITEM_PSY_BLOKADA][EFFECTS_PARAMETER_DELAY];
		break;

		case EFFECTID_ITEM_RAD_PROTECTOR:
//			this->List[effectID][this->PARAMETER_DELAY_COUNTER]			= this->effectsTimings[EFFECTID_ITEM_RAD_PROTECTOR];
			this->EffectsPool[poolID][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ITEM_RAD_PROTECTOR][EFFECTS_PARAMETER_DELAY];
		break;

		case EFFECTID_ITEM_FOOD:
			this->EffectsPool[poolID][this->PARAMETER_DELAY_COUNTER]	= this->effectsTimings[EFFECTID_ITEM_FOOD][EFFECTS_PARAMETER_DELAY];
		break;
		}
	}
void PlayerEffectsOldClass::removeAll ()
	{
	//return;
//	for (uint8_t effectID=0;effectID<this->EFFECTS_NUM;effectID++)
	for (uint8_t currentPoolID=0;currentPoolID<this->POOL_SIZE;currentPoolID++)
		{
		//		if (this->List[effectID][this->PARAMETER_TICKS] != this->TIMER_VALUE_EXPIRED)
		if (this->IsEffectPoolActive(currentPoolID))
			this->removeFromPool(currentPoolID);
		}
	}
void PlayerEffectsOldClass::process (void)
	{
	if (Player.IsDead())//нет на мёртвых никаких эффектов... пока
		{
		return;
		}
	
	for (uint8_t currentPoolID=0;currentPoolID<this->POOL_SIZE;currentPoolID++)
		{
		//if (this->isEffectActive(effectID))
		if (this->EffectsPool[currentPoolID][PARAMETER_EFFECT_ID] != this->EFFECTID_NONE)
			{
//			if (this->List[effectID][this->PARAMETER_TICKS] != TIMER_VALUE_EXPIRED)
			if (this->EffectsPool[currentPoolID][this->PARAMETER_TICKS] != TIMER_VALUE_EXPIRED)
				{
//				if (--this->List[effectID][this->PARAMETER_DELAY_COUNTER] == 0)
				if (--this->EffectsPool[currentPoolID][this->PARAMETER_DELAY_COUNTER] == 0)
					{
//					if (this->List[effectID][this->PARAMETER_TICKS] != TIMER_VALUE_INFINITY)
					if (this->EffectsPool[currentPoolID][this->PARAMETER_TICKS] != TIMER_VALUE_INFINITY)
						{
//						if (--this->List[effectID][this->PARAMETER_TICKS] == TIMER_VALUE_EXPIRED)
						if (--this->EffectsPool[currentPoolID][this->PARAMETER_TICKS] == TIMER_VALUE_EXPIRED)
							{
//							this->removeEffect(effectID);
							this->removeFromPool(currentPoolID);
							
							}
						}
//					this->tick(effectID);
					this->tickPool(currentPoolID);
					}
				}
			else
				{
//				this->removeEffect(effectID);
				this->removeFromPool(currentPoolID);
				/*
				LcdClearCache();
				sprintf (lcd_buf, "[%03d]", currentPoolID);
				LcdString(1,LCD_LINE_5);
				LcdUpdate();
				while(1);*/
				}
			}
		}
	
	}
PlayerEffectsDefenceValue PlayerEffectsOldClass::getDefenceFrom(DamageClass* damage)
	{
	return this->getDefenceFrom(damage->GetSource()->Get());
	}
PlayerEffectsDefenceValue PlayerEffectsOldClass::getDefenceFrom(DamageSource_t dmgSrc)
	{
	return PlayerEffects.GetDefenceFrom(dmgSrc);
	/*
	switch (dmgSrc)
		{
		case TemporaryClass::DAMAGE_SOURCE_GENERIC:
		break;
		
		case TemporaryClass::DAMAGE_SOURCE_RADIATION_EXTERNAL:
			{
			uint8_t def=0;
			for (uint8_t currentPoolID=0;currentPoolID<this->POOL_SIZE;currentPoolID++)
				{
				if (this->EffectsPool[currentPoolID][PARAMETER_EFFECT_ID] == this->EFFECTID_ITEM_RAD_PROTECTOR)
					{
					def+=60;
					}
				}
			return def;
			}
		break;
		
		case TemporaryClass::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL:
			{
			
			}

		case TemporaryClass::DAMAGE_SOURCE_FIRE:
			{
			uint8_t def=0;
			for (uint8_t currentPoolID=0;currentPoolID<this->POOL_SIZE;currentPoolID++)
				{
				if (this->EffectsPool[currentPoolID][PARAMETER_EFFECT_ID] == this->EFFECTID_ARTEFACT_OGN_SHAR)
					{
					def+=10;
					}
				if (this->EffectsPool[currentPoolID][PARAMETER_EFFECT_ID] == this->EFFECTID_ARTEFACT_PUSTIWKA)
					{
					def+=30;
					}
				}
			return def;
			}
		break;
		
		case TemporaryClass::DAMAGE_SOURCE_ELECTRICITY:
			{
			uint8_t def=0;
			for (uint8_t currentPoolID=0;currentPoolID<this->POOL_SIZE;currentPoolID++)
				{
				if (this->EffectsPool[currentPoolID][PARAMETER_EFFECT_ID] == this->EFFECTID_ARTEFACT_VSPYSHKA)
					{
					def+=10;
					}
				if (this->EffectsPool[currentPoolID][PARAMETER_EFFECT_ID] == this->EFFECTID_ARTEFACT_LUN_SVET)
					{
					def+=10;
					}
				}
			return def;
			}
		break;

		case TemporaryClass::DAMAGE_SOURCE_CHEMICAL:
			{
			uint8_t def=0;
			for (uint8_t currentPoolID=0;currentPoolID<this->POOL_SIZE;currentPoolID++)
				{
				if (this->EffectsPool[currentPoolID][PARAMETER_EFFECT_ID] == this->EFFECTID_ARTEFACT_PLENKA)
					{
					def+=30;
					}
				}
			return def;
			}
		break;

		case TemporaryClass::DAMAGE_SOURCE_GRAVY:
			{
			uint8_t def=0;
			for (uint8_t currentPoolID=0;currentPoolID<this->POOL_SIZE;currentPoolID++)
				{
				if (this->EffectsPool[currentPoolID][PARAMETER_EFFECT_ID] == this->EFFECTID_ARTEFACT_KAM_CVETOK)
					{
					def+=30;
					}
				}
			return def;
			}
		break;

		case TemporaryClass::DAMAGE_SOURCE_PSY:
			{
			uint8_t def=0;
			for (uint8_t currentPoolID=0;currentPoolID<this->POOL_SIZE;currentPoolID++)
				{
				if (this->EffectsPool[currentPoolID][PARAMETER_EFFECT_ID] == this->EFFECTID_ARTEFACT_KRYSTAL)
					{
					def+=10;
					}
				if (this->EffectsPool[currentPoolID][PARAMETER_EFFECT_ID] == this->EFFECTID_ARTEFACT_MORSKOI_EZH)
					{
					def+=30;
					}
				if (this->EffectsPool[currentPoolID][PARAMETER_EFFECT_ID] == this->EFFECTID_ITEM_PSY_BLOKADA)
					{
					def+=20;
					}
				}
			return def;
			}
		break;

		case TemporaryClass::DAMAGE_SOURCE_BIO:
			{
			
			}
		break;
		
		default:
			{
			
			}
		break;
		}
	return 0;
	*/
	}

uint16_t PlayerEffectsOldClass::getRemaningTimeInSeconds(EffectID_t EID)
	{
	for (uint8_t currentPoolID=0;currentPoolID<this->POOL_SIZE;currentPoolID++)
		{
		if (this->EffectsPool[currentPoolID][PARAMETER_EFFECT_ID] == EID)
			{
			if (this->EffectsPool[currentPoolID][PARAMETER_TICKS] == this->TIMER_VALUE_INFINITY)
				{
				return 0xFFFF;
				}
			if (this->EffectsPool[currentPoolID][PARAMETER_TICKS] == this->TIMER_VALUE_EXPIRED)
				{
				return 0;
				}
			//return (this->EffectsPool[currentPoolID][this->PARAMETER_TICKS] * this->effectsTimings[this->EffectsPool[currentPoolID][this->PARAMETER_EFFECT_ID]][EFFECTS_PARAMETER_DELAY]) - (this->effectsTimings[this->EffectsPool[currentPoolID][this->PARAMETER_EFFECT_ID]][EFFECTS_PARAMETER_DELAY] - this->EffectsPool[currentPoolID][this->PARAMETER_DELAY_COUNTER]);
			return (this->EffectsPool[currentPoolID][this->PARAMETER_TICKS] * this->getRepeatDelay(this->EffectsPool[currentPoolID][this->PARAMETER_EFFECT_ID]) ) - (this->getRepeatDelay(this->EffectsPool[currentPoolID][this->PARAMETER_EFFECT_ID])  - this->EffectsPool[currentPoolID][this->PARAMETER_DELAY_COUNTER]);
			}
		}
	return 0;
	}
uint8_t PlayerEffectsOldClass::getRepeatDelay(EffectID_t EID)
	{
	return this->effectsTimings[EID][EFFECTS_PARAMETER_DELAY];
	}
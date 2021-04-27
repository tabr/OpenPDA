#ifndef TEMPORARY_CLASS_H
#define TEMPORARY_CLASS_H

INFO("Incedent game")

class TemporaryClass
	{
	public:
		const static uint8_t ANOMALY_ID_NONE				= 0;
		const static uint8_t ANOMALY_ID_JARKA				= 1;
		const static uint8_t ANOMALY_ID_ELECTRA				= 2;
		const static uint8_t ANOMALY_ID_HOLODEC				= 3;
		const static uint8_t ANOMALY_ID_KISEL				= 4;
		const static uint8_t ANOMALY_ID_KARUSEL				= 5;
		const static uint8_t ANOMALY_ID_TRAMPLIN			= 6;
//		const static uint8_t ANOMALY_NUM					= 7;

		const static uint8_t ITEMID_NONE					= 0;
		const static uint8_t ITEMID_FIRST_AID				= 1;
		const static uint8_t ITEMID_BANDAGE					= 2;
		const static uint8_t ITEMID_ANTIRAD					= 3;
		const static uint8_t ITEMID_VODKA					= 4;
		const static uint8_t ITEMID_PSY_BLOKADA				= 5;
		const static uint8_t ITEMID_RAD_PROTECTOR			= 6;
		const static uint8_t ITEMID_FOOD					= 7;
		const static uint8_t ITEMID_REPAIR_KIT				= 8;
		const static uint8_t ITEMID_DETAILS					= 9;
		
		const static uint8_t ARTEFACTID_MEDUSA			= 1;
		const static uint8_t ARTEFACTID_KAM_CVETOK		= 2;
		const static uint8_t ARTEFACTID_VSPYSHKA		= 3;
		const static uint8_t ARTEFACTID_OGN_SHAR		= 4;
		const static uint8_t ARTEFACTID_PLENKA			= 5;
		const static uint8_t ARTEFACTID_PUSTIWKA		= 6;
		const static uint8_t ARTEFACTID_LUN_SVET		= 7;
		const static uint8_t ARTEFACTID_KRYSTAL			= 8;
		const static uint8_t ARTEFACTID_MORSKOI_EZH		= 9;
		const static uint8_t ARTEFACTID_DUWA			= 10;
		const static uint8_t ARTEFACTS_NUM			= 11;

		const static uint16_t PLAYER_SAVE_TIMER					= 600;//10мин
		
		const static uint8_t ANORAD_IDS_NUM				= 32;

		/*enum AGRESSOR_TYPE
			{
			AGRESSOR_TYPE_GENERIC,
			AGRESSOR_TYPE_RADIATION,
			AGRESSOR_TYPE_ANOMALY,
			AGRESSOR_TYPE_PSY,
			AGRESSOR_TYPE_ADDICTION,
			AGRESSOR_TYPE_VODKA,
			AGRESSOR_TYPE_BLOWOUT,
			};*/

		enum SUIT_ID
			{
			SUIT_ID_NONE,
			SUIT_ID_ZARYA,
			SUIT_ID_SEVA,
			SUIT_ID_EXO,
			SUIT_ID_MONOLIT_EXO,
			/*
			SUIT_ID_MONOLIT,
			SUIT_ID_KOZH,
			SUIT_ID_KOZH1,
			SUIT_ID_BANDOS,
			SUIT_ID_BANDOS1,
			SUIT_ID_ECOLOG,
			SUIT_ID_BERYL,
			SUIT_ID_BRONE,
			SUIT_ID_HALAT,
			*/
			SUIT_ID_SIZE,
			};
		enum DamageSource
			{
			DAMAGE_SOURCE_NONE,						//built-in		//web
			DAMAGE_SOURCE_GENERIC,					//built-in		//web
			DAMAGE_SOURCE_SELF,						//built-in		//web
			DAMAGE_SOURCE_RADIATION_EXTERNAL,		//built-in		//web
			DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL,	//built-in		//web
			DAMAGE_SOURCE_FIRE,										//web
			DAMAGE_SOURCE_ELECTRICITY,								//web
			DAMAGE_SOURCE_CHEMICAL,									//web
			DAMAGE_SOURCE_GRAVY ,									//web
			DAMAGE_SOURCE_PSY,										//web
			DAMAGE_SOURCE_BIO,										//web
			DAMAGE_SOURCE_BLOWOUT,									//web
			DAMAGE_SOURCE_CHEATER,									//web
			DAMAGE_SOURCE_MASTER,									//web
			DAMAGE_SOURCE_NUM,
			};
		enum FACTIONS
			{
			FACTION_UNDEFINED,
			FACTION_NONE,
			FACTION_MILITARY,
			FACTION_BANDIT,
			FACTION_MONOLIT,
			FACTION_SCI,
			FACTION_TRAIDER,
			FACTION_FREEDOM,
			FACTION_DUTY,
			};

		const static uint8_t EFFECTID_ITEM_SHIFT			= 10;//PlayerEffectsClass::EFFECTID_ARTEFACT_DUWA;

		const static uint8_t QID_FIRST						= 1;
		const static uint8_t QID_FIND_BAR					= 1;
		const static uint8_t QID_FIND_KEY					= 2;
//		const static uint8_t QID_FIND_BARMAN				= 2;
//		const static uint8_t QUESTS_NUM						= 3;
		const static uint8_t QUESTS_NUM						= 2;//почемубля!
		
		const static uint8_t VODKA_DAMAGE					= 10;
		const static uint8_t VODKA_RAD_DECRASE				= 10;
		
		const static uint8_t RADIATION_DOSE_SICK			= 25;

		const static uint8_t REPAIR_KIT_REPAIR_POINTS		= 10;
		const static uint8_t PLAYER_NAME_LENGTH				= 16;
		const static uint8_t ITEMS_NUM						= 10;
		
		const static uint8_t SUITE_PARAMETERS_NUM			= 1+2;//SuiteID[1] + Durability[2]
		

	protected:
	private:
	};




#endif
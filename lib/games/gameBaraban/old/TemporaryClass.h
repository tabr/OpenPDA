#ifndef TEMPORARY_CLASS_H
#define TEMPORARY_CLASS_H

class TemporaryClass
	{
	public:
		const static uint8_t ANOMALY_TYPE_NONE				= 0;
		const static uint8_t ANOMALY_TYPE_JARKA				= 1;
		const static uint8_t ANOMALY_TYPE_ELECTRA			= 2;
		const static uint8_t ANOMALY_TYPE_HOLODEC			= 3;
		const static uint8_t ANOMALY_TYPE_KISEL				= 4;
		const static uint8_t ANOMALY_TYPE_KARUSEL			= 5;
		const static uint8_t ANOMALY_TYPE_TRAMPLIN			= 6;
//		const static uint8_t ANOMALY_NUM					= 7;

		enum ITEMID
			{
			ITEMID_NONE			= 0,
			ITEMID_FIRST_AID,
			ITEMID_ANTIRAD,
			ITEMID_REPAIR_KIT,
			ITEMID_RADX,
			ITEMID_VODKA,
			};
		
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


		enum SUITE_ID
			{
			SUITE_ID_NONE,
			SUITE_ID_ZARYA,
			SUITE_ID_SEVA,
			SUITE_ID_MONOLIT,
			SUITE_ID_KOZH,
			SUITE_ID_KOZH1,
			SUITE_ID_BANDOS,
			SUITE_ID_BANDOS1,
			SUITE_ID_ECOLOG,
			SUITE_ID_BERYL,
			SUITE_ID_BRONE,
			SUITE_ID_HALAT,
			SUITE_ID_ARM_BRONE,
			SUITE_ID_EXO,
			SUITE_ID_SIZE,
			};

		const static uint8_t QID_FIRST				= 1;
		const static uint8_t QID_FIND_BAR					= 1;
		const static uint8_t QID_FIND_KEY					= 2;
		const static uint8_t QID_FIND_BARMAN				= 2;
		
		const static uint8_t VODKA_DAMAGE					= 10;
		const static uint8_t VODKA_RAD_DECRASE				= 10;
		
		const static uint8_t RADIATION_DOSE_SICK			= 25;

		const static uint8_t REPAIR_KIT_REPAIR_POINTS		= 10;
		const static uint8_t PLAYER_NAME_LENGTH				= 16;
		const static uint8_t ITEMS_NUM						= 10;
		
		const static uint8_t SUITE_PARAMETERS_NUM			= 1+2;//SuiteID[1] + Durability[2]
		
//		const static uint8_t QUESTS_NUM						= 3;
		const static uint8_t QUESTS_NUM						= 2;//почемубля!

	protected:
	private:
	};
#endif
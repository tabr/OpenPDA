#ifndef PLAYER_EFFECTS_CLASS_H
#define PLAYER_EFFECTS_CLASS_H

#include "DeviceConfigClass.h"
#include "DamageClass.h"
#include "typedefs.h"


class PlayerEffectsOldClass : public ITimerListener
	{
	public:
		enum EFFECT_TIMINGS
			{
			EFFECT_TIMINGS_NONE,
			EFFECT_TIMINGS_ONCE,
			EFFECT_TIMINGS_PERIODICALLY,
			EFFECT_TIMINGS_UNTILL_DIE,
			EFFECT_TIMINGS_PERMANENT,
//			EFFECT_TIMINGS_,
			};

		enum EFFECTID //v1.0
			{
			EFFECTID_NONE,
			EFFECTID_ARTEFACT_MEDUSA,
			EFFECTID_ARTEFACT_KAM_CVETOK,
			EFFECTID_ARTEFACT_VSPYSHKA,
			EFFECTID_ARTEFACT_OGN_SHAR,
			EFFECTID_ARTEFACT_PLENKA,
			EFFECTID_ARTEFACT_PUSTIWKA,
			EFFECTID_ARTEFACT_LUN_SVET,
			EFFECTID_ARTEFACT_KRYSTAL,
			EFFECTID_ARTEFACT_MORSKOI_EZH,
			EFFECTID_ARTEFACT_DUWA = 10,
			EFFECTID_ITEM_FIRST_AID,
			EFFECTID_ITEM_BANDAGE,
			EFFECTID_ITEM_ANTIRAD,
			EFFECTID_ITEM_VODKA,
			EFFECTID_ITEM_PSY_BLOKADA,
			EFFECTID_ITEM_RAD_PROTECTOR,
			EFFECTID_ITEM_FOOD,
			EFFECTID_ITEM_REPAIR_KIT,
			EFFECTID_ITEM_DETAILS,
			EFFECTID_SAFE_SHELTER,
			EFFECTS_NUM
			};
		const static uint8_t TIMER_VALUE_INFINITY			= 255;
		const static uint8_t TIMER_VALUE_MAX				= 254;
		const static uint8_t TIMER_VALUE_EXPIRED			= 0;

		//const static uint8_t PARAMETER_TIMER				= 0;//������ ����� �������� ������� (� �����), 255-�� ����������			
		//const static uint8_t PARAMETER_POWER				= 1;//�������� �������
		//const static uint8_t PARAMETER_DELAY				= 2;//�������� ����� ������
		//const static uint8_t PARAMETER_DELAY_COUNTER		= 3;//���������������� �������� ��������
		//const static uint8_t PARAMETER_SIZE					= 4;

//		const static uint8_t PARAMETER_TYPE					= 0;
		const static uint8_t PARAMETER_TICKS				= 0;
		const static uint8_t PARAMETER_DELAY_COUNTER		= 1;//���������������� �������� ��������
//		const static uint8_t PARAMETER_STATUS				= 2;
		const static uint8_t PARAMETER_EFFECT_ID			= 2;
		const static uint8_t PARAMETERS_SIZE				= 3;
		
		const static uint8_t POOL_SIZE						= 16 + DeviceConfigClass::MAX_ARTEFACT_SLOTS;
		
		const static uint8_t EFFECT_STATUS_APPLIED_bp		= 0;
		const static uint8_t EFFECT_STATUS_APPLIED_bm		= 1<<0;
		
		TODO("������ ��� ����� � SOURCE");
		
		enum EFFECT_SOURCE
			{
			SOURCE_ARTEFACT_SLOT_0,
			EFFECT_SOURCE_ARTEFACT_SLOT_1,
			EFFECT_SOURCE_ARTEFACT_SLOT_2,
			EFFECT_SOURCE_ARTEFACT_SLOT_3,
			EFFECT_SOURCE_ARTEFACT_SLOT_4,
			EFFECT_SOURCE_ITEM_SLOT,
			EFFECT_SOURCE_ANY				= 254,
			EFFECT_SOURCE_NONE				= 255,
			};
//		const static uint8_t SOURCE_ARTEFACT_SLOT_MIN		= SOURCE_ARTEFACT_SLOT_0;
//		const static uint8_t SOURCE_ARTEFACT_SLOT_0			= 0;
//		const static uint8_t SOURCE_ARTEFACT_SLOT_1			= 1;
//		const static uint8_t SOURCE_ARTEFACT_SLOT_2			= 2;
//		const static uint8_t SOURCE_ARTEFACT_SLOT_3			= 3;
//		const static uint8_t SOURCE_ARTEFACT_SLOT_4			= 4;
		const static uint8_t SOURCE_ARTEFACT_SLOT_MAX		= EFFECT_SOURCE_ARTEFACT_SLOT_4;
//		const static uint8_t SOURCE_ITEM_SLOT				= 5;
//		const static uint8_t SOURCE_ANY						= 254;
//		const static uint8_t SOURCE_NONE					= 255;

		const static uint8_t EFFECTS_PARAMETER_DELAY		= 0;
		const static uint8_t EFFECTS_PARAMETER_TICKS		= 1;
		const static uint8_t EFFECTS_PARAMETERS_NUM			= 2;

		const static uint8_t effectsTimings[PlayerEffectsOldClass::EFFECTS_NUM][EFFECTS_PARAMETERS_NUM];

		//->protected???
//		uint8_t List[EFFECTS_NUM][PARAMETERS_SIZE];//������� �����, ������� ����

		PlayerEffectsOldClass(void);
		
		void TimerUpdateEvent (uint8_t msPassed);
		
		EffectID_t GetActiveVisibleList(EffectID_t *data);								//���������� ������ ������� � effectID-���, ������� �� ������
		bool IsVisible (EffectID_t effectID);											//������� ����� ���� ��������
//		bool isEffectActiveInPool (EffectID EID, uint8_t* poolID=NULL);				//���������, ���������� �� ������ � �����. ������� �����, �.�. ���������� ���� ���!!!
		bool IsEffectActiveInPool (EffectID_t EID, uint8_t& poolID);					//���������, ���������� �� ������ � �����. ������� �����, �.�. ���������� ���� ���!!! poolID - ID ����, 
		bool IsEffectActiveInPool (EffectID_t EID);									//������������� �������, ������� ���������� � �������� isEffectActiveInPool(a,b)
		bool IsEffectPoolActive (uint8_t poolID);									//������� �� poolID
		bool CanBeApplied(EffectID_t EID);
		uint8_t getFreePoolID(void);												//�������� ����������� ��������� ��. �� ����������� ������������ �������!
		void renewEffect(EffectID_t EID);												//���������� � ������ ������ ������� ��� ��������� ��� ������
		void applyEffect (EffectID_t EID, EFFECT_SOURCE selectedEffectSource);		//������� ���������� �� 2� ����: ���� � ����� !!!������!!! ��� �������� �� ������� ����������!!!
		void removeFromPool(uint8_t poolID);										//������� �� ���� �� �������������� ����
		void removeAll (void);														//�������� ���� ���
//		void removeEffect (uint8_t effectID);
		void process (void);														//���������� ����� ��� ���������� ����
//		void tick(uint8_t effectID);
		PlayerEffectsDefenceValue getDefenceFrom(DamageSource_t dmgSrc);
		PlayerEffectsDefenceValue getDefenceFrom(DamageClass* damage);
		uint16_t getRemaningTimeInSeconds(EffectID_t EID);							//���������� ����� � ��������. ���������� ���� ���!!!
		uint8_t getRepeatDelay(EffectID_t EID);
		void test(uint8_t& tmp);													//������, ����� �����
		
	protected:
	private:
		uint8_t EffectsPool[POOL_SIZE][PARAMETERS_SIZE];							//��� ���
		void tickPool(uint8_t poolID);												//���������� ������� �� ��� �����
		PlayerEffectsPoolSize ActiveEffects;										//�� ����������� �� ������������
	};

#endif
/*
 * ConnectedItemClass.h
 *
 * Created: 2015-07-16 23:24:29
 *  Author: tabr
 */ 


#ifndef CONNECTEDITEMCLASS_H_
#define CONNECTEDITEMCLASS_H_

//#include "UsableItemClass.h"
#include "typedefs.h"
#include "PlayerEffectsInterface.hpp"
#include "EepromItemClass.hpp"
class UsableItemClass;

class ConnectedItemInterface
	{
	public:
		//ConnectedItemCoreClass(void);
		virtual void Clean(void)				= 0;
		virtual ItemID_t GetID(void)			= 0;
		//virtual uint8_t* GetConnectedItemArrayAddr(void);
		virtual EepromItemClass* GetItem(void)	= 0;
	protected:
	private:
		//uint8_t* connectedItemArray;//can't contain values because it multiplies to each classes
//		virtual uint8_t z(void);
	};

//sdafjalskdfjlkas
//asdfjkaslkdfjlkasd
//asdfjasldkfjlka
/*
class ConnectedItemDummyClass : public ConnectedItemCoreClass
	{
	public:
	protected:
	private:
	};
*/
class ConnectedItemMedicamentsClass  : public ConnectedItemInterface
	{
	public:
//		EffectID_t GetEffectID(void);
		PlayerEffects_Interface* GetEffect(void);
		ItemChargesNum_t GetChargesNum(void);
		bool isValidItem(void);
	protected:
	private:
	};

class ConnectedItemSuitClass  : public ConnectedItemInterface
	{
	public:
		SuitDurabiluty_t GetDurablity(void);
	protected:
	private:
	};
class ConnectedItemRepairKitClass : public ConnectedItemInterface
	{
	public:
		RepairKitPCS_t GetPCS(void);
	protected:
	private:
	};
class ConnectedItemResourceClass : public ConnectedItemInterface
	{
	public:
		ResourcePCS_t GetPCS(void);
		void SetPCS(ResourcePCS_t value);
		void SetID(ResourcePCS_t value);
		//void SetType(ResourcePCS_t value);
//		ResourceID_t GetID(void);
	protected:
	private:
	};
class ConnectedItemQuestClass : public ConnectedItemInterface
	{
	public:
		QuestStatus_t GetQuestStatus(void);
	protected:
	private:
	};
//lets start!!!
class ConnectedItemClass : public ConnectedItemRepairKitClass, public ConnectedItemSuitClass, public ConnectedItemMedicamentsClass, public ConnectedItemResourceClass, public ConnectedItemQuestClass//, public ConnectedItemDummyClass
	{
	public:
/*
		enum CONNECTED_ITEM_STRUCT
			{
			CONNECTED_ITEM_STRUCT_TYPE,
			CONNECTED_ITEM_STRUCT_SUBTYPE,
			CONNECTED_ITEM_STRUCT_ID,
			CONNECTED_ITEM_STRUCT_STATUS,
			CONNECTED_ITEM_STRUCT_EX0,
			CONNECTED_ITEM_STRUCT_EX1,
			CONNECTED_ITEM_STRUCT_EX2,
			CONNECTED_ITEM_STRUCT_EX3,
			};
*/
		//using ConnectedItemDummyClass::isNotUsable;
		bool isUsable(void);
		bool isNotUsable(void);
		bool isDecrementable(void);
		bool ReadHardware(UsableItemClass* UI);
		bool WriteHardware(UsableItemClass* UI);
//		ItemType_t GetType(void);

		ConnectedItemMedicamentsClass* AsMedicaments(void)
			{
			return this;
			}
		ConnectedItemQuestClass* AsQuest(void)
			{
			return this;
			}
		ConnectedItemSuitClass* AsSuit(void)
			{
			return this;
			}
		ConnectedItemRepairKitClass* AsRepairKit(void)
			{
			return this;
			}
		ConnectedItemResourceClass* AsResource(void)
			{
			return this;
			}

		//from dummy
		ItemID_t GetID(void)
			{
			return this->GetItem()->GetID();
			}
    /*void SetID(ItemID_t value)
      {
      this->GetItem()->SetID(value);
      }*/
//		ConnectedItemArray_t* GetConnectedItemArrayAddr(void);
		void Clean(void)
			{
			this->GetItem()->Clean();
			}
		EepromItemClass* GetItem(void)
			{
			return &this->EepromItem;
			}
		ItemType_t GetType(void)
			{
			return this->GetItem()->GetType();
			}
		
	protected:
	private:
		//TWI* m_hardware=NULL;
		//uint8_t connectedItemArray[ConnectedItemClass::CONNECTED_ITEM_SIZE];
		EepromItemClass EepromItem;
	};


#endif /* CONNECTEDITEMCLASS_H_ */
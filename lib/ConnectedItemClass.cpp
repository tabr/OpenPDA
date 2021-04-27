// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * ConnectedItemClass.cpp
 *
 * Created: 2015-07-16 23:29:01
 *  Author: tabr
 */ 
#include "ConnectedItemClass.hpp"
//#include "UsableItemClass.hpp"



/*

ConnectedItemCoreClass::ConnectedItemCoreClass(void)
	{
	TODO("this is hack!");
	this->connectedItemArray	= UsableItem.GetConnectedItemArray();
	this->Clean();
	}
void ConnectedItemCoreClass::Clean(void)
	{
	memset(this->connectedItemArray, 0, UsableItemClass::CONNECTED_ITEM_SIZE);
	}


ItemID ConnectedItemCoreClass::GetID(void)
	{
	//return this->connectedItemArray[UsableItemClass::FLASHDATA_ITEM_ID];
	return *(this->GetConnectedItemArrayAddr() + UsableItemClass::FLASHDATA_ITEM_ID);
	}
uint8_t* ConnectedItemCoreClass::GetConnectedItemArrayAddr(void)
	{
	return this->connectedItemArray;
	}
*/



/*
ConnectedItemMedicamentsClass* ConnectedItemClass::AsMedicaments(void)
	{
	return this;
	}
ConnectedItemSuitClass* ConnectedItemClass::AsSuit(void)
	{
	return this;
	}
ConnectedItemRepairKitClass* ConnectedItemClass::AsRepairKit(void)
	{
	return this;
	}
ConnectedItemResourceClass* ConnectedItemClass::AsResource(void)
	{
	return this;
	}
*/
/*
ItemType_t ConnectedItemClass::GetType(void)
	{
	//return this->connectedItemArray[UsableItemClass::FLASHDATA_ITEM_TYPE];
	//return *(this->GetConnectedItemArrayAddr() + UsableItemClass::FLASHDATA_ITEM_TYPE);
	return this->GetItem()->GetType();
	}
*/
bool ConnectedItemClass::isDecrementable(void)
	{
	//uint8_t* array	= this->GetItemArray();
	if (this->GetType() == UsableItemClass::ITEM_TYPE_MEDICAMENTS)
		{
		return true;
		}
	if (GameCFG.ItemTemplate.GetItemEffect(this->GetID()) != &PlayerEffects.PlayerEffect_NullEffect)
		{
		return true;
		}
	return false;
	}

bool ConnectedItemClass::isUsable(void)
	{
	if (this->GetType() == UsableItemClass::ITEM_TYPE_MEDICAMENTS)
		{
		return true;
		}
	if (this->GetType() == UsableItemClass::ITEM_TYPE_SUIT)
		{
		return true;
		}
	if (this->GetType() == UsableItemClass::ITEM_TYPE_ELSE )// && this->GetID() == TemporaryClass::ITEMID_REPAIR_KIT)
		{
		return true;
		}
	if (this->GetType() == UsableItemClass::ITEM_TYPE_QUEST)
		{
		return true;
		}
	if (this->GetType() == UsableItemClass::ITEM_TYPE_RESOURCE)
		{
		if (GameCFG.ItemTemplate.GetItemEffect(this->GetID()) != &PlayerEffects.PlayerEffect_NullEffect)
			{
			return true;
			}
		}
	return false;
	}
bool ConnectedItemClass::isNotUsable(void)
	{
	return !(this->isUsable());
	}
bool ConnectedItemClass::ReadHardware(UsableItemClass* UI)
	{
	if (UI->ReadConnectedItem())
		{
		return true;
		}
	this->Clean();
	return false;
	}
bool ConnectedItemClass::WriteHardware(UsableItemClass* UI)
	{
	if (UI->WriteConnectedItem())
		{
		return true;
		}
	return false;
	/*TODO("remove this hack & return");
	uint8_t* array	= UsableItem.GetConnectedItem()->GetConnectedItemArrayAddr();
	array[UsableItemClass::FLASHDATA_ITEM_ID]		= (this->GetID());
	array[UsableItemClass::FLASHDATA_ITEM_EX0]		= (this->GetDurability() >> 0) & 0xFF;
	array[UsableItemClass::FLASHDATA_ITEM_EX1]		= (this->GetDurability() >> 8) & 0xFF;
	UsableItem.writeConnectedItem();
	return true;*/
	}
/*
ItemID_t ConnectedItemClass::GetID(void)
	{
	//return this->ConnectedItemDummyClass::GetID();
	//return *(this->GetConnectedItemArrayAddr() + UsableItemClass::FLASHDATA_ITEM_ID);
	return this->GetItem()->GetID();
	}
*/
/*
ConnectedItemArray_t* ConnectedItemClass::GetConnectedItemArrayAddr(void)
	{
	//return this->ConnectedItemDummyClass::GetConnectedItemArrayAddr();
	return UsableItem.GetConnectedItemArray();
	}
*/
/*
void ConnectedItemClass::Clean(void)
	{
	//this->ConnectedItemDummyClass::Clean();
	//memset(this->GetConnectedItemArrayAddr(), 0, UsableItemClass::CONNECTED_ITEM_SIZE);
	this->GetItem()->Clean();
	}
*/


PlayerEffects_Interface* ConnectedItemMedicamentsClass::GetEffect(void)
	{
	return GameCFG.ItemTemplate.GetItemEffect(this->GetID());
	}
/*
EffectID_t ConnectedItemMedicamentsClass::GetEffectID(void)
	{
	//return PlayerEffectsClass::EFFECTID_ITEM_SHIFT + this->GetID();
	return GameCFG.ItemTemplate.getItemApplyEffectID(this->GetID());
	}*/
ItemChargesNum_t ConnectedItemMedicamentsClass::GetChargesNum(void)
	{
	//return (ItemChargesNum)(*(this->GetConnectedItemArrayAddr() + UsableItemClass::FLASHDATA_ITEM_EX0));
	//return (*((ItemChargesNum_t*)(this->GetConnectedItemArrayAddr() + EepromItemClass::EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_EX0)));
	return (ItemChargesNum_t)this->GetItem()->GetEx0();
	}
bool ConnectedItemMedicamentsClass::isValidItem(void)
	{
	return GameCFG.ItemTemplate.IsValidItemId(this->GetID());
	}
SuitDurabiluty_t ConnectedItemSuitClass::GetDurablity(void)
	{
//	SuitDurabiluty d	= ((*(this->GetConnectedItemArrayAddr() + UsableItemClass::FLASHDATA_ITEM_EX0)) << 8) + (*(this->GetConnectedItemArrayAddr() + UsableItemClass::FLASHDATA_ITEM_EX1));
	//void* d	= (this->GetConnectedItemArrayAddr() + UsableItemClass::FLASHDATA_ITEM_EX0);
	//return (SuitDurabiluty)(*(this->GetConnectedItemArrayAddr() + UsableItemClass::FLASHDATA_ITEM_EX0));
	//return (*((SuitDurabiluty_t*)(this->GetConnectedItemArrayAddr() + EepromItemClass::EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_EX0)));
	return (SuitDurabiluty_t)((this->GetItem()->GetEx0() << 8) | this->GetItem()->GetEx1());
	}

QuestStatus_t ConnectedItemQuestClass::GetQuestStatus(void)
  {
  uint8_t qs = this->GetItem()->GetEx0();
  if (qs >= QUEST_STATUS::QUEST_STATUS_NUM_STATUSES)
    {
    qs  = 0;
    }
  return static_cast<QUEST_STATUS>(qs);
  }

#include "ConnectedItemRepairKitClass.cpp"
#include "ConnectedItemResourceClass.cpp"



/*
void ConnectedItemClass::cloneFrom(ConnectedItemClass* item)
	{
//	uint8_t* src	= item->getStorage();
	memcpy(this->m_storage, item->getStorage(), UsableItemClass::FLASHDATA_ITEM_PARAMETERS_NUM);
//	for (uint8_t i = 0;i<UsableItemClass::FLASHDATA_ITEM_PARAMETERS_NUM;i++)
//		{
//		this->m_storage[i]	= src[i];
//		}
	}
void ConnectedItemClass::cloneTo(ConnectedItemClass* item)
	{
	memcpy(item->getStorage(), this->m_storage, UsableItemClass::FLASHDATA_ITEM_PARAMETERS_NUM);
	}*/
/*
ConnectedItemClass2::ConnectedItemClass2(uint8_t* storage)
	{
	this->m_storage	= storage;
	}
bool ConnectedItemClass2::isDecrementable(void)
	{
	if (this->m_storage[UsableItemClass::FLASHDATA_ITEM_TYPE] == UsableItemClass::ITEM_TYPE_MEDICAMENTS)
		{
		return true;
		}
	return false;
	}
bool ConnectedItemClass2::isUsable(void)
	{
	if (this->getType()== UsableItemClass::ITEM_TYPE_MEDICAMENTS)
		{
		return true;
		}
	if (this->getType() == UsableItemClass::ITEM_TYPE_SUITE)
		{
		return true;
		}
	if (this->getType() == UsableItemClass::ITEM_TYPE_ELSE && this->getID() == TemporaryClass::ITEMID_REPAIR_KIT)
		{
		return true;
		}
	return false;
	}
bool ConnectedItemClass2::isNotUsable(void)
	{
	return !(this->isUsable());
	}
ItemType ConnectedItemClass2::getType(void)
	{
	return this->m_storage[UsableItemClass::FLASHDATA_ITEM_TYPE];
	}
ItemID ConnectedItemClass2::getID(void)
	{
	return this->m_storage[UsableItemClass::FLASHDATA_ITEM_ID];
	}
*/
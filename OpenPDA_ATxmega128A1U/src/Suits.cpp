// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * Suits.cpp
 *
 * Created: 26.01.2016 1:33:13
 *  Author: tabr
 */ 
#include "Suits.hpp"
/*
//void SuiteInstance::setProperties(char* tmpName, SuitDurabiluty suitMaxDurability, uint8_t containers, PlayerDefenceValue* defences)
void SuitTemplateInstance::setProperties(char* tmpName, PlayerDefenceValue_t* defences, GameCharacteristicsClass* c)
	{
	//this->Name		= (char*)malloc((1 + strlen(tmpName)) * sizeof(char));
	//this->Name		= (char*)MemoryManager.allocate((1 + strlen(tmpName)) * sizeof(char));
	uint8_t len		= (1 + strlen(tmpName)) * sizeof(char);
	this->Name		= new char[len];
	memset(this->Name, 0, len);
	memcpy(this->Name, tmpName, (len - 1));
	//sprintf(this->Name, tmpName);
	//this->def		= new uint8_t[sizeof(PlayerDefenceValue) * GameCFG.getDamageSourceNum()];
	this->DefenceContainer	= new DamageSourceContainerClass(GameCFG.GetDamageSourceNum());
	memcpy(this->DefenceContainer->container, defences, (sizeof(PlayerDefenceValue_t) * GameCFG.GetDamageSourceNum()));

	//this->GameCharacteristics	= new GameCharacteristicsClass();
	//memcpy(this->GetCharacteristics(), c, sizeof(GameCharacteristicsClass));
	this->GetCharacteristics()->CloneFrom(c);
			
			
	//this->maxDurability			= suitMaxDurability;
	//this->containers			= containers;
	}
*/
SuitTemplateInstance::SuitTemplateInstance(SuitID_t id, char* tmpName, DamageSourceContainerClass*	SuitDef, GameCharacteristicsClass* c)
	{
	this->ID				= id;
	this->Name				= LcdStringCopy.CopyFrom(tmpName);
	this->DefenceContainer	= SuitDef;
	this->SetCharacteristics(c);
	}

SuitName_t SuitTemplateInstance::GetName(void)
	{
	return this->Name;
	}
SuitID_t SuitTemplateInstance::GetID(void)
	{
	return this->ID;
	}
DamageSourceContainerClass* SuitTemplateInstance::GetDefences(void)
	{
	return this->DefenceContainer;
	}
/*
GameCharacteristicsClass* SuitTemplateInstance::GetCharacteristics(void)
	{
	return &this->GameCharacteristics;
	}*/




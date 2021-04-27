// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ARTEFACT_CLASS_CPP
#define ARTEFACT_CLASS_CPP
#include "ArtefactClass.hpp"
ArtefactClass::ArtefactClass(void)
	{
	this->m_ID		= 0;
//	this->m_GTAC	= GTAC;
	}
void ArtefactClass::setArtefactRAW(ArtefactID_t AID)
	{
	this->m_ID	= AID;
	}
/*
void ArtefactClass::applyEffects(void)
	{
	//TODO
	if (this->ID == this->ARTEFACT_NONE)
		return;
	}
void ArtefactClass::removeEffects(void)
	{
	if (this->ID != this->ARTEFACT_NONE)
		return;
	}
*/
void ArtefactClass::connect(void)
	{
	this->SID	= PlayerEffects.ApplyEffectInstance(GameCFG.ArtefactsContainer.GetArtefactInstance(this->getArtefactID())->GetEffect());
	}
void ArtefactClass::disconnect(void)
	{
//	this->removeEffects();
	PlayerEffects.RemoveEffect(this->SID);
	//while(1);
	this->setArtefactRAW(GameTemplate_ArtefactsContainerClass::ARTEFACTID_NONE);
	}
bool ArtefactClass::isArtefactValid(ArtefactID_t AID)
	{
	if (AID >0 && AID <= GameCFG.ArtefactsContainer.getMaximumArtefactId())
		{
		return true;
		}
	return false;
	}
bool ArtefactClass::isArtefactValid(void)
	{
	return this->isArtefactValid(this->m_ID);
	}
bool ArtefactClass::isEmpty(void)
	{
	return (this->m_ID == GameTemplate_ArtefactsContainerClass::ARTEFACTID_NONE);
	}
bool ArtefactClass::isNotEmpty(void)
	{
	return !(this->isEmpty());
	}
//ArtefactName ArtefactClass::getArtefactName(ArtefactID AID)
//	{
//	return GameTemplate_ArtefactsContainer.getName(AID);
//	}
ArtefactName_t ArtefactClass::getArtefactName()
	{
	return GameCFG.ArtefactsContainer.getName(this->m_ID);
	}
ArtefactID_t ArtefactClass::getArtefactID(void)
	{
	return this->m_ID;
	}


void GameTemplate_ArtefactInstanceClass::Init(ArtefactID_t AID,ArtefactName_t tmpName, PlayerEffects_Interface* PlayerEffect)
  {
	this->ID              = AID;
	this->m_PlayerEffect  = PlayerEffect;
	this->Name            = LcdStringCopy.CopyFrom(tmpName);
  }
GameTemplate_ArtefactInstanceClass::GameTemplate_ArtefactInstanceClass(ArtefactID_t AID,ArtefactName_t tmpName, PlayerEffects_Interface* PlayerEffect)
  {
  this->Init(AID, tmpName, PlayerEffect);
  }
GameTemplate_ArtefactInstanceClass::GameTemplate_ArtefactInstanceClass(void)
  {
  this->Init(0,RAM_STR_UNDEFINED,&PlayerEffects.PlayerEffect_NullEffect);
  }
ArtefactName_t GameTemplate_ArtefactInstanceClass::GetName(void)
  {
  return this->Name;
  }
ArtefactID_t GameTemplate_ArtefactInstanceClass::GetID(void)
	{
	return this->ID;
	}
PlayerEffects_Interface* GameTemplate_ArtefactInstanceClass::GetEffect(void)
	{
	return this->m_PlayerEffect;
	}








/*
void GameTemplate_ArtefactsContainerClass::setContainerSize(ArtefactsSize_t size)//нулевой тоже нужно указывать
	{
	this->setSize_full(size+1);//Должно вызываться перед malloc
	//			this->container	= (GameTemplate_ArtefactInstanceClass*)malloc (this->getSize_Full() * sizeof(GameTemplate_ArtefactInstanceClass));
	this->container	= (GameTemplate_ArtefactInstanceClass*)MemoryManager.allocate (this->getSize_Full() * sizeof(GameTemplate_ArtefactInstanceClass));
	TODO("hack");
	this->container[0].setProperties((char*)"          ", PlayerEffects.FromStorageID(0));
	}
*/
void GameTemplate_ArtefactsContainerClass::RegisterNew(ArtefactID_t AID, ArtefactName_t tmpName, PlayerEffects_Interface* PlayerEffect)
	{
	this->GetContainer()->AddNode(new GameTemplate_ArtefactInstanceClass (AID, tmpName, PlayerEffect));
	this->m_registeredArtefactsCounter++;
	}
GameTemplate_ArtefactsContainerClass::GameTemplate_ArtefactsContainerClass(void)
	{
	this->m_sizeFull					= 0;
//	this->container						= NULL;
	this->m_registeredArtefactsCounter	= 0;
	}
void GameTemplate_ArtefactsContainerClass::setSize_full(uint8_t size)
	{
	this->m_sizeFull	= size;
	}
uint8_t GameTemplate_ArtefactsContainerClass::getSize_Full(void)
	{
	return this->m_sizeFull;
	}
uint8_t GameTemplate_ArtefactsContainerClass::getSize_UserConfigured(void)
	{
	return (this->m_sizeFull-1);
	}
uint8_t GameTemplate_ArtefactsContainerClass::getMaximumArtefactId(void)
	{
	return this->getSize_UserConfigured();//Хак? Не думаю =)
	}
ArtefactName_t GameTemplate_ArtefactsContainerClass::getName(ArtefactID_t AID)
	{
	return this->GetArtefactInstance(AID)->GetName();
	}
GameTemplate_ArtefactInstanceClass* GameTemplate_ArtefactsContainerClass::GetArtefactInstance(ArtefactID_t AID)
	{
	return static_cast<GameTemplate_ArtefactInstanceClass*>(this->GetNode(AID));
	}
GameTemplate_ArtefactInstanceClass* GameTemplate_ArtefactsContainerClass::GetContainer(void)
	{
	return &this->container;
	}
#endif
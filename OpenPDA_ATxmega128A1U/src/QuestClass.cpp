// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//#include "strings.h"

#include "QuestClass.hpp"

QuestID_t QuestInstance::GetNextQuestID(void)
	{
	return this->next;
	}
QuestID_t QuestInstance::GetID(void)
	{
	return this->ID;
	}
QuestName_t QuestInstance::GetName(void)
	{
	return this->Name;
	}
/*
void QuestInstance::SetProperties(QuestName_t tmpName)
	{
	this->NameLength	= strlen(tmpName);
	this->Name			= (char*)MemoryManager.allocate((this->NameLength + 1) * sizeof(char));
	sprintf(this->Name, tmpName);
	}
void QuestInstance::SetProperties(QuestInstance src)
	{
	this->Name			= src.Name;
	this->NameLength	= src.NameLength;
	this->Status		= src.Status;
	}
QuestNameLength_t QuestInstance::GetNameLength(void)
	{
	//return this->NameLength;
	return strlen(this->Name);
	}
*/
QuestStatus_t QuestInstance::GetStatus(void)
	{
	return this->Status;
	}
void QuestInstance::SetStatus(QuestStatus_t status)
	{
	this->Status	= status;
	}
QuestInstance::QuestInstance(void)
	{
	this->Status		= QUEST_STATUS::QUEST_STATUS_UNKNOWN;
	this->Name			= RAM_STR_UNDEFINED;
//	this->NameLength	= strlen(STR_None);
	this->ID			= 0;
	this->next			= 0;
	}
QuestInstance::QuestInstance(QuestID_t QID, QuestName_t N, QuestID_t nextQuest)
	{
	this->Status		= QUEST_STATUS::QUEST_STATUS_UNKNOWN;
	this->Name			= LcdStringCopy.CopyFromUnlimited(N);
//	this->NameLength	= strlen(N);
	this->ID			= QID;
	this->next			= nextQuest;
	}


/////////////////////////////
QuestNum_t QuestClass::GetRegisteredQuestsNum(void)
	{
	return this->registeredQuestCounter;
	}
/*
QuestNum_t QuestClass::GetKnownNumAndUpdate(void)
	{
	uint8_t num=0;
	for (uint8_t QID=0;QID < this->GetContainerSize() ;QID++) //TODO - оптимизировать, т.к. Quest.getQuestsNum() вызывается постоянно??!
		{
		if (this->GetStatus(QID) != QUEST_STATUS::QUEST_STATUS_UNKNOWN)
			{
			this->QuestStatusBuffer[num++]	= QID;
			}
		}
	return num;
	}
*/
QuestNum_t QuestClass::GetKnownList(QuestInstance* data[]=NULL)
	{
	uint8_t num=0;
	/*
	for (uint8_t QID=0;QID < this->GetRegisteredQuestsNum() ;QID++) //TODO - оптимизировать, т.к. Quest.getQuestsNum() вызывается постоянно??!
		{
		if (this->GetStatus(QID) != QuestStatus_t::QUEST_STATUS_UNKNOWN)
			{
			if (data != NULL)
				{
				data[num]	= this->GetQuestInstance(QID);
				}
			num++;
			}
		}
	return num;
	*/
	QuestInstance* Q	= static_cast<QuestInstance*>(this->GetContainer());
	while(1)
		{
		if (Q->GetNextNode() == NULL)
			{
			break;
			}
		Q	= static_cast<QuestInstance*>(Q->GetNextNode());
		if (Q->GetStatus() != QuestStatus_t::QUEST_STATUS_UNKNOWN)
			{
			if (data != NULL)
				{
				data[num]	= Q;
				}
			num++;
			}
		}
	return num;
	}
bool QuestClass::IsKnown(QuestID_t QID)
	{
	if (this->GetStatus(QID) == QuestStatus_t::QUEST_STATUS_UNKNOWN)
		{
		return false;
		}
	return true;
	}
bool QuestClass::IsInProgress(QuestID_t QID)
	{
	if (this->GetStatus(QID) == QuestStatus_t::QUEST_STATUS_INCOMPLETE)
		{
		return true;
		}
	return false;
	}
QuestStatus_t QuestClass::GetStatus(QuestID_t QID)
	{
	return this->GetQuestInstance(QID)->GetStatus();
	}
QuestStatus_t QuestClass::StatusFromInt(uint8_t intStatus)
	{
	switch (intStatus)
		{
		case QuestStatus_t::QUEST_STATUS_COMPLETE:
			{
			return QuestStatus_t::QUEST_STATUS_COMPLETE;
			}
		break;
		case QuestStatus_t::QUEST_STATUS_INCOMPLETE:
			{
			return QuestStatus_t::QUEST_STATUS_INCOMPLETE;
			}
		break;
		case QuestStatus_t::QUEST_STATUS_FAILED:
			{
			return QuestStatus_t::QUEST_STATUS_FAILED;
			}
		break;

		case QuestStatus_t::QUEST_STATUS_UNKNOWN:
		default:
			{
			return QuestStatus_t::QUEST_STATUS_UNKNOWN;
			}
		break;
		}
	}
QuestClass::QuestClass(void)
	{
	/*
	for (uint8_t i=0;i<this->QUESTS_NUM;i++)
		{
		this->QuestList[i]	= 0;
		}*/
//	this->registeredQuestCounter	= 0;
//	this->QuestNone.SetProperties((QuestName_t)"-");
	}
void QuestClass::RemoveQuest(QuestID_t QID)
{
	if (this->IsKnown(QID))
		{
		this->SetUnknown(QID);
//		PDASound.PlaylistAdd(Sound::SID_PDA_QUEST);
		Lcd.IsNeedUpdate	= true;
		}
	}
void QuestClass::CompleteQuest(QuestID_t QID)
	{
	if (this->IsInProgress(QID))
		{
		this->SetComplete(QID);
		if (this->GetQuestInstance(QID)->GetNextQuestID() != 0)
			{
			this->GiveQuest(this->GetQuestInstance(QID)->GetNextQuestID());
			}
		PDASound.PlaylistAdd(Sound::SID_PDA_NEWS);
		Lcd.IsNeedUpdate	= true;
		}
	}
void QuestClass::GiveQuest (QuestID_t QID)
	{
	if (!this->IsInProgress(QID))
		{
		this->SetIncomplete(QID);
		PDASound.PlaylistAdd(Sound::SID_PDA_NEWS);
		Lcd.IsNeedUpdate	= true;
		}
	}
void QuestClass::FailQuest (QuestID_t QID)
	{
	if (this->IsInProgress(QID))
		{
		this->SetFailed(QID);
		PDASound.PlaylistAdd(Sound::SID_PDA_NEWS);
		Lcd.IsNeedUpdate	= true;
		}
	}
/*
void QuestClass::SetNewQuestState(QuestID_t QID, QuestStatus_t newState)
	{
	switch (newState)
		{
		case QUEST_STATUS_COMPLETE:
			{
			this->CompleteQuest(QID);
			}
		break;
		case QUEST_STATUS_INCOMPLETE:
			{
			this->GiveQuest(QID);
			}
		break;
		case QUEST_STATUS_COMPLETE:
			{
			this->CompleteQuest(QID);
			}
		break;
		case QUEST_STATUS_COMPLETE:
			{
			this->CompleteQuest(QID);
			}
		break;
		}
	}*/
void QuestClass::GetQuestStatusName(QuestStatus_t status, char* buffer)
  {
  //return pos_array[this->GetQuestStatusNamePOS(status)];
  STRClass Str(this->GetQuestStatusNamePOS(status));
  Str.WriteTo(buffer);
  }

STR_POS  QuestClass::GetQuestStatusNamePOS(QuestStatus_t  status)
	{
	switch (status)
		{
		case QuestStatus_t::QUEST_STATUS_INCOMPLETE:
			{
			return STRPOS_STR_PDAMENU_QUESTS_STATUS_INCOMPLETE;
			}
		break;
		case QuestStatus_t::QUEST_STATUS_COMPLETE:
			{
			return STRPOS_STR_PDAMENU_QUESTS_STATUS_COMPLETE;
			}
		break;
		case QuestStatus_t::QUEST_STATUS_FAILED:
			{
			return STRPOS_STR_PDAMENU_QUESTS_STATUS_FAILED;
			}
		break;
		case QuestStatus_t::QUEST_STATUS_UNKNOWN:
		default:
			{
			//return STRPOS_STR_PDAMENU_QUESTS_STATUS_UNKNOWN;
			}
		break;
		}
	return STRPOS_STR_PDAMENU_QUESTS_STATUS_UNKNOWN;
	}
QuestName_t QuestClass::GetQuestName(QuestID_t QID)
	{
	return this->GetQuestInstance(QID)->GetName();
	}
QuestNameLength_t QuestClass::GetNameLength(QuestID_t QID)
	{
	return strlen(this->GetQuestName(QID));
	}
/*
void QuestClass::SetQuestsNum(QuestNum_t num)
	{
	this->Num			= num;
	//QuestStatusBuffer	= (uint8_t*) malloc(sizeof(uint8_t) * (num + 1));
	QuestStatusBuffer	= (uint8_t*) MemoryManager.allocate(sizeof(uint8_t) * (num + 1));

	//this->container		= (QuestInstance*)malloc (this->getContainerSize() * sizeof(QuestInstance));
	this->container		= (QuestInstance*)MemoryManager.allocate (this->GetContainerSize() * sizeof(QuestInstance));
	this->container[this->QID_NONE].SetProperties(this->QuestNone);
	}
*/
void QuestClass::RegisterNew(QuestID_t QID, QuestName_t tmpName, QuestID_t nextQuest)
	{
	this->GetContainer()->AddNode(new QuestInstance(QID, tmpName, nextQuest));
	this->registeredQuestCounter++;
	}
void QuestClass::SetIncomplete(QuestID_t QID)
	{
	this->SetStatus(QID, QUEST_STATUS::QUEST_STATUS_INCOMPLETE);
	}
void QuestClass::SetComplete(QuestID_t QID)
	{
	this->SetStatus(QID, QUEST_STATUS::QUEST_STATUS_COMPLETE);
	}
void QuestClass::SetFailed(QuestID_t QID)
	{
	this->SetStatus(QID, QUEST_STATUS::QUEST_STATUS_FAILED);
	}
void QuestClass::SetUnknown(QuestID_t QID)
	{
	this->SetStatus(QID, QUEST_STATUS::QUEST_STATUS_UNKNOWN);
	}
void QuestClass::SetStatus(QuestID_t QID, QuestStatus_t status)
	{
	this->GetQuestInstance(QID)->SetStatus(status);
	}
/*
QuestNum_t QuestClass::GetContainerSize(void)
	{
	return this->Num + 1;
	}*/
NodeExtended* QuestClass::GetContainer(void)
	{
	return &this->container;
	}
QuestInstance* QuestClass::GetQuestInstance(QuestID_t QID)
	{
	return static_cast<QuestInstance*>(this->GetNode(QID));
	}
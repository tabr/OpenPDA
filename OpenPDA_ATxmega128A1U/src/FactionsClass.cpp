// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * FactionsClass.cpp
 *
 * Created: 30.06.2017 23:14:58
 *  Author: tabr
 */ 
FactionsClass::FactionsClass (void)
	{
	this->ID	= 0;
	this->Name	= RAM_STR_UNDEFINED;
	}
FactionsClass::FactionsClass (FactionID_t FID, FactionName_t FName)
	{
	this->ID	= FID;
	this->Name	= LcdStringCopy.CopyFrom(FName);
	/*
	this->Name	= new char[strlen(FName)+1];
	memset(this->Name, 0, strlen(FName)+1);
	memcpy(this->Name, FName, strlen(FName));
	*/
	}
FactionName_t FactionsClass::GetName(void)
	{
	return this->Name;
	}
FactionID_t FactionsClass::GetID(void)
	{
	return this->ID;
	}
FactionsClass* FactionsClass::GetNextNode(void)
	{
	return static_cast<FactionsClass*>(Node::GetNextNode());
	}
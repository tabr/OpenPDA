// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * GameCharacteristicsClass.cpp
 *
 * Created: 03.02.2016 2:23:20
 *  Author: tabr
 */ 
void GameCharacteristicsClass::CloneFrom (GameCharacteristicsClass* src)
	{
	memcpy (this, src, sizeof(GameCharacteristicsClass));
	}
bool GameCharacteristicsClass::IsUsingCharacteristic1(GameCharacteristicsClass::CHARACTERISTICS c)
	{
	return (this->characteristicsUsing & (1<<c));
	}
void GameCharacteristicsClass::SetUsingCharacteristic(GameCharacteristicsClass::CHARACTERISTICS c)
	{
	sbi(this->characteristicsUsing, c);
	}
CharacteristicsValue_t GameCharacteristicsClass::Get(GameCharacteristicsClass::CHARACTERISTICS c)
	{
	CharacteristicsValue_t ret		= this->storage[c];
	GameCharacteristicsClass* maxC	= this->MaxValuesGet();
	if (maxC != NULL)//shold work=)
		{
		CharacteristicsValue_t maxValue	= this->MaxValuesGet()->Get(c);
		if (ret > maxValue)
			{
			return maxValue;
			}
		}
	return ret;
	}
void GameCharacteristicsClass::Set(GameCharacteristicsClass::CHARACTERISTICS c, CharacteristicsValue_t value)
	{
	this->storage[c]	= value;
	this->SetUsingCharacteristic(c);
	}
GameCharacteristicsClass::GameCharacteristicsClass(CharacteristicsBitLength_t select)
	{
//	this->characteristicsSelected	= select;
	memset(this->storage,		0, sizeof(this->storage));
	//memset(this->storageMax,	0, CHARACTERISTICS::CHARACTERISTICS_NUM);
	}
void GameCharacteristicsClass::MaxValuesSetObject(GameCharacteristicsInterface* max)
	{
	this->max	= max;
	}
GameCharacteristicsClass* GameCharacteristicsClass::MaxValuesGet(void)
	{
	return this->max->GetCharacteristics();
	}
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * AnomalySimpleClass.cpp
 *
 * Created: 21.09.2017 0:54:26
 *  Author: tabr
 */ 
void AnomalySimpleClass::setLevelType_Filter (uint8_t level, AnomalyID_t AID, uint8_t skipLevel, uint8_t killLevel)
	{
//	USART_startTX((char*)"[AnomalyClass::setLevelType_Filter]\r\n");
	//Player.DealSimpleDamage(level-skipLevel, TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC);
  Player.DealDamage({value:(DamageValue_t)(level-skipLevel)});
	}
void AnomalySimpleClass::setLevelType_FilterNone(void)
	{
	
	}
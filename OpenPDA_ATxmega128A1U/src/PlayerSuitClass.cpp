// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "PlayerSuitClass.hpp"
PlayerSuitClass::PlayerSuitClass (void)
  {
  /*for (uint8_t currentParameter=0; currentParameter<TemporaryClass::SUITE_PARAMETERS_NUM; currentParameter++)
    {
    this->currentSuite[currentParameter]  = 0;
    this->previousSuit[currentParameter]  = 0;
    }*/
  //this->currentSuite  = &EEPROM_Data.data[EEPROM_STRUCT_PLAYER_CURRENT_SUITE_ID];
  }
SuitDurabiluty_t PlayerSuitClass::getMaxDurability(void)
  {
  //return GameConfig::suits[this->currentSuite[this->PARAMETER_SUIT_ID]].maxDurability;
  //return GameCFG.SuitsContainer.getSuiteInstance(this->currentSuite[this->PARAMETER_SUIT_ID])->maxDurability;
//  return GameCFG.SuitsContainer.getSuiteInstance(this->currentSuite[this->PARAMETER_SUIT_ID])->GetCharacteristics()->Get(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY);
  //return GameCFG.SuitsContainer.getSuiteInstance(this->getSuitID())->GetCharacteristics()->Get(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY);
  return this->GetCurrentSuit()->GetCharacteristics()->MaxValuesGet()->Get(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY);
  }
Percent_t PlayerSuitClass::getDurabilityPercent(void)
  {
  if (this->getDurability() == 0)
    {
    return 0;
    }
  return ((uint32_t)100*this->getDurability()/this->getMaxDurability());
  }
SuitDurabiluty_t PlayerSuitClass::getDurability(void)
  {
  if(GameCFG.IsGameUseParameter(GameConfig::CFG_CONFIGURATION_BITS_GAME_USE_SUIT_DURABILITY))
    {
    return this->GetCurrentSuit()->GetCharacteristics()->Get(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY);
    }
  return this->GetCurrentSuit()->GetCharacteristics()->MaxValuesGet()->Get(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY);
  }
void PlayerSuitClass::loseDurability(SuitDurabiluty_t d)
  {
  if (this->getDurability() == 0)
    {
    return;
    }
  if (!GameCFG.IsGameUseParameter(GameConfig::CFG_CONFIGURATION_BITS_GAME_USE_SUIT_DURABILITY))
    {
    return;
    }
  if (d > this->getDurability())
    {
    d  = this->getDurability();
    }
  this->setDurability(this->getDurability() - d);
  }
void PlayerSuitClass::setDurability(SuitDurabiluty_t d)
  {
  if (d == this->DURABILITY_FULL)
    {
    d  = this->getMaxDurability();
    }
  //this->currentSuite[this->PARAMETER_DURABITITY_H]  = ((d >> 8) & 0xFF);
  //this->currentSuite[this->PARAMETER_DURABITITY_L]  = ((d >> 0) & 0xFF);
  this->GetCurrentSuit()->GetCharacteristics()->Set(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY, d);
  }
void PlayerSuitClass::damageTaken(DamageClass *damage)
  {
  #ifdef DEBUG_USART_SUIT_DAMAGE
    sendString((char*)"[SUIT_DAMAGE] damageTaken\r\n");
  #endif
  if (this->getSuitID() == TemporaryClass::SUIT_ID_NONE)
    {
    #ifdef DEBUG_USART_SUIT_DAMAGE
      sendString((char*)"[SUIT_DAMAGE] SUIT_ID_NONE, returning...");
    #endif
    return;
    }
  

  Lcd.IsSuiteScreenNeedRedraw  = true;
  if (damage->GetAggressorSource() == DamageClass::AGGRESSOR_SOURCE_EXTERNAL)
    {
    #ifdef DEBUG_USART_SUIT_DAMAGE
      {
      sendString((char*)"[SUIT_DAMAGE] AGGRESSOR_SOURCE_EXTERNAL\r\n");
      }
    #endif
    if (this->getDurabilityPercent() < RandomPseudo.getAsPercent())
      {
      #ifdef DEBUG_USART_SUIT_DAMAGE
        sprintf (USARTBuffer,"[SUIT_DAMAGE] lose Suit durability [%03d]\r\n", damage->GetValue());
        sendString(USARTBuffer);
      #endif
      this->loseDurability(damage->GetValue());
      }
    }
  }

SuitContainersNum_t PlayerSuitClass::getContainersNum(void)
  {
  //SuitContainersNum containtersNum = this->GetCurrentSuit()->containers;
  SuitContainersNum_t containtersNum = this->GetCurrentSuit()->GetCharacteristics()->MaxValuesGet()->Get(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS);
  //#warning "[T] HACK! bottom str(get containers num) is doesn't work!"
  //return DeviceConfigClass::MAX_ARTEFACT_SLOTS;
  //SuitContainersNum_t containtersNum =  this->GetCurrentSuit()->GetCharacteristics()->Get(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS);
  if (containtersNum > DeviceConfigClass::MAX_ARTEFACT_SLOTS)
    {
    containtersNum  = DeviceConfigClass::MAX_ARTEFACT_SLOTS;
    }
  return containtersNum;
  //return 3;
  }
/*
DamageDefenceValue_t PlayerSuitClass::getDefenceFrom(DamageClass damage)
  {
  return this->getDefenceFrom(damage.GetSource()->Get());
  }
DamageDefenceValue_t PlayerSuitClass::getDefenceFrom(DamageSource_t dmgSrc)
*/
DamageDefenceValue_t PlayerSuitClass::GetDefenceFrom(DamageClass damage)
  {
//  DamageDefenceValue_t defence  = this->GetCurrentSuit()->GetDefences()->GetDefenceFrom(dmgSrc);
  DamageDefenceValue_t defence  = this->GetCurrentSuit()->GetDefences()->GetDefenceFrom(damage.GetSource()->Get());
  #ifdef DEBUG_USART_DEFENCE
    sprintf (USARTBuffer,"PlayerSuitClass::getDefenceFrom SuitID: %03d\r\n",this->GetCurrentSuit()->GetID());
    sendString(USARTBuffer);
  #endif // DEBUG_USART_DEFENCE
  if (defence > 0 && this->getDurability() > 0)
    {
    defence    = (defence * this->getDurabilityPercent()) / 100;
    }
  return defence;
  }
bool PlayerSuitClass::Wear (UsableItemClass* UI)
  {
  return this->Wear(UI->GetConnectedItem());
  }
bool PlayerSuitClass::Wear (ConnectedItemSuitClass* connectedSuit)
  {
  #warning "[T] suit write bug" //"когда одевается костюм, то записываются на флешку данные, которые уже изменены (прочтость, если изменена) на одетом костюме"
  Lcd.IsSuiteScreenNeedRedraw  = true;
  this->GetPreviousSuit()->CloneFrom(this->GetCurrentSuit());
  this->GetCurrentSuit()->CloneFrom(connectedSuit);
  return true;
  }

void PlayerSuitClass::Wear(SuitID_t SID, SuitDurabiluty_t durability)//одну снимаем, другую одеваем
  {
  Lcd.IsSuiteScreenNeedRedraw  = true;
  this->GetPreviousSuit()->CloneFrom(this->GetCurrentSuit());
  this->GetCurrentSuit()->CloneFrom(SID, durability);
  }
void PlayerSuitClass::repair(SuitDurabiluty_t value)
  {
  /*LcdClearCache();
  LcdString(1,LCD_LINE_4);
  sprintf (lcd_buf, "%03d %03d %03d", (this->getMaxDurability()-value), this->getDurability(), (this->getMaxDurability() - value) > this->getDurability());
  LcdString(1,LCD_LINE_5);
  LcdUpdate();*/
  
  if ((value > this->getMaxDurability()) || (value == this->DURABILITY_FULL) || ((this->getMaxDurability() - value)) < this->getDurability())
    {
    this->setDurability(this->DURABILITY_FULL);
    //while(1);
    }
  else
    {
    this->setDurability(this->getDurability() + value);
    }
  
  }
SuitID_t PlayerSuitClass::GetID(void)
  {
  return this->getSuitID();
  }
SuitID_t PlayerSuitClass::getSuitID(void)
  {
//  return this->currentSuite[PlayerSuitClass::PARAMETER_SUIT_ID];
  return this->GetCurrentSuit()->GetID();
  }
SuitName_t PlayerSuitClass::getSuitName(void)
  {
  //return GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_SEVA].Name;
  //return (GameCFG.SuitsContainer.getSuiteInstance(Player.getSuit()->getSuitID()))->GetName();
  return this->GetCurrentSuit()->GetTemplate()->GetName();
  }
/*void PlayerSuitClass::setSuitID(SuitID SID)
  {
  this->currentSuite[this->PARAMETER_SUIT_ID]    = SID;
  }*/
/*SuitTemplateInstance* PlayerSuitClass::GetCurrentSuitTemplate(void)
  {
  return GameCFG.SuitsContainer.getSuiteInstance(this->getSuitID());
  }*/
void PlayerSuitClass::EEPROM_init(void)
  {
  //this->currentSuite  = EEPROM_Data.getParameterAddr(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_VARS, EEPROM_DataClass::PLAYER_VAR_CURRENT_SUITE_ID);
  }
bool PlayerSuitClass::isValidSuitID(SuitID_t SID)
  {
  return (SID < GameCFG.SuitsContainer.getRegisteredSuitsNum());
  }




PlayerSuitInstanceClass* PlayerSuitClass::GetCurrentSuit(void)
  {
  return &this->currentSuit;
  }
PlayerSuitInstanceClass* PlayerSuitClass::GetPreviousSuit(void)
  {
  return &this->previousSuit;
  }








void PlayerSuitInstanceClass::CloneFrom(SuitID_t SID, SuitDurabiluty_t durability)
  {
  this->SID  = SID;
  this->SuitTemplate  = GameCFG.SuitsContainer.getSuiteInstance(this->GetID());
  this->GetCharacteristics()->MaxValuesSetObject(GameCFG.SuitsContainer.getSuiteInstance(this->GetID()));
  if (durability == PlayerSuitClass::DURABILITY_FULL)
    {
    durability = this->GetCharacteristics()->MaxValuesGet()->Get(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY);
    }
  this->GetCharacteristics()->Set(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY, durability);
  }
void PlayerSuitInstanceClass::CloneFrom(PlayerSuitInstanceClass* src)
  {
  memcpy(this, src, sizeof(PlayerSuitInstanceClass));
  }
void PlayerSuitInstanceClass::CloneFrom (ConnectedItemSuitClass* connectedSuit)
  {
  this->CloneFrom(connectedSuit->GetID(), connectedSuit->GetDurablity());
  }
/*
GameCharacteristicsClass* PlayerSuitInstanceClass::GetCharacteristics(void)
  {
  return &this->GameCharacteristics;
  }
*/
SuitID_t PlayerSuitInstanceClass::GetID(void)
  {
  return this->SID;
  }
SuitTemplateInstance* PlayerSuitInstanceClass::GetTemplate(void)
  {
  return this->SuitTemplate;
  }
DamageSourceContainerClass* PlayerSuitInstanceClass::GetDefences(void)
  {
  return this->GetTemplate()->GetDefences();
  }
SuitDurabiluty_t PlayerSuitInstanceClass::GetDurability(void)
  {
  return this->GetCharacteristics()->Get(GameCharacteristicsClass::CHARACTERISTIC_DURABILITY);
  }
bool PlayerSuitInstanceClass::WriteTo(UsableItemClass* UI)
  {
//  UI->GetConnectedItem()
//  UI->WriteConnectedItem();
  //TODO("remove this hack & return");
  //uint8_t* array  = UI->GetConnectedItem()->GetConnectedItemArrayAddr();
  //array[UsableItemClass::FLASHDATA_ITEM_ID]    = (this->GetID());
  //array[UsableItemClass::FLASHDATA_ITEM_EX0]    = (this->GetDurability() >> 0) & 0xFF;
  //array[UsableItemClass::FLASHDATA_ITEM_EX1]    = (this->GetDurability() >> 8) & 0xFF;

  EepromItemClass* Item  = UI->GetConnectedItem()->GetItem();
  Item->SetID(this->GetID());
//  Item->SetEx0((this->GetDurability() >> 8) & 0xFF);
//  Item->SetEx1((this->GetDurability() >> 0) & 0xFF);
  SuitDurabiluty_t d  = this->GetDurability();
  Item->SetEx0((d >> 8) & 0xFF);
  Item->SetEx1((d >> 0) & 0xFF);

  return UI->WriteConnectedItem();
  }

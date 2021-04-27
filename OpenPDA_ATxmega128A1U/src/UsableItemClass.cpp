// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
UsableItemClass::UsableItemClass (void) : m_isSomethingConnected(false), ledOnTimer(0)
  {
  //uint8_t i;
//  twi_init(&AT24C02_TWI);
//  this->m_isSomethingConnected  = false;
  //this->ledOnTimer      = 0;
  //memset(this->connectedItem.connectedItemArray, 0, UsableItemClass::FLASHDATA_ITEM_PARAMETERS_NUM);//очистка буффера
  //this->connectedItem2    = new ConnectedItemClass2(this->connectedItem.connectedItemArray);
//  this->hardware        = new TWI(&AT24C02_TWI, AT24C02_SLAVE_ADDRESS, 400);
//  this->connectedItem      = ConnectedItemClass(hardware);

  UsableItemItemConnectedPin::SetDirIn();
  UsableItemItemConnectedPin::SetPullUp();
  UsableItemLedPin::SetDirOut();
  UsableItemLedPin::SetOutLow();
  
  //this->TaskScanForConnectedIfNeed.SetLinkedObject(this);
  //this->TaskLedOnTick.SetLinkedObject(this);
  }
void UsableItemClass::TimerUpdateEvent (uint8_t msPassed)
  {
  static uint16_t scanForConnectedIfNeed_msCounter=0;
  static uint16_t ledOnTick_msCounter=0;
  
  scanForConnectedIfNeed_msCounter+=msPassed;
  ledOnTick_msCounter+=msPassed;
  
  if (scanForConnectedIfNeed_msCounter >= 40)
    {
    scanForConnectedIfNeed_msCounter -= 40;
    this->scanForConnectedIfNeed();
    }
  if (ledOnTick_msCounter >= 100)
    {
    ledOnTick_msCounter -= 100;
    this->ledOnTick();
    }
  }
void UsableItemClass::ledOnTick()
  {
  if (this->ledOnTimer > 0)
    {
    if (--this->ledOnTimer == 0)
      {
      this->turnOffItemLed();
      }
    }
  }
bool UsableItemClass::ProcessMedicaments(void)
  {
  ConnectedItemMedicamentsClass* Medicament  = this->GetConnectedItem()->AsMedicaments();
  #ifdef DEBUG_USART_USABLE_ITEM
  sprintf (USARTBuffer,"[UsableItemClass::ProcessMedicaments] Medicament->isValidItem()=%03u\r\n", Medicament->isValidItem());
  sendString(USARTBuffer);
  #endif // DEBUG_USART_USABLE_ITEM
  if (Medicament->isValidItem())
    {
    #ifdef DEBUG_USART_USABLE_ITEM
    sprintf (USARTBuffer,"[UsableItemClass::ProcessMedicaments] PlayerEffects.IsEffectActive(Medicament->GetEffect())=%03u, id=%03d\r\n", PlayerEffects.IsEffectActive(Medicament->GetEffect()), Medicament->GetEffect()->GetID());
    sendString(USARTBuffer);
    #endif // DEBUG_USART_USABLE_ITEM
    if (PlayerEffects.IsEffectActive(Medicament->GetEffect()))
      {
      //already active
      //nothing to do
      //while(1);
      }
    else
      {
      
      if (this->DecrementChargesWrite())
        {
//        Player.getEffects()->applyEffect(GameCFG.ItemTemplate.getItemApplyEffectID(this->GetConnectedItem()->GetID()), PlayerEffectsClass::EFFECT_SOURCE_ITEM_SLOT);
        //Player.GetEffects()->applyEffect(this->GetConnectedItem()->AsMedicaments()->GetEffectID(), PlayerEffectsOldClass::EFFECT_SOURCE_ITEM_SLOT);
        PlayerEffects.ApplyEffectInstance(Medicament->GetEffect());
        Player.GetStatistics()->playerMedicamentUseIncrement(this->GetConnectedItem()->GetID());
//        Player.save();
        return true;
        }
      else
        {
        //can't write??!
        //while(1);
        }
      }
    //while(1);
    }
  else //item is invalid
    {
    //while(1);
    }
  return false;
  }
bool UsableItemClass::use(void)
  {
  if (this->isItemIsNotConnected())
    {
    #ifdef DEBUG_USART_USABLE_ITEM
      sprintf (USARTBuffer,"[UsableItemClass::use] isItemIsNotConnected\r\n");
      sendString(USARTBuffer);
    #endif // DEBUG_USART_USABLE_ITEM
    return false;
    }
  if (this->connectedItem.isNotUsable())
    {
    #ifdef DEBUG_USART_USABLE_ITEM
      sprintf (USARTBuffer,"[UsableItemClass::use] isNotUsable\r\n");
      sendString(USARTBuffer);
    #endif // DEBUG_USART_USABLE_ITEM
    return false;
    }
  #ifdef DEBUG_USART_USABLE_ITEM
    sprintf (USARTBuffer,"[UsableItemClass::use] before this->connectedItem.GetType()=%03u, item id=%03d, EffectID=%03d, t=%03d\r\n", this->connectedItem.GetType(), this->connectedItem.GetID(), GameCFG.ItemTemplate.GetItemEffect(this->connectedItem.GetID())->GetID(), GameCFG.GetPlayerEffect(TemporaryClass::PLAYEREFFECT_ITEM_FIRSTAIDKIT)->GetID());
    sendString(USARTBuffer);
  #endif // DEBUG_USART_USABLE_ITEM
  
  switch (this->connectedItem.GetType())
    {
    case ITEM_TYPE_RESOURCE:
      {
      if (GameCFG.ItemTemplate.GetItemEffect(this->connectedItem.GetID()) != &PlayerEffects.PlayerEffect_NullEffect)
        {
        return this->ProcessMedicaments();
        }
      }
    break;
    case ITEM_TYPE_MEDICAMENTS:
      {
      return this->ProcessMedicaments();
      }
    break;

    case ITEM_TYPE_SUIT:
      {
      PlayerSuitClass* PlayerSuit = Player.GetSuit();
      if (this->GetConnectedItem()->GetID() == 0)//prevent change empty to empty
        {
        if (PlayerSuit->GetID() == 0)
          {
          return false;
          }
        }
      if (Player.GetSuit()->isValidSuitID(this->GetConnectedItem()->GetID()))
        {
        PlayerSuit->Wear(this);
        PlayerSuit->GetPreviousSuit()->WriteTo(this);
        return true;
        }
      return false;
      }
    break;
    
    case ITEM_TYPE_REPAIR_KITS:
      {
      /*
      if (this->connectedItem.GetID() == TemporaryClass::ITEMID_REPAIR_KIT)
        {
        if (this->DecrementChargesWrite())
          {
          Player.GetSuit()->repair(TemporaryClass::REPAIR_KIT_REPAIR_POINTS);
          return true;
          }
        }
      */
      }
    break;

    case ITEM_TYPE_QUEST:
      {
      
      if (this->GetConnectedItem()->GetID() == 0)//prevent change empty to empty
        {
        return false;
        }
      //ConnectedItemArray_t* ItemArray  = this->GetConnectedItem()->GetConnectedItemArrayAddr();
      //QuestID_t QID    = ItemArray[UsableItemClass::FLASHDATA_ITEM_ID];
      //QuestStatus_t QS  = Quest.StatusFromInt(ItemArray[UsableItemClass::FLASHDATA_ITEM_EX0]);

      EepromItemClass* Item  = this->GetConnectedItem()->GetItem();
      QuestID_t QID      = Item->GetID();
      QuestStatus_t QS    = Quest.StatusFromInt(Item->GetEx0());
//      QuestInstance* Q  = Quest.GetQuestInstance(QID);
      
//      Quest.RemoveQuest(QID);
      switch (QS)
        {
        case QuestStatus_t::QUEST_STATUS_COMPLETE:
          {
          Quest.CompleteQuest(QID);
          }
        break;
        case QuestStatus_t::QUEST_STATUS_INCOMPLETE:
          {
          Quest.GiveQuest(QID);
          }
        break;
        case QuestStatus_t::QUEST_STATUS_FAILED:
          {
          Quest.FailQuest(QID);
          }
        break;

        case QuestStatus_t::QUEST_STATUS_UNKNOWN:
        default:
          {
          Quest.RemoveQuest(QID);
          }
        break;
        }
      //Q->SetStatus(QS);
      
      /*
      ConnectedItemArray_t* ItemArray  = this->GetConnectedItem()->GetConnectedItemArrayAddr();
      sprintf (Lcd.lcd_buf,"%03d %03d  ", ItemArray[UsableItemClass::FLASHDATA_ITEM_ID], ItemArray[UsableItemClass::FLASHDATA_ITEM_EX0]);
      LcdString(1,LCD_LINE_5);
      Lcd.IsNeedUpdate  = true;
      Lcd.UpdateIfNeed();
      _delay_ms(1000);
      */
      return true;
      }
    break;
    }
  return false;
  }

void UsableItemClass::turnOffItemLed(void)
  {
  UsableItemLedPin::SetOutLow();
  }
void UsableItemClass::turnOnItemLed(uint8_t delay)
  {
  if (delay > this->ledOnTimer)
    {
    UsableItemLedPin::SetOutHigh();
    this->ledOnTimer        = delay;
    }
  }
void UsableItemClass::itemLedStatusSuccess(void)
  {
  this->turnOnItemLed(this->ITEMLED_TIMER_SUCCESS);
  }
void UsableItemClass::itemLedStatusError(void)
  {
  this->turnOnItemLed(this->ITEMLED_TIMER_ERROR);
  }

bool UsableItemClass::isItemConnected(void)
  {
//  return (this->GetConnectedItem()->GetID() != 0);
  return (this->GetConnectedItem()->GetType() != 0);
  }
bool UsableItemClass::isItemIsNotConnected(void)
  {
  return !(this->isItemConnected());
  }
void UsableItemClass::itemJustConnectedOrDisconnected(CONNECTION_STATE state)
  {
  EventSystem.ExternalEventArrived(EventSystemSpace::EVID_USABLE_ITEM_CONNECTED_DISCONNECTED, (void*)state);
  Lcd.IsNeedUpdate  = true;
  }
void UsableItemClass::itemJustConnected(void)
  {
  this->itemJustConnectedOrDisconnected(CONNECTION_STATE_CONNECTED);
  #ifdef DEBUG_USART_USABLE_ITEM
    sprintf (USARTBuffer,"[UsableItemClass::itemJustConnected] Switch? %01u. \r\n", PDASettings.isParameterSet(ConfigClass::SETTINGS_SWITCH_TO_CONNECTED_ITEM));
    sendString(USARTBuffer);
  #endif // DEBUG_USART_USABLE_ITEM
  if (PDASettings.isParameterSet(ConfigClass::SETTINGS_SWITCH_TO_CONNECTED_ITEM))
    {
    PDAMenu.SelectMenu(PDAMenu_MainInterface::MENUID_CONNECTED_ITEM);
    }
  //this->isItemPresents  = true;
  }
void UsableItemClass::itemJustDisconnected(void)
  {
  this->itemJustConnectedOrDisconnected(CONNECTION_STATE_DISCONNECTED);
  #ifdef DEBUG_USART_USABLE_ITEM
    sprintf (USARTBuffer,"[UsableItemClass::itemJustDisconnected]\r\n");
    sendString(USARTBuffer);
  #endif // DEBUG_USART_USABLE_ITEM
  this->CleanConnectedItem();
  
  //memset(this->connectedItem,0,this->CONNECTED_ITEM_SIZE);//TODO 
  //this->setConnectedItem(UsableItemClass::ITEM_TYPE_EMPTY, UsableItemClass::ITEM_SUBTYPE_NONE, TemporaryClass::ITEMID_NONE, UsableItemClass::DEVICE_STATUS_EMPTY, 0, 0, 0, 0);
  //this->isItemPresents  = false;
  }

void UsableItemClass::SetConnectedItem(uint8_t type, uint8_t subtype, uint8_t id, uint8_t status, uint16_t ex01, uint8_t ex2, uint8_t ex3)
  {
  this->SetConnectedItem(type, subtype, id, status, (ex01>>8)&255, (ex01&255), ex2, ex3);
  }


void UsableItemClass::SetConnectedItem(uint8_t type, uint8_t subtype, uint8_t id, uint8_t status, uint8_t ex0, uint8_t ex1, uint8_t ex2, uint8_t ex3)
  {

//  uint8_t* array  = this->connectedItem.GetConnectedItemArrayAddr();
//  array[this->FLASHDATA_ITEM_TYPE]    = type;
//  array[this->FLASHDATA_ITEM_SUBTYPE]    = subtype;
//  array[this->FLASHDATA_ITEM_ID]      = id;
//  array[this->FLASHDATA_ITEM_STATUS]    = status;
//  array[this->FLASHDATA_ITEM_EX0]      = ex0;
//  array[this->FLASHDATA_ITEM_EX1]      = ex1;
//  array[this->FLASHDATA_ITEM_EX2]      = ex2;
//  array[this->FLASHDATA_ITEM_EX3]      = ex3;

  EepromItemClass* Item  = this->connectedItem.GetItem();
  Item->SetType(type);
  Item->SetSubtype(subtype);
  Item->SetID(id);
  Item->SetStatus(status);
  Item->SetEx0(ex0);
  Item->SetEx1(ex1);
  Item->SetEx2(ex2);
  Item->SetEx3(ex3);
  }

bool UsableItemClass::ReadConnectedItem(void)
  {
//  if (UsableItemTWI::readFromDevice((UsableItemClass::PAGE_SIZE * UsableItemClass::ITEM_PAGE_ADDRESS), UsableItemClass::CONNECTED_ITEM_SIZE, this->GetConnectedItem()->GetConnectedItemArrayAddr()))
  if (UsableItemTWI::readFromDevice((UsableItemClass::PAGE_SIZE * UsableItemClass::ITEM_PAGE_ADDRESS), EepromItemClass::EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_SIZE, this->GetConnectedItem()->GetItem()->GetArray()))
    {
    return true;
    }
  return false;
  }
bool UsableItemClass::WriteConnectedItem(void)
  {
  //TODO переделать...
  //this->twi_write_page(this->ITEM_PAGE_ADDRESS,this->connectedItem);
//  if (UsableItemTWI::writeToDevice((this->ITEM_PAGE_ADDRESS * this->PAGE_SIZE), (1 * this->PAGE_SIZE), this->connectedItem.GetConnectedItemArrayAddr()))
  if (UsableItemTWI::writeToDevice((UsableItemClass::PAGE_SIZE * UsableItemClass::ITEM_PAGE_ADDRESS), EepromItemClass::EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_SIZE, this->GetConnectedItem()->GetItem()->GetArray()))
    {
    return true;
    }
  return false;
  }
bool UsableItemClass::IncrementChargesWrite(void)
  {
  if (!this->isSomeHardwareConnected())
    {
    return false;
    }
  #ifdef UNLIMITED_ITEMS
    return true;
  #endif
/*
  uint8_t* array  = this->connectedItem.GetConnectedItemArrayAddr();
  if (array[this->FLASHDATA_ITEM_EX0] == 0)
    {
    return false;
    }
  ++array[this->FLASHDATA_ITEM_EX0];
*/
  EepromItemClass* Item  = this->GetConnectedItem()->GetItem();
  if (Item->GetEx0() > 0)
    {
    Item->SetEx0(Item->GetEx0()+1);
    if (this->WriteConnectedItem())
      {
      return true;
      }
    else
      {
      Item->SetEx0(Item->GetEx0()-1);
      }
    }
  return false;
  }
bool UsableItemClass::DecrementChargesWrite(void)
  {
  if (!this->isSomeHardwareConnected())
    {
    return false;
    }
  #ifdef UNLIMITED_ITEMS
    return true;
  #endif
/*
  uint8_t* array  = this->connectedItem.GetConnectedItemArrayAddr();
  if (array[this->FLASHDATA_ITEM_EX0] == 0)
    {
    return false;
    }
  --array[this->FLASHDATA_ITEM_EX0];
*/
  EepromItemClass* Item  = this->GetConnectedItem()->GetItem();
  if (Item->GetEx0() > 0)
    {
    Item->SetEx0(Item->GetEx0()-1);
    if (this->WriteConnectedItem())
      {
      return true;
      }
    else
      {
      Item->SetEx0(Item->GetEx0()+1);
      }
    }
  return false;
  }
void UsableItemClass::scanForConnected(void)
  {
  //this->isItemPresents  = this->at24c02_readConnectedItem();
  //this->isItemPresents  = this->hardware->readFromDevice((this->PAGE_SIZE * this->ITEM_PAGE_ADDRESS), this->CONNECTED_ITEM_SIZE, this->connectedItemArray);
  //this->isItemPresents  = this->connectedItem.ReadHardware(this->hardware);
  this->connectedItem.ReadHardware(this);
  }
void UsableItemClass::scanForConnectedIfNeed(void)
  {
  if (Player.IsDead())//мёртвые на данный момент не используют препараты
    {
    return;
    }
  if (UsableItemItemConnectedPin::IsPinLow())
    {
    #ifdef DEBUG_USART_USABLE_ITEM
      sprintf (USARTBuffer,"[UsableItemClass::scanForConnectedIfNeed] scan show connected item. Something connected? %01u. rand() = %05u\r\n", this->isSomeHardwareConnected(), rand());
      sendString(USARTBuffer);
    #endif // DEBUG_USART_USABLE_ITEM
    //item presens
    if (this->isSomeHardwareDisconnected())
      {
      #ifdef DEBUG_USART_USABLE_ITEM
        sendString((char*)"[UsableItemClass::scanForConnectedIfNeed] HW disconnected. Connecting...");
      #endif // DEBUG_USART_USABLE_ITEM
      this->SetSomeHardwareConnected(true);
      this->itemJustConnected();
      }
    }
  else
    {
    if (this->isSomeHardwareConnected())
      {
      this->SetSomeHardwareConnected(false);
      this->itemJustDisconnected();
      }
    }
/*
  //  if (Config.isParameterSet(ConfigClass::SWITCH_TO_CONNECTED_ITEM) && IOPort.IsPinLow(USABLE_ITEM_ITEM_CONNECTED_PORT, USABLE_ITEM_ITEM_CONNECTED_PIN))
  if (Config.isParameterSet(ConfigClass::SWITCH_TO_CONNECTED_ITEM) && HAL.IO.IsPinLow(USABLE_ITEM_ITEM_CONNECTED_PIN_HAL))
    {
    
    }
*/
  
  if (this->isSomeHardwareConnected() && PDAMenu.getSelectedMenuID() == PDAMenu_MainInterface::MENUID_CONNECTED_ITEM)
    {
    this->scanForConnected();
    Lcd.IsNeedUpdate  = true;//т.к. может использоваться для просмотра вещей, т.е. итемы будут меняться
    }
  }
ItemType_t UsableItemClass::getConnectedItemType(void)
  {
  return this->connectedItem.GetType();
  //return this->connectedItem.connectedItemArray[UsableItemClass::FLASHDATA_ITEM_TYPE];
  }
ItemID_t UsableItemClass::getConnectedItemID(void)
  {
  return this->connectedItem.GetID();
  //return this->connectedItem.connectedItemArray[UsableItemClass::FLASHDATA_ITEM_ID];
  }
ItemName_t UsableItemClass::getItemName(ItemType_t type, ItemID_t id)
  {
  switch (type)
    {
    case ITEM_TYPE_RESOURCE:
    case ITEM_TYPE_MEDICAMENTS:
      {
//      return ItemsClass::NAMES[UsableItem.connectedItem[UsableItemClass::FLASHDATA_ITEM_ID]];
//      return GameCFG.ItemTemplate.getItemName(this->connectedItem.connectedItemArray[UsableItemClass::FLASHDATA_ITEM_ID]);
      return GameCFG.ItemTemplate.GetItemName(this->connectedItem.GetID());
      }
    break;
    
    case ITEM_TYPE_SUIT:
      {
      if (Player.GetSuit()->isValidSuitID(this->connectedItem.GetID()))
      //GameCFG.SuitsContainer.isValidSuitID(this->connectedItem.GetID()))
        {
        return (GameCFG.SuitsContainer.GetSuitName(this->connectedItem.GetID()));
        }
      //else
        {
//        return RAM_STR_Unknown;
        return RAM_STR_UNDEFINED;
        }
      }
    break;
    
    case ITEM_TYPE_INFORMATION:
      {
      if (this->getConnectedItemType() != type)
        {
//        return ItemsClass::NAMES[ItemsClass::ITEMID_NOITEM];
        return GameCFG.ItemTemplate.GetItemName(ItemTemplateClass::ITEMID_NOITEM);
        }
      if (this->getConnectedItemID() != id)
        {
        //return ItemsClass::NAMES[ItemsClass::ITEMID_NOITEM];
        return GameCFG.ItemTemplate.GetItemName(ItemTemplateClass::ITEMID_NOITEM);
        }
      ItemInformation.getHead(this->connectedItem.GetID(), this->itemInformationHead);
      return itemInformationHead;
      }
    break;
    
    case  ITEM_TYPE_ELSE:
      {
      return GameCFG.ItemTemplate.GetItemName(this->connectedItem.GetID());
      }
    break;

    case ITEM_TYPE_EMPTY:
    default:
      {
      
      }
    break;
    }
  //return ItemsClass::NAMES[ItemsClass::ITEMID_NOITEM];
  return GameCFG.ItemTemplate.GetItemName(ItemTemplateClass::ITEMID_NOITEM);
  //return this->ItemsClass::NAMES[UsableItem.connectedItem[UsableItemClass::FLASHDATA_ITEM_ID]]
  }
ItemName_t UsableItemClass::getConnectedItemName(void)
  {
  return this->getItemName(this->getConnectedItemType(), this->getConnectedItemID());
  }

ItemTypeName_t UsableItemClass::getItemTypeName(ItemType_t type)
  {
  STRClass Str;
  Str.SetPos(this->getConnectedItemTypeNamePOS(type));
  return Str;
  }
STR_POS UsableItemClass::getConnectedItemTypeNamePOS()
  {
  return this->getConnectedItemTypeNamePOS(this->getConnectedItemType());
  }
STR_POS UsableItemClass::getConnectedItemTypeNamePOS(ItemType_t type)
  {
  switch (type)
    {
    case ITEM_TYPE_RESOURCE:
      {
      return STRPOS_STR_ItemTypeResourcesName;
      }
    break;

    case ITEM_TYPE_MEDICAMENTS:
      {
      return STRPOS_STR_ItemTypeMedicamentsName;
      }
    break;

    case ITEM_TYPE_SUIT:
      {
      return STRPOS_STR_ItemTypeSuiteName;
      }
    break;

    case ITEM_TYPE_INFORMATION:
      {
      return STRPOS_STR_ItemTypeInformationName;
      }
    break;

    case ITEM_TYPE_QUEST:
      {
      return STRPOS_STR_ItemTypeQuestName;
      }
    break;

    case ITEM_TYPE_ELSE:
      {
      return STRPOS_STR_ItemTypeElseName;
      }
    break;
    }
  return STRPOS_STR_ItemTypeEmptyName;
  }
ItemTypeName_t UsableItemClass::getConnectedItemTypeName(void)
  {
  return this->getItemTypeName(this->getConnectedItemType());
  }
void UsableItemClass::CleanConnectedItem(void)
  {
  this->connectedItem.Clean();
  }
ConnectedItemClass* UsableItemClass::GetConnectedItem(void)
  {
  return &this->connectedItem;
  }
//TWI* UsableItemClass::GetHardware(void)
//  {
//  return this->hardware;
//  }
/*
ConnectedItemArray_t* UsableItemClass::GetConnectedItemArray(void)
  {
  return this->connectedItemArray;
  }
*/
bool UsableItemClass::isSomeHardwareConnected(void)
  {
  return this->m_isSomethingConnected;
  }
bool UsableItemClass::isSomeHardwareDisconnected(void)
  {
  return !(this->isSomeHardwareConnected());
  }
void UsableItemClass::SetSomeHardwareConnected(bool value)
  {
  this->m_isSomethingConnected  = value;
  }

/*
void UsableItemClass::twi_stop(void)
  {
  AT24C02_TWI.MASTER.CTRLC = TWI_MASTER_ACKACT_bm | TWI_MASTER_CMD_STOP_gc;
  }
bool UsableItemClass::twi_write_page(uint8_t page, uint8_t *writeData)
  {
  uint8_t address,i,j;
  address  = page << 3;//page=8byte
  
  //TWI - If the R/W bit is low, it indicates a master write transaction
  //uint8_t i;

  j=0;
  AT24C02_TWI.MASTER.ADDR  = AT24C02_SLAVE_ADDRESS;
  while(!(AT24C02_TWI.MASTER.STATUS  & TWI_MASTER_WIF_bm))
    {
    if (++j == 96)//64 - малоб 70 - норм
      {
      this->twi_stop();
      return false;
      }
    delay_us(1);
    }

  j=0;
  AT24C02_TWI.MASTER.DATA  = address;
  while(!(AT24C02_TWI.MASTER.STATUS  & TWI_MASTER_WIF_bm))
    {
    if (++j == 96)//64 - малоб 70 - норм
      {
      this->twi_stop();
      return false;
      }
    delay_us(1);
    }
  for(i=0;i<8;i++)
    {
    j=0;
    AT24C02_TWI.MASTER.DATA  = writeData[i];
    while(!(AT24C02_TWI.MASTER.STATUS  & TWI_MASTER_WIF_bm))
      {
      if (++j == 96)//64 - малоб 70 - норм
        {
        this->twi_stop();
        return false;
        }
      delay_us(1);
      }
    }
  this->twi_stop();
  delay_ms(5);
  return true;
  }

void UsableItemClass::twi_write_byte(uint8_t eepromAddress, uint8_t writeData)
  {
  //TWI - If the R/W bit is low, it indicates a master write transaction
  AT24C02_TWI.MASTER.ADDR    = AT24C02_SLAVE_ADDRESS;
  while(!(AT24C02_TWI.MASTER.STATUS  & TWI_MASTER_WIF_bm));

  AT24C02_TWI.MASTER.DATA    = eepromAddress;
  while(!(AT24C02_TWI.MASTER.STATUS  & TWI_MASTER_WIF_bm));

  AT24C02_TWI.MASTER.DATA    = writeData;
  while(!(AT24C02_TWI.MASTER.STATUS  & TWI_MASTER_WIF_bm));

  AT24C02_TWI.MASTER.CTRLC  = TWI_MASTER_CMD_STOP_gc;
//  while (AT24C02_TWI.MASTER.STATUS != TWI_MASTER_BUSSTATE0_bm);

  delay_ms(5);//Write Cycle Time - 5ms ёбаный ты в рот!!!! КАК этого избежать?
  }
bool UsableItemClass::at24c02_readCustomlPage(uint8_t address, uint8_t pageSize, uint8_t pageNum, char *data)
  {
  uint8_t i,j=0;

  AT24C02_TWI.MASTER.ADDR = AT24C02_SLAVE_ADDRESS;
  while(!(AT24C02_TWI.MASTER.STATUS&TWI_MASTER_WIF_bm));

  AT24C02_TWI.MASTER.DATA = address + pageNum * pageSize;// write word addrpointer first
  AT24C02_TWI.MASTER.ADDR = AT24C02_SLAVE_ADDRESS | 1;// send read command
  

  for(i=0;i<pageSize;i++)
    {
    j=0;
    while(!(AT24C02_TWI.MASTER.STATUS&TWI_MASTER_RIF_bm))
      {
      if (++j == 96)//64 - малоб 70 - норм
        return false;
      delay_us(1);
      }
    data[i]  = AT24C02_TWI.MASTER.DATA;
    }
  return true;
  }
*/
/*
bool UsableItemClass::at24c02_readCustomlPage(uint8_t address, uint8_t pageSize, uint8_t pageNum, uint8_t *data)
  {
  uint8_t i,j=0;

  AT24C02_TWI.MASTER.ADDR = AT24C02_SLAVE_ADDRESS;
  while(!(AT24C02_TWI.MASTER.STATUS&TWI_MASTER_WIF_bm))
    {
    if (++j == 96)//64 - малоб 70 - норм
      return false;
    }

  AT24C02_TWI.MASTER.DATA = address + pageNum * pageSize;// write word addrpointer first
  AT24C02_TWI.MASTER.ADDR = AT24C02_SLAVE_ADDRESS | 1;// send read command
  

  for(i=0;i<pageSize;i++)
    {
    j=0;
    while(!(AT24C02_TWI.MASTER.STATUS&TWI_MASTER_RIF_bm))
      {
      if (++j == 96)//64 - малоб 70 - норм
        return false;
      delay_us(1);
      }
    data[i]  = AT24C02_TWI.MASTER.DATA;
    }
  return true;
  }
*/

//void twi_read_at(TWI_t *twiname, uint8_t *readData)
//bool UsableItemClass::at24c02_readConnectedItem1()
//  {
//  bool ret  = this->hardware->readFromDevice((this->PAGE_SIZE * this->ITEM_PAGE_ADDRESS), this->CONNECTED_ITEM_SIZE, this->connectedItem);//БАГ С ЭТИМ ЕБУЧИМ НУЛЁМ!!! лабо записывается неверно, либо читается - что-то с адресом
//  return ret;
  /*this->at24c02_read_pages(this->ITEM_PAGE_ADDRESS, 1, this->connectedItem);
  sprintf (lcd_buf, "%03d%03d %03d%03d", this->connectedItem[0], this->connectedItem[1], this->connectedItem[2], this->connectedItem[3]);
  
  ng(1,LCD_LINE_1);
  sprintf (lcd_buf, "%03d%03d %03d%03d", this->connectedItem[4], this->connectedItem[5], this->connectedItem[6], this->connectedItem[7]);
  LcdString(1,LCD_LINE_2);
  LcdUpdate();
  _delay_ms(5000);*/
  //return this->at24c02_read_pages(this->ITEM_PAGE_ADDRESS, 1, this->connectedItem);
  //bool ret  = this->at24c02_read_pages(this->ITEM_PAGE_ADDRESS, this->ITEM_PAGE_ADDRESS, this->connectedItem);
  /*while(1)
    {
    //this->hardware->readFromDevice((this->PAGE_SIZE * this->ITEM_PAGE_ADDRESS), 0, this->connectedItem);//БАГ С ЭТИМ ЕБУЧИМ НУЛЁМ!!! лабо записывается неверно, либо читается - что-то с адресом
    sprintf (lcd_buf, "%03d%03d %03d%03d", this->connectedItem[0],this->connectedItem[1],this->connectedItem[2],this->connectedItem[3]);
    LcdString(1,LCD_LINE_1);
    sprintf (lcd_buf, "%03d%03d %03d%03d", this->connectedItem[4],this->connectedItem[5],this->connectedItem[6],this->connectedItem[7]);
    LcdString(1,LCD_LINE_2);
    sprintf (lcd_buf, "%03d %01d",++randomPseudo, ret);
    LcdString(1,LCD_LINE_3);
    LcdUpdate();
    _delay_ms(1000);
    }*/
//  }
/*
bool UsableItemClass::at24c02_read_pages(uint8_t page, uint8_t pagesToRead, uint8_t *readData)
  {
  uint8_t address, bytesToRead;
  address    = this->PAGE_SIZE * page;//то есть 0я страница - адрес=0, 1я страница - 8, и т.д.
  
  bytesToRead  = pagesToRead * this->PAGE_SIZE;

  return this->at24c02_read_bytes(address, bytesToRead, readData);
  }
bool UsableItemClass::at24c02_read_bytes(uint8_t addressStart, uint8_t bytesToRead, uint8_t *readData)
  {
  uint8_t i,j=0;

  //addressStart--;//хуй знает что происходит, но адрес в еепроме увеличивается, посему так

  
  
  AT24C02_TWI.MASTER.ADDR = AT24C02_SLAVE_ADDRESS & ~0x01;
  j=0;
  while (!(AT24C02_TWI.MASTER.STATUS & TWI_MASTER_WIF_bm) || (AT24C02_TWI.MASTER.STATUS & TWI_SLAVE_RXACK_bm))
    {
    if (++j == 64)//32 - малоб 48 - норм
      {
      this->twi_stop();
      //while(1);
      return false;
      }
    delay_us(1);
    }

  AT24C02_TWI.MASTER.DATA = addressStart;
  j=0;
  while (!(AT24C02_TWI.MASTER.STATUS & TWI_MASTER_WIF_bm) || (AT24C02_TWI.MASTER.STATUS & TWI_SLAVE_RXACK_bm))
    {
    if (++j == 96)//64 - малоб 70 - норм
      {
      this->twi_stop();
      return false;
      }
    delay_us(1);
    }
  
  AT24C02_TWI.MASTER.ADDR = AT24C02_SLAVE_ADDRESS | 0x01;
//  
//  while (!(AT24C02_TWI.MASTER.STATUS & TWI_MASTER_RIF_bm))
//    {
//    if (++j == 96)//64 - малоб 70 - норм
//      {
//      this->twi_stop();
//      return false;
//      }
//    delay_us(1);
//    }

  AT24C02_TWI.MASTER.STATUS |= TWI_MASTER_RIF_bm;
  AT24C02_TWI.MASTER.CTRLC = TWI_MASTER_CMD_RECVTRANS_gc;
  for(i=0;i<bytesToRead;i++)
    {// read date and time
    j=0;
    while(!(AT24C02_TWI.MASTER.STATUS&TWI_MASTER_RIF_bm))
      {
      if (++j == 96)//64 - малоб 70 - норм
        {
        this->twi_stop();
        return false;
        }
      delay_us(1);
      }
    readData[i]  = AT24C02_TWI.MASTER.DATA;
    }
  this->twi_stop();
  return true;
  }
*/
/* TWI_MASTER.STATUS  bit masks and bit positions 
#define TWI_MASTER_RIF_bm  0x80  Read Interrupt Flag bit mask. 
#define TWI_MASTER_RIF_bp  7  Read Interrupt Flag bit position. 

#define TWI_MASTER_WIF_bm  0x40  Write Interrupt Flag bit mask. 
#define TWI_MASTER_WIF_bp  6  Write Interrupt Flag bit position.

#define TWI_MASTER_CLKHOLD_bm  0x20  Clock Hold bit mask.
#define TWI_MASTER_CLKHOLD_bp  5  Clock Hold bit position.

#define TWI_MASTER_RXACK_bm  0x10  Received Acknowledge bit mask.
#define TWI_MASTER_RXACK_bp  4  Received Acknowledge bit position.

#define TWI_MASTER_ARBLOST_bm  0x08  Arbitration Lost bit mask.
#define TWI_MASTER_ARBLOST_bp  3  Arbitration Lost bit position.

#define TWI_MASTER_BUSERR_bm  0x04  Bus Error bit mask.
#define TWI_MASTER_BUSERR_bp  2  Bus Error bit position.

#define TWI_MASTER_BUSSTATE_gm  0x03  Bus State group mask.
#define TWI_MASTER_BUSSTATE_gp  0  Bus State group position.
#define TWI_MASTER_BUSSTATE0_bm  (1<<0)  Bus State bit 0 mask.
#define TWI_MASTER_BUSSTATE0_bp  0  Bus State bit 0 position.
#define TWI_MASTER_BUSSTATE1_bm  (1<<1)   Bus State bit 1 mask.
#define TWI_MASTER_BUSSTATE1_bp  1   Bus State bit 1 position.
*/
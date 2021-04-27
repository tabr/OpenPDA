// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * PDAMenu_MenuItems.cpp
 *
 * Created: 2015-08-03 11:48:33
 *  Author: tabr
 */ 

void PDAMenu_MainClass::JustSelected(void)
  {
  if (Player.IsAlive())
    {
    SelectedSkin->DrawMainGrid();
    }
  else
    {
    if (Player.IsZombie())
      {
      SelectedSkin->DrawPlayerZombie();
      }
    else
      {
      SelectedSkin->DrawPlayerDead();
      }
    }
  this->timerUpdate = this->TIMER_UPDATE_VALUE;
#ifndef DEBUG_BUILD
    //this->chargeDotsRest  = 0;
    //this->mode            = PIXEL_ON;
    //this->prevDots        = 0;
  SelectedSkin->GetChargeVisualisationInterface()->Display();
#endif
  }
//void PDAMenu_MainClass::Select(void)
void PDAMenu_MainClass::ChargeStateChanged(PowerManagerClass::CHARGE_STATES state)
  {
  if (state == PowerManagerClass::CHARGE_STATE_CHARGING)
    {
    SelectedSkin->GetChargeVisualisationInterface()->SetCharging();
    }
  else
    {
    SelectedSkin->GetChargeVisualisationInterface()->SetDischarging();
    }
//#ifndef DEBUG_BUILD
  //this->chargeDotsRest  = 0;
  //this->mode        = PIXEL_ON;
  //this->prevDots      = 0;
  //clearing battery body
  //for (uint8_t i=0;i<80-69-1;i++)
  //  {
  //  LcdLine(80-1-i, 1+1, 80-1-i, 1+5, PIXEL_OFF);
  //  }
//#endif
  }
PDAMenu_MainClass::PDAMenu_MainClass(void)
  {
  EventSystem.RegisterUserEvent(EventSystemSpace::EVID_CHGARGE_STATE_CHANGED_TO, this);
  }
void PDAMenu_MainClass::EventArrived(EventSystemSpace::EVIDS evID, void* parameters)
  {
  #warning "[T] HACK! USE REFERENCE! V542 Consider inspecting an odd type cast: 'void *' to 'unsigned short'. pdamenu_menuitems.cpp 61"
  uint16_t state = (uint16_t)parameters; //-V542
  //uint16_t state = static_cast<uint16_t>(parameters);
  if (state < PowerManagerClass::CHARGE_STATES::CHARGE_STATES_NUM)
    {
    #warning "[T] HACK! change to interface call!"
    //PDAMenu.PDAMenu_Main.ChargeStateChanged((static_cast<PowerManagerClass::CHARGE_STATES>((uint16_t)state)));
    this->ChargeStateChanged((static_cast<PowerManagerClass::CHARGE_STATES>(state)));
    }
  else //error
    {
    //PDAMenu.PDAMenu_Main.ChargeStateChanged((static_cast<PowerManagerClass::CHARGE_STATES>(PowerManagerClass::CHARGE_STATES::CHARGE_STATES_NUM-1)));
    }
  }
void PDAMenu_MainClass::Update(uint8_t msPassed)
  {
  this->timerUpdate  += msPassed;
  SelectedSkin->Update(msPassed);
  if (this->timerUpdate < this->TIMER_UPDATE_VALUE)
    {
    return;
    }
  this->timerUpdate -= this->TIMER_UPDATE_VALUE;
  #ifndef DEBUG_BUILD
  SelectedSkin->UpdateMainMenuScreen();
  SelectedSkin->GetChargeVisualisationInterface()->Display();//need because UpdateMainMenuScreen() updating WHOLE screen
  SelectedSkin->GetChargeVisualisationInterface()->UpdateChargeVisualisation(PowerManager.GetChargePercent(), PowerManager.isCharging());
//  SelectedSkin->DisplayPlayerInSafeShelter(PlayerEffects.IsEffectActive(TemporaryClass::PLAYEREFFECT_SAFE_SHELTER));
  SelectedSkin->DisplayPlayerInSafeShelter(PlayerEffects.IsEffectActive(EffectSafeShelterHack));

  SelectedSkin->DisplayBlowoutActive(BlowoutTimer > 0);//if > 0 mean active

  #endif

  
  Lcd.IsMainScreenNeedRedraw  = false;
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_MainClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUID_MAIN;
  }
void PDAMenu_MainClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  if (btn == ButtonsClass::BUTTON_CENTER_MENU)
    {
//    #warning "TMP"
//    uint8_t t;
//    PDASound.Buf.Write(1);
    //SoundBuffer.Read(t);
    //PDASound.PlaySampleIfNeed();
    //PDASound.FillBufer();
    }
  };

void PDAMenu_ArtefactsConnectedClass::JustSelected(void)
  {
  STRClass Str;

  SuitContainersNum_t cNum  = Player.GetSuit()->getContainersNum();

  //StalkerUI.DisplayMenuHead(STRPOS_STR_PDAMENU_ARTEFACTS);
  //sprintf (Lcd.lcd_buf, "%01u", cNum);
  //StalkerUI.DisplayString(12,StalkerUI_Class::UI_LCD_LINE_0, Lcd.lcd_buf);
  
  Str.SetPos(STRPOS_STR_PDAMENU_ARTEFACTS_FORMAT);
  Str.WriteFormat(Lcd.lcd_buf, cNum);
  StalkerUI.DisplayMenuHead(Str);

  for (SuitContainersNum_t i=cNum; i > 0 ;i--)
    {
    //sprintf (Lcd.lcd_buf,"%d: ",i);
    //        LcdString(1,LCD_LINE_1 + i);
    //sprintf_P (Lcd.lcd_buf, STR_CONTAINERS_NUM_FORMAT, i);
    TODO("Переделать под постраничный просмотр");
    //LcdString(1,artLines[i-1]);
    //StalkerUI.DisplayMenuBody(i-1);
    //StalkerUI.DisplayString(i);
    Str.SetPos(STRPOS_STR_CONTAINERS_NUM_FORMAT);
    Str.WriteFormat(Lcd.lcd_buf, i);
//    StalkerUI.DisplayString(Str, static_cast<StalkerUI_Class::UI_LCD_LINE>(i));
    StalkerUI.DisplayString(Str, StalkerUI.ToStringLine(i));
    }
  }
void PDAMenu_ArtefactsConnectedClass::Update(uint8_t msPassed)
  {
  /*sprintf (lcd_buf,"%03u %05u", PlayerSuit.getContainersNum(), rand());
  LcdString(1,LCD_LINE_1);
  LcdUpdate();
  while(1);*/
  
  for (uint8_t i=0;i<Player.GetSuit()->getContainersNum();i++)
    {
    //        if    (ArtefactPorts.artefactsConnected[i].isArtefactValid())
    //sprintf (lcd_buf,);
    //        else
    //          sprintf (lcd_buf,"(---)");
    //        LcdString(4,i+1+1);
    //LcdString(4,artLines[i], Player.getArtefactPorts()->getConnectedArtefact(i)->getArtefactName());
//    StalkerUI.DisplayString(4, (i+1), Player.GetArtefactPorts()->getConnectedArtefact(i)->getArtefactName());
    //StalkerUI.DisplayString(4, (i+1), Player.GetArtefactPorts()->getConnectedArtefact(i)->getArtefactName());
    StalkerUI.DisplayString(Player.GetArtefactPorts()->GetConnectedArtefact(i)->getArtefactName(), StalkerUI.ToStringLine(i+1), 4);
    }
  Lcd.IsNeedUpdate  = true;
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_ArtefactsConnectedClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUID_ARTEFACTS_CONNECTED;
  }



void PDAMenu_ConnectedItemClass::JustSelected(void)
  {
  StalkerUI.DisplayMenuHead(STRPOS_STR_PDAMENU_CONNECTED_ITEMS);
  //LcdString(1, LCD_LINE_1, STR_PDAMENU_CONNECTED_ITEMS);
//  StalkerUI.DisplayString(12,StalkerUI_Class::UI_LCD_LINE_5, STR_USE);
  //LcdUpdate();
  //while(1);
  
  Lcd.IsNeedUpdate=true;
  }
void PDAMenu_ConnectedItemClass::Update(uint8_t msPassed)
  {
  this->timerUpdate  += msPassed;
  if (this->timerUpdate < 250)
    {
    return;
    }
  this->timerUpdate -= 250;
  if (UsableItem.isItemConnected())
    {
    #ifdef DEBUG_USART_USABLE_ITEM
      sprintf (USARTBuffer,"[PDAMenu_ConnectedItemClass::Update] UsableItem.isItemConnected()\r\n");
      sendString(USARTBuffer);
    #endif
    StalkerUI.DisplayEmptyBodyString(StalkerUI_Class::UI_MENU_BODY_LINE_0);
    StalkerUI.DisplayEmptyBodyString(StalkerUI_Class::UI_MENU_BODY_LINE_1);
    
    //UsableItem.getConnectedItemTypeName().WriteTo(Lcd.lcd_buf);
    StalkerUI.DisplayMenuBody(UsableItem.getConnectedItemTypeNamePOS(), StalkerUI_Class::UI_MENU_BODY_LINE_0);
    StalkerUI.DisplayMenuBody(UsableItem.getConnectedItemName(), StalkerUI_Class::UI_MENU_BODY_LINE_1);
    switch (UsableItem.getConnectedItemType())
      {
      case UsableItemClass::ITEM_TYPE_MEDICAMENTS:
        {
//        ConnectedItemMedicamentsClass Medicaments  = ConnectedItemMedicamentsClass (UsableItem.GetConnectedItem());
//        sprintf_P (Lcd.lcd_buf, STR_MENU_CHARGES_FORMAT, ((ConnectedItemMedicamentsClass*)UsableItem.GetConnectedItem())->GetChargesNum());
        //sprintf_P (Lcd.lcd_buf, STR_MENU_CHARGES_FORMAT, UsableItem.GetConnectedItem()->AsMedicaments()->GetChargesNum());
        //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_2);
        //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_2, STRPOS_STR_MENU_CHARGES_FORMAT, UsableItem.GetConnectedItem()->AsMedicaments()->GetChargesNum());
        STRClass Str(STRPOS_STR_MENU_CHARGES_FORMAT);
        Str.WriteFormat(Lcd.lcd_buf, UsableItem.GetConnectedItem()->AsMedicaments()->GetChargesNum());
        StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_2);
        }
      break;

      case UsableItemClass::ITEM_TYPE_RESOURCE:
        {
        //sprintf_P (Lcd.lcd_buf, STR_MENU_PCS_FORMAT, UsableItem.GetConnectedItem()->AsResource()->GetPCS());
        //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_2);
        //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_2, STRPOS_STR_MENU_PCS_FORMAT, UsableItem.GetConnectedItem()->AsResource()->GetPCS());
        STRClass Str(STRPOS_STR_MENU_PCS_FORMAT);
        Str.WriteFormat(Lcd.lcd_buf, UsableItem.GetConnectedItem()->AsResource()->GetPCS());
        StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_2);
        break;
        }
      case UsableItemClass::ITEM_TYPE_REPAIR_KITS:
        {
        //sprintf_P (Lcd.lcd_buf, STR_MENU_PCS_FORMAT, UsableItem.GetConnectedItem()->AsRepairKit()->GetPCS());
        //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_2);
        //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_2, STRPOS_STR_MENU_PCS_FORMAT, UsableItem.GetConnectedItem()->AsRepairKit()->GetPCS());
        STRClass Str(STRPOS_STR_MENU_PCS_FORMAT);
        Str.WriteFormat(Lcd.lcd_buf, UsableItem.GetConnectedItem()->AsRepairKit()->GetPCS());
        StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_2);
        }
      break;
          
      case UsableItemClass::ITEM_TYPE_SUIT:
        {
        //ConnectedItemSuitClass ConnectedItemSuit  = ConnectedItemSuitClass(UsableItem.GetConnectedItem());
        //sprintf_P (Lcd.lcd_buf, STR_MENU_DURABILITY_FORMAT, UsableItem.GetConnectedItem()->AsSuit()->GetDurablity());
        //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_2);
        //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_2, STRPOS_STR_MENU_DURABILITY_FORMAT, UsableItem.GetConnectedItem()->AsSuit()->GetDurablity());
        STRClass Str(STRPOS_STR_MENU_DURABILITY_FORMAT);
        Str.WriteFormat(Lcd.lcd_buf, UsableItem.GetConnectedItem()->AsSuit()->GetDurablity());
        StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_2);
//        sprintf (lcd_buf,"статус: %03d   ", UsableItem.connectedItem[UsableItemClass::FLASHDATA_ITEM_STATUS]);
//        LcdString(1,LCD_LINE_5);
        }
      break;

      case UsableItemClass::ITEM_TYPE_QUEST:
        {
//        sprintf_P (Lcd.lcd_buf, STR_ID_FORMAT, UsableItem.GetConnectedItem()->GetConnectedItemArrayAddr()[UsableItemClass::FLASHDATA_ITEM_ID]);
        //sprintf_P (Lcd.lcd_buf, STR_ID_FORMAT, UsableItem.GetConnectedItem()->AsQuest()->GetID());
        //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_1);
        //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_1, STRPOS_STR_ID_FORMAT, UsableItem.GetConnectedItem()->AsQuest()->GetID());
        STRClass Str(STRPOS_STR_ID_FORMAT);
        Str.WriteFormat(Lcd.lcd_buf, UsableItem.GetConnectedItem()->AsQuest()->GetID());
        StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_1);
//        QuestStatus_t QS  = Quest.StatusFromInt(UsableItem.GetConnectedItem()->GetConnectedItemArrayAddr()[UsableItemClass::FLASHDATA_ITEM_EX0]);
        QuestStatus_t QS  = Quest.StatusFromInt(UsableItem.GetConnectedItem()->AsQuest()->GetQuestStatus());
        
//        Quest.GetQuestStatusName(QS, Lcd.lcd_buf);
//        StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_2, Quest.GetQuestStatusName(QS, Lcd.lcd_buf));
        StalkerUI.DisplayMenuBody(Quest.GetQuestStatusNamePOS(QS), StalkerUI_Class::UI_MENU_BODY_LINE_2);
        //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_2, STRPOS_);
        /*
        switch (UsableItem.GetConnectedItem()->GetConnectedItemArrayAddr()[UsableItemClass::FLASHDATA_ITEM_EX0])
          {
          case QuestStatus_t::QUEST_STATUS_INCOMPLETE:
            {
            StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_2, STR_PDAMENU_QUESTS_STATUS_INCOMPLETE);
            }
          break;
          case QuestStatus_t::QUEST_STATUS_COMPLETE:
            {
            StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_2, STR_PDAMENU_QUESTS_STATUS_COMPLETE);
            }
          break;
          case QuestStatus_t::QUEST_STATUS_FAILED:
            {
            StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_2, STR_PDAMENU_QUESTS_STATUS_FAILED);
            }
          break;
          case QuestStatus_t::QUEST_STATUS_UNKNOWN:
          default:
            {
            StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_2, STR_PDAMENU_QUESTS_STATUS_UNKNOWN);
            }
          break;
          }
        */
//        sprintf (Lcd.lcd_buf, "%u", UsableItem.GetConnectedItem()->GetConnectedItemArrayAddr()[UsableItemClass::FLASHDATA_ITEM_EX0]);
//        StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_2);
        
//        sprintf (lcd_buf,"статус: %03d   ", UsableItem.connectedItem[UsableItemClass::FLASHDATA_ITEM_STATUS]);
//        LcdString(1,LCD_LINE_5);
        }
      break;
//      case UsableItemClass::ITEM_TYPE_ELSE:
//        sprintf (lcd_buf,"зарядов: %03d  ", UsableItem.connectedItem[UsableItemClass::FLASHDATA_ITEM_EX0]);
//        LcdStringNoClean(1,LCD_LINE_4);
//      break;
          
      /*case UsableItemClass::ITEM_TYPE_QUEST_COMPLETE:
        Quest.completeQuest(TemporaryClass::QID_FIND_KEY);
        #warning remove this!
      break;*/

      case UsableItemClass::ITEM_TYPE_INFORMATION:
        {
        /*
        //uint8_t selectedPage    = menuBuffer[this->selectedSubMenuID];
        uint8_t pages        = UsableItem.connectedItem[UsableItemClass::FLASHDATA_ITEM_EX0];
        if (pages > UsableItemClass::ITEM_INFORMATION_MAXIMUM_DATA_LENGTH_PAGES)
          {
          pages  = UsableItemClass::ITEM_INFORMATION_MAXIMUM_DATA_LENGTH_PAGES;
          }
        this->maxSubMenuID      = (pages * UsableItemClass::PAGE_SIZE) / (DeviceConfigClass::LCD_CHARS_IN_LINE << 1);
            
        ItemInformation.getHead(UsableItem.connectedItem[UsableItemClass::FLASHDATA_ITEM_ID], lcd_buf);
        LcdString(1,LCD_LINE_3);
        ItemInformation.getBody(UsableItem.connectedItem[UsableItemClass::FLASHDATA_ITEM_ID], 0 + (this->selectedSubMenuID << 1), lcd_buf);
        LcdString(1,LCD_LINE_4);
        ItemInformation.getBody(UsableItem.connectedItem[UsableItemClass::FLASHDATA_ITEM_ID], 1 + (this->selectedSubMenuID << 1), lcd_buf);
        LcdString(1,LCD_LINE_5);*/
        }
      break;
      }
    }
  else
    {
    //LcdClear2_to_5();
    StalkerUI.ClearMenuBody();
    //LcdString(1,LCD_LINE_2, STR_PDAMENU_CONNECTED_ITEM_EMPTY);
    //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_0, STR_PDAMENU_CONNECTED_ITEM_EMPTY);
    StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_CONNECTED_ITEM_EMPTY, StalkerUI_Class::UI_MENU_BODY_LINE_0);
    //StalkerUI.DisplayString(StalkerUI_Class::UI_LCD_LINE_1, STR_PDAMENU_CONNECTED_ITEM_EMPTY);
    //LcdEmptyString(LCD_LINE_3);
    //LcdEmptyString(LCD_LINE_4);
    //LcdEmptyString(LCD_LINE_5);
    }
  //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_3,STR_PDAMENU_CONNECTED_ITEM_HELP_USE);
  StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_CONNECTED_ITEM_HELP_USE, StalkerUI_Class::UI_MENU_BODY_LINE_3);
  Lcd.IsNeedUpdate  = true;
//  sprintf (lcd_buf,"%03d из %03d %03d", (this->selectedSubMenuID+1), this->maxSubMenuID, RandomPseudo.get());
//  LcdString(1,LCD_LINE_6);
  //TODO добавить битовый параметр для этого меню, чтобы не обновлять постоянно
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_ConnectedItemClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUID_CONNECTED_ITEM;
  }
void PDAMenu_ConnectedItemClass::itemJustConnectedOrDisconnected(UsableItemClass::CONNECTION_STATE state)
  {
  #ifdef DEBUG_USART_EVENT_SYSTEM
    sprintf (USARTBuffer,"[PDAMenu_ConnectedItemClass::itemJustConnectedOrDisconnected] %03u\r\n",state);
    sendString(USARTBuffer);
  #endif
  if (state == UsableItemClass::CONNECTION_STATE_DISCONNECTED)
    {
    StalkerUI.ClearMenuBody();
    Lcd.IsNeedUpdate  = true;
    }
  }
void PDAMenu_ConnectedItemClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  if (Player.IsDead())
    {
    return;
    }
  if (btn == ButtonsClass::BUTTONS::BUTTON_CENTER_MENU)
    {
    this->JustSelected();
    if (UsableItem.use())
      {
      UsableItem.itemLedStatusSuccess();
      }
    else
      {
      UsableItem.itemLedStatusError();
      }
    }
  }


void PDAMenu_QuestsClass::JustSelected(void)
  {
//  LcdString(1,LCD_LINE_1, STR_PDAMENU_QUESTS);
//  LcdString(1,LCD_LINE_6, STR_NEXT_QUEST);
  StalkerUI.DisplayMenuHead(STRPOS_STR_PDAMENU_QUESTS);
//  StalkerUI.DisplayMenuBottom(STR_NEXT_QUEST);
  }
void PDAMenu_QuestsClass::Update(uint8_t msPassed)
  {
  this->updateCounter += msPassed;
    
  if (this->updateCounter < 500)
    {
    return;
    }
  this->updateCounter  -= 500;

  TODO("warning very bugged place!");
  QuestInstance* QArray[Quest.GetRegisteredQuestsNum()];
  QuestNum_t knownQuestsNum  = Quest.GetKnownList(QArray);
  if (knownQuestsNum == 0)
    {
    return;
    }
  if (this->selectedQuest == 0xFF)
    {
    this->selectedQuest  = (knownQuestsNum-1);
    }
  if (this->selectedQuest >= knownQuestsNum)
    {
    this->selectedQuest  = 0;
    }
  StalkerUI.ClearMenuBody();
  QuestInstance*  Q  = QArray[this->selectedQuest];
  //QID        = Quest.QuestStatusBuffer[this->selectedQuest];//в буфере отсчет с нуля
  /*
  QuestInstance*  Q  = static_cast<QuestInstance*>(Quest.GetContainer()->GetNextNode());
  for (QuestNum_t i=0;i<this->selectedQuest;i++)
    {
    Q  = static_cast<QuestInstance*>(Q->GetNextNode());
    }
  */
  
  //sprintf_P (Lcd.lcd_buf,STR_QUEST_NUMS_FORMAT, (this->selectedQuest+1), knownQuestsNum);
  //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_0);
  //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_0, STRPOS_STR_QUEST_NUMS_FORMAT, (this->selectedQuest+1), knownQuestsNum);
  STRClass Str(STRPOS_STR_QUEST_NUMS_FORMAT);
  Str.WriteFormat(Lcd.lcd_buf, (this->selectedQuest+1), knownQuestsNum);
  StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_0);
  char* QuestName           = Q->GetName();
  QuestNameLength_t QLength = Quest.GetNameLength(Q->GetID());
  //LcdString(1,LCD_LINE_3, name);
  StalkerUI.DisplayMenuBody(QuestName, StalkerUI_Class::UI_MENU_BODY_LINE_1);
  if (QLength > DeviceConfigClass::LCD_CHARS_IN_LINE)
    {
    //LcdString(1,LCD_LINE_4, (name+DeviceConfigClass::LCD_CHARS_IN_LINE));
    char* secondLine  = (QuestName+DeviceConfigClass::LCD_CHARS_IN_LINE);
    StalkerUI.DisplayMenuBody(secondLine, StalkerUI_Class::UI_MENU_BODY_LINE_2);
    if (QLength > (DeviceConfigClass::LCD_CHARS_IN_LINE * 2))
      {
      char* thirdLine = (QuestName+(DeviceConfigClass::LCD_CHARS_IN_LINE*2));
      StalkerUI.DisplayMenuBody(thirdLine, StalkerUI_Class::UI_MENU_BODY_LINE_3);
      }
//    StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_2, (char*)(name+2));
    //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_2, (char*)"afsdafsdf");
    }
//  sprintf (lcd_buf,"статус:       ");
//  LcdString(1,LCD_LINE_5);
  /*
  switch (Q->GetStatus())
    {
    case QuestStatus_t::QUEST_STATUS_INCOMPLETE:
      {
      //LcdString(1,LCD_LINE_5, STR_PDAMENU_QUESTS_STATUS_INCOMPLETE);
      //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_3, STR_PDAMENU_QUESTS_STATUS_INCOMPLETE);
      sprintf_P (Lcd.lcd_buf,STR_PDAMENU_QUESTS_STATUS_INCOMPLETE);
      }
    break;

    case QuestStatus_t::QUEST_STATUS_COMPLETE:
      {
      //LcdString(1,LCD_LINE_5, STR_PDAMENU_QUESTS_STATUS_COMPLETE);
      //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_3, STR_PDAMENU_QUESTS_STATUS_COMPLETE);
      sprintf_P (Lcd.lcd_buf,STR_PDAMENU_QUESTS_STATUS_COMPLETE);
      }
    break;

    case QuestStatus_t::QUEST_STATUS_FAILED:
      {
      //LcdString(1,LCD_LINE_5, STR_PDAMENU_QUESTS_STATUS_FAILED);
      //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_3, STR_PDAMENU_QUESTS_STATUS_FAILED);
      sprintf_P (Lcd.lcd_buf,STR_PDAMENU_QUESTS_STATUS_FAILED);
      }
    break;

    case QuestStatus_t::QUEST_STATUS_UNKNOWN:
    default:
      {
      //LcdString(1,LCD_LINE_5, STR_PDAMENU_QUESTS_STATUS_UNKNOWN);
      //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_3, STR_PDAMENU_QUESTS_STATUS_UNKNOWN);
      sprintf_P (Lcd.lcd_buf,STR_PDAMENU_QUESTS_STATUS_UNKNOWN);
      }
    }
  StalkerUI.DisplayMenuBottom();
  */
//  StalkerUI.DisplayMenuBottom(Quest.GetQuestStatusName(Q->GetStatus()));
  StalkerUI.DisplayMenuBottom(Quest.GetQuestStatusNamePOS(Q->GetStatus()));


  Lcd.IsNeedUpdate  = true;
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_QuestsClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUID_QUESTS;
  }
void PDAMenu_QuestsClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  if (btn == ButtonsClass::BUTTONS::BUTTON_DOWN_ENTER)
    {
    --this->selectedQuest;
    //TODO: встроить ограничение сюда?
    }
  else
    {
    ++this->selectedQuest;
    }
  }


void PDAMenu_ActionSuicideClass::JustSelected(void)
  {
  //LcdString(1,LCD_LINE_1, STR_PDAMENU_ACTIONS);
  //LcdString(1,LCD_LINE_2, STR_PDAMENU_ACTION_SUICIDE);
  StalkerUI.DisplayMenuHead(STRPOS_STR_PDAMENU_ACTIONS);
  StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_ACTION_SUICIDE, StalkerUI_Class::UI_MENU_BODY_LINE_0);
  Lcd.IsNeedUpdate  = true;
  }
void PDAMenu_ActionSuicideClass::Update(uint8_t msPassed)
  {
  if (Player.GetSuicideTimer() > 0)
    {
    //sprintf (Lcd.lcd_buf,"через %02d сек",ActionsClass::SUICIDE_DELAY_SEC - Player.selfSuicideCounter);
    //LcdString(1,LCD_LINE_3);
    //LcdString(1,LCD_LINE_4, STR_PDAMENU_SETTINGS_SUICIDE_INFO_2);
    //LcdString(1,LCD_LINE_5, STR_PDAMENU_SETTINGS_SUICIDE_INFO_3);
    
    //sprintf_P (Lcd.lcd_buf, STR_SUICIDE_AFTER_FORMAT, ActionsClass::SUICIDE_DELAY_SEC - Player.GetSuicideTimer());
    //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_1);
    //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_1, STRPOS_STR_SUICIDE_AFTER_FORMAT, ActionsClass::SUICIDE_DELAY_SEC - Player.GetSuicideTimer());
    STRClass Str(STRPOS_STR_SUICIDE_AFTER_FORMAT);
    Str.WriteFormat(Lcd.lcd_buf, ActionsClass::SUICIDE_DELAY_SEC - Player.GetSuicideTimer());
    StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_1);
    StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_SUICIDE_INFO_2, StalkerUI_Class::UI_MENU_BODY_LINE_2);
    StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_SUICIDE_INFO_3, StalkerUI_Class::UI_MENU_BODY_LINE_3);
    }
  else
    {
    StalkerUI.DisplayEmptyBodyString(StalkerUI_Class::UI_MENU_BODY_LINE_1);
    StalkerUI.DisplayEmptyBodyString(StalkerUI_Class::UI_MENU_BODY_LINE_2);
    StalkerUI.DisplayEmptyBodyString(StalkerUI_Class::UI_MENU_BODY_LINE_3);
    //LcdEmptyString(LCD_LINE_3);
    //LcdEmptyString(LCD_LINE_4);
    //LcdEmptyString(LCD_LINE_5);
    }
  Lcd.IsNeedUpdate  = true;
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_ActionSuicideClass::getID(void)
  {
  //return ActionsClass::ACTION_SUICIDE;
  return PDAMenu_MainInterface::MENUIDS::MENUID_ACTION_SUICIDE;
  }
void PDAMenu_ActionSuicideClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  if (Player.IsDead())
    {
    return;
    }
  //while (1) {sprintf (lcd_buf,"%03u %03u %05u", btn, suicideCounter, rand());LcdString(1,LCD_LINE_1);LcdUpdate();}

  if (btn == ButtonsClass::BUTTONS::BUTTON_CENTER_MENU && Player.GetSuicideTimer() == 0)
    {
    Player.StartSuicideCounter();
    }
  else if (Player.GetSuicideTimer() > 0)
    {
    Player.StopSuicideCounter();
    }
  }


/*
void PDAMenuActionsClass::JustSelected(void)
  {
  sprintf (lcd_buf, STR_PDAMENU_ACTIONS);
  LcdString(1,LCD_LINE_1);
  }
void PDAMenuActionsClass::Update(uint8_t msPassed)
  {
  }
PDAMenu_MainInterface::MENUIDS PDAMenuActionsClass::getID(void)
  {
  return PDAMenuClass::MENUID_ACTIONS;
  }
void PDAMenuActionsClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  }
*/




void PDAMenu_LastMeetAnomalyClass::JustSelected(void)
  {
  }
void PDAMenu_LastMeetAnomalyClass::Update(uint8_t msPassed)
  {
  //LcdString(1,LCD_LINE_1, STR_PDAMENU_LAST_MEET_ANOMALY);
  //LcdString(1,LCD_LINE_2, Anomaly.getLastMeetAnomalyName());
  StalkerUI.DisplayMenuHead(STRPOS_STR_PDAMENU_LAST_MEET_ANOMALY);
  //StalkerUI.DisplayMenuHead(STR_PDAMENU_LAST_MEET_ANOMALY);
  StalkerUI.DisplayMenuBody({Anomaly.getLastMeetAnomalyName()}, StalkerUI_Class::UI_MENU_BODY_LINE_0);
  Lcd.IsNeedUpdate      = true;
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_LastMeetAnomalyClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUID_LAST_MEET_ANOMALY;
  }
void PDAMenu_LastMeetAnomalyClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  }

/////////////////////////////////////////////////////////
void PDAMenu_SuitClass::JustSelected(void)
  {
  }
void PDAMenu_SuitClass::Update(uint8_t msPassed)
  {
  PlayerSuitClass* PlayerSuit = Player.GetSuit();

  StalkerUI.DisplayMenuHead(STRPOS_STR_PDAMENU_SUITE);
  //StalkerUI.DisplayMenuBody(PlayerSuit->getSuitName(), StalkerUI_Class::UI_MENU_BODY_LINE_0);

  //sprintf_P (Lcd.lcd_buf, STR_MENU_DURABILITY_FORMAT, Player.GetSuit()->getDurability());
  //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_1);
  //sprintf_P (Lcd.lcd_buf, STR_MENU_DURABILITY_MAX_FORMAT, Player.GetSuit()->getMaxDurability());
  //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_2);
  //sprintf_P (Lcd.lcd_buf, STR_MENU_DURABILITY_PERCENT_FORMAT, "%", Player.GetSuit()->getDurabilityPercent());
  //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_3);

  //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_1, STRPOS_STR_MENU_DURABILITY_FORMAT, Player.GetSuit()->getDurability());
  //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_2, STRPOS_STR_MENU_DURABILITY_MAX_FORMAT, Player.GetSuit()->getMaxDurability());
  //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_3, STRPOS_STR_MENU_DURABILITY_PERCENT_FORMAT, "%", Player.GetSuit()->getDurabilityPercent());


  STRClass Str(STRPOS_STR_MENU_SUIT_FORMAT);
  Str.WriteFormat(Lcd.lcd_buf, PlayerSuit->getSuitName(), PlayerSuit->getContainersNum());
  StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_0);

  Str.SetPos(STRPOS_STR_MENU_DURABILITY_FORMAT);
  Str.WriteFormat(Lcd.lcd_buf, PlayerSuit->getDurability());
  StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_1);

  Str.SetPos(STRPOS_STR_MENU_DURABILITY_MAX_FORMAT);
  Str.WriteFormat(Lcd.lcd_buf, PlayerSuit->getMaxDurability());
  StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_2);

  Str.SetPos(STRPOS_STR_MENU_DURABILITY_PERCENT_FORMAT);
  Str.WriteFormat(Lcd.lcd_buf, "%", PlayerSuit->getDurabilityPercent());
  StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_3);

  Lcd.IsNeedUpdate      = true;
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_SuitClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUID_SUIT;
  }
void PDAMenu_SuitClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  }
/////////////////////////////////////////////////////////////////////

void PDAMenu_PlayerInfoClass::JustSelected(void)
  {
  //LcdString(1,LCD_LINE_1, STR_PDAMENU_PLAYER);
  //LcdString(1,LCD_LINE_2, Player.getName());
  //sprintf (Lcd.lcd_buf,"ID: %03d",Player.getID());
  //LcdString(1,LCD_LINE_3);
  //LcdString(1,LCD_LINE_4, Player.getFactionName());
  
  
  StalkerUI.DisplayMenuHead(STRPOS_STR_PDAMENU_PLAYER);
  StalkerUI.DisplayMenuBody(Player.GetName(), StalkerUI_Class::UI_MENU_BODY_LINE_0);
//  sprintf_P (Lcd.lcd_buf, STR_ID_FORMAT, Player.GetID());
//  sprintf (Lcd.lcd_buf, "%u", Player.GetFactionID());
  //sprintf_P (Lcd.lcd_buf, STR_DEVID_FORMAT, DeviceConfig.GetID());
  //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_1);
  //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_1, STRPOS_STR_DEVID_FORMAT, DeviceConfig.GetID());
  STRClass Str(STRPOS_STR_DEVID_FORMAT);
  Str.WriteFormat(Lcd.lcd_buf, DeviceConfig.GetID());
  StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_1);
  StalkerUI.DisplayMenuBody({Player.GetFactionName()}, StalkerUI_Class::UI_MENU_BODY_LINE_2);
//  sprintf (Lcd.lcd_buf,"FID: %05d",Player.GetFactionID());
//  sprintf (Lcd.lcd_buf,"FID: %05d",GameCFG.GetFaction(3));
//  StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_2);
  this->Update(0);
  }
void PDAMenu_PlayerInfoClass::Update(uint8_t msPassed)
  {
  //sprintf (Lcd.lcd_buf,"%02u:%02u:%02u", TimeRTC.hour, TimeRTC.minute, TimeRTC.second);
  //LcdString(1,LCD_LINE_5);
  //sprintf_P (Lcd.lcd_buf, STR_TIME_FORMAT, TimeRTC.GetHour(), TimeRTC.GetMinute(), TimeRTC.GetSecond());
  //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_3);
  //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_3, STRPOS_STR_TIME_FORMAT, TimeRTC.GetHour(), TimeRTC.GetMinute(), TimeRTC.GetSecond());
  STRClass Str(STRPOS_STR_TIME_FORMAT);
  Str.WriteFormat(Lcd.lcd_buf, TimeRTC.GetHour(), TimeRTC.GetMinute(), TimeRTC.GetSecond());
  StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_3);
//  sprintf (Lcd.lcd_buf, "%03d", timeUpdateTimer);
//  StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_1);

  Lcd.IsNeedUpdate      = true;
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_PlayerInfoClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUID_PLAYER_INFO;
  }
void PDAMenu_PlayerInfoClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  }
///////////////////////////////////////////////////////////////////////
void PDAMenu_SettingsClass::JustSelected(void)
  {
  StalkerUI.DisplayMenuHead(STRPOS_STR_PDAMENU_SETTINGS);
  StalkerUI.ClearMenuBody();
  
  
  switch (this->selectedSettings)
    {
    case ConfigClass::SETTINGS_ARTEFACTS_LEDS_ON:
      {
      StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_ART_LED, StalkerUI_Class::UI_MENU_BODY_LINE_0);
      StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_ART_LED_INFO_1, StalkerUI_Class::UI_MENU_BODY_LINE_1);
      StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_ART_LED_INFO_2, StalkerUI_Class::UI_MENU_BODY_LINE_2);
      StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_ART_LED_INFO_3, StalkerUI_Class::UI_MENU_BODY_LINE_3);
      }
      if (PDASettings.isParameterSet(ConfigClass::SETTINGS_ARTEFACTS_LEDS_ON))
        {
        StalkerUI.DisplayMenuBody(STRPOS_STR_PLUS_BRACKED, StalkerUI_Class::UI_MENU_BODY_LINE_0);
        }
      else
        {
        StalkerUI.DisplayMenuBody(STRPOS_STR_MINUS_BRACKED, StalkerUI_Class::UI_MENU_BODY_LINE_0);
        }
    break;

    case ConfigClass::SETTINGS_BACKLIGHT_ON:
      {
      StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_BACKLIGHT, StalkerUI_Class::UI_MENU_BODY_LINE_0);
      StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_BACKLIGHT_INFO_1, StalkerUI_Class::UI_MENU_BODY_LINE_1);
      StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_BACKLIGHT_INFO_2, StalkerUI_Class::UI_MENU_BODY_LINE_2);
      if (PDASettings.isParameterSet(ConfigClass::SETTINGS_BACKLIGHT_ON))
        {
        StalkerUI.DisplayMenuBody(STRPOS_STR_PLUS_BRACKED, StalkerUI_Class::UI_MENU_BODY_LINE_0);
        }
      else
        {
        StalkerUI.DisplayMenuBody(STRPOS_STR_MINUS_BRACKED, StalkerUI_Class::UI_MENU_BODY_LINE_0);
        }
      }
    break;
    
    case ConfigClass::SETTINGS_RADIO_ON:
      {
      StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_RADIO, StalkerUI_Class::UI_MENU_BODY_LINE_0);
      StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_RADIO_INFO_1, StalkerUI_Class::UI_MENU_BODY_LINE_1);
      }
      if (PDASettings.isParameterSet(ConfigClass::SETTINGS_RADIO_ON))
        {
        StalkerUI.DisplayMenuBody(STRPOS_STR_PLUS_BRACKED, StalkerUI_Class::UI_MENU_BODY_LINE_0);
        }
      else
        {
        StalkerUI.DisplayMenuBody(STRPOS_STR_MINUS_BRACKED, StalkerUI_Class::UI_MENU_BODY_LINE_0);
        }
    break;
    
    case ConfigClass::SETTINGS_VIBRO_ON:
      {
      StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_VIBRO, StalkerUI_Class::UI_MENU_BODY_LINE_0);
      StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_VIBRO_INFO_1, StalkerUI_Class::UI_MENU_BODY_LINE_1);
      if (PDASettings.isParameterSet(ConfigClass::SETTINGS_VIBRO_ON))
        {
        StalkerUI.DisplayMenuBody(STRPOS_STR_PLUS_BRACKED, StalkerUI_Class::UI_MENU_BODY_LINE_0);
        }
      else
        {
        StalkerUI.DisplayMenuBody(STRPOS_STR_MINUS_BRACKED, StalkerUI_Class::UI_MENU_BODY_LINE_0);
        }
    }
    break;
    
    case ConfigClass::SETTINGS_SWITCH_TO_CONNECTED_ITEM:
      {
      StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_SWITH_ITEM, StalkerUI_Class::UI_MENU_BODY_LINE_0);
      StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_ITEM_INFO_1, StalkerUI_Class::UI_MENU_BODY_LINE_1);
      StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_ITEM_INFO_2, StalkerUI_Class::UI_MENU_BODY_LINE_2);
      StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_ITEM_INFO_3, StalkerUI_Class::UI_MENU_BODY_LINE_3);
      if (PDASettings.isParameterSet(ConfigClass::SETTINGS_SWITCH_TO_CONNECTED_ITEM))
        {
        StalkerUI.DisplayMenuBody(STRPOS_STR_PLUS_BRACKED, StalkerUI_Class::UI_MENU_BODY_LINE_0);
        }
      else
        {
        StalkerUI.DisplayMenuBody(STRPOS_STR_MINUS_BRACKED, StalkerUI_Class::UI_MENU_BODY_LINE_0);
        }
      }
    break;

    case ConfigClass::SETTINGS_SWITCH_TO_CONNECTED_ARTEFACT:
      {
      StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_SWITH_ART, StalkerUI_Class::UI_MENU_BODY_LINE_0);
      StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_ART_INFO_1, StalkerUI_Class::UI_MENU_BODY_LINE_1);
      StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_ART_INFO_2, StalkerUI_Class::UI_MENU_BODY_LINE_2);
      StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_ART_INFO_3, StalkerUI_Class::UI_MENU_BODY_LINE_3);
      if (PDASettings.isParameterSet(ConfigClass::SETTINGS_SWITCH_TO_CONNECTED_ARTEFACT))
        {
        StalkerUI.DisplayMenuBody(STRPOS_STR_PLUS_BRACKED, StalkerUI_Class::UI_MENU_BODY_LINE_0);
        }
      else
        {
        StalkerUI.DisplayMenuBody(STRPOS_STR_MINUS_BRACKED, StalkerUI_Class::UI_MENU_BODY_LINE_0);
        }
      }
    break;

    case ConfigClass::SETTINGS_NIGHT_MODE:
      {
      StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_NIGHT_MODE, StalkerUI_Class::UI_MENU_BODY_LINE_0);
      StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_NIGHT_MODE_INFO_1, StalkerUI_Class::UI_MENU_BODY_LINE_1);
      StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_NIGHT_MODE_INFO_2, StalkerUI_Class::UI_MENU_BODY_LINE_2);
      StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_SETTINGS_NIGHT_MODE_INFO_3, StalkerUI_Class::UI_MENU_BODY_LINE_3);
      if (PDASettings.isParameterSet(ConfigClass::SETTINGS_NIGHT_MODE))
        {
        StalkerUI.DisplayMenuBody(STRPOS_STR_PLUS_BRACKED, StalkerUI_Class::UI_MENU_BODY_LINE_0);
        }
      else
        {
        StalkerUI.DisplayMenuBody(STRPOS_STR_MINUS_BRACKED, StalkerUI_Class::UI_MENU_BODY_LINE_0);
        }
      }
    break;
    }
//  TODO("this is hack");
//  LcdString(11,LCD_LINE_6, STR_PDAMENU_6ROW_STR_USE);
//  LcdString(6,LCD_LINE_6, STR_PDAMENU_6ROW_DOWN);
  Lcd.IsNeedUpdate  = true;
  }
void PDAMenu_SettingsClass::Update(uint8_t msPassed)
  {
  
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_SettingsClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUID_SETTINGS;
  }
void PDAMenu_SettingsClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  if (btn == ButtonsClass::BUTTONS::BUTTON_DOWN_ENTER)
    {
    if (++this->selectedSettings >= ConfigClass::SETTINGS_PARAMETERS_NUM)
      {
      this->selectedSettings  = 0;
      }
    }
  else if (btn == ButtonsClass::BUTTONS::BUTTON_UP_ESC)
    {
    if (--this->selectedSettings >= ConfigClass::SETTINGS_PARAMETERS_NUM)
      {
      this->selectedSettings  = (ConfigClass::SETTINGS_PARAMETERS_NUM-1);
      }
    }
  else if (btn == ButtonsClass::BUTTONS::BUTTON_CENTER_MENU)
    {
    PDASettings.switchParameter(selectedSettings);
    }
  this->JustSelected();
  }


/////////////////////////////////////////////////////////////////
void PDAMenu_StatsClass::JustSelected(void)
  {
//  Lcd.IsNeedUpdate      = true;
  //LcdString(1, LCD_LINE_1, STR_PDAMENU_STATS);
  //LcdString(11,LCD_LINE_6, STR_DOWN);
  StalkerUI.DisplayMenuHead(STRPOS_STR_PDAMENU_STATS);
//  this->Update(500)
  //StalkerUI.ShowButtonDown();
  }
void PDAMenu_StatsClass::Update(uint8_t msPassed)
  {
  STRClass Str;

  this->updateCounter += msPassed;
  
  if (this->updateCounter < 500)
    {
    return;
    }
  this->updateCounter  -= 500;


  uint8_t scrollTMP=this->scroll;
//  for (uint8_t lcdRow=LCD_LINE_2; lcdRow<LCD_LINE_6; lcdRow++)
  for (uint8_t lcdRow=0; lcdRow<StalkerUI_Class::UI_MENU_BODY_LINE_SIZE; lcdRow++)
    {
    switch (scrollTMP)
      {
      case 0:
        {
        //sprintf (Lcd.lcd_buf,"макс  ХП   %03d",Player.getMaxHealth());
        //sprintf_P (Lcd.lcd_buf, STR_STAT_MAX_HP_FORMAT, Player.GetMaxHealth());
        //StalkerUI.DisplayMenuBodyF(StalkerUI.ToMenuBody(lcdRow), STRPOS_STR_STAT_MAX_HP_FORMAT, Player.GetMaxHealth());
        Str.SetPos(STRPOS_STR_STAT_MAX_HP_FORMAT);
        Str.WriteFormat(Lcd.lcd_buf, Player.GetMaxHealth());
        }
      break;

      case 1:
        {
        //sprintf (Lcd.lcd_buf,"реген ХП   %03d", Player.getRegenTime());
        //sprintf_P (Lcd.lcd_buf, STR_STAT_REGEN_HP_FORMAT, Player.GetRegenTime());
        //StalkerUI.DisplayMenuBodyF(StalkerUI.ToMenuBody(lcdRow), STRPOS_STR_STAT_REGEN_HP_FORMAT, Player.GetRegenTime());
        Str.SetPos(STRPOS_STR_STAT_REGEN_HP_FORMAT);
        Str.WriteFormat(Lcd.lcd_buf, Player.GetRegenTime());
        }
      break;

      case 2:
        {
        //sprintf (Lcd.lcd_buf,"сопр. рад  %03d",Player.getResistanceRadiation());
//        sprintf_P (Lcd.lcd_buf, STR_STAT_RAD_RESIST_FORMAT, Player.getResistanceRadiation());
//        sprintf_P (Lcd.lcd_buf, STR_STAT_RAD_RESIST_FORMAT, Player.getComplexDefenceFrom(TemporaryClass::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL));
        //sprintf_P (Lcd.lcd_buf, STR_STAT_RAD_RESIST_FORMAT, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL}));
        //StalkerUI.DisplayMenuBodyF(StalkerUI.ToMenuBody(lcdRow), STRPOS_STR_STAT_RAD_RESIST_FORMAT, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL}));
        Str.SetPos(STRPOS_STR_STAT_RAD_RESIST_FORMAT);
        Str.WriteFormat(Lcd.lcd_buf, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL}));
        }
      break;

      case 3:
        {
        //sprintf (Lcd.lcd_buf,"защ. рад   %03d", Player.getComplexDefenceFrom(DamageClass::DAMAGE_SOURCE_RADIATION_EXTERNAL));
        //sprintf_P (Lcd.lcd_buf, STR_STAT_DEF_RAD_FORMAT, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_RADIATION_EXTERNAL}));
        //StalkerUI.DisplayMenuBodyF(StalkerUI.ToMenuBody(lcdRow), STRPOS_STR_STAT_DEF_RAD_FORMAT, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_RADIATION_EXTERNAL}));
        Str.SetPos(STRPOS_STR_STAT_DEF_RAD_FORMAT);
        Str.WriteFormat(Lcd.lcd_buf, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_RADIATION_EXTERNAL}));
        }
      break;

      case 4:
        {
        //sprintf (Lcd.lcd_buf,"защ. огонь %03d", Player.getComplexDefenceFrom(DamageClass::DAMAGE_SOURCE_FIRE));
        //sprintf_P (Lcd.lcd_buf, STR_STAT_DEF_FIRE_FORMAT, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_FIRE}));
        //StalkerUI.DisplayMenuBodyF(StalkerUI.ToMenuBody(lcdRow), STRPOS_STR_STAT_DEF_FIRE_FORMAT, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_FIRE}));
        Str.SetPos(STRPOS_STR_STAT_DEF_FIRE_FORMAT);
        Str.WriteFormat(Lcd.lcd_buf, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_FIRE}));
        }
      break;

      case 5:
        {
        //sprintf (Lcd.lcd_buf,"защ. хим   %03d", Player.getComplexDefenceFrom(DamageClass::DAMAGE_SOURCE_CHEMICAL));
        //sprintf_P (Lcd.lcd_buf, STR_STAT_DEF_CHEMICAL_FORMAT, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_CHEMICAL}));
        //StalkerUI.DisplayMenuBodyF(StalkerUI.ToMenuBody(lcdRow), STRPOS_STR_STAT_DEF_CHEMICAL_FORMAT, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_CHEMICAL}));
        Str.SetPos(STRPOS_STR_STAT_DEF_CHEMICAL_FORMAT);
        Str.WriteFormat(Lcd.lcd_buf, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_CHEMICAL}));
        }
      break;

      case 6:
        {
        //sprintf (Lcd.lcd_buf,"защ. био   %03d", Player.getComplexDefenceFrom(DamageClass::DAMAGE_SOURCE_BIO));
        //sprintf_P (Lcd.lcd_buf, STR_STAT_DEF_BIO_FORMAT, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_BIO}));
        //StalkerUI.DisplayMenuBodyF(StalkerUI.ToMenuBody(lcdRow), STRPOS_STR_STAT_DEF_BIO_FORMAT, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_BIO}));
        Str.SetPos(STRPOS_STR_STAT_DEF_BIO_FORMAT);
        Str.WriteFormat(Lcd.lcd_buf, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_BIO}));
        }
      break;

      case 7:
        {
        //sprintf (Lcd.lcd_buf,"защ.электро%03d", Player.getComplexDefenceFrom(DamageClass::DAMAGE_SOURCE_ELECTRICITY));
        //sprintf_P (Lcd.lcd_buf, STR_STAT_DEF_ELECTRO_FORMAT, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_ELECTRICITY}));
        //StalkerUI.DisplayMenuBodyF(StalkerUI.ToMenuBody(lcdRow), STRPOS_STR_STAT_DEF_ELECTRO_FORMAT, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_ELECTRICITY}));
        Str.SetPos(STRPOS_STR_STAT_DEF_ELECTRO_FORMAT);
        Str.WriteFormat(Lcd.lcd_buf, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_ELECTRICITY}));
        }
      break;

      case 8:
        {
        //sprintf (Lcd.lcd_buf,"защ. грави %03d", Player.getComplexDefenceFrom(DamageClass::DAMAGE_SOURCE_GRAVY));
        //sprintf_P (Lcd.lcd_buf, STR_STAT_DEF_GRAVY_FORMAT, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_GRAVY}));
        //StalkerUI.DisplayMenuBodyF(StalkerUI.ToMenuBody(lcdRow), STRPOS_STR_STAT_DEF_GRAVY_FORMAT, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_GRAVY}));
        Str.SetPos(STRPOS_STR_STAT_DEF_GRAVY_FORMAT);
        Str.WriteFormat(Lcd.lcd_buf, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_GRAVY}));
        }
      break;

      case 9:
        {
        //sprintf (Lcd.lcd_buf,"защ. пси   %03d", Player.getComplexDefenceFrom(DamageClass::DAMAGE_SOURCE_PSY));
        //sprintf_P (Lcd.lcd_buf, STR_STAT_DEF_PSY_FORMAT, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_PSY}));
        //StalkerUI.DisplayMenuBodyF(StalkerUI.ToMenuBody(lcdRow), STRPOS_STR_STAT_DEF_PSY_FORMAT, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_PSY}));
        Str.SetPos(STRPOS_STR_STAT_DEF_PSY_FORMAT);
        Str.WriteFormat(Lcd.lcd_buf, Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_PSY}));
        }
      break;
      }
    StalkerUI.DisplayMenuBody(&Str, StalkerUI.ToMenuBody(lcdRow));
    //LcdString(1, static_cast<LCD_LINE>(lcdRow));
    //StalkerUI.DisplayMenuBody(lcdRow);
    if (++scrollTMP >= PlayerSkillsClass::SKILLS_NUM)
      {
      scrollTMP  = 0;
      }
    }
  /*sprintf (lcd_buf,"М.хп%03d рег%03d",Player.getMaxHealth(), Player.getRegenTime());
  LcdString(1,LCD_LINE_2);
  sprintf (lcd_buf,"з/р %03d с/р%03d", Player.getComplexDefenceFrom(DamageClass::DAMAGE_SOURCE_RADIATION_EXTERNAL),Player.getResistanceRadiation());
  LcdString(1,LCD_LINE_3);
  sprintf (lcd_buf,"огн %03d хим%03d", Player.getComplexDefenceFrom(DamageClass::DAMAGE_SOURCE_FIRE), Player.getComplexDefenceFrom(DamageClass::DAMAGE_SOURCE_CHEMICAL));
  LcdString(1,LCD_LINE_4);
  sprintf (lcd_buf,"био %03d эле%03d", Player.getComplexDefenceFrom(DamageClass::DAMAGE_SOURCE_BIO), Player.getComplexDefenceFrom(DamageClass::DAMAGE_SOURCE_ELECTRICITY));
  LcdString(1,LCD_LINE_5);
  sprintf (lcd_buf,"грав%03d пси%03d", Player.getComplexDefenceFrom(DamageClass::DAMAGE_SOURCE_GRAVY), Player.getComplexDefenceFrom(DamageClass::DAMAGE_SOURCE_PSY));
  LcdString(1,LCD_LINE_6);*/
  //sprintf (lcd_buf,"грав%03d пси%03d", Player.getComplexDefenceFrom(DamageClass::DAMAGE_SOURCE_GRAVY), Player.getComplexDefenceFrom(DamageClass::DAMAGE_SOURCE_PSY));
//  LcdString(1,LCD_LINE_6,(char*)"next>  |  down");
  Lcd.IsNeedUpdate      = true;
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_StatsClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUIDS::MENUID_STATS;
  }
void PDAMenu_StatsClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  if (btn == ButtonsClass::BUTTONS::BUTTON_CENTER_MENU)
    {
    if (++this->scroll >= 10)
      {
      this->scroll  = 0;
      }
    //LcdClearCache();
    //LcdClear2_to_5();
    //StalkerUI.ClearMenuBody();
    //this->JustSelected();
    }
  /*else if (btn == ButtonsClass::BUTTONS::BUTTON_UP_ESC)
    {
    if (this->scroll == 0)
      {
      this->scroll  = 10 - 1;
      }
    else
      {
      this->scroll--;
      }
    StalkerUI.ClearMenuBody();
    this->JustSelected();
    }*/
  }

/////////////////////////////////////////////////////////////////////////////


void PDAMenu_PlayerSkillsClass::JustSelected(void)
  {
  //LcdStringUpdate(1,LCD_LINE_1,(char*)"skills:");
  StalkerUI.DisplayMenuHead(STRPOS_STR_PDAMENU_SKILLS);
  SkillID_t SID=this->scroll;
  //for (uint8_t lcdRow=LCD_LINE_2; lcdRow<LCD_LINE_6; lcdRow++)
  for (uint8_t lcdRow=0; lcdRow<StalkerUI_Class::UI_MENU_BODY_LINE_SIZE; lcdRow++)
    {
    //sprintf (Lcd.lcd_buf, "%s%03u", Player.getSkills()->getName(SID), Player.getSkills()->getValue(SID));
    //LcdString(1, static_cast<LCD_LINE>(lcdRow));
    //sprintf_P (Lcd.lcd_buf, STR_SKILL_STRING_FORMAT, Player.GetSkills()->getName(SID), Player.GetSkills()->getValue(SID));
    //StalkerUI.DisplayMenuBody(lcdRow);
    //StalkerUI.DisplayMenuBodyF(StalkerUI.ToMenuBody(lcdRow), STRPOS_STR_SKILL_STRING_FORMAT, Player.GetSkills()->getName(SID), Player.GetSkills()->getValue(SID));
    STRClass Str(STRPOS_STR_SKILL_STRING_FORMAT);
    Str.WriteFormat(Lcd.lcd_buf, StalkerUI.ToMenuBody(lcdRow), Player.GetSkills()->getName(SID), Player.GetSkills()->getValue(SID));
    StalkerUI.DisplayMenuBody(&Str, StalkerUI.ToMenuBody(lcdRow));
    if (++SID >= PlayerSkillsClass::SKILLS_NUM)
      {
      SID  = 0;
      }
    }
//  LcdString(1,LCD_LINE_6,(char*)"next>  |  down");
  //LcdString(11,LCD_LINE_6, STR_DOWN);
  //StalkerUI.ShowButtonDown();
  Lcd.IsNeedUpdate  = true;
  }
void PDAMenu_PlayerSkillsClass::Update(uint8_t msPassed)
  {
  //sprintf (lcd_buf, "%03u", this->test);
  //LcdString(1,LCD_LINE_6);
  //Lcd.IsNeedUpdate  = true;
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_PlayerSkillsClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUIDS::MENUID_SKILLS;
  }
void PDAMenu_PlayerSkillsClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  if (btn == ButtonsClass::BUTTONS::BUTTON_CENTER_MENU)
    {
    //this->test2++;
    //++this->test;
    if (++this->scroll >= (PlayerSkillsClass::SKILLS_NUM))//4 - num of available LCD rows
      {
      this->scroll  = 0;
      }
    //LcdClearCache();
    //LcdClear2_to_5();
    StalkerUI.ClearMenuBody();
    this->JustSelected();
    }
  /*else if (btn == ButtonsClass::BUTTONS::BUTTON_UP_ESC)
    {
    if (this->scroll == 0)
      {
      this->scroll  = PlayerSkillsClass::SKILLS_NUM - 1;
      }
    else
      {
      this->scroll--;
      }
    StalkerUI.ClearMenuBody();
    this->JustSelected();
    }*/
  }



void PDAMenu_ComputerHackClass::JustSelected(void)
  {
  //LcdStringUpdate(1,LCD_LINE_1, STR_PDAMENU_COMPUTER);
  StalkerUI.DisplayMenuHead(STRPOS_STR_PDAMENU_COMPUTER);
  this->updateCounter  = 1000;
  }
void PDAMenu_ComputerHackClass::Update(uint8_t msPassed)
  {
  this->updateCounter += msPassed;
  
  if (this->updateCounter < 1000)
    {
    return;
    }
  this->updateCounter  -= 1000;
  
/*
  while(1)
{
  if (Buttons.isButtonDown(ButtonsClass::BUTTON_USE))
    {
    uint8_t* respond  = HackableComputer.getStatus();
    LcdString(1,LCD_LINE_1, (char*)"stat");
    sprintf (lcd_buf, "%03u %03u", respond[0], respond[1]);
    LcdString(1,LCD_LINE_2);
    sprintf (lcd_buf, "%03u %03u", HackableComputer.data[PROTO_HACK_DATA_H], HackableComputer.data[PROTO_HACK_DATA_L]);
    LcdString(1,LCD_LINE_3);
    }
sprintf (lcd_buf, "%05u",rand());
LcdString(1,LCD_LINE_6);
LcdUpdate();
//_delay_ms(2000);
}*/
  //if (ArtefactPorts.)
  if (HackableComputer.isConnected())
    {
    /*
    uint8_t* result  = HackableComputer.getStatus();
    //uint8_t* result  = NULL;
    if (result != NULL)
      {
      this->connectedComputerLevel  = result[0];
      this->connectedComputerStatus  = result[1];
    
      switch (this->selectedAction)
        {
        case 0:
          {
          LcdString(1,LCD_LINE_2, (char*)"хакнуть?");
          }
        break;

        case 1:
          {
          LcdString(1,LCD_LINE_2, (char*)"try HACK?");
          }
        break;
        }
    
      sprintf (lcd_buf, "status:  %03u",this->connectedComputerStatus);
      LcdString(1,LCD_LINE_3);
      */
      //sprintf (Lcd.lcd_buf, "Level:  %03u",HackableComputer.getLevel());
      //LcdString(1,LCD_LINE_4);
      
      //sprintf_P (Lcd.lcd_buf, STR_LEVEL_FORMAT,HackableComputer.getLevel());
      //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_2);
      //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_2, STRPOS_STR_LEVEL_FORMAT,HackableComputer.getLevel());
      STRClass Str(STRPOS_STR_LEVEL_FORMAT);
      Str.WriteFormat(Lcd.lcd_buf, HackableComputer.getLevel());
      StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_2);
      
      if (HackableComputer.haveAccess())
        {
        //LcdString(1,LCD_LINE_2, STR_Q_SWITH);
        StalkerUI.DisplayMenuBody(STRPOS_STR_Q_SWITH, StalkerUI_Class::UI_MENU_BODY_LINE_0);
        if (HackableComputer.getSwitch())
          {
          //LcdString(1,LCD_LINE_3, STR_PLUS_BRACKED);
          StalkerUI.DisplayMenuBody(STRPOS_STR_PLUS_BRACKED, StalkerUI_Class::UI_MENU_BODY_LINE_1);
          }
        else
          {
          //LcdString(1,LCD_LINE_3, STR_MINUS_BRACKED);
          StalkerUI.DisplayMenuBody(STRPOS_STR_MINUS_BRACKED, StalkerUI_Class::UI_MENU_BODY_LINE_1);
          }
        //LcdString(1,LCD_LINE_5,STR_COMP_ACCESS_GRANTED);
        StalkerUI.DisplayMenuBody(STRPOS_STR_COMP_ACCESS_GRANTED, StalkerUI_Class::UI_MENU_BODY_LINE_3);
        }
      else
        {
        //LcdString(1,LCD_LINE_2, STR_COMP_Q_DO_HACK);
        //LcdEmptyString(LCD_LINE_3);
        StalkerUI.DisplayMenuBody(STRPOS_STR_COMP_Q_DO_HACK, StalkerUI_Class::UI_MENU_BODY_LINE_0);
        StalkerUI.DisplayEmptyBodyString(StalkerUI_Class::UI_MENU_BODY_LINE_1);
        this->selectedAction  = 0;
        //LcdString(1,LCD_LINE_5, STR_COMP_ACCESS_DENIED);
        StalkerUI.DisplayMenuBody(STRPOS_STR_COMP_ACCESS_DENIED, StalkerUI_Class::UI_MENU_BODY_LINE_3);
        }
    
      //sprintf (lcd_buf, "5: %05u",rand());
      //LcdString(1,LCD_LINE_6);
      Lcd.IsNeedUpdate  = true;
    //  }
    }
  else
    {
    //LcdClear2_to_5();
    StalkerUI.ClearMenuBody();
    //LcdString(1,LCD_LINE_5, STR_COMP_DISCONNECTED);
    StalkerUI.DisplayMenuBody(STRPOS_STR_COMP_DISCONNECTED, StalkerUI_Class::UI_MENU_BODY_LINE_3);
    Lcd.IsNeedUpdate  = true;
    }
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_ComputerHackClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUID_COMPUTER_HACK;
  }
void PDAMenu_ComputerHackClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  if (btn == ButtonsClass::BUTTONS::BUTTON_CENTER_MENU)
    {
    if(HackableComputer.haveAccess())
      {
      HackableComputer.toggleSwitch();
      }
    else
      {
      HackableComputer.tryToHack(&Player);
      }
    //LcdString(1,LCD_LINE_5, STR_COMP_TRYING);
    StalkerUI.DisplayMenuBody(STRPOS_STR_COMP_TRYING, StalkerUI_Class::UI_MENU_BODY_LINE_3);
    Lcd.IsNeedUpdate=true;
    }
  }






void PDAMenu_ActiveEffectsClass::JustSelected(void)
  {
  //LcdString(1,LCD_LINE_1, STR_PDAMENU_EFFECTS);
  StalkerUI.DisplayMenuHead(STRPOS_STR_PDAMENU_EFFECTS);
  this->Update(0);
  /*
  LcdStringUpdate(1,LCD_LINE_1,(char*)"skills:");
  SkillID SID=this->scroll;
  for (uint8_t lcdRow=LCD_LINE_2; lcdRow<LCD_LINE_6; lcdRow++)
    {
    sprintf (lcd_buf, "%s%03u", PlayerSkills.getName(SID), PlayerSkills.getValue(SID));
    LcdString(1, static_cast<LCD_LINE>(lcdRow));
    if (++SID >= PlayerSkillsClass::SKILLS_NUM)
      {
      SID  = 0;
      }
    }
//  LcdString(1,LCD_LINE_6,(char*)"next>  |  down");
  LcdString(11,LCD_LINE_6,(char*)"down");
  Lcd.IsNeedUpdate  = true;
  */
  }
void PDAMenu_ActiveEffectsClass::Update(uint8_t msPassed)
  {
  if (msPassed != 0)
    {
    updateCounter+=msPassed;
    if (updateCounter < 1000)
      {
      return;
      }
    updateCounter-=1000;
    }
  PlayerEffects_Interface* activeEffectsData[PlayerEffectsClass::STORAGE_SIZE];
//  uint8_t effectsNum  = PlayerEffects.GetActiveVisibleEffects(PlayerEffectsClass::EFFECTID_NONE, activeEffectsData);
  uint8_t effectsNum  = PlayerEffects.GetActiveEffects(PlayerEffectsClass::EFFECTID_NONE, activeEffectsData);
  if (this->scroll >= effectsNum)
    {
    this->scroll  = 0;
    }
  
  if (effectsNum > 0)
    {
    PlayerEffects_Interface* selectedEffect = activeEffectsData[this->scroll];
    STRClass Str(STRPOS_STR_FORMAT_4x_03D);
    Str.WriteFormat(Lcd.lcd_buf, effectsNum, selectedEffect->GetID(), PlayerEffects.GetRemainTimeSec(selectedEffect), 0);
    
    StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_0);
    StalkerUI.DisplayMenuBody(selectedEffect->GetName(),StalkerUI_Class::UI_MENU_BODY_LINE_1);
    }

  /*
  uint8_t activeEffectsData[PlayerEffectsOldClass::EFFECTS_NUM];
  uint8_t effectsNum  = Player.GetEffects()->GetActiveVisibleList(activeEffectsData);
  if (this->scroll > effectsNum)
    {
    this->scroll  = 0;
    }
    
  if (effectsNum > 0)
    {
    switch (activeEffectsData[this->scroll])
      {
      case PlayerEffectsOldClass::EFFECTID_SAFE_SHELTER:
        {
        //LcdString(1,LCD_LINE_2, STR_EFFECTS_SAFE_SHELTER);
        StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_0, STR_EFFECTS_SAFE_SHELTER);
        }
      break;

      default:
        {
        //LcdString(1,LCD_LINE_2, STR_EFFECTS_UNKNOWN);
        StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_0, STR_EFFECTS_UNKNOWN);
        }
      break;
      }
    //sprintf (Lcd.lcd_buf, "%05u сек", Player.getEffects()->getRemaningTimeInSeconds(data[this->scroll]));
    //LcdString(1, LCD_LINE_3);

    sprintf_P (Lcd.lcd_buf, STR_SECONDS_5_DIGITS_FORMAT, Player.GetEffects()->getRemaningTimeInSeconds(activeEffectsData[this->scroll]));
    StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_1);
    
    }
  else
    {
    //LcdString(1,LCD_LINE_2, STR_EFFECTS_NONE);
    //LcdEmptyString(LCD_LINE_3);
    
    StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_0, STR_EFFECTS_NONE);
    StalkerUI.DisplayEmptyBodyString(StalkerUI_Class::UI_MENU_BODY_LINE_1);
    }

  //sprintf (Lcd.lcd_buf, "%03u/%03u", (this->scroll+1), effectsNum);
  //LcdString(1, LCD_LINE_5);
  
  sprintf_P (Lcd.lcd_buf, STR_1_OF_2_FORMAT, (this->scroll+1), effectsNum);
  StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_3);
  
  //LcdString(1,LCD_LINE_6,(char*)"next>  |  down");
//  LcdString(1,LCD_LINE_6, STR_PDAMENU_6ROW_NEXT_DOWN);
  //LcdString(11,LCD_LINE_6,(char*)"down");
  */
  Lcd.IsNeedUpdate  = true;
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_ActiveEffectsClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUIDS::MENUID_UNDEFINED;
  }
void PDAMenu_ActiveEffectsClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  if (btn == ButtonsClass::BUTTONS::BUTTON_DOWN_ENTER)
    {
    ++this->scroll;//обработка переполнения в Update()
    //LcdClear2_to_5();
    StalkerUI.ClearMenuBody();
    this->Update(0);
//    this->JustSelected();
    }
  }



void PDAMenu_DebugClass::JustSelected(void)
  {
  StalkerUI.ClearDisplayCache();
  StalkerUI.DisplayMenuHead(STRPOS_STR_PDAMENU_DEBUG);
  this->Update(0);
  //ArtefactFlash00SPI
  }
void PDAMenu_DebugClass::Update(uint8_t msPassed)
  {
  static uint8_t i=0;
  STRClass Str;

  this->updateCounter+=msPassed;
  if (this->updateCounter < 1000)
    {
    return;
    }
  this->updateCounter-=1000;
  //StalkerUI.DisplayString(StalkerUI_Class::UI_LCD_LINE_0, (char*)"test");
  //sprintf(Lcd.lcd_buf, "mem free:%04d", MemoryManager.GetAvailableBytes());
  //StalkerUI.DisplayString(StalkerUI_Class::UI_LCD_LINE_1);
  //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_0, STRPOS_STR_DEBUG_MEMFREE_FORMAT, MemoryManager.GetAvailableBytes());
  Str.SetPos(STRPOS_STR_DEBUG_MEMFREE_FORMAT);
  Str.WriteFormat(Lcd.lcd_buf, MemoryManagerClass::GetAvailableBytes());
  StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_0);

//  uint8_t tmp[3];
//write DevID
  uint8_t writeData[]={13};
  ExternalEEPROMTWI::writeToDevice(0,0,1,writeData);
  //_delay_ms(10);
//  ExternalEEPROMTWI::readFromDevice(0,0, 3, tmp);
//  uint8_t* tmp=MediaMemory.GetJDEC();
/*
//copy SIDS to MediaFlash
  static bool IsWritten = false;
  static UNION_UINT32_LITTLE_ENDIAN flash_num_address;
  static UNION_UINT32_LITTLE_ENDIAN flash_data_address;
  static UNION_UINT32_LITTLE_ENDIAN flash_ptr_address;
  static uint32_t wrt_counter=0;
  if (IsWritten == false)
{
  IsWritten = true;
  MediaMemory.EraseDevice();
//  _delay_ms(1000);
  uint8_t byte        = 0;
  uint8_t SelecedSID  = Sound::SIDS::SID_RADIOATION4;
  uint32_t addressData          = 0;
  flash_data_address.value_int  = 4096;//first
//<= init data


  flash_num_address.value_int   = 0;//write to [num of sounds]
  byte                          = Sound::SIDS::SIDS_NUM;
  MediaMemory.WriteData(flash_num_address.byte_field.mh, flash_num_address.byte_field.ml, flash_num_address.byte_field.l, &byte, 1);
//<= post init write
//  flash_data_address.value_int  += 4096;//first

for (SelecedSID=0;SelecedSID<Sound::SIDS::SIDS_NUM;SelecedSID++)
{

  uint8_t* selected_sound_ptr   = PDASound.GetSoundAddress(SelecedSID);

  flash_ptr_address.value_int   = 1024+(SelecedSID*4);//write to [address of selected SID]
  addressData                   = flash_data_address.value_int;
  MediaMemory.WriteData(flash_ptr_address.byte_field.mh, flash_ptr_address.byte_field.ml, flash_ptr_address.byte_field.l, (uint8_t*)&addressData, 4);

  uint8_t headCounter = 0;
  while (1)//write data
    {
    wrt_counter++;
    byte  = pgm_read_byte(selected_sound_ptr++);
    MediaMemory.WriteData(flash_data_address.byte_field.mh, flash_data_address.byte_field.ml, flash_data_address.byte_field.l, &byte, 1);
//    _delay_ms(1);
    flash_data_address.value_int++;
    if (headCounter > Sound::WAV_HEAD_DIFF)
      {
      if (byte == 0x00)//end
        {
        break;
        }
      }
    else
      {
      headCounter++;
      }
    }
}
}
*/
  
/*
  UNION_UINT32_LITTLE_ENDIAN z;
  z.value_int = PDASound.GetSoundAddress(Sound::SID_PDA_NEWS);
  //z.value_int = 2134123424;
  sprintf(Lcd.lcd_buf, "%03u%03u %03u%03u", z.byte_field.h, z.byte_field.mh, z.byte_field.ml, z.byte_field.l);
  StalkerUI.DisplayString(StalkerUI_Class::UI_LCD_LINE_2);
*/  
/*
  //MediaMemory.ReadData(0,0,0, tmp, 3);
  uint32_t images[PDAImagesClass::IMAGES::IMAGES_NUM]={0};
  UNION_UINT32_LITTLE_ENDIAN z;
  for (uint8_t i=0;i<PDAImagesClass::IMAGES::IMAGES_NUM;i++)
    {
    z.value_int = MediaFlashClass::MEDIAFLASH_ADDRESS::MEDIAFLASH_ADDRESS_IMAGE_POINTERS+(4*i);//address
    uint32_t addressValue = 0;
    MediaMemory.ReadData(z.byte_field.mh, z.byte_field.ml, z.byte_field.l, (uint8_t*)&addressValue, (uint16_t)4);
    images[i]  = addressValue;
    }

  UNION_UINT32_LITTLE_ENDIAN flash_num_address;
  uint8_t tmp[4];
  memset(tmp, 0, 4);
//  flash_num_address.value_int = 1024+(4*(Sound::SIDS::SID_PDA_NEWS));
//  flash_num_address.value_int = PDASound.GetSoundAddress(Sound::SIDS::SID_NONE);
//  flash_num_address.value_int = PDASound.GetSoundAddress(Sound::SIDS::SID_RADIOATION);
  //flash_num_address.value_int = PDASound.GetSoundAddress(Sound::SIDS::SID_HIT_4);
//  flash_num_address.value_int = PDASound.GetSoundAddress(Sound::SIDS::SID_RADIOATION4);
  //flash_num_address.value_int = PDASound.GetSoundAddress(Sound::SIDS::SID_PDA_NEWS);
//  flash_num_address.value_int = PDASound.GetSoundAddress(Sound::SIDS::SID_BLOWOUT_HIT_2);
  flash_num_address.value_int = images[PDAImagesClass::IMAGES::IMG_PBOY];
//  MediaMemory.ReadData(flash_num_address.byte_field.mh, flash_num_address.byte_field.ml, flash_num_address.byte_field.l, tmp, (uint8_t)4);
//  sprintf(Lcd.lcd_buf, "%05u", *((uint32_t*)tmp));
//  sprintf(Lcd.lcd_buf, "%05u", *((uint32_t*)flash_num_address.value_int));
  sprintf(Lcd.lcd_buf, "%03u%03u %03u%03u", flash_num_address.byte_field.h, flash_num_address.byte_field.mh, flash_num_address.byte_field.ml, flash_num_address.byte_field.l);
//  sprintf(Lcd.lcd_buf, "%03u%03u %03u%03u", tmp[0], tmp[1], tmp[2], tmp[3]);
//  StalkerUI.DisplayString(StalkerUI_Class::UI_LCD_LINE_1);
//  sprintf(Lcd.lcd_buf, "%03u%03u %03u%03u", tmp[4], tmp[5], tmp[6], tmp[7]);

  //MediaMemory.ReadData(0,0,0, tmp, 3);
//  sprintf(Lcd.lcd_buf, "%03d %03d %05d", lastADCValueRAWH, lastADCValueRAWL, lastADCValueRAW);
//  sprintf(Lcd.lcd_buf, "media: %02d mbit", MediaMemory.GetCapacity());
//  sprintf(Lcd.lcd_buf, "%03d %03d %03d", tmp[0], tmp[1], tmp[2]);
//  flash_data_address.value_int-=4096;
//  sprintf(Lcd.lcd_buf, "%05u", wrt_counter);
  //sprintf(Lcd.lcd_buf, "%03d%03d %03d%03u", z.byte_field.h, z.byte_field.mh, z.byte_field.ml, z.byte_field.l);
  StalkerUI.DisplayString(StalkerUI_Class::UI_LCD_LINE_2);
  */
//  sprintf(Lcd.lcd_buf, "%05u %06lu", PowerManager.getVoltage(), PowerManager.getADCValue());
  //sprintf(Lcd.lcd_buf, "%04umv", PowerManager.GetBatteryVoltage());
  //StalkerUI.DisplayString(StalkerUI_Class::UI_LCD_LINE_3);
  //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_2, STRPOS_STR_DEBUG_BATTERY_VOLTAGE_FORMAT, PowerManager.GetBatteryVoltage());
  Str.SetPos(STRPOS_STR_DEBUG_BATTERY_VOLTAGE_FORMAT);
  Str.WriteFormat(Lcd.lcd_buf, PowerManager.GetBatteryVoltage());
  StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_2);

  //uint8_t* tmp=MediaMemory.GetCachedJDEC();
  //_delay_ms(1);
  //Player.GetArtefactPorts()->SetPortOut(0);
  /*
  ArtefactsPortsHardwareClass *m_Hardware  = Player.GetArtefactPorts()->getHardware();
  ArtefactsPinSS00::SetDirOut();
  ArtefactsPinSS00::SetOutLow();

//  Artefact00.ReadData(tmp, 3);
  //Artefact00.ReadJEDEC();
  //uint8_t* tmp=Artefact00.GetCachedJDEC();
  
  
  m_Hardware->SPI_send(M25P05_INSTRUCTION_READ_DATA_BYTES);
  _delay_us(5);
  m_Hardware->SPI_send(0);
  _delay_us(5);
  m_Hardware->SPI_send(0);
  _delay_us(5);
  m_Hardware->SPI_send(0);
  _delay_us(5);
  tmp[0]      = m_Hardware->SPI_send(0);
  tmp[1]      = m_Hardware->SPI_send(0);
  tmp[2]      = m_Hardware->SPI_send(0);
  
  ArtefactsPinSS00::SetOutHigh();
  */

//  sprintf(Lcd.lcd_buf, "%03d %03d %05d", lastADCValueRAWH, lastADCValueRAWL, lastADCValueRAW);
  //sprintf(Lcd.lcd_buf, "media: %02d mbit", Artefact00.GetCapacity());
  //Artefact00.ReadData();
//  sprintf(Lcd.lcd_buf, "DrID: [%02d]", Artefact00.GetDriver()->GetDriverID());

//  uint16_t zzz[10];
//  sprintf(Lcd.lcd_buf, "%03d %03d %03d", tmp[0], tmp[1], tmp[2]);
//  sprintf(Lcd.lcd_buf, "%03d %03d %03d", Player.GetArtefactPorts()->m_lastArtefact[0], Player.GetArtefactPorts()->m_lastArtefact[1], Player.GetArtefactPorts()->m_lastArtefact[2]);
//  StalkerUI.DisplayString(StalkerUI_Class::UI_LCD_LINE_2);
  
  //sprintf(Lcd.lcd_buf, "%03d", ++i);
  //StalkerUI.DisplayString(StalkerUI_Class::UI_LCD_LINE_4);
  //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_2, STRPOS_STR_DEBUG_3D_FORMAT, ++i);
  Str.SetPos(STRPOS_STR_FORMAT_03D);
  Str.WriteFormat(Lcd.lcd_buf, ++i);
  StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_2);
  

//  sprintf(Lcd.lcd_buf, "%03d %03d %03d", zzz[0], sizeof(zzz), sizeof(uint16_t));
//  StalkerUI.DisplayString(StalkerUI_Class::UI_LCD_LINE_5);
  
  //LcdImage(PBoy);
  Lcd.IsNeedUpdate  = true;
  //new uint8_t[100];
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_DebugClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUIDS::MENUID_UNDEFINED;
  }
void PDAMenu_DebugClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  }




void PDAMenu_TimeTranmitterClass::JustSelected(void)
  {
  StalkerUI.DisplayMenuHead(STRPOS_STR_PDAMENU_ADM_TIME_TRANSMITTER);
  
//  StalkerUI.ClearDisplayCache();
//  this->Update(0);
  }
void PDAMenu_TimeTranmitterClass::Update(uint8_t msPassed)
  {
  this->updateCounter+=msPassed;
  if (this->updateCounter < 500)
    {
    return;
    }
  this->updateCounter-=500;
  //TimeRTC.hour  = 18;
  /*
  if (TimeRTC.hour == 2 && TimeRTC.minute == 2 && (TimeRTC.second == 2 || TimeRTC.second == 3 ))
    {
    this->txOn  = false;
    #warning "hackFirstTxPass"
    }
  */
  if (hackFirstTxPass == false)
    {
    hackFirstTxPass = true;
    StalkerLayer2->L1.L0.HardwareInitialization();
    HAL.EnvironmentRarioModule.setTXPower(HAL.EnvironmentRarioModule.TX_POWER_MAX);
    StalkerLayer2->L1.L0.SetTXPacketType(Class_StalkerLayer0::PACKET_TYPE_NONE);
    StalkerLayer2->L1.L0.packetContainerTX[1]  = 0;
    StalkerLayer2->L1.L0.packetContainerTX[2]  = 0;
    StalkerLayer2->L1.L0.packetContainerTX[3]  = 0;
    StalkerLayer2->L1.L0.prepareTXPacket();
    HAL.EnvironmentRarioModule.sendBufferToRM();
    StalkerLayer2->L1.L0.sendPacket();
    HAL.EnvironmentRarioModule.waitModeReady();
    StalkerLayer2->L1.L0.ClearFifo();
    }

  //sprintf(Lcd.lcd_buf, "День:%u", TimeRTC.GetDay());
  //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_0);
  //sprintf_P(Lcd.lcd_buf, STR_TIME_FORMAT, TimeRTC.GetHour(), TimeRTC.GetMinute(), TimeRTC.GetSecond());
  //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_1);

  //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_0, STRPOS_STR_DATE_DAY_FORMAT, TimeRTC.GetDay());
  //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_1, STRPOS_STR_TIME_FORMAT, TimeRTC.GetHour(), TimeRTC.GetMinute(), TimeRTC.GetSecond());

  STRClass Str(STRPOS_STR_DATE_DAY_FORMAT);
  Str.WriteFormat(Lcd.lcd_buf, TimeRTC.GetDay());
  StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_0);

  Str.SetPos(STRPOS_STR_TIME_FORMAT);
  Str.WriteFormat(Lcd.lcd_buf, TimeRTC.GetHour(), TimeRTC.GetMinute(), TimeRTC.GetSecond());
  StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_1);
  

  if (this->txOn == true )// || hackFirstTxPass == false)
    {
    //hackFirstTxPass  = true;
//    sprintf_P(Lcd.lcd_buf, STR_TIME_FORMAT, TimeRTC.GetHour(), TimeRTC.GetMinute(), TimeRTC.GetSecond());
    //StalkerUI.DisplayMenuBody(TIME_FORMAT_LENGTH+1+3, StalkerUI_Class::UI_MENU_BODY_LINE_1, STR_PLUS_BRACKED);
    StalkerUI.DisplayMenuBody(STRPOS_STR_PLUS_BRACKED, StalkerUI_Class::UI_MENU_BODY_LINE_1, TIME_FORMAT_LENGTH+1+3);

    
    
    
//    sprintf(Lcd.lcd_buf, "%02u:%02u:%02u tx:+", TimeRTC.GetHour(), TimeRTC.GetMinute(), TimeRTC.GetSecond());
//    sprintf(Lcd.lcd_buf, "%02u:%02u:%02u tx:+", TimeRTC.GetHour(), TimeRTC.GetMinute(), TimeRTC.GetSecond());
//    StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_1);

    //HAL.EnvironmentRarioModule.waitModeReady();
    
    StalkerLayer2->L1.L0.HardwareInitialization();
    //HAL.EnvironmentRarioModule.setTXPower(HAL.EnvironmentRarioModule.TX_POWER_MAX);
//    StalkerLayer2->L1.L0.SetTXPacketType(Class_StalkerLayer0::PACKET_TYPE_TIMEUPDATE);
    StalkerLayer2->L1.L0.packetContainerTX[1]  = TimeRTC.GetRawHour();
    StalkerLayer2->L1.L0.packetContainerTX[2]  = TimeRTC.GetRawMinute();
    StalkerLayer2->L1.L0.packetContainerTX[3]  = TimeRTC.GetRawSecond();
    StalkerLayer2->L1.L0.prepareTimeUpdatePacket();
//    StalkerLayer2->L1.L0.prepareTXPacket();
    HAL.EnvironmentRarioModule.sendBufferToRM();
    StalkerLayer2->L1.L0.sendPacket();
    HAL.EnvironmentRarioModule.waitModeReady();
    StalkerLayer2->L1.L0.ClearFifo();
    /*
    StalkerLayer2->L1.L0.packetContainerTX[0]  = 0;
    StalkerLayer2->L1.L0.packetContainerTX[1]  = 0;
    StalkerLayer2->L1.L0.packetContainerTX[2]  = 0;
    StalkerLayer2->L1.L0.packetContainerTX[3]  = 0;
    StalkerLayer2->L1.L0.packetContainerTX[4]  = 0;
    StalkerLayer2->L1.L0.packetContainerTX[5]  = 0;
    HAL.EnvironmentRarioModule.sendBufferToRM();
    */
    
    //HAL.EnvironmentRarioModule.switchMode(Driver_AnoRadRarioModule::TRX_STATE::TRX_STATE_RECEIVING);

    }
  else
    {
    //sprintf(Lcd.lcd_buf, "%02u:%02u:%02u tx:-", TimeRTC.GetHour(), TimeRTC.GetMinute(), TimeRTC.GetSecond());
    //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_1);
    //StalkerUI.DisplayMenuBody(TIME_FORMAT_LENGTH+1+3, StalkerUI_Class::UI_MENU_BODY_LINE_1, STR_MINUS_BRACKED);
    StalkerUI.DisplayMenuBody(STRPOS_STR_MINUS_BRACKED, StalkerUI_Class::UI_MENU_BODY_LINE_1, TIME_FORMAT_LENGTH+1+3);
    }

  StalkerUI.DisplayEmptyString(StalkerUI_Class::UI_MENU_BODY_LINE_2);
  //StalkerUI.DisplayMenuBody(this->position+1, StalkerUI_Class::UI_MENU_BODY_LINE_2, STR_STAR);
  StalkerUI.DisplayMenuBody(STRPOS_STR_STAR, StalkerUI_Class::UI_MENU_BODY_LINE_2, this->position+1);


  Lcd.IsNeedUpdate  = true;
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_TimeTranmitterClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUIDS::MENUID_UNDEFINED;
  }
void PDAMenu_TimeTranmitterClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  if (btn == ButtonsClass::BUTTONS::BUTTON_CENTER_MENU)
    {
    this->position++;
    if (this->position == 2)
      {
      this->position++;
      }
    else if (this->position == 5)
      {
      this->position++;
      }
    else if (this->position == 8)
      {
      this->position+=4;
      }
    else if (this->position > 12)
      {
      this->position=0;
      }
    }
  else if (btn == ButtonsClass::BUTTONS::BUTTON_UP_ESC)
    {
    switch (this->position)
      {
      case 0:
        {
        TimeRTC.hour+=10;
        }
      break;
      case 1:
        {
        TimeRTC.hour++;
        }
      break;
      case 3:
        {
        TimeRTC.minute+=10;
        }
      break;
      case 4:
        {
        TimeRTC.minute++;
        }
      break;
      case 6:
        {
        TimeRTC.second+=10;
        }
      break;
      case 7:
        {
        TimeRTC.second++;
        }
      break;
      case  12:
        {
        this->txOn  = true;
        }
      break;
      }
    TimeRTC.Update();
    Lcd.IsNeedUpdate  = true;
    }
  else if (btn == ButtonsClass::BUTTONS::BUTTON_DOWN_ENTER)
    {
    switch (this->position)
      {
      case 0:
        {
        TimeRTC.hour-=10;
        }
      break;
      case 1:
        {
        TimeRTC.hour--;
        }
      break;
      case 3:
        {
        TimeRTC.minute-=10;
        }
      break;
      case 4:
        {
        TimeRTC.minute--;
        }
      break;
      case 6:
        {
        TimeRTC.second-=10;
        }
      break;
      case 7:
        {
        TimeRTC.second--;
        }
      break;
      case  12:
        {
        this->txOn  = false;
        }
      break;
      }
    TimeRTC.Update();
    }
  }



void PDAMenu_FMClass::JustSelected(void)
  {
//  StalkerUI.ClearDisplayCache();
//  this->Update(0);
  }
void PDAMenu_FMClass::Update(uint8_t msPassed)
  {
  this->updateCounter+=msPassed;
  if (this->updateCounter < 500)
    {
    return;
    }
  this->updateCounter-=500;

  //sprintf(Lcd.lcd_buf, "%04u %03d",(875+this->freqencyDiff), Ar1010.getRSSIValue());
  //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_0);
  //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_0, STRPOS_STR_DEBUG_4D_3D_FORMAT, (875+this->freqencyDiff), Ar1010.getRSSIValue());
  STRClass Str(STRPOS_STR_DEBUG_4D_3D_FORMAT);
  Str.WriteFormat(Lcd.lcd_buf, (875+this->freqencyDiff), Ar1010.getRSSIValue());
  StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_0);
  if (Ar1010.isDisabled)
    {
    //sprintf(Lcd.lcd_buf, "OFF");
    StalkerUI.DisplayMenuBody(STRPOS_STR_OFF, StalkerUI_Class::UI_MENU_BODY_LINE_2);
    }
  else
    {
    //sprintf(Lcd.lcd_buf, "ON ");
    StalkerUI.DisplayMenuBody(STRPOS_STR_ON, StalkerUI_Class::UI_MENU_BODY_LINE_2);
    }
  //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_2);
  //sprintf(Lcd.lcd_buf, "rdy:%01u", StalkerLayer2->L1.L0.isModuleReadyToWork());
  //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_2);

//  StalkerUI.DisplayEmptyString(StalkerUI_Class::UI_MENU_BODY_LINE_1);
//  StalkerUI.DisplayMenuBody(this->position+1, StalkerUI_Class::UI_MENU_BODY_LINE_1, STR_STAR);

  Lcd.IsNeedUpdate  = true;
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_FMClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUIDS::MENUID_UNDEFINED;
  }
void PDAMenu_FMClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  if (btn == ButtonsClass::BUTTONS::BUTTON_CENTER_MENU)
    {
    if (Ar1010.isDisabled)
      {
      PDASettings.setParameter(ConfigClass::SETTINGS_RADIO_ON);
      Ar1010.deviceEnable();
      //sprintf(Lcd.lcd_buf, "");
      //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_0);
      }
    else
      {
      PDASettings.clearParameter(ConfigClass::SETTINGS_RADIO_ON);
      Ar1010.deviceDisable();
      }
    }
  else if (btn == ButtonsClass::BUTTONS::BUTTON_UP_ESC)
    {
    this->freqencyDiff+=5;
    if (this->freqencyDiff > 205)
      {
      this->freqencyDiff  = 0;
      }
    Ar1010.setFrequency(205+this->freqencyDiff);
    }
  else if (btn == ButtonsClass::BUTTONS::BUTTON_DOWN_ENTER)
    {
    this->freqencyDiff--;
    if (this->freqencyDiff == 255)
      {
      this->freqencyDiff  = 205;
      }
    Ar1010.setFrequency(205+this->freqencyDiff);
    }
  }



void PDAMenu_GameSnakeClass::NewFood(void)
  {
  this->generateNewFood();
  this->displayFood();
  }
void PDAMenu_GameSnakeClass::JustSelected(void)
  {
  StalkerUI.ClearDisplayCache();
  this->Update(0);
  LcdRect(this->Xdiff, this->Ydiff, this->Xdiff+((this->Xlength + 1)*3), this->Ydiff+((this->Ylength+1)*3), PIXEL_ON);
  this->gamePaused    = false;
  XheadPosition      = 0;//signed
  YheadPosition      = 0;//signed
  this->bodyLength    = 1;
  this->selectedDirection  = MOVES_DIRECTION_RIGHT;
  this->displayBodyDot(XheadPosition, YheadPosition, PIXEL_ON);
  this->NewFood();
  Lcd.IsNeedUpdate    = true;
  }
void PDAMenu_GameSnakeClass::Update(uint8_t msPassed)
  {
  //static uint8_t i=0;
  this->updateCounter+=msPassed;
  if (this->updateCounter < 750)
    {
    return;
    }
  this->updateCounter-=750;
//  StalkerUI.DisplayString(StalkerUI_Class::UI_LCD_LINE_0, (char*)"Змейка...");
//  sprintf(Lcd.lcd_buf, "%03d", ++i);
//  StalkerUI.DisplayString(StalkerUI_Class::UI_LCD_LINE_5);
  
  if (!this->gamePaused)
    {
    //this->displayBodyDot(XheadPosition, YheadPosition, PIXEL_OFF);
    this->desideNewMoveDirection();
    this->calculateNextHeadPosition();
    //this->displayBodyDot(XheadPosition, YheadPosition, PIXEL_ON);
    if (this->checkBorderCollision() || this->checkBodyCollision(false, this->XheadPosition, this->YheadPosition))
      {
      //this->JustSelected();
      //StalkerUI.DisplayString(6, StalkerUI_Class::UI_LCD_LINE_1, (char*)"GameOver");
      StalkerUI.DisplayMenuBottom(STRPOS_STR_GAMEOVER);
      this->gamePaused  = true;
      }
    }
  
  Lcd.IsNeedUpdate  = true;
  //new uint8_t[100];
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_GameSnakeClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUIDS::MENUID_UNDEFINED;
  }
void PDAMenu_GameSnakeClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  switch (btn)
    {
    case ButtonsClass::BUTTON_UP_ESC:
      {
      if (this->selectedDirection != MOVES_DIRECTION_DOWN)
        {
        this->pendingDirection  = MOVES_DIRECTION_UP;
        }
      }
    break;
    
    case ButtonsClass::BUTTON_LEFT:
      {
      if (this->selectedDirection != MOVES_DIRECTION_RIGHT)
        {
        this->pendingDirection  = MOVES_DIRECTION_LEFT;
        }
      }
    break;

    case ButtonsClass::BUTTON_RIGHT:
      {
      if (this->selectedDirection != MOVES_DIRECTION_LEFT)
        {
        this->pendingDirection  = MOVES_DIRECTION_RIGHT;
        }
      }
    break;

    case ButtonsClass::BUTTON_DOWN_ENTER:
      {
      if (this->selectedDirection != MOVES_DIRECTION_UP)
        {
        this->pendingDirection    = MOVES_DIRECTION_DOWN;
        }
      //PDAMenu.selectMenuID(PDAMenu_MainInterface::MENUID_SELECT_NEXT);
      }
    break;

    case ButtonsClass::BUTTON_CENTER_MENU:
      {
//      ((PDAMenu_GamesClass*)this->parentMenu)->StopGame();
      ((PDAMenu_GamesClass*)this->GetParentMenu())->StopGame();
      }
    break;

    case ButtonsClass::BUTTONS_NUM://to avoid warnings
      {
      
      }
    break;
    }
  }
void PDAMenu_GameSnakeClass::goBack(int8_t* x, int8_t* y, MOVES_DIRECTIONS direction)
  {
  switch (direction)
    {
    case MOVES_DIRECTION_UP:
      {
      (*y)++;
      }
    break;
    case MOVES_DIRECTION_DOWN:
      {
      (*y)--;
      }
    break;
    case MOVES_DIRECTION_LEFT:
      {
      (*x)++;
      }
    break;
    case MOVES_DIRECTION_RIGHT:
      {
      (*x)--;
      }
    break;
    }
  }
void PDAMenu_GameSnakeClass::calculateNextHeadPosition(void)
  {
  //uint8_t lastBottom  = this->body[0];
  //=>прорисовка нового положения головы
  this->body[this->bodyLength]  = this->selectedDirection;
  switch (this->selectedDirection)
    {
    case MOVES_DIRECTION_UP:
      {
      this->YheadPosition--;
      }
    break;
    case MOVES_DIRECTION_DOWN:
      {
      this->YheadPosition++;
      }
    break;
    case MOVES_DIRECTION_LEFT:
      {
      this->XheadPosition--;
      }
    break;
    case MOVES_DIRECTION_RIGHT:
      {
      this->XheadPosition++;
      }
    break;
    }
  this->displayBodyDot(XheadPosition, YheadPosition, PIXEL_ON);
  //<=прорисовка нового положения головы

  if (this->checkFoodAfterMove())
    {
    //если есть еда, значит, хвост оставляем
    //и увеличиваю длину тела
    this->bodyLength++;
    this->NewFood();
    }
  else
    {
    //еды нет, отрубаю хвост
  
    int8_t bottomX  = this->XheadPosition;
    int8_t bottomY  = this->YheadPosition;
    for (uint8_t i=this->bodyLength;i>0;i--)//вычисляю хвост
      {
      this->goBack(&bottomX, &bottomY, this->body[i]);
      }
    for (uint8_t i=0;i<this->bodyLength;i++)//сдвигаю тело
      {
      this->body[i]=this->body[i+1];
      }
//sprintf(Lcd.lcd_buf, "h%03i%03i ", XheadPosition, YheadPosition);
//StalkerUI.DisplayString(StalkerUI_Class::UI_LCD_LINE_3);
//sprintf(Lcd.lcd_buf, "b%03i%03i ", bottomX,bottomY);
//StalkerUI.DisplayString(StalkerUI_Class::UI_LCD_LINE_4);
    if (bottomX == this->XheadPosition && bottomY == this->YheadPosition)
      {
      }
    else//если голова не там
      {
      this->displayBodyDot(bottomX, bottomY, PIXEL_OFF);//закрашиваю хвост
      }
    }
  }
void PDAMenu_GameSnakeClass::displayFood()
  {
  uint8_t x=this->Xdiff+((this->Xlength/2)+this->XFoodPosition)*3;
  uint8_t y=this->Ydiff+((this->Ylength/2)+this->YFoodPosition)*3;
  LcdRect(x-1, y-1, x+1, y+1, PIXEL_ON);
  }
void PDAMenu_GameSnakeClass::displayBodyDot(int8_t bodyX, int8_t bodyY, LcdPixelMode PIXEL)
  {
  uint8_t x=this->Xdiff+((this->Xlength/2)+bodyX)*3;
  uint8_t y=this->Ydiff+((this->Ylength/2)+bodyY)*3;
  LcdPixel(x, y, PIXEL);
  LcdRect(x-1, y-1, x+1, y+1, PIXEL);
  }
void PDAMenu_GameSnakeClass::generateNewFood(void)
  {
  GameSnakeField_t position  = rand() % FieldWidth;//getting position
  while (true)
    {
    this->XFoodPosition    = (position / this->Xlength) - (this->Xlength/2) + 1;
    this->YFoodPosition    = (position % this->Ylength) - (this->Ylength/2) + 1;
    if (this->checkBodyCollision(true, this->XFoodPosition, this->YFoodPosition))
      {
      if (++position >= FieldWidth)
        {
        position = 0;
        }
      }
    else
      {
      break;
      }
    } 
  
  }
bool PDAMenu_GameSnakeClass::checkFoodAfterMove(void)
  {
  if (this->XFoodPosition == this->XheadPosition && this->YFoodPosition == this->YheadPosition)
    {
    return true;
    }
  return false;
  }
bool PDAMenu_GameSnakeClass::checkBodyCollision(bool withHeadCheck, int8_t x, int8_t y)
  {
  int8_t headX = this->XheadPosition;
  int8_t headY = this->YheadPosition;
  if (withHeadCheck && x == headX && y == headY)
    {
    return true;
    }
  for (GameSnakeField_t i=this->bodyLength-1;i>0;i--)
    {
    this->goBack(&headX, &headY, this->body[i]);
    if (x == headX && y == headY)
      {
      return true;
      }
    }
  return false;
  }
bool PDAMenu_GameSnakeClass::checkBorderCollision(void)
  {
  if (2*this->XheadPosition > this->Xlength)
    {
    return true;
    }
  if (2*this->XheadPosition <= -(this->Xlength))
    {
    return true;
    }
  if (2*this->YheadPosition > this->Ylength)
    {
    return true;
    }
  if (2*this->YheadPosition <= -(this->Ylength))
    {
    return true;
    }
  return false;
  }
void PDAMenu_GameSnakeClass::desideNewMoveDirection(void)
  {
  this->selectedDirection  = this->pendingDirection;
  }









void PDAMenu_GamesClass::JustSelected(void)
  {
  StalkerUI.ClearMenuBody();
  StalkerUI.DisplayMenuHead(STRPOS_STR_PDAMENU_GAMES);
  
  StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_GAMES_GAME_SNAKE, StalkerUI_Class::UI_MENU_BODY_LINE::UI_MENU_BODY_LINE_0);
  StalkerUI.DisplayMenuBody(STRPOS_STR_PDAMENU_GAMES_GAME_GTAVI, StalkerUI_Class::UI_MENU_BODY_LINE::UI_MENU_BODY_LINE_1);

  StalkerUI.DisplayMenuBody(STRPOS_STR_POINTER, StalkerUI.ToMenuBody(this->scroll));

  Lcd.IsNeedUpdate  = true;
  //this->StopGame();
  }
void PDAMenu_GamesClass::Update(uint8_t msPassed)
  {
  if (this->startedGame != NULL)
    {
    this->startedGame->Update(msPassed);
    }
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_GamesClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUIDS::MENUID_UNDEFINED;
  }
void PDAMenu_GamesClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  if (this->startedGame != NULL)//game in progress
    {
    this->startedGame->buttonPressed(btn);
    return;
    }
  if (btn == ButtonsClass::BUTTONS::BUTTON_DOWN_ENTER)
    {
    if (++this->scroll >= 2)
      {
      this->scroll  = 0;
      }
    StalkerUI.ClearMenuBody();
    this->JustSelected();
    }
  if (btn == ButtonsClass::BUTTONS::BUTTON_CENTER_MENU)
    {
    if (scroll == 0)
      {
      this->startedGame        = &this->GameSnake;
      this->startedGame->JustSelected();
      //this->startedGame->parentMenu  = this;
      this->startedGame->SetParentMenu(this);
      }
    }
  }
///////////////////////////////////////////////////////////////////////////////////////////////
void PDAMenu_MASTER_ArtefactClass::JustSelected(void)
  {
  StalkerUI.DisplayMenuHead(STRPOS_STR_ARTEFACT);
  }
void PDAMenu_MASTER_ArtefactClass::Update(uint8_t msPassed)
  {
  StalkerUI.DisplayEmptyString(StalkerUI_Class::UI_LCD_LINE::UI_LCD_LINE_1);
  if (Player.GetArtefactPorts()->GetConnectedArtefact(0)->isEmpty())
    {
    }
  else
    {
    //StalkerUI.DisplayString(1, StalkerUI_Class::UI_LCD_LINE::UI_LCD_LINE_1, Player.GetArtefactPorts()->getConnectedArtefact(0)->getArtefactName());
    StalkerUI.DisplayMenuBody(Player.GetArtefactPorts()->GetConnectedArtefact(0)->getArtefactName(), StalkerUI_Class::UI_MENU_BODY_LINE_0);
    }
  Lcd.IsNeedUpdate  = true;
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_MASTER_ArtefactClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUID_UNDEFINED;
  }
void PDAMenu_MASTER_ArtefactClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  ArtefactPortsClass* ArtefacePorts = Player.GetArtefactPorts();
  ArtefactClass* ConnectedArtefact0  = ArtefacePorts->GetConnectedArtefact(0);
  
  if (btn == ButtonsClass::BUTTONS::BUTTON_CENTER_MENU)
    {
    }
  /////////////////////////////////
  else if (btn == ButtonsClass::BUTTONS::BUTTON_UP_ESC)
    {
    if (ConnectedArtefact0->isArtefactValid())
      {
      ArtefactID_t AID  = ConnectedArtefact0->getArtefactID();
      if (!(ConnectedArtefact0->isArtefactValid(++AID)))//not valid
        {
        AID  = 1;
        }
      ArtefacePorts->SetPortOut(0);
      Artefact00.EraseDevice();
      uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_ARTEFACT,    0,    AID, 0,0, 0, 0, 0};
      Artefact00.WriteData(item, (uint16_t)8);
      ArtefacePorts->SetPortIn(0);
      ConnectedArtefact0->setArtefactRAW(AID);
      }
    }
  else if (btn == ButtonsClass::BUTTONS::BUTTON_DOWN_ENTER)
    {
    if (ConnectedArtefact0->isArtefactValid())
      {
      ArtefactID_t AID  = ConnectedArtefact0->getArtefactID();
      if (AID == 1 || !(ConnectedArtefact0->isArtefactValid(AID)))
        {
        AID  = (TemporaryClass::ARTEFACTS_NUM-1);
        }
      else
        {
        AID--;
        }
      ArtefacePorts->SetPortOut(0);
      Artefact00.EraseDevice();
      uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_ARTEFACT,    0,    AID, 0,0, 0, 0, 0};
      Artefact00.WriteData(item, (uint16_t)8);
      ArtefacePorts->SetPortIn(0);
      ConnectedArtefact0->setArtefactRAW(AID);
      }
    }
  }

///////////////////////////////////////////////////////////////////////////////////////////////
void PDAMenu_MASTER_ItemClass::JustSelected(void)
  {
  switch (this->changeSubject)
    {
    case EepromItemClass::EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_TYPE:
      {
      StalkerUI.DisplayMenuHead(STRPOS_STR_CONNECTED_ITEM_STUCT_TYPE);
      }
    break;
    case EepromItemClass::EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_SUBTYPE:
      {
      StalkerUI.DisplayMenuHead(STRPOS_STR_CONNECTED_ITEM_STUCT_SUBTYPE);
      }
    break;
    case EepromItemClass::EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_ID:
      {
      StalkerUI.DisplayMenuHead(STRPOS_STR_CONNECTED_ITEM_STUCT_ID);
      }
    break;
    case EepromItemClass::EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_STATUS:
      {
      StalkerUI.DisplayMenuHead(STRPOS_STR_CONNECTED_ITEM_STUCT_STATUS);
      }
    break;
    case EepromItemClass::EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_EX0:
      {
      StalkerUI.DisplayMenuHead(STRPOS_STR_CONNECTED_ITEM_STUCT_EX0);
      }
    break;
    case EepromItemClass::EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_EX1:
      {
      StalkerUI.DisplayMenuHead(STRPOS_STR_CONNECTED_ITEM_STUCT_EX1);
      }
    break;
    case EepromItemClass::EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_EX2:
      {
      StalkerUI.DisplayMenuHead(STRPOS_STR_CONNECTED_ITEM_STUCT_EX2);
      }
    break;
    case EepromItemClass::EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_EX3:
      {
      StalkerUI.DisplayMenuHead(STRPOS_STR_CONNECTED_ITEM_STUCT_EX3);
      }
    break;
    default:
      {
      StalkerUI.DisplayMenuHead(STRPOS_STR_Unknown);
      }
    break;
    }
  }
void PDAMenu_MASTER_ItemClass::Update(uint8_t msPassed)
  {
  #warning "[T] MASTER PDA hack disabled!"
  
  PDAMenu_MainInterface* m  = PDAMenu.GetMenu(PDAMenu_MainInterface::MENUID_CONNECTED_ITEM);
  m->Update(msPassed);
  STRClass Str(STRPOS_STR_FORMAT_03D);
  Str.WriteFormat(Lcd.lcd_buf, (UsableItem.GetConnectedItem()->GetItem()->GetArray()[this->changeSubject]));
  StalkerUI.DisplayString(Str, StalkerUI_Class::UI_LCD_LINE::UI_LCD_LINE_0, 12);
  
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_MASTER_ItemClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUID_UNDEFINED;
  }
void PDAMenu_MASTER_ItemClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  if (btn == ButtonsClass::BUTTONS::BUTTON_CENTER_MENU)
    {
    if (++changeSubject >= 8)
      {
      changeSubject=0;
      }
    this->JustSelected();
    }
  /////////////////////////////////
  else if (btn == ButtonsClass::BUTTONS::BUTTON_UP_ESC)
    {
    ConnectedItemArray_t*  Item  = UsableItem.GetConnectedItem()->GetItem()->GetArray();
    Item+=changeSubject;
    /*switch (changeSubject)
      {
      case UsableItemClass::ty
      }*/
    ++(*Item);
    if (changeSubject == EepromItemClass::EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_TYPE)//changing TYPE
      {
      if ((*Item) >= UsableItemClass::ITEM_TYPES_NUM)
        {
        (*Item)=0;
        }
      memset(Item+1,0,7);//clear Item when changing TYPE
      }
    UsableItem.WriteConnectedItem();
    //UsableItem.IncrementChargesWrite();
    }
  else if (btn == ButtonsClass::BUTTONS::BUTTON_DOWN_ENTER)
    {
    ConnectedItemArray_t*  Item  = UsableItem.GetConnectedItem()->GetItem()->GetArray();
    Item+=changeSubject;
    --(*Item);
    if (changeSubject == 0)//id
      {
      if ((*Item) >= UsableItemClass::ITEM_TYPES_NUM)
        {
        (*Item)=0;
        }
      memset(Item+1,0,7);//clear Item
      }
    UsableItem.WriteConnectedItem();
    //UsableItem.IncrementChargesWrit
    }
  }

///////////////////////////////////////////////////////////////////////////////////////////////
void PDAMenu_MASTER_ReviveActionClass::JustSelected(void)
  {
  StalkerUI.DisplayMenuHead(STRPOS_STR_PDAMENU_ADM_REVIVE);
  }
void PDAMenu_MASTER_ReviveActionClass::Update(uint8_t msPassed)
  {
  this->updateCounter+=msPassed;
  STRClass Str;


  if (this->updateCounter < 500)
    {
    return;
    }
  this->updateCounter-=500;

  if (hackFirstTxPass == false)
    {
    hackFirstTxPass = true;
    StalkerLayer2->L1.L0.HardwareInitialization();
    HAL.EnvironmentRarioModule.setTXPower(HAL.EnvironmentRarioModule.TX_POWER_MAX);
    StalkerLayer2->L1.L0.SetTXPacketType(Class_StalkerLayer0::PACKET_TYPE_NONE);
    StalkerLayer2->L1.L0.packetContainerTX[1]  = 0;
    StalkerLayer2->L1.L0.packetContainerTX[2]  = 0;
    StalkerLayer2->L1.L0.packetContainerTX[3]  = 0;
    StalkerLayer2->L1.L0.prepareTXPacket();
    HAL.EnvironmentRarioModule.sendBufferToRM();
    StalkerLayer2->L1.L0.sendPacket();
    HAL.EnvironmentRarioModule.waitModeReady();
    StalkerLayer2->L1.L0.ClearFifo();
    }


  if (this->txOn == true )// || hackFirstTxPass == false)
    {
    //sprintf(Lcd.lcd_buf, "%03u tx:+", this->PDANum);
    //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_0);
    //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_0, STRPOS_STR_MASTER_TX_PLUS_FORMAT, this->PDANum);
    Str.SetPos(STRPOS_STR_MASTER_TX_PLUS_FORMAT);
    Str.WriteFormat(Lcd.lcd_buf, this->PDANum);
    StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_0);

    StalkerLayer2->L1.L0.HardwareInitialization();
    //HAL.EnvironmentRarioModule.setTXPower(HAL.EnvironmentRarioModule.TX_POWER_MAX);
    StalkerLayer2->L1.L0.SetTXPacketType(Class_StalkerLayer0::PACKET_TYPE_ADM_ACTION);
//    StalkerLayer2->L1.L0.packetContainerTX[0]  = Class_StalkerLayer0::PACKET_TYPE_ADM_ACTION;
    StalkerLayer2->L1.L0.packetContainerTX[1]  = RADIOMARK_ADM_ACTION_REVIVE;
    StalkerLayer2->L1.L0.packetContainerTX[2]  = this->PDANum;
    StalkerLayer2->L1.L0.packetContainerTX[3]  = 0;
    StalkerLayer2->L1.L0.prepareTXPacket();
    HAL.EnvironmentRarioModule.sendBufferToRM();
    StalkerLayer2->L1.L0.sendPacket();
    HAL.EnvironmentRarioModule.waitModeReady();
    StalkerLayer2->L1.L0.ClearFifo();
    }
  else
    {
    //sprintf(Lcd.lcd_buf, "%03u tx:-", this->PDANum);
    //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_0);
    //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_0, STRPOS_STR_MASTER_TX_MINUS_FORMAT, this->PDANum);
    Str.SetPos(STRPOS_STR_MASTER_TX_MINUS_FORMAT);
    Str.WriteFormat(Lcd.lcd_buf, this->PDANum);
    StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_0);

    }
  //sprintf(Lcd.lcd_buf, "rdy:%01u", StalkerLayer2->L1.L0.isModuleReadyToWork());
  //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_2);

  StalkerUI.DisplayEmptyString(StalkerUI_Class::UI_MENU_BODY_LINE_1);
  //StalkerUI.DisplayMenuBody(this->position+1, StalkerUI_Class::UI_MENU_BODY_LINE_1, STR_STAR);
  Str.SetPos(STRPOS_STR_STAR);
  Str.WriteTo(Lcd.lcd_buf);
  StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_1, this->position+1);
//  StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_1);

  Lcd.IsNeedUpdate  = true;
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_MASTER_ReviveActionClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUID_UNDEFINED;
  }
void PDAMenu_MASTER_ReviveActionClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  int8_t numDiff=0;
  if (btn == ButtonsClass::BUTTONS::BUTTON_CENTER_MENU)
    {
    this->position++;
    if (this->position == 3)
      {
      this->position+=4;
      }
    else if (this->position > 7)
      {
      this->position  = 0;
      }
    }
  else if (btn == ButtonsClass::BUTTONS::BUTTON_UP_ESC)
    {
    switch (this->position)
      {
      case 0:
        {
        //this->PDANum+=100;
        numDiff=100;
        }
      break;

      case 1:
        {
        //this->PDANum+=10;
        numDiff=10;
        }
      break;

      case 2:
        {
        //this->PDANum++;
        numDiff=1;
        }
      break;

      case 7:
        {
        this->txOn  = true;
        }
      break;
      }
    Lcd.IsNeedUpdate  = true;
    }
  else if (btn == ButtonsClass::BUTTONS::BUTTON_DOWN_ENTER)
    {
    switch (this->position)
      {
      case 0:
        {
        //this->PDANum-=100;
        numDiff=-100; //-V569
        }
      break;

      case 1:
        {
        //this->PDANum-=10;
        numDiff=-10; //-V569
        }
      break;

      case 2:
        {
        //this->PDANum--;
        numDiff=-1;
        }
      break;

      case 7:
        {
        this->txOn  = false;
        }
      break;
      }
    }
  if (numDiff != 0)
    {
    this->PDANum += numDiff;
    }
  }
///////////////////////////////////////////////////////////////////////////////////////////////
void PDAMenu_UndertakerClass::JustSelected(void)
  {
  StalkerUI.DisplayMenuHead(STRPOS_STR_PDAMENU_ADM_HALF_DEATH_TIME);
  }
void PDAMenu_UndertakerClass::Update(uint8_t msPassed)
  {
  this->updateCounter+=msPassed;
  STRClass Str;

  if (this->updateCounter < 500)
    {
    return;
    }
  this->updateCounter-=500;

  if (hackFirstTxPass == false)
    {
    hackFirstTxPass = true;
    StalkerLayer2->L1.L0.HardwareInitialization();
    HAL.EnvironmentRarioModule.setTXPower(HAL.EnvironmentRarioModule.TX_POWER_MAX);
    StalkerLayer2->L1.L0.SetTXPacketType(Class_StalkerLayer0::PACKET_TYPE_NONE);
    StalkerLayer2->L1.L0.packetContainerTX[1]  = 0;
    StalkerLayer2->L1.L0.packetContainerTX[2]  = 0;
    StalkerLayer2->L1.L0.packetContainerTX[3]  = 0;
    StalkerLayer2->L1.L0.prepareTXPacket();
    HAL.EnvironmentRarioModule.sendBufferToRM();
    StalkerLayer2->L1.L0.sendPacket();
    HAL.EnvironmentRarioModule.waitModeReady();
    StalkerLayer2->L1.L0.ClearFifo();
    }

  if (this->txOn == true )// || hackFirstTxPass == false)
    {
    //sprintf(Lcd.lcd_buf, "%03u tx:+", this->PDANum);
    //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_0);
    //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_0, STRPOS_STR_MASTER_TX_PLUS_FORMAT, this->PDANum);
    Str.SetPos(STRPOS_STR_MASTER_TX_PLUS_FORMAT);
    Str.WriteFormat(Lcd.lcd_buf, this->PDANum);
    StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_0);
    

    StalkerLayer2->L1.L0.HardwareInitialization();
    //HAL.EnvironmentRarioModule.setTXPower(HAL.EnvironmentRarioModule.TX_POWER_MAX);
    StalkerLayer2->L1.L0.SetTXPacketType(Class_StalkerLayer0::PACKET_TYPE_ADM_ACTION);
//    StalkerLayer2->L1.L0.packetContainerTX[0]  = Class_StalkerLayer0::PACKET_TYPE_ADM_ACTION;
    StalkerLayer2->L1.L0.packetContainerTX[1]  = RADIOMARK_ADM_ACTION_HALF_DEATH_TIME;
    StalkerLayer2->L1.L0.packetContainerTX[2]  = this->PDANum;
    StalkerLayer2->L1.L0.packetContainerTX[3]  = 0;
    StalkerLayer2->L1.L0.prepareTXPacket();
    HAL.EnvironmentRarioModule.sendBufferToRM();
    StalkerLayer2->L1.L0.sendPacket();
    HAL.EnvironmentRarioModule.waitModeReady();
    StalkerLayer2->L1.L0.ClearFifo();
    }
  else
    {
    //sprintf(Lcd.lcd_buf, "%03u tx:-", this->PDANum);
    //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_0);
    //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_0, STRPOS_STR_MASTER_TX_MINUS_FORMAT, this->PDANum);
    Str.SetPos(STRPOS_STR_MASTER_TX_MINUS_FORMAT);
    Str.WriteFormat(Lcd.lcd_buf, this->PDANum);
    StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_0);

    }
  //sprintf(Lcd.lcd_buf, "rdy:%01u", StalkerLayer2->L1.L0.isModuleReadyToWork());
  //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_2);

  StalkerUI.DisplayEmptyString(StalkerUI_Class::UI_MENU_BODY_LINE_1);
  //StalkerUI.DisplayMenuBody(this->position+1, StalkerUI_Class::UI_MENU_BODY_LINE_1, STR_STAR);
  Str.SetPos(STRPOS_STR_STAR);
  Str.WriteTo(Lcd.lcd_buf);
  StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_1, this->position+1);
//  StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_1);

  Lcd.IsNeedUpdate  = true;
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_UndertakerClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUID_UNDEFINED;
  }
void PDAMenu_UndertakerClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  int8_t numDiff=0;
  if (btn == ButtonsClass::BUTTONS::BUTTON_CENTER_MENU)
    {
    this->position++;
    if (this->position == 3)
      {
      this->position+=4;
      }
    else if (this->position > 7)
      {
      this->position  = 0;
      }
    }
  else if (btn == ButtonsClass::BUTTONS::BUTTON_UP_ESC)
    {
    switch (this->position)
      {
      case 0:
        {
        //this->PDANum+=100;
        numDiff=100;
        }
      break;

      case 1:
        {
        //this->PDANum+=10;
        numDiff=10;
        }
      break;

      case 2:
        {
        //this->PDANum++;
        numDiff=1;
        }
      break;

      case 7:
        {
        this->txOn  = true;
        }
      break;
      }
    Lcd.IsNeedUpdate  = true;
    }
  else if (btn == ButtonsClass::BUTTONS::BUTTON_DOWN_ENTER)
    {
    switch (this->position)
      {
      case 0:
        {
        //this->PDANum-=100;
        numDiff=-100; //-V569
        }
      break;

      case 1:
        {
        //this->PDANum-=10;
        numDiff=-10; //-V569
        }
      break;

      case 2:
        {
        //this->PDANum--;
        numDiff=-1;
        }
      break;

      case 7:
        {
        this->txOn  = false;
        }
      break;
      }
    }
  if (numDiff != 0)
    {
    this->PDANum += numDiff;
    }
  }
///////////////////////////////////////////////////////////////////////////////////////////////
void PDAMenu_MagicClass::JustSelected(void)
  {
  #warning "[T] REMOVE ram string"
  //StalkerUI.DisplayMenuHead(STRPOS_STR_PDAMENU_ADM_HALF_DEATH_TIME);
  LcdString(1, LCD_LINE_1, (char*)"magic");
  }
void PDAMenu_MagicClass::Update(uint8_t msPassed)
  {
  this->updateCounter+=msPassed;
  STRClass Str;

  if (this->updateCounter < 500)
    {
    return;
    }
  this->updateCounter-=500;

  if (hackFirstTxPass == false)
    {
    hackFirstTxPass = true;
    StalkerLayer2->L1.L0.HardwareInitialization();
    HAL.EnvironmentRarioModule.setTXPower(HAL.EnvironmentRarioModule.TX_POWER_MAX);
    StalkerLayer2->L1.L0.SetTXPacketType(Class_StalkerLayer0::PACKET_TYPE_NONE);
    StalkerLayer2->L1.L0.packetContainerTX[1]  = 0;
    StalkerLayer2->L1.L0.packetContainerTX[2]  = 0;
    StalkerLayer2->L1.L0.packetContainerTX[3]  = 0;
    StalkerLayer2->L1.L0.prepareTXPacket();
    HAL.EnvironmentRarioModule.sendBufferToRM();
    StalkerLayer2->L1.L0.sendPacket();
    HAL.EnvironmentRarioModule.waitModeReady();
    StalkerLayer2->L1.L0.ClearFifo();
    }

  if (this->txOn == true )// || hackFirstTxPass == false)
    {
    //sprintf(Lcd.lcd_buf, "%03u tx:+", this->PDANum);
    //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_0);
    //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_0, STRPOS_STR_MASTER_TX_PLUS_FORMAT, this->PDANum);
    Str.SetPos(STRPOS_STR_MASTER_TX_PLUS_FORMAT);
    Str.WriteFormat(Lcd.lcd_buf, this->PDANum);
    StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_0);
    

    StalkerLayer2->L1.L0.HardwareInitialization();
    //HAL.EnvironmentRarioModule.setTXPower(HAL.EnvironmentRarioModule.TX_POWER_MAX);
    StalkerLayer2->L1.L0.SetTXPacketType(Class_StalkerLayer0::PACKET_TYPE_ENVIRONMENT);
//    StalkerLayer2->L1.L0.packetContainerTX[0]  = Class_StalkerLayer0::PACKET_TYPE_ADM_ACTION;
    StalkerLayer2->L1.L0.packetContainerTX[1]  = 31;
    StalkerLayer2->L1.L0.packetContainerTX[2]  = this->PDANum;
    StalkerLayer2->L1.L0.packetContainerTX[3]  = 0;
    StalkerLayer2->L1.L0.prepareTXPacket();
    HAL.EnvironmentRarioModule.sendBufferToRM();
    StalkerLayer2->L1.L0.sendPacket();
    HAL.EnvironmentRarioModule.waitModeReady();
    StalkerLayer2->L1.L0.ClearFifo();
    }
  else
    {
    //sprintf(Lcd.lcd_buf, "%03u tx:-", this->PDANum);
    //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_0);
    //StalkerUI.DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE_0, STRPOS_STR_MASTER_TX_MINUS_FORMAT, this->PDANum);
    Str.SetPos(STRPOS_STR_MASTER_TX_MINUS_FORMAT);
    Str.WriteFormat(Lcd.lcd_buf, this->PDANum);
    StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_0);

    }
  //sprintf(Lcd.lcd_buf, "rdy:%01u", StalkerLayer2->L1.L0.isModuleReadyToWork());
  //StalkerUI.DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE_2);

  StalkerUI.DisplayEmptyString(StalkerUI_Class::UI_MENU_BODY_LINE_1);
  //StalkerUI.DisplayMenuBody(this->position+1, StalkerUI_Class::UI_MENU_BODY_LINE_1, STR_STAR);
  Str.SetPos(STRPOS_STR_STAR);
  Str.WriteTo(Lcd.lcd_buf);
  StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_1, this->position+1);
  //StalkerUI.DisplayMenuBody(STRPOS_STR_STAR, StalkerUI_Class::UI_MENU_BODY_LINE_1, this->position+1);

  Lcd.IsNeedUpdate  = true;
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_MagicClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUID_UNDEFINED;
  }
void PDAMenu_MagicClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  int8_t numDiff=0;
  if (btn == ButtonsClass::BUTTONS::BUTTON_CENTER_MENU)
    {
    this->position++;
    if (this->position == 3)
      {
      this->position+=4;
      }
    else if (this->position > 7)
      {
      this->position  = 0;
      }
    }
  else if (btn == ButtonsClass::BUTTONS::BUTTON_UP_ESC)
    {
    switch (this->position)
      {
      case 0:
        {
        //this->PDANum+=100;
        numDiff=100;
        }
      break;

      case 1:
        {
        //this->PDANum+=10;
        numDiff=10;
        }
      break;

      case 2:
        {
        //this->PDANum++;
        numDiff=1;
        }
      break;

      case 7:
        {
        this->txOn  = true;
        }
      break;
      }
    Lcd.IsNeedUpdate  = true;
    }
  else if (btn == ButtonsClass::BUTTONS::BUTTON_DOWN_ENTER)
    {
    switch (this->position)
      {
      case 0:
        {
        //this->PDANum-=100;
        numDiff=-100; //-V569
        }
      break;

      case 1:
        {
        //this->PDANum-=10;
        numDiff=-10; //-V569
        }
      break;

      case 2:
        {
        //this->PDANum--;
        numDiff=-1;
        }
      break;

      case 7:
        {
        this->txOn  = false;
        }
      break;
      }
    }
  if (numDiff != 0)
    {
    this->PDANum += numDiff;
    }
  }
/////////////////////////////////////////////////////////
void PDAMenu_SignalScannerClass::JustSelected(void)
  {
  #warning "[T] REMOVE ram string"
  sprintf(Lcd.lcd_buf, "SignalScanner%u", this->num);
  LcdString(1, LCD_LINE_1);
  }
void PDAMenu_SignalScannerClass::Update(uint8_t msPassed)
  {
  static uint16_t oneSecond_msCounter=0;
  oneSecond_msCounter+=msPassed;

  if (IsHacked)
    {
    if (oneSecond_msCounter < 1000)
      {
      return;
      }
    oneSecond_msCounter-=1000;
//    if (EmissionInstanceDetector.GetSignalID() == this->num)
//      {
      this->DisplayEmissionLevel(EmissionInstanceDetector);
//      }
    return;
    }
  ///////////////////////////
  if (oneSecond_msCounter < 500)
    {
    return;
    }
  oneSecond_msCounter-=500;
  StalkerUI.DisplayEmptyString(StalkerUI_Class::UI_MENU_BODY_LINE_1);
  //StalkerUI.DisplayMenuBody(this->position+1, StalkerUI_Class::UI_MENU_BODY_LINE_1, STR_STAR);
  #warning "[T] remove RAM str"
  sprintf(Lcd.lcd_buf, "%u-%u-%u-%u-%u-%u >", this->userPass[0], this->userPass[1], this->userPass[2], this->userPass[3], this->userPass[4], this->userPass[5]);
  StalkerUI.DisplayMenuBody(Lcd.lcd_buf, StalkerUI_Class::UI_MENU_BODY_LINE_0);
  STRClass Str;
  Str.SetPos(STRPOS_STR_STAR);
  Str.WriteTo(Lcd.lcd_buf);
  StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_1, this->GetDotPosition()+1);
  //StalkerUI.DisplayMenuBody(STRPOS_STR_STAR, StalkerUI_Class::UI_MENU_BODY_LINE_1, this->position+1);
  
  Lcd.IsNeedUpdate  = true;
  }
PDAMenu_MainInterface::MENUIDS PDAMenu_SignalScannerClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUID_SIGNAL_SCANNER;
  }
uint8_t PDAMenu_SignalScannerClass::GetDotPosition(void)
  {
  return ((this->userPassIndex*2));
  }
void PDAMenu_SignalScannerClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  //int8_t numDiff=0;
  if (btn == ButtonsClass::BUTTONS::BUTTON_CENTER_MENU)
    {
    /*
    this->position+=2;
    if (this->position > 11)
      {
      this->position  = 0;
      }*/
    if (++this->userPassIndex > this->passLength)
      {
      this->userPassIndex = 0;
      }
    }
  else if (btn == ButtonsClass::BUTTONS::BUTTON_UP_ESC)
    {
    if (this->GetDotPosition() <= ((this->passLength*2) - 1))
      {
      if (++this->userPass[this->userPassIndex] > ((this->passLength*2) - 1 - 2))
        {
        this->userPass[this->userPassIndex] = 0;
        }
      }
    else
      {
      STRClass Str;
      if (this->CheckPass())
        {
        this->IsHacked  = true;
        Str.SetPos(STRPOS_STR_COMP_ACCESS_GRANTED);
        }
      else
        {
        Str.SetPos(STRPOS_STR_COMP_ACCESS_DENIED);
        }
      Str.WriteTo(Lcd.lcd_buf);
      StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_3);
      }
    }
  else if (btn == ButtonsClass::BUTTONS::BUTTON_DOWN_ENTER)
    {
    if (this->GetDotPosition() <= ((this->passLength*2) - 1))
      {
      if (--this->userPass[this->userPassIndex] > ((this->passLength*2) - 1 - 2))
        {
        this->userPass[this->userPassIndex] = ((this->passLength*2) - 1 - 2);
        }
      }
    else
      {
      //nothing
      }

    }
    Lcd.IsNeedUpdate  = true;
  }
bool PDAMenu_SignalScannerClass::CheckPass(void)
  {
  for (uint8_t i=0;i<this->passLength;i++)
    {
    if (this->pass[i] != this->userPass[i])
      {
      return false;
      }
    }
  return true;
  }
PDAMenu_SignalScannerClass::PDAMenu_SignalScannerClass( uint8_t selected_num, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4, uint8_t p5, uint8_t p6 )
  {
  //TimerMS.RegisterListener(this);
  this->pass[0] = p1;
  this->pass[1] = p2;
  this->pass[2] = p3;
  this->pass[3] = p4;
  this->pass[4] = p5;
  this->pass[5] = p6;
  memset(this->userPass, 0, sizeof(this->userPass));
  this->num     = selected_num;
  }

/*
void PDAMenu_SignalScannerClass::TimerUpdateEvent (uint8_t msPassed)
  {
  static uint16_t oneSecond_msCounter=0;
  if (!(IsHacked))
    {
    return;
    }
  oneSecond_msCounter+=msPassed;
  if (oneSecond_msCounter < 1000)
    {
    return;
    }
  oneSecond_msCounter-=1000;
  this->DisplayEmissionLevel(EmissionInstanceDetector.GetSignalPowerPercent());
  }
*/
void PDAMenu_SignalScannerClass::DisplayEmissionLevel(EmissionInstanceDetectorClass& E)
  {
  Percent_t percent = E.GetSignalPowerPercent();
  if (E.GetSignalID() != this->num)
    {
    //Hack!
    percent = 0;
    }
  if (percent > 0)
    {
    Vibro.activate(4);
    }
  //sprintf(Lcd.lcd_buf, "%u", percent);
  //LcdString(1, LCD_LINE_2);
  if (percent > 80)
    {
    PDAMenu.DrawImg(PDAImagesClass::IMAGES::IMG_RADIO_WAVES_3);
//    PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
    }
  else if (percent > 50)
    {
    PDAMenu.DrawImg(PDAImagesClass::IMAGES::IMG_RADIO_WAVES_2);
    }
  else if (percent > 20)
    {
    PDAMenu.DrawImg(PDAImagesClass::IMAGES::IMG_RADIO_WAVES_1);
    }
  else
    {
    PDAMenu.DrawImg(PDAImagesClass::IMAGES::IMG_RADIO_WAVES_0);
    }
  if (percent > 80)
    {
    PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
    }
  if (percent > 60)
    {
    PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
    }
  if (percent > 40)
    {
    PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
    }
  if (percent > 20)
    {
    PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
    }
  }
/*
void PDAMenuSpecsClass::JustSelected(void)
  {
  
  }
void PDAMenuSpecsClass::Update(uint8_t msPassed)
  {
  
  }
PDAMenu_MainInterface::MENUIDS PDAMenuSpecsClass::getID(void)
  {
  return PDAMenu_MainInterface::MENUID_SPECS;
  }
void PDAMenuSpecsClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  }

*/
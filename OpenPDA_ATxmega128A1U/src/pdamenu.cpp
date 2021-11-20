// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//Файл в кодировке WIN1251!!!! (в отличие от других)
/*
void PDAMenuClass::PDAMenuTask1::Task(void)
  {
  PDAMenu.UpdateInformation(40);
  }
*/



void PDAMenuClass::TimerUpdateEvent (uint8_t msPassed)
  {
  static uint16_t updateInformation_msCounter=0;

  updateInformation_msCounter+=msPassed;

  if (updateInformation_msCounter >= 40)
    {
    updateInformation_msCounter -= 40;
    this->UpdateInformation(40);
    }
  }

PDAMenuClass::PDAMenuClass(void)
  {
  //this->selectedMenuID    = this->MENUID_MAIN;
  this->selectedSubMenuID   = 0;
  this->maxSubMenuID        = 0;
  this->subMenuJustSelected = false;
  this->m_selectedMenu      = &this->PDAMenu_Main;
  this->defaultMenu         = &this->PDAMenu_Main;
  //this->m_selectedMenu      = nullptr;
  }
/*
void PDAMenuClass::displayPercentBar(uint8_t GridPosX1, uint8_t Percent)
  {
  uint8_t Lines;
  uint8_t i;
  uint8_t GridPosX2;


  Lcd.IsNeedUpdate  = true;

  //  Lines     = (GridPosY2-GridPosY1+1-2);//общее кол-во линий
  GridPosX2   = GridPosX1+14;


  GridPosX1+=2;
  GridPosX2--;
  //  GridPosY2--;

  for (i=GridPosX1;i<GridPosX2;i++)//очистка
    {
    LcdLine(i, LCD_MENU_BAR_LINES_BOTTOM, i, LCD_MENU_BAR_LINES_TOP, PIXEL_OFF);
    }
  Lines=LCD_MENU_BAR_LINES_NUM;//Нельзя переместить вниз, т.к. иначе, по видимому, результат перемножения 8мибитный!
  Lines = (Lines*Percent)/100;//заполненных линий
  for (i=GridPosX1;i<GridPosX2;i++)//заполнение по вертикали
    {
    LcdLine(i, LCD_MENU_BAR_LINES_BOTTOM, i, LCD_MENU_BAR_LINES_BOTTOM-Lines, PIXEL_ON);
    }
  }
*/
void PDAMenuClass::UpdateInformation(uint8_t msPassed)
  {
  if (this->m_selectedMenu->hasSubmenu())
    {
    this->m_selectedMenu->GetSelectedSubMenu()->Update(msPassed);
    }
  else
    {
    this->m_selectedMenu->Update(msPassed);
    }
  //this->subMenuJustSelected  = false; //TODO
  //Lcd.IsMainScreenNeedRedraw  = false;
  Lcd.UpdateIfNeed();
  }

/*void PDAMenuClass::selectNextSubMenu(void)
  {
  if (this->maxSubMenuID < 2)
    {
    return;
    }
  if (++this->selectedSubMenuID >= this->maxSubMenuID)
    {
    this->selectedSubMenuID=0;
    }
  Lcd.IsNeedUpdate  = true;
//  if (this->getSelectedSubMenuID() == this->SUBMENU_SPECS_SUITE)
//    {
//    Lcd.IsSuiteScreenNeedRedraw  = true;
//    }
  this->subMenuJustSelected  = true;
  if (this->getSelectedMenuID() == this->MENUID_SPECS) //TODO: ХАК блеааа
    {
    LcdClearCache();
    }
  }*/
void PDAMenuClass::SelectDefaultMenu(void)
  {
  this->SelectMenu(this->GetDefaultMenu());
  //this->m_selectedMenu
  }
PDAMenu_MainInterface* PDAMenuClass::GetMenu(uint8_t menuID)
  {
  PDAMenu_MainInterface* select = &this->PDAMenu_Main;
  TODO("is it works?");
  
  for (uint8_t i = 0;i<MAXIMIM_MENUID;i++)
    {
    if (select->getID() == menuID)
      {
      return select;
      }
    select  = select->GetNext();
    }
  TODO("Log this ERROR!");
  return &this->PDAMenu_Main;
  }
void PDAMenuClass::SelectMenu(uint8_t menuID)
  {
  /***************************************************************************/
  /* Вперед-назад листать можно selectMenu(PDAMenuClass::MENUID_SELECT_NEXT) */
  /***************************************************************************/
  PDAMenu_MainInterface* select = &this->PDAMenu_Main;

  if (menuID == PDAMenu_MainInterface::MENUID_SELECT_NEXT)
    {
    //this->m_selectedMenu  = this->m_selectedMenu->GetNext();
    select  = this->m_selectedMenu->GetNext();
    }
  else if (menuID == PDAMenu_MainInterface::MENUID_SELECT_PREV)
    {
    //this->m_selectedMenu  = this->m_selectedMenu->getPrev();
    select  = this->m_selectedMenu->GetPrev();
    }
  else
    {
    select  = this->GetMenu(menuID);
    /*
    TODO("is it works?");
    uint8_t i = 0;
    while(1)
      {
      if (select->getID() == menuID)
        {
        break;
        }
      select  = select->GetNext();
      if (++i == MAXIMIM_MENUID)
        {
        TODO("Log this ERROR!");
        select  = &this->PDAMenu_Main;
        break;
        }
      }
    */
    }
  this->SelectMenu(select);
  }
void PDAMenuClass::SelectMenu(PDAMenu_MainInterface* m)
  {
  this->m_selectedMenu        = m;
  selectedSubMenuID           = 0;
  Lcd.IsMainScreenNeedRedraw  = true;

  LcdClearCache();
  if (this->m_selectedMenu->hasSubmenu())
    {
    this->menuItemSelected(this->m_selectedMenu->GetSelectedSubMenu());
    }
  else
    {
    this->menuItemSelected(this->m_selectedMenu);
    }
  
  Lcd.IsNeedUpdate  = true;
  }
void PDAMenuClass::menuItemSelected(PDAMenu_MainInterface* m)
  {
  STRClass Str;

  LcdClearCache();
  m->JustSelected();
//  if (m->isScrollable())
//    {
//    LcdString(11,LCD_LINE_6, STR_PDAMENU_6ROW_STR_USE);
//    }
  if (m->isUsable() || m->isScrollable())
    {
    //LcdString(11,LCD_LINE_6, STR_PDAMENU_6ROW_STR_USE);
    StalkerUI.DisplayMenuBottom(STRPOS_STR_PDAMENU_6ROW_STR_USE,11);
    }
  if (( m->hasParent() && m->GetNext() != m ) || m->hasSubmenu() || m->isSelectable())//self is submenu or has submenu
    {
    //LcdString(6,LCD_LINE_6, STR_PDAMENU_6ROW_DOWN);
    StalkerUI.DisplayMenuBottom(STRPOS_STR_PDAMENU_6ROW_DOWN,6);
    }
  }
void PDAMenuClass::DeathScreen(void)
  {
  //LcdImage(ImageSkull);
  //PDAMenu.DrawImg(PDAImagesClass::IMAGES::IMG_SKULL);
  SelectedSkin->DrawPlayerDead();
  n3310LcdClass::RequestUpdate();
  }
uint8_t PDAMenuClass::getSelectedMenuID(void)
  {
  //return this->selectedMenuID;
  return this->m_selectedMenu->getID();
  }
void PDAMenuClass::buttonPressed(ButtonsClass::BUTTONS btn)
  {
  if (this->m_selectedMenu->hasSpec(PDAMenu_MainInterface::MENU_SPECS_BIT__BUTTON_INTERCEPTION))
  //if (true)
    {
    this->m_selectedMenu->buttonPressed(btn);
    }
  else if (btn == ButtonsClass::BUTTONS::BUTTON_LEFT)
    {
    PDAMenu.SelectMenu(PDAMenu_MainInterface::MENUID_SELECT_PREV);
    }
  else if (btn == ButtonsClass::BUTTONS::BUTTON_RIGHT)
    {
    PDAMenu.SelectMenu(PDAMenu_MainInterface::MENUID_SELECT_NEXT);
    }
  else if (this->m_selectedMenu->hasSubmenu())
    {
    if (btn == ButtonsClass::BUTTONS::BUTTON_DOWN_ENTER)
      {
      LcdClear1_to_5();
      //this->m_selectedMenu->selectedSubMenu  = this->m_selectedMenu->selectedSubMenu->GetNext();
      this->m_selectedMenu->SetSelectedSubMenu(this->m_selectedMenu->GetSelectedSubMenu()->GetNext());
      //LcdString(1,LCD_LINE_6, STR_PDAMENU_6ROW_NEXT);//Дублирование бля
      //LcdString(6,LCD_LINE_6, STR_PDAMENU_6ROW_HAS_SUBMENU_PTR);//Дублирование бля
      //this->m_selectedMenu->selectedSubMenu->JustSelected();
      this->menuItemSelected(this->m_selectedMenu->GetSelectedSubMenu());
      }
    else if (btn == ButtonsClass::BUTTONS::BUTTON_UP_ESC)
      {
      LcdClear1_to_5();
      //this->m_selectedMenu->selectedSubMenu  = this->m_selectedMenu->selectedSubMenu->getPrev();
      this->m_selectedMenu->SetSelectedSubMenu(this->m_selectedMenu->GetSelectedSubMenu()->GetPrev());
      this->menuItemSelected(this->m_selectedMenu->GetSelectedSubMenu());
      }
    else
      {
      this->m_selectedMenu->GetSelectedSubMenu()->buttonPressed(btn);//сначала в текущий объект
      }
    }
  else
    {
    //this->m_selectedMenu->Update();
    this->m_selectedMenu->buttonPressed(btn);
    }
  }
bool PDAMenuClass::SetDefaultMenu(PDAMenu_MainInterface* m)
  {
  //TODO: return
  this->defaultMenu     = m;
//  this->m_selectedMenu  = m;
  return true;
  }
PDAMenu_MainInterface* PDAMenuClass::GetDefaultMenu(void)
  {
  return this->defaultMenu;
  }
void PDAMenuClass::DrawImg(PDAImagesClass::IMAGES img)
  {
  PDAImages.DrawImg(img);
  }

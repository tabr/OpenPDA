// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * SkinClass.cpp
 *
 * Created: 27.08.2018 21:04:04
 *  Author: tabr
 */ 
void GenericSkinClass::DrawMainGrid(void)
  {
  PDAMenu.DrawImg(PDAImagesClass::IMAGES::IMG_4_COLS);
  }
void GenericSkinClass::DrawPlayerZombie(void)
  {
  PDAMenu.DrawImg(PDAImagesClass::IMAGES::IMG_ZOMBIE);
  }
void GenericSkinClass::DrawPlayerDead(void)
  {
  PDAMenu.DrawImg(PDAImagesClass::IMAGES::IMG_SKULL);
  }
void GenericSkinClass::DisplayPlayerHealthPercent()
  {
  this->DisplayPercentBar(this->HEALTH_GRID_POS_X1, Player.GetHealthPercent());
  }
void GenericSkinClass::DisplayEmissionLevel(DamageSource_t dmgSrc, Percent_t levelPercent)
  {
  switch (dmgSrc)
    {
    case DamageSource_t::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL:
      {
      this->DisplayPercentBar(this->PLAYER_RAD_DOSE_GRID_POS_X1, Player.GetRadiationDosePercent());
      }
  	break;
    case DamageSource_t::DAMAGE_SOURCE_RADIATION_EXTERNAL:
      {
      //this->DisplayPercentBar(this->RAD_GRID_POS_X1, Env.GetRadiationLevelPercent());
      this->DisplayPercentBar(this->RAD_GRID_POS_X1, Env.GetComplexRadiationLevelPercent());
      }
  	break;
    case DamageSource_t::DAMAGE_SOURCE_PSY:
      {
      this->DisplayPercentBar(this->PSY_HAZARD_GRID_POS_X1, Env.GetPsyLevelPercent());
      }
  	break;
    default:
      //none
    break;
    }
  }
void GenericSkinClass::DisplayPercentBar(uint8_t GridPosX1, uint8_t Percent)
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
    LcdLine(i, this->LCD_MENU_BAR_LINES_BOTTOM, i, this->LCD_MENU_BAR_LINES_TOP, PIXEL_OFF);
    }
  Lines=this->LCD_MENU_BAR_LINES_NUM;//Ќельз€ переместить вниз, т.к. иначе, по видимому, результат перемножени€ 8мибитный!
  Lines = (Lines*Percent)/100;//заполненных линий
  for (i=GridPosX1;i<GridPosX2;i++)//заполнение по вертикали
    {
    LcdLine(i, this->LCD_MENU_BAR_LINES_BOTTOM, i, this->LCD_MENU_BAR_LINES_BOTTOM-Lines, PIXEL_ON);
    }
  }
ChargeVisualisationClass* GenericSkinClass::GetChargeVisualisationInterface(void)
  {
  return &this->ChargeVisualisation;
  }
void GenericSkinClass::DisplayPlayerInSafeShelter(bool isInSafeShelter)
  {
  if (isInSafeShelter)
    {
    LcdSymbol(12, LCD_LINE_2, LCD_SYMBOL_SHIELD);
    } 
  else
    {
    LcdSymbol(12, LCD_LINE_2, LCD_SYMBOL_EMPTY);
    }
  }
void GenericSkinClass::DisplayBlowoutActive(bool isActive)
  {
  if (isActive)
    {
    LcdSymbol(13, LCD_LINE_2, LCD_SYMBOL_STAR);
    } 
  else
    {
    LcdSymbol(13, LCD_LINE_2, LCD_SYMBOL_EMPTY);
    }
  }
void GenericSkinClass::UpdatePlayerZombie(void)
  {
  STRClass Str(STRPOS_STR_DEATH_TIME_REMAIN_FORMAT);
  Str.WriteFormat(Lcd.lcd_buf, Player.GetZombieTimeRemain());
  StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_1);
  }
void GenericSkinClass::UpdatePlayerDead(void)
  {
  STRClass Str(STRPOS_STR_DEATH_TIME_REMAIN_FORMAT);
  Str.WriteFormat(Lcd.lcd_buf, Player.GetDeathTimeRemain());
  StalkerUI.DisplayMenuBody(&Str, StalkerUI_Class::UI_MENU_BODY_LINE_1);
  }
void GenericSkinClass::UpdatePlayerAwaitingGraveyard(void)
  {
  StalkerUI.DisplayMenuBody(STRPOS_STR_GO_GRAVEYARD_2, StalkerUI_Class::UI_MENU_BODY_LINE_3);
  StalkerUI.DisplayMenuBody(STRPOS_STR_GO_GRAVEYARD_1, StalkerUI_Class::UI_MENU_BODY_LINE_1);
	sprintf (Lcd.lcd_buf, "%02d", Player.lastDamagerSource);
	LcdString(5, LCD_LINE_6);  }
void GenericSkinClass::UpdateMainMenuScreen(void)
  {
  if (Player.IsAlive())
    {
    if (Lcd.IsPlayerHealthNeedRedraw || Lcd.IsMainScreenNeedRedraw)
      {
      Lcd.IsPlayerHealthNeedRedraw  = false;
      Lcd.IsNeedUpdate        = true;
      //StalkerUI.DisplayHealthPercent(Player.GetHealthPercent());
      //PDAMenu.displayPercentBar(PDAMenuClass::HEALTH_GRID_POS_X1, Player.GetHealthPercent());
      this->DisplayPlayerHealthPercent();
      }
    if (Lcd.IsPlayerRadDoseNeedRedraw || Lcd.IsMainScreenNeedRedraw)
      {
      Lcd.IsPlayerRadDoseNeedRedraw  = false;
      Lcd.IsNeedUpdate        = true;
      //StalkerUI.DisplayRadiationDosePercent(Player.GetRadiationDosePercent());
      //PDAMenu.displayPercentBar(PDAMenuClass::PLAYER_RAD_DOSE_GRID_POS_X1, Player.GetRadiationDosePercent());
      this->DisplayEmissionLevel(DamageSource_t::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL, Player.GetRadiationDosePercent());
      }
    if (Lcd.IsEnvRadLevelNeedRedraw || Lcd.IsMainScreenNeedRedraw)
      {
      Lcd.IsEnvRadLevelNeedRedraw    = false;
      Lcd.IsNeedUpdate        = true;
      //PDAMenu.displayPercentBar(PDAMenuClass::RAD_GRID_POS_X1, Env.GetRadiationLevel()*100/Environment::MAX_RAD_LEVEL);
      //this->DisplayEmissionLevel(DamageSource_t::DAMAGE_SOURCE_RADIATION_EXTERNAL, (Env.GetRadiationLevel()*100/Environment::MAX_RAD_LEVEL));
      this->DisplayEmissionLevel(DamageSource_t::DAMAGE_SOURCE_RADIATION_EXTERNAL, (Env.GetComplexRadiationLevelPercent()));
      }
    if (Lcd.IsEnvPsyLevelNeedRedraw || Lcd.IsMainScreenNeedRedraw)
      {
      Lcd.IsEnvPsyLevelNeedRedraw    = false;
      Lcd.IsNeedUpdate        = true;
      //PDAMenu.displayPercentBar(PDAMenuClass::PSY_HAZARD_GRID_POS_X1, Env.GetPsyLevel()*100/Environment::MAX_LEVEL_PSY);
      this->DisplayEmissionLevel(DamageSource_t::DAMAGE_SOURCE_PSY, Env.GetPsyLevelPercent());
      }
    }
  else
    {
    if (Player.IsZombie())
      {
      this->UpdatePlayerZombie();
      }
    else
      {
      //sprintf (Lcd.lcd_buf, "%04uс",Player.getDeathTimeRemain());
      if (Player.IsAwaitingGraveyard())
        {
        this->UpdatePlayerAwaitingGraveyard();
        }
      else
        {
        this->UpdatePlayerDead();
        }
      }
    Lcd.IsNeedUpdate        = true;
    }
  }
void GenericSkinClass::Update(uint8_t msPassed)
  {

  }
///////////////////////////////////
void DetectorSkinClass::DrawMainGrid(void)
  {
  //PDAMenu.DrawImg(PDAImagesClass::IMAGES::IMG_RADIO_WAVES_0);
  sprintf(Lcd.lcd_buf, "CyberTech inc ");
  StalkerUI.DisplayMenuBody(Lcd.lcd_buf, StalkerUI_Class::UI_MENU_BODY_LINE_0);
  sprintf(Lcd.lcd_buf, "   –абочий    ");
  StalkerUI.DisplayMenuBody(Lcd.lcd_buf, StalkerUI_Class::UI_MENU_BODY_LINE_1);
  sprintf(Lcd.lcd_buf, "  терминал    ");
  StalkerUI.DisplayMenuBody(Lcd.lcd_buf, StalkerUI_Class::UI_MENU_BODY_LINE_2);
  sprintf(Lcd.lcd_buf, " активирован  ");
  StalkerUI.DisplayMenuBody(Lcd.lcd_buf, StalkerUI_Class::UI_MENU_BODY_LINE_3);
  }
void DetectorSkinClass::DrawPlayerZombie(void)
  {
  
  }
void DetectorSkinClass::DrawPlayerDead(void)
  {
  
  }
void DetectorSkinClass::DisplayPlayerHealthPercent()
  {
  
  }
void DetectorSkinClass::DisplayEmissionLevel(DamageSource_t dmgSrc, Percent_t levelPercent)
  {
  /*
  switch (dmgSrc)
    {
    case DamageSource_t::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL:
      {
      //this->DisplayPercentBar(this->PLAYER_RAD_DOSE_GRID_POS_X1, Player.GetRadiationDosePercent());
      }
  	break;
    case DamageSource_t::DAMAGE_SOURCE_RADIATION_EXTERNAL:
      {
      //this->DisplayPercentBar(this->RAD_GRID_POS_X1, Env.GetRadiationLevel()*100/Environment::MAX_RAD_LEVEL);
      }
  	break;
    case DamageSource_t::DAMAGE_SOURCE_DETECTOR_TMP:
      {
      if (this->counter < 500)
        {
        this->counter+=levelPercent;
        }
//      if (counter > 100)
//      if ((++divider & 3) == 1)
//        {
//        counter-=100;
//        //divider = 0;
        //if (levelPercent > 20)
//          {
          //PsyBeepKeepOnHack = 2;//(levelPercent/2) + 0;
          //PDASound.startSoundsPsy(175);
//          }
//        }
      //this->DisplayPercentBar(this->PSY_HAZARD_GRID_POS_X1, Env.GetPsyLevel()*100/Environment::MAX_LEVEL_PSY);
      if (levelPercent > 80)
        {
        PDAMenu.DrawImg(PDAImagesClass::IMAGES::IMG_RADIO_WAVES_3);
        //PsyBeepKeepOnHack = 6;
        //PDASound.startSoundsPsy(175);
        //PDASound.startSoundsPsy(175);
        //PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
        //PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
        //PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
        }
      else if (levelPercent > 50)
        {
        //PsyBeepKeepOnHack = 4;
        //PDASound.startSoundsPsy(175);
        PDAMenu.DrawImg(PDAImagesClass::IMAGES::IMG_RADIO_WAVES_2);
        //PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
        //PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
        }
      else if (levelPercent > 20)
        {
        //PsyBeepKeepOnHack = 2;
        //PDASound.startSoundsPsy(175);
        PDAMenu.DrawImg(PDAImagesClass::IMAGES::IMG_RADIO_WAVES_1);
        //PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
        }
      else
        {
        PDAMenu.DrawImg(PDAImagesClass::IMAGES::IMG_RADIO_WAVES_0);
        }
      }
  	break;
    default:
      //none
    break;
    }
  */
  }

ChargeVisualisationClass* DetectorSkinClass::GetChargeVisualisationInterface(void)
  {
  return &this->ChargeVisualisation;
  }
void DetectorSkinClass::DisplayPlayerInSafeShelter(bool isInSafeShelter)
  {
  if (isInSafeShelter)
    {
    //LcdSymbol(12, LCD_LINE_2, LCD_SYMBOL_SHIELD);
    } 
  else
    {
    //LcdSymbol(12, LCD_LINE_2, LCD_SYMBOL_EMPTY);
    }
  }
void DetectorSkinClass::DisplayBlowoutActive(bool isActive)
  {
  if (isActive)
    {
    //LcdSymbol(13, LCD_LINE_2, LCD_SYMBOL_STAR);
    } 
  else
    {
    //LcdSymbol(13, LCD_LINE_2, LCD_SYMBOL_EMPTY);
    }
  }
void DetectorSkinClass::UpdatePlayerZombie(void)
  {
  }
void DetectorSkinClass::UpdatePlayerDead(void)
  {
  }
void DetectorSkinClass::UpdatePlayerAwaitingGraveyard(void)
  {
  }
void DetectorSkinClass::UpdateMainMenuScreen(void)//1s period
  {
  //static uint8_t i=0;
  //this->DisplayEmissionLevel(DamageSource_t::DAMAGE_SOURCE_DETECTOR_TMP, EmissionInstanceDetector.GetSignalPowerPercent());
    //sprintf (Lcd.lcd_buf, "%03u %03u", EmissionInstanceDetector.GetSignalPowerPercent(), ++i);
    //StalkerUI.DisplayString(Lcd.lcd_buf, StalkerUI_Class::UI_LCD_LINE_5, 1);

//  this->DisplayEmissionLevel(DamageSource_t::DAMAGE_SOURCE_DETECTOR_TMP, 100);
  }
void DetectorSkinClass::Update(uint8_t msPassed)
  {
  /*
  static uint16_t ms100counter = 0;
  ms100counter  += msPassed;
  //sprintf (Lcd.lcd_buf, "%03u %03u", this->counter, msPassed);
  //StalkerUI.DisplayString(Lcd.lcd_buf, StalkerUI_Class::UI_LCD_LINE_4, 1);
  //SelectedSkin->Update(msPassed);
  if (ms100counter < 200)
    {
    return;
    }
  ms100counter -= 200;
  PsyBeepKeepOnHack += (this->counter/16);//(levelPercent/2) + 0;
  this->counter = 0;
  if (PsyBeepKeepOnHack > 5)
    {
    PsyBeepKeepOnHack = 5;
    }
  */
  //PDASound.startSoundsPsy(175);
  

  }

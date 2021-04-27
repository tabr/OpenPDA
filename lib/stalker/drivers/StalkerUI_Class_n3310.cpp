// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
void StalkerUI_Class::DisplayHealthPercent(Percent_t percent)
  {
//  PDAMenu.displayPercentBar(this->HORIZONTAL_HEALTH_GRID_POS_X1, percent);

  uint8_t Lines, i, GridPosX1, GridPosX2;

  GridPosX1  = this->HORIZONTAL_HEALTH_GRID_POS_X1;

  Lcd.IsNeedUpdate  = true;

  //  Lines     = (GridPosY2-GridPosY1+1-2);//общее кол-во линий
  GridPosX2    = GridPosX1+14;


  GridPosX1+=2;
  GridPosX2--;
  //  GridPosY2--;

  for (i=GridPosX1;i<GridPosX2;i++)            //очистка
    {
    LcdLine(i, this->HORIZONTAL_LCD_MENU_BAR_LINES_BOTTOM, i, this->HORIZONTAL_LCD_MENU_BAR_LINES_TOP, PIXEL_OFF);
    }
  Lines  = this->HORIZONTAL_LCD_MENU_BAR_LINES_NUM;    //Нельзя переместить вниз, т.к. иначе, по видимому, результат перемножения 8мибитный!
  Lines  = (Lines*percent)/100;              //заполненных линий
  for (i=GridPosX1;i<GridPosX2;i++)            //заполнение по вертикали
    {
    LcdLine(i, this->HORIZONTAL_LCD_MENU_BAR_LINES_BOTTOM, i, this->HORIZONTAL_LCD_MENU_BAR_LINES_BOTTOM-Lines, PIXEL_ON);
    }

  }
*/
void StalkerUI_Class::DisplayRadiationDosePercent(Percent_t percent)
  {
  uint8_t Lines, i, GridPosX1, GridPosX2;

  GridPosX1  = this->HORIZONTAL_PLAYER_RAD_DOSE_GRID_POS_X1;

  Lcd.IsNeedUpdate  = true;

  //  Lines     = (GridPosY2-GridPosY1+1-2);//общее кол-во линий
  GridPosX2    = GridPosX1+14;


  GridPosX1+=2;
  GridPosX2--;
  //  GridPosY2--;

  for (i=GridPosX1;i<GridPosX2;i++)            //очистка
    {
    LcdLine(i, this->HORIZONTAL_LCD_MENU_BAR_LINES_BOTTOM, i, this->HORIZONTAL_LCD_MENU_BAR_LINES_TOP, PIXEL_OFF);
    }
  Lines  = this->HORIZONTAL_LCD_MENU_BAR_LINES_NUM;    //Нельзя переместить вниз, т.к. иначе, по видимому, результат перемножения 8мибитный!
  Lines  = (Lines*percent)/100;              //заполненных линий
  for (i=GridPosX1;i<GridPosX2;i++)            //заполнение по вертикали
    {
    LcdLine(i, this->HORIZONTAL_LCD_MENU_BAR_LINES_BOTTOM, i, this->HORIZONTAL_LCD_MENU_BAR_LINES_BOTTOM-Lines, PIXEL_ON);
    }

  }
void StalkerUI_Class::DisplayString(uint8_t line)
  {
  line  = this->ToStringLine(line);
  LcdString(1, static_cast<LCD_LINE>(line), Lcd.lcd_buf);
  }
void StalkerUI_Class::DisplayString(StalkerUI_Class::UI_LCD_LINE line)
  {
  LcdString(1, static_cast<LCD_LINE>(line), Lcd.lcd_buf);
  }
//void StalkerUI_Class::DisplayString(StalkerUI_Class::UI_LCD_LINE line, STR_POS pos)
//  {
//  STRClass Str(pos);
//  Str.WriteTo(Lcd.lcd_buf);
//  this->DisplayString(line);
//  }
void StalkerUI_Class::DisplayString(char* str, StalkerUI_Class::UI_LCD_LINE line, uint8_t x)
  {
  LcdString(x, static_cast<LCD_LINE>(line), str);
  }
void StalkerUI_Class::DisplayString(STR_POS pos, StalkerUI_Class::UI_LCD_LINE line, uint8_t x)
  {
  STRClass Str(pos);
  Str.WriteTo(Lcd.lcd_buf);
  LcdString(x, static_cast<LCD_LINE>(line), Lcd.lcd_buf);
  }
void StalkerUI_Class::DisplayString(STRClass& Str, StalkerUI_Class::UI_LCD_LINE line, uint8_t x)
  {
  Str.WriteTo(Lcd.lcd_buf);
  this->DisplayString(Lcd.lcd_buf, line, x);
  }
//void StalkerUI_Class::DisplayString(uint8_t x, StalkerUI_Class::UI_LCD_LINE line, STR_POS pos)
//  {
//  STRClass Str(pos);
//  this->DisplayString(Str, line, x);
//  }
//void StalkerUI_Class::DisplayString(uint8_t x, StalkerUI_Class::UI_LCD_LINE line, const char* str PROGMEM)
//  {
//  LcdString(x, static_cast<LCD_LINE>(line), str);
//  }
//void StalkerUI_Class::DisplayString(StalkerUI_Class::UI_LCD_LINE line, char* str)
//  {
//  LcdString(1, static_cast<LCD_LINE>(line), str);
//  }
//void StalkerUI_Class::DisplayString(uint8_t x, uint8_t line, char* str)
//  {
//  if (line >= this->UI_LCD_LINE_SIZE)
//    {
//    line  = (this->UI_LCD_LINE_SIZE - 1);
//    }
//  LcdString(x, static_cast<LCD_LINE>(line), str);
//  }
//void StalkerUI_Class::DisplayString(uint8_t x, StalkerUI_Class::UI_LCD_LINE line, char* str)
//  {
//  LcdString(x, static_cast<LCD_LINE>(line), str);
//  }
//void StalkerUI_Class::DisplayString(StalkerUI_Class::UI_LCD_LINE line, const char* str PROGMEM)
//  {
//  LcdString(1, static_cast<LCD_LINE>(line), str);
//  }
void StalkerUI_Class::DisplayEmptyString(StalkerUI_Class::UI_MENU_BODY_LINE bLine)
  {
  this->DisplayEmptyString(this->FromMenyBodyLine(bLine));
  }
void StalkerUI_Class::DisplayEmptyString(StalkerUI_Class::UI_LCD_LINE line)
  {
  LcdEmptyString(static_cast<LCD_LINE>(line));
  }
void StalkerUI_Class::ClearDisplayCache(void)
  {
  LcdClearCache();
  }
//void StalkerUI_Class::DisplayMenuHead(const char* str PROGMEM)
//  {
//  this->DisplayString(UI_LCD_LINE_0, str);
//  }
void StalkerUI_Class::DisplayMenuHead(char* str)
  {
  this->DisplayString(str, UI_LCD_LINE_0);
  }
void StalkerUI_Class::DisplayMenuHead(STRClass& Str)
  {
  Str.WriteTo(Lcd.lcd_buf);
  this->DisplayString(UI_LCD_LINE_0);
  }
void StalkerUI_Class::DisplayMenuHead(STR_POS pos)
  {
  STRClass Str(pos);
  this->DisplayMenuHead(Str);
  }
void StalkerUI_Class::DisplayMenuBottom(STRClass& Str, uint8_t x)
  {
  Str.WriteTo(Lcd.lcd_buf);
  this->DisplayString(Lcd.lcd_buf, UI_LCD_LINE_5, x);
  }
void StalkerUI_Class::DisplayMenuBottom(STR_POS pos, uint8_t x)
  {
  STRClass Str(pos);
  this->DisplayMenuBottom(Str, x);
  }
//void StalkerUI_Class::DisplayMenuBottom(const char* str PROGMEM)
//  {
//  this->DisplayString(UI_LCD_LINE_5, str);
//  }

void StalkerUI_Class::DisplayMenuBottom(void)
  {
  this->DisplayString(Lcd.lcd_buf, UI_LCD_LINE_5);
  }
StalkerUI_Class::UI_LCD_LINE StalkerUI_Class::ToStringLine(uint8_t line)
  {
  if (line >= StalkerUI_Class::UI_LCD_LINE_SIZE)
    {
    line = (StalkerUI_Class::UI_LCD_LINE_SIZE - 1);
    }
  if (line < 1)
    {
    line = 1;
    }
  return static_cast<StalkerUI_Class::UI_LCD_LINE>(line);
  }
StalkerUI_Class::UI_MENU_BODY_LINE StalkerUI_Class::ToMenuBody(uint8_t line)
  {
  if (line >= this->UI_MENU_BODY_LINE_SIZE)
    {
    line  = (this->UI_MENU_BODY_LINE_SIZE - 1);
    }
  return static_cast<StalkerUI_Class::UI_MENU_BODY_LINE>(line);
  }
void StalkerUI_Class::DisplayMenuBody(uint8_t line)
  {
  this->DisplayMenuBody(this->ToMenuBody(line));
  }
void StalkerUI_Class::DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE bLine)
  {
  this->DisplayString(this->FromMenyBodyLine(bLine));
  }
/*
void StalkerUI_Class::DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE bLine, char* str)
  {
  this->DisplayString(str, this->FromMenyBodyLine(bLine));
  }
void StalkerUI_Class::DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE bLine, STR_POS format_pos, ...)
  {
  STRClass Str(format_pos);
  char format[STRClass::MAX_STR_LENGTH+1];
  memset(format, 0, sizeof(format));
  Str.WriteTo(format);
  va_list ap;

  va_start(ap, format_pos);
  //это вместо fprintf
  vsprintf(Lcd.lcd_buf, format, ap);
  va_end(ap);
  this->DisplayMenuBody(bLine, Lcd.lcd_buf);
  }
*/
void StalkerUI_Class::DisplayMenuBody(char* str, StalkerUI_Class::UI_MENU_BODY_LINE bLine, uint8_t x)
  {
  this->DisplayString(str, this->FromMenyBodyLine(bLine), x);
  }
void StalkerUI_Class::DisplayMenuBody(STRClass* Str, StalkerUI_Class::UI_MENU_BODY_LINE bLine, uint8_t x)
  {
//  Str->WriteTo(Lcd.lcd_buf);
  this->DisplayString(Str->Get(), this->FromMenyBodyLine(bLine), x);
  }
void StalkerUI_Class::DisplayMenuBody(STR_POS pos, StalkerUI_Class::UI_MENU_BODY_LINE bLine, uint8_t x)
  {
  STRClass Str(pos);
  Str.WriteTo(Lcd.lcd_buf);
  this->DisplayString(Lcd.lcd_buf, this->FromMenyBodyLine(bLine), x);
  }
/*
void StalkerUI_Class::DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE bLine, STR_POS pos)
  {
  STRClass Str(pos);
  Str.WriteTo(Lcd.lcd_buf);
  this->DisplayString(this->FromMenyBodyLine(bLine));
  }
void StalkerUI_Class::DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE bLine, const char* str PROGMEM)
  {
  this->DisplayString(this->FromMenyBodyLine(bLine), str);
  }
void StalkerUI_Class::DisplayMenuBody(uint8_t line, const char* str PROGMEM)
  {
  if (line >= this->UI_MENU_BODY_LINE_SIZE)
    {
    line  = (this->UI_MENU_BODY_LINE_SIZE - 1);
    }
  this->DisplayString(this->FromMenyBodyLine(static_cast<StalkerUI_Class::UI_MENU_BODY_LINE>(line)), str);
  }
void StalkerUI_Class::DisplayMenuBody(uint8_t x, StalkerUI_Class::UI_MENU_BODY_LINE bLine, const char* str PROGMEM)
  {
  this->DisplayString(x, this->FromMenyBodyLine(bLine), str);
  }
*/
void StalkerUI_Class::DisplayEmptyBodyString(StalkerUI_Class::UI_MENU_BODY_LINE line)
  {
  this->DisplayEmptyString(this->FromMenyBodyLine(line));
  }
void StalkerUI_Class::ClearDisplay(void)
  {
  ClearDisplayCache();
  }
void StalkerUI_Class::ClearMenuBody(void)
  {
  //LcdClear2_to_5();
  memset( (LcdCache+LCD_X_RES), 0x00, (LCD_X_RES*4));
  }
void StalkerUI_Class::RequestUpdate(void)
  {
  n3310LcdClass::RequestUpdate();
  }


StalkerUI_Class::UI_LCD_LINE StalkerUI_Class::FromMenyBodyLine(UI_MENU_BODY_LINE line)
  {
  return static_cast<StalkerUI_Class::UI_LCD_LINE>(line+1);
  }
//void StalkerUI_Class::ShowButtonDown1(void)
//  {
//  LcdString(11,LCD_LINE_6, STR_PDAMENU_6ROW_DOWN);
//  }
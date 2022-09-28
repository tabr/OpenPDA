#ifndef LCD_MODE_CHAR
void OpenPDA_Nokia3110DriverClass::LcdSymbol (LCD_SYMBOLS symbol, uint8_t char_y_position, uint8_t char_x_position){
  //LcdCacheChanged = true;
  //char_x_position--;
  GotoYXFont(char_x_position,char_y_position);
  for (uint8_t i = 0; i < 5; i++ ){
    LcdCache[LcdCacheIdx++] = pgm_read_byte( &(LCD_Symbols[symbol][i]) ) ;
  }
  LcdCache[LcdCacheIdx] = 0x00;
  if(++LcdCacheIdx == LCD_CACHE_SIZE ){
    LcdCacheIdx = 0;
  }
}

bool OpenPDA_Nokia3110DriverClass::IsPointValid(uint8_t x, uint8_t y){
  if( x < OpenPDA_Nokia3110DriverClass::LCD_WIDTH_PIXEL || y < OpenPDA_Nokia3110DriverClass::LCD_HEIGHT_PIXEL ){
    return true;
  }
  return false;//OUT OF BORDER
}
bool OpenPDA_Nokia3110DriverClass::IsPointInvalid(uint8_t x, uint8_t y){
  return !(IsPointValid(x, y));
}
void OpenPDA_Nokia3110DriverClass::LcdPixel ( uint8_t x, uint8_t y, LcdPixelMode mode ){
  uint16_t index;
  uint8_t offset;

  if ( !(IsPointValid(x, y))){
    return;
  }

  // Пересчет индекса и смещения
  index = ( ( y / LCD_FONT_HEIGHT ) * LCD_WIDTH_PIXEL ) + x;
  offset  = y - ( ( y / LCD_FONT_HEIGHT ) * LCD_FONT_HEIGHT );

  if ( mode == PIXEL_OFF ){
    LcdCache[ index ] &= ( ~( 0x01 << offset ) );
  }
  else if ( mode == PIXEL_ON ){
    LcdCache[ index ] |= ( 0x01 << offset );
  }
  else if ( mode  == PIXEL_XOR ){
    LcdCache[ index ] ^= ( 0x01 << offset );
  }

  return;// OK
}
#endif

void OpenPDA_Nokia3110DriverClass::LcdImage ( const uint8_t *imageData ){
#ifdef LCD_MODE_CHAR
  for (uint16_t i = 0;i<LCD_CACHE_SIZE;i++){
    SendByteTroughtBus(pgm_read_byte(&(imageData[i])));
  }
#else
  memcpy_P( LcdCache, imageData, LCD_CACHE_SIZE );
#endif
}


//void OpenPDA_Nokia3110DriverClass::LcdCleanBuf(void){
//  memset(OpenPDA_Nokia3110DriverClass::lcd_string_char_buf, 0, sizeof(OpenPDA_Nokia3110DriverClass::lcd_string_char_buf));
//}

void OpenPDA_Nokia3110DriverClass::LcdClearCache(void){
  //LcdCacheChanged = true;
#ifdef LCD_MODE_CHAR
  memset( LcdCharCache, 0x00, LCD_CHAR_CACHE_SIZE );
#else
  memset( LcdCache, 0x00, LCD_CACHE_SIZE );
#endif
}

void OpenPDA_Nokia3110DriverClass::GotoYXFont ( uint8_t char_y_position, uint8_t char_x_position ){
  //uint8_t x = char_x_position * (OpenPDA_Nokia3110DriverClass::LCD_FONT_WIDTH + 1);
  //uint8_t y = char_y_position * (OpenPDA_Nokia3110DriverClass::LCD_FONT_HEIGHT + 1);
  //uint8_t x = char_x_position * (OpenPDA_Nokia3110DriverClass::LCD_HEIGHT_PIXEL / LCD_FONT_HEIGHT);//because each byte is 8 pixels height
  //uint8_t y = char_y_position * OpenPDA_Nokia3110DriverClass::LCD_WIDTH_PIXEL;
  //if ( !(IsPointValid(x, y))){
  //  return;
  //}
#ifdef LCD_MODE_CHAR
  LcdCharCacheIdx = (char_y_position * LCD_WIDTH_CHARS) + char_x_position;
  if (LcdCharCacheIdx >= LCD_CHAR_CACHE_SIZE ){
    LcdCharCacheIdx = 0;
  }
#else
  LcdCacheIdx = (char_x_position * (OpenPDA_Nokia3110DriverClass::LCD_HEIGHT_PIXEL / LCD_FONT_HEIGHT)) + (char_y_position * OpenPDA_Nokia3110DriverClass::LCD_WIDTH_PIXEL);//because each byte is 8 pixels height
  if (LcdCacheIdx >= LCD_CACHE_SIZE ){
    LcdCacheIdx = 0;
  }
  //LcdCacheIdx = x + y;
  //OK
#endif
}

void OpenPDA_Nokia3110DriverClass::LcdClearUpdate(void){
  OpenPDA_Nokia3110DriverClass::LcdClearCache();
  OpenPDA_Nokia3110DriverClass::RequestSendCacheToLCD();
}


/*
void OpenPDA_Nokia3110DriverClass::LcdChrFull ( uint8_t ch ){
  for (uint8_t i = 0; i < LCD_MAX_HEIGHT_CHAR; i++ ){
    // Копируем вид символа из таблицы в кэш
    //LcdCache[LcdCacheIdx++] = pgm_read_byte( &(FontLookup[ch][i]) ) << 1;
    LcdCache[LcdCacheIdx++] = pgm_read_byte( &(ASCIItableFull[ch][i]) );
  }
  // Горизонтальный разрыв между символами
  LcdCache[LcdCacheIdx] = 0x00;
  // Если достигли позицию указателя LCD_CACHE_SIZE - 1, переходим в начало
  if(LcdCacheIdx == (LCD_CACHE_SIZE - 1) ){
    LcdCacheIdx = 0;
    return ;//OK_WITH_WRAP;
  }
  // Иначе просто инкрементируем указатель
  LcdCacheIdx++;
  // OK;
}
*/
void OpenPDA_Nokia3110DriverClass::LcdChr ( uint8_t ch, uint8_t cache_idx ){
#ifdef LCD_MODE_CHAR
  LcdCharCacheIdx = cache_idx;
  if (LcdCharCacheIdx >= LCD_CHAR_CACHE_SIZE ){
    LcdCharCacheIdx = 0;
  }
#else
  GotoYXFont((cache_idx % LCD_WIDTH_CHARS), (cache_idx/LCD_WIDTH_CHARS));
#endif
  LcdChr(ch);
}
void OpenPDA_Nokia3110DriverClass::LcdChr ( uint8_t ch, uint8_t char_y_position, uint8_t char_x_position ){
  GotoYXFont(char_y_position, char_x_position);
  LcdChr(ch);
}
void OpenPDA_Nokia3110DriverClass::LcdChr ( uint8_t ch ){
  if ( (ch >= LCD_FONT_ASCII_TABLE_RANGE_1_START) && (ch <= LCD_FONT_ASCII_TABLE_RANGE_1_END) ){ //first range
    // Смещение в таблице для символов ASCII[0x20-0x7F]
    ch -= LCD_FONT_ASCII_TABLE_RANGE_1_START;
  }
  else if ( ch >= LCD_FONT_ASCII_TABLE_RANGE_2_START ){ // untill the end - 0xFF
    // Смещение в таблице для символов CP1251[0xC0-0xFF]
    ch -= LCD_FONT_ASCII_TABLE_RANGE_2_DIFF;
  }
  else{
    // Остальные игнорируем (их просто нет в таблице для экономии памяти)
    ch = LCD_FONT_ASCII_TABLE_SYMBOL_NO_SYMBOL;
  }
#ifdef LCD_MODE_CHAR
  LcdCharCache[LcdCharCacheIdx] = ch;
#else
  for (uint8_t i = 0; i < LCD_MAX_HEIGHT_CHAR; i++ ){
    // Копируем вид символа из таблицы в кэш
    //LcdCache[LcdCacheIdx++] = pgm_read_byte( &(FontLookup[ch][i]) ) << 1;
    LcdCache[LcdCacheIdx++] = pgm_read_byte( &(FontLookup[ch][i]) );
  }

  // Горизонтальный разрыв между символами
  LcdCache[LcdCacheIdx] = 0x00;
  // Если достигли позицию указателя LCD_CACHE_SIZE - 1, переходим в начало
  if(LcdCacheIdx == (LCD_CACHE_SIZE - 1) ){
    LcdCacheIdx = 0;
    return ;//OK_WITH_WRAP;
  }
  // Иначе просто инкрементируем указатель
  LcdCacheIdx++;
  // OK;
#endif
}



void OpenPDA_Nokia3110DriverClass::IOInit(void){
  LcdPinCLK::SetDirOut();
  LcdPinSDIN::SetDirOut();
  LcdPinDC::SetDirOut();
  LcdPinSCE::SetDirOut();
  LcdPinRST::SetDirOut();
  LcdPinRST::SetPullUp();
//while (1) {BeepPin::SetOutLow();RedLEDPin::SetOutToggle();delay_ms(1000);}
  
  LcdPinCLK::SetOutLow();//1
  LcdPinSDIN::SetOutHigh();//1
  LcdPinDC::SetOutLow();
  LcdPinSCE::SetOutHigh();//High - disabled
  LcdPinRST::SetOutHigh();

  OpenPDA_Nokia3110DriverClass::BusInit();
  
}
void OpenPDA_Nokia3110DriverClass::HardwareInitialization(void){
  DeactivateDisplay();
  Reset20MS();
  uint8_t commandPacket[]=
    {
    COMMAND_FUNCTION_SET__EXTENDED_INSTRUCTION_SET | COMMAND_FUNCTION_SET__POWER_DOWN_DEACTIVATE,//0b00100001,//0x21,//
    COMMAND_H1_SET_VOP_INSTRUCTION | (70 & COMMAND_H1_SET_VOP_MASK),//0b11001000,//0xc8,//
    COMMAND_H1_TEMPERATURE_CONTROL__COEFFICIENT_0,//0b00000110,//0x06,//temperature compensation for liquid crystals
    COMMAND_H1_BIAS_SYSTEM_INSTRUCTION | (2 & COMMAND_H1_BIAS_SYSTEM_MASK),//0b00010011,//0x13,//
    COMMAND_FUNCTION_SET__BASIC_INSTRUCTION_SET | COMMAND_FUNCTION_SET__HORIZONTAL_ADDRESSING | COMMAND_FUNCTION_SET__POWER_DOWN_DEACTIVATE,//0b00100000,//0x20,//
    COMMAND_H0_DISPLAY_CONTROL__NORMAL_MODE,//0b00001100,//0x0c,//
    COMMAND_H0_SET_Y_ADDRESS_RAM_INSTRUCTION | (0 & Y_ADDRESS_MASK),//0b10000000,//0x80,//
    COMMAND_H0_SET_X_ADDRESS_RAM_INSTRUCTION | (0 & X_ADDRESS_MASK),//0b01000000,//0x40,//
    };
  LcdSendCommandPacket(sizeof(commandPacket), commandPacket);

  ActivateDisplay();
  //LcdPinDC::SetOutHigh();//data next - only data
  SetData();

  // init cleanup
  ClearCache();
  SendCacheToLCD();
}

void OpenPDA_Nokia3110DriverClass::ActivateDisplay(void){
  LcdPinSCE::SetOutLow();
}
void OpenPDA_Nokia3110DriverClass::DeactivateDisplay(void){
  TODO("this is hack: //LcdPinSCE::SetOutHigh()");
  //LcdPinSCE::SetOutHigh();
}

void OpenPDA_Nokia3110DriverClass::Reset20MS(void){
  LcdPinRST::SetOutLow();
  _delay_ms(20);
  LcdPinRST::SetOutHigh();
}
void OpenPDA_Nokia3110DriverClass::SetData(void){
  LcdPinDC::SetOutHigh();//data
}
void OpenPDA_Nokia3110DriverClass::SetCommand(void){
  LcdPinDC::SetOutLow();//command
}

void OpenPDA_Nokia3110DriverClass::LcdSendCommandPacket(uint16_t length, uint8_t* packet){
  ActivateDisplay();
  SetCommand();

  for (uint16_t i=0;i<length;i++){
    SendByteTroughtBus(packet[i]);
    }
  DeactivateDisplay();
}

  
void OpenPDA_Nokia3110DriverClass::ClearCache(void){
#ifdef LCD_MODE_CHAR
  memset(LcdCharCache, LCD_CHAR_CACHE_SIZE, 0);
#else
  memset(LcdCache, LCD_CACHE_SIZE, 0);
#endif
}

void OpenPDA_Nokia3110DriverClass::SendCacheToLCD(void){
  ResetHardwareBufferPointer();
  ActivateDisplay();
#ifdef LCD_MODE_CHAR
  for (uint8_t ch=0; ch<LCD_CHAR_CACHE_SIZE; ch++){
    for (uint8_t i = 0; i < LCD_MAX_HEIGHT_CHAR; i++ ){
      SendByteTroughtBus(pgm_read_byte( &(FontLookup[LcdCharCache[ch]][i]) ));
      //SendByteTroughtBus(0xFA);
    }
    // Горизонтальный разрыв между символами
  SendByteTroughtBus(0x00);
  }
#else
  for (uint16_t i=0;i<LCD_CACHE_SIZE;i++){
    SendByteTroughtBus(LcdCache[i]);
  }
#endif
}

void OpenPDA_Nokia3110DriverClass::ResetHardwareBufferPointer(void){
  //uint8_t commandPacket[]={0x80, 0x40};
  uint8_t commandPacket[]={
    COMMAND_H0_SET_Y_ADDRESS_RAM_INSTRUCTION | (0 & Y_ADDRESS_MASK),
    COMMAND_H0_SET_X_ADDRESS_RAM_INSTRUCTION | (0 & X_ADDRESS_MASK)
    };
  LcdSendCommandPacket(sizeof(commandPacket), commandPacket);
  SetData();
}
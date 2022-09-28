template <class T>
void OpenPDA_UI_generic<T>::SetFlagCacheChanged(void){
  SetFlag(FLAG_0_CACHE_CHANGED);
}

template <class T>
void OpenPDA_UI_generic<T>::ClearFlagCacheChanged(void){
  ClearFlag(FLAG_0_CACHE_CHANGED);
}

template <class T>
void OpenPDA_UI_generic<T>::SetFlag(FLAGS f){
  sbi(flag, f);
}

template <class T>
void OpenPDA_UI_generic<T>::ClearFlag(FLAGS f){
  cbi(flag, f);
}

template <class T>
bool OpenPDA_UI_generic<T>::IsCacheChanged(void){
  return (flag & (1<<FLAG_0_CACHE_CHANGED));
}


template <class T>
void OpenPDA_UI_generic<T>::UpdateIfNeed(void){
  if (IsCacheChanged()){
    RealUpdate();
    ClearFlag(FLAG_0_CACHE_CHANGED);
  }
}

template <class T>
bool OpenPDA_UI_generic<T>::IsCharXPosiotionValid(uint8_t char_x_position){
  return char_x_position < UI_WIDTH_CHARS;
}

template <class T>
void OpenPDA_UI_generic<T>::LcdString (const char *buf, UI_LINE y_line){
  LcdString(buf, y_line, 0);
}

template <class T>
void OpenPDA_UI_generic<T>::LcdString (const char *buf, UI_LINE y_line, uint8_t char_x_position){
  if (char_x_position >= UI_WIDTH_CHARS){
    return;
  }
  SetFlagCacheChanged();
  while (char_x_position < UI_WIDTH_CHARS){ //also this validate x
    char ch = *buf;
    buf++;
    if (ch == '\0'){
      return;
    }
    driver::LcdChr(ch, y_line, char_x_position);
    //LcdStr((uint8_t*)buf);
    char_x_position++;
  }
  //driver-LcdCleanBuf();
}

template <class T>
void OpenPDA_UI_generic<T>::ClearDisplayCache(void){
  SetFlagCacheChanged();
  driver::LcdClearCache();
}

template <class T>
void OpenPDA_UI_generic<T>::DisplayBottom(const char *buf){
  LcdString(buf, UI_LINE_5_BOTTOM);
}

template <class T>
void OpenPDA_UI_generic<T>::DisplayHead(const char *buf){
  //char str[UI_WIDTH_CHARS];
  //memset(str, 0, UI_WIDTH_CHARS);
  //strncpy(str, buf, UI_WIDTH_CHARS);
  //LcdString(str, UI_LINE_0_HEAD);
  LcdString(buf, UI_LINE_0_HEAD);
}

template <class T>
void OpenPDA_UI_generic<T>::DisplayBody(const char *buf, UI_BODY_LINE body_line, uint8_t char_x_position){
  LcdString(buf, static_cast<UI_LINE>(body_line + 1), char_x_position);
}
template <class T>
void OpenPDA_UI_generic<T>::DisplayBody(const char *buf, UI_BODY_LINE body_line){
  DisplayBody(buf, body_line, 0);
}

template <class T>
void OpenPDA_UI_generic<T>::RealUpdate(void){
  ClearFlagCacheChanged();
  driver::SendCacheToLCD();
}

template <class T>
void OpenPDA_UI_generic<T>::ShowImage(const uint8_t *imageData){
  SetFlagCacheChanged();
  driver::LcdImage (imageData );
}


#ifdef OPENPDA_UI_GRAPHICS_ENABLED

/*
 * Имя                   :  LcdLine
 * Описание              :  Рисует линию между двумя точками на дисплее (алгоритм Брезенхэма)
 * Аргумент(ы)           :  x1, y1  -> абсолютные координаты начала линии
 *                          x2, y2  -> абсолютные координаты конца линии
 *                          mode    -> Off, On или Xor. Смотри enum в n3310.h
 * Возвращаемое значение :  смотри возвращаемое значение в n3310lcd.h
 */
template <class T>
void OpenPDA_UI_generic<T>::LcdLineOrbitrary ( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode )
{
    int16_t dx, dy, stepx, stepy, fraction;
    
    if ( !(IsPointValid(x1, y1)) || !(IsPointValid(x2, y1))){
        return;
    }
    
    // dy   y2 - y1
    // -- = -------
    // dx   x2 - x1

    dy = y2 - y1;
    dx = x2 - x1;

    // dy отрицательное
    if ( dy < 0 ){
        dy    = -dy;
        stepy = -1;
    }
    else{
        stepy = 1;
    }

    // dx отрицательное
    if ( dx < 0 ){
        dx    = -dx;
        stepx = -1;
    }
    else{
        stepx = 1;
    }

    dx <<= 1;
    dy <<= 1;

    // Рисуем начальную точку
    LcdPixel( x1, y1, mode );

    // Рисуем следующие точки до конца
    if ( dx > dy ){
        fraction = dy - ( dx >> 1);
        while ( x1 != x2 ){
            if ( fraction >= 0 ){
                y1 += stepy;
                fraction -= dx;
            }
            x1 += stepx;
            fraction += dy;

            LcdPixel( x1, y1, mode );

        }
    }
    else{
        fraction = dx - ( dy >> 1);
        while ( y1 != y2 ){
            if ( fraction >= 0 ){
                x1 += stepx;
                fraction -= dy;
            }
            y1 += stepy;
            fraction += dx;

            LcdPixel( x1, y1, mode );
        }
    }
}

template <class T>
void OpenPDA_UI_generic<T>::LcdLineHorizontal  ( uint8_t x, uint8_t y, uint8_t length, uint8_t mode ){
    if ( IsPointInalid(x, y)){
        return;
    }
    uint16_t untill_x = x + length;
    for (;x++;x < untill_x ) {
        if ( IsPointInalid(x, y)){ //now x is incremented
            return;
        }
        LcdPixel( x, y, mode );
    }
}

template <class T>
void OpenPDA_UI_generic<T>::LcdLineVertical  ( uint8_t x, uint8_t y, uint8_t length, uint8_t mode ){ //can be used a hack: each 8 bytes draw in 3 stages: [part or 0][bytes cycle or 0][part or 0]
    if ( IsPointInalid(x, y)){
        return;
    }
    uint16_t untill_y = y + length;
    for (;y++;y < untill_y ) {
        if ( IsPointInalid(x, y)){ //now x is incremented
            return;
        }
        LcdPixel( x, y, mode );
    }
}
#endif
/*
void OpenPDA_UI_generic<T>::LcdStringNoClean (uint8_t x, LCD_LINE y){
    x--;
    LcdGotoXYFont(x,y);
    LcdStr((uint8_t*)Lcd.lcd_buf);
}

void OpenPDA_UI_generic<T>::LcdString (uint8_t x, LCD_LINE y){
    x--;
    LcdGotoXYFont(x,y);
    LcdStr((uint8_t*)Lcd.lcd_buf);
    LcdCleanBuf();
}

void OpenPDA_UI_generic<T>::LcdString (LCD_LINE y){
    LcdString(1, y);
}

void OpenPDA_UI_generic<T>::LcdString (uint8_t x, LCD_LINE y, const char *dataArray PROGMEM){
    char readedChar=0;
    LcdGotoXYFont((x-1), y);
    uint8_t charIdx=0;
    while(charIdx < LCD_CHAR_WIDTH)
        {
        readedChar =  pgm_read_byte(dataArray + charIdx);
        if (readedChar == '\0'){
            break;
            }
        LcdChr( readedChar);
        charIdx++;
    }
}
void OpenPDA_UI_generic<T>::LcdStringUpdate (uint8_t x, LCD_LINE y, const char *dataArray PROGMEM){
    LcdString(x, y, dataArray);
    n3310LcdClass::RequestUpdate();
}

void OpenPDA_UI_generic<T>::LcdStringUpdate (uint8_t x, LCD_LINE y, char *buf){
    LcdString (x, y, buf);
    n3310LcdClass::RequestUpdate();
}

void OpenPDA_UI_generic<T>::LcdEmptyString(LCD_LINE line){
    //LcdCacheChanged = true;
    memset( (LcdCache+((LCD_X_RES)*(line))), 0x00, LCD_X_RES);
}
*/
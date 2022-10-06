#pragma once

//generic mean 6 lines with 14 chars on each. 48x84 px size
//this equals nikia3310/5110 LCD but not the same
#ifndef LCD_MODE_CHAR
  #define OPENPDA_UI_GRAPHICS_ENABLED
#endif
template <class T>
class OpenPDA_UI_generic{
public:
typedef T driver;
  enum UI_LINE {
    UI_LINE_0_HEAD,
    UI_LINE_1_BODY,  
    UI_LINE_2_BODY,
    UI_LINE_3_BODY,
    UI_LINE_4_BODY,
    UI_LINE_5_BOTTOM,
  };
  enum UI_BODY_LINE {
    UI_BODY_LINE_0,
    UI_BODY_LINE_1,
    UI_BODY_LINE_2,
    UI_BODY_LINE_3,
  };
  enum FLAGS {
    FLAG_0_CACHE_CHANGED,
  };
  const static uint8_t UI_WIDTH_PIXEL           = 84;
  const static uint8_t UI_HEIGHT_PIXEL          = 48;
  const static uint8_t UI_WIDTH_CHARS           = 14;
  const static uint8_t UI_HEIGHT_CHARS          = 6;
  //OpenPDA_UI_generic(void);
  //T& GetDriver(void){
  //  return this->driver;
  //}
  static void ClearFlag(FLAGS f);
  static void SetFlag(FLAGS f);
  static void ClearFlagCacheChanged(void);
  static void SetFlagCacheChanged(void);
  static bool IsCacheChanged(void);
  static void ShowImage(const uint8_t *imageData);
  static void RealUpdate(void);
  static void UpdateIfNeed(void);
  static void ClearDisplayCache(void);
  static bool IsCharXPosiotionValid(uint8_t char_x_position);
  static void LcdString (const char *buf, UI_LINE y, uint8_t char_x_position);
  static void LcdString (const char *buf, UI_LINE y);
  static void DisplayHead(const char *buf);
  static void DisplayBottom(const char *buf);
  static void DisplayBody(const char *buf, UI_BODY_LINE body_line, uint8_t char_x_position);
  static void DisplayBody(const char *buf, UI_BODY_LINE body_line);
#ifdef OPENPDA_UI_GRAPHICS_ENABLED
  static void LcdLineHorizontal ( uint8_t x, uint8_t y, uint8_t length, uint8_t mode );//LcdPixelMode mode
  static void LcdLineVertical ( uint8_t x, uint8_t y, uint8_t length, uint8_t mode );//LcdPixelMode mode
  static void LcdLineOrbitrary  ( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode );//LcdPixelMode mode
  static bool IsPointValid(const uint8_t x, const uint8_t y);
  static bool IsPointInvalid(const uint8_t x, const uint8_t y);
#endif //OPENPDA_UI_GRAPHICS_ENABLED
/*
  
    void LcdString (uint8_t x, LCD_LINE y);
    void LcdString (LCD_LINE y);
    void LcdString (uint8_t x, LCD_LINE y, char *buf);
    void LcdString (uint8_t x, LCD_LINE y, const char *dataArray PROGMEM); //outputs char array until '\0' or LCD_CHAR_WIDTH
    void LcdStringUpdate (uint8_t x, LCD_LINE y, const char *dataArray PROGMEM);
    void LcdStringUpdate (uint8_t x, LCD_LINE y, char *buf);
    void LcdStringNoClean (uint8_t x, LCD_LINE y);
    void LcdEmptyString(LCD_LINE line);
*/
//private:
  //T driver;
  static uint8_t flag;
  static char line_buffer[32];
};
template <class T>
uint8_t OpenPDA_UI_generic<T>::flag = 0;
template <class T>
char OpenPDA_UI_generic<T>::line_buffer[32];



//TODO: make kernel-based statuses!
template <class T>
class OpenPDA_UI_stalker: public OpenPDA_UI_generic<T>{
public:
  enum CHANGABLE_STATUSES{
    CHANGABLE_STATUS_PLAYER_DEAD,//default is alive
    CHANGABLE_STATUS_PLAYER_ZOMBIE,//default not zombie
    CHANGABLE_STATUS_PLAYER_IS_SAFE_SHELTER,
    CHANGABLE_STATUS_,
    //CHANGABLE_STATUS_,
    //CHANGABLE_STATUS_,
    //CHANGABLE_STATUS_,
    //CHANGABLE_STATUS_,
  };
  static void UpdateHealthPercent(Percent_t percent);
  static void UpdateExternalRadiationPercent(Percent_t percent);
  static void UpdateRadDosePercent(Percent_t percent);
  static void UpdateBatteryChargePercent(Percent_t percent);
  static void JustSelected(void);
  static void Update(uint8_t msPassed);
};

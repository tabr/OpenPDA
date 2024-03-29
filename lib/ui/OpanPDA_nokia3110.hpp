#pragma once

//#define LCD_MODE_CHAR //does not support graphics or DMA

#include "TODOmacro.h"
template <uint8_t b7, uint8_t b6, uint8_t b5, uint8_t b4, uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0>
struct BinaryConst
  {
  enum {get      =  (((b7&1)<<7) | ((b6&1)<<6) | ((b5&1)<<5) | ((b4&1)<<4) | ((b3&1)<<3) | ((b2&1)<<2) | ((b1&1)<<1) | ((b0&1)<<0))};
  };

class OpenPDA_LcdInterface {
    public:
    virtual void IOInit(void) = 0;
    virtual void HardwareInitializaion(void) = 0;
}

TODO("warning sprintf can overwrite data over the buffer!");

class OpenPDA_Nokia3110DriverClass {
public:
  enum LcdPixelMode {
    PIXEL_OFF,
    PIXEL_ON,
    PIXEL_XOR,
    PIXEL_LAST_ELEMENT = PIXEL_XOR
  };
  enum LCD_SYMBOLS {
    LCD_SYMBOL_EMPTY,
    LCD_SYMBOL_SHIELD,
    LCD_SYMBOL_STAR,
  };
  const static uint8_t LCD_WIDTH_PIXEL                        = 84;
  const static uint8_t LCD_HEIGHT_PIXEL                       = 48;
  const static uint8_t LCD_BIT_DEPTH                          = 1;
  const static uint8_t LCD_MAX_WIDTH_PIXEL                    = LCD_WIDTH_PIXEL - 1;
  const static uint8_t LCD_MAX_HEIGHT_PIXEL                   = LCD_HEIGHT_PIXEL - 1;
  const static uint16_t LCD_CACHE_SIZE                        = (LCD_WIDTH_PIXEL * LCD_HEIGHT_PIXEL * LCD_BIT_DEPTH) / 8;
  const static uint8_t LCD_WIDTH_CHARS                         = 14;
  const static uint8_t LCD_HEIGHT_CHARS                        = 6;
  const static uint8_t LCD_MAX_WIDTH_CHAR                     = LCD_WIDTH_CHARS - 1;
  const static uint8_t LCD_MAX_HEIGHT_CHAR                    = LCD_HEIGHT_CHARS - 1;
  const static uint8_t LCD_CHAR_CACHE_SIZE                    = LCD_WIDTH_CHARS * LCD_HEIGHT_CHARS;
  const static uint8_t LCD_FONT_WIDTH                         = 5;//do not change this!
  const static uint8_t LCD_FONT_HEIGHT                        = 8;//do not change this!
  const static uint8_t LCD_FONT_ASCII_TABLE_RANGE_1_START     = 0x20; //32
  const static uint8_t LCD_FONT_ASCII_TABLE_RANGE_1_END       = 0x7F; //127
  const static uint8_t LCD_FONT_ASCII_TABLE_RANGE_1_DIFF      = LCD_FONT_ASCII_TABLE_RANGE_1_START;
  const static uint8_t LCD_FONT_ASCII_TABLE_RANGE_2_START     = 0xC0; //192
  const static uint8_t LCD_FONT_ASCII_TABLE_RANGE_2_END       = 0xFF; //255
  const static uint8_t LCD_FONT_ASCII_TABLE_RANGE_2_DIFF      = (LCD_FONT_ASCII_TABLE_RANGE_2_START - LCD_FONT_ASCII_TABLE_RANGE_1_END) + LCD_FONT_ASCII_TABLE_RANGE_1_START - 1 ;
  const static uint8_t LCD_FONT_ASCII_TABLE_DEFAULT_SIZE      = 0xFF;
  const static uint8_t LCD_FONT_ASCII_TABLE_SYMBOL_NO_SYMBOL  = LCD_FONT_ASCII_TABLE_RANGE_2_DIFF - 1;//last symbol in ASCII table
  
  const static uint8_t COMMAND_FUNCTION_SET_INSTRUCTION                         = BinaryConst<0,0,1,0,0,0,0,0>::get;
  const static uint8_t COMMAND_H0_DISPLAY_CONTROL_INSTRUCTION                   = BinaryConst<0,0,0,0,1,0,0,0>::get;
  const static uint8_t COMMAND_H0_SET_VOP_RANGE_INSTRUCTION                     = BinaryConst<0,0,0,1,0,0,0,0>::get;
  const static uint8_t COMMAND_H0_SET_Y_ADDRESS_RAM_INSTRUCTION                 = BinaryConst<0,1,0,0,0,0,0,0>::get;
  const static uint8_t COMMAND_H0_SET_X_ADDRESS_RAM_INSTRUCTION                 = BinaryConst<1,0,0,0,0,0,0,0>::get;
  const static uint8_t Y_ADDRESS_MASK                                           = BinaryConst<0,0,0,0,1,1,1,1>::get;//[0..8]
  const static uint8_t X_ADDRESS_MASK                                           = BinaryConst<0,1,1,1,1,1,1,1>::get;//[0..101]

  const static uint8_t COMMAND_H1_TEMPERATURE_CONTROL_INSTRUCTION               = BinaryConst<0,0,0,0,0,1,0,0>::get;
//  const static uint8_t COMMAND_H1_SET_VOLTAGE_MULTIPLIER_FACTOR_INSTRUCTION     = BinaryConst<0,0,0,1,0,0,0,0>::get;
  const static uint8_t COMMAND_H1_BIAS_SYSTEM_INSTRUCTION                       = BinaryConst<0,0,0,1,0,0,0,0>::get;
  const static uint8_t COMMAND_H1_SET_VOP_INSTRUCTION                           = BinaryConst<1,0,0,0,0,0,0,0>::get;

  const static uint8_t COMMAND_FUNCTION_SET__BASIC_INSTRUCTION_SET              = BinaryConst<0,0,0,0,0,0,0,0>::get | COMMAND_FUNCTION_SET_INSTRUCTION;
  const static uint8_t COMMAND_FUNCTION_SET__EXTENDED_INSTRUCTION_SET           = BinaryConst<0,0,0,0,0,0,0,1>::get | COMMAND_FUNCTION_SET_INSTRUCTION;
  const static uint8_t COMMAND_FUNCTION_SET__HORIZONTAL_ADDRESSING              = BinaryConst<0,0,0,0,0,0,0,0>::get | COMMAND_FUNCTION_SET_INSTRUCTION;
  const static uint8_t COMMAND_FUNCTION_SET__VERTICAL_ADDRESSING                = BinaryConst<0,0,0,0,0,0,1,0>::get | COMMAND_FUNCTION_SET_INSTRUCTION;
  const static uint8_t COMMAND_FUNCTION_SET__POWER_DOWN_DEACTIVATE              = BinaryConst<0,0,0,0,0,0,0,0>::get | COMMAND_FUNCTION_SET_INSTRUCTION;
  const static uint8_t COMMAND_FUNCTION_SET__POWER_DOWN_ACTIVATE                = BinaryConst<0,0,0,0,0,1,0,0>::get | COMMAND_FUNCTION_SET_INSTRUCTION;
  const static uint8_t COMMAND_H0_DISPLAY_CONTROL__DISPLAY_BLANK                = BinaryConst<0,0,0,0,0,0,0,0>::get | COMMAND_H0_DISPLAY_CONTROL_INSTRUCTION;
  const static uint8_t COMMAND_H0_DISPLAY_CONTROL__NORMAL_MODE                  = BinaryConst<0,0,0,0,0,1,0,0>::get | COMMAND_H0_DISPLAY_CONTROL_INSTRUCTION;
  const static uint8_t COMMAND_H0_DISPLAY_CONTROL__ALL_DISPLAY_SEGMENTS_ON      = BinaryConst<0,0,0,0,0,0,0,1>::get | COMMAND_H0_DISPLAY_CONTROL_INSTRUCTION;
  const static uint8_t COMMAND_H0_DISPLAY_CONTROL__INVERSE_VIDEO_MODE           = BinaryConst<0,0,0,0,0,1,0,1>::get | COMMAND_H0_DISPLAY_CONTROL_INSTRUCTION;
  const static uint8_t COMMAND_H0_SET_VOP_RANGE__HI                             = BinaryConst<0,0,0,0,0,0,0,1>::get | COMMAND_H0_SET_VOP_RANGE_INSTRUCTION;
  const static uint8_t COMMAND_H0_SET_VOP_RANGE__LOW                            = BinaryConst<0,0,0,0,0,0,0,0>::get | COMMAND_H0_SET_VOP_RANGE_INSTRUCTION;
  const static uint8_t COMMAND_H1_TEMPERATURE_CONTROL__COEFFICIENT_0            = BinaryConst<0,0,0,0,0,0,0,0>::get | COMMAND_H1_TEMPERATURE_CONTROL_INSTRUCTION;
  const static uint8_t COMMAND_H1_TEMPERATURE_CONTROL__COEFFICIENT_1            = BinaryConst<0,0,0,0,0,0,0,1>::get | COMMAND_H1_TEMPERATURE_CONTROL_INSTRUCTION;
  const static uint8_t COMMAND_H1_TEMPERATURE_CONTROL__COEFFICIENT_2            = BinaryConst<0,0,0,0,0,0,1,0>::get | COMMAND_H1_TEMPERATURE_CONTROL_INSTRUCTION;
  const static uint8_t COMMAND_H1_TEMPERATURE_CONTROL__COEFFICIENT_3            = BinaryConst<0,0,0,0,0,0,1,1>::get | COMMAND_H1_TEMPERATURE_CONTROL_INSTRUCTION;
//  const static uint8_t COMMAND_H1_SET_VOLTAGE_MULTIPLIER_FACTOR_2               = BinaryConst<0,0,0,0,0,0,0,0>::get | COMMAND_H1_SET_VOLTAGE_MULTIPLIER_FACTOR_INSTRUCTION;
//  const static uint8_t COMMAND_H1_SET_VOLTAGE_MULTIPLIER_FACTOR_3               = BinaryConst<0,0,0,0,0,0,0,1>::get | COMMAND_H1_SET_VOLTAGE_MULTIPLIER_FACTOR_INSTRUCTION;
//  const static uint8_t COMMAND_H1_SET_VOLTAGE_MULTIPLIER_FACTOR_4               = BinaryConst<0,0,0,0,0,0,1,0>::get | COMMAND_H1_SET_VOLTAGE_MULTIPLIER_FACTOR_INSTRUCTION;
//  const static uint8_t COMMAND_H1_SET_VOLTAGE_MULTIPLIER_FACTOR_5               = BinaryConst<0,0,0,0,0,0,1,1>::get | COMMAND_H1_SET_VOLTAGE_MULTIPLIER_FACTOR_INSTRUCTION;
  const static uint8_t COMMAND_H1_BIAS_SYSTEM_MASK                              = BinaryConst<0,0,0,0,0,1,1,1>::get;
  const static uint8_t COMMAND_H1_SET_VOP_MASK                                  = BinaryConst<0,1,1,1,1,1,1,1>::get;
  
#ifdef LCD_MODE_CHAR
  static char LcdCharCache[LCD_CHAR_CACHE_SIZE];
  static uint8_t LcdCharCacheIdx;
#else
  static uint8_t LcdCache[ LCD_CACHE_SIZE ];
  static uint16_t LcdCacheIdx;

  static void LcdSymbol (LCD_SYMBOLS symbol, uint8_t char_y_position, uint8_t char_x_position);
  static void LcdPixel ( uint8_t x, uint8_t y, uint8_t mode );
  static void LcdPixel ( uint8_t x, uint8_t y, LcdPixelMode mode );
  static bool IsPointValid(uint8_t x, uint8_t y);
  static bool IsPointInvalid(uint8_t x, uint8_t y);
#endif
  static void LcdImage ( const uint8_t *imageData ); //works ... not really as expected with LCD_MODE_CHAR
  //char lcd_string_char_buf[32];
  static void ActivateDisplay(void);
  static void DeactivateDisplay(void);
  static void Reset20MS(void);
  static void SetData(void);
  static void SetCommand(void);
  static void LcdSendCommandPacket(uint16_t length, uint8_t* packet);
  

  //void LcdCleanBuf(void);
  static void LcdClearCache(void);
  static void LcdClearUpdate(void);
  
  static void GotoYXFont ( uint8_t char_y_position, uint8_t char_x_position );// starting from 0
  static void LcdChr ( uint8_t ch );
  static void LcdChr ( uint8_t ch, uint8_t cache_idx );
  static void LcdChr ( uint8_t ch, uint8_t char_y_position, uint8_t char_x_position );
  //void LcdChrFull ( uint8_t ch );
  
  static void IOInit(void);
  static void HardwareInitialization(void);
  static void ClearCache(void);
  static void RequestSendCacheToLCD(void);
  static void SendCacheToLCD(void);
  static void ResetHardwareBufferPointer(void);

  static void BusInit(void);//should be defined for each MCU + LCD individually
  static void SendByteTroughtBus(uint8_t byte);//should be defined for each MCU + LCD individually
};
#ifdef LCD_MODE_CHAR
  uint8_t OpenPDA_Nokia3110DriverClass::LcdCharCacheIdx = 0;
  char OpenPDA_Nokia3110DriverClass::LcdCharCache[ LCD_CHAR_CACHE_SIZE ];
#else
  uint16_t OpenPDA_Nokia3110DriverClass::LcdCacheIdx = 0;
  uint8_t OpenPDA_Nokia3110DriverClass::LcdCache[ LCD_CACHE_SIZE ];
#endif
//Nokia3110Lcd::p_instance = NULL;

/*
 * Таблица для отображения символов (ASCII[0x20-0x7F] + CP1251[0xC0-0xFF] = всего 160 символов)
 */
static const uint8_t FontLookup [][5] PROGMEM =
{
   { 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x20  32
   { 0x00, 0x00, 0x5F, 0x00, 0x00 },   // ! 0x21  33
   { 0x00, 0x07, 0x00, 0x07, 0x00 },   // " 0x22  34
   { 0x14, 0x7F, 0x14, 0x7F, 0x14 },   // # 0x23  35
   { 0x24, 0x2A, 0x7F, 0x2A, 0x12 },   // $ 0x24  36
   { 0x4C, 0x2C, 0x10, 0x68, 0x64 },   // % 0x25  37
   { 0x36, 0x49, 0x55, 0x22, 0x50 },   // & 0x26  38
   { 0x00, 0x05, 0x03, 0x00, 0x00 },   // ' 0x27  39
   { 0x00, 0x1C, 0x22, 0x41, 0x00 },   // ( 0x28  40
   { 0x00, 0x41, 0x22, 0x1C, 0x00 },   // ) 0x29  41
   { 0x14, 0x08, 0x3E, 0x08, 0x14 },   // * 0x2A  42
   { 0x08, 0x08, 0x3E, 0x08, 0x08 },   // + 0x2B  43
   { 0x00, 0x00, 0x50, 0x30, 0x00 },   // , 0x2C  44
   { 0x10, 0x10, 0x10, 0x10, 0x10 },   // - 0x2D  45
   { 0x00, 0x60, 0x60, 0x00, 0x00 },   // . 0x2E  46
   { 0x20, 0x10, 0x08, 0x04, 0x02 },   // / 0x2F  47
   { 0x3E, 0x51, 0x49, 0x45, 0x3E },   // 0 0x30  48
   { 0x00, 0x42, 0x7F, 0x40, 0x00 },   // 1 0x31  49
   { 0x42, 0x61, 0x51, 0x49, 0x46 },   // 2 0x32  50
   { 0x21, 0x41, 0x45, 0x4B, 0x31 },   // 3 0x33  51
   { 0x18, 0x14, 0x12, 0x7F, 0x10 },   // 4 0x34  52
   { 0x27, 0x45, 0x45, 0x45, 0x39 },   // 5 0x35  53
   { 0x3C, 0x4A, 0x49, 0x49, 0x30 },   // 6 0x36  54
   { 0x01, 0x71, 0x09, 0x05, 0x03 },   // 7 0x37  55
   { 0x36, 0x49, 0x49, 0x49, 0x36 },   // 8 0x38  56
   { 0x06, 0x49, 0x49, 0x29, 0x1E },   // 9 0x39  57
   { 0x00, 0x36, 0x36, 0x00, 0x00 },   // : 0x3A  58
   { 0x00, 0x56, 0x36, 0x00, 0x00 },   // ; 0x3B  59
   { 0x08, 0x14, 0x22, 0x41, 0x00 },   // < 0x3C  60
   { 0x14, 0x14, 0x14, 0x14, 0x14 },   // = 0x3D  61
   { 0x00, 0x41, 0x22, 0x14, 0x08 },   // > 0x3E  62
   { 0x02, 0x01, 0x51, 0x09, 0x06 },   // ? 0x3F  63
   { 0x32, 0x49, 0x79, 0x41, 0x3E },   // @ 0x40  64
   { 0x7E, 0x11, 0x11, 0x11, 0x7E },   // A 0x41  65
   { 0x7F, 0x49, 0x49, 0x49, 0x36 },   // B 0x42  66
   { 0x3E, 0x41, 0x41, 0x41, 0x22 },   // C 0x43  67
   { 0x7F, 0x41, 0x41, 0x22, 0x1C },   // D 0x44  68
   { 0x7F, 0x49, 0x49, 0x49, 0x41 },   // E 0x45  69
   { 0x7F, 0x09, 0x09, 0x09, 0x01 },   // F 0x46  70
   { 0x3E, 0x41, 0x49, 0x49, 0x7A },   // G 0x47  71
   { 0x7F, 0x08, 0x08, 0x08, 0x7F },   // H 0x48  72
   { 0x00, 0x41, 0x7F, 0x41, 0x00 },   // I 0x49  73
   { 0x20, 0x40, 0x41, 0x3F, 0x01 },   // J 0x4A  74
   { 0x7F, 0x08, 0x14, 0x22, 0x41 },   // K 0x4B  75
   { 0x7F, 0x40, 0x40, 0x40, 0x40 },   // L 0x4C  76
   { 0x7F, 0x02, 0x0C, 0x02, 0x7F },   // M 0x4D  77
   { 0x7F, 0x04, 0x08, 0x10, 0x7F },   // N 0x4E  78
   { 0x3E, 0x41, 0x41, 0x41, 0x3E },   // O 0x4F  79
   { 0x7F, 0x09, 0x09, 0x09, 0x06 },   // P 0x50  80
   { 0x3E, 0x41, 0x51, 0x21, 0x5E },   // Q 0x51  81
   { 0x7F, 0x09, 0x19, 0x29, 0x46 },   // R 0x52  82
   { 0x46, 0x49, 0x49, 0x49, 0x31 },   // S 0x53  83
   { 0x01, 0x01, 0x7F, 0x01, 0x01 },   // T 0x54  84
   { 0x3F, 0x40, 0x40, 0x40, 0x3F },   // U 0x55  85
   { 0x1F, 0x20, 0x40, 0x20, 0x1F },   // V 0x56  86
   { 0x3F, 0x40, 0x38, 0x40, 0x3F },   // W 0x57  87
   { 0x63, 0x14, 0x08, 0x14, 0x63 },   // X 0x58  88
   { 0x07, 0x08, 0x70, 0x08, 0x07 },   // Y 0x59  89
   { 0x61, 0x51, 0x49, 0x45, 0x43 },   // Z 0x5A  90
   { 0x00, 0x7F, 0x41, 0x41, 0x00 },   // [ 0x5B  91
   { 0x02, 0x04, 0x08, 0x10, 0x20 },   // \ 0x5C  92
   { 0x00, 0x41, 0x41, 0x7F, 0x00 },   // ] 0x5D  93
   { 0x04, 0x02, 0x01, 0x02, 0x04 },   // ^ 0x5E  94
   { 0x40, 0x40, 0x40, 0x40, 0x40 },   // _ 0x5F  95
   { 0x00, 0x01, 0x02, 0x04, 0x00 },   // ` 0x60  96
   { 0x20, 0x54, 0x54, 0x54, 0x78 },   // a 0x61  97
   { 0x7F, 0x48, 0x44, 0x44, 0x38 },   // b 0x62  98
   { 0x38, 0x44, 0x44, 0x44, 0x20 },   // c 0x63  99
   { 0x38, 0x44, 0x44, 0x48, 0x7F },   // d 0x64 100
   { 0x38, 0x54, 0x54, 0x54, 0x18 },   // e 0x65 101
   { 0x08, 0x7E, 0x09, 0x01, 0x02 },   // f 0x66 102
   { 0x0C, 0x52, 0x52, 0x52, 0x3E },   // g 0x67 103
   { 0x7F, 0x08, 0x04, 0x04, 0x78 },   // h 0x68 104
   { 0x00, 0x44, 0x7D, 0x40, 0x00 },   // i 0x69 105
   { 0x20, 0x40, 0x44, 0x3D, 0x00 },   // j 0x6A 106
   { 0x7F, 0x10, 0x28, 0x44, 0x00 },   // k 0x6B 107
   { 0x00, 0x41, 0x7F, 0x40, 0x00 },   // l 0x6C 108
   { 0x7C, 0x04, 0x18, 0x04, 0x78 },   // m 0x6D 109
   { 0x7C, 0x08, 0x04, 0x04, 0x78 },   // n 0x6E 110
   { 0x38, 0x44, 0x44, 0x44, 0x38 },   // o 0x6F 111
   { 0x7C, 0x14, 0x14, 0x14, 0x08 },   // p 0x70 112
   { 0x08, 0x14, 0x14, 0x18, 0x7C },   // q 0x71 113
   { 0x7C, 0x08, 0x04, 0x04, 0x08 },   // r 0x72 114
   { 0x48, 0x54, 0x54, 0x54, 0x20 },   // s 0x73 115
   { 0x04, 0x3F, 0x44, 0x40, 0x20 },   // t 0x74 116
   { 0x3C, 0x40, 0x40, 0x20, 0x7C },   // u 0x75 117
   { 0x1C, 0x20, 0x40, 0x20, 0x1C },   // v 0x76 118
   { 0x3C, 0x40, 0x30, 0x40, 0x3C },   // w 0x77 119
   { 0x44, 0x28, 0x10, 0x28, 0x44 },   // x 0x78 120
   { 0x0C, 0x50, 0x50, 0x50, 0x3C },   // y 0x79 121
   { 0x44, 0x64, 0x54, 0x4C, 0x44 },   // z 0x7A 122
   { 0x00, 0x08, 0x36, 0x41, 0x00 },   // { 0x7B 123
   { 0x00, 0x00, 0x7F, 0x00, 0x00 },   // | 0x7C 124
   { 0x00, 0x41, 0x36, 0x08, 0x00 },   // } 0x7D 125
   { 0x08, 0x04, 0x08, 0x10, 0x08 },   // ~ 0x7E 126
   { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },   //  0x7F 127

   { 0x7C, 0x12, 0x11, 0x12, 0x7C },   // А 0xC0 192
   { 0x7F, 0x49, 0x49, 0x49, 0x31 },   // Б 0xC1 193
   { 0x7F, 0x49, 0x49, 0x49, 0x36 },   // В 0xC2 194
   { 0x7F, 0x01, 0x01, 0x01, 0x01 },   // Г 0xC3 195
   { 0x60, 0x3F, 0x21, 0x3F, 0x60 },   // Д 0xC4 196
   { 0x7F, 0x49, 0x49, 0x49, 0x41 },   // Е 0xC5 197
   { 0x77, 0x08, 0x7F, 0x08, 0x77 },   // Ж 0xC6 198
   { 0x22, 0x41, 0x49, 0x49, 0x36 },   // З 0xC7 199
   { 0x7F, 0x10, 0x08, 0x04, 0x7F },   // И 0xC8 200
   { 0x7E, 0x10, 0x09, 0x04, 0x7E },   // Й 0xC9 201
   { 0x7F, 0x08, 0x14, 0x22, 0x41 },   // К 0xCA 202
   { 0x40, 0x3E, 0x01, 0x01, 0x7F },   // Л 0xCB 203
   { 0x7F, 0x02, 0x0C, 0x02, 0x7F },   // М 0xCC 204
   { 0x7F, 0x08, 0x08, 0x08, 0x7F },   // Н 0xCD 205
   { 0x3E, 0x41, 0x41, 0x41, 0x3E },   // О 0xCE 206
   { 0x7F, 0x01, 0x01, 0x01, 0x7F },   // П 0xCF 207
   { 0x7F, 0x09, 0x09, 0x09, 0x06 },   // Р 0xD0 208
   { 0x3E, 0x41, 0x41, 0x41, 0x22 },   // С 0xD1 209
   { 0x01, 0x01, 0x7F, 0x01, 0x01 },   // Т 0xD2 210
   { 0x07, 0x48, 0x48, 0x48, 0x3F },   // У 0xD3 211
   { 0x0E, 0x11, 0x7F, 0x11, 0x0E },   // Ф 0xD4 212
   { 0x63, 0x14, 0x08, 0x14, 0x63 },   // Х 0xD5 213
   { 0x3F, 0x20, 0x20, 0x3F, 0x60 },   // Ц 0xD6 214
   { 0x07, 0x08, 0x08, 0x08, 0x7F },   // Ч 0xD7 215
   { 0x7F, 0x40, 0x7E, 0x40, 0x7F },   // Ш 0xD8 216
   { 0x3F, 0x20, 0x3F, 0x20, 0x7F },   // Щ 0xD9 217
   { 0x01, 0x7F, 0x48, 0x48, 0x30 },   // Ъ 0xDA 218
   { 0x7F, 0x48, 0x30, 0x00, 0x7F },   // Ы 0xDB 219
   { 0x00, 0x7F, 0x48, 0x48, 0x30 },   // Ь 0xDC 220
   { 0x22, 0x41, 0x49, 0x49, 0x3E },   // Э 0xDD 221
   { 0x7F, 0x08, 0x3E, 0x41, 0x3E },   // Ю 0xDE 222
   { 0x46, 0x29, 0x19, 0x09, 0x7F },   // Я 0xDF 223
   { 0x20, 0x54, 0x54, 0x54, 0x78 },   // а 0xE0 224
   { 0x3C, 0x4A, 0x4A, 0x4A, 0x31 },   // б 0xE1 225
   { 0x7C, 0x54, 0x54, 0x28, 0x00 },   // в 0xE2 226
   { 0x7C, 0x04, 0x04, 0x0C, 0x00 },   // г 0xE3 227
   { 0x60, 0x3C, 0x24, 0x3C, 0x60 },   // д 0xE4 228
   { 0x38, 0x54, 0x54, 0x54, 0x18 },   // е 0xE5 229
   { 0x6C, 0x10, 0x7C, 0x10, 0x6C },   // ж 0xE6 230
   { 0x00, 0x44, 0x54, 0x54, 0x28 },   // з 0xE7 231
   { 0x7C, 0x20, 0x10, 0x08, 0x7C },   // и 0xE8 232
   { 0x7C, 0x21, 0x12, 0x09, 0x7C },   // й 0xE9 233
   { 0x7C, 0x10, 0x28, 0x44, 0x00 },   // к 0xEA 234
   { 0x40, 0x38, 0x04, 0x04, 0x7C },   // л 0xEB 235
   { 0x7C, 0x08, 0x10, 0x08, 0x7C },   // м 0xEC 236
   { 0x7C, 0x10, 0x10, 0x10, 0x7C },   // н 0xED 237
   { 0x38, 0x44, 0x44, 0x44, 0x38 },   // о 0xEE 238
   { 0x7C, 0x04, 0x04, 0x04, 0x7C },   // п 0xEF 239
   { 0x7C, 0x14, 0x14, 0x14, 0x08 },   // р 0xF0 240
   { 0x38, 0x44, 0x44, 0x44, 0x00 },   // с 0xF1 241
   { 0x04, 0x04, 0x7C, 0x04, 0x04 },   // т 0xF2 242
   { 0x0C, 0x50, 0x50, 0x50, 0x3C },   // у 0xF3 243
   { 0x08, 0x14, 0x7C, 0x14, 0x08 },   // ф 0xF4 244
   { 0x44, 0x28, 0x10, 0x28, 0x44 },   // х 0xF5 245
   { 0x3C, 0x20, 0x20, 0x3C, 0x60 },   // ц 0xF6 246
   { 0x0C, 0x10, 0x10, 0x10, 0x7C },   // ч 0xF7 247
   { 0x7C, 0x40, 0x7C, 0x40, 0x7C },   // ш 0xF8 248
   { 0x3C, 0x20, 0x3C, 0x20, 0x7C },   // щ 0xF9 249
   { 0x04, 0x7C, 0x50, 0x50, 0x20 },   // ъ 0xFA 250
   { 0x7C, 0x50, 0x20, 0x00, 0x7C },   // ы 0xFB 251
   { 0x00, 0x7C, 0x50, 0x50, 0x20 },   // ь 0xFC 252
   { 0x28, 0x44, 0x54, 0x54, 0x38 },   // э 0xFD 253
   { 0x7C, 0x10, 0x38, 0x44, 0x38 },   // ю 0xFE 254
   { 0x48, 0x54, 0x34, 0x14, 0x7C }    // я 0xFF 255
};
static const uint8_t LCD_Symbols [][5] PROGMEM=
  {
  { 0x00, 0x00, 0x00, 0x00, 0x00 },   // empty
  { 0x1F, 0x3F, 0x7F, 0x3F, 0x1F },   // shield
  { 0x2A, 0x1C, 0x7F, 0x1C, 0x2A },  // star
  };


/*
static const uint8_t ASCIItableFull[][5] = {
  {0x00, 0x00, 0x00, 0x00, 0x00},// 00
  {0x00, 0x00, 0x5F, 0x00, 0x00},// 01
  {0x00, 0x07, 0x00, 0x07, 0x00},// 02
  {0x14, 0x7F, 0x14, 0x7F, 0x14},// 03 
  {0x24, 0x2A, 0x7F, 0x2A, 0x12},// 04
  {0x23, 0x13, 0x08, 0x64, 0x62},// 05
  {0x36, 0x49, 0x55, 0x22, 0x50},// 06
  {0x00, 0x05, 0x03, 0x00, 0x00},// 07
  {0x00, 0x1C, 0x22, 0x41, 0x00},// 08
  {0x00, 0x41, 0x22, 0x1C, 0x00},// 09 
  {0x14, 0x08, 0x3E, 0x08, 0x14},// 0A
  {0x08, 0x08, 0x3E, 0x08, 0x08},// 0B 
  {0x00, 0x50, 0x30, 0x00, 0x00},// 0C
  {0x08, 0x08, 0x08, 0x08, 0x08},// 0D 
  {0x00, 0x60, 0x60, 0x00, 0x00},// 0E
  {0x20, 0x10, 0x08, 0x04, 0x02},// 0F 
  {0x00, 0x00, 0x00, 0x00, 0x00},// 10 
  {0x00, 0x00, 0x5F, 0x00, 0x00},// 11 
  {0x00, 0x07, 0x00, 0x07, 0x00},// 12 
  {0x14, 0x7F, 0x14, 0x7F, 0x14},// 13 
  {0x24, 0x2A, 0x7F, 0x2A, 0x12},// 14 
  {0x23, 0x13, 0x08, 0x64, 0x62},// 15 
  {0x36, 0x49, 0x55, 0x22, 0x50},// 16
  {0x00, 0x05, 0x03, 0x00, 0x00},// 17 
  {0x00, 0x1C, 0x22, 0x41, 0x00},// 18 
  {0x00, 0x41, 0x22, 0x1C, 0x00},// 19 
  {0x14, 0x08, 0x3E, 0x08, 0x14},// 1A 
  {0x08, 0x08, 0x3E, 0x08, 0x08},// 1B
  {0x00, 0x50, 0x30, 0x00, 0x00},// 1C 
  {0x08, 0x08, 0x08, 0x08, 0x08},// 1D 
  {0x00, 0x60, 0x60, 0x00, 0x00},// 1E 
  {0x20, 0x10, 0x08, 0x04, 0x02},// 1F
  {0x00, 0x00, 0x00, 0x00, 0x00},// 20 space
  {0x00, 0x00, 0x5F, 0x00, 0x00},// 21 ! 
  {0x00, 0x07, 0x00, 0x07, 0x00},// 22 " 
  {0x14, 0x7F, 0x14, 0x7F, 0x14},// 23 # 
  {0x24, 0x2A, 0x7F, 0x2A, 0x12},// 24 $ 
  {0x23, 0x13, 0x08, 0x64, 0x62},// 25 % 
  {0x36, 0x49, 0x55, 0x22, 0x50},// 26 & 
  {0x00, 0x05, 0x03, 0x00, 0x00},// 27 '
  {0x00, 0x1C, 0x22, 0x41, 0x00},// 28 ( 
  {0x00, 0x41, 0x22, 0x1C, 0x00},// 29 )
  {0x14, 0x08, 0x3E, 0x08, 0x14},// 2a * 
  {0x08, 0x08, 0x3E, 0x08, 0x08},// 2b + 
  {0x00, 0x50, 0x30, 0x00, 0x00},// 2c , 
  {0x08, 0x08, 0x08, 0x08, 0x08},// 2d - 
  {0x00, 0x60, 0x60, 0x00, 0x00},// 2e . 
  {0x20, 0x10, 0x08, 0x04, 0x02},// 2f / 
  {0x3E, 0x51, 0x49, 0x45, 0x3E},// 30 0 
  {0x00, 0x42, 0x7F, 0x40, 0x00},// 31 1 
  {0x42, 0x61, 0x51, 0x49, 0x46},// 32 2 
  {0x21, 0x41, 0x45, 0x4B, 0x31},// 33 3 
  {0x18, 0x14, 0x12, 0x7F, 0x10},// 34 4
  {0x27, 0x45, 0x45, 0x45, 0x39},// 35 5 
  {0x3C, 0x4A, 0x49, 0x49, 0x30},// 36 6 
  {0x01, 0x71, 0x09, 0x05, 0x03},// 37 7 
  {0x36, 0x49, 0x49, 0x49, 0x36},// 38 8 
  {0x06, 0x49, 0x49, 0x29, 0x1E},// 39 9 
  {0x00, 0x36, 0x36, 0x00, 0x00},// 3a : 
  {0x00, 0x56, 0x36, 0x00, 0x00},// 3b ; 
  {0x08, 0x14, 0x22, 0x41, 0x00},// 3c < 
  {0x14, 0x14, 0x14, 0x14, 0x14},// 3d = 
  {0x00, 0x41, 0x22, 0x14, 0x08},// 3e > 
  {0x02, 0x01, 0x51, 0x09, 0x06},// 3f ? 
  {0x32, 0x49, 0x79, 0x41, 0x3E},// 40 @ 
  {0x7E, 0x11, 0x11, 0x11, 0x7E},// 41 A 
  {0x7F, 0x49, 0x49, 0x49, 0x36},// 42 B 
  {0x3E, 0x41, 0x41, 0x41, 0x22},// 43 C 
  {0x7F, 0x41, 0x41, 0x22, 0x1C},// 44 D 
  {0x7F, 0x49, 0x49, 0x49, 0x41},// 45 E 
  {0x7F, 0x09, 0x09, 0x09, 0x01},// 46 F 
  {0x3E, 0x41, 0x49, 0x49, 0x7A},// 47 G 
  {0x7F, 0x08, 0x08, 0x08, 0x7F},// 48 H 
  {0x00, 0x41, 0x7F, 0x41, 0x00},// 49 I 
  {0x20, 0x40, 0x41, 0x3F, 0x01},// 4a J 
  {0x7F, 0x08, 0x14, 0x22, 0x41},// 4b K 
  {0x7F, 0x40, 0x40, 0x40, 0x40},// 4c L 
  {0x7F, 0x02, 0x0C, 0x02, 0x7F},// 4d M 
  {0x7F, 0x04, 0x08, 0x10, 0x7F},// 4e N 
  {0x3E, 0x41, 0x41, 0x41, 0x3E},// 4f O 
  {0x7F, 0x09, 0x09, 0x09, 0x06},// 50 P 
  {0x3E, 0x41, 0x51, 0x21, 0x5E},// 51 Q 
  {0x7F, 0x09, 0x19, 0x29, 0x46},// 52 R 
  {0x46, 0x49, 0x49, 0x49, 0x31},// 53 S 
  {0x01, 0x01, 0x7F, 0x01, 0x01},// 54 T 
  {0x3F, 0x40, 0x40, 0x40, 0x3F},// 55 U 
  {0x1F, 0x20, 0x40, 0x20, 0x1F},// 56 V 
  {0x3F, 0x40, 0x38, 0x40, 0x3F},// 57 W 
  {0x63, 0x14, 0x08, 0x14, 0x63},// 58 X 
  {0x07, 0x08, 0x70, 0x08, 0x07},// 59 Y 
  {0x61, 0x51, 0x49, 0x45, 0x43},// 5a Z 
  {0x00, 0x7F, 0x41, 0x41, 0x00},// 5b [ 
  {0x02, 0x04, 0x08, 0x10, 0x20},// 5c Yen Currency Sign 
  {0x00, 0x41, 0x41, 0x7F, 0x00},// 5d ]
  {0x04, 0x02, 0x01, 0x02, 0x04},// 5e ^ 
  {0x40, 0x40, 0x40, 0x40, 0x40},// 5f _ 
  {0x00, 0x01, 0x02, 0x04, 0x00},// 60 ` 
  {0x20, 0x54, 0x54, 0x54, 0x78},// 61 a 
  {0x7F, 0x48, 0x44, 0x44, 0x38},// 62 b 
  {0x38, 0x44, 0x44, 0x44, 0x20},// 63 c 
  {0x38, 0x44, 0x44, 0x48, 0x7F},// 64 d 
  {0x38, 0x54, 0x54, 0x54, 0x18},// 65 e 
  {0x08, 0x7E, 0x09, 0x01, 0x02},// 66 f 
  {0x0C, 0x52, 0x52, 0x52, 0x3E},// 67 g 
  {0x7F, 0x08, 0x04, 0x04, 0x78},// 68 h 
  {0x00, 0x44, 0x7D, 0x40, 0x00},// 69 i 
  {0x20, 0x40, 0x44, 0x3D, 0x00},// 6a j 
  {0x7F, 0x10, 0x28, 0x44, 0x00},// 6b k 
  {0x00, 0x41, 0x7F, 0x40, 0x00},// 6c l 
  {0x7C, 0x04, 0x18, 0x04, 0x78},// 6d m 
  {0x7C, 0x08, 0x04, 0x04, 0x78},// 6e n 
  {0x38, 0x44, 0x44, 0x44, 0x38},// 6f o 
  {0x7C, 0x14, 0x14, 0x14, 0x08},// 70 p 
  {0x08, 0x14, 0x14, 0x18, 0x7C},// 71 q 
  {0x7C, 0x08, 0x04, 0x04, 0x08},// 72 r 
  {0x08, 0x54, 0x54, 0x54, 0x20},// 73 s 
  {0x04, 0x3F, 0x44, 0x40, 0x20},// 74 t 
  {0x3C, 0x40, 0x40, 0x20, 0x7C},// 75 u 
  {0x1C, 0x20, 0x40, 0x20, 0x1C},// 76 v 
  {0x3C, 0x40, 0x30, 0x40, 0x3C},// 77 w 
  {0x44, 0x28, 0x10, 0x28, 0x44},// 78 x 
  {0x0C, 0x50, 0x50, 0x50, 0x3C},// 79 y 
  {0x44, 0x64, 0x54, 0x4C, 0x44},// 7a z 
  {0x00, 0x08, 0x36, 0x41, 0x00},// 7b < 
  {0x00, 0x00, 0x7F, 0x00, 0x00},// 7c | 
  {0x00, 0x41, 0x36, 0x08, 0x00},// 7d > 
  {0x10, 0x08, 0x08, 0x10, 0x08},// 7e Right Arrow -> 
  {0x78, 0x46, 0x41, 0x46, 0x78},// 7f Left Arrow <- 
  {0x00, 0x00, 0x00, 0x00, 0x00},// 80
  {0x00, 0x00, 0x5F, 0x00, 0x00},// 81
  {0x00, 0x07, 0x00, 0x07, 0x00},// 82
  {0x14, 0x7F, 0x14, 0x7F, 0x14},// 83
  {0x24, 0x2A, 0x7F, 0x2A, 0x12},// 84
  {0x23, 0x13, 0x08, 0x64, 0x62},// 85
  {0x36, 0x49, 0x55, 0x22, 0x50},// 86
  {0x00, 0x05, 0x03, 0x00, 0x00},// 87
  {0x00, 0x1C, 0x22, 0x41, 0x00},// 88
  {0x00, 0x41, 0x22, 0x1C, 0x00},// 89
  {0x14, 0x08, 0x3E, 0x08, 0x14},// 8A
  {0x08, 0x08, 0x3E, 0x08, 0x08},// 8B
  {0x00, 0x50, 0x30, 0x00, 0x00},// 8C
  {0x08, 0x08, 0x08, 0x08, 0x08},// 8D
  {0x00, 0x60, 0x60, 0x00, 0x00},// 8E
  {0x20, 0x10, 0x08, 0x04, 0x02},// 8F
  {0x00, 0x00, 0x00, 0x00, 0x00},// 90
  {0x00, 0x00, 0x5F, 0x00, 0x00},// 91
  {0x00, 0x07, 0x00, 0x07, 0x00},// 92
  {0x14, 0x7F, 0x14, 0x7F, 0x14},// 93
  {0x24, 0x2A, 0x7F, 0x2A, 0x12},// 94
  {0x23, 0x13, 0x08, 0x64, 0x62},// 95
  {0x36, 0x49, 0x55, 0x22, 0x50},// 96
  {0x00, 0x05, 0x03, 0x00, 0x00},// 97
  {0x00, 0x1C, 0x22, 0x41, 0x00},// 98 
  {0x00, 0x41, 0x22, 0x1C, 0x00},// 99
  {0x14, 0x08, 0x3E, 0x08, 0x14},// 9A
  {0x08, 0x08, 0x3E, 0x08, 0x08},// 9B
  {0x00, 0x50, 0x30, 0x00, 0x00},// 9C
  {0x08, 0x08, 0x08, 0x08, 0x08},// 9D
  {0x00, 0x60, 0x60, 0x00, 0x00},// 9E
  {0x20, 0x10, 0x08, 0x04, 0x02},// 9F
  {0x00, 0x00, 0x00, 0x00, 0x00},// A0
  {0x00, 0x00, 0x5F, 0x00, 0x00},// A1
  {0x00, 0x07, 0x00, 0x07, 0x00},// A2
  {0x14, 0x7F, 0x14, 0x7F, 0x14},// A3
  {0x24, 0x2A, 0x7F, 0x2A, 0x12},// A4
  {0x23, 0x13, 0x08, 0x64, 0x62},// A5
  {0x36, 0x49, 0x55, 0x22, 0x50},// A6
  {0x00, 0x05, 0x03, 0x00, 0x00},// A7
  {0x00, 0x1C, 0x22, 0x41, 0x00},// A8
  {0x00, 0x41, 0x22, 0x1C, 0x00},// A9
  {0x14, 0x08, 0x3E, 0x08, 0x14},// AA
  {0x08, 0x08, 0x3E, 0x08, 0x08},// AB
  {0x00, 0x50, 0x30, 0x00, 0x00},// AC
  {0x08, 0x08, 0x08, 0x08, 0x08},// AD
  {0x00, 0x60, 0x60, 0x00, 0x00},// AE
  {0x20, 0x10, 0x08, 0x04, 0x02},// AF
  //{0x3E, 0x51, 0x49, 0x45, 0x3E},// B0
  {0x00, 0x06, 0x09, 0x09, 0x06},
  {0x00, 0x42, 0x7F, 0x40, 0x00},// B1
  {0x42, 0x61, 0x51, 0x49, 0x46},// B2
  {0x21, 0x41, 0x45, 0x4B, 0x31},// B3
  {0x18, 0x14, 0x12, 0x7F, 0x10},// B4
  {0x27, 0x45, 0x45, 0x45, 0x39},// B5
  {0x3C, 0x4A, 0x49, 0x49, 0x30},// B6
  {0x01, 0x71, 0x09, 0x05, 0x03},// B7
  {0x36, 0x49, 0x49, 0x49, 0x36},// B8
  {0x06, 0x49, 0x49, 0x29, 0x1E},// B9
  {0x00, 0x36, 0x36, 0x00, 0x00},// BA
  {0x00, 0x56, 0x36, 0x00, 0x00},// BB
  {0x08, 0x14, 0x22, 0x41, 0x00},// BC
  {0x14, 0x14, 0x14, 0x14, 0x14},// BD
  {0x00, 0x41, 0x22, 0x14, 0x08},// BE
  {0x02, 0x01, 0x51, 0x09, 0x06},// BF
  {0x7E, 0x11, 0x11, 0x11, 0x7E},// C0 А
  {0x7F, 0x49, 0x49, 0x49, 0x31},// C1 Б
  {0x7F, 0x49, 0x49, 0x49, 0x36},// C2 В
  {0x7F, 0x01, 0x01, 0x01, 0x03},// C3 Г
  {0x60, 0x3E, 0x21, 0x21, 0x7F},// C4 Д
  {0x7F, 0x49, 0x49, 0x49, 0x41},// C5 Е
  {0x77, 0x08, 0x7F, 0x08, 0x77},// C6 Ж
  {0x22, 0x41, 0x49, 0x49, 0x36},// C7 З
  {0x7F, 0x10, 0x08, 0x04, 0x7F},// C8 И
  {0x7F, 0x10, 0x09, 0x04, 0x7F},// C9 И
  {0x7F, 0x08, 0x14, 0x22, 0x41},// CA К
  {0x40, 0x3E, 0x01, 0x01, 0x7F},// CB Л
  {0x7F, 0x02, 0x0C, 0x02, 0x7F},// CC М
  {0x7F, 0x08, 0x08, 0x08, 0x7F},// CD Н
  {0x3E, 0x41, 0x41, 0x41, 0x3E},// CE О
  {0x7F, 0x01, 0x01, 0x01, 0x7F},// CF П
  {0x7F, 0x09, 0x09, 0x09, 0x06},// D0 Р
  {0x3E, 0x41, 0x41, 0x41, 0x22},// D1 С
  {0x01, 0x01, 0x7F, 0x01, 0x01},// D2 Т
  {0x27, 0x48, 0x48, 0x48, 0x3F},// D3 У
  {0x1E, 0x21, 0x7F, 0x21, 0x1E},// D4 Ф
  {0x63, 0x14, 0x08, 0x14, 0x63},// D5 Х
  {0x3F, 0x20, 0x20, 0x3F, 0x60},// D6 Ц
  {0x07, 0x08, 0x08, 0x08, 0x7F},// D7 Ч
  {0x7F, 0x40, 0x7F, 0x40, 0x7F},// D8 Ш
  {0x3F, 0x20, 0x3F, 0x20, 0x7F},// D9 Щ
  {0x01, 0x7F, 0x48, 0x48, 0x30},// DA Ъ
  {0x7F, 0x48, 0x30, 0x00, 0x7F},// DB Ы
  {0x00, 0x7F, 0x48, 0x48, 0x30},// DC Ь
  {0x22, 0x41, 0x49, 0x49, 0x3E},// DD Э
  {0x7F, 0x08, 0x3E, 0x41, 0x3E},// DE Ю
  {0x46, 0x29, 0x19, 0x09, 0x7F},// DF Я
  {0x20, 0x54, 0x54, 0x54, 0x78},// E0 а
  {0x3C, 0x4A, 0x4A, 0x4A, 0x30},// E1 б
  {0x7C, 0x54, 0x54, 0x28, 0x00},// E2 в
  {0x7C, 0x04, 0x04, 0x04, 0x04},// E3 г
  {0x60, 0x38, 0x24, 0x24, 0x7C},// E4 д
  {0x38, 0x54, 0x54, 0x54, 0x18},// E5 е
  {0x6C, 0x10, 0x7C, 0x10, 0x6C},// E6 ж
  {0x00, 0x44, 0x54, 0x54, 0x28},// E7 з
  {0x7C, 0x20, 0x10, 0x08, 0x7C},// E8 и
  {0x7C, 0x21, 0x12, 0x09, 0x7C},// E9 й
  {0x7C, 0x10, 0x28, 0x44, 0x00},// EA к
  {0x40, 0x38, 0x04, 0x04, 0x7C},// EB л
  {0x7C, 0x08, 0x10, 0x08, 0x7C},// EC м
  {0x7C, 0x10, 0x10, 0x10, 0x7C},// ED н
  {0x38, 0x44, 0x44, 0x44, 0x38},// EE о
  {0x7C, 0x04, 0x04, 0x04, 0x7C},// EF п
  {0x7C, 0x14, 0x14, 0x14, 0x08},// F0 р
  {0x38, 0x44, 0x44, 0x44, 0x00},// F1 с
  {0x04, 0x04, 0x7C, 0x04, 0x04},// F2 т
  {0x0C, 0x50, 0x50, 0x50, 0x3C},// F3 у
  {0x08, 0x14, 0x7C, 0x14, 0x08},// F4 ф
  {0x44, 0x28, 0x10, 0x28, 0x44},// F5 х
  {0x3C, 0x20, 0x20, 0x3C, 0x60},// F6 ц
  {0x0C, 0x10, 0x10, 0x10, 0x7C},// F7 ч
  {0x7C, 0x40, 0x7C, 0x40, 0x7C},// F8 ш
  {0x3C, 0x20, 0x3C, 0x20, 0x7C},// F9 щ
  {0x04, 0x7C, 0x50, 0x50, 0x20},// FA ъ
  {0x7C, 0x50, 0x20, 0x00, 0x7C},// FB ы
  {0x00, 0x7C, 0x50, 0x50, 0x20},// FC ь
  {0x28, 0x44, 0x54, 0x54, 0x38},// FD э
  {0x7C, 0x10, 0x38, 0x44, 0x38},// FE ю
  {0x48, 0x54, 0x34, 0x14, 0x7C} // FF я
};
*/
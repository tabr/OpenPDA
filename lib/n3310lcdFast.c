// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//!!!!!!!
//http://we.easyelectronics.ru/lcd_gfx/biblioteka-dlya-raboty-s-displeem-nokia-3310.html
/************************************************************************/
/* 1 VDD              NONE                                              */
/* 2 SCLK             LCD_CLK                                           */
/* 3 SDIN             LCD_MOSI                                          */
/* 4 D/C              LCD_DC                                            */
/* 5 SCEN             LCD_SS                                            */
/* 6 GND              NONE                                              */
/* 7 VOUT (CAPCITOR)  NONE                                              */
/* 8 RESET            LCD_RST                                           */
/************************************************************************/

/**********************************************
****************PCD8544 Driver*****************
***********************************************

for original NOKIA 3310 & alternative "chinese" version of display

48x84 dots, 6x14 symbols

**********************************************/

#define LCD_LINE_0      0
#define LCD_LINE_1      1
#define LCD_LINE_2      2
#define LCD_LINE_3      3
#define LCD_LINE_4      4
#define LCD_LINE_5      5
#define LCD_LINE_6      6

//#define china           1		// если определено - работаем по алгоритмам "китайского" дисплея, иначе - оригинального
//#define SOFT_SPI        1	    // если определено - используем программный SPI, иначе - аппаратный

//#define LCD_SPCR_VAL    0x50    // режим
#define LCD_SPCR_VAL    1<<6 | 1<<4    // режим
#define LCD_SPSR_VAL    0x01    // удвоение частоты


//***********************************************************
//Настройки контроллера дисплея и переменные для работы с ним
//***********************************************************

#ifndef ATMEL_STUDIO
#pragma used+
#endif
//bit instuct_set = 0;            //набор инструкций: 0 - стандартный, 1 - расширенный - в текущей версии не используется
//unsigned char set_y;            //адрес по У, 0..5 - в текущей версии не используется
//unsigned char set_x;                     //адрес по Х, 0..83 - в текущей версии не используется


//china vars
#define LCD_X_MIRROR        0   //зеркалирование по X: 0 - выкл., 1 - вкл.
#define LCD_Y_MIRROR        0   //зеркалирование по Y: 0 - выкл., 1 - вкл.
#define LCD_SPI_INVERT      0   //порядок битов в SPI: 0 - MSB first, 1 - LSB first
#define LCD_SHIFT           5   //0..3F - сдвиг экрана вверх, в точках



//all vars
#define LCD_ADDRESSING      0   //направление адресации: 0 - горизонтальная, 1- вертикальная
#define LCD_TEMP_CONTROL    3   //температурный коэффициент, 0..3
#define LCD_BIAS            3   //смещение, 0..7[хз что это...]
#define LCD_VOP             70  //рабочее напрядение LCD, 0..127 (определяет контрастность)
#define LCD_DISP_CONFIG     2   //режим дисплея: 0 - blank, 1 - all on, 2 - normal, 3 - inverse


#define PIXEL_OFF           0        //режимы отображения пикселя - используются в графических функциях
#define PIXEL_ON            1
#define PIXEL_XOR           2

#define LCD_X_RES           84    //разрешение экрана    
#define LCD_Y_RES           48    
#define LCD_CACHSIZE        LCD_X_RES*LCD_Y_RES/8  

#define Cntr_X_RES          102        //разрешение контроллера - предполагаемое - но работает))
#define Cntr_Y_RES          64   
#define Cntr_buf_size       Cntr_X_RES*Cntr_Y_RES/8


#define LCD_CMD         0
#define LCD_DATA        1 

//bit power_down  = 0;            //power-down control: 0 - chip is active, 1 - chip is in PD-mode
//unsigned char LcdCache [LCD_CACHSIZE];    //Cache buffer in SRAM 84*48 bits or 504 bytes
//unsigned char lcd_buf[15];        //текстовый буфер для вывода на LCD
char lcd_buf[15];        //текстовый буфер для вывода на LCD
//unsigned int  LcdCacheIdx;                  //Cache index
//***************************************************
//****************Прототипы функций******************
//***************************************************
void LcdSend (unsigned char data, unsigned char cmd);                //Sends data to display controller
//void LcdUpdate (void);                               //Copies the LCD cache into the device RAM
//void LcdClear (void);                                //Clears the display
void LcdInit ( void );                                //Настройка SPI и дисплея
void LcdContrast (unsigned char contrast);                     //contrast -> Contrast value from 0x00 to 0x7F
void LcdMode (unsigned char mode);                         //режимы дисплея: 0 - blank, 1 - all on, 2 - normal, 3 - inverse
void LcdPwrMode (void);                                //инвертирует состояние вкл/выкл дисплея
//#ifdef ATMEL_STUDIO
//	void LcdImage (unsigned char *imageData PROGMEM);                    //вывод изображения
//	void LcdImage40x40 (unsigned char *imageData PROGMEM);                    //вывод изображения
//#else
//	void LcdImage (flash unsigned char *imageData);                    //вывод изображения
//	void LcdImage40x40 (flash unsigned char *imageData);                    //вывод изображения
//#endif
//void LcdPixel (unsigned char x, unsigned char y, unsigned char mode);         //Displays a pixel at given absolute (x, y) location, mode -> Off, On or Xor
void LcdLine (int x1, int y1, int x2, int y2, unsigned char mode);          //Draws a line between two points on the display
//void LcdCircle(char x, char y, char radius, unsigned char mode);        //рисуем круг с координатами центра и радиусом
//void LcdBatt(int x1, int y1, int x2, int y2, unsigned char persent);        //рисуем батарейку и заполняем ее на %
//void LcdGotoXYFont (unsigned char x, unsigned char y);               //Sets cursor location to xy location. Range: 1,1 .. 14,6
void clean_lcd_buf (void);                            //очистка текстового буфера
//void LcdChr (int ch);                                //Displays a character at current cursor location and increment cursor location
//void LcdString (unsigned char x, unsigned char y);                //Displays a string at current cursor location
void LcdStringUpdate (unsigned char x, unsigned char y);
//void LcdChrBold (int ch);                            //Печатает символ на текущем месте, большой и жирный)
//void LcdStringBold (unsigned char x, unsigned char y);                //Печатает большую и жирную строку
//void LcdChrBig (int ch);                            //Печатает символ на текущем месте, большой
//void LcdStringBig (unsigned char x, unsigned char y);                //Печатает большую строку
//***************************************************
// UPDATE ##1
//void LcdBar(int x1, int y1, int x2, int y2, unsigned char persent);        // рисует прогресс-бар и заполняет его на "процент"
//void LcdBarLine(unsigned char line, unsigned char persent);            // рисуем прошресс-бар в указанной строке
void LcdStringInv (unsigned char x, unsigned char y);                           // печатает строку в инверсном шрифте (удобно для настроек)

//ASCII
#ifdef ATMEL_STUDIO
//const char table[0x0500] PROGMEM =
const char table[] PROGMEM =
#else
//flash char table[0x0500] =
flash char table[][2] =
#endif

//char table[0x0500] =
{
0x00, 0x00, 0x00, 0x00, 0x00,// 00
0x00, 0x00, 0x5F, 0x00, 0x00,// 01
0x00, 0x07, 0x00, 0x07, 0x00,// 02
0x14, 0x7F, 0x14, 0x7F, 0x14,// 03 
0x24, 0x2A, 0x7F, 0x2A, 0x12,// 04
0x23, 0x13, 0x08, 0x64, 0x62,// 05
0x36, 0x49, 0x55, 0x22, 0x50,// 06
0x00, 0x05, 0x03, 0x00, 0x00,// 07
0x00, 0x1C, 0x22, 0x41, 0x00,// 08
0x00, 0x41, 0x22, 0x1C, 0x00,// 09 
0x14, 0x08, 0x3E, 0x08, 0x14,// 0A
0x08, 0x08, 0x3E, 0x08, 0x08,// 0B 
0x00, 0x50, 0x30, 0x00, 0x00,// 0C
0x08, 0x08, 0x08, 0x08, 0x08,// 0D 
0x00, 0x60, 0x60, 0x00, 0x00,// 0E
0x20, 0x10, 0x08, 0x04, 0x02,// 0F 
0x00, 0x00, 0x00, 0x00, 0x00,// 10 
0x00, 0x00, 0x5F, 0x00, 0x00,// 11 
0x00, 0x07, 0x00, 0x07, 0x00,// 12 
0x14, 0x7F, 0x14, 0x7F, 0x14,// 13 
0x24, 0x2A, 0x7F, 0x2A, 0x12,// 14 
0x23, 0x13, 0x08, 0x64, 0x62,// 15 
0x36, 0x49, 0x55, 0x22, 0x50,// 16
0x00, 0x05, 0x03, 0x00, 0x00,// 17 
0x00, 0x1C, 0x22, 0x41, 0x00,// 18 
0x00, 0x41, 0x22, 0x1C, 0x00,// 19 
0x14, 0x08, 0x3E, 0x08, 0x14,// 1A 
0x08, 0x08, 0x3E, 0x08, 0x08,// 1B
0x00, 0x50, 0x30, 0x00, 0x00,// 1C 
0x08, 0x08, 0x08, 0x08, 0x08,// 1D 
0x00, 0x60, 0x60, 0x00, 0x00,// 1E 
0x20, 0x10, 0x08, 0x04, 0x02,// 1F
0x00, 0x00, 0x00, 0x00, 0x00,// 20 space
0x00, 0x00, 0x5F, 0x00, 0x00,// 21 ! 
0x00, 0x07, 0x00, 0x07, 0x00,// 22 " 
0x14, 0x7F, 0x14, 0x7F, 0x14,// 23 # 
0x24, 0x2A, 0x7F, 0x2A, 0x12,// 24 $ 
0x23, 0x13, 0x08, 0x64, 0x62,// 25 % 
0x36, 0x49, 0x55, 0x22, 0x50,// 26 & 
0x00, 0x05, 0x03, 0x00, 0x00,// 27 '
0x00, 0x1C, 0x22, 0x41, 0x00,// 28 ( 
0x00, 0x41, 0x22, 0x1C, 0x00,// 29 )
0x14, 0x08, 0x3E, 0x08, 0x14,// 2a * 
0x08, 0x08, 0x3E, 0x08, 0x08,// 2b + 
0x00, 0x50, 0x30, 0x00, 0x00,// 2c , 
0x08, 0x08, 0x08, 0x08, 0x08,// 2d - 
0x00, 0x60, 0x60, 0x00, 0x00,// 2e . 
0x20, 0x10, 0x08, 0x04, 0x02,// 2f / 
0x3E, 0x51, 0x49, 0x45, 0x3E,// 30 0 
0x00, 0x42, 0x7F, 0x40, 0x00,// 31 1 
0x42, 0x61, 0x51, 0x49, 0x46,// 32 2 
0x21, 0x41, 0x45, 0x4B, 0x31,// 33 3 
0x18, 0x14, 0x12, 0x7F, 0x10,// 34 4
0x27, 0x45, 0x45, 0x45, 0x39,// 35 5 
0x3C, 0x4A, 0x49, 0x49, 0x30,// 36 6 
0x01, 0x71, 0x09, 0x05, 0x03,// 37 7 
0x36, 0x49, 0x49, 0x49, 0x36,// 38 8 
0x06, 0x49, 0x49, 0x29, 0x1E,// 39 9 
0x00, 0x36, 0x36, 0x00, 0x00,// 3a : 
0x00, 0x56, 0x36, 0x00, 0x00,// 3b ; 
0x08, 0x14, 0x22, 0x41, 0x00,// 3c < 
0x14, 0x14, 0x14, 0x14, 0x14,// 3d = 
0x00, 0x41, 0x22, 0x14, 0x08,// 3e > 
0x02, 0x01, 0x51, 0x09, 0x06,// 3f ? 
0x32, 0x49, 0x79, 0x41, 0x3E,// 40 @ 
0x7E, 0x11, 0x11, 0x11, 0x7E,// 41 A 
0x7F, 0x49, 0x49, 0x49, 0x36,// 42 B 
0x3E, 0x41, 0x41, 0x41, 0x22,// 43 C 
0x7F, 0x41, 0x41, 0x22, 0x1C,// 44 D 
0x7F, 0x49, 0x49, 0x49, 0x41,// 45 E 
0x7F, 0x09, 0x09, 0x09, 0x01,// 46 F 
0x3E, 0x41, 0x49, 0x49, 0x7A,// 47 G 
0x7F, 0x08, 0x08, 0x08, 0x7F,// 48 H 
0x00, 0x41, 0x7F, 0x41, 0x00,// 49 I 
0x20, 0x40, 0x41, 0x3F, 0x01,// 4a J 
0x7F, 0x08, 0x14, 0x22, 0x41,// 4b K 
0x7F, 0x40, 0x40, 0x40, 0x40,// 4c L 
0x7F, 0x02, 0x0C, 0x02, 0x7F,// 4d M 
0x7F, 0x04, 0x08, 0x10, 0x7F,// 4e N 
0x3E, 0x41, 0x41, 0x41, 0x3E,// 4f O 
0x7F, 0x09, 0x09, 0x09, 0x06,// 50 P 
0x3E, 0x41, 0x51, 0x21, 0x5E,// 51 Q 
0x7F, 0x09, 0x19, 0x29, 0x46,// 52 R 
0x46, 0x49, 0x49, 0x49, 0x31,// 53 S 
0x01, 0x01, 0x7F, 0x01, 0x01,// 54 T 
0x3F, 0x40, 0x40, 0x40, 0x3F,// 55 U 
0x1F, 0x20, 0x40, 0x20, 0x1F,// 56 V 
0x3F, 0x40, 0x38, 0x40, 0x3F,// 57 W 
0x63, 0x14, 0x08, 0x14, 0x63,// 58 X 
0x07, 0x08, 0x70, 0x08, 0x07,// 59 Y 
0x61, 0x51, 0x49, 0x45, 0x43,// 5a Z 
0x00, 0x7F, 0x41, 0x41, 0x00,// 5b [ 
0x02, 0x04, 0x08, 0x10, 0x20,// 5c Yen Currency Sign 
0x00, 0x41, 0x41, 0x7F, 0x00,// 5d ]
0x04, 0x02, 0x01, 0x02, 0x04,// 5e ^ 
0x40, 0x40, 0x40, 0x40, 0x40,// 5f _ 
0x00, 0x01, 0x02, 0x04, 0x00,// 60 ` 
0x20, 0x54, 0x54, 0x54, 0x78,// 61 a 
0x7F, 0x48, 0x44, 0x44, 0x38,// 62 b 
0x38, 0x44, 0x44, 0x44, 0x20,// 63 c 
0x38, 0x44, 0x44, 0x48, 0x7F,// 64 d 
0x38, 0x54, 0x54, 0x54, 0x18,// 65 e 
0x08, 0x7E, 0x09, 0x01, 0x02,// 66 f 
0x0C, 0x52, 0x52, 0x52, 0x3E,// 67 g 
0x7F, 0x08, 0x04, 0x04, 0x78,// 68 h 
0x00, 0x44, 0x7D, 0x40, 0x00,// 69 i 
0x20, 0x40, 0x44, 0x3D, 0x00,// 6a j 
0x7F, 0x10, 0x28, 0x44, 0x00,// 6b k 
0x00, 0x41, 0x7F, 0x40, 0x00,// 6c l 
0x7C, 0x04, 0x18, 0x04, 0x78,// 6d m 
0x7C, 0x08, 0x04, 0x04, 0x78,// 6e n 
0x38, 0x44, 0x44, 0x44, 0x38,// 6f o 
0x7C, 0x14, 0x14, 0x14, 0x08,// 70 p 
0x08, 0x14, 0x14, 0x18, 0x7C,// 71 q 
0x7C, 0x08, 0x04, 0x04, 0x08,// 72 r 
0x08, 0x54, 0x54, 0x54, 0x20,// 73 s 
0x04, 0x3F, 0x44, 0x40, 0x20,// 74 t 
0x3C, 0x40, 0x40, 0x20, 0x7C,// 75 u 
0x1C, 0x20, 0x40, 0x20, 0x1C,// 76 v 
0x3C, 0x40, 0x30, 0x40, 0x3C,// 77 w 
0x44, 0x28, 0x10, 0x28, 0x44,// 78 x 
0x0C, 0x50, 0x50, 0x50, 0x3C,// 79 y 
0x44, 0x64, 0x54, 0x4C, 0x44,// 7a z 
0x00, 0x08, 0x36, 0x41, 0x00,// 7b < 
0x00, 0x00, 0x7F, 0x00, 0x00,// 7c | 
0x00, 0x41, 0x36, 0x08, 0x00,// 7d > 
0x10, 0x08, 0x08, 0x10, 0x08,// 7e Right Arrow -> 
0x78, 0x46, 0x41, 0x46, 0x78,// 7f Left Arrow <- 
0x00, 0x00, 0x00, 0x00, 0x00,// 80
0x00, 0x00, 0x5F, 0x00, 0x00,// 81
0x00, 0x07, 0x00, 0x07, 0x00,// 82
0x14, 0x7F, 0x14, 0x7F, 0x14,// 83
0x24, 0x2A, 0x7F, 0x2A, 0x12,// 84
0x23, 0x13, 0x08, 0x64, 0x62,// 85
0x36, 0x49, 0x55, 0x22, 0x50,// 86
0x00, 0x05, 0x03, 0x00, 0x00,// 87
0x00, 0x1C, 0x22, 0x41, 0x00,// 88
0x00, 0x41, 0x22, 0x1C, 0x00,// 89
0x14, 0x08, 0x3E, 0x08, 0x14,// 8A
0x08, 0x08, 0x3E, 0x08, 0x08,// 8B
0x00, 0x50, 0x30, 0x00, 0x00,// 8C
0x08, 0x08, 0x08, 0x08, 0x08,// 8D
0x00, 0x60, 0x60, 0x00, 0x00,// 8E
0x20, 0x10, 0x08, 0x04, 0x02,// 8F
0x00, 0x00, 0x00, 0x00, 0x00,// 90
0x00, 0x00, 0x5F, 0x00, 0x00,// 91
0x00, 0x07, 0x00, 0x07, 0x00,// 92
0x14, 0x7F, 0x14, 0x7F, 0x14,// 93
0x24, 0x2A, 0x7F, 0x2A, 0x12,// 94
0x23, 0x13, 0x08, 0x64, 0x62,// 95
0x36, 0x49, 0x55, 0x22, 0x50,// 96
0x00, 0x05, 0x03, 0x00, 0x00,// 97
0x00, 0x1C, 0x22, 0x41, 0x00,// 98 
0x00, 0x41, 0x22, 0x1C, 0x00,// 99
0x14, 0x08, 0x3E, 0x08, 0x14,// 9A
0x08, 0x08, 0x3E, 0x08, 0x08,// 9B
0x00, 0x50, 0x30, 0x00, 0x00,// 9C
0x08, 0x08, 0x08, 0x08, 0x08,// 9D
0x00, 0x60, 0x60, 0x00, 0x00,// 9E
0x20, 0x10, 0x08, 0x04, 0x02,// 9F
0x00, 0x00, 0x00, 0x00, 0x00,// A0
0x00, 0x00, 0x5F, 0x00, 0x00,// A1
0x00, 0x07, 0x00, 0x07, 0x00,// A2
0x14, 0x7F, 0x14, 0x7F, 0x14,// A3
0x24, 0x2A, 0x7F, 0x2A, 0x12,// A4
0x23, 0x13, 0x08, 0x64, 0x62,// A5
0x36, 0x49, 0x55, 0x22, 0x50,// A6
0x00, 0x05, 0x03, 0x00, 0x00,// A7
0x00, 0x1C, 0x22, 0x41, 0x00,// A8
0x00, 0x41, 0x22, 0x1C, 0x00,// A9
0x14, 0x08, 0x3E, 0x08, 0x14,// AA
0x08, 0x08, 0x3E, 0x08, 0x08,// AB
0x00, 0x50, 0x30, 0x00, 0x00,// AC
0x08, 0x08, 0x08, 0x08, 0x08,// AD
0x00, 0x60, 0x60, 0x00, 0x00,// AE
0x20, 0x10, 0x08, 0x04, 0x02,// AF
//0x3E, 0x51, 0x49, 0x45, 0x3E,// B0
0x00, 0x06, 0x09, 0x09, 0x06,
0x00, 0x42, 0x7F, 0x40, 0x00,// B1
0x42, 0x61, 0x51, 0x49, 0x46,// B2
0x21, 0x41, 0x45, 0x4B, 0x31,// B3
0x18, 0x14, 0x12, 0x7F, 0x10,// B4
0x27, 0x45, 0x45, 0x45, 0x39,// B5
0x3C, 0x4A, 0x49, 0x49, 0x30,// B6
0x01, 0x71, 0x09, 0x05, 0x03,// B7
0x36, 0x49, 0x49, 0x49, 0x36,// B8
0x06, 0x49, 0x49, 0x29, 0x1E,// B9
0x00, 0x36, 0x36, 0x00, 0x00,// BA
0x00, 0x56, 0x36, 0x00, 0x00,// BB
0x08, 0x14, 0x22, 0x41, 0x00,// BC
0x14, 0x14, 0x14, 0x14, 0x14,// BD
0x00, 0x41, 0x22, 0x14, 0x08,// BE
0x02, 0x01, 0x51, 0x09, 0x06,// BF
0x7E, 0x11, 0x11, 0x11, 0x7E,// C0 А
0x7F, 0x49, 0x49, 0x49, 0x31,// C1 Б
0x7F, 0x49, 0x49, 0x49, 0x36,// C2 В
0x7F, 0x01, 0x01, 0x01, 0x03,// C3 Г
0x60, 0x3E, 0x21, 0x21, 0x7F,// C4 Д
0x7F, 0x49, 0x49, 0x49, 0x41,// C5 Е
0x77, 0x08, 0x7F, 0x08, 0x77,// C6 Ж
0x22, 0x41, 0x49, 0x49, 0x36,// C7 З
0x7F, 0x10, 0x08, 0x04, 0x7F,// C8 И
0x7F, 0x10, 0x09, 0x04, 0x7F,// C9 И
0x7F, 0x08, 0x14, 0x22, 0x41,// CA К
0x40, 0x3E, 0x01, 0x01, 0x7F,// CB Л
0x7F, 0x02, 0x0C, 0x02, 0x7F,// CC М
0x7F, 0x08, 0x08, 0x08, 0x7F,// CD Н
0x3E, 0x41, 0x41, 0x41, 0x3E,// CE О
0x7F, 0x01, 0x01, 0x01, 0x7F,// CF П
0x7F, 0x09, 0x09, 0x09, 0x06,// D0 Р
0x3E, 0x41, 0x41, 0x41, 0x22,// D1 С
0x01, 0x01, 0x7F, 0x01, 0x01,// D2 Т
0x27, 0x48, 0x48, 0x48, 0x3F,// D3 У
0x1E, 0x21, 0x7F, 0x21, 0x1E,// D4 Ф
0x63, 0x14, 0x08, 0x14, 0x63,// D5 Х
0x3F, 0x20, 0x20, 0x3F, 0x60,// D6 Ц
0x07, 0x08, 0x08, 0x08, 0x7F,// D7 Ч
0x7F, 0x40, 0x7F, 0x40, 0x7F,// D8 Ш
0x3F, 0x20, 0x3F, 0x20, 0x7F,// D9 Щ
0x01, 0x7F, 0x48, 0x48, 0x30,// DA Ъ
0x7F, 0x48, 0x30, 0x00, 0x7F,// DB Ы
0x00, 0x7F, 0x48, 0x48, 0x30,// DC Ь
0x22, 0x41, 0x49, 0x49, 0x3E,// DD Э
0x7F, 0x08, 0x3E, 0x41, 0x3E,// DE Ю
0x46, 0x29, 0x19, 0x09, 0x7F,// DF Я
0x20, 0x54, 0x54, 0x54, 0x78,// E0 а
0x3C, 0x4A, 0x4A, 0x4A, 0x30,// E1 б
0x7C, 0x54, 0x54, 0x28, 0x00,// E2 в
0x7C, 0x04, 0x04, 0x04, 0x04,// E3 г
0x60, 0x38, 0x24, 0x24, 0x7C,// E4 д
0x38, 0x54, 0x54, 0x54, 0x18,// E5 е
0x6C, 0x10, 0x7C, 0x10, 0x6C,// E6 ж
0x00, 0x44, 0x54, 0x54, 0x28,// E7 з
0x7C, 0x20, 0x10, 0x08, 0x7C,// E8 и
0x7C, 0x21, 0x12, 0x09, 0x7C,// E9 й
0x7C, 0x10, 0x28, 0x44, 0x00,// EA к
0x40, 0x38, 0x04, 0x04, 0x7C,// EB л
0x7C, 0x08, 0x10, 0x08, 0x7C,// EC м
0x7C, 0x10, 0x10, 0x10, 0x7C,// ED н
0x38, 0x44, 0x44, 0x44, 0x38,// EE о
0x7C, 0x04, 0x04, 0x04, 0x7C,// EF п
0x7C, 0x14, 0x14, 0x14, 0x08,// F0 р
0x38, 0x44, 0x44, 0x44, 0x00,// F1 с
0x04, 0x04, 0x7C, 0x04, 0x04,// F2 т
0x0C, 0x50, 0x50, 0x50, 0x3C,// F3 у
0x08, 0x14, 0x7C, 0x14, 0x08,// F4 ф
0x44, 0x28, 0x10, 0x28, 0x44,// F5 х
0x3C, 0x20, 0x20, 0x3C, 0x60,// F6 ц
0x0C, 0x10, 0x10, 0x10, 0x7C,// F7 ч
0x7C, 0x40, 0x7C, 0x40, 0x7C,// F8 ш
0x3C, 0x20, 0x3C, 0x20, 0x7C,// F9 щ
0x04, 0x7C, 0x50, 0x50, 0x20,// FA ъ
0x7C, 0x50, 0x20, 0x00, 0x7C,// FB ы
0x00, 0x7C, 0x50, 0x50, 0x20,// FC ь
0x28, 0x44, 0x54, 0x54, 0x38,// FD э
0x7C, 0x10, 0x38, 0x44, 0x38,// FE ю
0x48, 0x54, 0x34, 0x14, 0x7C // FF я
};

void LcdSend (unsigned char data, unsigned char cmd)    //Sends data to display controller
        {
//			unsigned char tmp=0;
        #ifdef SOFT_SPI
        unsigned char i, mask = 128;
        #endif
//		unsigned char result;
        
//        LCD_CPORT.LCD_CPIN = 0;                //Enable display controller (active low)
        cbi(LCD_SS_PORT,LCD_SS_PIN);                //Enable display controller (active low)
        if (cmd)
			{
//            LCD_DC_PORT.LCD_DC_PIN = 1;    //выбираем команда или данные
            sbi(LCD_DC_PORT,LCD_DC_PIN);    //выбираем команда или данные
			}
        else
			{
//            LCD_DC_PORT.LCD_DC_PIN = 0;
            cbi(LCD_DC_PORT,LCD_DC_PIN);
			}
        #ifdef SOFT_SPI
        for (i=0;i<8;i++)
            {
            if ((data&mask)!=0)
				{
//                LCD_MOSI_PORT.LCD_MOSI_PIN = 1; 
                sbi(LCD_MOSI_PORT,LCD_MOSI_PIN); 
				}
            else
				{
//                LCD_MOSI_PORT.LCD_MOSI_PIN = 0;
                cbi(LCD_MOSI_PORT,LCD_MOSI_PIN); 
				}
//            mask = mask/2;// >>1 ???
            mask = mask>>1;// >>1 ???
//            LCD_CLK_PORT.LCD_CLK_PIN = 1;
            sbi(LCD_CLK_PORT,LCD_CLK_PIN);
//            LCD_CLK_PORT1.LCD_CLK_PIN1 = 1;
            delay_us(1);
//            LCD_CLK_PORT.LCD_CLK_PIN = 0;
            cbi(LCD_CLK_PORT,LCD_CLK_PIN);
//            LCD_CLK_PORT1.LCD_CLK_PIN1 = 0;
            } 
        #endif

        #ifndef SOFT_SPI
#ifdef ATMEL_STUDIO
        LCD_SPI.DATA	= data;
		while (!(LCD_SPI.STATUS & SPI_IF_bm))
			{
			}        //Wait Interrupt
#else
        SPDR = data;                            //Send data to display controller
        while ( (SPSR & 0x80) != 0x80 );        //Wait until Tx register empty
#endif
        #endif
        
//        LCD_CPORT.LCD_CPIN = 1;                //Disable display controller
//        sbi(LCD_SS_PORT,LCD_SS_PIN);                //Disable display controller
        }

void LcdStartDMAUpdate (void)
	{
	LcdSend(0x80, LCD_CMD);        //команды установки указателя памяти дисплея на 0,0
	LcdSend(0x40, LCD_CMD);
	cbi(LCD_DC_PORT,LCD_DC_PIN);// выбираем данные
	//TODO...
	}
/*
void LcdUpdate (void)   //Copies the LCD cache into the device RAM
        {
        int i;
//		unsigned char i;
//		byte tmp;
		unsigned char *ptr=&LcdCache[0];
    #ifdef china
    char j;
    #endif

        LcdSend(0x80, LCD_CMD);        //команды установки указателя памяти дисплея на 0,0
        LcdSend(0x40, LCD_CMD);
        
        #ifdef china                            //если китайский дисплей - грузим пустую строку
        for (j = Cntr_X_RES; j>0; j--) LcdSend(0, LCD_DATA);
		#endif
        
		for (i = 0; i < LCD_CACHSIZE; i++)        //грузим данные
//		for (i = 0; i < LCD_CACHSIZE/2; i++)        //грузим данные
//			while(1)
			{
//			tmp=*ptr++;
//			if (tmp)
			//LcdSend(LcdCache[i], LCD_DATA);
			LcdSend(*ptr++, LCD_DATA);
//			ptr++;
//			LcdSend(*ptr++, LCD_DATA);
//			ptr++;
			//LcdSend(LcdCache[i][0], LCD_DATA);
//			LcdSend(LcdCache[i][1], LCD_DATA);

        #ifdef china                //если дисплей китайский - догружаем каждую строку до размера его буфера
        if (++j == LCD_X_RES) 
            {
            for (j = (Cntr_X_RES-LCD_X_RES); j>0; j--) LcdSend(0, LCD_DATA);
            j=0;
            }
        #endif 
//			++ptr;
//			if (*ptr == 255)
//				break;
			}
        }
        
void LcdClear (void)    //Clears the display
        {
        int i;
		unsigned char *ptr=&LcdCache[0];
//    memset( LcdCache, 0x00, LCD_CACHSIZE );    
//    for (i = 0; i < LCD_CACHSIZE; i++) LcdCache[i] = 0;    //забиваем всю память 0
    for (i = 0; i < LCD_CACHSIZE; i++) *ptr++ = 0;    //забиваем всю память 0
//    i=LCD_CACHSIZE;
//    while (i-- > 0)
//        LcdCache[i] = 0;
		LcdUpdate ();
        }
*/
void LcdClearUpdate (void)    //Clears the display
	{
	int i;
	LcdSend(0x80, LCD_CMD);        //команды установки указателя памяти дисплея на 0,0
	LcdSend(0x40, LCD_CMD);
	for (i = 0; i < LCD_CACHSIZE; i++)
		{
		LcdSend(0x00,LCD_DATA);    //забиваем всю память 0
		}
	}

void LcdInit ( void )    //инициализация SPI и дисплея
        {
		//LcdCache [LCD_CACHSIZE]=255;
//        LCD_RST_PORT.LCD_RST_PIN = 1;       //настроили порты ввода/вывода
//		sbi(LCD_RST_PORT,LCD_RST_PIN);       //настроили порты ввода/вывода
//        LCD_RST_DDR.LCD_RST_PIN = LCD_DC_DDR.LCD_DC_PIN = LCD_CDDR.LCD_CPIN = LCD_MOSI_DDR.LCD_MOSI_PIN = LCD_CLK_DDR.LCD_CLK_PIN = 1;
		sbi(LCD_RST_DDR, LCD_RST_PIN);
		sbi(LCD_DC_DDR, LCD_DC_PIN);
		sbi(LCD_SS_DDR, LCD_SS_PIN);
		sbi(LCD_MOSI_DDR, LCD_MOSI_PIN);
		sbi(LCD_CLK_DDR, LCD_CLK_PIN);
//        LCD_RST_DDR.LCD_RST_PIN = LCD_DC_DDR.LCD_DC_PIN = LCD_CDDR.LCD_CPIN = LCD_MOSI_DDR.LCD_MOSI_PIN = LCD_CLK_DDR.LCD_CLK_PIN = LCD_CLK_DDR1.LCD_CLK_PIN1 = 1;
//        LCD_CLK_PORT.LCD_CLK_PIN = 0;
        cbi(LCD_CLK_PORT, LCD_CLK_PIN);
//        LCD_CLK_PORT1.LCD_CLK_PIN1 = 0;
//            #ifndef SOFT_SPI
//        LCD_SS_DDR.LCD_SS_PIN = 1;
//        LCD_SS_PORT.LCD_SS_PIN = 0;
//            #endif
        delay_ms(1);
            #ifndef SOFT_SPI
#ifdef ATMEL_STUDIO
//	LCD_SPI.CTRL	= 1<<7 | 1<<6 | 0<<5 | 1<<4 | (0<<3 | 0<<2) | (0<<1 | 0<<0);
//					  [double CLK]	[enable][DORD] [master][transfer mode][clk prescaller]
	LCD_SPI.CTRL	= 1<<7			| 1<<6	| 0<<5 | 1<<4 | (0<<3 | 0<<2) | (0<<1 | 0<<0);
//	LCD_SPI.CTRL	= 0<<7			| 1<<6	| 0<<5 | 1<<4 | (0<<3 | 0<<2) | (1<<1 | 1<<0);
	LCD_SPI.INTCTRL = SPI_INTLVL_OFF_gc ; // no interrupt
#else
        SPCR = LCD_SPCR_VAL;
        SPSR = LCD_SPSR_VAL;
#endif
            #endif
//        LCD_RST_PORT.LCD_RST_PIN = 0;       //дернули ресет
        cbi(LCD_RST_PORT,LCD_RST_PIN);       //дернули ресет
        delay_ms(20);
//        LCD_RST_PORT.LCD_RST_PIN = 1;
        sbi(LCD_RST_PORT, LCD_RST_PIN);
                            //Enable SPI port: No interrupt, MSBit first, Master mode, CPOL->0, CPHA->0, Clk/4

//        LCD_CPORT.LCD_CPIN = 1;        //Disable LCD controller
        sbi(LCD_SS_PORT, LCD_SS_PIN);        //Disable LCD controller

        LcdSend( 0b00100001, LCD_CMD );                         //LCD Extended Commands
        LcdSend( 0b00000100+LCD_TEMP_CONTROL, LCD_CMD );                     //Set Temp coefficent
            #ifdef china
        LcdSend( 0b00001000|LCD_SPI_INVERT<<3, LCD_CMD );                     //порядок битов в SPI
        #endif
        LcdSend( 0b00010000+LCD_BIAS, LCD_CMD );                         //LCD bias mode 1:48
            #ifdef china
        LcdSend( 0b01000000+LCD_SHIFT, LCD_CMD );                         //первая строка выше экрана, отображаем со второй
        #endif
    LcdSend( 0b10000000+LCD_VOP, LCD_CMD );                         //Set LCD Vop (Contrast)
    
        #ifdef china
//    LcdSend( 0x20|LCD_X_MIRROR<<4|LCD_Y_MIRROR<<3|power_down<<2, LCD_CMD );            //LCD Standard Commands
    LcdSend( 0x20|LCD_X_MIRROR<<4|LCD_Y_MIRROR<<3|0<<2, LCD_CMD );            //LCD Standard Commands
            #endif
//        LcdSend( 0x20|power_down<<2|LCD_ADDRESSING<<1, LCD_CMD );                //LCD Standard Commands
        LcdSend( 0x20|0<<2|LCD_ADDRESSING<<1, LCD_CMD );                //LCD Standard Commands
        LcdSend( 0b00001000|((LCD_DISP_CONFIG<<1|LCD_DISP_CONFIG)&0b00000101), LCD_CMD );     //LCD mode
//        LcdClear();
        LcdClearUpdate();
        }

/*
void LcdInit ( void )    //инициализация SPI и дисплея
        {
//        LCD_PORT.LCD_RST_PIN = 1;       //настроили порты ввода/вывода
        LCD_RST_PORT.LCD_RST_PIN = 1;       //настроили порты ввода/вывода
//        LCD_DDR.LCD_RST_PIN = LCD_DDR.LCD_DC_PIN = LCD_DDR.LCD_CE_PIN = LCD_DDR.SPI_MOSI_PIN = LCD_DDR.SPI_CLK_PIN = 1;
        LCD_RST_DDR.LCD_RST_PIN = LCD_DC_DDR.LCD_DC_PIN = LCD_CDDR.LCD_CPIN = LCD_MOSI_DDR.LCD_MOSI_PIN = LCD_CLK_DDR.LCD_CLK_PIN = 1;
        LCD_CLK_PORT.LCD_CLK_PIN = 0;
//        delay_ms(1);
//НОВОЕ!!!
            #ifndef SOFT_SPI
        LCD_SS_DDR.LCD_SS_PIN = 1;
        LCD_SS_PORT.LCD_SS_PIN = 0;
            #endif
        delay_ms(1);
            #ifndef SOFT_SPI
        SPCR = SPCR_val;
        SPSR = SPSR_val;
            #endif
//        SPCR = 0x50;
//        LCD_PORT.LCD_RST_PIN = 0;       //дернули ресет
        LCD_RST_PORT.LCD_RST_PIN = 0;       //дернули ресет
//        delay_ms(10);
        delay_ms(20);
//        LCD_PORT.LCD_RST_PIN = 1;
        LCD_RST_PORT.LCD_RST_PIN = 1;
                            //Enable SPI port: No interrupt, MSBit first, Master mode, CPOL->0, CPHA->0, Clk/4

//        LCD_PORT.LCD_CE_PIN = 1;        //Disable LCD controller
        LCD_CPORT.LCD_CPIN = 1;        //Disable LCD controller

        LcdSend( 0b00100001, LCD_CMD );                         //LCD Extended Commands
//было закоменчено!
////        LcdSend( 0b00000100+temp_control, LCD_CMD );                     //Set Temp coefficent
        LcdSend( 0b00000100+temp_control, LCD_CMD );                     //Set Temp coefficent
            #ifdef china
        LcdSend( 0b00001000|SPI_invert<<3, LCD_CMD );                     //порядок битов в SPI
        #endif
        LcdSend( 0b00010000+bias, LCD_CMD );                         //LCD bias mode 1:48
            #ifdef china
        LcdSend( 0b01000000+shift, LCD_CMD );                         //первая строка выше экрана, отображаем со второй
        #endif
    LcdSend( 0b10000000+Vop, LCD_CMD );                         //Set LCD Vop (Contrast)
    
        #ifdef china
//    LcdSend( 0x20|x_mirror<<5|y_mirror<<4|power_down<<3, LCD_CMD );            //LCD Standard Commands
    LcdSend( 0x20|x_mirror<<4|y_mirror<<3|power_down<<2, LCD_CMD );            //LCD Standard Commands
            #endif
                #ifndef china
//        LcdSend( 0x20|power_down<<3|LCD_ADDRESSING<<2, LCD_CMD );                //LCD Standard Commands
        LcdSend( 0x20|power_down<<2|LCD_ADDRESSING<<1, LCD_CMD );                //LCD Standard Commands
                #endif
        LcdSend( 0b00001000|((disp_config<<1|disp_config)&0b00000101), LCD_CMD );     //LCD mode
        LcdClear();
        }
*/
void LcdContrast (unsigned char contrast)     //contrast -> Contrast value from 0x00 to 0x7F
        {
        if (contrast > 0x7F) return;
        LcdSend( 0x21, LCD_CMD );               //LCD Extended Commands
        LcdSend( 0x80 | contrast, LCD_CMD );    //Set LCD Vop (Contrast)
        LcdSend( 0x20, LCD_CMD );               //LCD Standard Commands,Horizontal LCD_ADDRESSING mode
        }
        
void LcdMode (unsigned char mode)         //режим дисплея: 0 - blank, 1 - all on, 2 - normal, 3 - inverse
        {
        if (mode > 3) return;
        LcdSend( 0b00001000|((mode<<1|mode)&0b00000101), LCD_CMD );     //LCD mode
        }
/*        
void LcdPwrMode (void)                 //инвертирует состояние вкл/выкл дисплея
        {
        power_down = ~power_down;
            #ifdef china
    LcdSend( 0x20|LCD_X_MIRROR<<4|LCD_Y_MIRROR<<3|power_down<<2|LCD_ADDRESSING<<1, LCD_CMD );            //LCD Standard Commands
    //#elif
            #endif
            #ifndef china
        LcdSend( 0x20|0<<2|LCD_ADDRESSING<<1, LCD_CMD );
                #endif
        }
*/        
void Lcd_off (void)                 //выкл дисплея
        {
            #ifdef china
    LcdSend( 0x20|LCD_X_MIRROR<<4|LCD_Y_MIRROR<<3|1<<2|LCD_ADDRESSING<<1, LCD_CMD );            //LCD Standard Commands
            #endif
            #ifndef china
//            #elif
        LcdSend( 0x20|1<<2|LCD_ADDRESSING<<1, LCD_CMD );
                #endif
        }
        
void Lcd_on (void)                 //вкл дисплея
        {
            #ifdef china
    LcdSend( 0x20|LCD_X_MIRROR<<4|LCD_Y_MIRROR<<3|0<<2|LCD_ADDRESSING<<1, LCD_CMD );            //LCD Standard Commands
//            #elif
            #endif
            #ifndef china
        LcdSend( 0x20|0<<2|LCD_ADDRESSING<<1, LCD_CMD );
                #endif
        }
/*
#ifdef ATMEL_STUDIO
//void LcdImage (unsigned char *imageData PROGMEM)                    //вывод изображения
void LcdImage (const unsigned char *imageData PROGMEM)                    //вывод изображения
//void LcdImage (const unsigned char& imageData)                    //вывод изображения
#else
void LcdImage (flash unsigned char *imageData)                    //вывод изображения
#endif
//void LcdImage (flash unsigned char *imageData)    //вывод изображения
        {
        unsigned int i;
        
//        LcdSend(0x80, LCD_CMD);        //ставим указатель на 0,0
//        LcdSend(0x40, LCD_CMD);
			#ifdef ATMEL_STUDIO
//			LcdCache[LcdCacheIdx++] = pgm_read_byte(&table[(ch*5+i)]);    //выделяем байт-столбик из символа и грузим в массив - 5 раз
	        for (i = 0; i < LCD_CACHSIZE; i++) LcdCache[i] = pgm_read_byte(&(imageData[i]));    //грузим данные
//	        for (i = 0; i < LCD_CACHSIZE; i++) LcdCache[i] = pgm_read_byte(imageData++);    //грузим данные
			#else
	        for (i = 0; i < LCD_CACHSIZE; i++) LcdCache[i] = imageData[i];    //грузим данные
			#endif
        }
*/
/*
#ifdef ATMEL_STUDIO
void LcdImage40x40 (unsigned char *imageData PROGMEM)                    //вывод изображения
#else
void LcdImage40x40 (flash unsigned char *imageData)                    //вывод изображения
#endif
//void LcdImage40x40 (flash unsigned char *imageData)    //вывод изображения
        {
        unsigned int i;
        unsigned char j,k=0;

//        LcdSend(0x80, LCD_CMD);        //ставим указатель на 0,0
//        LcdSend(0x40, LCD_CMD);
        
        for (i = 0; i < LCD_CACHSIZE; i++)
            {
            j=i%84;//TODO: генерит большой код, проще уж двойная итерация
            if (j>=40)
                LcdCache[i]=0;
            else
                LcdCache[i] = imageData[k++];    //грузим данные
            }
        }
*/
#ifdef ATMEL_STUDIO
//void LcdImage (unsigned char *imageData PROGMEM)                    //вывод изображения
void LcdImageUpdate (const unsigned char *imageData PROGMEM)                    //вывод изображения
//void LcdImage (const unsigned char& imageData)                    //вывод изображения
#else
void LcdImageUpdate (flash unsigned char *imageData)                    //вывод изображения
#endif
//void LcdImage (flash unsigned char *imageData)    //вывод изображения
	{
	unsigned int i;
	
	LcdSend(0x80, LCD_CMD);        //ставим указатель на 0,0
	LcdSend(0x40, LCD_CMD);
	#ifdef ATMEL_STUDIO
	//			LcdCache[LcdCacheIdx++] = pgm_read_byte(&table[(ch*5+i)]);    //выделяем байт-столбик из символа и грузим в массив - 5 раз
	//	        for (i = 0; i < LCD_CACHSIZE; i++) LcdCache[i] = pgm_read_byte(&(imageData[i]));    //грузим данные
	for (i = 0; i < LCD_CACHSIZE; i++)
		{
//		LcdCache[i] = pgm_read_byte(&(imageData[i]));    //грузим данные
		LcdSend(pgm_read_byte(&(imageData[i])),LCD_DATA);    //грузим данные
		}
	#else
	for (i = 0; i < LCD_CACHSIZE; i++)
		{
		//LcdCache[i] = imageData[i];    //грузим данные
		LcdSend(imageData[i],LCD_DATA);
		}
	#endif
	}
/*
void LcdPixel (unsigned char x, unsigned char y, unsigned char mode)     //Displays a pixel at given absolute (x, y) location, mode -> Off, On or Xor
        {
        int index;
        unsigned char offset, data;
        
        if ( x > LCD_X_RES ) return;    //если передали в функцию муть - выходим
        if ( y > LCD_Y_RES ) return;
    
        index = (((int)(y)/8)*84)+x;    //считаем номер байта в массиве памяти дисплея
        offset  = y-((y/8)*8);          //считаем номер бита в этом байте

        data = LcdCache[index];         //берем байт по найденному индексу

        if ( mode == PIXEL_OFF ) data &= ( ~( 0x01 << offset ) );    //редактируем бит в этом байте
                else if ( mode == PIXEL_ON ) data |= ( 0x01 << offset );
                        else if ( mode  == PIXEL_XOR ) data ^= ( 0x01 << offset );
        
        LcdCache[index] = data;        //загружаем байт назад
        }

void LcdLine (int x1, int y1, int x2, int y2, unsigned char mode)      //Draws a line between two points on the display - по Брезенхейму
        {
        signed int dy = 0;
        signed int dx = 0;
        signed int stepx = 0;
        signed int stepy = 0;
        signed int fraction = 0;
        
        if (x1>LCD_X_RES || x2>LCD_X_RES || y1>LCD_Y_RES || y2>LCD_Y_RES) return;
        
        dy = y2 - y1;
        dx = x2 - x1;
        if (dy < 0) 
                {
                dy = -dy;
                stepy = -1;
                }
                else stepy = 1;
        if (dx < 0)
                {
                dx = -dx;
                stepx = -1;
                }
                else stepx = 1;
        dy <<= 1;
        dx <<= 1;
        LcdPixel(x1,y1,mode);
        if (dx > dy)
                {
                fraction = dy - (dx >> 1); 
                while (x1 != x2)
                        {
                        if (fraction >= 0)
                                {
                                y1 += stepy;
                                fraction -= dx;
                                }
                        x1 += stepx;
                        fraction += dy;  
                        LcdPixel(x1,y1,mode);
                        }
                }
                else
                        {
                        fraction = dx - (dy >> 1);
                        while (y1 != y2)
                                {
                                if (fraction >= 0)
                                        {
                                        x1 += stepx;
                                        fraction -= dy;
                                        }
                                y1 += stepy;
                                fraction += dx;
                                LcdPixel(x1,y1,mode);
                                }
                        }
        }

void LcdCircle(char x, char y, char radius, unsigned char mode)        //рисуем круг по координатам с радиусом - по Брезенхейму
        {
        signed char xc = 0;
        signed char yc = 0;
        signed char p = 0;
        
        if (x>LCD_X_RES || y>LCD_Y_RES) return;
        
        yc=radius;
        p = 3 - (radius<<1);
        while (xc <= yc)  
                {
                LcdPixel(x + xc, y + yc, mode);
                LcdPixel(x + xc, y - yc, mode);
                LcdPixel(x - xc, y + yc, mode);
                LcdPixel(x - xc, y - yc, mode);
                LcdPixel(x + yc, y + xc, mode);
                LcdPixel(x + yc, y - xc, mode);
                LcdPixel(x - yc, y + xc, mode);
                LcdPixel(x - yc, y - xc, mode);
                if (p < 0) p += (xc++ << 2) + 6;
                        else p += ((xc++ - yc--)<<2) + 10;
                }
        }
*/
/*        
void LcdBatt(int x1, int y1, int x2, int y2, unsigned char persent)    //рисуем батарейку с заполнением в %
        {
        unsigned char horizon_line,horizon_line2,i;
        if(persent>100)return;
        LcdLine(x1,y2,x2,y2,1);  //down
        LcdLine(x2,y1,x2,y2,1);  //right
    LcdLine(x1,y1,x1,y2,1);  //left
    LcdLine(x1,y1,x2,y1,1);  //up
    LcdLine(x1+7,y1-1,x2-7,y1-1,1);
    LcdLine(x1+7,y1-2,x2-7,y1-2,1);
    
        horizon_line=persent*(y2-y1-3)/100;
        for(i=0;i<horizon_line;i++) LcdLine(x1+2,y2-2-i,x2-2,y2-2-i,1);

        horizon_line2=(y2-y1-3);
        for(i=horizon_line2;i>horizon_line;i--) LcdLine(x1+2,y2-2-i,x2-2,y2-2-i,0);
    }

void LcdBar(int x1, int y1, int x2, int y2, unsigned char persent)    //рисуем прогресс-бар
        {
        unsigned char line;
        if(persent>100)return;
        LcdLine(x1+2,y2,x2-2,y2,1);  //down
        LcdLine(x2-2,y1,x2-2,y2,1);  //right
    LcdLine(x1+2,y1,x1+2,y2,1);  //left
    LcdLine(x1+2,y1,x2-2,y1,1);  //up
    
        LcdLine(x2-1,y1+1,x2-1,y2-1,1);  //right
    LcdLine(x1+1,y1+1,x1+1,y2-1,1);  //left
        
        LcdLine(x2,y1+2,x2,y2-2,1);  //right
    LcdLine(x1,y1+2,x1,y2-2,1);  //left
        
        line=persent*(x2-x1-7)/100-1;
        LcdLine(x1+4,y1+2,x2-4,y2-2,0);
        LcdLine(x1+4,y1+2,x1+4+line,y2-2,1);
    }
void LcdBarLine(unsigned char line, unsigned char persent)    //рисуем прошресс-бар
        {
        LcdBar(0, (line-1)*7+1, 83, (line-1)*7+5, persent); 
        }
void LcdGotoXYFont (unsigned char x, unsigned char y)   //Sets cursor location to xy location. Range: 1,1 .. 14,6
        {
        if (x <= 14 && y <= 6) LcdCacheIdx = ( (int)(y) - 1 ) * 84 + ( (int)(x) - 1 ) * 6;
        }
*/

void clean_lcd_buf (void)    //очистка текстового буфера
    {
    unsigned char i;
    
    for (i=0; i<14; i++) lcd_buf[i] = 0;
    } 
/*
void LcdChr (int ch)    //Displays a character at current cursor location and increment cursor location
     {
         unsigned char i;
         
//        for ( i = 0; i < 5; i++ ) LcdCache[LcdCacheIdx++] = table[(ch*5+i)];    //выделяем байт-столбик из символа и грузим в массив - 5 раз
        for ( i = 0; i < 5; i++ )
			{
			//хуй знает, заработает ли на cvavr...
			#ifdef ATMEL_STUDIO
			LcdCache[LcdCacheIdx++] = pgm_read_byte(&table[(ch*5+i)]);    //выделяем байт-столбик из символа и грузим в массив - 5 раз
			#else
            LcdCache[LcdCacheIdx++] = table[(ch*5+i)];    //выделяем байт-столбик из символа и грузим в массив - 5 раз
			#endif
			}
         LcdCache[LcdCacheIdx++] = 0x00;    //добавляем пробел между символами
     }
void LcdChrInv (int ch)    //Displays a character at current cursor location and increment cursor location
     {
         unsigned char i;
         
        for ( i = 0; i < 5; i++ ) LcdCache[LcdCacheIdx++] = ~(table[(ch*5+i)]);    //выделяем байт-столбик из символа и грузим в массив - 5 раз
         LcdCache[LcdCacheIdx++] = 0xFF;    //добавляем пробел между символами
     }
*/
/*
void LcdFlashString (unsigned char x, unsigned char y, flash unsigned char *str)    //Displays a string at current cursor location
    {
    unsigned int i;
    LcdGotoXYFont (x, y);
    for ( i = 0; i < 15-x; i++ )
        if (str[i])
            LcdChr (str[i]);
    }
*/

void LcdEmptyString (unsigned char y)    //Displays a string at current cursor location
    {
    unsigned char i;
    LcdGotoXYFont (1, y);
    for ( i = 0; i < 15; i++ ) LcdChr (0);
    }

void LcdString (unsigned char x, unsigned char y)    //Displays a string at current cursor location
    {
    unsigned char i;
    
    if (x > 14 || y > 6) return;
    LcdGotoXYFont (x, y);
    for ( i = 0; i < 15-x; i++ ) if (lcd_buf[i]) LcdChr (lcd_buf[i]);
    clean_lcd_buf(); 
    }
void LcdStringUpdate (unsigned char x, unsigned char y)    //Displays a string at current cursor location
	{
	unsigned char k,i;
	unsigned int chr;
	const char *ptr;
	
	if (x > 14 || y > 6) return;
	LcdSend(0x80 | x*6, LCD_CMD);        //команды установки указателя памяти дисплея на 0,0
	LcdSend(0x40 | y, LCD_CMD);

	for (i=0;i < 14-x;i++)
		{
		chr	= lcd_buf[i]*5;
		//TODO: добавить *ptr
		ptr	= &table[chr];//можно не оптимизировать - размер кода одинаков =(
		for ( k = 0; k < 5; k++ )
			{
			//LcdSend(pgm_read_byte(&table[((lcd_buf[i]*5)+k)]), LCD_DATA);
			//LcdSend(pgm_read_byte(&table[((chr)+k)]), LCD_DATA);
			LcdSend(pgm_read_byte(ptr++), LCD_DATA);
			}
		LcdSend(0x00,LCD_DATA);
		}
	clean_lcd_buf(); 
	}
/*        
void LcdStringInv (unsigned char x, unsigned char y)    //Displays a string at current cursor location
    {
    unsigned char i;
    
    if (x > 14 || y > 6) return;
    LcdGotoXYFont (x, y);
    for ( i = 0; i < 15-x; i++ ) if (lcd_buf[i]) LcdChrInv (lcd_buf[i]);
    clean_lcd_buf(); 
    }

void LcdChrBold (int ch)    //Displays a bold character at current cursor location and increment cursor location
     {
         unsigned char i;
         unsigned char a = 0, b = 0, c = 0;
         
         for ( i = 0; i < 5; i++ )
                 {
                 c = table[(ch*5+i)];        //выделяем столбец из символа
                 
                 b =  (c & 0x01) * 3;            //"растягиваем" столбец на два байта 
                  b |= (c & 0x02) * 6;
                  b |= (c & 0x04) * 12;
                  b |= (c & 0x08) * 24;
  
                  c >>= 4;
                  a =  (c & 0x01) * 3;
                  a |= (c & 0x02) * 6;
                  a |= (c & 0x04) * 12;
                  a |= (c & 0x08) * 24;
        
                 LcdCache[LcdCacheIdx] = b;    //копируем байты в экранный буфер
                 LcdCache[LcdCacheIdx+1] = b;    //дублируем для получения жирного шрифта
                 LcdCache[LcdCacheIdx+84] = a;
                 LcdCache[LcdCacheIdx+85] = a;
                 LcdCacheIdx = LcdCacheIdx+2;
                 }
         
         LcdCache[LcdCacheIdx++] = 0x00;    //для пробела между символами
         LcdCache[LcdCacheIdx++] = 0x00;
     }

void LcdStringBold (unsigned char x, unsigned char y)    //Displays a string at current cursor location
    {
    unsigned char i;
    
    if (x > 13 || y > 5) return;
    LcdGotoXYFont (x, y);
    for ( i = 0; i < 14-x; i++ ) if (lcd_buf[i]) LcdChrBold (lcd_buf[i]); 
    clean_lcd_buf();
    }
    
void LcdChrBig (int ch)    //Displays a character at current cursor location and increment cursor location
     {
         unsigned char i;
         unsigned char a = 0, b = 0, c = 0;
         
         for ( i = 0; i < 5; i++ )
                 {
                 c = table[(ch*5+i)];        //выделяем столбец из символа
                 
                 b =  (c & 0x01) * 3;            //"растягиваем" столбец на два байта 
                  b |= (c & 0x02) * 6;
                  b |= (c & 0x04) * 12;
                  b |= (c & 0x08) * 24;
  
                  c >>= 4;
                  a =  (c & 0x01) * 3;
                  a |= (c & 0x02) * 6;
                  a |= (c & 0x04) * 12;
                  a |= (c & 0x08) * 24;
                 LcdCache[LcdCacheIdx] = b;
                 LcdCache[LcdCacheIdx+84] = a;
                 LcdCacheIdx = LcdCacheIdx+1;
                 }
         
         LcdCache[LcdCacheIdx++] = 0x00;
         }

void LcdStringBig (unsigned char x, unsigned char y)    //Displays a string at current cursor location
    {
    unsigned char i;
    
    if (x > 14 || y > 5) return;
    LcdGotoXYFont (x, y);
    for ( i = 0; i < 15-x; i++ ) if (lcd_buf[i]) LcdChrBig (lcd_buf[i]); 
    clean_lcd_buf();
    }
*/
#ifndef ATMEL_STUDIO
#pragma used-
#endif
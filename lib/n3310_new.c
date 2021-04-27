// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//https://github.com/gresolio/N3310Lib
/*
 * Имя          :  n3310.c
 *
 * Описание     :  Это драйвер для графического LCD от Nokia 3310, а также его китайских клонов.
 *                 Базируется на коде библиотек написанных Sylvain Bissonnette и Fandi Gunawan:
 *                 http://www.microsyl.com/index.php/2010/03/24/nokia-lcd-library/
 *                 http://fandigunawan.wordpress.com/2008/06/18/lcd-nokia-3310-pcd8544-driver-in-winavravr-gcc/
 *                 Основные отличия между оригиналом и клоном хорошо описаны в статье от Aheir:
 *                 http://radiokot.ru/articles/29/
 *
 * Автор        :  Xander Gresolio <xugres@gmail.com>
 * Веб-страница :  http://we.easyelectronics.ru/profile/XANDER/
 *
 * Лицензия     :  GPL v3.0
 *
 * Компилятор   :  WinAVR, GCC for AVR platform
 *
 * История      :
 * Версия 1.0 (06.08.2011)
 * + Первая версия
 * + Добавлена поддержка китайских клонов LCD Nokia 3310
 * + Полный перевод комментариев к исходному коду драйвера
 * + Таблица символов драйвера дополнена кириллицей (упрощенная Windows-1251)
 * + Добавлена функция рисования окружностей LcdCircle
 * - Исправлены ошибки в проверке корректности координат при вызове функций рисования
 * - Исправлена ошибка в функции LcdSingleBar (неверная отрисовка по y)
 */

//#include <avr/io.h>
//#include <string.h>
//#include <avr/pgmspace.h>
//#include <avr/interrupt.h>
#include "n3310_new.h"

// Прототипы приватных функций драйвера

//static void Delay      ( void );
/*
static void LcdActivate(void)
	{
	//cbi(LCD_SS_PORT1,LCD_SS_PIN1);
	LcdDisplay.ActivateDisplay();
	}
static void LcdDectivate(void)
	{
	//sbi(LCD_SS_PORT1,LCD_SS_PIN1);
	LcdDisplay.DeactivateDisplay();
	}
*/
// Глобальные переменные

// Кэш в ОЗУ 84*48 бит или 504 байта
//static uint8_t  LcdCacheFull[LCD_CACHE_SIZE + 2]={0x80, 0x40};//+update cmd
//uint8_t*  LcdCache	= LcdCacheFull + 2;
//static uint8_t  LcdCache [ LCD_CACHE_SIZE ];
//static uint8_t  LcdCache1 [ LCD_CACHE_SIZE ];

#ifdef USING_WATERMARKS
// Чтобы не обновлять весь дисплей, а лишь ту часть что изменилась,
// будем отмечать две границы кэша где произошли изменения. Затем
// можно копировать эту часть кэша между границами в ОЗУ дисплея.
	static int   LoWaterMark;   // нижняя граница
	static int   HiWaterMark;   // верхняя граница
#endif

//!!!!!!!!!!!!!!!!!!
void LcdEmptyString(LCD_LINE line)
	{
        LcdCacheChanged = true;
	
	// Оптимизация от Jakub Lasinski (March 14 2009)
	memset( (LcdCache+((LCD_X_RES)*(line))), 0x00, LCD_X_RES);
	// Сброс указателей границ в максимальное значение
	//LoWaterMark = LCD_X_RES*(line);//0;
	//HiWaterMark = ((line+1)*LCD_X_RES - 1);//LCD_CACHE_SIZE - 1;
	// Установка флага изменений кэша
	//UpdateLcd = TRUE;
	
	/*
	LcdGotoXYFont(0,line);
	//memset(lcd_buf, 0, 14);
	//sprintf (lcd_buf,"              ");
	for (uint8_t i=0; i<14; i++)
		{
		if( LcdChr( FONT_1X, 0+32 ) == OUT_OF_BORDER)
			return;// OUT_OF_BORDER;
		}
	*/
	}
void LcdStringNoClean (uint8_t x, LCD_LINE y)                //Displays a string at current cursor location
	{
	x--;
	LcdGotoXYFont(x,y);
	LcdStr(FONT_1X,(uint8_t*)Lcd.lcd_buf);
	}
/*void LcdString (uint8_t x, uint8_t y)                //Displays a string at current cursor location
	{
	x--;
	LcdGotoXYFont(x,y);
	LcdStr(FONT_1X,(uint8_t*)lcd_buf);
	memset(lcd_buf, 0, 15);
	}*/
void LcdSymbol (uint8_t x, LCD_LINE y, LCD_SYMBOLS symbol)
	{
        LcdCacheChanged = true;
	x--;
	LcdGotoXYFont(x,y);
	for (uint8_t i = 0; i < 5; i++ )
		{
		// Копируем вид символа из таблицы в кэш
		LcdCache[LcdCacheIdx++] = pgm_read_byte( &(LCD_Symbols[symbol][i]) ) ;//<< 1; //<< 0 отступ сверху
		}
	// Горизонтальный разрыв между символами
	LcdCache[LcdCacheIdx] = 0x00;
	// Если достигли позицию указателя LCD_CACHE_SIZE - 1, переходим в начало
	if(++LcdCacheIdx == LCD_CACHE_SIZE )
		{
		LcdCacheIdx = 0;
		}
	}

/*
void LcdSymbols	(uint8_t dataArray[])
	{
    uint8_t tmpIdx=0;
    while( dataArray[ tmpIdx ] != '\0' && tmpIdx < LCD_CHAR_WIDTH)
		{
        // Выводим символ
		LcdSymbol(dataArray[ tmpIdx ] );
        // Не стоит волноваться если произойдет OUT_OF_BORDER,
        // строка будет печататься дальше из начала дисплея
//        if( response == OUT_OF_BORDER)
//            return OUT_OF_BORDER;
        // Увеличиваем указатель
        tmpIdx++;
	    }
	}
*/

void LcdString (uint8_t x, LCD_LINE y)                //Displays a string at current cursor location
	{
	x--;
	LcdGotoXYFont(x,y);
	LcdStr(FONT_1X,(uint8_t*)Lcd.lcd_buf);
	LcdCleanBuf();
	}
/*void LcdString1 (uint8_t x, LCD_LINE y, const char *buf)
	{
//	LcdString (x, (uint8_t)y, (char*)buf);
	LcdString (x, y, (char*)buf);
	}*/
void LcdCleanBuf(void)
  {
  memset(Lcd.lcd_buf, 0, sizeof(Lcd.lcd_buf));
  }
void LcdString (uint8_t x, LCD_LINE y, char *buf)
	{
//	x--;
	LcdGotoXYFont((x-1), y);
	LcdStr(FONT_1X,(uint8_t*)buf);
	LcdCleanBuf();
	}
/*
void LcdString (uint8_t x, LCD_LINE y, char *buf)
	{
	LcdString (x, (uint8_t)y, buf);
	}
void LcdString (uint8_t x, uint8_t y, char *buf)
	{
	x--;
	LcdGotoXYFont(x,y);
	LcdStr(FONT_1X,(uint8_t*)buf);
	memset(lcd_buf, 0, 15);
	}
*/
void LcdStringUpdate (uint8_t x, LCD_LINE y, const char *dataArray PROGMEM)
	{
	LcdString(x, y, dataArray);
	n3310LcdClass::RequestUpdate();
	}
void LcdStringUpdate (uint8_t x, LCD_LINE y, char *buf)
	{
	LcdString (x, y, buf);
	//LcdUpdate();
	n3310LcdClass::RequestUpdate();
	}
void LcdClear1_to_5(void)
	{
        LcdCacheChanged = true;
	// Оптимизация от Jakub Lasinski (March 14 2009)
	memset( LcdCache, 0x00, (LCD_CACHE_SIZE - LCD_X_RES) ); //-V512
	
	#ifdef USING_WATERMARKS
	// Сброс указателей границ в максимальное значение
		LoWaterMark = 0;
//		HiWaterMark = (LCD_CACHE_SIZE - LCD_X_RES - 1);//LCD_CACHE_SIZE - 1;
		HiWaterMark = (LCD_CACHE_SIZE - 1);//LCD_CACHE_SIZE - 1;
	#endif

	// Установка флага изменений кэша
	//UpdateLcd = TRUE;
	}
/*
void LcdClear2_to_5(void)
	{
	// Оптимизация от Jakub Lasinski (March 14 2009)
	memset( (LcdCache+LCD_X_RES), 0x00, (LCD_CACHE_SIZE - 2*LCD_X_RES) );
	
	#ifdef USING_WATERMARKS
	// Сброс указателей границ в максимальное значение
//		LoWaterMark = LCD_X_RES;//0;
//		HiWaterMark = (LCD_CACHE_SIZE - 2*LCD_X_RES - 1);//LCD_CACHE_SIZE - 1;
		LoWaterMark = 0;
		HiWaterMark = (LCD_CACHE_SIZE - 1);//LCD_CACHE_SIZE - 1;
	#endif

	// Установка флага изменений кэша
	UpdateLcd = TRUE;
	}
*/
void LcdClearCache(void)
	{
        LcdCacheChanged = true;
	//LoWaterMark = 0;
	//HiWaterMark = LCD_CACHE_SIZE - 1;
	//memset(LcdCache, 0, LCD_CACHE_SIZE);
	//LcdClear();
	// Оптимизация от Jakub Lasinski (March 14 2009)
	memset( LcdCache, 0x00, LCD_CACHE_SIZE );
    // Установка флага изменений кэша
    //UpdateLcd = TRUE;
	}
void LcdClearUpdate(void)
	{
	LcdClearCache();
	//LcdUpdate();
	n3310LcdClass::RequestUpdate();
	}


/*
 * Имя                   :  LcdInit
 * Описание              :  Производит инициализацию порта и SPI МК, контроллера LCD
 * Аргумент(ы)           :  Нет
 * Возвращаемое значение :  Нет
 */
/*
void LcdInit ( void )
{
		
		
		sbi(LCD_RST_DDR1, LCD_RST_PIN1);
		//HAL.IO.SetDirOut(LCD_RST_PIN_HAL);
		sbi(LCD_DC_DDR1, LCD_DC_PIN1);
		//HAL.IO.SetDirOut(LCD_DC_PIN_HAL);
		sbi(LCD_SS_DDR1, LCD_SS_PIN1);
		//HAL.IO.SetDirOut(LCD_SS_PIN_HAL);
		sbi(LCD_MOSI_DDR1, LCD_MOSI_PIN1);
		//HAL.IO.SetDirOut(LCD_MOSI_PIN_HAL);
		
		sbi(LCD_CLK_DDR1, LCD_CLK_PIN1);
		cbi(LCD_CLK_PORT1, LCD_CLK_PIN1);
		
    // Pull-up на вывод подключенный к reset дисплея
	//LCD_PORT |= _BV ( LCD_RST_PIN );

    // Устанавливаем нужные биты порта на выход
    //LCD_DDR |= _BV( LCD_RST_PIN ) | _BV( LCD_DC_PIN ) | _BV( LCD_CE_PIN ) | _BV( SPI_MOSI_PIN ) | _BV( SPI_CLK_PIN );

    // Некалиброванная задержка
    Delay();

    // Дергаем reset
    //LCD_PORT &= ~( _BV( LCD_RST_PIN ) );
	cbi(LCD_RST_PORT1, LCD_RST_PIN1);
    Delay();
    //LCD_PORT |= _BV ( LCD_RST_PIN );
	sbi(LCD_RST_PORT1, LCD_RST_PIN1);

    // Активируем SPI:
    // без прерываний, старший бит первый, режим мастера, CPOL->0, CPHA->0, Clk/4
    //SPCR = 0x50;
	
	
	//	LCD_SPI.CTRL	= 1<<7 | 1<<6 | 0<<5 | 1<<4 | (0<<3 | 0<<2) | (0<<1 | 0<<0);
	//					  [double CLK]	[enable][DORD] [master][transfer mode][clk prescaller]
		LCD_SPI.CTRL	= 1<<7			| 1<<6	| 0<<5 | 1<<4 | (0<<3 | 0<<2) | (0<<1 | 0<<0);
	//LCD_SPI.CTRL	= 0<<7			| 1<<6	| 0<<5 | 1<<4 | (0<<3 | 0<<2) | (1<<1 | 1<<0);
	LCD_SPI.INTCTRL = SPI_INTLVL_OFF_gc ; // no interrupt

    // Отключаем LCD контроллер - высокий уровень на SCE
    //LCD_PORT |= _BV( LCD_CE_PIN );
	LcdDectivate();

    // Отправляем команды дисплею
    LcdSend( 0x21, LCD_CMD ); // Включаем расширенный набор команд (LCD Extended Commands)
    LcdSend( 0xC8, LCD_CMD ); // Установка контрастности (LCD Vop)
    LcdSend( 0x06, LCD_CMD ); // Установка температурного коэффициента (Temp coefficent)
    LcdSend( 0x13, LCD_CMD ); // Настройка питания (LCD bias mode 1:48)
    LcdSend( 0x20, LCD_CMD ); // Включаем стандартный набор команд и горизонтальную адресацию (LCD Standard Commands,Horizontal addressing mode)
    LcdSend( 0x0C, LCD_CMD ); // Нормальный режим (LCD in normal mode)

    // Первичная очистка дисплея
    LcdClear();
    LcdUpdate();
}
*/


/*
 * Имя                   :  LcdClear
 * Описание              :  Очищает дисплей. Далее необходимо выполнить LcdUpdate
 * Аргумент(ы)           :  Нет
 * Возвращаемое значение :  Нет
 */
/*
void LcdClear ( void )
{
//    // Очистка кэша дисплея
//    int i;
//    for ( i = 0; i < LCD_CACHE_SIZE; i++ )
//    {
//        LcdCache[i] = 0x00;
//    }

    // Оптимизация от Jakub Lasinski (March 14 2009)
    memset( LcdCache, 0x00, LCD_CACHE_SIZE );
    
	#ifdef USING_WATERMARKS
		// Сброс указателей границ в максимальное значение
		LoWaterMark = 0;
		HiWaterMark = LCD_CACHE_SIZE - 1;
	#endif

    // Установка флага изменений кэша
    UpdateLcd = TRUE;
}
*/


/*
 * Имя                   :  LcdUpdate
 * Описание              :  Копирует кэш в ОЗУ дисплея
 * Аргумент(ы)           :  Нет
 * Возвращаемое значение :  Нет
 */
/*
void void LcdUpdateDoNotUse1 (void)
{
//if ((DMA.STATUS & (DMA_CH0PEND_bm | DMA_CH0BUSY_bm)) != 0)
//	{
//	return;
//	}
//    int i;

	#ifdef USING_WATERMARKS
		if ( LoWaterMark < 0 )
			LoWaterMark = 0;
		else if ( LoWaterMark >= LCD_CACHE_SIZE )
			LoWaterMark = LCD_CACHE_SIZE - 1;

		if ( HiWaterMark < 0 )
			HiWaterMark = 0;
		else if ( HiWaterMark >= LCD_CACHE_SIZE )
			HiWaterMark = LCD_CACHE_SIZE - 1;
	#endif

    #ifdef CHINA_LCD  // Алгоритм для китайского ЖК из нестандартным контроллером

        byte x,y;

        // 102 x 64 - таково предполагаемое разрешение буфера китайского ЖК, при чем
        // память буфера отображается на дисплей со сдвигом вверх на 3 пикселя.
        // Поэтому выводим картинку ниже - начиная с второй строки y+1, а потом
        // сдвинем вверх (опять таки фича китайца, полезная в данном случае)
                
        x = LoWaterMark % LCD_X_RES;      // Устанавливаем начальный адрес x
        n3310LcdClass::LcdSendCommand( 0x80 | x);     // относительно нижней границы LoWaterMark
        
        y = LoWaterMark / LCD_X_RES + 1;  // Устанавливаем начальный адрес y+1
        n3310LcdClass::LcdSendCommand( 0x40 | y);     // относительно нижней границы LoWaterMark

        for ( i = LoWaterMark; i <= HiWaterMark; i++ )
        {
            // передаем данные в буфер дисплея
            LcdSend( LcdCache[i], LCD_DATA );
            
            x++;                 // заодно подсчитываем координату x, чтобы вовремя перейти на новую строку
            if (x >= LCD_X_RES)  // если вышли за предел, то переходим на следующую строку (x=0; y++)
            {
                // проще говоря, чтобы верно заполнить нужную часть нестандартного буфера,
                // придется явно указывать требуемый адрес, иначе все поплывет :)
                x=0;                
                n3310LcdClass::LcdSendCommand( 0x80);
                y++;
                n3310LcdClass::LcdSendCommand( 0x40 | y,);
            }
        }

        n3310LcdClass::LcdSendCommand( 0x21);    // Включаем расширенный набор команд
        n3310LcdClass::LcdSendCommand( 0x45);    // Сдвигаем картинку на 5 пикселей вверх (нестандартная команда китайца, оригинал её игнорирует)
        n3310LcdClass::LcdSendCommand( 0x20);    // Включаем стандартный набор команд и горизонтальную адресацию

    #else  // Алгоритм для оригинального дисплея

			// Устанавливаем начальный адрес в 0
			//n3310LcdClass::LcdSendCommand( 0x80);
			//n3310LcdClass::LcdSendCommand( 0x40);
			//uint8_t commandPacket[]={0x80, 0x40};
			//n3310LcdClass::LcdSendCommandPacket(sizeof(commandPacket), commandPacket);
//			memcpy(LcdCache1, LcdCache, LCD_CACHE_SIZE);
			//#warning "memcpy"
			//DMA.CH0.CTRLA |= DMA_CH_ENABLE_bm;
			//_delay_ms(1);

			n3310LcdClass::LcdSendCachePacket(LCD_CACHE_SIZE , LcdCache);
			//n3310LcdClass::LcdSendCachePacket(LCD_CACHE_SIZE+2 , LcdCacheFull);
			// Обновляем необходимую часть буфера дисплея
			//for (uint16_t i = 0; i < LCD_CACHE_SIZE; i++ )
//		        {
		        // Для оригинального дисплея не нужно следить за адресом в буфере,
	            // можно просто последовательно выводить данные
				//n3310LcdClass::LcdSendData( LcdCache[i]);
			
				//LcdPinDC::SetOutHigh();
				//n3310LcdClass::ActivateDisplay();
				//dma_start(LcdCache);
				//_delay_ms(2);
				//n3310LcdClass::DeactivateDisplay();
//				}

    #endif

    // Сброс флага изменений кэша
//    UpdateLcd = FALSE;
}
*/


/*
 * Имя                   :  LcdSend
 * Описание              :  Отправляет данные в контроллер дисплея
 * Аргумент(ы)           :  data -> данные для отправки
 *                          cd   -> команда или данные (смотри enum в n3310.h)
 * Возвращаемое значение :  Нет
 */
/*
static void LcdSendData ( uint8_t data )
	{
	n3310LcdClass::LcdSendData(data);
	}*/
//static void LcdSend ( uint8_t data, LcdCmdData cd )
//static void LcdSendCommand ( uint8_t command)
//{
//	n3310LcdClass::LcdSendCommand(command);
	/*
    // Включаем контроллер дисплея (низкий уровень активный)
    //LCD_PORT &= ~( _BV( LCD_CE_PIN ) );
	LcdActivate();

    if ( cd == LCD_DATA )
		{
        //LCD_PORT |= _BV( LCD_DC_PIN );
		sbi(LCD_DC_PORT1, LCD_DC_PIN1)
		}
    else
		{
        //LCD_PORT &= ~( _BV( LCD_DC_PIN ) );
		cbi(LCD_DC_PORT1, LCD_DC_PIN1)
		}

	LCD_SPI.DATA	= data;// Отправка данных в контроллер дисплея
	while (!(LCD_SPI.STATUS & SPI_IF_bm));// Ждем окончания передачи
    // Отправка данных в контроллер дисплея
    //SPDR = data;

    // Ждем окончания передачи
    //while ( (SPSR & 0x80) != 0x80 );

    // Отключаем контроллер дисплея
    //LCD_PORT |= _BV( LCD_CE_PIN );
	LcdDectivate();*/
//}



/*
 * Имя                   :  LcdContrast
 * Описание              :  Устанавливает контрастность дисплея
 * Аргумент(ы)           :  контраст -> значение от 0x00 к 0x7F
 * Возвращаемое значение :  Нет
 */
/*
void LcdContrast ( uint8_t contrast )
{
    n3310LcdClass::LcdSendCommand( 0x21);              // Расширенный набор команд
    n3310LcdClass::LcdSendCommand( 0x80 | contrast);   // Установка уровня контрастности
    n3310LcdClass::LcdSendCommand( 0x20);              // Стандартный набор команд, горизонтальная адресация
}

*/

/*
 * Имя                   :  Delay
 * Описание              :  Некалиброванная задержка для процедуры инициализации LCD
 * Аргумент(ы)           :  Нет
 * Возвращаемое значение :  Нет
 */
/*
static void Delay ( void )
{
    int i;

    for ( i = -32000; i < 32000; i++ );
}
*/


/*
 * Имя                   :  LcdGotoXYFont
 * Описание              :  Устанавливает курсор в позицию x,y относительно стандартного размера шрифта
 * Аргумент(ы)           :  x,y -> координаты новой позиции курсора. Значения: 0,0 .. 13,5
 * Возвращаемое значение :  смотри возвращаемое значение в n3310.h
 */
uint8_t LcdGotoXYFont ( uint8_t x, uint8_t y )
{
    // Проверка границ
    if( x > 13 || y > 5 ) return OUT_OF_BORDER;

    //  Вычисление указателя. Определен как адрес в пределах 504 байт
    LcdCacheIdx = x * 6 + y * 84;
    return OK;
}

/*
 * Имя                   :  LcdChr
 * Описание              :  Выводит символ в текущей позиции курсора, затем инкрементирует положение курсора
 * Аргумент(ы)           :  size -> размер шрифта. Смотри enum в n3310.h
 *                          ch   -> символ для вывода
 * Возвращаемое значение :  смотри возвращаемое значение в n3310lcd.h
 */
uint8_t LcdChr ( LcdFontSize size, uint8_t ch )
	{
	uint8_t i, c;
	uint8_t b1, b2;
	int  tmpIdx;

        LcdCacheChanged = true;
	#ifdef USING_WATERMARKS
		if ( LcdCacheIdx < LoWaterMark )
			{
			// Обновляем нижнюю границу
			LoWaterMark = LcdCacheIdx;
			}
	#endif

	if ( (ch >= 0x20) && (ch <= 0x7F) )
		{
		// Смещение в таблице для символов ASCII[0x20-0x7F]
		ch -= 32;
		}
	else if ( ch >= 0xC0 )
		{
		// Смещение в таблице для символов CP1251[0xC0-0xFF]
	    ch -= 96;
		}
	else
		{
		// Остальные игнорируем (их просто нет в таблице для экономии памяти)
		ch = 95;
		}

    if ( size == FONT_1X )
    {
        for ( i = 0; i < 5; i++ )
        {
            // Копируем вид символа из таблицы в кэш
            LcdCache[LcdCacheIdx++] = pgm_read_byte( &(FontLookup[ch][i]) ) << 1;
        }
    }
    else if ( size == FONT_2X )
    {
        tmpIdx = LcdCacheIdx - 84;

		#ifdef USING_WATERMARKS
			if ( tmpIdx < LoWaterMark )
				{
				LoWaterMark = tmpIdx;
				}
		#endif

        if ( tmpIdx < 0 ) return OUT_OF_BORDER;

        for ( i = 0; i < 5; i++ )
        {
            // Копируем вид символа из таблицы у временную переменную
            c = pgm_read_byte(&(FontLookup[ch][i])) << 1;
            // Увеличиваем картинку
            // Первую часть
            b1 =  (c & 0x01) * 3;
            b1 |= (c & 0x02) * 6;
            b1 |= (c & 0x04) * 12;
            b1 |= (c & 0x08) * 24;

            c >>= 4;
            // Вторую часть
            b2 =  (c & 0x01) * 3;
            b2 |= (c & 0x02) * 6;
            b2 |= (c & 0x04) * 12;
            b2 |= (c & 0x08) * 24;

            // Копируем две части в кэш
            LcdCache[tmpIdx++] = b1;
            LcdCache[tmpIdx++] = b1;
            LcdCache[tmpIdx + 82] = b2;
            LcdCache[tmpIdx + 83] = b2;
        }

        // Обновляем x координату курсора
        LcdCacheIdx = (LcdCacheIdx + 11) % LCD_CACHE_SIZE;
    }

	#ifdef USING_WATERMARKS
		if ( LcdCacheIdx > HiWaterMark )
			{
			// Обновляем верхнюю границу
			HiWaterMark = LcdCacheIdx;
			}
	#endif

    // Горизонтальный разрыв между символами
    LcdCache[LcdCacheIdx] = 0x00;
    // Если достигли позицию указателя LCD_CACHE_SIZE - 1, переходим в начало
//    if(LcdCacheIdx == (LCD_CACHE_SIZE - 1) )
    if(++LcdCacheIdx == LCD_CACHE_SIZE )
    {
        LcdCacheIdx = 0;
        return OK_WITH_WRAP;
    }
    // Иначе просто инкрементируем указатель
//    LcdCacheIdx++;
    return OK;
}



/*
 * Имя                   :  LcdStr
 * Описание              :  Эта функция предназначена для печати строки которая хранится в RAM
 * Аргумент(ы)           :  size      -> размер шрифта. Смотри enum в n3310.h
 *                          dataArray -> массив содержащий строку которую нужно напечатать
 * Возвращаемое значение :  смотри возвращаемое значение в n3310lcd.h
 */
uint8_t LcdStr ( LcdFontSize size, uint8_t dataArray[] )
{
    uint8_t tmpIdx=0;
    uint8_t response;
    while( dataArray[ tmpIdx ] != '\0' && tmpIdx < LCD_CHAR_WIDTH)
    {
        // Выводим символ
        response = LcdChr( size, dataArray[ tmpIdx ] );
        // Не стоит волноваться если произойдет OUT_OF_BORDER,
        // строка будет печататься дальше из начала дисплея
        if( response == OUT_OF_BORDER)
            return OUT_OF_BORDER;
        // Увеличиваем указатель
        tmpIdx++;
    }
    return OK;
}

void LcdString (uint8_t x, LCD_LINE y, const char *dataArray PROGMEM)
	{
		//LcdString(1,LCD_LINE_6,(char*)"next>  |  down");
		//LcdFStr(FONT_1X, dataArray);
		//return;
	char readedChar=0;
	LcdGotoXYFont((x-1), y);
	//for (uint8_t k = 0; k < 5; k++)
	uint8_t charIdx=0;
	while(charIdx < LCD_CHAR_WIDTH)
		{
//		readedChar =  pgm_read_byte_near(dataArray + charIdx);
		readedChar =  pgm_read_byte(dataArray + charIdx);
		if (readedChar == '\0')
			{
			break;
			}
		LcdChr( FONT_1X, readedChar);
		charIdx++;
		}
	/*
	uint8_t tmpIdx=0;
	uint8_t response;
	uint8_t *ptr	= (uint8_t*)dataArray;
	LcdGotoXYFont((x-1), y);
	//LcdStr(FONT_1X,(uint8_t*)buf);
	while( dataArray[ tmpIdx ] != '\0' && tmpIdx < LCD_CHAR_WIDTH)
		{
		// Выводим символ
//		response = LcdChr( FONT_1X, pgm_read_byte(dataArray[ tmpIdx ]) );
//		response = LcdChr( FONT_1X, pgm_read_byte(dataArray[ tmpIdx ]) );
		response = LcdChr( FONT_1X, pgm_read_byte(STR_PDAMENU_6ROW_NEXT_DOWN + tmpIdx ));
		// Не стоит волноваться если произойдет OUT_OF_BORDER,
		// строка будет печататься дальше из начала дисплея
		if( response == OUT_OF_BORDER)
			{
			return;
			//return OUT_OF_BORDER;
			}
		// Увеличиваем указатель
		tmpIdx++;
		}
	memset(lcd_buf, 0, 15);
	*/
	}




/*
 * Имя                   :  LcdFStr
 * Описание              :  Эта функция предназначена для печати строки которая хранится в Flash ROM
 * Аргумент(ы)           :  size    -> размер шрифта. Смотри enum в n3310.h
 *                          dataPtr -> указатель на строку которую нужно напечатать
 * Возвращаемое значение :  смотри возвращаемое значение в n3310lcd.h
 * Пример                :  LcdFStr(FONT_1X, PSTR("Hello World"));
 *                          LcdFStr(FONT_1X, &name_of_string_as_array);
 */
uint8_t LcdFStr ( LcdFontSize size, const uint8_t *dataPtr )
{
    uint8_t c;
    uint8_t response;
    for ( c = pgm_read_byte( dataPtr ); c; ++dataPtr, c = pgm_read_byte( dataPtr ) )
    {
        // Выводим символ
        response = LcdChr( size, c );
        if(response == OUT_OF_BORDER)
            return OUT_OF_BORDER;
    }

    return OK;
}



/*
 * Имя                   :  LcdPixel
 * Описание              :  Отображает пиксель по абсолютным координатам (x,y)
 * Аргумент(ы)           :  x,y  -> абсолютные координаты пикселя
 *                          mode -> Off, On или Xor. Смотри enum в n3310.h
 * Возвращаемое значение :  смотри возвращаемое значение в n3310lcd.h
 */
uint8_t LcdPixel ( uint8_t x, uint8_t y, LcdPixelMode mode )
    {
    int  index;
    uint8_t  offset;
    uint8_t  data;

    // Защита от выхода за пределы
    if ( x >= LCD_X_RES || y >= LCD_Y_RES)
      {
      return OUT_OF_BORDER;
      }

    LcdCacheChanged = true;
    // Пересчет индекса и смещения
    index = ( ( y / 8 ) * 84 ) + x;
    offset  = y - ( ( y / 8 ) * 8 );

    data = LcdCache[ index ];

    // Обработка битов

    // Режим PIXEL_OFF
    if ( mode == PIXEL_OFF )
        {
        data &= ( ~( 0x01 << offset ) );
        }
    // Режим PIXEL_ON
    else if ( mode == PIXEL_ON )
        {
        data |= ( 0x01 << offset );
        }
    // Режим PIXEL_XOR
    else if ( mode  == PIXEL_XOR )
        {
        data ^= ( 0x01 << offset );
        }

    // Окончательный результат копируем в кэш
    LcdCache[ index ] = data;

	#ifdef USING_WATERMARKS
		if ( index < LoWaterMark )
			{
			// Обновляем нижнюю границу
			LoWaterMark = index;
			}

		if ( index > HiWaterMark )
			{
			// Обновляем верхнюю границу
			HiWaterMark = index;
			}
	#endif
    return OK;
    }



/*
 * Имя                   :  LcdLine
 * Описание              :  Рисует линию между двумя точками на дисплее (алгоритм Брезенхэма)
 * Аргумент(ы)           :  x1, y1  -> абсолютные координаты начала линии
 *                          x2, y2  -> абсолютные координаты конца линии
 *                          mode    -> Off, On или Xor. Смотри enum в n3310.h
 * Возвращаемое значение :  смотри возвращаемое значение в n3310lcd.h
 */
uint8_t LcdLine ( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, LcdPixelMode mode )
{
    int dx, dy, stepx, stepy, fraction;
    uint8_t response;

    // dy   y2 - y1
    // -- = -------
    // dx   x2 - x1

    dy = y2 - y1;
    dx = x2 - x1;

    // dy отрицательное
    if ( dy < 0 )
    {
        dy    = -dy;
        stepy = -1;
    }
    else
    {
        stepy = 1;
    }

    // dx отрицательное
    if ( dx < 0 )
    {
        dx    = -dx;
        stepx = -1;
    }
    else
    {
        stepx = 1;
    }

    dx <<= 1;
    dy <<= 1;

    // Рисуем начальную точку
    response = LcdPixel( x1, y1, mode );
    if(response)
        return response;

    // Рисуем следующие точки до конца
    if ( dx > dy )
    {
        fraction = dy - ( dx >> 1);
        while ( x1 != x2 )
        {
            if ( fraction >= 0 )
            {
                y1 += stepy;
                fraction -= dx;
            }
            x1 += stepx;
            fraction += dy;

            response = LcdPixel( x1, y1, mode );
            if(response)
                return response;

        }
    }
    else
    {
        fraction = dx - ( dy >> 1);
        while ( y1 != y2 )
        {
            if ( fraction >= 0 )
            {
                x1 += stepx;
                fraction -= dy;
            }
            y1 += stepy;
            fraction += dx;

            response = LcdPixel( x1, y1, mode );
            if(response)
                return response;
        }
    }

    // Установка флага изменений кэша
    //UpdateLcd = TRUE;
    return OK;
}



/*
 * Имя                   :  LcdCircle
 * Описание              :  Рисует окружность (алгоритм Брезенхэма)
 * Аргумент(ы)           :  x, y   -> абсолютные координаты центра
 *                          radius -> радиус окружности
 *                          mode   -> Off, On или Xor. Смотри enum в n3310.h
 * Возвращаемое значение :  смотри возвращаемое значение в n3310lcd.h
 */
uint8_t LcdCircle(uint8_t x, uint8_t y, uint8_t radius, LcdPixelMode mode)
{
    signed char xc = 0;
    signed char yc = 0;
    signed char p = 0;

    if ( x >= LCD_X_RES || y >= LCD_Y_RES) return OUT_OF_BORDER;

    yc = radius;
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

    // Установка флага изменений кэша
    //UpdateLcd = TRUE;
    return OK;
}


/*
 * Имя                   :  LcdSingleBar
 * Описание              :  Рисует один закрашенный прямоугольник
 * Аргумент(ы)           :  baseX  -> абсолютная координата x (нижний левый угол)
 *                          baseY  -> абсолютная координата y (нижний левый угол)
 *                          height -> высота (в пикселях)
 *                          width  -> ширина (в пикселях)
 *                          mode   -> Off, On или Xor. Смотри enum в n3310.h
 * Возвращаемое значение :  смотри возвращаемое значение в n3310lcd.h
 */
uint8_t LcdSingleBar ( uint8_t baseX, uint8_t baseY, uint8_t height, uint8_t width, LcdPixelMode mode )
{
    uint8_t tmpIdxX,tmpIdxY,tmp;

    uint8_t response;

    // Проверка границ
    if ( ( baseX >= LCD_X_RES) || ( baseY >= LCD_Y_RES) ) return OUT_OF_BORDER;

    if ( height > baseY )
        tmp = 0;
    else
        tmp = baseY - height + 1;

    // Рисование линий
    for ( tmpIdxY = tmp; tmpIdxY <= baseY; tmpIdxY++ )
    {
        for ( tmpIdxX = baseX; tmpIdxX < (baseX + width); tmpIdxX++ )
        {
            response = LcdPixel( tmpIdxX, tmpIdxY, mode );
            if(response)
                return response;

        }
    }

    // Установка флага изменений кэша
    //UpdateLcd = TRUE;
    return OK;
}



/*
 * Имя                   :  LcdBars
 * Описание              :  Рисует группу закрашенных прямоугольников (в режиме PIXEL_ON)
 * Аргумент(ы)           :  data[]     -> данные которые нужно отобразить
 *                          numbBars   -> количество прямоугольников
 *                          width      -> ширина (в пикселях)
 *                          multiplier -> множитель для высоты
 * Возвращаемое значение :  смотри возвращаемое значение в n3310lcd.h
 * Примечание            :  Пожалуйста проверьте значения EMPTY_SPACE_BARS, BAR_X, BAR_Y в n3310.h
 * Пример                :  byte example[5] = {1, 2, 3, 4, 5};
 *                          LcdBars(example, 5, 3, 2);
 */
uint8_t LcdBars ( uint8_t data[], uint8_t numbBars, uint8_t width, uint8_t multiplier )
{
    uint8_t b;
    uint8_t tmpIdx = 0;
    uint8_t response;

    for ( b = 0;  b < numbBars ; b++ )
    {
        // Защита от выхода за пределы
        if ( tmpIdx > LCD_X_RES - 1 ) return OUT_OF_BORDER;

        // Расчет значения x
        tmpIdx = ((width + EMPTY_SPACE_BARS) * b) + BAR_X;

        // Рисуем один прямоугольник
        response = LcdSingleBar( tmpIdx, BAR_Y, data[b] * multiplier, width, PIXEL_ON);
        if(response == OUT_OF_BORDER)
            return response;
    }

    // Установка флага изменений кэша
    //UpdateLcd = TRUE;
    return OK;

}



/*
 * Имя                   :  LcdRect
 * Описание              :  Рисует незакрашенный прямоугольник
 * Аргумент(ы)           :  x1    -> абсолютная координата x левого верхнего угла
 *                          y1    -> абсолютная координата y левого верхнего угла
 *                          x2    -> абсолютная координата x правого нижнего угла
 *                          y2    -> абсолютная координата y правого нижнего угла
 *                          mode  -> Off, On или Xor. Смотри enum в n3310.h
 * Возвращаемое значение :  смотри возвращаемое значение в n3310lcd.h
 */
uint8_t LcdRect ( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, LcdPixelMode mode )
{
    uint8_t tmpIdx;

    // Проверка границ
    if ( ( x1 >= LCD_X_RES) ||  ( x2 >= LCD_X_RES) || ( y1 >= LCD_Y_RES) || ( y2 >= LCD_Y_RES) )
        return OUT_OF_BORDER;

    if ( ( x2 > x1 ) && ( y2 > y1 ) )
    {
        // Рисуем горизонтальные линии
        for ( tmpIdx = x1; tmpIdx <= x2; tmpIdx++ )
        {
            LcdPixel( tmpIdx, y1, mode );
            LcdPixel( tmpIdx, y2, mode );
        }

        // Рисуем вертикальные линии
        for ( tmpIdx = y1; tmpIdx <= y2; tmpIdx++ )
        {
            LcdPixel( x1, tmpIdx, mode );
            LcdPixel( x2, tmpIdx, mode );
        }

        // Установка флага изменений кэша
        //UpdateLcd = TRUE;
    }
    return OK;
}



/*
 * Имя                   :  LcdImage
 * Описание              :  Рисует картинку из массива сохраненного в Flash ROM
 * Аргумент(ы)           :  Указатель на массив картинки
 * Возвращаемое значение :  Нет
 */
void LcdImage ( const uint8_t *imageData )
    {
//    // Инициализация указателя кэша
//    LcdCacheIdx = 0;
//    // В пределах кэша
//    for ( LcdCacheIdx = 0; LcdCacheIdx < LCD_CACHE_SIZE; LcdCacheIdx++ )
//    {
//        // Копируем данные из массива в кэш
//        LcdCache[LcdCacheIdx] = pgm_read_byte( imageData++ );
//    }
    
    LcdCacheChanged = true;
    // Оптимизация от Jakub Lasinski (March 14 2009)
    memcpy_P( LcdCache, imageData, LCD_CACHE_SIZE );  // Тоже самое что и выше, но занимает меньше памяти и быстрее выполняется
    
    #ifdef USING_WATERMARKS
		// Сброс указателей границ в максимальное значение
		LoWaterMark = 0;
		HiWaterMark = LCD_CACHE_SIZE - 1;
	#endif

    // Установка флага изменений кэша
    //UpdateLcd = TRUE;
}


/*
void Lcd_dma_init(void){

DMA.CTRL			= DMA_ENABLE_bm;     // Включение DMA
//DMA.CH0.REPCNT		= 1;
//DMA.CH0.CTRLA		= DMA_CH_BURSTLEN0_bm | DMA_CH_REPEAT_bm; // Настройка на повторяющуюся передачу 1 байтными пакетами
DMA.CH0.CTRLA		= DMA_CH_BURSTLEN_1BYTE_gc | DMA_CH_SINGLE_bm; // Настройка на повторяющуюся передачу 1 байтными пакетами
//DMA.CH0.CTRLA		= DMA_CH_SINGLE_bm; // Настройка на повторяющуюся передачу 1 байтными пакетами
//DMA.CH0.CTRLB		= DMA_CH_TRNIF_bm | DMA_CH_TRNINTLVL0_bm;
DMA.CH0.CTRLB		= DMA_CH_TRNINTLVL0_bm;
//DMA.CH0.ADDRCTRL	= DMA_CH_SRCRELOAD_gm |DMA_CH_SRCDIR0_bm | DMA_CH_DESTRELOAD_gm | DMA_CH_DESTDIR0_bm; // Установка инкрементации адресов после каждой передачи и обновление адресов по окончанию передачи
//DMA.CH0.ADDRCTRL	= DMA_CH_SRCRELOAD_BURST_gc | DMA_CH_SRCDIR_INC_gc | DMA_CH_DESTRELOAD_BURST_gc | DMA_CH_DESTDIR_FIXED_gc; // Установка инкрементации адресов после каждой передачи и обновление адресов по окончанию передачи
//DMA.CH0.ADDRCTRL	= DMA_CH_SRCRELOAD_BURST_gc | DMA_CH_SRCDIR_FIXED_gc | DMA_CH_DESTRELOAD_BURST_gc | DMA_CH_DESTDIR_FIXED_gc; // Установка инкрементации адресов после каждой передачи и обновление адресов по окончанию передачи
//DMA.CH0.ADDRCTRL	= DMA_CH_SRCRELOAD_NONE_gc | DMA_CH_SRCDIR_INC_gc | DMA_CH_DESTRELOAD_NONE_gc | DMA_CH_DESTDIR_FIXED_gc; // Установка инкрементации адресов после каждой передачи и обновление адресов по окончанию передачи
DMA.CH0.ADDRCTRL	= DMA_CH_SRCRELOAD_TRANSACTION_gc | DMA_CH_SRCDIR_INC_gc | DMA_CH_DESTRELOAD_NONE_gc | DMA_CH_DESTDIR_FIXED_gc; // Установка инкрементации адресов после каждой передачи и обновление адресов по окончанию передачи
DMA.CH0.TRIGSRC		= DMA_CH_TRIGSRC_USARTE1_DRE_gc;
DMA.CH0.TRFCNT		= LCD_CACHE_SIZE;                  // Установка счетчика передачи на 40 байтов (т.к. int = 2 байтом)
DMA.CH0.REPCNT		= 1;

//DMA.CH0.SRCADDR0 = (uint16_t)&LcdCache;     // Настройка адреса источника на массив massIn
//DMA.CH0.SRCADDR1 = (uint16_t)&LcdCache>>8;
DMA.CH0.SRCADDR0 = (uintptr_t)&LcdCache;     // Настройка адреса источника на массив massIn
DMA.CH0.SRCADDR1 = (uintptr_t)&LcdCache>>8;
DMA.CH0.SRCADDR2 = 0;

//DMA.CH0.DESTADDR0 = (int)&LcdCache1;  // Настройка адреса приемника на массив massOut
//DMA.CH0.DESTADDR1 = (int)&LcdCache1>>8;
//DMA.CH0.DESTADDR2 = 0;

DMA.CH0.DESTADDR0 = (((uintptr_t) &USARTE1.DATA) >>0*8)&0xFF;
DMA.CH0.DESTADDR1 = (((uintptr_t) &USARTE1.DATA) >>1*8)&0xFF;
DMA.CH0.DESTADDR2 = 0;//(((uint16_t) &USARTE1.DATA) >>2*8)&0xFF;


//DMA.CH0.CTRLA |= DMA_CH_ENABLE_bm;   // разрешение работы канала 0 DMA

//DMA.CH0.CTRLA &= ~DMA_CH_ENABLE_bm;

}*/

//void Lcd_dma_start(void){
/*
	//Datenpuffer 256
	DMA.CH0.TRFCNT = LCD_CACHE_SIZE;
	DMA.CH0.REPCNT = 1;

	DMA.CH0.SRCADDR0  =(((uint16_t)(LcdCache))>>0*8) & 0xFF;
	DMA.CH0.SRCADDR1  =(((uint16_t)(LcdCache))>>1*8) & 0xFF;
	DMA.CH0.SRCADDR2  =0;//(((uint16_t)(LcdCache))>>2*8) & 0xFF;
	// DMA CH2 aktivieren (Takt)
	DMA.CH0.CTRLA = DMA_CH_ENABLE_bm | DMA_CH_SINGLE_bm;
*/
/*
DMA.CH0.REPCNT = 0;
DMA.CH0.CTRLA = DMA_CH_SINGLE_bm;
//DMA.CH0.CTRLA = DMA_CH_BURSTLEN_1BYTE_gc | DMA_CH_SINGLE_bm | DMA_CH_REPEAT_bm; // ADC result is 2 byte 12 bit word

DMA.CH0.ADDRCTRL = DMA_CH_SRCRELOAD_NONE_gc | DMA_CH_SRCDIR_FIXED_gc | DMA_CH_DESTRELOAD_TRANSACTION_gc | DMA_CH_DESTDIR_INC_gc;
//DMA.CH0.ADDRCTRL = DMA_CH_SRCRELOAD_BURST_gc | DMA_CH_SRCDIR_INC_gc | // reload source after every burst
//DMA_CH_DESTRELOAD_TRANSACTION_gc | DMA_CH_DESTDIR_INC_gc; // reload dest after every transaction


DMA.CH0.TRIGSRC = DMA_CH_TRIGSRC_USARTE1_DRE_gc;//DMA_CH_TRIGSRC_ADCA_CH0_gc;
DMA.CH0.TRFCNT = LCD_CACHE_SIZE; // always the number of bytes, even if burst length > 1
//DMA.CH0.DESTADDR0 = (( (uint16_t) &USARTE1.DATA) >> 0) & 0xFF;
//DMA.CH0.DESTADDR1 = (( (uint16_t) &USARTE1.DATA) >> 8) & 0xFF;
DMA.CH0.DESTADDR0 = (( (uint16_t) LcdCache1) >> 0) & 0xFF;
DMA.CH0.DESTADDR1 = (( (uint16_t) LcdCache1) >> 8) & 0xFF;
DMA.CH0.DESTADDR2 = 0;
DMA.CH0.SRCADDR0 = (( (uint16_t) LcdCache) >> 0) & 0xFF;
DMA.CH0.SRCADDR1 = (( (uint16_t) LcdCache) >> 8) & 0xFF;
DMA.CH0.SRCADDR2 = 0;

//DMA.CH0.CTRLA |= DMA_CH_ENABLE_bm;
*/
/*
if (DMA.INTFLAGS&0x01)
	{
	DMA.INTFLAGS|=1;
	}
else
	{
	DMA.CH0.CTRLA |= DMA_CH_TRFREQ_bm; // запуск DMA передачи
	}*/
//DMA.CH0.CTRLA |= DMA_CH_TRFREQ_bm; // запуск DMA передачи
//_delay_ms(1);
/*
//_delay_us(1);
if ((DMA.STATUS & (DMA_CH0PEND_bm | DMA_CH0BUSY_bm)) == 0)
	{
	// disable the DMA channel
	DMA.CH0.CTRLA &= ~DMA_CH_ENABLE_bm;
	// reset SRCADDR
	DMA.CH0.SRCADDR0 = (int)&LcdCache;     // Настройка адреса источника на массив massIn
	DMA.CH0.SRCADDR1 = (int)&LcdCache>>8;
	DMA.CH0.SRCADDR2 = 0;
	DMA.CH0.CTRLA |= DMA_CH_ENABLE_bm;
	USARTE1.DATA	= LcdCache[0];
	}
*/
/*
_delay_us(1);
// wait until DMA channel is neither busy nor pending
while (DMA.STATUS & (DMA_CH0PEND_bm | DMA_CH0BUSY_bm));

// disable the DMA channel
DMA.CH0.CTRLA &= ~DMA_CH_ENABLE_bm;

// reset SRCADDR
DMA.CH0.SRCADDR0 = (uint16_t)&LcdCache;     // Настройка адреса источника на массив massIn
DMA.CH0.SRCADDR1 = (uint16_t)&LcdCache>>8;
DMA.CH0.SRCADDR2 = 0;
*/
/*
if ((DMA.STATUS & (DMA_CH0PEND_bm | DMA_CH0BUSY_bm)) == 0)
	{
	//DMA.CH0.CTRLA &= ~DMA_CH_ENABLE_bm;
	//DMA.INTFLAGS=0;
	//DMA.CH0.CTRLA	= DMA_CH_RESET_bm;
	//while (DMA.CH0.CTRLA & DMA_CH_RESET_bm);
	DMA.CH0.CTRLA |= DMA_CH_ENABLE_bm;
	//DMA.CH0.TRIGSRC		= DMA_CH_TRIGSRC_USARTE1_DRE_gc;
	while (DMA.STATUS & (DMA_CH0PEND_bm | DMA_CH0BUSY_bm));
	//DMA.CH0.TRIGSRC		= DMA_CH_TRIGSRC_OFF_gc;
	DMA.CH0.CTRLA &= ~DMA_CH_ENABLE_bm;
	DMA.CH0.SRCADDR0 = (int)&LcdCache;     // Настройка адреса источника на массив massIn
	DMA.CH0.SRCADDR1 = (int)&LcdCache>>8;
	DMA.CH0.SRCADDR2 = 0;
	}
*/
/*
for (uint16_t i=0;i<LCD_CACHE_SIZE;i++)
	{
	USARTE1.DATA	= LcdCache[i];
	while (!(USARTE1.STATUS & USART_TXCIF_bm));
	USARTE1.STATUS |= USART_TXCIF_bm;
	}
*/
//DMA.CH0.CTRLA |= DMA_CH_ENABLE_bm;
//USARTE1.DATA	= LcdCache[0];
//_delay_ms(10);
/*
while (DMA.STATUS & (DMA_CH0PEND_bm | DMA_CH0BUSY_bm));
DMA.CH0.TRIGSRC		= DMA_CH_TRIGSRC_OFF_gc;
DMA.CH0.SRCADDR0 = (int)&LcdCache;     // Настройка адреса источника на массив massIn
DMA.CH0.SRCADDR1 = (int)&LcdCache>>8;
DMA.CH0.SRCADDR2 = 0;*/
//DMA.CH0.CTRLA &= ~DMA_CH_ENABLE_bm;
/*

n3310LcdClass::DeactivateDisplay();
*/
/*
if (DMA.INTFLAGS&0x01)
	{
	DMA.INTFLAGS|=1;
	}
else
	{
	DMA.CH0.CTRLA |= DMA_CH_TRFREQ_bm; // запуск DMA передачи
	USARTE1.DATA	= LcdCache[0];
	}
*/
//}

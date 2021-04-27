// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//https://github.com/gresolio/N3310Lib
/*
 * ���          :  n3310.c
 *
 * ��������     :  ��� ������� ��� ������������ LCD �� Nokia 3310, � ����� ��� ��������� ������.
 *                 ���������� �� ���� ��������� ���������� Sylvain Bissonnette � Fandi Gunawan:
 *                 http://www.microsyl.com/index.php/2010/03/24/nokia-lcd-library/
 *                 http://fandigunawan.wordpress.com/2008/06/18/lcd-nokia-3310-pcd8544-driver-in-winavravr-gcc/
 *                 �������� ������� ����� ���������� � ������ ������ ������� � ������ �� Aheir:
 *                 http://radiokot.ru/articles/29/
 *
 * �����        :  Xander Gresolio <xugres@gmail.com>
 * ���-�������� :  http://we.easyelectronics.ru/profile/XANDER/
 *
 * ��������     :  GPL v3.0
 *
 * ����������   :  WinAVR, GCC for AVR platform
 *
 * �������      :
 * ������ 1.0 (06.08.2011)
 * + ������ ������
 * + ��������� ��������� ��������� ������ LCD Nokia 3310
 * + ������ ������� ������������ � ��������� ���� ��������
 * + ������� �������� �������� ��������� ���������� (���������� Windows-1251)
 * + ��������� ������� ��������� ����������� LcdCircle
 * - ���������� ������ � �������� ������������ ��������� ��� ������ ������� ���������
 * - ���������� ������ � ������� LcdSingleBar (�������� ��������� �� y)
 */

//#include <avr/io.h>
//#include <string.h>
//#include <avr/pgmspace.h>
//#include <avr/interrupt.h>
#include "n3310_new.h"

// ��������� ��������� ������� ��������

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
// ���������� ����������

// ��� � ��� 84*48 ��� ��� 504 �����
//static uint8_t  LcdCacheFull[LCD_CACHE_SIZE + 2]={0x80, 0x40};//+update cmd
//uint8_t*  LcdCache	= LcdCacheFull + 2;
//static uint8_t  LcdCache [ LCD_CACHE_SIZE ];
//static uint8_t  LcdCache1 [ LCD_CACHE_SIZE ];

#ifdef USING_WATERMARKS
// ����� �� ��������� ���� �������, � ���� �� ����� ��� ����������,
// ����� �������� ��� ������� ���� ��� ��������� ���������. �����
// ����� ���������� ��� ����� ���� ����� ��������� � ��� �������.
	static int   LoWaterMark;   // ������ �������
	static int   HiWaterMark;   // ������� �������
#endif

//!!!!!!!!!!!!!!!!!!
void LcdEmptyString(LCD_LINE line)
	{
        LcdCacheChanged = true;
	
	// ����������� �� Jakub Lasinski (March 14 2009)
	memset( (LcdCache+((LCD_X_RES)*(line))), 0x00, LCD_X_RES);
	// ����� ���������� ������ � ������������ ��������
	//LoWaterMark = LCD_X_RES*(line);//0;
	//HiWaterMark = ((line+1)*LCD_X_RES - 1);//LCD_CACHE_SIZE - 1;
	// ��������� ����� ��������� ����
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
		// �������� ��� ������� �� ������� � ���
		LcdCache[LcdCacheIdx++] = pgm_read_byte( &(LCD_Symbols[symbol][i]) ) ;//<< 1; //<< 0 ������ ������
		}
	// �������������� ������ ����� ���������
	LcdCache[LcdCacheIdx] = 0x00;
	// ���� �������� ������� ��������� LCD_CACHE_SIZE - 1, ��������� � ������
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
        // ������� ������
		LcdSymbol(dataArray[ tmpIdx ] );
        // �� ����� ����������� ���� ���������� OUT_OF_BORDER,
        // ������ ����� ���������� ������ �� ������ �������
//        if( response == OUT_OF_BORDER)
//            return OUT_OF_BORDER;
        // ����������� ���������
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
	// ����������� �� Jakub Lasinski (March 14 2009)
	memset( LcdCache, 0x00, (LCD_CACHE_SIZE - LCD_X_RES) ); //-V512
	
	#ifdef USING_WATERMARKS
	// ����� ���������� ������ � ������������ ��������
		LoWaterMark = 0;
//		HiWaterMark = (LCD_CACHE_SIZE - LCD_X_RES - 1);//LCD_CACHE_SIZE - 1;
		HiWaterMark = (LCD_CACHE_SIZE - 1);//LCD_CACHE_SIZE - 1;
	#endif

	// ��������� ����� ��������� ����
	//UpdateLcd = TRUE;
	}
/*
void LcdClear2_to_5(void)
	{
	// ����������� �� Jakub Lasinski (March 14 2009)
	memset( (LcdCache+LCD_X_RES), 0x00, (LCD_CACHE_SIZE - 2*LCD_X_RES) );
	
	#ifdef USING_WATERMARKS
	// ����� ���������� ������ � ������������ ��������
//		LoWaterMark = LCD_X_RES;//0;
//		HiWaterMark = (LCD_CACHE_SIZE - 2*LCD_X_RES - 1);//LCD_CACHE_SIZE - 1;
		LoWaterMark = 0;
		HiWaterMark = (LCD_CACHE_SIZE - 1);//LCD_CACHE_SIZE - 1;
	#endif

	// ��������� ����� ��������� ����
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
	// ����������� �� Jakub Lasinski (March 14 2009)
	memset( LcdCache, 0x00, LCD_CACHE_SIZE );
    // ��������� ����� ��������� ����
    //UpdateLcd = TRUE;
	}
void LcdClearUpdate(void)
	{
	LcdClearCache();
	//LcdUpdate();
	n3310LcdClass::RequestUpdate();
	}


/*
 * ���                   :  LcdInit
 * ��������              :  ���������� ������������� ����� � SPI ��, ����������� LCD
 * ��������(�)           :  ���
 * ������������ �������� :  ���
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
		
    // Pull-up �� ����� ������������ � reset �������
	//LCD_PORT |= _BV ( LCD_RST_PIN );

    // ������������� ������ ���� ����� �� �����
    //LCD_DDR |= _BV( LCD_RST_PIN ) | _BV( LCD_DC_PIN ) | _BV( LCD_CE_PIN ) | _BV( SPI_MOSI_PIN ) | _BV( SPI_CLK_PIN );

    // ��������������� ��������
    Delay();

    // ������� reset
    //LCD_PORT &= ~( _BV( LCD_RST_PIN ) );
	cbi(LCD_RST_PORT1, LCD_RST_PIN1);
    Delay();
    //LCD_PORT |= _BV ( LCD_RST_PIN );
	sbi(LCD_RST_PORT1, LCD_RST_PIN1);

    // ���������� SPI:
    // ��� ����������, ������� ��� ������, ����� �������, CPOL->0, CPHA->0, Clk/4
    //SPCR = 0x50;
	
	
	//	LCD_SPI.CTRL	= 1<<7 | 1<<6 | 0<<5 | 1<<4 | (0<<3 | 0<<2) | (0<<1 | 0<<0);
	//					  [double CLK]	[enable][DORD] [master][transfer mode][clk prescaller]
		LCD_SPI.CTRL	= 1<<7			| 1<<6	| 0<<5 | 1<<4 | (0<<3 | 0<<2) | (0<<1 | 0<<0);
	//LCD_SPI.CTRL	= 0<<7			| 1<<6	| 0<<5 | 1<<4 | (0<<3 | 0<<2) | (1<<1 | 1<<0);
	LCD_SPI.INTCTRL = SPI_INTLVL_OFF_gc ; // no interrupt

    // ��������� LCD ���������� - ������� ������� �� SCE
    //LCD_PORT |= _BV( LCD_CE_PIN );
	LcdDectivate();

    // ���������� ������� �������
    LcdSend( 0x21, LCD_CMD ); // �������� ����������� ����� ������ (LCD Extended Commands)
    LcdSend( 0xC8, LCD_CMD ); // ��������� ������������� (LCD Vop)
    LcdSend( 0x06, LCD_CMD ); // ��������� �������������� ������������ (Temp coefficent)
    LcdSend( 0x13, LCD_CMD ); // ��������� ������� (LCD bias mode 1:48)
    LcdSend( 0x20, LCD_CMD ); // �������� ����������� ����� ������ � �������������� ��������� (LCD Standard Commands,Horizontal addressing mode)
    LcdSend( 0x0C, LCD_CMD ); // ���������� ����� (LCD in normal mode)

    // ��������� ������� �������
    LcdClear();
    LcdUpdate();
}
*/


/*
 * ���                   :  LcdClear
 * ��������              :  ������� �������. ����� ���������� ��������� LcdUpdate
 * ��������(�)           :  ���
 * ������������ �������� :  ���
 */
/*
void LcdClear ( void )
{
//    // ������� ���� �������
//    int i;
//    for ( i = 0; i < LCD_CACHE_SIZE; i++ )
//    {
//        LcdCache[i] = 0x00;
//    }

    // ����������� �� Jakub Lasinski (March 14 2009)
    memset( LcdCache, 0x00, LCD_CACHE_SIZE );
    
	#ifdef USING_WATERMARKS
		// ����� ���������� ������ � ������������ ��������
		LoWaterMark = 0;
		HiWaterMark = LCD_CACHE_SIZE - 1;
	#endif

    // ��������� ����� ��������� ����
    UpdateLcd = TRUE;
}
*/


/*
 * ���                   :  LcdUpdate
 * ��������              :  �������� ��� � ��� �������
 * ��������(�)           :  ���
 * ������������ �������� :  ���
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

    #ifdef CHINA_LCD  // �������� ��� ���������� �� �� ������������� ������������

        byte x,y;

        // 102 x 64 - ������ �������������� ���������� ������ ���������� ��, ��� ���
        // ������ ������ ������������ �� ������� �� ������� ����� �� 3 �������.
        // ������� ������� �������� ���� - ������� � ������ ������ y+1, � �����
        // ������� ����� (����� ���� ���� �������, �������� � ������ ������)
                
        x = LoWaterMark % LCD_X_RES;      // ������������� ��������� ����� x
        n3310LcdClass::LcdSendCommand( 0x80 | x);     // ������������ ������ ������� LoWaterMark
        
        y = LoWaterMark / LCD_X_RES + 1;  // ������������� ��������� ����� y+1
        n3310LcdClass::LcdSendCommand( 0x40 | y);     // ������������ ������ ������� LoWaterMark

        for ( i = LoWaterMark; i <= HiWaterMark; i++ )
        {
            // �������� ������ � ����� �������
            LcdSend( LcdCache[i], LCD_DATA );
            
            x++;                 // ������ ������������ ���������� x, ����� ������� ������� �� ����� ������
            if (x >= LCD_X_RES)  // ���� ����� �� ������, �� ��������� �� ��������� ������ (x=0; y++)
            {
                // ����� ������, ����� ����� ��������� ������ ����� �������������� ������,
                // �������� ���� ��������� ��������� �����, ����� ��� �������� :)
                x=0;                
                n3310LcdClass::LcdSendCommand( 0x80);
                y++;
                n3310LcdClass::LcdSendCommand( 0x40 | y,);
            }
        }

        n3310LcdClass::LcdSendCommand( 0x21);    // �������� ����������� ����� ������
        n3310LcdClass::LcdSendCommand( 0x45);    // �������� �������� �� 5 �������� ����� (������������� ������� �������, �������� � ����������)
        n3310LcdClass::LcdSendCommand( 0x20);    // �������� ����������� ����� ������ � �������������� ���������

    #else  // �������� ��� ������������� �������

			// ������������� ��������� ����� � 0
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
			// ��������� ����������� ����� ������ �������
			//for (uint16_t i = 0; i < LCD_CACHE_SIZE; i++ )
//		        {
		        // ��� ������������� ������� �� ����� ������� �� ������� � ������,
	            // ����� ������ ��������������� �������� ������
				//n3310LcdClass::LcdSendData( LcdCache[i]);
			
				//LcdPinDC::SetOutHigh();
				//n3310LcdClass::ActivateDisplay();
				//dma_start(LcdCache);
				//_delay_ms(2);
				//n3310LcdClass::DeactivateDisplay();
//				}

    #endif

    // ����� ����� ��������� ����
//    UpdateLcd = FALSE;
}
*/


/*
 * ���                   :  LcdSend
 * ��������              :  ���������� ������ � ���������� �������
 * ��������(�)           :  data -> ������ ��� ��������
 *                          cd   -> ������� ��� ������ (������ enum � n3310.h)
 * ������������ �������� :  ���
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
    // �������� ���������� ������� (������ ������� ��������)
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

	LCD_SPI.DATA	= data;// �������� ������ � ���������� �������
	while (!(LCD_SPI.STATUS & SPI_IF_bm));// ���� ��������� ��������
    // �������� ������ � ���������� �������
    //SPDR = data;

    // ���� ��������� ��������
    //while ( (SPSR & 0x80) != 0x80 );

    // ��������� ���������� �������
    //LCD_PORT |= _BV( LCD_CE_PIN );
	LcdDectivate();*/
//}



/*
 * ���                   :  LcdContrast
 * ��������              :  ������������� ������������� �������
 * ��������(�)           :  �������� -> �������� �� 0x00 � 0x7F
 * ������������ �������� :  ���
 */
/*
void LcdContrast ( uint8_t contrast )
{
    n3310LcdClass::LcdSendCommand( 0x21);              // ����������� ����� ������
    n3310LcdClass::LcdSendCommand( 0x80 | contrast);   // ��������� ������ �������������
    n3310LcdClass::LcdSendCommand( 0x20);              // ����������� ����� ������, �������������� ���������
}

*/

/*
 * ���                   :  Delay
 * ��������              :  ��������������� �������� ��� ��������� ������������� LCD
 * ��������(�)           :  ���
 * ������������ �������� :  ���
 */
/*
static void Delay ( void )
{
    int i;

    for ( i = -32000; i < 32000; i++ );
}
*/


/*
 * ���                   :  LcdGotoXYFont
 * ��������              :  ������������� ������ � ������� x,y ������������ ������������ ������� ������
 * ��������(�)           :  x,y -> ���������� ����� ������� �������. ��������: 0,0 .. 13,5
 * ������������ �������� :  ������ ������������ �������� � n3310.h
 */
uint8_t LcdGotoXYFont ( uint8_t x, uint8_t y )
{
    // �������� ������
    if( x > 13 || y > 5 ) return OUT_OF_BORDER;

    //  ���������� ���������. ��������� ��� ����� � �������� 504 ����
    LcdCacheIdx = x * 6 + y * 84;
    return OK;
}

/*
 * ���                   :  LcdChr
 * ��������              :  ������� ������ � ������� ������� �������, ����� �������������� ��������� �������
 * ��������(�)           :  size -> ������ ������. ������ enum � n3310.h
 *                          ch   -> ������ ��� ������
 * ������������ �������� :  ������ ������������ �������� � n3310lcd.h
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
			// ��������� ������ �������
			LoWaterMark = LcdCacheIdx;
			}
	#endif

	if ( (ch >= 0x20) && (ch <= 0x7F) )
		{
		// �������� � ������� ��� �������� ASCII[0x20-0x7F]
		ch -= 32;
		}
	else if ( ch >= 0xC0 )
		{
		// �������� � ������� ��� �������� CP1251[0xC0-0xFF]
	    ch -= 96;
		}
	else
		{
		// ��������� ���������� (�� ������ ��� � ������� ��� �������� ������)
		ch = 95;
		}

    if ( size == FONT_1X )
    {
        for ( i = 0; i < 5; i++ )
        {
            // �������� ��� ������� �� ������� � ���
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
            // �������� ��� ������� �� ������� � ��������� ����������
            c = pgm_read_byte(&(FontLookup[ch][i])) << 1;
            // ����������� ��������
            // ������ �����
            b1 =  (c & 0x01) * 3;
            b1 |= (c & 0x02) * 6;
            b1 |= (c & 0x04) * 12;
            b1 |= (c & 0x08) * 24;

            c >>= 4;
            // ������ �����
            b2 =  (c & 0x01) * 3;
            b2 |= (c & 0x02) * 6;
            b2 |= (c & 0x04) * 12;
            b2 |= (c & 0x08) * 24;

            // �������� ��� ����� � ���
            LcdCache[tmpIdx++] = b1;
            LcdCache[tmpIdx++] = b1;
            LcdCache[tmpIdx + 82] = b2;
            LcdCache[tmpIdx + 83] = b2;
        }

        // ��������� x ���������� �������
        LcdCacheIdx = (LcdCacheIdx + 11) % LCD_CACHE_SIZE;
    }

	#ifdef USING_WATERMARKS
		if ( LcdCacheIdx > HiWaterMark )
			{
			// ��������� ������� �������
			HiWaterMark = LcdCacheIdx;
			}
	#endif

    // �������������� ������ ����� ���������
    LcdCache[LcdCacheIdx] = 0x00;
    // ���� �������� ������� ��������� LCD_CACHE_SIZE - 1, ��������� � ������
//    if(LcdCacheIdx == (LCD_CACHE_SIZE - 1) )
    if(++LcdCacheIdx == LCD_CACHE_SIZE )
    {
        LcdCacheIdx = 0;
        return OK_WITH_WRAP;
    }
    // ����� ������ �������������� ���������
//    LcdCacheIdx++;
    return OK;
}



/*
 * ���                   :  LcdStr
 * ��������              :  ��� ������� ������������� ��� ������ ������ ������� �������� � RAM
 * ��������(�)           :  size      -> ������ ������. ������ enum � n3310.h
 *                          dataArray -> ������ ���������� ������ ������� ����� ����������
 * ������������ �������� :  ������ ������������ �������� � n3310lcd.h
 */
uint8_t LcdStr ( LcdFontSize size, uint8_t dataArray[] )
{
    uint8_t tmpIdx=0;
    uint8_t response;
    while( dataArray[ tmpIdx ] != '\0' && tmpIdx < LCD_CHAR_WIDTH)
    {
        // ������� ������
        response = LcdChr( size, dataArray[ tmpIdx ] );
        // �� ����� ����������� ���� ���������� OUT_OF_BORDER,
        // ������ ����� ���������� ������ �� ������ �������
        if( response == OUT_OF_BORDER)
            return OUT_OF_BORDER;
        // ����������� ���������
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
		// ������� ������
//		response = LcdChr( FONT_1X, pgm_read_byte(dataArray[ tmpIdx ]) );
//		response = LcdChr( FONT_1X, pgm_read_byte(dataArray[ tmpIdx ]) );
		response = LcdChr( FONT_1X, pgm_read_byte(STR_PDAMENU_6ROW_NEXT_DOWN + tmpIdx ));
		// �� ����� ����������� ���� ���������� OUT_OF_BORDER,
		// ������ ����� ���������� ������ �� ������ �������
		if( response == OUT_OF_BORDER)
			{
			return;
			//return OUT_OF_BORDER;
			}
		// ����������� ���������
		tmpIdx++;
		}
	memset(lcd_buf, 0, 15);
	*/
	}




/*
 * ���                   :  LcdFStr
 * ��������              :  ��� ������� ������������� ��� ������ ������ ������� �������� � Flash ROM
 * ��������(�)           :  size    -> ������ ������. ������ enum � n3310.h
 *                          dataPtr -> ��������� �� ������ ������� ����� ����������
 * ������������ �������� :  ������ ������������ �������� � n3310lcd.h
 * ������                :  LcdFStr(FONT_1X, PSTR("Hello World"));
 *                          LcdFStr(FONT_1X, &name_of_string_as_array);
 */
uint8_t LcdFStr ( LcdFontSize size, const uint8_t *dataPtr )
{
    uint8_t c;
    uint8_t response;
    for ( c = pgm_read_byte( dataPtr ); c; ++dataPtr, c = pgm_read_byte( dataPtr ) )
    {
        // ������� ������
        response = LcdChr( size, c );
        if(response == OUT_OF_BORDER)
            return OUT_OF_BORDER;
    }

    return OK;
}



/*
 * ���                   :  LcdPixel
 * ��������              :  ���������� ������� �� ���������� ����������� (x,y)
 * ��������(�)           :  x,y  -> ���������� ���������� �������
 *                          mode -> Off, On ��� Xor. ������ enum � n3310.h
 * ������������ �������� :  ������ ������������ �������� � n3310lcd.h
 */
uint8_t LcdPixel ( uint8_t x, uint8_t y, LcdPixelMode mode )
    {
    int  index;
    uint8_t  offset;
    uint8_t  data;

    // ������ �� ������ �� �������
    if ( x >= LCD_X_RES || y >= LCD_Y_RES)
      {
      return OUT_OF_BORDER;
      }

    LcdCacheChanged = true;
    // �������� ������� � ��������
    index = ( ( y / 8 ) * 84 ) + x;
    offset  = y - ( ( y / 8 ) * 8 );

    data = LcdCache[ index ];

    // ��������� �����

    // ����� PIXEL_OFF
    if ( mode == PIXEL_OFF )
        {
        data &= ( ~( 0x01 << offset ) );
        }
    // ����� PIXEL_ON
    else if ( mode == PIXEL_ON )
        {
        data |= ( 0x01 << offset );
        }
    // ����� PIXEL_XOR
    else if ( mode  == PIXEL_XOR )
        {
        data ^= ( 0x01 << offset );
        }

    // ������������� ��������� �������� � ���
    LcdCache[ index ] = data;

	#ifdef USING_WATERMARKS
		if ( index < LoWaterMark )
			{
			// ��������� ������ �������
			LoWaterMark = index;
			}

		if ( index > HiWaterMark )
			{
			// ��������� ������� �������
			HiWaterMark = index;
			}
	#endif
    return OK;
    }



/*
 * ���                   :  LcdLine
 * ��������              :  ������ ����� ����� ����� ������� �� ������� (�������� ����������)
 * ��������(�)           :  x1, y1  -> ���������� ���������� ������ �����
 *                          x2, y2  -> ���������� ���������� ����� �����
 *                          mode    -> Off, On ��� Xor. ������ enum � n3310.h
 * ������������ �������� :  ������ ������������ �������� � n3310lcd.h
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

    // dy �������������
    if ( dy < 0 )
    {
        dy    = -dy;
        stepy = -1;
    }
    else
    {
        stepy = 1;
    }

    // dx �������������
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

    // ������ ��������� �����
    response = LcdPixel( x1, y1, mode );
    if(response)
        return response;

    // ������ ��������� ����� �� �����
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

    // ��������� ����� ��������� ����
    //UpdateLcd = TRUE;
    return OK;
}



/*
 * ���                   :  LcdCircle
 * ��������              :  ������ ���������� (�������� ����������)
 * ��������(�)           :  x, y   -> ���������� ���������� ������
 *                          radius -> ������ ����������
 *                          mode   -> Off, On ��� Xor. ������ enum � n3310.h
 * ������������ �������� :  ������ ������������ �������� � n3310lcd.h
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

    // ��������� ����� ��������� ����
    //UpdateLcd = TRUE;
    return OK;
}


/*
 * ���                   :  LcdSingleBar
 * ��������              :  ������ ���� ����������� �������������
 * ��������(�)           :  baseX  -> ���������� ���������� x (������ ����� ����)
 *                          baseY  -> ���������� ���������� y (������ ����� ����)
 *                          height -> ������ (� ��������)
 *                          width  -> ������ (� ��������)
 *                          mode   -> Off, On ��� Xor. ������ enum � n3310.h
 * ������������ �������� :  ������ ������������ �������� � n3310lcd.h
 */
uint8_t LcdSingleBar ( uint8_t baseX, uint8_t baseY, uint8_t height, uint8_t width, LcdPixelMode mode )
{
    uint8_t tmpIdxX,tmpIdxY,tmp;

    uint8_t response;

    // �������� ������
    if ( ( baseX >= LCD_X_RES) || ( baseY >= LCD_Y_RES) ) return OUT_OF_BORDER;

    if ( height > baseY )
        tmp = 0;
    else
        tmp = baseY - height + 1;

    // ��������� �����
    for ( tmpIdxY = tmp; tmpIdxY <= baseY; tmpIdxY++ )
    {
        for ( tmpIdxX = baseX; tmpIdxX < (baseX + width); tmpIdxX++ )
        {
            response = LcdPixel( tmpIdxX, tmpIdxY, mode );
            if(response)
                return response;

        }
    }

    // ��������� ����� ��������� ����
    //UpdateLcd = TRUE;
    return OK;
}



/*
 * ���                   :  LcdBars
 * ��������              :  ������ ������ ����������� ��������������� (� ������ PIXEL_ON)
 * ��������(�)           :  data[]     -> ������ ������� ����� ����������
 *                          numbBars   -> ���������� ���������������
 *                          width      -> ������ (� ��������)
 *                          multiplier -> ��������� ��� ������
 * ������������ �������� :  ������ ������������ �������� � n3310lcd.h
 * ����������            :  ���������� ��������� �������� EMPTY_SPACE_BARS, BAR_X, BAR_Y � n3310.h
 * ������                :  byte example[5] = {1, 2, 3, 4, 5};
 *                          LcdBars(example, 5, 3, 2);
 */
uint8_t LcdBars ( uint8_t data[], uint8_t numbBars, uint8_t width, uint8_t multiplier )
{
    uint8_t b;
    uint8_t tmpIdx = 0;
    uint8_t response;

    for ( b = 0;  b < numbBars ; b++ )
    {
        // ������ �� ������ �� �������
        if ( tmpIdx > LCD_X_RES - 1 ) return OUT_OF_BORDER;

        // ������ �������� x
        tmpIdx = ((width + EMPTY_SPACE_BARS) * b) + BAR_X;

        // ������ ���� �������������
        response = LcdSingleBar( tmpIdx, BAR_Y, data[b] * multiplier, width, PIXEL_ON);
        if(response == OUT_OF_BORDER)
            return response;
    }

    // ��������� ����� ��������� ����
    //UpdateLcd = TRUE;
    return OK;

}



/*
 * ���                   :  LcdRect
 * ��������              :  ������ ������������� �������������
 * ��������(�)           :  x1    -> ���������� ���������� x ������ �������� ����
 *                          y1    -> ���������� ���������� y ������ �������� ����
 *                          x2    -> ���������� ���������� x ������� ������� ����
 *                          y2    -> ���������� ���������� y ������� ������� ����
 *                          mode  -> Off, On ��� Xor. ������ enum � n3310.h
 * ������������ �������� :  ������ ������������ �������� � n3310lcd.h
 */
uint8_t LcdRect ( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, LcdPixelMode mode )
{
    uint8_t tmpIdx;

    // �������� ������
    if ( ( x1 >= LCD_X_RES) ||  ( x2 >= LCD_X_RES) || ( y1 >= LCD_Y_RES) || ( y2 >= LCD_Y_RES) )
        return OUT_OF_BORDER;

    if ( ( x2 > x1 ) && ( y2 > y1 ) )
    {
        // ������ �������������� �����
        for ( tmpIdx = x1; tmpIdx <= x2; tmpIdx++ )
        {
            LcdPixel( tmpIdx, y1, mode );
            LcdPixel( tmpIdx, y2, mode );
        }

        // ������ ������������ �����
        for ( tmpIdx = y1; tmpIdx <= y2; tmpIdx++ )
        {
            LcdPixel( x1, tmpIdx, mode );
            LcdPixel( x2, tmpIdx, mode );
        }

        // ��������� ����� ��������� ����
        //UpdateLcd = TRUE;
    }
    return OK;
}



/*
 * ���                   :  LcdImage
 * ��������              :  ������ �������� �� ������� ������������ � Flash ROM
 * ��������(�)           :  ��������� �� ������ ��������
 * ������������ �������� :  ���
 */
void LcdImage ( const uint8_t *imageData )
    {
//    // ������������� ��������� ����
//    LcdCacheIdx = 0;
//    // � �������� ����
//    for ( LcdCacheIdx = 0; LcdCacheIdx < LCD_CACHE_SIZE; LcdCacheIdx++ )
//    {
//        // �������� ������ �� ������� � ���
//        LcdCache[LcdCacheIdx] = pgm_read_byte( imageData++ );
//    }
    
    LcdCacheChanged = true;
    // ����������� �� Jakub Lasinski (March 14 2009)
    memcpy_P( LcdCache, imageData, LCD_CACHE_SIZE );  // ���� ����� ��� � ����, �� �������� ������ ������ � ������� �����������
    
    #ifdef USING_WATERMARKS
		// ����� ���������� ������ � ������������ ��������
		LoWaterMark = 0;
		HiWaterMark = LCD_CACHE_SIZE - 1;
	#endif

    // ��������� ����� ��������� ����
    //UpdateLcd = TRUE;
}


/*
void Lcd_dma_init(void){

DMA.CTRL			= DMA_ENABLE_bm;     // ��������� DMA
//DMA.CH0.REPCNT		= 1;
//DMA.CH0.CTRLA		= DMA_CH_BURSTLEN0_bm | DMA_CH_REPEAT_bm; // ��������� �� ������������� �������� 1 �������� ��������
DMA.CH0.CTRLA		= DMA_CH_BURSTLEN_1BYTE_gc | DMA_CH_SINGLE_bm; // ��������� �� ������������� �������� 1 �������� ��������
//DMA.CH0.CTRLA		= DMA_CH_SINGLE_bm; // ��������� �� ������������� �������� 1 �������� ��������
//DMA.CH0.CTRLB		= DMA_CH_TRNIF_bm | DMA_CH_TRNINTLVL0_bm;
DMA.CH0.CTRLB		= DMA_CH_TRNINTLVL0_bm;
//DMA.CH0.ADDRCTRL	= DMA_CH_SRCRELOAD_gm |DMA_CH_SRCDIR0_bm | DMA_CH_DESTRELOAD_gm | DMA_CH_DESTDIR0_bm; // ��������� ������������� ������� ����� ������ �������� � ���������� ������� �� ��������� ��������
//DMA.CH0.ADDRCTRL	= DMA_CH_SRCRELOAD_BURST_gc | DMA_CH_SRCDIR_INC_gc | DMA_CH_DESTRELOAD_BURST_gc | DMA_CH_DESTDIR_FIXED_gc; // ��������� ������������� ������� ����� ������ �������� � ���������� ������� �� ��������� ��������
//DMA.CH0.ADDRCTRL	= DMA_CH_SRCRELOAD_BURST_gc | DMA_CH_SRCDIR_FIXED_gc | DMA_CH_DESTRELOAD_BURST_gc | DMA_CH_DESTDIR_FIXED_gc; // ��������� ������������� ������� ����� ������ �������� � ���������� ������� �� ��������� ��������
//DMA.CH0.ADDRCTRL	= DMA_CH_SRCRELOAD_NONE_gc | DMA_CH_SRCDIR_INC_gc | DMA_CH_DESTRELOAD_NONE_gc | DMA_CH_DESTDIR_FIXED_gc; // ��������� ������������� ������� ����� ������ �������� � ���������� ������� �� ��������� ��������
DMA.CH0.ADDRCTRL	= DMA_CH_SRCRELOAD_TRANSACTION_gc | DMA_CH_SRCDIR_INC_gc | DMA_CH_DESTRELOAD_NONE_gc | DMA_CH_DESTDIR_FIXED_gc; // ��������� ������������� ������� ����� ������ �������� � ���������� ������� �� ��������� ��������
DMA.CH0.TRIGSRC		= DMA_CH_TRIGSRC_USARTE1_DRE_gc;
DMA.CH0.TRFCNT		= LCD_CACHE_SIZE;                  // ��������� �������� �������� �� 40 ������ (�.�. int = 2 ������)
DMA.CH0.REPCNT		= 1;

//DMA.CH0.SRCADDR0 = (uint16_t)&LcdCache;     // ��������� ������ ��������� �� ������ massIn
//DMA.CH0.SRCADDR1 = (uint16_t)&LcdCache>>8;
DMA.CH0.SRCADDR0 = (uintptr_t)&LcdCache;     // ��������� ������ ��������� �� ������ massIn
DMA.CH0.SRCADDR1 = (uintptr_t)&LcdCache>>8;
DMA.CH0.SRCADDR2 = 0;

//DMA.CH0.DESTADDR0 = (int)&LcdCache1;  // ��������� ������ ��������� �� ������ massOut
//DMA.CH0.DESTADDR1 = (int)&LcdCache1>>8;
//DMA.CH0.DESTADDR2 = 0;

DMA.CH0.DESTADDR0 = (((uintptr_t) &USARTE1.DATA) >>0*8)&0xFF;
DMA.CH0.DESTADDR1 = (((uintptr_t) &USARTE1.DATA) >>1*8)&0xFF;
DMA.CH0.DESTADDR2 = 0;//(((uint16_t) &USARTE1.DATA) >>2*8)&0xFF;


//DMA.CH0.CTRLA |= DMA_CH_ENABLE_bm;   // ���������� ������ ������ 0 DMA

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
	DMA.CH0.CTRLA |= DMA_CH_TRFREQ_bm; // ������ DMA ��������
	}*/
//DMA.CH0.CTRLA |= DMA_CH_TRFREQ_bm; // ������ DMA ��������
//_delay_ms(1);
/*
//_delay_us(1);
if ((DMA.STATUS & (DMA_CH0PEND_bm | DMA_CH0BUSY_bm)) == 0)
	{
	// disable the DMA channel
	DMA.CH0.CTRLA &= ~DMA_CH_ENABLE_bm;
	// reset SRCADDR
	DMA.CH0.SRCADDR0 = (int)&LcdCache;     // ��������� ������ ��������� �� ������ massIn
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
DMA.CH0.SRCADDR0 = (uint16_t)&LcdCache;     // ��������� ������ ��������� �� ������ massIn
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
	DMA.CH0.SRCADDR0 = (int)&LcdCache;     // ��������� ������ ��������� �� ������ massIn
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
DMA.CH0.SRCADDR0 = (int)&LcdCache;     // ��������� ������ ��������� �� ������ massIn
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
	DMA.CH0.CTRLA |= DMA_CH_TRFREQ_bm; // ������ DMA ��������
	USARTE1.DATA	= LcdCache[0];
	}
*/
//}

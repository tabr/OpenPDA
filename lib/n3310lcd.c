// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


/*void LcdInit ( void )    //инициализация SPI и дисплея
        {
//		LcdCache [LCD_CACHSIZE]=255;
//        LCD_RST_PORT.LCD_RST_PIN = 1;       //настроили порты ввода/вывода
//		sbi(LCD_RST_PORT,LCD_RST_PIN);       //настроили порты ввода/вывода
//        LCD_RST_DDR.LCD_RST_PIN = LCD_DC_DDR.LCD_DC_PIN = LCD_CDDR.LCD_CPIN = LCD_MOSI_DDR.LCD_MOSI_PIN = LCD_CLK_DDR.LCD_CLK_PIN = 1;
		//sbi(LCD_RST_DDR, LCD_RST_PIN);
		HAL.IO.setDirOut(LCD_RST_PIN_HAL);
		//sbi(LCD_DC_DDR, LCD_DC_PIN);
		HAL.IO.setDirOut(LCD_DC_PIN_HAL);
		//sbi(LCD_SS_DDR, LCD_SS_PIN);
		HAL.IO.setDirOut(LCD_SS_PIN_HAL);
		//sbi(LCD_MOSI_DDR, LCD_MOSI_PIN);
		HAL.IO.setDirOut(LCD_MOSI_PIN_HAL);
		
//		sbi(LCD_CLK_DDR, LCD_CLK_PIN);
//      cbi(LCD_CLK_PORT, LCD_CLK_PIN);
		HAL.IO.setDirOut(LCD_CLK_PIN_HAL);

		HAL.IO.setOutLow(LCD_CLK_PIN_HAL);
//        LCD_RST_DDR.LCD_RST_PIN = LCD_DC_DDR.LCD_DC_PIN = LCD_CDDR.LCD_CPIN = LCD_MOSI_DDR.LCD_MOSI_PIN = LCD_CLK_DDR.LCD_CLK_PIN = LCD_CLK_DDR1.LCD_CLK_PIN1 = 1;
//        LCD_CLK_PORT.LCD_CLK_PIN = 0;
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
        //cbi(LCD_RST_PORT,LCD_RST_PIN);       //дернули ресет
		HAL.IO.setOutLow(LCD_RST_PIN_HAL);//дернули ресет
        delay_ms(20);
//        LCD_RST_PORT.LCD_RST_PIN = 1;
        //sbi(LCD_RST_PORT, LCD_RST_PIN);
		HAL.IO.setOutHigh(LCD_RST_PIN_HAL);
                            //Enable SPI port: No interrupt, MSBit first, Master mode, CPOL->0, CPHA->0, Clk/4

//        LCD_CPORT.LCD_CPIN = 1;        //Disable LCD controller
        //sbi(LCD_SS_PORT, LCD_SS_PIN);        //Disable LCD controller
		HAL.IO.setOutHigh(LCD_SS_PIN_HAL);

        LcdDisplay.LcdSendData( 0b00100001, LCD_CMD );                         //LCD Extended Commands
        LcdDisplay.LcdSendData( 0b00000100+LCD_TEMP_CONTROL, LCD_CMD );                     //Set Temp coefficent
        #ifdef china
			LcdDisplay.LcdSendData( 0b00001000|LCD_SPI_INVERT<<3, LCD_CMD );                     //порядок битов в SPI
        #endif
//return;
		LcdDisplay.LcdSendData( 0b00010000+LCD_BIAS, LCD_CMD );                         //LCD bias mode 1:48
        #ifdef china
			LcdDisplay.LcdSendData( 0b01000000+LCD_SHIFT, LCD_CMD );                         //первая строка выше экрана, отображаем со второй
        #endif
		LcdDisplay.LcdSendData( 0b10000000+LCD_VOP, LCD_CMD );                         //Set LCD Vop (Contrast)
    
        #ifdef china
//    LcdSend( 0x20|LCD_X_MIRROR<<4|LCD_Y_MIRROR<<3|power_down<<2, LCD_CMD );            //LCD Standard Commands
			LcdDisplay.LcdSendData( 0x20|LCD_X_MIRROR<<4|LCD_Y_MIRROR<<3|0<<2, LCD_CMD );            //LCD Standard Commands
        #endif
//        LcdSend( 0x20|power_down<<2|LCD_ADDRESSING<<1, LCD_CMD );                //LCD Standard Commands
        LcdDisplay.LcdSendData( 0x20|0<<2|LCD_ADDRESSING<<1, LCD_CMD );                //LCD Standard Commands
        LcdDisplay.LcdSendData( 0b00001000|((LCD_DISP_CONFIG<<1|LCD_DISP_CONFIG)&0b00000101), LCD_CMD );     //LCD mode
//        LcdClear();
        LcdClearUpdate();
        }
*/		

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
void LcdSend (uint8_t data, uint8_t cmd)    //Sends data to display controller
        {

		LcdDisplay.LcdSendData(data, cmd);
		return;
//			uint8_t tmp=0;
        #ifdef SOFT_SPI
			uint8_t i, mask = 128;
        #endif
//		uint8_t result;
        
//        LCD_CPORT.LCD_CPIN = 0;                //Enable display controller (active low)
        //cbi(LCD_SS_PORT,LCD_SS_PIN);                //Enable display controller (active low)
		HAL.IO.setOutLow(LCD_SS_PIN_HAL);
        if (cmd)
			{
//            LCD_DC_PORT.LCD_DC_PIN = 1;    //выбираем команда или данные
            //sbi(LCD_DC_PORT,LCD_DC_PIN);    //выбираем команда или данные
			HAL.IO.setOutHigh(LCD_DC_PIN_HAL);
			}
        else
			{
//            LCD_DC_PORT.LCD_DC_PIN = 0;
            //cbi(LCD_DC_PORT,LCD_DC_PIN);
			HAL.IO.setOutLow(LCD_DC_PIN_HAL);
			}
        #ifdef SOFT_SPI
			for (i=0;i<8;i++)
				{
				if ((data&mask)!=0)
					{
//	                LCD_MOSI_PORT.LCD_MOSI_PIN = 1; 
					sbi(LCD_MOSI_PORT,LCD_MOSI_PIN); 
					}
				else
					{
//	                LCD_MOSI_PORT.LCD_MOSI_PIN = 0;
					cbi(LCD_MOSI_PORT,LCD_MOSI_PIN); 
					}
//		          mask = mask/2;// >>1 ???
				mask = mask>>1;// >>1 ???
//				LCD_CLK_PORT.LCD_CLK_PIN = 1;
				sbi(LCD_CLK_PORT,LCD_CLK_PIN);
//				LCD_CLK_PORT1.LCD_CLK_PIN1 = 1;
				delay_us(1);
//				LCD_CLK_PORT.LCD_CLK_PIN = 0;
				cbi(LCD_CLK_PORT,LCD_CLK_PIN);
//				LCD_CLK_PORT1.LCD_CLK_PIN1 = 0;
				}
        #else
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
		//setOutHigh
		HAL.IO.setOutHigh(LCD_SS_PIN_HAL);//Disable display controller
		//PORTC.OUTSET	= 1<<3;
        }
*/

/*
void LcdStartDMAUpdate (void)
	{
	LcdSend(0x80, LCD_CMD);        //команды установки указателя памяти дисплея на 0,0
	LcdSend(0x40, LCD_CMD);
	cbi(LCD_DC_PORT,LCD_DC_PIN);// выбираем данные
	//TODO...
	}
*/

void LcdUpdate (void)   //Copies the LCD cache into the device RAM
        {
        int i;
//		uint8_t i;
//		byte tmp;
		uint8_t *ptr=LcdCache;
    #ifdef china
    char j;
    #endif

        LcdDisplay.LcdSendData(0x80, LCD_CMD);        //команды установки указателя памяти дисплея на 0,0
        LcdDisplay.LcdSendData(0x40, LCD_CMD);
        
        #ifdef china                            //если китайский дисплей - грузим пустую строку
        for (j = Cntr_X_RES; j>0; j--)
			{
			LcdDisplay.LcdSendData(0, LCD_DATA);
			}
		#endif
        
#ifndef SOFT_SPI
LcdDisplay.ActivateDisplay();//1.
#endif
//PORTC.OUTSET	= 1<<2;//1. dc=data
		for (i = 0; i < LCD_CACHSIZE; i++)        //грузим данные
//		for (i = 0; i < LCD_CACHSIZE/2; i++)        //грузим данные
//			while(1)
			{
			#ifdef SOFT_SPI
				LcdDisplay.LcdSendData(*ptr++, LCD_DATA);
				wdt_reset();
			#else
				LCD_SPI.DATA	= *ptr++;
				while (!(LCD_SPI.STATUS & SPI_IF_bm));
			#endif // SOFT_SPI
			

			#ifdef china                //если дисплей китайский - догружаем каждую строку до размера его буфера
			if (++j == LCD_X_RES) 
				{
				for (j = (Cntr_X_RES-LCD_X_RES); j>0; j--)
					{
					LcdSend(0, LCD_DATA);
					}
				j=0;
				}
			#endif 
//			++ptr;
//			if (*ptr == 255)
//				break;
			}
#ifndef SOFT_SPI
LcdDisplay.DeactivateDisplay();
#endif
        }
/*
void LcdClear (void)    //Clears the display
        {
        int i;
		uint8_t *ptr=&LcdCache[0];
//    memset( LcdCache, 0x00, LCD_CACHSIZE );    
//    for (i = 0; i < LCD_CACHSIZE; i++) LcdCache[i] = 0;    //забиваем всю память 0
    for (i = 0; i < LCD_CACHSIZE; i++) *ptr++ = 0;    //забиваем всю память 0
//    i=LCD_CACHSIZE;
//    while (i-- > 0)
//        LcdCache[i] = 0;
		LcdUpdate ();
        }
*/
void LcdClearCache (void)    //Clears the display
	{
	int i;
	uint8_t *ptr=&LcdCache[0];
	for (i = 0; i < LCD_CACHSIZE; i++) *ptr++ = 0;    //забиваем всю память 0
	}

void LcdClearUpdate (void)    //Clears the display
	{
	int i;
	LcdDisplay.LcdSendData(0x80, LCD_CMD);        //команды установки указателя памяти дисплея на 0,0
	LcdDisplay.LcdSendData(0x40, LCD_CMD);
	for (i = 0; i < LCD_CACHSIZE; i++)
		{
		LcdDisplay.LcdSendData(0x00,LCD_DATA);    //забиваем всю память 0
		}
	}

void LcdContrast (uint8_t contrast)     //contrast -> Contrast value from 0x00 to 0x7F
	{
	if (contrast > 0x7F)
		return;
	LcdDisplay.LcdSendData( 0x21, LCD_CMD );               //LCD Extended Commands
	LcdDisplay.LcdSendData( 0x80 | contrast, LCD_CMD );    //Set LCD Vop (Contrast)
	LcdDisplay.LcdSendData( 0x20, LCD_CMD );               //LCD Standard Commands,Horizontal LCD_ADDRESSING mode
	}
        
void LcdMode (uint8_t mode)         //режим дисплея: 0 - blank, 1 - all on, 2 - normal, 3 - inverse
	{
	if (mode > 3)
		return;
	LcdDisplay.LcdSendData( 0b00001000|((mode<<1|mode)&0b00000101), LCD_CMD );     //LCD mode
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
		LcdDisplay.LcdSendData( 0x20|LCD_X_MIRROR<<4|LCD_Y_MIRROR<<3|1<<2|LCD_ADDRESSING<<1, LCD_CMD );            //LCD Standard Commands
	#else
		LcdDisplay.LcdSendData( 0x20|1<<2|LCD_ADDRESSING<<1, LCD_CMD );
	#endif
	}
        
void Lcd_on (void)                 //вкл дисплея
	{
	#ifdef china
		LcdDisplay.LcdSendData( 0x20|LCD_X_MIRROR<<4|LCD_Y_MIRROR<<3|0<<2|LCD_ADDRESSING<<1, LCD_CMD );            //LCD Standard Commands
	#else
		LcdDisplay.LcdSendData( 0x20|0<<2|LCD_ADDRESSING<<1, LCD_CMD );
	#endif
	}

#ifdef ATMEL_STUDIO
//void LcdImage (uint8_t *imageData PROGMEM)                    //вывод изображения
void LcdImage (const uint8_t *imageData PROGMEM)                    //вывод изображения
//void LcdImage (const uint8_t& imageData)                    //вывод изображения
#else
void LcdImage (flash uint8_t *imageData)                    //вывод изображения
#endif
//void LcdImage (flash uint8_t *imageData)    //вывод изображения
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
#ifdef ATMEL_STUDIO
void LcdImage40x40 (uint8_t *imageData PROGMEM)                    //вывод изображения
#else
void LcdImage40x40 (flash uint8_t *imageData)                    //вывод изображения
#endif
//void LcdImage40x40 (flash uint8_t *imageData)    //вывод изображения
        {
        unsigned int i;
        uint8_t j,k=0;

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
/*
#ifdef ATMEL_STUDIO
//void LcdImage (uint8_t *imageData PROGMEM)                    //вывод изображения
void LcdImageUpdate (const uint8_t *imageData PROGMEM)                    //вывод изображения
//void LcdImage (const uint8_t& imageData)                    //вывод изображения
#else
void LcdImageUpdate (flash uint8_t *imageData)                    //вывод изображения
#endif
//void LcdImage (flash uint8_t *imageData)    //вывод изображения
	{
	unsigned int i;
	uint8_t dataByte;
	
	LcdSend(0x80, LCD_CMD);        //ставим указатель на 0,0
	LcdSend(0x40, LCD_CMD);
	#ifdef ATMEL_STUDIO
	//			LcdCache[LcdCacheIdx++] = pgm_read_byte(&table[(ch*5+i)]);    //выделяем байт-столбик из символа и грузим в массив - 5 раз
	//	        for (i = 0; i < LCD_CACHSIZE; i++) LcdCache[i] = pgm_read_byte(&(imageData[i]));    //грузим данные
	for (i = 0; i < LCD_CACHSIZE; i++)
		{
		dataByte	= pgm_read_byte(&(imageData[i]));
//		LcdCache[i] = pgm_read_byte(&(imageData[i]));    //грузим данные
		LcdSend(dataByte,LCD_DATA);    //грузим данные
		LcdCache[i]	= dataByte;
		
		}
	#else
	for (i = 0; i < LCD_CACHSIZE; i++)
		{
		//LcdCache[i] = imageData[i];    //грузим данные
		LcdSend(imageData[i],LCD_DATA);
		}
	#endif
	}
*/
void LcdPixel (uint8_t x, uint8_t y, uint8_t mode)     //Displays a pixel at given absolute (x, y) location, mode -> Off, On or Xor
        {
        int index;
        uint8_t offset, data;
        
        if ( x > LCD_X_RES ) return;    //если передали в функцию муть - выходим
        if ( y > LCD_Y_RES ) return;
    
        index = (((int)(y)/8)*84)+x;    //считаем номер байта в массиве памяти дисплея
        offset  = y-((y/8)*8);          //считаем номер бита в этом байте

        data = LcdCache[index];         //берем байт по найденному индексу

		if ( mode == PIXEL_OFF )
			data &= ( ~( 0x01 << offset ) );    //редактируем бит в этом байте
		else if ( mode == PIXEL_ON )
			data |= ( 0x01 << offset );
		else if ( mode  == PIXEL_XOR )
			data ^= ( 0x01 << offset );
        
        LcdCache[index] = data;        //загружаем байт назад
        }

void LcdLine (int x1, int y1, int x2, int y2, uint8_t mode)      //Draws a line between two points on the display - по Брезенхейму
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

void LcdCircle(char x, char y, char radius, uint8_t mode)        //рисуем круг по координатам с радиусом - по Брезенхейму
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

/*        
void LcdBatt(int x1, int y1, int x2, int y2, uint8_t persent)    //рисуем батарейку с заполнением в %
        {
        uint8_t horizon_line,horizon_line2,i;
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

void LcdBar(int x1, int y1, int x2, int y2, uint8_t persent)    //рисуем прогресс-бар
        {
        uint8_t line;
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
void LcdBarLine(uint8_t line, uint8_t persent)    //рисуем прошресс-бар
        {
        LcdBar(0, (line-1)*7+1, 83, (line-1)*7+5, persent); 
        }
*/        
void LcdGotoXYFont (uint8_t x, uint8_t y)   //Sets cursor location to xy location. Range: 1,1 .. 14,6
        {
        if (x <= 14 && y <= 6) LcdCacheIdx = ( (int)(y) - 1 ) * 84 + ( (int)(x) - 1 ) * 6;
        }

void clean_lcd_buf (void)    //очистка текстового буфера
    {
    uint8_t i;
    
    for (i=0; i<14; i++) lcd_buf[i] = 0;
    } 

void LcdChr (int ch)    //Displays a character at current cursor location and increment cursor location
     {
         uint8_t i;
         
//        for ( i = 0; i < 5; i++ ) LcdCache[LcdCacheIdx++] = table[(ch*5+i)];    //выделяем байт-столбик из символа и грузим в массив - 5 раз
        for ( i = 0; i < 5; i++ )
			{
			#ifdef ATMEL_STUDIO
			LcdCache[LcdCacheIdx++] = pgm_read_byte(&ASCIItable[(ch*5+i)]);    //выделяем байт-столбик из символа и грузим в массив - 5 раз
			#else
            LcdCache[LcdCacheIdx++] = table[(ch*5+i)];    //выделяем байт-столбик из символа и грузим в массив - 5 раз
			#endif
			}
         LcdCache[LcdCacheIdx++] = 0x00;    //добавляем пробел между символами
     }
        
void LcdChrInv (int ch)    //Displays a character at current cursor location and increment cursor location
     {
         uint8_t i;
         
        for ( i = 0; i < 5; i++ ) LcdCache[LcdCacheIdx++] = ~(ASCIItable[(ch*5+i)]);    //выделяем байт-столбик из символа и грузим в массив - 5 раз
         LcdCache[LcdCacheIdx++] = 0xFF;    //добавляем пробел между символами
     }
/*
void LcdFlashString (uint8_t x, uint8_t y, flash uint8_t *str)    //Displays a string at current cursor location
    {
    unsigned int i;
    LcdGotoXYFont (x, y);
    for ( i = 0; i < 15-x; i++ )
        if (str[i])
            LcdChr (str[i]);
    }
*/

void LcdEmptyString (uint8_t y)    //Displays a string at current cursor location
    {
    LcdGotoXYFont (1, y);
    for ( uint8_t i = 0; i < 15; i++ )
		LcdChr (0x20);//20 space
    }

void LcdStringNoClean (uint8_t x, uint8_t y)    //Displays a string at current cursor location
	{
	uint8_t i;
	
	if (x > 14 || y > 6)
		return;
	LcdGotoXYFont (x, y);
	for ( i = 0; i < 15-x; i++ )
		if (lcd_buf[i])
			LcdChr (lcd_buf[i]);
	}
void LcdString (uint8_t x, uint8_t y)    //Displays a string at current cursor location
    {
    uint8_t i;
    
    if (x > 14 || y > 6)
		return;
    LcdGotoXYFont (x, y);
    for ( i = 0; i < 15-x; i++ )
		if (lcd_buf[i])
			LcdChr (lcd_buf[i]);
    clean_lcd_buf(); 
    }
void LcdString (uint8_t x, uint8_t y, char *buf)    //Displays a string at current cursor location
    {
    uint8_t i;
	int c;
    
    if (x > 14 || y > 6)
		return;
    LcdGotoXYFont (x, y);
    for ( i = 0; i < 15-x; i++ )
		{
		c	= buf[i];
		if (c == 0x00)
			break;
		LcdChr (c);
		}
    }
void LcdString (uint8_t x, uint8_t y, const char *buf PROGMEM, uint8_t length)    //Displays a string at current cursor location
    {
    uint8_t i;
    
    if (x > 14 || y > 6)
		return;
    LcdGotoXYFont (x, y);
    for ( i = 0; i < length; i++ )
		LcdChr (buf[i]);
    }
void LcdFlashString (uint8_t x, uint8_t y, const char *buf PROGMEM, uint8_t length)    //Displays a string at current cursor location
    {
    uint8_t i;
    
    if (x > 14 || y > 6)
		return;
    LcdGotoXYFont (x, y);
    for ( i = 0; i < length; i++ )
		LcdChr (pgm_read_byte(&(buf[i])));
    }
/*
void LcdStringUpdate (uint8_t x, uint8_t y)    //Displays a string at current cursor location
	{
	uint8_t k,i,dataByte;
//	unsigned int chr;
//	const char *ptr;
	
	if (x > 14 || y > 6) return;
	LcdSend(0x80 | x*6, LCD_CMD);        //команды установки указателя памяти дисплея на 0,0
	LcdSend(0x40 | y, LCD_CMD);
//	LcdGotoXYFont (x, y);
	for (i=0;i < 14-x;i++)
		{
		//chr	= lcd_buf[i]*5;
		//TODO: добавить *ptr
		//ptr	= &table[chr];//можно не оптимизировать - размер кода одинаков =(
		for ( k = 0; k < 5; k++ )
			{
			dataByte	= pgm_read_byte(&table[((lcd_buf[i]*5)+k)]);
			LcdSend(dataByte, LCD_DATA);
//			LcdCache[LcdCacheIdx++]	= dataByte;
			//LcdSend(pgm_read_byte(&table[((chr)+k)]), LCD_DATA);
			//LcdSend(pgm_read_byte(ptr++), LCD_DATA);
			}
		LcdSend(0x00,LCD_DATA);
//		if (lcd_buf[i]) LcdChr (lcd_buf[i]);
		}
	clean_lcd_buf(); 
	}
*/
void LcdStringInv (uint8_t x, uint8_t y)    //Displays a string at current cursor location
    {
    uint8_t i;
    
    if (x > 14 || y > 6) return;
    LcdGotoXYFont (x, y);
    for ( i = 0; i < 15-x; i++ ) if (lcd_buf[i]) LcdChrInv (lcd_buf[i]);
    clean_lcd_buf(); 
    }

void LcdChrBold (int ch)    //Displays a bold character at current cursor location and increment cursor location
     {
         uint8_t i;
         uint8_t a = 0, b = 0, c = 0;
         
         for ( i = 0; i < 5; i++ )
                 {
                 c = ASCIItable[(ch*5+i)];        //выделяем столбец из символа
                 
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

void LcdStringBold (uint8_t x, uint8_t y)    //Displays a string at current cursor location
    {
    uint8_t i;
    
    if (x > 13 || y > 5) return;
    LcdGotoXYFont (x, y);
    for ( i = 0; i < 14-x; i++ ) if (lcd_buf[i]) LcdChrBold (lcd_buf[i]); 
    clean_lcd_buf();
    }
    
void LcdChrBig (int ch)    //Displays a character at current cursor location and increment cursor location
     {
         uint8_t i;
         uint8_t a = 0, b = 0, c = 0;
         
         for ( i = 0; i < 5; i++ )
                 {
                 c = ASCIItable[(ch*5+i)];        //выделяем столбец из символа
                 
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

void LcdStringBig (uint8_t x, uint8_t y)    //Displays a string at current cursor location
    {
    uint8_t i;
    
    if (x > 14 || y > 5) return;
    LcdGotoXYFont (x, y);
    for ( i = 0; i < 15-x; i++ ) if (lcd_buf[i]) LcdChrBig (lcd_buf[i]); 
    clean_lcd_buf();
    }

#ifndef ATMEL_STUDIO
#pragma used-
#endif
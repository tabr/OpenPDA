// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//flash unsigned char STRING_PDA_TYPE_NORMAL_1[15]="лабораторный  ";
//flash unsigned char STRING_PDA_TYPE_NORMAL_2[15]="образец       ";

#define RAD_GRID_POS_X1                     0
#define RAD_GRID_POS_X2                     14
#define RAD_GRID_POS_Y1                     0
#define RAD_GRID_POS_Y2                     34
#define RAD_DISP_POS_X                      0
#define RAD_DISP_POS_Y                      36

#define PLAYER_RAD_DOSE_GRID_POS_X1         16
#define PLAYER_RAD_DOSE_GRID_POS_X2         30
#define PLAYER_RAD_DOSE_GRID_POS_Y1         0
#define PLAYER_RAD_DOSE_GRID_POS_Y2         34

//#define PLAYER_RAD_DOSE_DISP_POS_X          16
//#define PLAYER_RAD_DOSE_DISP_POS_Y          36

#define HEALTH_GRID_POS_X1                  32
#define HEALTH_GRID_POS_X2                  46
#define HEALTH_GRID_POS_Y1                  0
#define HEALTH_GRID_POS_Y2                  34
//#define HEALTH_DISP_POS_X                   32
//#define HEALTH_DISP_POS_Y                   36

#define PSY_HAZARD_GRID_POS_X1              48
#define PSY_HAZARD_GRID_POS_X2              62
#define PSY_HAZARD_GRID_POS_Y1              0
#define PSY_HAZARD_GRID_POS_Y2              34
//#define PSY_HAZARD_DISP_POS_X               48
//#define PSY_HAZARD_DISP_POS_Y               36
#define LCD_MENU_BAR_LINES_BOTTOM           34
#define LCD_MENU_BAR_LINES_TOP              1
#define LCD_MENU_BAR_LINES_NUM              LCD_MENU_BAR_LINES_BOTTOM-LCD_MENU_BAR_LINES_TOP

#define false   0
#define true    1
/*
только СТАТИЧНЫЕ данные/функции!!!
*/
#ifdef DEBUG
void Error(unsigned char num)
    {
    LcdClear();
    sprintf (lcd_buf, "error %03d",num); 
    LcdString(1, LCD_LINE_1);
    LcdUpdate();
    while(1)
    {}
    }
#endif
void UpdateTime()
    {
    if (TimeSecond>=60)
        {
        TimeSecond-=60;
        TimeMinute++;
        eventNewMinuteArrived();
        }
    if (TimeMinute>=60)
        {
        TimeMinute-=60;
        TimeHour++;
        }
    if (TimeHour >= 24)
        TimeHour-=24;
//    sprintf (lcd_buf, "%02u", TimeMinute); 
//    LcdString(12, 5);
//    sprintf (lcd_buf, "%02u", TimeSecond); 
//    LcdString(12, 6);
    }

void displayPercentBak(unsigned char GridPosX1, unsigned char GridPosX2, unsigned char GridPosY1, unsigned char GridPosY2, unsigned char Percent)
    {
    unsigned char Lines;
    unsigned char i;
//    bit tmpMode;


    NeedLcdUpdate=1;

    Lines       = (GridPosY2-GridPosY1+1-2);//общее кол-во линий


    GridPosX1+=2;
    GridPosX2--;
//    GridPosY2--;

    for (i=GridPosX1;i<GridPosX2;i++)//очистка
        {
        LcdLine(i, GridPosY2, i, GridPosY2-Lines, 0);
        }
    Lines = (Lines*Percent)/100;//заполненных линий
    for (i=GridPosX1;i<GridPosX2;i++)//заполнение
        {
        LcdLine(i, GridPosY2, i, GridPosY2-Lines, 1);
        }
    
//    tmpMode     = 1;
    /*
    for (i=0;i<Lines;i++)
        {
        if (tmpMode == 1 && i >= LinesFilled)
            tmpMode=0;
        LcdLine(GridPosX1+2, GridPosY2-1-i, GridPosX2-2, GridPosY2-1-i, tmpMode);
        }
    */
    }
//void displayPercent(unsigned char GridPosX1, unsigned char GridPosX2, unsigned char GridPosY1, unsigned char GridPosY2, unsigned char Percent)
void displayPercentBar(unsigned char GridPosX1, unsigned char Percent)
    {
    unsigned char Lines;
    unsigned char i;
    unsigned char GridPosX2;


    NeedLcdUpdate=1;

//    Lines       = (GridPosY2-GridPosY1+1-2);//общее кол-во линий 
    GridPosX2   = GridPosX1+14;


    GridPosX1+=2;
    GridPosX2--;
//    GridPosY2--;

    for (i=GridPosX1;i<GridPosX2;i++)//очистка
        {
        LcdLine(i, LCD_MENU_BAR_LINES_BOTTOM, i, LCD_MENU_BAR_LINES_TOP, 0);
        }
    Lines=LCD_MENU_BAR_LINES_NUM;//Нельзя переместить вниз, т.к. иначе, по видимому, результат перемножения 8мибитный!
    Lines = (Lines*Percent)/100;//заполненных линий
    for (i=GridPosX1;i<GridPosX2;i++)//заполнение по вертикале
        {
        LcdLine(i, LCD_MENU_BAR_LINES_BOTTOM, i, LCD_MENU_BAR_LINES_BOTTOM-Lines, 1);
        }
    
//                    sprintf (lcd_buf, "%02d",Player.currentHealth); 
//                    LcdString(12,6);
    }

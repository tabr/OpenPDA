// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "KBSymbols.h"





#define MAX_WRONG_PASS_COUNTER                          10
#define PLAYER_NAME_LENGTH                              = 16;

//flash unsigned char volatile pass[8]                    = {84,36,21,41,22,30,38,37};
eeprom unsigned char wrongPasswordCounter               = 0;
//eeprom unsigned char PlayerName[PLAYER_NAME_LENGTH]     = "";

void KBInit()
    {
    //на выход с подтягивающими резирсторами
//    KB_CLK_DDR     |= (1<<KB_CLK_BIT);
//    KB_CLK_PORT    |= (1<<KB_CLK_BIT);
//    KB_DATA_DDR    |= (1<<KB_DATA_BIT);
//    KB_DATA_PORT   |= (1<<KB_DATA_BIT);
    cbi(KB_CLK_DDR,         KB_CLK_BIT);
    cbi(KB_CLK_PORT,        KB_CLK_BIT);
    cbi(KB_DATA_DDR,        KB_DATA_BIT);
    cbi(KB_DATA_PORT,       KB_DATA_BIT);

    cbi(KB_CONNECTED_PORT, KB_CONNECTED_BIT);
    cbi(KB_CONNECTED_DDR,  KB_CONNECTED_BIT);//Вход

    if (wrongPasswordCounter > (1+MAX_WRONG_PASS_COUNTER))
        wrongPasswordCounter=0;
    }
/*
void KBDeInit()
    {
//    cbi(KB_CLK_DDR,    KB_CLK_BIT);
//    cbi(KB_CLK_PORT,   KB_CLK_BIT);
//    cbi(KB_DATA_DDR,   KB_DATA_BIT);
//    cbi(KB_DATA_PORT,  KB_DATA_BIT);
    }
*/
unsigned char KBRead()
    {
    unsigned char byte[3]={0,0,0},i,tmp;
    //глюк?? - данные читаются как:
    //byte, 240, byte
    //т.е. три раза!!!!!!
//    cbi(KB_CLK_DDR,    KB_CLK_BIT);//как вход  
    for (tmp=0;tmp<3;tmp++)
        {
        
        while(KB_CLK_PIN == 1){}
        while(KB_CLK_PIN == 0){}//start bit
        for (i=0; i < 8; i++)//можно убрать "tmp", увеличив "i"
            {
            while(KB_CLK_PIN == 1){}
            byte[tmp]    = byte[tmp] | (KB_DATA_PIN<<i);
            while(KB_CLK_PIN == 0){}
            }
        while(KB_CLK_PIN == 1){}
        while(KB_CLK_PIN == 0){}//parity bit

        while(KB_CLK_PIN == 1){}
        while(KB_CLK_PIN == 0){}//stop bit
        }
//    sprintf (lcd_buf, "%u/%u/%u",byte[0],byte[1],byte[2]);
//    LcdString(1,5);
//    sprintf (lcd_buf, "%u/%u/%u",byte[3],byte[4],byte[5]);
//    LcdString(1,6);
//    LcdUpdate();
    return byte[0];
    }
/*
void KBMainMenuPassLock()
    {
    bit needPassRedraw                      = 1;
    bit passwordValid                       = 1;
//    bit anyKeyPressed                       = 0;
    unsigned char charCounter               = 0;
    unsigned char KBSymbol                  = 0;
    unsigned char wrongPasswordCounterLocal = 0;
    
    
    wrongPasswordCounterLocal   = wrongPasswordCounter;

                sprintf (lcd_buf, "press any key");
                LcdString(1,1);
                sprintf (lcd_buf, "to continue...");
                LcdString(1,2);
                LcdUpdate();
                KBSymbol       = KBRead();
                LcdClear();

    while(1)
        {
//            sprintf (lcd_buf, "[%u]   ",KB_TMP_REG);
//            LcdString(1,6);
//            LcdUpdate();

//        if (KB_TMP_REG == 0)
//            break;
        if (wrongPasswordCounterLocal > MAX_WRONG_PASS_COUNTER)
            {
            LcdClear();
            sprintf (lcd_buf, "превышено число");
            LcdString(1,1);
            sprintf (lcd_buf, "попыток ввода");
            LcdString(1,2);
            sprintf (lcd_buf, "пароля[%u]",wrongPasswordCounterLocal);
            LcdString(1,3);
            sprintf (lcd_buf, "устройство заблокировано");
            LcdString(1,4);
            LcdUpdate();
            while(1){};
            }
//        if (needPassRedraw == 1 && anyKeyPressed == 1)
        if (needPassRedraw == 1)
            {
            LcdClear();
            sprintf (lcd_buf, "пароль:");
            LcdString(1,1);
            sprintf (lcd_buf, "[________]");
            LcdString(1,2);
            LcdUpdate();
            needPassRedraw  = 0;
            }
        if (KB_KEY_PRESSED)//начинаю прием
            {
//            KB_TMP_REG  = 0xFF;//счетчик не будет опускаться

//            if (anyKeyPressed == 0)
//                {
//                anyKeyPressed   = 1;
//                LcdClear();
//                sprintf (lcd_buf, "press any key");
//                LcdString(1,1);
//                sprintf (lcd_buf, "to continue...");
//                LcdString(1,2);
//                LcdUpdate();
//                KBSymbol       = KBRead();
//                continue;
//                }
            KBSymbol        = KBRead();
//            KB_CLK             = 0;// hold incoming data
            if (KBSymbol != pass[charCounter])
                passwordValid=0;
            if (KBSymbol == KB_KEY_ESC)
                {
                LcdClear();
                sprintf (lcd_buf, "пока =)"); 
                LcdString(1,5);
                LcdUpdate();
                delay_ms(1000);
                return;
                }
            sprintf (lcd_buf, "*");
            LcdString(2+charCounter,2);
            sprintf (lcd_buf, "%u/%c  ",KBSymbol,KBSymbols[KBSymbol]);
            LcdString(1,3);
            sprintf (lcd_buf, "символ:%u из 8",(1+charCounter)); 
            LcdString(1,4);
            sprintf (lcd_buf, "попытка:%u/%u",wrongPasswordCounterLocal,MAX_WRONG_PASS_COUNTER); 
            LcdString(1,5);
            LcdUpdate();
//            KB_CLK     = 1;// RELEASE incoming data
            charCounter++;
            }
        if (charCounter>7)
            {
            if (passwordValid == 1)
                {
                wrongPasswordCounter        = 0;
                wrongPasswordCounterLocal   = 0;
//                KBMainMenu();
                return;
                }
            sprintf (lcd_buf, "пароли не совпадают!"); 
            LcdString(1,1);
            LcdUpdate();
            charCounter                 = 0;
            needPassRedraw              = 1;
            passwordValid               = 1;
            wrongPasswordCounter++;
            wrongPasswordCounterLocal   = wrongPasswordCounter;
            delay_ms(1000);
            }
        }
    }
*/
unsigned char KBPressedToNumeric(unsigned char pressed)
    {
    switch (pressed)
        {
        case 22:
        return 1;

        case 30:
        return 2;

        case 38:
        return 3;

        case 37:
        return 4;

        case 46:
        return 5;

        case 54:
        return 6;        

        case 61:
        return 7;        

        case 62:
        return 8;        

        case 70:
        return 9;        

        default:
        return 0;
        }
    }
unsigned char KBEnterNumericValue()
    {
    unsigned char i=0;
    unsigned char value=0,pressed=0;
//    LcdClear();
//    sprintf (lcd_buf, "введи 3 цифры:");
//    LcdString(1,1);
    sprintf (lcd_buf, "[___] 000..255");
    LcdString(1,3);
    sprintf (lcd_buf, "   значение");
    LcdString(1,4);
    sprintf (lcd_buf, "  не должно");
    LcdString(1,5);
    sprintf (lcd_buf, "превышать 255");
    LcdString(1,6);
    LcdUpdate();
    for (i=0;i<3;i++)
        {
        while (KB_KEY_NOT_PRESSED){};
        pressed     = KBRead();
        pressed     = KBPressedToNumeric(pressed);
        sprintf (lcd_buf, "%u",pressed);
        LcdString(2+i,3);

        switch (i)
            {
            case 0:
            value   = pressed * 100;
            break;

            case 1:
            value   += pressed * 10;
            break;

            case 2:
            value   += pressed;
            break;
            }
        sprintf (lcd_buf, "value=[%u]",value);
        LcdString(1,3);
        LcdUpdate();
        }
    delay_ms(1000);
    return value;
    }
/*
void KBMainMenu()
    {
    unsigned char pressed   = 0;
    #asm("KBMainMenuStart:");
    LcdClear();
    sprintf (lcd_buf, "главное меню");
    LcdString(1,1);
    LcdUpdate();
    delay_ms(1000);

    LcdClear();
    sprintf (lcd_buf, "1) владелец");
    LcdString(1,1);

    sprintf (lcd_buf, "2) к-во апт");
    LcdString(1,2);

    sprintf (lcd_buf, "3) к-во антир");
    LcdString(1,3);

    sprintf (lcd_buf, "4) воскресить");
    LcdString(1,4);

    sprintf (lcd_buf, "5) нач иниц");
    LcdString(1,5);

    sprintf (lcd_buf, "9) далее");
    LcdString(1,6);
    LcdUpdate();
    while (KB_KEY_NOT_PRESSED){};
    pressed                 = KBRead();
    pressed                 = KBPressedToNumeric(pressed);
    switch (pressed)
        {
        case 1:
        KBChangeUser();
        break;

        case 2:
//        KBChangeFirstAid();
        break;

        case 3:
//        KBChangeAntiRad();
        break;

        case 4:
        PlayerSetAlive();
        Player.currentHealth    = PLAYER_START_HEALTH;
        LcdClear();
        sprintf (lcd_buf, "воскрешен!");
        LcdString(1,1);
        LcdUpdate();
        delay_ms(1000);
        break;

        case 5:
        PlayerInitDefault();
        break;

        case 9:
        KBMainMenu2();
        break;

        default:
        return;
        }
    #asm("RJMP KBMainMenuStart");
    }
void KBMainMenu2()
    {
    unsigned char pressed   = 0;
    #asm("KBMainMenu2Start:");
    LcdClear();
    sprintf (lcd_buf, "1) защита рад");
    LcdString(1,1);

    sprintf (lcd_buf, "2) сопрот рад");
    LcdString(1,2);

    sprintf (lcd_buf, "3) сопр аномалиям");
    LcdString(1,3);

    sprintf (lcd_buf, "4) к-во восст ХП");
    LcdString(1,4);

    sprintf (lcd_buf, "5) [уст ХП]");
    LcdString(1,5);

    sprintf (lcd_buf, "9) назад");
    LcdString(1,6);
    LcdUpdate();
    while (KB_KEY_NOT_PRESSED){};
    pressed                 = KBRead();
    pressed                 = KBPressedToNumeric(pressed);
    switch (pressed)
        {
        case 1:
        KBChangeDefenceRad();
        break;

        case 2:
        KBChangeResistanceRad();
        break;

        case 3:
//        KBChangeResistanceAno();
        break;

        case 4:
        KBChangeRegenHP();
        break;

        case 5:
        Player.currentHealth    = KBEnterNumericValue();
        break;

        default:
        return;
        }
    #asm("RJMP KBMainMenu2Start");
    }
*/
#ifndef STALKER_UI_CLASS_H
#define STALKER_UI_CLASS_H
#include "strings.h"
#include "STRClass.cpp"
class StalkerUI_Class//TODO
	{
	public:
		const static uint8_t HORIZONTAL_HEALTH_GRID_POS_X1          = 32;
		const static uint8_t HORIZONTAL_PLAYER_RAD_DOSE_GRID_POS_X1 = 16;
		const static uint8_t HORIZONTAL_LCD_MENU_BAR_LINES_BOTTOM   = 34;
		const static uint8_t HORIZONTAL_LCD_MENU_BAR_LINES_TOP      = 1;
		const static uint8_t HORIZONTAL_LCD_MENU_BAR_LINES_NUM      = (HORIZONTAL_LCD_MENU_BAR_LINES_BOTTOM - HORIZONTAL_LCD_MENU_BAR_LINES_TOP);
		enum UI_LCD_LINE
			{
			UI_LCD_LINE_0,
			UI_LCD_LINE_1,
			UI_LCD_LINE_2,
			UI_LCD_LINE_3,
			UI_LCD_LINE_4,
			UI_LCD_LINE_5,
			UI_LCD_LINE_SIZE
			};
		enum UI_MENU_BODY_LINE
			{
			UI_MENU_BODY_LINE_0,
			UI_MENU_BODY_LINE_1,
			UI_MENU_BODY_LINE_2,
			UI_MENU_BODY_LINE_3,
			UI_MENU_BODY_LINE_SIZE
			};

	
		//void DisplayHealthPercent(Percent_t percent);
		void DisplayRadiationDosePercent(Percent_t percent);
		void DisplayString(uint8_t line);
		void DisplayString(StalkerUI_Class::UI_LCD_LINE line);
		//void DisplayString(StalkerUI_Class::UI_LCD_LINE line, char* str);
		//void DisplayString(uint8_t x, StalkerUI_Class::UI_LCD_LINE line, char* str);
		//void DisplayString(uint8_t x, uint8_t line, char* str);
		//void DisplayString(StalkerUI_Class::UI_LCD_LINE line, const char* str PROGMEM);
		//void DisplayString(uint8_t x, StalkerUI_Class::UI_LCD_LINE line, const char* str PROGMEM);
		//void DisplayString(StalkerUI_Class::UI_LCD_LINE line, STR_POS pos);
		//void DisplayString(uint8_t x, StalkerUI_Class::UI_LCD_LINE line, STR_POS pos);

		void DisplayString(char* str, StalkerUI_Class::UI_LCD_LINE line=StalkerUI_Class::UI_LCD_LINE_0, uint8_t x=1);
		void DisplayString(STR_POS pos, StalkerUI_Class::UI_LCD_LINE line=StalkerUI_Class::UI_LCD_LINE_0, uint8_t x=1);
		void DisplayString(STRClass& Str, StalkerUI_Class::UI_LCD_LINE line=StalkerUI_Class::UI_LCD_LINE_0, uint8_t x=1);

        void DisplayEmptyString(StalkerUI_Class::UI_LCD_LINE line);
        void DisplayEmptyString(StalkerUI_Class::UI_MENU_BODY_LINE bLine);

        void DisplayMenuHead(STR_POS pos);
        void DisplayMenuHead(STRClass& str);
        void DisplayMenuHead(char* str);

        void DisplayMenuBottom(STR_POS pos, uint8_t x=1);
        void DisplayMenuBottom(STRClass& Str, uint8_t x=1);
        void DisplayMenuBottom(void);

        void ClearMenuBody(void);
        void ClearDisplay(void);

        void DisplayMenuBody(uint8_t line);
        void DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE bLine);
//      void DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE bLine, STR_POS pos);
        void DisplayMenuBody(STRClass* Str, StalkerUI_Class::UI_MENU_BODY_LINE bLine=UI_MENU_BODY_LINE_0, uint8_t x=1);
        void DisplayMenuBody(STR_POS pos, StalkerUI_Class::UI_MENU_BODY_LINE bLine=UI_MENU_BODY_LINE_0, uint8_t x=1);
        void DisplayMenuBody(char* str, StalkerUI_Class::UI_MENU_BODY_LINE bLine=UI_MENU_BODY_LINE_0, uint8_t x=1);
        //void DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE bLine, char* str);
        //void DisplayMenuBody(StalkerUI_Class::UI_MENU_BODY_LINE bLine, const char* str PROGMEM);
        //void DisplayMenuBodyF(StalkerUI_Class::UI_MENU_BODY_LINE bLine, STR_POS format_pos, ...);
//      void DisplayMenuBody(uint8_t line, const char* str PROGMEM);
        //void DisplayMenuBody(uint8_t x, StalkerUI_Class::UI_MENU_BODY_LINE bLine, const char* str PROGMEM);
        void DisplayEmptyBodyString(StalkerUI_Class::UI_MENU_BODY_LINE line);
        void RequestUpdate(void);
        //void ShowButtonDown1(void);

 		StalkerUI_Class::UI_LCD_LINE ToStringLine(uint8_t line);
 		StalkerUI_Class::UI_MENU_BODY_LINE ToMenuBody(uint8_t line);

		void ClearDisplayCache(void);
	protected:
	private:
		StalkerUI_Class::UI_LCD_LINE FromMenyBodyLine(UI_MENU_BODY_LINE line);
	};
#endif
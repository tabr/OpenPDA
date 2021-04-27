#ifndef LCD_CLASS_H
#define LCD_CLASS_H

class LcdClass
	{
	public:
		bool IsNeedUpdate;
		bool IsPlayerHealthNeedRedraw;
		bool IsPlayerRadDoseNeedRedraw;
		bool IsEnvRadLevelNeedRedraw;
		bool IsEnvPsyLevelNeedRedraw;
		bool IsMainScreenNeedRedraw;
		bool IsSuiteScreenNeedRedraw;
		
		char lcd_buf[32];

		void UpdateIfNeed(void);
		LcdClass(void);
	protected:
	private:
	};
#endif
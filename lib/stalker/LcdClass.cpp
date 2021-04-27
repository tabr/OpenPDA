// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
void LcdClass::UpdateIfNeed(void)
	{
	if (this->IsNeedUpdate)
		{
		this->IsNeedUpdate	= false;
		n3310LcdClass::RequestUpdate();
		}
	}
LcdClass::LcdClass(void)
	{
	this->IsNeedUpdate					= true;
	this->IsPlayerHealthNeedRedraw		= false;
	this->IsPlayerRadDoseNeedRedraw		= false;
	this->IsEnvRadLevelNeedRedraw		= false;
	this->IsEnvPsyLevelNeedRedraw		= false;
	this->IsMainScreenNeedRedraw		= false;
	this->IsSuiteScreenNeedRedraw		= false;
    memset(this->lcd_buf, 0, sizeof(this->lcd_buf));
	}
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * PDAMenu_MainInterface.cpp
 *
 * Created: 24.02.2016 4:47:03
 *  Author: tabr
 */ 
#include "PDAMenu_MainInterface.hpp"
bool PDAMenu_MainInterface::hasSpecs(void)
	{
	return (this->getSpecs() != 0);
	}
uint8_t PDAMenu_MainInterface::getSpecs(void)
	{
	return 0;
//	return this->specs;
	}
bool PDAMenu_MainInterface::hasSpec(uint8_t s)
	{
	if (this->hasSpecs())
		{
		if (this->getSpecs() & (1<<s))
			{
			return true;
			}
		}
	return false;
	}
bool PDAMenu_MainInterface::hasSubmenu(void)
	{
	return (this->selectedSubMenu != NULL);
	}
void PDAMenu_MainInterface::InsertBefore(PDAMenu_MainInterface* item)
	{
	this->GetPrev()->insertAfterThis(item);
	}
void PDAMenu_MainInterface::insertAfterThis(PDAMenu_MainInterface* item)
	{
	item->next			= this->next;
	//			item->prev			= this;
	//			this->next->prev	= item;
	this->next			= item;
	}
bool PDAMenu_MainInterface::isScrollable(void)
	{
	return false;
	}
bool PDAMenu_MainInterface::isUsable(void)
	{
	return false;
	}
bool PDAMenu_MainInterface::isSelectable(void)
	{
	return false;
	}
void PDAMenu_MainInterface::addSubMenu(PDAMenu_MainInterface* item)
	{
	if (this->selectedSubMenu == NULL)
		{
		this->selectedSubMenu	= item;
		}
	//item->parentMenu	= this;
  item->SetParentMenu(this);
	this->selectedSubMenu->GetPrev()->insertAfterThis(item);
	//this->getPrev()->insertAfterThis(item);
	}
PDAMenu_MainInterface* PDAMenu_MainInterface::GetPrev(void)
	{
	PDAMenu_MainInterface* prev	= this->next;
	while (1)
		{
		#ifdef DEBUG_BUILD
		sprintf (Lcd.lcd_buf,"1: %05u", rand());
		LcdString(1,LCD_LINE_1);
		n3310LcdClass::RequestUpdate();
		TODO("warning! may be infinity cycle");
		#endif
		if (prev->next == this)//если следующий элемент - текущий, значит он - предыдущий =)
			{
			return prev;
			}
		prev	= prev->next;
		}
	return NULL;
	}
PDAMenu_MainInterface::PDAMenu_MainInterface(void)
	{
	this->next				= this;
//	this->parentMenu		= NULL;
  this->SetParentMenu(NULL);
	this->selectedSubMenu	= NULL;
	}






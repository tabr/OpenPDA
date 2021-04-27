// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ItemInformationClass.hpp"

void ItemInformationClass::getHead(uint8_t id, char *data)
	{
	//UsableItem.at24c02_read_pages(UsableItemClass::ITEM_INFORMATION_HEAD_PAGE, 2, (uint8_t*)data);
	UsableItemTWI::readFromDevice(UsableItemClass::ITEM_INFORMATION_HEAD_ADDRESS, (2 * UsableItemClass::PAGE_SIZE), (uint8_t*)data);
	}
void ItemInformationClass::getBody(uint8_t id, uint8_t LCDLine, char *data)
	{
	//UsableItem.at24c02_read_pages(UsableItemClass::ITEM_INFORMATION_DATA_PAGE + (page<<1), 2, (uint8_t*)data);
	//UsableItem.at24c02_read_bytes(UsableItemClass::ITEM_INFORMATION_DATA_ADDRESS + (LCDLine * DeviceConfigClass::LCD_CHARS_IN_LINE), DeviceConfigClass::LCD_CHARS_IN_LINE, (uint8_t*)data);
	UsableItemTWI::readFromDevice(UsableItemClass::ITEM_INFORMATION_DATA_ADDRESS + (LCDLine * DeviceConfigClass::LCD_CHARS_IN_LINE), DeviceConfigClass::LCD_CHARS_IN_LINE, (uint8_t*)data);
	}
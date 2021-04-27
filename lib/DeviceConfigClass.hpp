#ifndef DEVICE_CONFIG_CLASS_H
#define DEVICE_CONFIG_CLASS_H

#include "typedefs.h"

//низкоуровневые параметры
class DeviceConfigClass
	{
	public:
		const static uint8_t MAX_ARTEFACT_SLOTS				= 5;
//		const static uint8_t MAX_SUITS						= 128;
		const static uint8_t MAX_ITEM_NAME_LENGTH			= 14;
		const static uint8_t LCD_CHARS_IN_LINE				= 14;
		const static uint8_t ITEM_NAME_CHAR_ARRAY_LENGTH	= MAX_ITEM_NAME_LENGTH+1;
		const static DeviceID_t ADDRESS_BROADCAST			= 0xFF;


		DeviceID_t GetID(void);
		void WriteNewDevID(DeviceID_t DID);
		bool IsAddressedToMe(DeviceID_t DID);
	protected:
	private:
		DeviceID_t DeviceID	= ADDRESS_BROADCAST;
	};
#endif
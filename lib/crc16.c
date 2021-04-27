// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "crc16.h"
uint16_t Crc16Update(uint16_t crc, uint8_t data)
    {
	#ifdef CRC_TABLE_RAM
		crc = (crc << 8) ^ Crc16Table[(crc >> 8) ^ data];
	#else
		crc = (crc << 8) ^ pgm_read_word(Crc16Table + ((crc >> 8) ^ data));
	#endif
 
    return crc;
    }
void updatePacketCRC(uint8_t * data, const uint8_t PacketSize)
	{
	UNION_UINT16 crc;
  #warning "[T] What byte order use RFM69HW crc?"
	crc.value_int=CRC16_INIT_VALUE;
	for (uint8_t i=0; i < (PacketSize-2); i++)
		{
		crc.value_int=Crc16Update(crc.value_int,data[i]);
		}
	data[PacketSize-2]	= crc.byte_field.h;
	data[PacketSize-1]	= crc.byte_field.l;
	}
bool isCRCMatch(uint8_t * data, const uint8_t PacketSize)
	{
	UNION_UINT16 crc;
	crc.value_int=CRC16_INIT_VALUE;
	for (uint8_t i=0; i < (PacketSize-2); i++)
		{
		crc.value_int=Crc16Update(crc.value_int,data[i]);
		}
	if (data[(PacketSize-2)]	!= crc.byte_field.h)
		{
		return false;
		}
	if (data[(PacketSize-1)]	!= crc.byte_field.l)
		{
		return false;
		}
	return true;
	}

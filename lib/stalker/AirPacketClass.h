#ifndef AIR_PACKET_CLASS_H
#define AIR_PACKET_CLASS_H
class AirPacketClass
	{
	public:
	const static uint8_t STRUCTURE_0X00_HEAD_H		= 0x00;
	const static uint8_t STRUCTURE_0X01_RESERVED	= 0x01;
	const static uint8_t STRUCTURE_0X02_DATA_H		= 0x02;
	const static uint8_t STRUCTURE_0X03_DATA_L		= 0x03;
	const static uint8_t STRUCTURE_0X04_CRC16_H		= 0x04;
	const static uint8_t STRUCTURE_0X05_CRC16_L		= 0x05;
	const static uint8_t STRUCTURE_SIZE				= 6;
	/*[0|0b00000111-packetType|0b11111000-reserved], [1]-reserved,[2,3]-DATA,[4,5]-CRC16*/

	const static uint8_t TYPEMASK					= 0b00000111;
	const static uint8_t TYPE_NONE					= 0 & TYPEMASK;
	const static uint8_t TYPE_ENVIRONMENT			= 1 & TYPEMASK;

	uint8_t packetContainer[STRUCTURE_SIZE];
	
	AirPacketClass (void)
		{
		for (uint8_t i=0;i<STRUCTURE_SIZE;i++)
			{
			this->packetContainer[i]=0;
			}
		}
	void setType(uint8_t type)
		{
		//TODO нуу сделать по-нормальному, с обработкой битовых полей
		type	= type & this->TYPEMASK;
		this->packetContainer[this->STRUCTURE_0X00_HEAD_H]	= type;
		}
	protected:
	private:
	};
#endif
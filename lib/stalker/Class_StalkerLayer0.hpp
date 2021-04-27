#ifndef CLASS_STALKER_LAYER_0_H
#define CLASS_STALKER_LAYER_0_H

#include "stalker/HAL.hpp"
#include "crc16.h"
#include "unionsFixed.h"
#include "radiomark.h"

//#define DEBUG_CRC_BYPASS	1
class Class_StalkerLayer0
	{
	public:
		const static uint8_t STRUCTURE_0X00_HEAD_H		= 0x00;//0b11111000 for multipacket - TransferID
		const static uint8_t STRUCTURE_0X01_VAR			= 0x01;//variable, for multipacket - PacketID
		const static uint8_t STRUCTURE_0X02_DATA_H		= 0x02;
		const static uint8_t STRUCTURE_0X03_DATA_L		= 0x03;
#ifdef RFM69_HW_CRC
		const static uint8_t STRUCTURE_SIZE				= 4;
#else //software crc
		const static uint8_t STRUCTURE_0X04_CRC16_H		= 0x04;
		const static uint8_t STRUCTURE_0X05_CRC16_L		= 0x05;
		const static uint8_t STRUCTURE_SIZE				= 6;
#endif
//		const static uint8_t STRUCTURE_SIZE				= 8;
//		#warning("STRUCTURE_SIZE changed")
//		const static uint8_t STRUCTURE_SIZE_NO_CRC		= STRUCTURE_SIZE-2;
//		const static uint8_t CRC_INCLUDED				= 0;
#ifdef RFM69_HW_CRC
//		const static uint8_t STRUCTURE_DATA_SIZE		= STRUCTURE_SIZE;
#else
		const static uint8_t STRUCTURE_DATA_SIZE		= STRUCTURE_SIZE-2; //used only in crc calculation
#endif
		/*[0|0b00000111-packetType|0b11111000-subtype], [1]-reserved,[2,3]-DATA,[4,5]-CRC16*/

		const static uint8_t PACKET_TYPEMASK			= 0b00000111;
		const static uint8_t PACKET_SUBTYPEMASK			= 0b11111000;//[0..247]
		
		enum PACKET_TYPES //as part of head
			{
			PACKET_TYPE_NONE							= (0 & PACKET_TYPEMASK),
			PACKET_TYPE_ENVIRONMENT						= (1 & PACKET_TYPEMASK),
			PACKET_TYPE_TIMEUPDATE						= (2 & PACKET_TYPEMASK),
			PACKET_TYPE_ADM_ACTION						= (3 & PACKET_TYPEMASK),
			PACKET_TYPE_250BYTES						= (4 & PACKET_TYPEMASK),
			PACKET_TYPE_RESERVED5						= (5 & PACKET_TYPEMASK),
			PACKET_TYPE_RESERVED6						= (6 & PACKET_TYPEMASK),
			PACKET_TYPE_RESERVED7						= (7 & PACKET_TYPEMASK),
			};
		
		//const static uint8_t TYPE_NONE					= (0 & TYPEMASK);
		//const static uint8_t TYPE_ENVIRONMENT			= (1 & TYPEMASK);
		//const static uint8_t TYPE_TIMEUPDATE			= (2 & TYPEMASK);

//		const static uint8_t TRANSMITTER_ID				= 2;

		
		Class_StalkerLayer0(void);
		PACKET_TYPES GetRXPacketType(void);
		uint8_t GetRXPacketSubType(void);
		uint8_t GetRXPacketVar(void);
		void SetTXPacketVar(uint8_t packetVar);
		void SetTXPacketType(PACKET_TYPES type);
		void SetTXPacketSubType(uint8_t subType);
//		void setID1(uint8_t id);							//Устаность ID (передатчика) - не должно тут находиться!
		void prepareTimeUpdatePacket(void);				//должна вызываться перед отправкой пакета
		void prepareEnvironmentPacket(void);			//должна вызываться перед отправкой пакета
		void prepareMultyBytePacket(uint8_t TransferID, uint8_t MID);				//должна вызываться перед отправкой пакета
		void prepareTXPacket(void);						//должна вызываться перед отправкой пакета
		void applyCalculatedCRC16(void);				//crc уже должен быть посчитан
		void sendPacket(void);
		void packetChanged (void);						//после изменения пакета стОит вызывать этот метод
		void receiveBegin (void);
		bool checkEnvironmentPacketAcception (void);	//проверяет, пришёл ли пакет и принимает его
		bool checkReceivedPacketCRC(void);
		bool isNewEnvPacketReceived(void);				//проверяет результат checkEnvironmentPacketAcception() [нихуя!!!]
		void getRSSI(void);
		void packetProcessed(void);						//если не вызвать, пакет так и будет висеть, новые не будут приниматься
//TODO: перекинуть в приват!!!
		void getEnvPacketAndRSSI(void);					//вызывается внутри checkEnvironmentPacketAcception()
		PACKET_TYPES getReceivedPacketType(void);
		void HardwareInitialization(void);				//Нужно вызывать в runlevel-e
//		bool isGoodPacketReceived(void);
//		void isGoodPacketReceived(bool value);
		bool isModuleReadyToWork(void);
		uint8_t* GetReceivedPacketData(void);
		uint8_t* GetReceivedPacket(void);
		void ClearFifo(void);
	uint8_t packetContainerTX[STRUCTURE_SIZE];
	uint8_t packetContainerRX[STRUCTURE_SIZE];
	//volatile uint8_t i;//nahua???
	volatile uint8_t RSSI;
	volatile uint8_t RSSIRaw;
	volatile uint8_t SignalPower;
	protected:
	private:
		//Class_HAL HAL;
//		uint8_t txBuf[STRUCTURE_SIZE];//TODO ДУБЛИРОВАНИЕ с "packetContainer"
		//uint8_t packetContainer[STRUCTURE_SIZE];
//		volatile bool isGoodPacketReceived;
//		bool isGoodPacketReceivedValue	= false;
		bool isDataInsideRM   = false;
		bool isRMInit         = false;
		bool isRMReadyToWork  = false;
		bool isRSSIReceived   = false;
		
#ifndef RFM69_HW_CRC //software crc
		UNION_UINT16_LITTLE_ENDIAN crc;
#endif
	};
#endif
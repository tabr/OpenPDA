#ifndef CLASS_STALKER_LAYER_1_H
#define CLASS_STALKER_LAYER_1_H

#include "Class_StalkerLayer0.hpp"

class Class_StalkerLayer1
	{
	public:
		const static uint16_t CACHE_SIZE			= 256;
		const static uint8_t BYTES_IN_PACKET		= 2;
		const static uint8_t PACKETS_TO_RECEIVE		= (CACHE_SIZE/BYTES_IN_PACKET);
		const static uint8_t MAX_MULTI_PACKET_ID	= (PACKETS_TO_RECEIVE - 1);
		const static uint8_t RCV_IDS_BUFFER_SIZE	= (PACKETS_TO_RECEIVE/8);
		enum MULTIBYTE_STRUCTURE
			{
			MULTIBYTE_STRUCTURE_TRANSFERID	= 0x00,
			MULTIBYTE_STRUCTURE_SIZE		= 0x01,
			MULTIBYTE_STRUCTURE_1			= 0x02,
			MULTIBYTE_STRUCTURE_2			= 0x03,
			MULTIBYTE_STRUCTURE_DATA_STARTS	= 0x04,
			MULTIBYTE_STRUCTURE_DATA_ENDS	= (CACHE_SIZE - 3),
			MULTIBYTE_STRUCTURE_CRC16_H		= (CACHE_SIZE - 2),
			MULTIBYTE_STRUCTURE_CRC16_L		= (CACHE_SIZE - 1),
			};

		void CleanCache(void);
		void programmStart(void);
		void HardwareInitialization(void);
		bool isEnvironmentActive(void);						//происходит приём пакета из радиомодуля
		bool CheckMultibytePacketReceived(void);
		uint8_t getReceivedEnvPacketID(void);
		uint8_t getReceivedEnvPacketSignalPower(void);
		Class_StalkerLayer1(void);

		Class_StalkerLayer0 L0;//TODO - private
	protected:
	private:
		uint8_t multiByteCache[CACHE_SIZE];
		uint8_t rcv_ids[RCV_IDS_BUFFER_SIZE];//16 bytes
	};
#endif
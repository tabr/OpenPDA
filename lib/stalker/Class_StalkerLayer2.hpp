#ifndef CLASS_STALKER_LAYER_2_H
#define CLASS_STALKER_LAYER_2_H

#include "stdint.h"
#include "HAL.hpp"
#include "Class_StalkerLayer1.hpp"


class Class_StalkerLayer2 : public ITimerListener
	{
	public:

		//const static uint8_t NUM_PACKET_PARAMETERS    = 2;//id,rssi
		//const static uint8_t BUF_ID_ID                = 0x00;
		//const static uint8_t BUF_ID_SIGNAL_POWER      = 0x01;
    enum L2_PACKET_STRUCTURE
      {
      L2_PACKET_STRUCTURE_BUF_ID_ID,
      L2_PACKET_STRUCTURE_BUF_ID_SIGNAL_POWER,
      L2_PACKET_STRUCTURE_SIZE
      };
    struct L2_Packet_struct
      {
      uint8_t ID;
      RM_SignalPower_t SignalPower;
      };

		Class_StalkerLayer1 L1;//TODO - private
		
		void TimerUpdateEvent (uint8_t msPassed);

		void cleanBuf(void);
		void programmStart(void);						//вызывается единожды при старте программы
		void EnvironmentLookAround(void);				//10ms - вызывается извне
		void EnvironmentProcess(void);					//40ms - вызывается извне
		void HardwareInitialization(void);
		Class_StalkerLayer2(void);
	protected:
	private:
//		uint8_t buf[Class_HAL::MAX_ENV_PACKETS_IN_TRANSACTION][Class_StalkerLayer2::NUM_PACKET_PARAMETERS];
		L2_Packet_struct buf[Class_HAL::MAX_ENV_PACKETS_IN_TRANSACTION];
		uint8_t bufPointer=0;
	};
#endif
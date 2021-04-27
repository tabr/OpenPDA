#include "rfm22b-23b_registers.h"
#include "rfm22bHAL.c"
#include "stalker/Driver_AnoRadRarioModuleInterfaceClass.h"

class Driver_AnoRadRarioModule : public Driver_AnoRadRarioModuleInterfaceClass
	{
	public:
		enum CURRENT_RX_STATES
			{
			CURRENT_RX_STATE_NONE,
			CURRENT_RX_STATE_AWAITING_RSSI,
			CURRENT_RX_STATE_RSSI_RECEIVED,
			CURRENT_RX_STATE_PACKET_RECEIVED,
			};
		const static uint8_t CFG_RSSI_INVERTED												= false;
	
		const static uint8_t TX_POWER_MAX				= 7;
		const static uint8_t RM_INIT_MAX_RETRIES		= 10;

		const static uint8_t TX_HEADER_0				= 0x00;
		const static uint8_t TX_HEADER_1				= 0x00;
		const static uint8_t TX_HEADER_2				= 0x00;
		const static uint8_t TX_HEADER_3				= 0x00;

		const static uint8_t SYNC_WORD_0				= 0x65;
		const static uint8_t SYNC_WORD_1				= 0xa6;
		const static uint8_t SYNC_WORD_2				= 0xa6;
		const static uint8_t SYNC_WORD_3				= 0x59;
		
		const static uint8_t GPIO_FUICTION_SELECT_POWER_ON_RESET_OUT						= 0b00000;
		const static uint8_t GPIO_FUICTION_SELECT_WAKEUP_TIMER_WUT_EXPIRED_OUT				= 0b00001;
		const static uint8_t GPIO_FUICTION_SELECT_LOW_BATTERY_DETECT_BELOW_THRESHHOLD_OUT	= 0b00010;
		const static uint8_t GPIO_FUICTION_SELECT_DIRECT_DIGITAL_INPUT_IN					= 0b00011;
		const static uint8_t GPIO_FUICTION_SELECT_EXT_INT_FALLING_EDGE_IN					= 0b00100;
		const static uint8_t GPIO_FUICTION_SELECT_EXT_INT_RASING_EDGE_IN					= 0b00101;
		const static uint8_t GPIO_FUICTION_SELECT_EXT_INT_STATE_CHANGE_IN					= 0b00110;
		const static uint8_t GPIO_FUICTION_SELECT_ADC_INPUT									= 0b00111;
		const static uint8_t GPIO_FUICTION_SELECT_RESERVED_ATNI_OUT							= 0b01000;
		const static uint8_t GPIO_FUICTION_SELECT_RESERVED_ATPI_OUT							= 0b01001;
		const static uint8_t GPIO_FUICTION_SELECT_DIRECT_DIGITAL_OUTPUT						= 0b01010;
		const static uint8_t GPIO_FUICTION_SELECT_RESERVED_DTO_OUT							= 0b01011;
		const static uint8_t GPIO_FUICTION_SELECT_RESERVED_ATNO_OUT							= 0b01100;
		const static uint8_t GPIO_FUICTION_SELECT_RESERVED_ATPO_OUT							= 0b01101;
		const static uint8_t GPIO_FUICTION_SELECT_REFERENCE_VOLTAGE_OUT						= 0b01110;
		const static uint8_t GPIO_FUICTION_SELECT_TX_RX_DATA_CLK_OUT						= 0b01111;
		const static uint8_t GPIO_FUICTION_SELECT_TX_DATA_INPUT_IN							= 0b10000;
		const static uint8_t GPIO_FUICTION_SELECT_EXTERNAL_RETRANSMISSION_REQUEST_IN		= 0b10001;
		const static uint8_t GPIO_FUICTION_SELECT_TX_STATE_OUT								= 0b10010;
		const static uint8_t GPIO_FUICTION_SELECT_TX_FIFO_ALMOSU_FULL_OUT					= 0b10011;
		const static uint8_t GPIO_FUICTION_SELECT_RX_DATA_OUT								= 0b10100;
		const static uint8_t GPIO_FUICTION_SELECT_RX_STATE_OUT								= 0b10101;
		const static uint8_t GPIO_FUICTION_SELECT_RX_FIFO_ALMOST_FULL_OUT					= 0b10110;
		const static uint8_t GPIO_FUICTION_SELECT_ANT1_SWITCH_OUT							= 0b10111;
		const static uint8_t GPIO_FUICTION_SELECT_ANT2_SWITCH_OUT							= 0b11000;
		const static uint8_t GPIO_FUICTION_SELECT_VALID_PREAMBLE_DETECT_OUT					= 0b11001;
		const static uint8_t GPIO_FUICTION_SELECT_INVALID_PREAMBLE_DETECT_OUT				= 0b11010;
		const static uint8_t GPIO_FUICTION_SELECT_SYNC_WORD_DETECTED_OUT					= 0b11011;
		const static uint8_t GPIO_FUICTION_SELECT_CLEAR_CHANNEL_ASSESSMENT_OUT				= 0b11100;
		const static uint8_t GPIO_FUICTION_SELECT_VDD										= 0b11101;
		const static uint8_t GPIO_FUICTION_SELECT_GND										= 0b11111;
		
		const static uint8_t STATUS_RXTX_FIFO_OVERFLOW										= 1<<7;
		const static uint8_t STATUS_RXTX_FIFO_UNDERFLOW										= 1<<6;
		const static uint8_t STATUS_RX_FIFO_EMPTY											= 1<<5;
		const static uint8_t STATUS_HEADER_ERROR											= 1<<4;
		const static uint8_t STATUS_FREQUENCY_ERROR											= 1<<3;
		const static uint8_t STATUS_STATE_IDLE												= 0b00;
		const static uint8_t STATUS_STATE_RX												= 0b01;
		const static uint8_t STATUS_STATE_TX												= 0b10;
		
		const static uint8_t PREAMBLE_LENGTH												= 0x06;
		
		
		uint8_t globalRSSI;//TODO: remove this
//		volatile bool RSSIReceived;//TODO: remove this
		
		void setPacketSize(uint8_t size);
		//uint8_t initRM(void);
		uint8_t sendPacket(void);
		void setTXPower(uint8_t pwr);
		void setTXBuffer(uint8_t* buf);
		void setRXBuffer(uint8_t* buf);
		uint8_t clearTXBuf(void);
		uint8_t clearRXBuf(void);
		void RFM22B_init4Kbps_w_crc(void);
		void RFM22B_init8kbps(void);
		void RFM22B_init16kbps(void);
		void RFM22B_init32kbps(void);
		void RFM22B_init64kbps(void);
		void RFM22B_init128kbps100khz(void);
		void RFM22B_init128kbps50khz(void);
		void RFM22B_init128kbps50khzNoHeader(void);
		void RFM22B_init128kbps40khz(void);
		void RFM22B_init128kbps30khz(void);
		void RFM22B_init(void);
		void sendBufferToRM(void);
		void ModeReady(void);
		uint8_t startTX(void);
		void RFM22B_reset(void);
		//bool packetReceived1(void);
		void TXMode(void);
		void IOInit(void);
		uint8_t HardwareInitialization(void);
		void getPacket(void);//уже сделано в прерывании
		void fetchPacket(void);//должен вызываться ТОЛЬКО из прерывания
		uint8_t fetchRSSIRaw(void);
		uint8_t getRSSIRaw(void);
		void receiveBegin(void);
		Driver_AnoRadRarioModule::TRX_STATE getState(void);
//		void PacketProcessed(void);
		volatile bool isPacketReceived(void);
		void RSSI_ISR(void);
		void ClearFifo(void);


		//TODO пустые методы
		void deviceEnable(void);
		void deviceDisable(void);
		void waitModeReady(void);
		
		Driver_AnoRadRarioModule(void)
			{
//			this->isRMInit				= false;
//			this->isRXBufInit			= false;
//			this->isTXBufInit			= false;
//			this->packetSize			= 0;
//			this->txPower				= 0;
			
//			this->globalRSSI			= 0;
//			this->RSSIReceived			= false;
			//RFM22B_ioinit();
			}
		//volatile CURRENT_RX_STATES RXState	= CURRENT_RX_STATE_NONE;
    uint8_t GetRSSIMax(void)
      {
      #warning "[T] know max RSSI"
      return 127;
      }
		uint8_t HACK_packetContainer[16];
		#warning "[T] HACK! packet cotnainer is fixed size 16 bytes"
	protected:
	private:
		void RFM22B_rxMode(void);
		void RFM22B_txMode(void);

		uint8_t packetSize=0;
		uint8_t txPower=0;
		bool isRMInit=false;
		bool isRXBufInit=false;
		bool isTXBufInit=false;
		//#warning "remove m_isPacket..."
		//bool m_isPacketReceived=false;
		uint8_t* rxBuffer=NULL;
		uint8_t* txBuffer=NULL;
		bool isEnvPacketReceived		= false;
	};

	

////////////////////////////////////////
//C++
////////////////////////////////////////

#ifndef DRIVER_ANORAD_RADIOMODULE_INTERFACE_CLASS
#define DRIVER_ANORAD_RADIOMODULE_INTERFACE_CLASS
class Driver_AnoRadRarioModuleInterfaceClass
	{
	public:
		enum TRX_STATE
			{
			TRX_STATE_UNKNOWN,
			TRX_STATE_IDLE,
			TRX_STATE_RECEIVING,
			TRX_STATE_TRANSMITTING,
			TRX_STATE_STANDBY
			};
		const static uint8_t TX_POWER_MAX;
		virtual void IOInit(void);
		virtual uint8_t HardwareInitialization(void);
		virtual uint8_t startTX(void);
		virtual void setTXPower(uint8_t pwr);
		virtual void deviceEnable(void);
		virtual void deviceDisable(void);
		virtual void waitModeReady(void);
		//virtual void PacketProcessed(void);
	protected:
	private:
	};
#endif //DRIVER_ANORAD_RADIOMODULE_INTERFACE_CLASS

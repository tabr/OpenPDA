#ifndef DRIVER_CLOCK_H
#define DRIVER_CLOCK_H
#include "stalker/drivers/Interface_Driver_Clock.hpp"
class Driver_Clock : public Interface_Driver_Clock
	{
	public:
		uint8_t FREQUENCY_MHZ;

		void SelectMaxExternal(void);
		void select_16x2_MHZExternal();
		void init_32MHZ_oscillator();
		Driver_Clock (void);
	protected:
	private:
	};
#endif
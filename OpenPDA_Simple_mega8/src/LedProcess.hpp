/*
 * LedProcess.h
 *
 * Created: 20.09.2017 17:58:32
 *  Author: tabr
 */ 


#ifndef LEDPROCESS_H_
#define LEDPROCESS_H_

class LedProcessClass
	{
	public:
		void Process(void);
	protected:
	private:
		uint8_t greenLedtimer=3;
	};


#endif /* LEDPROCESS_H_ */
#ifndef STALKER_H
#define STALKER_H

class STALKER //TODO
	{
	
	public:
	//void Init(void);
	void InitRTC(void);
	void InitInterrupts(void);
	void NewPacketAccepted(void);
//	void programmStart(void);
	void checkEnvironmentPacketAcception(void);
	static void PlayPlayerDeathSound(void);
	//StalkerTask1 a;
	};
#endif
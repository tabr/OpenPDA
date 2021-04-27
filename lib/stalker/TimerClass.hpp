#ifndef TIMER_CLASS_H
#define TIMER_CLASS_H

//#include <stdint.h>
//#include <stddef.h>


#include "Runnable.hpp"
class ITimerListener
	{
	public:
		virtual void TimerUpdateEvent (uint8_t msPassed)=0;
	protected:
	private:
	};
class ITimer
	{
	public:
		virtual void RegisterListener (ITimerListener* Listener)=0;
	protected:
	private:
	};
struct ITimerContainer 
	{
	ITimerListener* regtisteredObject;//	= NULL;
	ITimerContainer* nextObject;//	= NULL;
	ITimerContainer(): regtisteredObject(NULL), nextObject(NULL){};
	};
class TimerMSClass : public ITimer
	{
	public:
		TimerMSClass(void) : m_msPassed(0)
			{
			this->lastRegtisteredObject	= &this->regtisteredObjects;
			}
		void RegisterListener(ITimerListener* Listener)
			{
			this->lastRegtisteredObject->regtisteredObject	= Listener;

			this->lastRegtisteredObject->nextObject	= new ITimerContainer;
			
			this->lastRegtisteredObject				= this->lastRegtisteredObject->nextObject;
			};
		/*volatile*/ void TimerUpdateMS (uint8_t msPassed);
		void CheckPassed(void);
	protected:
	private:
		TimerMS_t m_msPassed;//=0;
		ITimerContainer regtisteredObjects;
		ITimerContainer* lastRegtisteredObject;
		//if .nextObject	== NULL this mean this is the last object
	};

/*
class ITimerListenerImplementation : public ITimerListener
	{
	public:
		virtual void TimerUpdateEvent (uint8_t msPassed);
		
	protected:
	private:
		ITimerListenerImplementation* nextItem = NULL;
	};*/
//АХТУНГ!!! Нельзя 2 раза одну и ту же задачу помеcтить в очередь!
//т.к. они будут ссылаться на разные последующие объекты
//и при проходе всё, что между ними, потеряется
/*
class TimerClass 
	{
	public:
		class NullTaskClass : public Runnable
			{
			public:
			void Task(void){}
			uint8_t getRepeatTime()
				{
				return 0;
				}
			}NullTask;
		enum TIMER_TIMINGS
			{
			TIME_REALTIME				= 1,
			TIME_10MS					= 1,
			TIME_30MS					= 3,
			TIME_40MS					= 4,
			TIME_50MS					= 5,
			TIME_100MS					= 10,
			TIME_150MS					= 15,
			TIME_1000MS					= 100,
			};
//		const static uint8_t PRG_BUFFER_SIZE			= 20;

		volatile void Update (TIMER_TIMINGS ms10);		//вызывается из прерывания - обработка времени. TODO int???
		void checkPassed(void);
		void addTaskFirst(Runnable& func);
		void addTaskLast(Runnable& func);
		inline void addTask(Runnable& func);//default - at the start
		//void removeTask(Runnable& func);
		TimerClass(void);
 
 	protected:
	private:
		//volatile register
		uint8_t ms10Counter;
		void* linkedObject=NULL;
	};
*/
#endif
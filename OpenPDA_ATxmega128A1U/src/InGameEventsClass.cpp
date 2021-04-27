// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * InGameEventsClass.cpp
 *
 * Created: 2015-10-16 01:34:42
 *  Author: tabr
 */ 
#include "InGameEventsClass.hpp"
/*
void InGameEventsClass::InGameEventsClassTask1::Task(void)
	{
	//InGameEvents.checkState();
	((InGameEventsClass*)this->GetLinkedObject())->checkState();
	}*/
void InGameEventsClass::TimerUpdateEvent (uint8_t msPassed)
	{
	static uint16_t checkState_msCounter=0;
	checkState_msCounter+=msPassed;
	if (checkState_msCounter >= 1000)
		{
		checkState_msCounter -= 1000;
		this->checkState();
		}
	}
void InGameEventsClass::checkState(void)
	{
	for (EventID_t EID=0; EID < this->registered; EID++)
		{
		switch (this->getState(EID))
			{
			case EVENT_STATE_ACTIVE:
				{
				if (!(this->isEventTimeArrived(EID)))
					{
					this->setState(EID, EVENT_STATE_INACTIVE);
//					this->period[EID]	= this->parameters[EID][this->PARAMETER_PERIOD];//ре-инициализирую
					this->pool[EID].ReInit();//ре-инициализирую
					continue;//возвращаемся в начало, т.к. состояние сменилось
					}
				//крутим период
//				if (--this->period[EID] == 0)//пришло время =)
				if (--this->pool[EID].periodCounter == 0)//пришло время =)
					{
					//this->period[EID]	= this->parameters[EID][this->PARAMETER_PERIOD];//ре-инициализирую
					//this->pool[EID]->Task();
          this->pool[EID].ReInit();//ре-инициализирую
					this->pool[EID].callback->Task();
					}
				}
			break;

			case EVENT_STATE_INACTIVE:
				{
				if (this->isEventTimeArrived(EID))
					{
					this->setState(EID, EVENT_STATE_ACTIVE);
//					this->period[EID]	= 0+1;//чтобы стартанул сразу
					this->pool[EID].periodCounter	= 0+1;//чтобы стартанул сразу
					continue;//возвращаемся в начало, т.к. состояние сменилось
					}
				}
			break;

			default:
				{
				//TODO
				}
			break;
			}
		}
	}
void InGameEventsClass::setState(EventID_t EID, EVENT_STATE s)
	{
	this->pool[EID].state	= s;
	}
InGameEventsClass::EVENT_STATE InGameEventsClass::getState(EventID_t EID)
	{
	return this->pool[EID].state;
	}
bool InGameEventsClass::isEventTimeArrived(EventID_t EID)//check START >= currentTime >= END
	{
	EventsParemeter_t* selectedEventParameters	= this->pool[EID].parameters;
	
	if (TimeRTC.AsMinutesPassed(selectedEventParameters[this->PARAMETER_START_H], selectedEventParameters[this->PARAMETER_START_M]) <= TimeRTC.AsMinutesPassed() &&\
	 TimeRTC.AsMinutesPassed() <= TimeRTC.AsMinutesPassed(selectedEventParameters[this->PARAMETER_END_H], selectedEventParameters[this->PARAMETER_END_M]))
		{
		return true;
		}
	/*
	if (selectedEventParameters[this->PARAMETER_START_H] <= TimeRTC.hour && TimeRTC.hour <= selectedEventParameters[this->PARAMETER_END_H])
		{
		if (selectedEventParameters[this->PARAMETER_START_M] <= TimeRTC.minute && TimeRTC.minute <= selectedEventParameters[this->PARAMETER_END_M])
			{
			return true;
			}
		}*/
	return false;
	}
EventID_t InGameEventsClass::registerNew(uint8_t startH, uint8_t startM, uint8_t endH, uint8_t endM, EventsPeriod_t periodSec, Runnable& callback)
	{
	//			this->pool[this->registered][PARAMETER_CALLBACK]		= static_cast<void*>(&callback);
	//			this->pool[this->registered][PARAMETER_PERIOD]			= static_cast<void*>(&callback);
	this->pool[this->registered].callback							= &callback;
	this->pool[this->registered].parameters[PARAMETER_PERIOD]	= periodSec;
	this->pool[this->registered].parameters[PARAMETER_START_H]	= startH;
	this->pool[this->registered].parameters[PARAMETER_START_M]	= startM;
	this->pool[this->registered].parameters[PARAMETER_END_H]		= endH;
	this->pool[this->registered].parameters[PARAMETER_END_M]		= endM;
	
//	this->period[this->registered]							= 0;
	this->pool[this->registered].periodCounter							= 0;
	
	this->setState(this->registered, EVENT_STATE_INACTIVE);

	this->registered++;
	return (this->registered - 1);
	}
EventsPeriod_t* InGameEventsClass::getParameters(EventID_t EID)
	{
	return this->pool[EID].parameters;
	}
//InGameEventsClass::InGameEventsClass(void)
//	{
	//this->TInGameEventsClass1secCheckStateTask.SetLinkedObject(this);
//	}
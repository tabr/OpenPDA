// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * EventSystemClass.cpp
 *
 * Created: 28.04.2016 0:11:08
 *  Author: tabr
 */ 
/*
void EventSystemClass::registerUserEvent(void (*pf)(void*), EventSystemSpace::EVIDS evID)
	{
	//		this->programms[evID][this->counters[evID]]		= pf;
	this->programms[this->counter]					= pf;
	this->parameters[this->counter]					= evID;
	this->counter++;
	}
*/
void EventSystemClass::RegisterUserEvent(EventSystemSpace::EVIDS evID, EventArrivedInterface* EListener)
	{
	//		this->programms[evID][this->counters[evID]]		= pf;
	this->programms[this->counter]					= EListener;
	this->parameters[this->counter]					= evID;
	this->counter++;
	}
void EventSystemClass::ExternalEventArrived(EventSystemSpace::EVIDS evID, void* E_Parameters)
	{
	#ifdef DEBUG_USART_EVENT_SYSTEM
		sprintf (USARTBuffer,"[eventArrived] evid: %03u param*:%05u\r\n",evID, ((uint8_t*)E_Parameters));
		sendString(USARTBuffer);
	#endif
	for (uint8_t i=0;i<this->counter;i++)
	//		for (uint8_t i=this->counter; i>0; i++)
		{
		if (this->parameters[i] == evID || this->parameters[i] == EventSystemSpace::EVIDS::EVID_ANY )
			{
//			this->programms[i](parameters);
			this->programms[i]->EventArrived(evID, E_Parameters);
			}
		}
	}
EventSystemClass::EventSystemClass(void)
	{
	this->counter=0;
	}
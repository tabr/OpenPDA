// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


/*volatile*/ void TimerMSClass::TimerUpdateMS (uint8_t msPassed)
	{
  if ((this->m_msPassed+msPassed) > 255)
    {
    this->m_msPassed=255;
    }
  else
    {
	  this->m_msPassed+=msPassed;
    }
	}
void TimerMSClass::CheckPassed(void)
	{
	TimerMS_t msPassed		= this->m_msPassed;
	this->m_msPassed		-= msPassed;
	ITimerContainer* workingObject		= &this->regtisteredObjects;
	while (workingObject->nextObject != NULL)
		{
		workingObject->regtisteredObject->TimerUpdateEvent(msPassed);
		workingObject	= workingObject->nextObject;
		TODO("may be infinity cycle");
		}
	}

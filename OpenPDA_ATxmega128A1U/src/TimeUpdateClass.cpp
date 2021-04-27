// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * TimeUpdateClass.cpp
 *
 * Created: 24.12.2017 1:35:06
 *  Author: tabr
 */ 
void TimeUpdateClass::TimerUpdateEvent (uint8_t msPassed)
  {
  static uint16_t oneSecond_msCounter=0;
  oneSecond_msCounter+=msPassed;
  if (oneSecond_msCounter < 1000)
    {
    return;
    }
  if (this->updateTimer > 0)
    {
    updateTimer--;
    }
  }
void TimeUpdateClass::RequestUpdate (TimeHour_t h, TimeMinute_t m, TimeSecond_t s)
  {
  //if (this->updateTimer == 0)
    {
    TimeRTC.SetTime(h, m, s);
    this->updateTimer = TIMER_RELOAD_VALUE;

    this->timeSyncReceivedAtLastOnce=true;

    #ifdef DEBUG_USART_CODES
      USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_TIME_UPDATED);
    #endif // DEBUG_USART_CODES
    }
  }
bool TimeUpdateClass::IsTimeSyncReceivedAtLastOnce(void)
  {
  return this->timeSyncReceivedAtLastOnce;
  }
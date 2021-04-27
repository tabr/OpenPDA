// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * LedProcess.cpp
 *
 * Created: 04.11.2015 0:48:14
 *  Author: tabr
 */ 

void LedProcessClass::Process(void)
	{
	if (Player.IsZombie())
		{
		if (TimeRTC.second & 1)
			{
			RedLEDPin::SetOutHigh();
			GreenLEDPin::SetOutLow();
			}
		else
			{
			RedLEDPin::SetOutLow();
			GreenLEDPin::SetOutHigh();
			}
		}
//	else if (isPlayerDead)
	else if (Player.IsDead())
		{
		if (TimeUpdate.IsTimeSyncReceivedAtLastOnce() == false)
			{
			if (TimeRTC.second & 1)
				{
				RedLEDPin::SetOutLow();
				}
			else
				{
				RedLEDPin::SetOutHigh();
				}
			if (TimeRTC.second & 2)
				{
				GreenLEDPin::SetOutHigh();
				}
			else
				{
				GreenLEDPin::SetOutLow();
				}
			}
		else if (InGameEvent_SleepTimer > 0)
			{
			
			}
		else
			{
			RedLEDPin::SetOutToggle();
			if (Player.IsAwaitingGraveyard())
				{
				GreenLEDPin::SetOutToggle();
				}
			}
		}
	else//Player Alive
		{
		//ХАК!!!
		//if (PlayerInSafeShelterTimer == (SAFE_SHELTER_TIMER/2))
		if (Player.IsLeavingSafeZone())
			{
			GreenLEDPin::SetOutLow();
			}
		//if (isPlayerInSafeShelterNearTransmitter())//таймер пребывания в безопасном убежище (15сек)
		if (Player.IsInSafeShelterNearTransmitter())//таймер пребывания в безопасном убежище (15сек)
			{
			GreenLEDPin::SetOutHigh();
			}
		else
			{
			if (++greenLedtimer >= 4)
				{
				greenLedtimer	= 0;
				GreenLEDPin::SetOutLow();
				}
			else if (greenLedtimer == 1 && Player.GetHealthPercent() < 50)
				{
				GreenLEDPin::SetOutHigh();
				}
			else if (greenLedtimer == 2)
				{
				GreenLEDPin::SetOutLow();
				}
			else if (greenLedtimer == 3)
				{
				GreenLEDPin::SetOutHigh();
				}
			/*
			else if (greenLedtimer == 200)
				{
				GreenLEDPin::setOutHigh();
				}
			*/
			}
		}
	}


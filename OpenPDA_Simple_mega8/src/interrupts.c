// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * interrupts.h
 *
 * Created: 09.11.2015 1:30:24
 *  Author: tabr
 */ 


//#ifndef INTERRUPTS_H_
//#define INTERRUPTS_H_


ISR(INT1_vect)
	{
//	hui++;
	
	
	//sei();
	Hack_RcvMayStuckTimer_Reload();
	HAL.EnvironmentRarioModule.RSSI_ISR();
	//return false;
	
	
	
	//HAL.EnvironmentRarioModule.getRSSI();
	
	
	/*
	if (SPILockedByMain)
		{
		NeedRSSIGet	= true;
		return;
		}
	SPILockedByInterupt		= true;
	HAL.EnvironmentRarioModule.globalRSSI			= HAL.EnvironmentRarioModule.fetchRSSIRaw();
	HACK_RCV_RESTART;
	*/
//	cbi(GICR,INT1);
//	HAL.EnvironmentRarioModule.getPacket();
	/*
	if (StalkerLayer2.L1.L0.checkReceivedPacketCRC())
		{
		GoodPacketCounter++;
		}
	else
		{
		HAL.EnvironmentRarioModule.receiveBegin();
		}
	
	*/
	//SPILockedByInterupt	= false;
	/*
	if (SPILocked || HAL.EnvironmentRarioModule.RSSIReceived)
		{
		return;
		}
	SPILocked		= true;
	//HAL.EnvironmentRarioModule.globalRSSI			= 1;
	SPILocked		= false;
	HAL.EnvironmentRarioModule.RSSIReceived			= true;
	//rssi++;
	*/
	}
ISR(TIMER1_OVF_vect) //inactive
	{
	// Reinitialize Timer1 value
	TCNT1H=0xD8F0 >> 8;
	TCNT1L=0xD8F0 & 0xff;
	
	/*
	if (++oneSecCounter == 100)//1 sec
		{
		oneSecCounter	= 0;
		oneSecPassed	= true;
//		test++;
		}
	if (packetProcessCounter < 15)
		{
		packetProcessCounter++;
		}
	if (--buzzerOnCounter == 0)
		{
		BuzzerPin::setOutLow();
		BuzzerPin_H::setOutLow();
		}*/
	}

// Timer2 overflow interrupt service routine
ISR(TIMER2_OVF_vect)//10ms
	{
	static uint8_t timeShift		= 0;
	static uint8_t oneSecCounter	= 0;
	static uint8_t ms100Counter		= 0;
	static uint8_t soundDeathWait	= 0;
	static uint8_t sleepLedCnt		= 0;
	
	
	sei();//enable RM ISR
	
	#ifdef DEBUG_USART_CODES
		  USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_TIME_ISR, DEBUG_USART_LOGLEVEL_DEBUG);
	#endif // DEBUG_USART_CODES
	// Reinitialize Timer2 value
	//TCNT2=0x00;//~32.768ms
	if (++timeShift < 8)
		{
		TCNT2=0xB2;//~10ms
		//9.984ms (7x16=112)
		}
	else
		{
		timeShift=0;
		TCNT2=0xB1;//~10ms
		//10.112ms
		}
	if (!IsInSleepMode())
		{
		TimerMS.TimerUpdateMS(10);//TODO: do not run in sleep mode!
		}
	if (InGameEvent_SleepTimer > 0 && TimeUpdate.IsTimeSyncReceivedAtLastOnce())
		{
		if (++sleepLedCnt == 0)
			{
			//sleepLedCnt=0;
			GreenLEDPin::SetOutHigh();
			RedLEDPin::SetOutHigh();
			}
		else if (sleepLedCnt == 1)
			{
			GreenLEDPin::SetOutLow();
			RedLEDPin::SetOutLow();
			}
		}
	
	if (++ms100Counter == 10)//100ms
		{
		ms100Counter=0;
		if (Hack_RcvMayStuckTimer > 0)
			{
			Hack_RcvMayStuckTimer--;
			}

		//PacketShouldProcess	= true;
		//setPacketShouldProcess();

		if (++oneSecCounter == 10)//1 sec // moved to Player
			{
			oneSecCounter	= 0;
			oneSecPassed	= true;
			//		test++;
			}
		if (soundDeathStage > 0)//100ms tick
			{
			#ifdef DEBUG_USART_CODES
				USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_PROCESSING_DEATH_SOUND);
			#endif // DEBUG_USART_CODES
			//GreenLEDPin::SetOutToggle();
			switch (soundDeathStage)
				{
				case 1:
					{
					BuzzerActivate(130);//130ms
					soundDeathStage++;//wait 128+1000=1128ms
					soundDeathWait=0;
					}
				break;
				
				case 2:
					{
					if (++soundDeathWait == 11)
						{
						soundDeathWait=0;
						BuzzerActivate(130);//130ms
						soundDeathStage++;//wait 128+1200=1328ms
						}
					}
				break;
				
				case 3:
					{
					if (++soundDeathWait == 13)
						{
						soundDeathWait=0;
						BuzzerActivate(130);//130ms
						soundDeathStage++;//wait 128+1400=1528ms
						}
					}
				break;
				
				case 4:
					{
					if (++soundDeathWait == 15)
						{
						soundDeathWait=0;
						BuzzerOn();//7500ms
						soundDeathStage++;//wait 7500ms
						}
					}
				break;
				
				case 5:
					{
//						BuzzerOn();//7500ms
					if (++soundDeathWait == 75)
						{
						//RedLEDPin::setOutHigh();
						soundDeathWait=0;
						BuzzerOff();//7500ms
						soundDeathStage=0;
						}
					}
				break;
				
				default:
					{
					soundDeathWait=0;
					BuzzerOff();//7500ms
					soundDeathStage=0;
					}
				break;
				}
			}
		}
	/*if (packetProcessCounter < 15)
		{
		packetProcessCounter++;
		}*/
	if (buzzerOnCounter > 0)
		{
		if (--buzzerOnCounter == 0)
			{
			BuzzerOff();
			}
		}
	}


//#endif /* INTERRUPTS_H_ */
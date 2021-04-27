// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * RadiomarkClass.cpp
 *
 * Created: 24.12.2017 4:46:05
 *  Author: tabr
 */ 
RadiomarkInstanceClass::RadiomarkInstanceClass(void)
	{
	
	}
RadiomarkInstanceClass::RadiomarkInstanceClass(RadiomarkID_t RID, RadiomarkType_t RType, RadiomarkParameter_t RP1, RadiomarkParameter_t RP2, RadiomarkParameter_t RP3, RadiomarkParameter_t RP4)
	{
	this->RID   = RID;
	this->RType = RType;
	this->RP1   = RP1;
	this->RP2   = RP2;
	this->RP3   = RP3;
	this->RP4   = RP4;
	}

RadiomarkID_t RadiomarkInstanceClass::GetID(void)
	{
	return this->RID;
	}
RadiomarkID_t RadiomarkInstanceClass::GetType(void)
	{
	return this->RType;
	}
RadiomarkParameter_t RadiomarkInstanceClass::GetParameter1(void)
	{
	return this->RP1;
	}
RadiomarkParameter_t RadiomarkInstanceClass::GetParameter2(void)
	{
	return this->RP2;
	}
RadiomarkParameter_t RadiomarkInstanceClass::GetParameter3(void)
	{
	return this->RP3;
	}
RadiomarkParameter_t RadiomarkInstanceClass::GetParameter4(void)
	{
	return this->RP4;
	}
void RadiomarkInstanceClass::SetSignalPower(RM_SignalPower_t newSignalPower)
  {
  this->SignalPower = newSignalPower;
  }
RM_SignalPower_t RadiomarkInstanceClass::GetSignalPower(void)
  {
  return this->SignalPower;
  }
Percent_t RadiomarkInstanceClass::GetSignalPowerPercent(void)
  {
  //HAL.EnvironmentRarioModule.GetRSSIMax();
  uint16_t percent  = 0;
  percent           = this->GetSignalPower() * 100;
  percent           = percent/HAL.EnvironmentRarioModule.GetRSSIMax();
  return percent;
  }

 void RadiomarkRadiationAnomayClass::ProcessSignal(uint8_t signalPower)
  {
  int8_t RadiationMultiplier	= this->GetRadiationMultiplier();
  LogClass::Log(LogClass::MESSAGES::MESSAGE_RADIOMARK_RADANO__PROCESS_SIGNAL__ENTER, signalPower);

  if (RadiationMultiplier != 0)
    {
    LogClass::Log(LogClass::MESSAGES::MESSAGE_RADIOMARK_RADANO__PROCESS_SIGNAL__RAD_MUL, RadiationMultiplier);

		uint16_t itmp	= 0;
		if (RadiationMultiplier > 0)
			{
			itmp	= ((uint8_t)RadiationMultiplier) * signalPower;//multiplier * [rssi/2]
			}
		else
			{
			itmp	= signalPower/(-RadiationMultiplier);
			}
		if (itmp> 255)
			{
			itmp=255;
			}
    LogClass::Log(LogClass::MESSAGES::MESSAGE_RADIOMARK_RADANO__PROCESS_SIGNAL__ITMP, itmp);
		Env.RadLevelSetFilter((uint8_t)itmp);
		}
  //return;
	if (this->GetAnomalyID() > 0)
		{
		//sprintf (USARTBuffer,"processing Anomaly... type: %03d SignalPower[%03d] killLvl[%03d]\r\n",RadAno.GetAnomalyType(), SignalPower, RadAno.GetAnomalyKillLevel());
		//sendString(USARTBuffer);
		if (signalPower > this->GetAnomalyKillLevel())
			{
      #ifdef DEBUG_USART_CODES
      	USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_KILLING_PLAYER_BY_ANOMALY_KILL_LEVEL);
      #endif // DEBUG_USART_CODES
			//PlayerDie();
			//sendString((char*)"Anomaly kills");
			//RadAno.GetAnomalyType()
//			Player.Kill(TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC);
			Player.Kill(Anomaly.getDamageSource(this->GetAnomalyID()));
//			sprintf (USARTBuffer,"anomaly kills");
//			sendString(USARTBuffer);
//			#warning("anomaly kills as generic");
			}
		else if (signalPower > this->GetAnomalySkipLevel())
			{
			Anomaly.setLevelType_Filter(signalPower, this->GetAnomalyID(), this->GetAnomalySkipLevel(), this->GetAnomalyKillLevel() );
			}
    //this->typeOfSignal |= SIGNAL_TYPE_ANOMALY;
		}
  }
bool RadiomarkRadiationAnomayClass::IsRadiationReceived(void)
  {
  //return (this->typeOfSignal & SIGNAL_TYPE_RADIATION);
  return (((int8_t)this->GetRadiationMultiplier()) != 0);
  }
bool RadiomarkRadiationAnomayClass::IsAnomalyReceived(void)
  {
  //return (this->typeOfSignal & SIGNAL_TYPE_ANOMALY);
  return (this->GetAnomalyID() > 0);
  }




//RadiomarkQuestClass
void RadiomarkQuestClass::ProcessSignal(uint8_t signalPower)
  {
  if (signalPower > this->GetSensetivityThreshold())
  	{
  	switch (this->GetQuestAction())
  		{
  		case RADIOMARK_TYPE_QUEST_ACTION_COMPLETE:
  			{
  			Quest.CompleteQuest(this->GetQuestID());
  			}
  		break;
  
  		case RADIOMARK_TYPE_QUEST_ACTION_FAIL:
  			{
  			Quest.FailQuest(this->GetQuestID());
  			}
  		break;
  
  		case RADIOMARK_TYPE_QUEST_ACTION_GIVE:
  			{
  			Quest.GiveQuest(this->GetQuestID());
  			}
  		break;
  
  		case RADIOMARK_TYPE_QUEST_ACTION_REMOVE:
  			{
  			Quest.RemoveQuest(this->GetQuestID());
  			}
  		break;
  		}
  	}
  }
//RadiomarkPsyClass
void RadiomarkPsyClass::ProcessSignal(uint8_t signalPower)
  {
    int8_t Multiplier	= static_cast<int8_t>(this->GetPsyMultiplier());
//	#ifdef DEBUG_USART_ENV_PACKETS
//		sprintf (USARTBuffer,"[EnvironmentProcess]processing RadAno... rariomarkID: %03d\r\n",rariomarkID);
//		sendString(USARTBuffer);
//	#endif

	if (Multiplier != 0)
		{
		uint16_t itmp	= 0;
		if (Multiplier > 0)
			{
			itmp	= ((uint8_t)Multiplier) * signalPower;//multiplier * [rssi/2]
			}
		else
			{
			itmp	= signalPower/(-Multiplier);
			}
		if (itmp> 255)
			{
			itmp=255;
			}
//		#ifdef DEBUG_USART_ENV_PACKETS
//			sprintf (USARTBuffer,"EnvironmentProcess Env.RadLevelSetFilter: [%03d]\r\n", itmp);
//			sendString(USARTBuffer);
//		#endif
		//Env.PsyLevelSetFilter((uint8_t)itmp);
    Env.setPsyLevelFilter((uint8_t)itmp);
    }
  }
//////////EMISSION

uint8_t EmissionInstanceDetectorClass::GetSignalID(void)
  {
  return this->signalID;
  }
void EmissionInstanceDetectorClass::ProcessSignal(RadiomarkInstanceClass* selectedRadiomark)
  {
  //selectedRadiomark->get
  //
  this->storedSignalPowerPercent  = selectedRadiomark->GetSignalPowerPercent();
  this->signalArrived             = true;
  this->signalID                  = selectedRadiomark->GetParameter1();
  }
void EmissionInstanceDetectorClass::TimerUpdateEvent (uint8_t msPassed)
  {
  //SelectedSkin->DisplayEmissionLevel(DamageSource_t::DAMAGE_SOURCE_DETECTOR_TMP, this->GetSignalPower());
	
  uint16_t test = this->msCounter + msPassed;
	if (test >= 100)
		{
		this->msCounter = (test - 100);
    /*
    if (PsyBeepKeepOnHack > 0)
      {
      if (--PsyBeepKeepOnHack == 0)
        {
        PDASound.stopSoundsPsy();
        }
      }
    */
    //SelectedSkin->DisplayEmissionLevel(DamageSource_t::DAMAGE_SOURCE_DETECTOR_TMP, this->storedSignalPower);
		
    if (this->signalArrived == true)
      {
      this->signalArrived = false;
      }
    else
      {
      this->storedSignalPowerPercent = 0;
      //SelectedSkin->DisplayEmissionLevel(DamageSource_t::DAMAGE_SOURCE_DETECTOR_TMP, this->storedSignalPower);
      }
    
		}
  else
    {
    this->msCounter = test;
    }
  
  }
Percent_t EmissionInstanceDetectorClass::GetSignalPowerPercent(void)
  {
  //static uint8_t i=95;
  //return ++i;
  return this->storedSignalPowerPercent;
  }
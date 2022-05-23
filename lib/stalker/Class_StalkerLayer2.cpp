// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef STALKER_LAYER2_CPP
#define STALKER_LAYER2_CPP

/*
void Class_StalkerLayer2::StalkerLayer2Task1::Task(void)
	{
	((Class_StalkerLayer2*)this->GetLinkedObject())->EnvironmentLookAround();
	}
void Class_StalkerLayer2::StalkerLayer2Task2::Task(void)
	{
	((Class_StalkerLayer2*)this->GetLinkedObject())->EnvironmentProcess();
	}*/
void Class_StalkerLayer2::TimerUpdateEvent (uint8_t msPassed)
	{
	static uint16_t environmentLookAround_msCounter=0;
	//static uint16_t environmentProcess_msCounter=0;
	environmentLookAround_msCounter+=msPassed;
	//environmentProcess_msCounter+=msPassed;
	//char tmp[255];
	//sprintf (tmp,"4: %03d %03d \r\n",RandomPseudo.get(), this->bufPointer);
	//sendString(tmp);
	if (environmentLookAround_msCounter >= 11)
		{
		environmentLookAround_msCounter -= 11;
		this->EnvironmentLookAround();
		}
	/*if (environmentProcess_msCounter >= 150)
		{
		environmentProcess_msCounter	-=150;
		this->EnvironmentProcess();
		}*/
	}
Class_StalkerLayer2::Class_StalkerLayer2(void)
	{
	this->cleanBuf();
  //memset(this->buf, 0, sizeof(this->buf));
	//this->TaskEnvironmentLookAround.SetLinkedObject(this);
	//this->TaskEnvironmentProcess.SetLinkedObject(this);
	}
void Class_StalkerLayer2::cleanBuf(void)
	{
	/*
	for (uint8_t i=0;i<Class_HAL::MAX_ENV_PACKETS_IN_TRANSACTION;i++)
		{
		for (uint8_t j=0;j<this->NUM_PACKET_PARAMETERS;j++)
			{
			this->buf[i][j]	= 0;
			}
		}*/
	//memset(this->buf, 0, (Class_HAL::MAX_ENV_PACKETS_IN_TRANSACTION * this->NUM_PACKET_PARAMETERS));//кагбэ въуй не впилось
	TODO('check this')
	memset(this->buf, 0, (Class_HAL::MAX_ENV_PACKETS_IN_TRANSACTION * sizeof(L2_Packet_struct)));//seems too be sometimes processing old data
	this->bufPointer	= 0;
	}
void Class_StalkerLayer2::programmStart(void)
	{
	this->L1.programmStart();
	}
//Сканит принятый пакет, достаёт его и складывает в пул
void Class_StalkerLayer2::EnvironmentLookAround(void)
	{
  LogClass::Log(LogClass::MESSAGES::MESSAGE_SL2_ENVIRONMENT_LOOK_AROUND__ENTER);
	//bool isSameIDDetected		= false;
	static uint8_t lookCounter	= 0;


	if (this->L1.isEnvironmentActive())
		{
		RadiomarkID_t RID           = this->L1.getReceivedEnvPacketID();
		RadiomarkRSSI_t	signalPower = this->L1.getReceivedEnvPacketSignalPower();
		uint8_t bufPointerBak       = this->bufPointer;
    LogClass::Log(LogClass::MESSAGES::MESSAGE_SL2_ENVIRONMENT_LOOK_AROUND__RECEIVED_PACKET, RID, signalPower);
		TODO("cross-level access");
		if (this->L1.L0.getReceivedPacketType() == Class_StalkerLayer0::PACKET_TYPE_250BYTES)
			{
			#ifdef DEBUG_USART_MULTY_PACKETS
				sprintf (USARTBuffer,"[multy] L2...\r\n");
				sendString(USARTBuffer);
			#endif // DEBUG_USART_MULTY_PACKETS
			this->L1.CleanCache();
			TODO("cross-level access L2->L0");
			this->L1.L0.packetProcessed();
			return;
			}
		while (1)
			{
			//uint8_t* bufPacket[Class_StalkerLayer2::NUM_PACKET_PARAMETERS]	= buf[bufPointerBak];
			if (RID == 0)// very weird!
				{
				break;//exit
				}
			if (this->bufPointer == (Class_HAL::MAX_ENV_PACKETS_IN_TRANSACTION - 1))// very weird!
				{
				break;//exit
				}
//			if (this->bufPointer == 0)//first time
//				{
//				this->buf[this->bufPointer][this->BUF_ID_ID]			= RID;
//				this->buf[this->bufPointer][this->BUF_ID_SIGNAL_POWER]	= signalPower;
//				this->bufPointer++;
				//should now exit
//				break;//exit
//				}
//			else
			if (this->bufPointer > 0)
				{
				//search for duplicate ID in buffer
				if (RID == buf[bufPointerBak].ID)//found duplicate
					{
          LogClass::Log(LogClass::MESSAGES::MESSAGE_SL2_ENVIRONMENT_LOOK_AROUND__FOUND_DUPLICATE_PACKET, RID, signalPower);
					if (this->buf[bufPointerBak].SignalPower < signalPower)//current RID signal power higher
						{
						this->buf[bufPointerBak].SignalPower	= signalPower;
						}
					break;//exit
					}
				}
			if (bufPointerBak == 0)
				{
				this->buf[this->bufPointer].ID			= RID;
				this->buf[this->bufPointer].SignalPower	= signalPower;
				this->bufPointer++;
				break;
				}
			bufPointerBak--;
			}
		/*
	//sprintf (Lcd.lcd_buf,"3: %03d",RandomPseudo.get());
	//LcdString(1,LCD_LINE_6);
		#ifdef DEBUG_USART_ENV_PACKETS
			sprintf (USARTBuffer,"[EnvironmentLookAround] 4: %03d %03d \r\n",RandomPseudo.get(), this->bufPointer);
			sendString(USARTBuffer);
		#endif
		if (this->bufPointer > 0)
			{
			for (uint8_t i=0;i<Class_HAL::MAX_ENV_PACKETS_IN_TRANSACTION;i++)
				{
				if (this->buf[i][this->BUF_ID_ID] == 0x00)
					{
					continue;
					}
				#ifdef DEBUG_USART_ENV_PACKETS
					sprintf (USARTBuffer,"[EnvironmentLookAround] this->buf[i][this->BUF_ID_ID] == this->L1.getReceivedEnvPacketID() [%03d]==[%03d]\r\n",this->buf[i][this->BUF_ID_ID] ,this->L1.getReceivedEnvPacketID());
					sendString(USARTBuffer);
				#endif
				if (this->buf[i][this->BUF_ID_ID] == this->L1.getReceivedEnvPacketID())
					{
					if (this->buf[i][this->BUF_ID_SIGNAL_POWER] < this->L1.getReceivedEnvPacketSignalPower())
						{
						this->buf[this->bufPointer][this->BUF_ID_SIGNAL_POWER]	= this->L1.getReceivedEnvPacketSignalPower();
						isSameIDDetected	= true;
						#ifdef DEBUG_USART_ENV_PACKETS
							sendString ((char*)"[EnvironmentLookAround]isSameIDDetected\r\n");
						#endif
						}
					}
				}
			}
		if (!isSameIDDetected && this->L1.getReceivedEnvPacketID() != RadiomarkInstanceClass::RADIOMARK_TYPE_NONE)
			{
			#ifdef DEBUG_USART_ENV_PACKETS
				sendString ((char*)"[EnvironmentLookAround] NOT isSameIDDetected && this->L1.getReceivedEnvPacketID() != RadiomarkInstanceClass::RADIOMARK_TYPE_NONE\r\n");
			#endif
			this->buf[this->bufPointer][this->BUF_ID_ID]			= this->L1.getReceivedEnvPacketID();
			this->buf[this->bufPointer][this->BUF_ID_SIGNAL_POWER]	= this->L1.getReceivedEnvPacketSignalPower();
			this->bufPointer++;
			}
		*/
		TODO("cross-level access L2->L0");
		this->L1.L0.packetProcessed();
		}
	if (++lookCounter > Class_HAL::MAX_ENV_PACKETS_IN_TRANSACTION)
		{
		lookCounter	= 0;
		this->EnvironmentProcess();
		}
//	this->cleanBuf();
	}



//обрабатывает пул: по каждому типу выдает решение
void Class_StalkerLayer2::EnvironmentProcess(void)
	{
//	uint8_t* anoRad	= &(anoradData[this->buf[this->bufPointer][this->BUF_ID_ID]][0]);
	uint8_t rariomarkID             = 0;
	uint8_t SignalPower             = 0;
	bool isRadiationPacketReceived  = false;
	bool isRadiation1PacketReceived  = false;
	bool isAnomalyPacketReceived    = false;
	bool isPsyPacketReceived        = false;
  LogClass::Log(LogClass::MESSAGES::MESSAGE_SL2_ENVIRONMENT_PROCESS__ENTER,this->bufPointer);
  //return;

	if (Player.IsDead())//на данный момент мёртвые не обрабатывают пакеты
		{
		//#ifdef DEBUG_USART
		//	USART_startTX((char*)"Player is dead\r\n");
		//#endif

		TODO ("remove this hack!");
		//this works only if revive packet is 1st

    RadiomarkParameter_t RMType = GameCFG.GetRadiomark(this->buf[0].ID)->GetType();

		if (this->bufPointer > 0)
			{
			if(RMType == RadiomarkInstanceClass::RADIOMARK_TYPE_REVIVE)
				{
        LogClass::Log(LogClass::MESSAGES::MESSAGE_SL2_ENVIRONMENT_PROCESS__RADIOMARK_TYPE_REVIVE);
				Player.Revive();
				}
			if(RMType ==  RadiomarkInstanceClass::RADIOMARK_TYPE_UNDERTAKER)
				{
				if (Player.IsDead())
					{
					PlayerDeathTimer_t halfTime	= (Player.GetDeathTimeRemain() / 2);
					if (Player.GetDeathTimeRemain() > halfTime)
						{
						Player.SetDeathTimeRemain(halfTime);
						}
					}
				}
			else if(RMType == RadiomarkInstanceClass::RADIOMARK_TYPE_GRAVEYARD)
				{
				if (Player.IsAwaitingGraveyard())
					{
					Player.RenewDeathTimer();
					PDAMenu.DeathScreen();
					}
				}
			else if(RMType == RadiomarkInstanceClass::RADIOMARK_TYPE_SAFE_SHELTER && GameCFG.IsGameUseParameter(GameConfig::CFG_CONFIGURATION_BITS_REVIVE_AT_SAFE_ZONE)){
				if (Player.IsAwaitingGraveyard()){
					Player.RenewDeathTimer();
					PDAMenu.DeathScreen();
				}
			}
			}
//		sendString ((char*)"Player.isDead\r\n");
		this->cleanBuf();//packet stuck fix
		return;
		}

	while (this->bufPointer > 0)
		{
		--this->bufPointer;
		rariomarkID			= this->buf[this->bufPointer].ID;
		SignalPower			= this->buf[this->bufPointer].SignalPower;
//		uint8_t* selectedRadiomark	= anoradData[rariomarkID];
		RadiomarkInstanceClass* selectedRadiomark	= GameCFG.GetRadiomark(rariomarkID);
    selectedRadiomark->SetSignalPower(SignalPower);
    LogClass::Log(LogClass::MESSAGES::MESSAGE_SL2_ENVIRONMENT_PROCESS__PROCESSING_BUFFER,this->bufPointer, rariomarkID, SignalPower, selectedRadiomark->GetType());

    //sprintf(Lcd.lcd_buf, "%03u%03u %03u%03u", this->bufPointer, rariomarkID, SignalPower, selectedRadiomark->GetType());
    //LcdStringUpdate(1,LCD_LINE_1, Lcd.lcd_buf);
    //RadiomarkRadiationAnomayClass RadAno	= RadiomarkRadiationAnomayClass(selectedRadiomark);
    //sprintf(Lcd.lcd_buf, "%03u%03u %03u%03u", RadAno.GetRadiationMultiplier(), RadAno.GetAnomalyID(), RadAno.GetAnomalyKillLevel(), RadAno.GetAnomalySkipLevel());
    //LcdStringUpdate(1,LCD_LINE_2, Lcd.lcd_buf);
    //while(1);

		switch (selectedRadiomark->GetType())
			{
			case RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_NEUTRON_FLUX:
			{
			RadiomarkRadiationNeutronFluxClass RadiationNeutronFlux = RadiomarkRadiationNeutronFluxClass(selectedRadiomark);
			RadiationNeutronFlux.ProcessSignal(SignalPower);
			isRadiation1PacketReceived	= true;
				//RadiomarkRadiationAnomayClass RadAno	= RadiomarkRadiationAnomayClass(selectedRadiomark);
				//RadAno.ProcessSignal(SignalPower);
			break;
			}
			case RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY:
				{
        LogClass::Log(LogClass::MESSAGES::MESSAGE_SL2_ENVIRONMENT_PROCESS__RADIOMARK_TYPE_RADIATION_ANOMALY);
				RadiomarkRadiationAnomayClass RadAno	= RadiomarkRadiationAnomayClass(selectedRadiomark);
				RadAno.ProcessSignal(SignalPower);
        if (RadAno.IsRadiationReceived())
          {
          isRadiationPacketReceived	= true;
          }
        if (RadAno.IsAnomalyReceived())
          {
          isAnomalyPacketReceived   = true;
          }
				}
			break;

			case RadiomarkInstanceClass::RADIOMARK_TYPE_PSY:
				{
				#ifdef IS_MONOLYTH
					//psy imunne
				#else
					//Env.setPsyLevelFilter(SignalPower);
          RadiomarkPsyClass RPsy	= RadiomarkPsyClass (selectedRadiomark);
          RPsy.ProcessSignal(SignalPower);
					isPsyPacketReceived			= true;
				#endif

				}
			break;

			case RadiomarkInstanceClass::RADIOMARK_TYPE_QUEST:
				{
				RadiomarkQuestClass RQuest	= RadiomarkQuestClass (selectedRadiomark);
        RQuest.ProcessSignal(SignalPower);
				}
			break;
			
			case RadiomarkInstanceClass::RADIOMARK_TYPE_GRENADE:
				{
        Grenade.ProcessSignal(SignalPower);
				}
			break;

			/*
			case RadiomarkInstanceClass::RADIOMARK_TYPE_GRAVEYARD:
				{
				while(1);
				if (Player.IsAwaitingGraveyard())
					{
					Player.SetPlayerAtGraveyard();
					}
				}
			break;
			*/
/*
			case RadiomarkInstanceClass::RADIOMARK_TYPE_REVIVE://moved to L1, ADM_ACTION
				{
				TODO("move to L1 with SYSTEM___SOMETHING?");
				if (Player.isDead())
					{
					Player.Revive();
					}
				}
			break;
*/
/*
			case RADIOMARK_TYPE_TIME://moved to L1
				{
				if (timeUpdateTimer == 0)
					{
					TimeRTC.setTime(selectedRadiomark[PACKET_RADIOMARK_TYPE_PARAM0], selectedRadiomark[PACKET_RADIOMARK_TYPE_PARAM1], selectedRadiomark[PACKET_RADIOMARK_TYPE_PARAM2]);
//					Time.hour		= radio._RXBuffer[PACKET_RADIOMARK_TYPE_PARAM0];
//					Time.minute		= radio._RXBuffer[PACKET_RADIOMARK_TYPE_PARAM1];
//					Time.second		= radio._RXBuffer[PACKET_RADIOMARK_TYPE_PARAM2];
//					timeSecond		= Time.second;
//					timeMinute		= Time.minute;
//					timeHour		= Time.hour;
//					timeUpdateTimer	= 255;
					}
				}
			break;
*/
			case RadiomarkInstanceClass::RADIOMARK_TYPE_SAFE_ZONE:
			case RadiomarkInstanceClass::RADIOMARK_TYPE_SAFE_SHELTER:
				{
				//Player.GetEffects()->renewEffect(PlayerEffectsOldClass::EFFECTID_SAFE_SHELTER);
				//PlayerEffects.RenewEffectInstance(TemporaryClass::PLAYEREFFECT_SAFE_SHELTER);
				PlayerEffects.RenewEffectInstance(EffectSafeShelterHack);
				}
			break;
			case RadiomarkInstanceClass::RADIOMARK_TYPE_MAGIC:
        {
        //uint8_t addr_to = selectedRadiomark->GetParameter3();
        /*
        while(1)
          {
          LcdStringUpdate(1, LCD_LINE_1, "sdfsdf");
          }
        */
        }
      break;

			case RadiomarkInstanceClass::RADIOMARK_TYPE_DETECTOR:
        {
        EmissionInstanceDetector.ProcessSignal(selectedRadiomark);
        }
      break;
      default:
        {
        //
        //GameCFG.GetEmission(selectedRadiomark->GetID())->ProcessSignal(selectedRadiomark, SignalPower);
        }
      break;
			}
		//this->bufPointer--;
		}
  TODO("REMOVE THIS BOOL VARS!")
	if (isRadiationPacketReceived == false){
		Env.RadLevelSetFilter(0);
		}
	if (isRadiation1PacketReceived == false){
		Env.RadiationNeutronFluxLevelSetFilter(0);
	}
	if (isAnomalyPacketReceived == false)
		{
		Anomaly.setLevelType_FilterNone();
		}
	if (isPsyPacketReceived == false)
		{
		Env.setPsyLevelFilter(0);
		}
//	hui++;
	this->cleanBuf();
	//EventSystem.eventArrived(EventSystemClass::EVID_ENVIRONMENT_PROCESSED,NULL);
	}
void Class_StalkerLayer2::HardwareInitialization(void)
	{
	this->L1.HardwareInitialization();
	}
#endif
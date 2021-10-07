// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


/*void Environment::EnvironmentTask1::Task(void)
	{
	Env.process();
	}*/
void Environment::TimerUpdateEvent (uint8_t msPassed)
	{
	static uint16_t envProcess_msCounter=0;
	envProcess_msCounter+=msPassed;
	if (envProcess_msCounter >= 50)
		{
		envProcess_msCounter -= 50;
		this->process();
		}
	}
Environment::Environment()
	{
	
	//		this->lastAnomalyType			= 0;
	//		this->anomalyLevel				= 0;
	//		this->anomalyLevelCounter		= 0;
	//		this->radiationLevel			= 0;
	this->radLevelSoundCounter		= 0;
	//		this->anoLevelSoundCounter		= 0;
	//		this->RadDoseCounter			= 0;
	//		this->radFilterValue			= 0;
	this->playerRadDoseCollector	= 0;
	this->cleanPsyFilter();
	this->cleanRadFilter();
	
	}
void Environment::process(void)//генерация звука радиации и преобразование излучения в дозу
	{
	if (Player.IsDead())//мёртвые не подвержены радиации
		{
		return;
		}
	this->radLevelSoundCounter+=this->radiationLevel;
//	this->anoLevelSoundCounter+=Anomaly.strength;
	if (this->radLevelSoundCounter > this->RADIATION_SOUND_THRESHOLD)
		{
		this->radLevelSoundCounter-=this->RADIATION_SOUND_THRESHOLD;
		if (RandomPseudo.get() & 1)
			{
			PDASound.PlaylistAdd(Sound::SID_RADIOATION);
			}
		else
			{
			PDASound.PlaylistAdd(Sound::SID_RADIOATION4);
			}
		this->RadiationToDoseProcess();
		}
	}

void Environment::RadLevelSet1(RadLevel_t value)
	{
	if (value > this->MAX_RAD_LEVEL)
		{
		value	= this->MAX_RAD_LEVEL;
		}
	this->radiationLevel=value;
	Lcd.IsEnvRadLevelNeedRedraw	= true;
//	if (PDAMenu.selectedMenuID == PDAMenuClass::MENUID_MAIN) //TODO: ДУБЛИРУЕТСЯ!!!
//		PDAMenu.displayPercentBar(RAD_GRID_POS_X1, Env.radiationLevel*100/Environment::MAX_RAD_LEVEL);

	}
void Environment::RadLevelSetFilter(RadLevel_t value)
	{
	if (value > this->MAX_RAD_LEVEL)
		{
		value	= this->MAX_RAD_LEVEL;
		}

	/*
	this->radFilter[0]	= this->radFilter[1];
	this->radFilter[1]	= this->radFilter[2];
	this->radFilter[2]	= this->radFilter[3];
	this->radFilter[3]	= this->radFilter[4];
	this->radFilter[4]	= this->radFilter[5];
	this->radFilter[5]	= this->radFilter[6];
	this->radFilter[6]	= this->radFilter[7];
	this->radFilter[7]	= value;

	this->radiationLevel	= (this->radFilter[0] + this->radFilter[1] + this->radFilter[2] + this->radFilter[3] + this->radFilter[4] + this->radFilter[5] + this->radFilter[6] + this->radFilter[7]) >> 3;
	*/
	uint16_t sum=0;
	for (uint8_t i=0;i<this->RAD_FILTER_CACHE_LENGTH-1;i++)
		{
		sum					+= this->radFilter[i];
		this->radFilter[i]	= this->radFilter[i+1];
		}
	this->radFilter[this->RAD_FILTER_CACHE_LENGTH-1]	= value;
	this->radiationLevel			= (sum + value)/RAD_FILTER_CACHE_LENGTH;

	Lcd.IsEnvRadLevelNeedRedraw	= true;
	}
void Environment::RadiationToDoseProcess(void)
    {
	//sprintf (USARTBuffer,"RadiationToDoseProcess... this->playerRadDoseCollector[%03d] radiationLevel[%03d] def[%03d]\r\n",this->playerRadDoseCollector, radiationLevel, Player.getComplexDefenceFrom(TemporaryClass::DAMAGE_SOURCE_RADIATION_EXTERNAL));
	//sendString(USARTBuffer);
//    uint8_t mod;
//    uint8_t resist;

//    if (PlayerSpecs.radiationDose >= Player.getMaxRadiationDose())
    if (Player.IsRadiationDoseMaximimReached())
		{
        return;
		}
//    if (Player.defenceRad > 0 && Player.defenceRad > this->radiationLevel) // более оптимально за счет проверки на нуль, тоесть если большинство без защиты
//    if (Player.getDefenceRadiation() >= this->radiationLevel)
    if (Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_RADIATION_EXTERNAL}) >= this->radiationLevel)
		{
		return;//и нахера было всё, что ниже??!
//        resist	= this->radiationLevel;
//    else
//        resist	= PlayerSpecs.defenceRadiation;
		}
//    this->playerRadDoseCollector+=radiationLevel-resist;
//    this->playerRadDoseCollector+=radiationLevel - Player.getDefenceRadiation();
    this->playerRadDoseCollector+=this->radiationLevel - Player.GetComplexDefenceFrom({value:1, damageSource:TemporaryClass::DAMAGE_SOURCE_RADIATION_EXTERNAL});
    if (this->playerRadDoseCollector > this->RAD_DOSE_THRESHOLD)
        {
        this->playerRadDoseCollector-=this->RAD_DOSE_THRESHOLD;
        Player.RadDoseIncrase(1);
		Lcd.IsPlayerRadDoseNeedRedraw	= true;
//        Player.LastAgressorType = PLAYER_AGRESSOR_TYPE_RADIATION;
//        RadiationRadLevelSet(0);
        }

/*
//    mod = (1000*((RadiationLevel-resist)*RAD_MOD)/time);
//    mod = (100*((RadiationLevel-resist)*RAD_MOD)/time);

//    mod = (50*((RadiationLevel-resist)*RAD_MOD)/time);
    mod = (50*((RadiationLevel-resist)*RAD_MOD)/UPDATE_STATS_TIMER_THRESHOLD);
    if (mod>0)
        Player.LastAgressorType = PLAYER_AGRESSOR_TYPE_RADIATION;

        sprintf (lcd_buf, "%02d% 03d%",resist,Player.RadDose); 
        LcdString(1,3);
        LcdUpdate();
    PlayerRadDoseIncrase(mod);
*/
    }
/*
void Environment::AnomalyLevelSetFilter(uint8_t level, uint8_t anoType)
	{
	if (level > this->MAX_ANOMALY_LEVEL)
		level	= this->MAX_ANOMALY_LEVEL;

	this->anomalyLevel		+= level;
	this->anomalyLevel		= this->anomalyLevel>>1;
	this->lastAnomalyType	= anoType;
	}
*/
void Environment::cleanRadFilter(void)
	{
	//CleanArray(this->radFilter,this->RAD_FILTER_CACHE_LENGTH);
	memset(this->radFilter, 0, this->RAD_FILTER_CACHE_LENGTH);
	this->radiationLevel		= 0;
	}
void Environment::cleanPsyFilter(void)
	{
	//CleanArray(this->psyFilter,this->PSY_FILTER_CACHE_LENGTH);
	memset(this->psyFilter, 0, this->PSY_FILTER_CACHE_LENGTH);
	//std::fill(this->psyFilter, 0, this->PSY_FILTER_CACHE_LENGTH);
	this->psyLevel				= 0;
	}
RadLevel_t Environment::GetRadiationLevel(void)
	{
	return this->radiationLevel;
	}
Percent_t Environment::GetRadiationLevelPercent(void)
  {
  return (this->GetRadiationLevel()*100/this->MAX_RAD_LEVEL);
  }
void Environment::setPsyLevelFilter(PsyLevel_t value)
	{
	if (value > this->MAX_LEVEL_PSY)
		{
		value	= this->MAX_LEVEL_PSY;
		}

	uint16_t sum=0;
	for (uint8_t i=0;i<this->PSY_FILTER_CACHE_LENGTH-1;i++)
		{
		sum					+= this->psyFilter[i];
		this->psyFilter[i]	= this->psyFilter[i+1];
		}
	this->psyFilter[this->PSY_FILTER_CACHE_LENGTH-1]	= value;
	this->psyLevel			= (sum + value)/PSY_FILTER_CACHE_LENGTH;


	if (this->psyLevel > 0)
		{
		
		PDASound.startSoundsPsy(175 - (this->psyLevel>>1));
		}
	else
		{
		//if (PsyBeepKeepOnHack == 0)
      //{
      PDASound.stopSoundsPsy();
      //}
    //else
      //{
      //if (--PsyBeepKeepOnHack == 0)
        //{
        //PDASound.stopSoundsPsy();
        //}
      //}
		}
	TODO('make update via PsyUpdate object')
	if (PDAMenu.getSelectedMenuID() == PDAMenu_MainInterface::MENUID_MAIN)
		Lcd.IsEnvPsyLevelNeedRedraw	= true;
	}
uint8_t Environment::GetPsyLevel(void)
	{
	return this->psyLevel;
	}
Percent_t Environment::GetPsyLevelPercent(void)
  {
  
  return (this->GetPsyLevel()*100/this->MAX_LEVEL_PSY);
  }
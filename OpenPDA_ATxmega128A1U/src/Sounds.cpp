// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Sounds.hpp"
uint16_t deathSound[]={4*128, 4*1000, 4*128, 4*1200, 4*128, 4*1400, 0x8000, 0, 0xFFFF};//нуть в конце - хак
Sound::Sound(void)
  {
  this->CleanQueue();
  this->queueTop    = 0;
  this->queueBottom = 0;
  SoundBuffer.Clear();
  }
void Sound::TimerUpdateEvent (uint8_t msPassed)
  {
  static uint8_t ms100Counter = 0;
  //static uint8_t i=0;
  if (ms100Counter + msPassed > 255)
    {
    ms100Counter  = 255;
    }
  else
    {
    ms100Counter+= msPassed;
    }
  //sprintf (Lcd.lcd_buf,"%03d",ms100Counter);
  //LcdString(12,LCD_LINE_4);
  if (ms100Counter < 100)
    {
    return;
    }
  ms100Counter-= 100;
  this->PlayNext();
  //this->FillBufer();
  }
bool Sound::IsPsyActive(void)
  {
  return (TIMER_PSY.PER != 0);
  }
bool Sound::IsHiFiActive(void)
  {
  //return this->IsHifiSoundBusy;
  return SoundBuffer.IsNotEmpty();
  }
void Sound::DAC_init(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[Sound::DAC_init]");
  #endif
  SOUND_HIFI_DAC.CTRLA    =  0<<DAC_IDOEN_bp | 1<<DAC_CH0EN_bp | 0<<DAC_CH1EN_bp | 1<<DAC_ENABLE_bp;      // Enable DACA and CH0
  SOUND_HIFI_DAC.CTRLB    = (0b00)<<DAC_CHSEL0_bp | 0<<DAC_CH0TRIG_bp | 0<<DAC_CH1TRIG_bp;  // CH0 auto triggered by an event (CH1)
  SOUND_HIFI_DAC.CTRLC    = DAC_REFSEL_INT1V_gc | 1<<DAC_LEFTADJ_bp;
  SOUND_HIFI_DAC.EVCTRL    = 0b000; // Event CH1 triggers the DAC Conversion
  #ifdef _AVR_ATXMEGA128A1U_H_INCLUDED
    //TIMCTRL register does not exist in ATxmega128A1U/64A1U, so there are no timing constraints on DAC operation.
  #else
    SOUND_HIFI_DAC.TIMCTRL  = DAC_CONINTVAL_16CLK_gc | DAC_REFRESH_OFF_gc;//рефреш - больше? конинтервал меньше?
  #endif
    
  }
void Sound::IOInit(void)
  {
  psyPin::SetDirOut();
  VA_SDN::SetDirOut();
  VA_SDN::SetOutLow();
  }
void Sound::CleanQueue(void)
  {
  memset(this->queue, 0, sizeof(this->queue));
  }
void Sound::HardwareInitialization(void)
  {
  TIMER_PSY.CTRLA    = ( TIMER_PSY.CTRLA & ~TC1_CLKSEL_gm ) | TC_CLKSEL_DIV64_gc;
  TIMER_PSY.PER    = 0;// 125-1;//10 000Hz
  TIMER_PSY.INTCTRLA  = TC_OVFINTLVL_OFF_gc;//звук ПСИ
  this->DAC_init();
  this->CleanQueue();
  this->stopSoundsHiFi();
  this->MuteOn();
  }
void Sound::PlaylistAdd(SIDS SID)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[Sound::PlaylistAdd]");
  #endif
  if (this->queueBottom == 0 && this->queueTop == (Sound::QUEUE_SIZE-1))
    {
    return;
    }
  if (this->queueTop == (this->queueBottom-1))
    {
    return;
    }

  if (++this->queueTop == Sound::QUEUE_SIZE)
    {
    this->queueTop=0;
    }
  this->queue[this->queueTop]=SID;
  this->startSoundsHiFi();
  }
void Sound::ISR_PsyVerctor(void)
  {
  psyPin::SetOutToggle();
  }
void Sound::ISR_DeathSound(void)
  {
  static uint16_t deathSoundSample=0;
  if (*this->deathSoundPtr == 0xFFFF)
    {
    TIMER_DEATH_SOUND.INTCTRLA  = TC_OVFINTLVL_OFF_gc;
    this->stopSoundsHiFi();//хак??!
    return;
    }
  if (deathSoundSample == 0)
    {
    this->MuteOff();
    deathSoundSample  = *this->deathSoundPtr;  //гружу текущий сэмпл
    this->deathSoundPtr++;            //кручу на следующий
    return;
    }
  if ((this->deathSoundPtr - &deathSound[0]) & 1)
    {
    SOUND_HIFI_DAC_CHANNEL^=127;
    #warning "[T] make psyPin"
    }
  deathSoundSample--;
  }
void Sound::FillBufer(void)
  {
  //uint8_t buf_free  = Buf.GetFreeSpace();
  //uint8_t buf_free  = Buf.GetUsedSpace() - Buf.Size();
//  if (Buf.GetFreeSpace() > (Buf.GetMaxSize()/2))
  //if (Buf.GetFreeSpace() > 0)
  if (SoundBuffer.IsFull())
    {
    return;
    }
  //while (true)
    {
    playableSample Cache[SoundBuffer.size()];
    //playableSample sample=0;
    TFS_FAT_SizeBytes_t bytes_readed=0;
    TFS_FAT_SizeBytes_t BufferFreeSize  = SoundBuffer.GetFreeSpace();
    bytes_readed  = this->sound_file.ReadData(Cache, BufferFreeSize);
    if (bytes_readed == 0)
      {
      return;
      }
    for (TFS_FAT_SizeBytes_t i=0;i<bytes_readed;i++)
      {
      playableSample sample = Cache[i];
      SoundBuffer.Write(sample);
      }
    /*
    if (SoundBuffer.Write(sample) == false)//mean buf is full
      {
      #warning "This should be never happen!"
      return;
      }
    if (SoundBuffer.IsFull())
      {
      return;
      }
*/
    }
  }
playableSample Sound::getNextPlayableSample(void)
  {
  playableSample sample=0;
  //this->sound_file.ReadData(&sample, 1);
  SoundBuffer.Read(sample);
  //this->Buf.IncrementRead();
  return sample;
  }
/*
#ifdef SOUNDS_ON_MEDIAFLASH
playableSample Sound::getNextPlayableSample(void)
  {
  UNION_UINT32_LITTLE_
  N z;
  z.value_int = this->SoundNowPlaying_ptr;
  this->SoundNowPlaying_ptr++;
  playableSample tmp[1];
  MediaMemory.ReadData(z.byte_field.mh, z.byte_field.ml, z.byte_field.l, tmp, (uint16_t)1);
  return tmp[0];
  }

void Sound::LoadSoundAddressesFromMediaFlash(void)
  {
  UNION_UINT32_LITTLE_ENDIAN z;
  for (uint8_t i=0;i<SIDS::SIDS_NUM;i++)
    {
    z.value_int = MediaFlashClass::MEDIAFLASH_ADDRESS::MEDIAFLASH_ADDRESS_SOUND_POINTERS+(4*i);//address
    uint32_t addressValue = 0;
    MediaMemory.ReadData(z.byte_field.mh, z.byte_field.ml, z.byte_field.l, (uint8_t*)&addressValue, (uint16_t)4);
    this->MediaFlashSamples[i]  = addressValue;
	  //StatusLedPin::SetOutToggle();
	  //_delay_ms(200);
    }
	//StatusLedPin::SetOutLow();
  }

uint32_t Sound::GetSoundAddress(uint8_t SID)
  {
  if (this->MediaFlashSamples[0] == 0)//load
    {
    this->LoadSoundAddressesFromMediaFlash();
    }
	if (SID >= SIDS::SIDS_NUM)
	  {
		SID = SIDS::SID_NONE;
	  }
  return this->MediaFlashSamples[SID];
  }
#else //sounds on pgm
playableSample Sound::getNextPlayableSample(void)
  {
//  #ifdef DEBUG_USART_FUNCTION_CALL
//    sendString((char*)"[Sound::getNextPlayableSample]");
//  #endif
  return pgm_read_byte(this->SoundNowPlaying_ptr++);
  }
uint8_t* Sound::GetSoundAddress(uint8_t SID)
  {
  switch (SID)
    {
    case Sound::SID_RADIOATION:
      {
      return (uint8_t*)&Sound_geiger_1;//[WAV_HEAD_DIFF];
      }
    break;

    case Sound::SID_RADIOATION4:
      {
      return (uint8_t*)&Sound_geiger_4;//[WAV_HEAD_DIFF];
      }
    break;
    
    case Sound::SID_PDA_NEWS:
      {
      //return (uint8_t*)6452;
      return (uint8_t*)&Sound_pda_news;//[WAV_HEAD_DIFF];
      //#warning "TMP"
      //this->SoundNowPlaying_ptr      = (uint8_t*)(NULL + WAV_HEAD_DIFF);
      }
    break;

    case Sound::SID_ANOMALY_BEEP:
      {
      return (uint8_t*)&Sound_da_2_beep1;//[WAV_HEAD_DIFF];
      }
    break;

    case Sound::SID_HIT_1:
      {
      return (uint8_t*)&Sound_pain_1;//[WAV_HEAD_DIFF];
      }
    break;

    case Sound::SID_HIT_2:
      {
      return (uint8_t*)&Sound_pain_7;//[WAV_HEAD_DIFF];
      }
    break;

    case Sound::SID_HIT_3://speech aai
      {
      return (uint8_t*)&Sound_hit_5;//[WAV_HEAD_DIFF];
      }
    break;

    case Sound::SID_HIT_4://speech yop
      {
      return (uint8_t*)&Sound_hit_6;//[WAV_HEAD_DIFF];
      }
    break;

    case Sound::SID_HIT_5://speech svolotch
      {
      return (uint8_t*)&Sound_hurt3;//[WAV_HEAD_DIFF];
      }
    break;
    
    case Sound::SID_BLOWOUT_HIT_2:
      {
      return (uint8_t*)&Sound_blowout_hit_2;//[WAV_HEAD_DIFF];
      }
    break;
    

//    case Sound::SID_GRAVY_HIT:
//      {
//      this->SoundNowPlaying_ptr      = (uint8_t*)&SoundGravyHit[0];
//      }
//    break;

//    default: //+Sound::SID_NONE
//      {
//      this->IsHifiSoundBusy        = false;
//      this->stopSoundsHiFi();//TODO: ХАК!!!
//      VA_SDN::SetOutLow();//turn off
//      }
//    break;
    
    }
  return (uint8_t*)SoundNone;
  }
#endif //SOUNDS_ON_MEDIAFLASH
*/
void Sound::SetCurrentSound(SIDS snd)//обращение к железу
  {
  this->sound_file.SeekByPosition(this->snd_pos[snd]);
  this->sound_file.SetInternalPointer(WAV_HEAD_DIFF);
  }
void Sound::PlayNext(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[Sound::playNext]");
  #endif
  if (this->IsHiFiActive())
    {
    return;
    }
  if (this->queueTop == this->queueBottom)
    {
    this->stopSoundsHiFi();//TODO: ХАК!!!
    return;
    }
  if (++this->queueBottom == Sound::QUEUE_SIZE)
    {
    this->queueBottom=0;
    }

  this->MuteOff();
  //this->IsHifiSoundBusy        = true;

  SIDS selected_SID        = this->queue[this->queueBottom];
  //this->sound_file.SeekByPosition(this->snd_pos[selected_SID]);
  this->SetCurrentSound(selected_SID);

  //sprintf (Lcd.lcd_buf,"%03d",PDASound.IsHiFiActive());
  //LcdString(1,LCD_LINE_3);
  //sprintf (Lcd.lcd_buf,"%03d",PDASound.queueBottom);
  //LcdString(1,LCD_LINE_4);
  //sprintf (Lcd.lcd_buf,"%03d",PDASound.queueTop);
  //LcdString(1,LCD_LINE_5);
  //sprintf (Lcd.lcd_buf,"%03d", this->queue[this->queueBottom]);
  //LcdStringUpdate(1,LCD_LINE_6, Lcd.lcd_buf);

  if (selected_SID == SIDS::SID_NONE)
    {
    SoundBuffer.Clear();
    //this->IsHifiSoundBusy        = false;
    this->stopSoundsHiFi();//TODO: ХАК!!!
    VA_SDN::SetOutLow();//turn off
    }
/*
  this->SoundNowPlaying_ptr = (GetSoundAddress(selected_SID) + WAV_HEAD_DIFF);
//  if (this->SoundNowPlaying_ptr == SoundNone)
  if (this->SoundNowPlaying_ptr == this->GetSoundAddress(SIDS::SID_NONE))
    {
    this->IsHifiSoundBusy        = false;
    this->stopSoundsHiFi();//TODO: ХАК!!!
    VA_SDN::SetOutLow();//turn off
    }
*/
  }
void Sound::startSoundsPsy(uint8_t period)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[Sound::startSoundsPsy]");
  #endif
  this->MuteOff();
  TIMER_PSY.PER    = period;
  TODO("hack!");
  #ifdef MONOLIT_PSY_SOUND_MUTE
  if (Player.GetFactionID() == TemporaryClass::FACTION_MONOLIT)
    {
    return;
    }
  #endif
  TIMER_PSY.INTCTRLA  = TC_OVFINTLVL_LO_gc;
//  TIMER_PSY.INTCTRLA  = TC_TC1_OVFINTLVL_enum::TC_TC1_OVFINTLVL_LO_gc;
  }
void Sound::startSoundsHiFi(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[Sound::startSoundsHiFi]");
  #endif
  TIMER_DAC.INTCTRLA  = TC_OVFINTLVL_LO_gc;
//  TIMER_DAC.INTCTRLA  = TC_TC0_OVFINTLVL_enum::TC_TC0_OVFINTLVL_LO_gc;
  }
void Sound::stopSoundsPsy(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[Sound::stopSoundsPsy]");
  #endif
  TIMER_PSY.PER    = 0;
  TIMER_PSY.INTCTRLA  = TC_OVFINTLVL_OFF_gc;
//  TIMER_PSY.INTCTRLA  = TC_TC1_OVFINTLVL_enum::TC_TC1_OVFINTLVL_OFF_gc;
  if (!this->IsHiFiActive())
    {
    this->MuteOn();
    }
  }
void Sound::stopSoundsHiFi(void)
  {
  //return;
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[Sound::stopSoundsHiFi]");
  #endif
  TIMER_DAC.INTCTRLA  = TC_OVFINTLVL_OFF_gc;
//  TIMER_DAC.INTCTRLA  = TC_TC0_OVFINTLVL_enum::TC_TC0_OVFINTLVL_OFF_gc;
  this->queueTop    = 0;
  this->queueBottom  = 0;
  SoundBuffer.Clear();
  //this->IsHifiSoundBusy  = false;
//  this->SoundNowPlaying_ptr  = (uint8_t*)&SoundNone[0];
  //this->SoundNowPlaying_ptr  = this->GetSoundAddress(SIDS::SID_NONE);
  this->SetCurrentSound(SID_NONE);
  if (!this->IsPsyActive())
    {
    this->MuteOn();
    }
  }
void Sound::stopAllSounds(void)
  {
  #ifdef DEBUG_USART_FUNCTION_CALL
    sendString((char*)"[Sound::stopAllSounds]");
  #endif
  this->stopSoundsHiFi();
  this->stopSoundsPsy();
  }
void Sound::MuteOn(void)
  {
  if (VA_SDN::IsPinHigh())
    {
    VA_SDN::SetOutLow();
    }
  }
void Sound::MuteOff(void)
  {
  if (VA_SDN::IsPinLow())
    {
    VA_SDN::SetOutHigh();
    }
  //#warning "may cause sound 'crack'"
  }
volatile void Sound::PlaySampleIfNeed(void)
  {
//  #ifdef DEBUG_USART_FUNCTION_CALL
//    sendString((char*)"[Sound::playSampleIfNeed]");
//  #endif
  //return;
  //#warning "TEMPORARY DISABLED"
//  if (this->IsHiFiActive())
  if (SoundBuffer.IsNotEmpty())
    {
    //this->startSoundsHiFi();
    this->MuteOff();
//    SoundNowPlayingCounter--;
//    SOUND_HIFI_DAC_CHANNEL  ^=255;
    uint8_t readedData=this->getNextPlayableSample();
    //hui++;
    if (readedData != SOUND_END_OF_SOUND)
      {
      SOUND_HIFI_DAC_CHANNEL  = readedData;
      //SOUND_HIFI_DAC_CHANNEL  ^=255;
      //SOUND_HIFI_DAC_CHANNEL  ^=255;
     }
    /*
    else
      {
      SoundBuffer.Clear();
      //this->IsHifiSoundBusy  = false;
      if (!this->IsPsyActive())
        {
        this->MuteOn();
        }
      }
    */
    }
  }


// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/************************************************************************/
/*  нопочные прерывани€                         */
/************************************************************************/
ISR (PORTD_INT0_vect)
  {
//  hui=3;
//  radio.interruptHandler();
  }
ISR (PORTA_INT0_vect)
  {
//  hui=1;
  }
/*
ISR (PORTA_INT1_vect)
  {
  buttonUsePresed=1;
  //hui=2;
//  if (buttonLocked == 0)
//    sbi(buttonPressed, BUTTONS_SELECT_MENU);
  }
*/
ISR (ADCA_CH0_vect)
  {
  ADCValueSum-=ADCValueRAWArray[ADCValueIDX];
//  lastADCValueRAWH        = BATTERY_ADC_CHANNEL.CH0.RESH;
//  lastADCValueRAWL        = BATTERY_ADC_CHANNEL.CH0.RESL;
//  lastADCValueRAW          = BATTERY_ADC_CHANNEL.CH0.RES;
  ADCValueRAWArray[ADCValueIDX]  = BATTERY_ADC_RESULT_REGISTER;
  ADCValueSum+=ADCValueRAWArray[ADCValueIDX];
  
  if (++ADCValueIDX >= ADC_BUFFER_SIZE)
    {
    ADCValueIDX  = 0;
    }

//  ADCValue        = ADCA.CH0.RESL;
  //ADCValue        = ADCA.CH0.RES;
  //ADCA.INTFLAGS      = ADC_CH0IF_bm;//IF is automatically cleared when the ADC channel interrupt vector is executed
  ADCMeasurmentsStarted  = false;
  //hui++;
  }
ISR (ADCB_CH0_vect)
  {
  //hui++;
//  HW_Battery.level    = ADCB.CH0RESL;
  //batteryLevel  = ADCB.CH0RESL;
  }
ISR(DMA_CH0_vect)
  {
  DMA.INTFLAGS|=(1<<0) | (0<<1) | (0<<2) | (0<<3);
  n3310LcdClass::StopDMATransaction();
//  hui++;
  }
ISR(RTC_COMP_vect)//RTC - 1Hz - HIGH
//ISR(RTC_OVF_vect)
  {
  TimeRTC.UpdateTimeFromRTC();
//  ADCValue;
  //PDASound.PlaylistAdd(Sound::SID_RADIOATION);
//  timeNewSecond=1;
//  RTC.CNT=0;
  }
ISR(TCE0_OVF_vect)//100 Hz
  {
  //static uint8_t timer1sec=0;

  n3310LcdClass::TryStartDMATransaction();
//  ++ms10timer;
  //RandomPseudo.increment();

  if (!(PowerManager.isInSleepMode()))
    {
    //Timer.Update(TimerClass::TIME_10MS);
    TimerMS.TimerUpdateMS(10);
    /*
    if (++timer1sec == 100)
      {
      timer1sec  = 0;
      //StatusLedPin::SetOutHigh();
      }
    else if (timer1sec == 1)
      {
      //StatusLedPin::SetOutLow();
      }
    */
    }

  //hui++;
/*
  if (++ms40Counter > 3)
    {
    timerUpdateEnviroment      = 1;
    timerNeedToReceivePacket    = 1;
    ms40Counter  = 0;
    }
*/
//  hui++;
  }

ISR(TIMER_PSY_VECTOR)
  {
  PDASound.ISR_PsyVerctor();
  }

//ISR(TCD0_OVF_vect)//1 Hz
//ISR(TCD0_OVF_vect)//10 Hz
//  {
/*
  static uint8_t tmp=0;
  
  if (buttonLocked > 0)
    --buttonLocked;
  if (++tmp == 10)
    {
    tmp=0;
    //timeNewSecond=1;
    if (++timeSecond > 59)
      {
      timeSecond-=60;
      if (++timeMinute > 59)
        {
        timeMinute-=60;
        if (++timeHour > 23)
          timeHour-=24;
        }
      }
    }
  //timer100ms=1;
  //ArtefactPorts.ledFlashProcess();
  if (itemLedOnTimer > 0)
    {
    if (--itemLedOnTimer == 0)
      {
      //HW_SLOT_ITEM_LEDS_PORT.OUTCLR  = 1<<UsableItemClass::HW_LEDS_PIN;
//      IOPort.SetOutLow (USABLE_ITEM_LED_PORT, USABLE_ITEM_LED_PIN);
      UsableItem.turnOffItemLed();
      }
    }
*/
/*
  if (firstAidKitApplyLock > 0)
    {
    --firstAidKitApplyLock;
//    if (--firstAidKitApplyLock == 1)
//      HW_SLOT_LEDS_PORT.OUTCLR  = 1<<ArtefactPortsClass::USE_SLOT_PIN;
    }
  if (antiradApplyLock > 0)
    {
    --antiradApplyLock;
//    if (--antiradApplyLock == 1)
//      HW_SLOT_LEDS_PORT.OUTCLR  = 1<<ArtefactPortsClass::USE_SLOT_PIN;
    }
  if ((firstAidKitApplyLock | antiradApplyLock) == 1)//тоесть либо оба единицы либо один нуль, другой единица
    {
    HW_SLOT_LEDS_PORT.OUTCLR  = 1<<ArtefactPortsClass::USE_SLOT_PIN;
    }
*/
//  }
/*
ISR(TCC1_OVF_vect)//обработка прин€тых –јƒ»ќданных ~40ms
  {
//  timerUpdateEnviroment      = 1;
//  timerNeedToReceivePacket    = 1;
//  Vibro.updateState();
  }
*/
ISR(TCC0_OVF_vect)//15625 Hz
  {
  //RandomPseudo.increment();
  //uint8_t readedData;
  //DACB.CH0DATAH^=255;
  //DACB.CH0DATAH^=16;
//  if (SoundNowPlayingCounter>0)
  PDASound.PlaySampleIfNeed();
  //hui1++;
  }
ISR(TCC1_OVF_vect)
  {
  PDASound.ISR_DeathSound();
  }
/************************************************************************/
/* USART                                */
/************************************************************************/
ISR(USARTD0_RXC_vect)
  {
  //echo_char = USARTD0.DATA;
  //echo_char = 1;
  }
ISR(USARTD0_DRE_vect)
  {
  
  }
ISR(USARTD0_TXC_vect)
  {
  
  }
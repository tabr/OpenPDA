// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * PowerManager.cpp
 *
 * Created: 2015-08-05 02:17:32
 *  Author: tabr
 */ 
//http://www.atmel.com/Images/Atmel-42456-Low-Power-Consumption-Techniques-for-XMEGA-XPLAINED-Kits_Application-Note_AT11487.pdf
//http://www.atmel.com/Images/doc8407.pdf
//http://www.atmel.com/Images/doc8267.pdf

#include "PowerManager.hpp"
/*
void PowerManagerClass::PowerManagerClassTask1::Task(void)
  {
  //PowerManager.startADCMeasurments();
  //this->GetLinkedObject();
  ((PowerManagerClass*)this->GetLinkedObject())->startADCMeasurments();
  }*/
PowerManagerClass::PowerManagerClass(void)
  {
  //this->PowerManagerADCMeasuremntsTask.SetLinkedObject(this);
  }
void PowerManagerClass::TimerUpdateEvent (uint8_t msPassed)
  {
  static uint16_t startADCMeasurments_msCounter=0;
  static uint16_t chargeStatus_msCounter=0;
  
  startADCMeasurments_msCounter+=msPassed;
  chargeStatus_msCounter+=msPassed;
  if (startADCMeasurments_msCounter >= 1000)
    {
    startADCMeasurments_msCounter -= 1000;
    this->StartBatteryADCMeasurments();
    }
  if (chargeStatus_msCounter >= 500)
    {
    chargeStatus_msCounter -= 500;
    this->ChargeCheck();
    }
  }
void PowerManagerClass::HardwareInitialization(void)
  {
//  BATTERY_ADC_CHANNEL.PRESCALER    = ADC_PRESCALER_DIV512_gc;
  BATTERY_ADC_CHANNEL.PRESCALER    = ADC_PRESCALER_DIV128_gc;
//  BATTERY_ADC_CHANNEL.PRESCALER    = ADC_PRESCALER_DIV64_gc;
//  BATTERY_ADC_CHANNEL.PRESCALER    = ADC_PRESCALER_DIV32_gc;
//  BATTERY_ADC_CHANNEL.PRESCALER    = ADC_PRESCALER_DIV4_gc;
  BATTERY_ADC_CHANNEL.CALL      = ReadSignatureByte(0x20) ; //ADC Calibration Byte 0
  BATTERY_ADC_CHANNEL.CALH      = ReadSignatureByte(0x21) ; //ADC Calibration Byte 1
  BATTERY_ADC_CHANNEL.CH0.INTCTRL    = ADC_CH_INTMODE_COMPLETE_gc | ADC_CH_INTLVL_HI_gc;//ADC_CH_INTLVL1_bm | ADC_CH_INTLVL0_bm;
  BATTERY_ADC_CHANNEL.INTFLAGS    = ADC_CH0IF_bm; 
  BATTERY_ADC_CHANNEL.CTRLA      = ADC_ENABLE_bm;
  #ifdef BATTERY_ADC12BIT
    BATTERY_ADC_CHANNEL.CTRLB      = ADC_RESOLUTION_12BIT_gc | ADC_CURRLIMIT_HIGH_gc;//ADC_CONMODE_bm; // 0x10
//    BATTERY_ADC_CHANNEL.CTRLB      = ADC_RESOLUTION_LEFT12BIT_gc | ADC_CURRLIMIT_HIGH_gc;//ADC_CONMODE_bm; // 0x10
//    BATTERY_ADC_CHANNEL.CTRLB      = ADC_CURRLIMIT_HIGH_gc;//12bit by default??!
  #else
  
    BATTERY_ADC_CHANNEL.CTRLB      = ADC_RESOLUTION_8BIT_gc | ADC_CURRLIMIT_HIGH_gc;//ADC_CONMODE_bm; // 0x10
  #endif
  
  
//  BATTERY_ADC_CHANNEL.CTRLB      = ADC_FREERUN_bm | ADC_RESOLUTION_8BIT_gc;//ADC_CONMODE_bm; // 0x10
//  BATTERY_ADC_CHANNEL.CTRLB      = ADC_FREERUN_bm | ADC_RESOLUTION_8BIT_gc | ADC_CURRLIMIT_HIGH_gc;//ADC_CONMODE_bm; // 0x10
  //BATTERY_ADC_CHANNEL.CTRLB      = ADC_RESOLUTION_8BIT_gc;//ADC_CONMODE_bm; // 0x10
  BATTERY_ADC_PORT.DIRCLR        = 1<<BATTERY_ADC_PIN;
  //BATTERY_ADC_CHANNEL.CH0.CTRL    = ADC_CH_INPUTMODE_INTERNAL_gc;
  BATTERY_ADC_CHANNEL.CH0.CTRL    = ADC_CH_INPUTMODE_SINGLEENDED_gc;
  BATTERY_ADC_CHANNEL.CH0.MUXCTRL    = ADC_CH_MUXPOS_PIN7_gc;
  BATTERY_ADC_CHANNEL.REFCTRL      = ADC_REFSEL_INT1V_gc;
  //BATTERY_ADC_CHANNEL.REFCTRL    = ADC_REFSEL_INTVCC2_gc;//ADC_REFSEL_INT1V_gc;
  BATTERY_ADC_CHANNEL.EVCTRL      = 0x00;
  BATTERY_ADC_CHANNEL.CTRLA      |= ADC_CH0START_bm;
  //  BATTERY_ADC_CHANNEL.CTRLB      |= ADC_CURRLIMIT_HIGH_gc;
//  BATTERY_ADC_CHANNEL.in
  //while(ADCValueRAW[0] == 0);
  //
  }
void PowerManagerClass::EnterNormalMode(void)//после пробуждения жрёт больше!
  {
  n3310LcdClass::DMAActivate();
  set_sleep_mode(SLEEP_MODE_IDLE);
  this->currentSleepEvent  = PowerManagerClass::SLEEP_EVENTS::SLEEP_EVENT_NONE;

  if (PDASettings.isParameterSet(ConfigClass::SETTINGS_RADIO_ON))
    {
    Ar1010.deviceEnable();
    }
  HAL.EnvironmentRarioModule.deviceEnable();
  HAL.EnvironmentRarioModule.HardwareInitialization();
  HAL.EnvironmentRarioModule.receiveBegin();
  //LcdClearUpdate();
  //runlevel_5();
  PDAMenu.SelectDefaultMenu();
  MediaMemory.EnterNormalMode();
  
  this->disableJTAG();
  PR.PRGEN  = 0  /*  |  PR_USB_bm  |  PR_AES_bm    |  PR_EBI_bm  |  PR_RTC_bm  |  PR_EVSYS_bm  |  PR_DMA_bm*/;
  PR.PRPA    = 0    |  PR_DAC_bm/*  |  PR_ADC_bm*/    | PR_AC_bm;
  PR.PRPB    = 0  /*  |  PR_DAC_bm*/  |  PR_ADC_bm    | PR_AC_bm;
  PR.PRPC    = 0  /*  |  PR_TWI_bm*/  |  PR_USART0_bm  | PR_USART1_bm /*  | PR_SPI_bm    |  PR_HIRES_bm    | PR_TC0_bm    | PR_TC1_bm*/;
  PR.PRPD    = 0    |  PR_TWI_bm  |  PR_USART0_bm  | PR_USART1_bm     | PR_SPI_bm/*  |  PR_HIRES_bm */  | PR_TC0_bm /*  | PR_TC1_bm*/;
  PR.PRPE    = 0  /*  |  PR_TWI_bm*/  |  PR_USART0_bm/*  | PR_USART1_bm */  | PR_SPI_bm/*  |  PR_HIRES_bm    | PR_TC0_bm  */  | PR_TC1_bm;
  PR.PRPF    = 0    |  PR_TWI_bm/*  |  PR_USART0_bm*/  | PR_USART1_bm /*  | PR_SPI_bm*/  |  PR_HIRES_bm    | PR_TC0_bm    | PR_TC1_bm;

  this->currentPowerMode  = this->POWER_MODE_NORMAL;
  }
/*
void PowerManagerClass::SleepModeOneSecTick(void)
  {
  if (this->sleepTimer > 0)
    {
    --this->sleepTimer;
    }
  }
bool PowerManagerClass::isInDelayedSleep(void)
  {
  return (this->sleepTimer > 0);
  }
void PowerManagerClass::EnterSleepMode(uint16_t timeInSeconds)
  {
  this->sleepTimer  = timeInSeconds;
  this->EnterNormalMode();
  }
*/
void PowerManagerClass::EnterSleepMode(SLEEP_EVENTS evt)
  {
//  n3310LcdClass::DeactivateDisplay();
  if (this->isInSleepMode())
    {
    return;
    }
  this->currentSleepEvent  = evt;
  /*if (evt == SLEEP_EVENT_EVENT && timeSyncReceivedAtLastOnce == false)
    {
    //should rcv timeSync before
    return;
    }*/
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);
  PR.PRPA    = 0    |  PR_DAC_bm/*  |  PR_ADC_bm*/    | PR_AC_bm;
  PR.PRPB    = 0    |  PR_DAC_bm  |  PR_ADC_bm    | PR_AC_bm;
  MediaMemory.EnterSleepMode();
  Vibro.deactivate();
  BackLight.turnOFF();
  StatusLedPin::SetOutLow();
  Ar1010.deviceDisable();
  HAL.EnvironmentRarioModule.deviceDisable();
  LcdClearUpdate();
  if (InGameEvent_SleepTimer > 0)
    {
    LcdClearCache();
    //StalkerUI.DisplayString(StalkerUI_Class::UI_LCD_LINE_1, STRPOS_STR_NON_PLAYABLE_TIME);
//    StalkerUI.DisplayMenuBody(STRPOS_STR_NON_PLAYABLE_TIME, StalkerUI_Class::UI_MENU_BODY_LINE::UI_MENU_BODY_LINE_0);
    StalkerUI.DisplayMenuBody((char*)"   неигровое", StalkerUI_Class::UI_MENU_BODY_LINE::UI_MENU_BODY_LINE_0);
    StalkerUI.DisplayMenuBody((char*)"     время", StalkerUI_Class::UI_MENU_BODY_LINE::UI_MENU_BODY_LINE_1);
    #warning "[T] in sleep can't read eeprom?"
    //sprintf(Lcd.lcd_buf, "%05d", rand());
    //StalkerUI.DisplayString(StalkerUI_Class::UI_LCD_LINE_2);
    }
  else
    {
    //LcdImage(ImageLowBat);
    PDAMenu.DrawImg(PDAImagesClass::IMAGES::IMG_LOW_BAT);
    }
  n3310LcdClass::DMADeactivate();
  n3310LcdClass::RequestUpdate();
  //M25P05_DeepPowerDown();
  //SOUND_HIFI_DAC_CHANNEL=0;//не надо, т.к. жрёт больше потом =)
  this->currentPowerMode  = this->POWER_MODE_SLEEP;
  }
volatile bool PowerManagerClass::isInSleepMode(void)
  {
  return (this->currentPowerMode  == this->POWER_MODE_SLEEP);
  }
bool PowerManagerClass::isBatteryDischarged(void)
  {
  return (this->GetBatteryVoltage() < this->VOLTAGE_LEVEL_BATTERY_DISCHARGED);
  }
bool PowerManagerClass::isCanWakeup(void)
  {
  switch (this->GetSleepEvent())
    {
    case PowerManagerClass::SLEEP_EVENT_DEVICE_START:
    case PowerManagerClass::SLEEP_EVENT_BATT:
      {
      if (this->GetBatteryVoltage() >= this->VOLTAGE_LEVEL_BATTERY_CAN_WAKEUP)
        {
        return true;
        }
      }
    break;
    case PowerManagerClass::SLEEP_EVENT_EVENT:
      {
      if (InGameEvent_SleepTimer == 0)
        {
        return true;
        }
      }
    break;
    case PowerManagerClass::SLEEP_EVENT_NONE://something goin wrong
      {
      return true;
      }
    break;
    }
  return false;
  }
Milivolts_t PowerManagerClass::GetBatteryVoltage(void)
  {
  return ( ((uint32_t)this->GetBatteryADCValue()) * this->VOLTAGE_LEVEL_BATTERY_FULL)/(BATTERY_ADC_LEVEL_FULL);
//  return (this->getADCValueSum() / (((uint32_t)ADC_BUFFER_SIZE * (BATTERY_ADC_LEVEL_FULL+1))/this->VOLTAGE_LEVEL_BATTERY_FULL));
  }
PowerManagerClass::SLEEP_EVENTS PowerManagerClass::GetSleepEvent(void)
  {
  return this->currentSleepEvent;
  }
//bool PowerManagerClass::isDischarged(void)
//  {
//  return (this->GetBatteryVoltage() < this->VOLTAGE_LEVEL_BATTERY_DISCHARGED);
//  }
Percent_t PowerManagerClass::GetChargePercent(void)
  {
  if (this->isBatteryDischarged())
    {
    return 0;
    }
//  return ((this->getVoltage() - this->VOLTAGE_LEVEL_BATTERY_DISCHARGED) * 100 ) / (this->VOLTAGE_LEVEL_BATTERY_FULL - this->VOLTAGE_LEVEL_BATTERY_DISCHARGED);
  return (this->GetBatteryVoltage() - this->VOLTAGE_LEVEL_BATTERY_DISCHARGED) / ((this->VOLTAGE_LEVEL_BATTERY_FULL - this->VOLTAGE_LEVEL_BATTERY_DISCHARGED)/100);
  
  //return ((this->getADCValue() - this->ADC_LEVEL_BATTERY_DISCHARGED) / (ADC_BUFFER_SIZE/2) );
  }
bool PowerManagerClass::isCharging(void)
  {
  return (ChargerPinCharging::IsPinLow() && ChargerPinStandby::IsPinHigh());
  }
bool PowerManagerClass::isDischarging(void)
  {
  return !(this->isCharging());
  }
void PowerManagerClass::disableJTAG(void)
  {
  CCP      = CCP_IOREG_gc;
  MCU.MCUCR  = MCU_JTAGD_bm;
  }
ADCValue_t PowerManagerClass::GetBatteryADCValue(void)
  {
  return (this->GetBatteryADCValueSum() / ADC_BUFFER_SIZE);
  }
volatile ADCValueSum_t PowerManagerClass::GetBatteryADCValueSum(void)
  {
  #ifdef FAKE_ADC_POWER
    return (BATTERY_ADC_LEVEL_FULL * ADC_BUFFER_SIZE);
  #else
    return ADCValueSum;
  #endif
  /*
  uint8_t first=0;
  uint8_t second=0;
  uint8_t differentValue=0;
  uint8_t differentValueIDX=0;
  for (uint8_t i=1;i<ADC_BUFFER_SIZE;i++)
    {
    if (ADCValueRAW[i] != ADCValueRAW[0])
      {
      differentValueIDX  = i;
      differentValue    = ADCValueRAW[i];
      }
    }
  if (differentValueIDX == 0)//all is the same
    {
    return ADCValueRAW[0];
    }
  for (uint8_t i=0;i<ADC_BUFFER_SIZE;i++)
    {
    if (ADCValueRAW[i] == ADCValueRAW[0])
      {
      first++;
      }
    else if (ADCValueRAW[i] == differentValue)
      {
      second++;
      }
    }
  if (first > second)
    {
    return ADCValueRAW[0];
    }
  return differentValue;
  */
  }
/*void PowerManagerClass::FirstBatteryADCMeasurments(void)
  {
  //BATTERY_ADC_CHANNEL.CTRLA      |= ADC_CH0START_bm;
  //ADCMeasurmentsStarted  = true;
  this->StartBatteryADCMeasurments();
  while(ADCMeasurmentsStarted);
  ADCValue_t tmp  = ADCValueRAWArray[0];
  //uint8_t *ptr  = (uint8_t*)ADCValueRAW;
  ADCValueSum  = tmp * ADC_BUFFER_SIZE;
  //memset ((ADCValue_t*)ADCValueRAWArray, tmp, ADC_BUFFER_SIZE);
  for (uint8_t i=0;i<ADC_BUFFER_SIZE;i++)
    {
    ADCValueRAWArray[i]  = tmp;
    }
  
  }*/
void PowerManagerClass::StartBatteryADCMeasurments(void)
  {
  //BATTERY_ADC_CHANNEL.CTRLA      = ADC_ENABLE_bm;
  BATTERY_ADC_CHANNEL.CTRLA      |= ADC_CH0START_bm;
  ADCMeasurmentsStarted  = true;
  if (this->currentPowerMode == POWER_MODE_UNSELECTED)
    {
    while(ADCMeasurmentsStarted);
    ADCValue_t tmp  = ADCValueRAWArray[0];
    //uint8_t *ptr  = (uint8_t*)ADCValueRAW;
    ADCValueSum  = tmp * ADC_BUFFER_SIZE;
    //memset ((ADCValue_t*)ADCValueRAWArray, tmp, ADC_BUFFER_SIZE);
    for (uint8_t i=0;i<ADC_BUFFER_SIZE;i++)
      {
      ADCValueRAWArray[i]  = tmp;
      }
    this->EnterNormalMode();
    }
  }
void PowerManagerClass::ChargeCheck(void)
  {
  switch (this->lastCHargeState)
    {
    case CHARGE_STATE_DISCHARGING:
      {
      if (this->isCharging())//was discharging, now charging
        {
        this->lastCHargeState  = CHARGE_STATE_CHARGING;
        EventSystem.ExternalEventArrived(EventSystemSpace::EVID_CHGARGE_STATE_CHANGED_TO, (void*)CHARGE_STATE_CHARGING);
        }
      }
    break;

    case CHARGE_STATE_CHARGING:
      {
      if (this->isDischarging())
        {
        this->lastCHargeState  = CHARGE_STATE_DISCHARGING;
        EventSystem.ExternalEventArrived(EventSystemSpace::EVID_CHGARGE_STATE_CHANGED_TO, (void*)CHARGE_STATE_DISCHARGING);
        }
      }
    break;

    case CHARGE_STATES_NUM:
    default:
    break;
    }
  }

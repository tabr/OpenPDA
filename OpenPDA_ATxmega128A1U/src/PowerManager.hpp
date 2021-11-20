/*
  *  PowerManager.h
  *
  *  Created:  2015-08-05  02:06:50
  *    Author:  tabr
  */  


#ifndef  POWERMANAGER_H_
#define  POWERMANAGER_H_


#include  <stdint.h>
#include  <stddef.h>
#include  <avr/io.h>
#include  <string.h>
#include  <avr/sleep.h>

#include  "Runnable.hpp"
#include  "boards/compiler_defines.h"
#include  "ConfigClass.hpp"
//#include  "Driver_AR1010.h"
#include  "stalker/HAL.hpp"
//#include  "pdamenu.h"
//#include  "VibroClass.h"
#include  <n3310LcdClass.hpp>
//#include  <images.h>
#include  <typedefs.h>
/*
extern  uint8_t  ReadSignatureByte(uint16_t  Address);
extern  volatile  bool  ADCMeasurmentsStarted;
extern  volatile  uint8_t  ADCValueRAW[ADC_BUFFER_SIZE];
extern  volatile  uint16_t  ADCValueSum;
extern  ConfigClass  PDASettings;
extern  AR1010  Ar1010;
extern  Class_HAL  HAL;
extern  PDAMenuClass  PDAMenu;
extern  VibroClass  Vibro;
extern  n3310LcdClass  LcdDisplay;

extern  void  M25P05_DeepPowerDown();
*/

class  PowerManagerClass : public ITimerListener
  {
  public:
    enum  POWER_MODES
      {
      POWER_MODE_UNSELECTED,
      POWER_MODE_NORMAL,
      POWER_MODE_SLEEP,
      };
    enum  CHARGE_STATES
      {
      CHARGE_STATE_DISCHARGING,
      CHARGE_STATE_CHARGING,
      CHARGE_STATES_NUM,
      };
    enum  SLEEP_EVENTS
      {
      SLEEP_EVENT_NONE,
      SLEEP_EVENT_DEVICE_START,
      SLEEP_EVENT_BATT,
      SLEEP_EVENT_EVENT,
      };
//    const static uint16_t  ADC_LEVEL_BATTERY_DISCHARGED    =  205*ADC_BUFFER_SIZE;
//    const static uint16_t  ADC_LEVEL_BATTERY_CAN_WAKEUP    =  220*ADC_BUFFER_SIZE;
//    const static uint16_t  ADC_LEVEL_BATTERY_FULL      =  255*ADC_BUFFER_SIZE;
    const static uint16_t VOLTAGE_LEVEL_BATTERY_DISCHARGED    =  3400;//~38h
    const static uint16_t VOLTAGE_LEVEL_BATTERY_LOW        =  3600;
    const static uint16_t VOLTAGE_LEVEL_BATTERY_CAN_WAKEUP    =  3600;
    const static uint16_t VOLTAGE_LEVEL_BATTERY_FULL      =  4200;
    
    void TimerUpdateEvent (uint8_t msPassed);
    
    void  HardwareInitialization(void);
    void  EnterNormalMode(void);
    void  EnterSleepMode(SLEEP_EVENTS  evt);
//    void  EnterSleepMode(uint16_t  timeInSeconds);
//    void  SleepModeOneSecTick(void);
//    bool  isInDelayedSleep(void);
    volatile  bool  isInSleepMode(void);
    bool  isBatteryDischarged(void);
    bool  isCanWakeup(void);
    bool  isCharging(void);
    bool  isDischarging(void);
    //bool  isDischarged(void);
    SLEEP_EVENTS  GetSleepEvent(void);
    Percent_t  GetChargePercent(void);
    Milivolts_t  GetBatteryVoltage(void);
    void  disableJTAG(void);
    //void  FirstBatteryADCMeasurments(void);
    void  StartBatteryADCMeasurments(void);
    void  ChargeCheck(void);
    PowerManagerClass(void);
    
//    volatile  uint8_t  ADCValue        =  0;
  protected:
  private:
    CHARGE_STATES  lastCHargeState=CHARGE_STATE_DISCHARGING;
    ADCValue_t  GetBatteryADCValue(void);
    volatile  ADCValueSum_t  GetBatteryADCValueSum(void);
    POWER_MODES  currentPowerMode=POWER_MODES::POWER_MODE_UNSELECTED;
    SLEEP_EVENTS  currentSleepEvent  =  SLEEP_EVENTS::SLEEP_EVENT_NONE;
//    uint16_t  sleepTimer=0;
  };



#endif  /*  POWERMANAGER_H_  */

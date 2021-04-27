#ifndef ENVIRONMENT_CLASS_H
#define ENVIRONMENT_CLASS_H

//#include "typedefs.h"
typedef uint8_t RadLevel_t;
typedef uint8_t PsyLevel_t;

class Environment : public ITimerListener
  {
  public:

  const static RadLevel_t MAX_RAD_LEVEL        = 100;
  const static uint8_t RAD_DOSE_THRESHOLD        = 150;//не должно быть больше 255-MAX_RAD_LEVEL
  const static uint16_t RADIATION_SOUND_THRESHOLD    = 100;
  const static PsyLevel_t MAX_LEVEL_PSY        = 100;
  const static uint8_t RAD_FILTER_CACHE_LENGTH    = 8;
  const static uint8_t PSY_FILTER_CACHE_LENGTH    = 8;
  //const static uint16_t ANOMALY_SOUND_THRESHOLD    = 200;
//  uint8_t lastAnomalyType;
//  uint8_t anomalyLevel;
//  uint8_t anomalyLevelCounter;
  uint8_t playerRadDoseCollector=0;

  void TimerUpdateEvent (uint8_t msPassed);

  void process(void);                        //вызывается извне
  void RadiationToDoseProcess(void);                  //вызывается извне
  void RadLevelSet1(RadLevel_t value);
  void RadLevelSetFilter(RadLevel_t value);
//  void AnomalyLevelSetFilter(uint8_t value, uint8_t anoType);
//  void AnomalyLevelProcess(void);
  uint8_t GetPsyLevel(void);
  Percent_t GetPsyLevelPercent(void);
  void cleanRadFilter(void);
  void cleanPsyFilter(void);
  void setPsyLevelFilter(PsyLevel_t value);
  RadLevel_t GetRadiationLevel(void);
  Percent_t GetRadiationLevelPercent(void);
  Environment();
  protected:
  private:
    uint16_t radLevelSoundCounter=0;
//    uint16_t anoLevelSoundCounter;
//    uint8_t RadDoseCounter;
//    uint8_t radFilterValue;
    RadLevel_t radiationLevel=0;
    PsyLevel_t psyLevel=0;
    PsyLevel_t psyFilter[PSY_FILTER_CACHE_LENGTH];
    //RingBuffer<PSY_FILTER_CACHE_LENGTH> psyFilterR;
    RadLevel_t radFilter[RAD_FILTER_CACHE_LENGTH];

};
#endif
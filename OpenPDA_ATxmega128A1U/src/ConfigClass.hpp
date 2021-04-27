#ifndef  CONFIG_CLASS_H
#define  CONFIG_CLASS_H

//#include  <stdint.h>
//#include  <stddef.h>
//#include  <avr/io.h>

//#include  "my_defines.h"
//#include  "BackLightClass.h"
//#include  "Driver_AR1010.h"

//extern  BackLightClass  BackLight;
//extern  AR1010  Ar1010;

class  ConfigClass
  {
  public:
    enum  SETTINGS
      {
      SETTINGS_ARTEFACTS_LEDS_ON,
      SETTINGS_BACKLIGHT_ON,
      SETTINGS_RADIO_ON,
      SETTINGS_VIBRO_ON,
      SETTINGS_SWITCH_TO_CONNECTED_ITEM,
      SETTINGS_SWITCH_TO_CONNECTED_ARTEFACT,
      SETTINGS_NIGHT_MODE,
      SETTINGS_PARAMETERS_NUM,
//      SETTINGS_,
      };
    const static uint8_t  SETTINGS_EMPTY          =  0;

    uint8_t  settings;

    ConfigClass(void);
    void  loadDefaultSettings(void);
    bool  isParameterSet(uint8_t  parameter);
    void  switchParameter(uint8_t  parameter);
    void  clearParameter(uint8_t  parameter);
    void  setParameter(uint8_t  parameter);

  protected:
  private:
    void  parameterUpdated(uint8_t  parameter);
  };
#endif
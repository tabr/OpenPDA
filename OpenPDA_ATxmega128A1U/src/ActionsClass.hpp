#ifndef ACTIONS_CLASS_H
#define ACTIONS_CLASS_H

class ActionsClass
  {
  public:
    const static uint8_t ACTION_NONE              = 0;
    const static uint8_t ACTION_SUICIDE           = 1;

    const static uint8_t SUBMENU_ACTION_SUICIDE   = ACTION_SUICIDE - 1;

    const static uint8_t ACTIONS_REASONABLE_NUM   = 1;

    const static uint8_t SUICIDE_START_COUNTER    = 1;
    const static uint8_t SUICIDE_STOP_COUNTER     = 255;
    const static uint8_t SUICIDE_DELAY_SEC        = 10;
  protected:
  private:
  };
#endif

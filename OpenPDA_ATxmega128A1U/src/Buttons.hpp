#ifndef  BUTTONS_CLASS_H
#define  BUTTONS_CLASS_H

#include  "boards/pcb_1.h"
#include  "stalker/TimerClass.hpp"
//#include  "PlayerClass.hpp"

//extern  PlayerClass  Player;
/*
enum  BUTTON_UNLOCK_TIMINGS
  {
  BUTTON_UNLOCK_TIMINGS_100MS,
  };
enum  BUTTON_LOCK_TIMINGS
  {
  BUTTON_LOCK_TIMINGS_50MS,
  };*/

class  ButtonsClass : public ITimerListener
  {
  public:
    const static uint16_t  LOCK_TIME_MS  =  50;
//  const static uint8_t  PIN_MENU      =  0;
//  const static uint8_t  PIN_SELECT      =  1;
//  const static uint8_t  PIN_USE      =  2;
/*
  const static uint8_t  FIRST_PIN      =  Driver_IO::PA0;

  const static uint8_t  PIN_MENU_HAL    =  Driver_IO::PA0;
  const static uint8_t  PIN_SELECT_HAL    =  Driver_IO::PA1;
  const static uint8_t  PIN_USE_HAL    =  Driver_IO::PA2;

  const static uint8_t  LAST_PIN      =  Driver_IO::PA2;
*/
//  const static uint8_t  NUM        =  3;
//  const static uint8_t  LOCK_TIME      =  5;
  enum  BUTTONS
    {
//    BUTTON_MENU,
//    BUTTON_SELECT,
//    BUTTON_USE,
//    BUTTON_MENU_PREV,
    BUTTON_DOWN_ENTER,
    BUTTON_RIGHT,
    BUTTON_CENTER_MENU,
    BUTTON_LEFT,
    BUTTON_UP_ESC,
    BUTTONS_NUM,
//    BUTTON_NONE,
    };
  enum  BUTTON_STATES
    {
    BUTTON_STATE_RELEASED,
    BUTTON_STATE_PRESSED,
    };


  /*class  ButtonsTask1:  public  Runnable
    {
    public:
      void  Task  (void);
      uint8_t  getRepeatTime(void)
        {
        return  TimerClass::TIME_10MS;
        }
    protected:
    private:
    }  TaskScanForPressed;
  class  ButtonsTask2:  public  Runnable
    {
    public:
      void  Task  (void);
      uint8_t  getRepeatTime(void)
        {
        return  TimerClass::TIME_100MS;
        }
    protected:
    private:
    }  TaskTryUnlockButton;*/
  
  
  ButtonsClass  (void);
  void TimerUpdateEvent (uint8_t msPassed);
  void  IOInit(void);
//  void  tryUnlockButton(BUTTON_UNLOCK_TIMINGS  timePassed);
  bool  isButtonLocked(ButtonsClass::BUTTONS  button);
  bool  isButtonUnlocked(ButtonsClass::BUTTONS  button);
  bool  isButtonDown(ButtonsClass::BUTTONS  button);    //нажата  ли  (придавлена  ли)  в  данный  момент  кнопка
  void  lockButton  (ButtonsClass::BUTTONS  button);
  void  eventButtonPressed  (ButtonsClass::BUTTONS  button);              //кагбэ  Event=)
//  void  eventUsePressed  (void);              //кагбэ  Event=)
//  void  eventMenuPressed  (void);              //кагбэ  Event=)
//  void  eventMenuPrevPressed  (void);              //кагбэ  Event=)
//  void  eventSelectPressed  (void);              //кагбэ  Event=)
  void  scanForPressed  (void);                //должна  вызываться  извне
//  ButtonsClass::BUTTONS  getOnePressed(void);
  BUTTON_STATES  getState(ButtonsClass::BUTTONS  button);
  void  setState(ButtonsClass::BUTTONS  button,  BUTTON_STATES  state);
  void  stateChanged(ButtonsClass::BUTTONS  button);
  protected:
  private:
    uint16_t  lockTimers[BUTTONS_NUM];
    BUTTON_STATES  state[BUTTONS_NUM];
  };
#endif
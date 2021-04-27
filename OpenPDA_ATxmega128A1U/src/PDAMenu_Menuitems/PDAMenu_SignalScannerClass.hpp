/*
 * PDAMenu_SignalScannerClass.h
 *
 * Created: 23.09.2018 21:59:48
 *  Author: tabr
 */ 


#ifndef PDAMENU_SIGNALSCANNERCLASS_H_
#define PDAMENU_SIGNALSCANNERCLASS_H_


class PDAMenu_SignalScannerClass : public PDAMenu_MainInterface//, public ITimerListener
  {
  public:
    const static uint8_t passLength = 6;
    //void TimerUpdateEvent (uint8_t msPassed);
    void Update(uint8_t msPassed);
    void JustSelected(void);
    PDAMenu_MainInterface::MENUIDS getID(void);
    void buttonPressed(ButtonsClass::BUTTONS btn);
    bool isSelectable(void)
      {
      return false;
      }
    bool isUsable(void)
      {
      return false;
      }
    uint8_t GetDotPosition(void);
    PDAMenu_SignalScannerClass( uint8_t num, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4, uint8_t p5, uint8_t p6 );
    bool CheckPass(void);
  protected:
  private:
    uint8_t pass[passLength];
    uint8_t userPass[passLength];
    uint8_t num;
    bool IsHacked = false;
    //uint8_t position = 0;
    uint8_t userPassIndex = 0;

    void DisplayEmissionLevel(EmissionInstanceDetectorClass& E);
  };


#endif /* PDAMENU_SIGNALSCANNERCLASS_H_ */
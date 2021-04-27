/*
 * PDAMenu_DebugClass.h
 *
 * Created: 27.04.2017 2:04:05
 *  Author: tabr
 */ 


#ifndef PDAMENU_DEBUGCLASS_H_
#define PDAMENU_DEBUGCLASS_H_


class PDAMenu_DebugClass : public PDAMenu_MainInterface
  {
  public:
    void Update(uint8_t msPassed);
    void JustSelected(void);
    PDAMenu_MainInterface::MENUIDS getID(void);
    void buttonPressed(ButtonsClass::BUTTONS btn);
  protected:
  private:
    uint8_t scroll=0;
    uint16_t updateCounter=0;
  };



#endif /* PDAMENU_DEBUGCLASS_H_ */
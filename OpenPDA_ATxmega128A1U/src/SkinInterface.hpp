/*
 * SkinInterface.h
 *
 * Created: 27.08.2018 21:02:02
 *  Author: tabr
 */ 


#ifndef SKININTERFACE_H_
#define SKININTERFACE_H_

/*
For EACH emission DYNAMICLY create EmissionInstance

*/


class SkinInterface
  {
  public:
    virtual void DrawMainGrid(void)                                                   = 0;
    virtual void DrawPlayerZombie(void)                                               = 0;
    virtual void DrawPlayerDead(void)                                                 = 0;
    virtual void DisplayPlayerHealthPercent(void)                                     = 0;
    virtual void DisplayEmissionLevel(DamageSource_t dmgSrc, Percent_t levelPercent)  = 0;
    virtual ChargeVisualisationInterface* GetChargeVisualisationInterface(void)       = 0;
    virtual void DisplayBlowoutActive(bool isActive)                                  = 0;
    virtual void DisplayPlayerInSafeShelter(bool isInSafeShelter)                     = 0;
    virtual void UpdateMainMenuScreen(void)                                           = 0;
    virtual void UpdatePlayerZombie(void)                                             = 0;
    virtual void UpdatePlayerDead(void)                                               = 0;
    virtual void UpdatePlayerAwaitingGraveyard(void)                                  = 0;
    virtual void Update(uint8_t msPassed)                                             = 0;
  protected:
  private:
  };
class SoundSkinInterface
  {
  public:
  protected:
  private:
  };

#endif /* SKININTERFACE_H_ */
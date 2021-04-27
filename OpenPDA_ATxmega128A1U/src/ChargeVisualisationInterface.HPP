/*
 * ChargeVisualisationInterface.h
 *
 * Created: 27.08.2018 21:01:09
 *  Author: tabr
 */ 


#ifndef CHARGEVISUALISATIONINTERFACE_H_
#define CHARGEVISUALISATIONINTERFACE_H_


class ChargeVisualisationInterface
  {
  public:
    virtual void Display(void)                                      = 0;
    virtual void SetCharging(void)                                  = 0;
    virtual void SetDischarging(void)                               = 0;
    virtual void UpdateChargeVisualisation(Percent_t chargePercent, bool isCharging=false) = 0;
  protected:
  private:
  };



#endif /* CHARGEVISUALISATIONINTERFACE_H_ */
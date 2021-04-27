/*
 * SkinClass.h
 *
 * Created: 27.08.2018 20:58:47
 *  Author: tabr
 */ 


#ifndef SKINCLASS_H_
#define SKINCLASS_H_

#include "ChargeVisualisationInterface.hpp"
#include "SkinInterface.hpp"



class ChargeVisualisationClass : public ChargeVisualisationInterface
  {
  public:
    const static uint8_t positionTopX       = 68;
    const static uint8_t positionTopY       = 0;
    const static uint8_t positionBottomX    = 80;
    const static uint8_t positionBottomY    = 6;

    const static uint8_t smallRectDiff      = (positionBottomY - positionTopY) / 3;
    const static uint8_t smallRectTopY      = positionTopY + smallRectDiff;
    const static uint8_t smallRectBottomY   = positionBottomY - smallRectDiff;

    const static uint8_t smallRectTopX      = positionTopX;

    const static uint8_t smallRectWidth     = (positionBottomX - positionTopX) / 5;
    const static uint8_t smallRectBottomX   = smallRectTopX + smallRectWidth;

    const static uint8_t bigRectTopX        = positionTopX+smallRectWidth;
    const static uint8_t bigRectBottomX     = positionBottomX+smallRectWidth;
    const static uint8_t bigRectTopY        = positionTopY;
    const static uint8_t bigRectBottomY     = positionBottomY;

    const static uint8_t chargeAreaFullX    = bigRectTopX+1;

    const static uint8_t chargeAreaTopX     = bigRectTopX+1;
    const static uint8_t chargeAreaTopY     = bigRectTopY+1;
    const static uint8_t chargeAreaBottomX  = bigRectBottomX-1;
    const static uint8_t chargeAreaBottomY  = bigRectBottomY-1;
    const static uint8_t chargeAreaWidth    = chargeAreaBottomX - chargeAreaTopX;

    void Display(void)
      {
      LcdRect((this->smallRectTopX),  (this->smallRectTopY),  (this->smallRectBottomX),   (this->smallRectBottomY),   PIXEL_ON);//small rect
      LcdRect((this->bigRectTopX),    (this->bigRectTopY),    (this->bigRectBottomX),     (this->bigRectBottomY),     PIXEL_ON);//big rect

      //LcdRect((this->chargeAreaTopX),  (this->chargeAreaTopY),  (this->chargeAreaBottomX),   (this->chargeAreaBottomY),   PIXEL_ON);//small rect
//      LcdRect((smallRectTopX),   (smallRectTopY),  (smallRectBottomX),   (smallRectBottomY),  PIXEL_ON);//small rect
      }
    void SetCharging(void)
      {
      this->animatedX = 0;
      }
    void SetDischarging(void)
      {
      this->animatedX = 0;
      }
    void UpdateChargeVisualisation(Percent_t chargePercent, bool isCharging=false)
      {
//      uint8_t percentPerPixel  = 100/chargeAreaWidth;
      uint8_t pixelDiff   = (this->chargeAreaWidth * chargePercent) / 100;
      uint8_t chargedTo   = this->chargeAreaTopX + this->chargeAreaWidth - pixelDiff;
      if (isCharging)
        {
        if (++this->animatedX + pixelDiff > this->chargeAreaWidth)
          {
          this->animatedX = 0;
          }
        chargedTo -= this->animatedX;
        }

      //char aaa[14];
      //sprintf(aaa, "%02d %02d", chargedTo, pixelDiff);
      //LcdStringUpdate(10, LCD_LINE_6, aaa);

//      chargedTo++;//to make 99% not full

      //if (chargePercent == 100)
        //{
        //LcdLine(chargeAreaFullX, chargeAreaTopY, chargeAreaFullX, chargeAreaBottomY, PIXEL_ON);
        //chargedTo--;//hack!
        //}
      for (uint8_t i=chargeAreaTopY; i<=chargeAreaBottomY; i++)
        {
        LcdLine(this->chargeAreaTopX, i, chargedTo,                i, PIXEL_OFF);
        LcdLine(chargedTo,            i, this->chargeAreaBottomX,  i, PIXEL_ON);

        //LcdLine(this->chargeAreaTopX, i+6, chargedTo,                i+6, PIXEL_OFF);
        //LcdLine(chargedTo,            i+6, this->chargeAreaBottomX,  i+6, PIXEL_ON);
        }
      }
    void Update(uint8_t msPassed);
  protected:
  private:
    uint8_t animatedX=0;
  };
class GenericSkinClass : public SkinInterface
  {
  public:
    const static uint8_t HORIZONTAL_HEALTH_GRID_POS_X1          = 32;
    const static uint8_t HORIZONTAL_PLAYER_RAD_DOSE_GRID_POS_X1 = 16;
    const static uint8_t HORIZONTAL_LCD_MENU_BAR_LINES_BOTTOM   = 34;
    const static uint8_t HORIZONTAL_LCD_MENU_BAR_LINES_TOP      = 1;
    const static uint8_t HORIZONTAL_LCD_MENU_BAR_LINES_NUM      = (HORIZONTAL_LCD_MENU_BAR_LINES_BOTTOM - HORIZONTAL_LCD_MENU_BAR_LINES_TOP);

    const static uint8_t RAD_GRID_POS_X1                        = 0;
    const static uint8_t RAD_GRID_POS_X2                        = 14;
    const static uint8_t RAD_GRID_POS_Y1                        = 0;
    const static uint8_t RAD_GRID_POS_Y2                        = 34;
    const static uint8_t RAD_DISP_POS_X                         = 0;
    const static uint8_t RAD_DISP_POS_Y                         = 36;

    const static uint8_t PLAYER_RAD_DOSE_GRID_POS_X1            = 16;
    const static uint8_t PLAYER_RAD_DOSE_GRID_POS_X2            = 30;
    const static uint8_t PLAYER_RAD_DOSE_GRID_POS_Y1            = 0;
    const static uint8_t PLAYER_RAD_DOSE_GRID_POS_Y2            = 34;

    const static uint8_t HEALTH_GRID_POS_X1                     = 32;
    const static uint8_t HEALTH_GRID_POS_X2                     = 46;
    const static uint8_t HEALTH_GRID_POS_Y1                     = 0;
    const static uint8_t HEALTH_GRID_POS_Y2                     = 34;

    const static uint8_t PSY_HAZARD_GRID_POS_X1                 = 48;
    const static uint8_t PSY_HAZARD_GRID_POS_X2                 = 62;
    const static uint8_t PSY_HAZARD_GRID_POS_Y1                 = 0;
    const static uint8_t PSY_HAZARD_GRID_POS_Y2                 = 34;

    const static uint8_t LCD_MENU_BAR_LINES_BOTTOM              = 34;
    const static uint8_t LCD_MENU_BAR_LINES_TOP                 = 1;
    const static uint8_t LCD_MENU_BAR_LINES_NUM                 = (LCD_MENU_BAR_LINES_BOTTOM-LCD_MENU_BAR_LINES_TOP);


    void DrawMainGrid(void);
    void DrawPlayerZombie(void);
    void DrawPlayerDead(void);
    void DisplayPlayerHealthPercent();
    void DisplayEmissionLevel(DamageSource_t dmgSrc, Percent_t levelPercent);
    void DisplayPercentBar(uint8_t GridPosX1, uint8_t Percent);
    ChargeVisualisationClass* GetChargeVisualisationInterface(void);
    void DisplayPlayerInSafeShelter(bool isInSafeShelter);
    void DisplayBlowoutActive(bool isActive);
    void UpdatePlayerZombie(void);
    void UpdatePlayerDead(void);
    void UpdatePlayerAwaitingGraveyard(void);
    void UpdateMainMenuScreen(void);
    void Update(uint8_t msPassed);
  protected:
  private:
    Percent_t oldHealthPercent=0xFF;
    ChargeVisualisationClass ChargeVisualisation;
  };
class DetectorSkinClass : public SkinInterface
  {
  public:

    void DrawMainGrid(void);
    void DrawPlayerZombie(void);
    void DrawPlayerDead(void);
    void DisplayPlayerHealthPercent();
    void DisplayEmissionLevel(DamageSource_t dmgSrc, Percent_t levelPercent);
    ChargeVisualisationClass* GetChargeVisualisationInterface(void);
    void DisplayPlayerInSafeShelter(bool isInSafeShelter);
    void DisplayBlowoutActive(bool isActive);
    void UpdatePlayerZombie(void);
    void UpdatePlayerDead(void);
    void UpdatePlayerAwaitingGraveyard(void);
    void UpdateMainMenuScreen(void);
    void Update(uint8_t msPassed);
  protected:
  private:
    //Percent_t oldHealthPercent=0xFF;
    ChargeVisualisationClass ChargeVisualisation;
    uint16_t counter=0;
  };
class StalkerSkinClass : public GenericSkinClass
  {
  public:
  protected:
  private:
  };



#endif /* SKINCLASS_H_ */
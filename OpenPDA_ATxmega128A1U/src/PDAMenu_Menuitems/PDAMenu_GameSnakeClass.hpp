/*
  *  PDAMenu_GameSnakeClass.h
  *
  *  Created:  27.04.2017  2:05:58
  *    Author:  tabr
  */  


#ifndef PDAMENU_GAMESNAKECLASS_H_
#define PDAMENU_GAMESNAKECLASS_H_


typedef uint8_t GameSnakeField_t;
class PDAMenu_GameSnakeClass : public PDAMenu_MainInterface
  {
  public:
    enum  MOVES_DIRECTIONS
      {
      MOVES_DIRECTION_UP,
      MOVES_DIRECTION_DOWN,
      MOVES_DIRECTION_LEFT,
      MOVES_DIRECTION_RIGHT,
      };
    void Update(uint8_t msPassed);
    void JustSelected(void);
    PDAMenu_MainInterface::MENUIDS getID(void);
    void buttonPressed(ButtonsClass::BUTTONS  btn);
    /*uint8_t  getSpecs()
      {
      return  (1<<PDAMenu_MainInterface::MENU_SPECS_BIT__BUTTON_INTERCEPTION);
      }*/
    void calculateNextHeadPosition(void);
    void displayBodyDot(int8_t xBody, int8_t yBody, LcdPixelMode PIXEL);
    void goBack(int8_t* x, int8_t* y, MOVES_DIRECTIONS direction);
    bool checkBorderCollision(void);
    bool checkBodyCollision(bool withHeadCheck, int8_t x, int8_t y);
    bool checkFoodAfterMove(void);
    void displayFood();
    void generateNewFood(void);
    void NewFood(void);
    void desideNewMoveDirection(void);
  protected:
  private:
    const static uint8_t Xdiff=0;
    const static uint8_t Ydiff=9;
    const static uint8_t Xlength=16;
    const static uint8_t Ylength=8;
    const static GameSnakeField_t FieldWidth=Xlength*Ylength;

    //uint8_t scroll=0;
    uint16_t updateCounter=0;
    //MOVES_DIRECTIONS moveVect=MOVES_DIRECTION_RIGHT;
    MOVES_DIRECTIONS selectedDirection=MOVES_DIRECTION_RIGHT;
    MOVES_DIRECTIONS pendingDirection=MOVES_DIRECTION_RIGHT;
    int8_t XheadPosition=0;//signed
    int8_t YheadPosition=0;//signed
    int8_t XFoodPosition=0;//signed
    int8_t YFoodPosition=0;//signed
    bool gamePaused = false;
    MOVES_DIRECTIONS body[FieldWidth]={MOVES_DIRECTION_RIGHT};
    GameSnakeField_t bodyLength=1;
  };



#endif  /*  PDAMENU_GAMESNAKECLASS_H_  */

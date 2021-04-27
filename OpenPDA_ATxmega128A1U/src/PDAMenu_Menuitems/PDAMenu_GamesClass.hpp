/*
  *  PDAMenu_GamesClass.h
  *
  *  Created:  27.04.2017  2:06:48
  *    Author:  tabr
  */  


#ifndef  PDAMENU_GAMESCLASS_H_
#define  PDAMENU_GAMESCLASS_H_


class  PDAMenu_GamesClass : public PDAMenu_MainInterface
  {
  public:
    void  Update(uint8_t  msPassed);
    void  JustSelected(void);
    PDAMenu_MainInterface::MENUIDS  getID(void);
    void  buttonPressed(ButtonsClass::BUTTONS  btn);
    bool  isSelectable()
      {
      return  true;
      }
    bool  isUsable()
      {
      return  true;
      }
    void  StopGame(void)
      {
      this->startedGame  =  NULL;
      this->JustSelected();
      }
    uint8_t  getSpecs()
      {
      if  (this->startedGame  !=  NULL)
        {
        return  (1<<PDAMenu_MainInterface::MENU_SPECS_BIT__BUTTON_INTERCEPTION);
        }
      return  0;
      }
  protected:
  private:
    uint8_t  scroll=0;
    uint16_t  updateCounter=0;
    PDAMenu_GameSnakeClass  GameSnake;
    PDAMenu_MainInterface*  startedGame=NULL;
  };



#endif  /*  PDAMENU_GAMESCLASS_H_  */

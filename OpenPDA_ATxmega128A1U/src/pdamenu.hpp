#ifndef PDAMENU_CLASS_H
#define PDAMENU_CLASS_H

#include "PDAMenu_MainInterface.hpp"
#include "PDAMenu_MenuItems.hpp"
#include "Buttons.hpp"
#include "PDAImagesClass.hpp"

class PDAMenuClass : public ITimerListener
  {
  public:
    /*class PDAMenuTask1: public Runnable
      {
      void Task (void);
      uint8_t getRepeatTime(void)
        {
        return TimerClass::TIME_40MS;
        }
      } TaskUpdateInformation;*/
    PDAMenu_MainClass PDAMenu_Main;
    /*
    PDAMenu_ArtefactsConnectedClass PDAMenu_ArtefactsConnected;
    PDAMenu_ConnectedItemClass PDAMenu_ConnectedItem;
    PDAMenu_QuestsClass PDAMenu_Quests;
//    PDAMenuActionsClass PDAMenu_Actions;
    PDAMenu_ActionSuicideClass PDAMenu_ActionSuicide;
    PDAMenu_StatsClass PDAMenu_Stats;
    PDAMenu_LastMeetAnomalyClass PDAMenu_LastMeetAnomaly;
    PDAMenu_SuitClass PDAMenu_Suit;
    PDAMenu_PlayerInfoClass PDAMenu_PlayerInfo;
    PDAMenu_SettingsClass PDAMenu_Settings;
    PDAMenu_PlayerSkillsClass PDAMenu_PlayerSkills;
    PDAMenu_ComputerHackClass PDAMenu_ComputerHack;
    PDAMenu_ActiveEffectsClass PDAMenu_ActiveEffects;
    PDAMenu_UndertakerClass PDAMenu_Undertaker;
    PDAMenu_MagicClass PDAMenu_Magic;
    
    PDAMenu_DebugClass PDAMenu_Debug;
    PDAMenu_GamesClass PDAMenu_Games;
    PDAMenu_TimeTranmitterClass PDAMenu_TimeStranmitter;
    PDAMenu_FMClass PDAMenu_FM;
    PDAMenu_MASTER_ItemClass PDAMenu_MASTER_ItemArtefact;
    PDAMenu_MASTER_ArtefactClass PDAMenu_MASTER_Artefact;
    PDAMenu_MASTER_ReviveActionClass PDAMenu_MASTER_ReviveAction;

    PDAMenuDummyClass PDAMenu_Dummy0;
    PDAMenuDummyClass PDAMenu_Dummy1;
    PDAMenuDummyClass PDAMenu_Dummy2;
    PDAMenuDummyClass PDAMenu_Dummy3;
    */
    
/*
    const static uint8_t RAD_GRID_POS_X1        = 0;
    const static uint8_t RAD_GRID_POS_X2        = 14;
    const static uint8_t RAD_GRID_POS_Y1        = 0;
    const static uint8_t RAD_GRID_POS_Y2        = 34;
    const static uint8_t RAD_DISP_POS_X          = 0;
    const static uint8_t RAD_DISP_POS_Y          = 36;

    const static uint8_t PLAYER_RAD_DOSE_GRID_POS_X1  = 16;
    const static uint8_t PLAYER_RAD_DOSE_GRID_POS_X2  = 30;
    const static uint8_t PLAYER_RAD_DOSE_GRID_POS_Y1  = 0;
    const static uint8_t PLAYER_RAD_DOSE_GRID_POS_Y2  = 34;

    const static uint8_t HEALTH_GRID_POS_X1        = 32;
    const static uint8_t HEALTH_GRID_POS_X2        = 46;
    const static uint8_t HEALTH_GRID_POS_Y1        = 0;
    const static uint8_t HEALTH_GRID_POS_Y2        = 34;

    const static uint8_t PSY_HAZARD_GRID_POS_X1      = 48;
    const static uint8_t PSY_HAZARD_GRID_POS_X2      = 62;
    const static uint8_t PSY_HAZARD_GRID_POS_Y1      = 0;
    const static uint8_t PSY_HAZARD_GRID_POS_Y2      = 34;

    const static uint8_t LCD_MENU_BAR_LINES_BOTTOM    = 34;
    const static uint8_t LCD_MENU_BAR_LINES_TOP      = 1;
    const static uint8_t LCD_MENU_BAR_LINES_NUM      = LCD_MENU_BAR_LINES_BOTTOM-LCD_MENU_BAR_LINES_TOP;
*/




    const static uint8_t MAXIMIM_MENUID           = 0xFF;//TODO??!
    enum SUBMENU_SPECS
      {
      SUBMENU_SPECS_STATS,
      SUBMENU_SPECS_LAST_MEET_ANOMALY,
      SUBMENU_SPECS_SUITE,
      SUBMENU_SPECS_PLAYER,
      SUBMENU_SPECS_NUM,
      };
    //const static char HEADS[PDAMenuClass::MENUID_NUM][14];//ниже


    PDAMenuClass(void);
    
    void TimerUpdateEvent (uint8_t msPassed);
    
    void UpdateInformation(uint8_t msPassed);                        //вызывается ИЗВНЕ периодически для обновления информции в кэше
    void SelectMenu(uint8_t menuID);                      //выбрать меню
    void SelectMenu(PDAMenu_MainInterface* m);
    PDAMenu_MainInterface* GetMenu(uint8_t menuID);
    //void displayPercentBar(uint8_t GridPosX1, uint8_t Percent);
    void DeathScreen(void);
    void menuItemSelected(PDAMenu_MainInterface* m);
    uint8_t getSelectedMenuID(void);
    void SelectDefaultMenu(void);
    void buttonPressed(ButtonsClass::BUTTONS btn);
    bool SetDefaultMenu(PDAMenu_MainInterface* m);
    PDAMenu_MainInterface* GetDefaultMenu(void);
    void DrawImg(PDAImagesClass::IMAGES img);

  protected:
  private:
    PDAMenu_MainInterface* defaultMenu;
//    uint8_t selectedMenuID;
    uint8_t selectedSubMenuID;
    uint8_t maxSubMenuID;
    bool subMenuJustSelected;
    PDAMenu_MainInterface* m_selectedMenu;
  };
#endif
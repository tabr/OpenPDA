// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * RuntimeClass.cpp
 *
 * Created: 09.10.2017 15:17:08
 *  Author: tabr
 */ 
void RuntimeClass::Run(void)
  {
  Level0();
  //runlevel_0();
#ifndef LOAD_SOUNDS
  Level1();
  //runlevel_1();
  Level2();
  //runlevel_2();
  Level3();
  //runlevel_3();
  Level4();
  //runlevel_4();
  Level5();
  //runlevel_5();
  Level6();
  //runlevel_6();
  Level7();
#endif //LOAD_SOUNDS
  }
void RuntimeClass::Level0(void)
  {
  SetLevel(RUNLEVEL_0);
  //BackLight.IOInit();
  n3310LcdClass::IOInit();
  StatusLedPin::SetOutLow();
  StatusLedPin::SetDirOut();//Так - нормально?
  n3310LcdClass::HardwareInitialization();
  #ifdef DEBUG_BUILD
    //sprintf (lcd_buf, "runlevel 0");
    LcdString(1,LCD_LINE_1, (char*)"runlevel 0");
    LcdString(1,LCD_LINE_2, (char*)"XTAL...");
    n3310LcdClass::RequestUpdate();
  #endif
  //BackLight.turnON();
  HAL.GetClock()->SelectMaxExternal();
//  HAL.Clock.select_16x2_MHZExternal();
//  n3310LcdClass::IOInit();
//  n3310LcdClass::HardwareInitialization();
//  HAL.Clock.init_32MHZ_oscillator();
//  _delay_ms(100);
  /*
  sysclk_enable_module(SYSCLK_PORT_GEN, SYSCLK_RTC);
  //sysclk_enable_module(SYSCLK_PORT_GEN, SYSCLK_AES);
  
  sysclk_enable_module(SYSCLK_PORT_B, SYSCLK_DAC);

  sysclk_enable_module(SYSCLK_PORT_C, SYSCLK_TWI);
  sysclk_enable_module(SYSCLK_PORT_C, SYSCLK_SPI);
  sysclk_enable_module(SYSCLK_PORT_C, SYSCLK_TC0);

  sysclk_enable_module(SYSCLK_PORT_D, SYSCLK_TC1);

  sysclk_enable_module(SYSCLK_PORT_E, SYSCLK_TWI);
  sysclk_enable_module(SYSCLK_PORT_E, SYSCLK_SPI);
  sysclk_enable_module(SYSCLK_PORT_E, SYSCLK_TC0);


  sysclk_enable_module(SYSCLK_PORT_F, SYSCLK_SPI);
  */
//  Lcd_dma_init();
  #ifdef DEBUG_BUILD
    LcdStringUpdate(1,LCD_LINE_2, (char*)"Completed     ");
  #endif
  //_delay_ms(3000);
  }
#ifndef LOAD_SOUNDS
void RuntimeClass::Level1(void)
  {
  SetLevel(RUNLEVEL_1);
  #ifdef DEBUG_BUILD
  LcdString(1,LCD_LINE_1, (char*)"runlevel 1");
  LcdEmptyString(LCD_LINE_2);
  n3310LcdClass::RequestUpdate();
  #endif
  HAL.IOInit();
  Vibro.IOInit();
  BackLight.IOInit();
  Player.GetArtefactPorts()->IOInit();
  Buttons.IOInit();
  PDASound.IOInit();
  
  MediaFlashPinClk::SetDirOut();
  MediaFlashPinClk::SetOutHigh();

  MediaFlashPinMiso::SetDirIn();

  MediaFlashPinMosi::SetDirOut();
  MediaFlashPinMosi::SetOutHigh();

  MediaFlashPinSS::SetDirOut();
  MediaFlashPinSS::SetOutHigh();//deactivate
  
  ChargerPinCE::SetDirOut();
  ChargerPinCE::SetOutHigh();
  ChargerPinCharging::SetDirIn();
  ChargerPinCharging::SetPullUp();
  ChargerPinStandby::SetDirIn();
  ChargerPinStandby::SetPullUp();

  
  VBUSPin::SetDirIn();
  VBUSPin::SetPullDown();




  #ifdef DEBUG_BUILD
  LcdStringUpdate(1,LCD_LINE_2, (char*)"Completed     ");
  #endif
  }
void RuntimeClass::Level2(void)
  {
  SetLevel(RUNLEVEL_2);
  #ifdef DEBUG_BUILD
    LcdString(1,LCD_LINE_1, (char*)"runlevel 2");
    LcdEmptyString(LCD_LINE_2);
    n3310LcdClass::RequestUpdate();
  #endif

  #ifdef DEBUG_BUILD
    LcdStringUpdate(1,LCD_LINE_2, (char*)"ArtefactPortHW");
  #endif
  Player.GetArtefactPorts()->HardwareInitialization();

  #ifdef DEBUG_BUILD
    LcdStringUpdate(1,LCD_LINE_2, (char*)"UsableItem TWI");
  #endif
  UsableItemTWI::HardwareInitialization();

  #ifdef DEBUG_BUILD
    LcdStringUpdate(1,LCD_LINE_2, (char*)"Ext EEPROM TWI");
  #endif
  ExternalEEPROMTWI::HardwareInitialization();

  #ifdef DEBUG_BUILD
    LcdStringUpdate(1,LCD_LINE_2, (char*)"stalker layer ");
  #endif
  if (Buttons.isButtonDown(ButtonsClass::BUTTON_UP_ESC))
    {
    USBBoot();
    }
  StalkerLayer2 = new Class_StalkerLayer2();
  StalkerLayer2->HardwareInitialization();
  if (!(StalkerLayer2->L1.L0.isModuleReadyToWork()))
    {
    //LcdStringUpdate(1,LCD_LINE_2, (char*)"err RM0");
    StalkerUI.DisplayMenuBody(STRPOS_STR_ERROR_RM0);
    n3310LcdClass::RequestUpdate();
    while(1);
    }
  /*
//  MediaMemory.EraseDevice();
  //_delay_ms(3000);
//  char fname[]="hui.txt";
//  uint8_t data[]={1,2,3,4,5,6,7,8,9};
  uint8_t data2[32]={0,0,0,0,0,0,0,0,0,0,0};
//  bool result = TFS.WriteNewFile(fname, 0, data, sizeof(data));
  //MediaMemory.WriteData(0,0,0,data, (uint16_t)8);
//  _delay_ms(100);
  uint8_t i=0;
  TFSFileClass file;
  //UNION_UINT32_LITTLE_ENDIAN file_addr;
  //file_addr.value_int = 8192;
  //file.SeekByPosition(2);
  while(1)
    {
    file.SeekByPosition(i);
    //TFS.ReadFileHeadInPosition(1, data2);
    //MediaMemory.ReadData(0,0,32, data2, (uint16_t)32);
    //MediaMemory.ReadData(file_addr.byte_field.mh, file_addr.byte_field.ml, file_addr.byte_field.l, data2, (uint16_t)32);

    //sprintf (Lcd.lcd_buf, "%03u %01u %03u",++i, result, file.ReadData(data2,2));
    sprintf (Lcd.lcd_buf, "%03u %03u",++i, file.ReadData(data2,2));
    //sprintf (Lcd.lcd_buf, "%03u %01u %03u",++i, result, file.WriteData(&data[3],2));
    LcdString(LCD_LINE_1);
    //sprintf (Lcd.lcd_buf, "%03u%03u %03u%03u",data2[0], data2[1], data2[2], data2[3]);
    //TFS.
    //sprintf (Lcd.lcd_buf, "%03u%03u %03u%03u",data2[0]);
//    sprintf (Lcd.lcd_buf, "%s %03u",file.GetName(), file.GetStartClusterAddr());
    sprintf (Lcd.lcd_buf, "%s %03u",file.GetName(), file.GetSizeBytes());
    LcdString(LCD_LINE_2);

    sprintf (Lcd.lcd_buf, "%03u%03u %03u%03u",data2[0], data2[1], data2[2], data2[3]);
    LcdStringUpdate(1,LCD_LINE_6, Lcd.lcd_buf);
    _delay_ms(500);
    }
    */




  #ifdef DEBUG_BUILD
    LcdStringUpdate(1,LCD_LINE_2, (char*)"RTC           ");
  #endif
  Stalker.InitRTC();
  #ifdef DEBUG_BUILD
    LcdStringUpdate(1,LCD_LINE_2, (char*)"Interrupts    ");
  #endif
  Stalker.InitInterrupts();
  #ifdef DEBUG_BUILD
    LcdStringUpdate(1,LCD_LINE_2, (char*)"PDASound      ");
  #endif
  PDASound.HardwareInitialization();
  #ifdef DEBUG_BUILD
    LcdStringUpdate(1,LCD_LINE_2, (char*)"PrgStart...   ");
  #endif
  StalkerLayer2->programmStart();

  /*#ifndef FM_DISABLED
    #ifdef DEBUG_BUILD
      sprintf (lcd_buf, "FM module     ");
      LcdString(1,LCD_LINE_2);
      LcdUpdate();
    #endif
    //twi_init(fm);
  #endif*/
  #ifdef DEBUG_BUILD
    LcdStringUpdate(1,LCD_LINE_2, (char*)"RFM AR1010[1]");
  #endif
  //_delay_ms(1000);
  Ar1010.deviceEnable();
  #ifdef DEBUG_BUILD
    LcdStringUpdate(1,LCD_LINE_2, (char*)"RFM AR1010[2]");
  #endif
  Ar1010.HardwareInitialization();
  //_delay_ms(1000);

  #ifdef DEBUG_BUILD
    LcdStringUpdate(1,LCD_LINE_2, (char*)"PowerManager");
  #endif
  PowerManager.HardwareInitialization();

  #ifdef DEBUG_BUILD
    LcdStringUpdate(1,LCD_LINE_2, (char*)"Completed     ");
  #endif
  }
void RuntimeClass::Level3(void)
  {
  SetLevel(RUNLEVEL_3);
  #ifdef DEBUG_BUILD
  LcdString(1,LCD_LINE_1, (char*)"runlevel 3");
  LcdEmptyString(LCD_LINE_2);
  n3310LcdClass::RequestUpdate();
  #endif

  #ifdef DEBUG_BUILD
  LcdStringUpdate(1,LCD_LINE_2, (char*)"Events        ");
  #endif
  /*
  //Moved to constructors
  EventSystem.registerUserEvent(EventSystemSpace::EVID_DAMAGE_TAKEN, &damageTaken);
  //EventSystem.registerUserEvent(&usableItem_ConnDisconn,      EventSystemClass::EVID_USABLE_ITEM_CONNECTED_DISCONNECTED);
  EventSystem.registerUserEvent(EventSystemSpace::EVID_CHGARGE_STATE_CHANGED_TO, &PDAMenu_Main_ChargeStateChanged);
  //EventSystem.registerUserEvent(&EnvironmentProcessed,        EventSystemClass::EVID_ENVIRONMENT_PROCESSED);
  */
  EventSystem.RegisterUserEvent(EventSystemSpace::EVID_DAMAGE_TAKEN, &Player);
  
  
  //Timer.addTask(Anomaly.TaskProcess);                //01[p]
  //Timer.addTask(StalkerLayer2->TaskEnvironmentLookAround);      //02
  //Timer.addTask(StalkerLayer2->TaskEnvironmentProcess);      //03[p]
  //Timer.addTask(Player.getArtefactPorts()->TaskScanForConnected);        //04[p]
  //Timer.addTask(Player.getArtefactPorts()->TaskLedFlashProcess);        //05
  //Timer.addTask(PDAMenu.TaskUpdateInformation);          //06
  //Timer.addTask(Env.TaskEnvironmentProcess);            //07[p] caall moved to StalkerLayer2->TaskEnvironmentProcess
  //Timer.addTask(UsableItem.TaskScanForConnectedIfNeed);      //08[p]
  //Timer.addTask(UsableItem.TaskLedOnTick);            //09
  //  Timer.addTask(userFunction100msTask);              //10
  //Timer.addTask(userFunction1000msTask);              //10[p]
  //Timer.addTask(Player.TaskOneSecondPassed);            //11[p]
  //  Timer.addTask(Buttons.TaskScanForPressed);            //12[p/2]
  //  Timer.addTask(Buttons.TaskTryUnlockButton);            //13
  //Timer.addTask(Player.getEffects()->TaskPlayerEffectsProcess);      //14[p]
  //Timer.addTask(Vibro.TaskUpdateState);              //15
  //Timer.addTask(PowerManager.PowerManagerADCMeasuremntsTask);    //16??!
  //Timer.addTask(InGameEvents.TInGameEventsClass1secCheckStateTask);
  
  #ifdef DEBUG_BUILD
  LcdStringUpdate(1,LCD_LINE_2, (char*)"Timers        ");
  #endif
  TimerMS.RegisterListener(&Buttons);
  TimerMS.RegisterListener(&InGameEvents);
  TimerMS.RegisterListener(&PowerManager);
  TimerMS.RegisterListener(&Vibro);
  TimerMS.RegisterListener(&UsableItem);
  TimerMS.RegisterListener(Player.GetArtefactPorts());
  TimerMS.RegisterListener(&Env);
  TimerMS.RegisterListener(StalkerLayer2);
  TimerMS.RegisterListener(&Player);
  TimerMS.RegisterListener(&Anomaly);
  TimerMS.RegisterListener(&PDAMenu);
  //TimerMS.RegisterListener(Player.GetEffects());
  TimerMS.RegisterListener(&userFunction1000msTask);
  TimerMS.RegisterListener(&BackLight);
  TimerMS.RegisterListener(&PlayerEffects);
  TimerMS.RegisterListener(&EmissionInstanceDetector);
  TimerMS.RegisterListener(&PDASound);
  
  
  //  InGameEvents.registerNew(10,02, 10,02, 2, BlowoutEvent);
  
  
  //  Timer.addTask(PlayerEffectsNG.TaskPlayerEffectsNGOneSecondTick);//17??!
  #ifdef DEBUG_BUILD
  LcdStringUpdate(1,LCD_LINE_2, (char*)"INT. starting ");
  #endif
  sei();
  #ifdef DEBUG_BUILD
  LcdStringUpdate(1,LCD_LINE_2, (char*)"Completed     ");
  #endif
  }
void RuntimeClass::Level4(void)
  {
  SetLevel(RUNLEVEL_4);
  //runlevel_4();
  n3310LcdClass::DMAActivate();

  #ifdef DEBUG_BUILD
    LcdString(1,LCD_LINE_1, (char*)"runlevel 4");
    LcdEmptyString(LCD_LINE_2);
    n3310LcdClass::RequestUpdate();
  #endif

  #ifdef DEBUG_BUILD
    LcdStringUpdate(1,LCD_LINE_2, (char*)"PDASettingsLoa");
  #endif
  PDASettings.loadDefaultSettings();
  
  #ifdef DEBUG_BUILD
    LcdStringUpdate(1,LCD_LINE_2, (char*)"First Batt ADC");
  #endif
  PowerManager.StartBatteryADCMeasurments();
  
  
  //              имя        [макс.прочность]  [защ.пси]  [защ.хим]  [защ.электро]  [защ.огонь]  [защ.рад]  [защ.грав]  [макс.контейнеров]
//  GameCFG.SuitsContainer.registerNew("(пусто)",    0,          0,      0,      0,        0,      0,      0,      1);
//  GameCFG.SuitsContainer.registerNew("к.сталкера",  100,        0,      25,      25,        25,      25,      25,      3);
//  GameCFG.SuitsContainer.registerNew("сева",      150,        10,      70,      90,        80,      90,      50,      5);

//  char string0[DeviceConfigClass::ITEM_NAME_CHAR_ARRAY_LENGTH];
  /*
  //eeprom_write_block(string0,(void *)128,15);
//  strcpy(string0, "(пусто)");
  eeprom_read_block(string0,(void *)128,15);
  if (string0[0] == 0xFF)
    {
    char tmp[15]  = "(пусто)       ";
    eeprom_write_block(tmp,(void *)128,15);
    sprintf(tmp,"к.сталкера    ");
    eeprom_write_block(tmp,(void *)(128+15),15);
    sprintf(tmp,"сева          ");
    eeprom_write_block(tmp,(void *)(128+30),15);


    sprintf (lcd_buf,"ЕЕПРОМ обновлён");
    LcdString(1,LCD_LINE_5);
    LcdUpdate();
    while (1);
    }
  */
//  char string0[15]="сева";
  //eeprom_read_block(string0,(void *)128,15);
//  sprintf(string0,  "(пусто)       ");
//                            имя              [макс.прочность]  [защ.пси]  [защ.хим]  [защ.электро]  [защ.огонь]  [защ.рад]  [защ.грав]  [макс.контейнеров]
//  GameCFG.SuitsContainer.registerNew(new SuitExample((char*)("(пусто)"),      0,          0,      0,      0,        0,      0,      0,      1));
  //eeprom_read_block(string0,(void *)(128+15),15);
//  sprintf(string0,  "к.сталкера    ");
//  GameCFG.SuitsContainer.registerNew(new SuitExample((char*)("к.сталкера"),    100,        0,      25,      25,        25,      25,      25,      3));
  //eeprom_read_block(string0,(void *)(128+30),15);
//  sprintf(string0,  "сева          ");
//  GameCFG.SuitsContainer.registerNew(new SuitExample((char*)("сева"),        150,        10,      70,      90,        80,      90,      50,      5));


  //При версии протокола 1, вся нижеследующая дрянь должна лежать последовательно по 2 байта с начала ЕЕПРОМа, т.е. надо прочитать
  //"EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_SIZE" байт

  EEPROM_Data.setDataSize(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_VERSION,        2);
  EEPROM_Data.setDataSize(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_DEFENCE_SELF,  TemporaryClass::DAMAGE_SOURCE_NUM);
  EEPROM_Data.setDataSize(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_NAME,      TemporaryClass::PLAYER_NAME_LENGTH);
  EEPROM_Data.setDataSize(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_STATISTICS,    (1 + TemporaryClass::ITEMS_NUM));
  EEPROM_Data.setDataSize(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_SKILLS,      PlayerSkillsClass::SKILLS_NUM);
  EEPROM_Data.setDataSize(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_QUESTS,        TemporaryClass::QUESTS_NUM);
  EEPROM_Data.setDataSize(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_VARS,      EEPROM_DataClass::PLAYER_VARS::PLAYER_VARS_SIZE);
  EEPROM_Data.setDataSize(EEPROM_DataClass::EEPROM_STRUCTURE::EEPROM_STRUCTURE_PLAYER_ACTIVE_EFFECTS,  PlayerEffectsClass::STORAGE_SIZE);
  EEPROM_Data.finishConfiguration();

  GameCFG.SetDamageSourcesNum(TemporaryClass::DAMAGE_SOURCE_NUM);
  /*
  GameCFG.registerDamageSource(TemporaryClass::DAMAGE_SOURCE_NONE);
  GameCFG.registerDamageSource(TemporaryClass::DAMAGE_SOURCE_GENERIC);
  GameCFG.registerDamageSource(TemporaryClass::DAMAGE_SOURCE_SELF);
  GameCFG.registerDamageSource(TemporaryClass::DAMAGE_SOURCE_RADIATION_EXTERNAL);
  GameCFG.registerDamageSource(TemporaryClass::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL);
  GameCFG.registerDamageSource(TemporaryClass::DAMAGE_SOURCE_FIRE);
  GameCFG.registerDamageSource(TemporaryClass::DAMAGE_SOURCE_ELECTRICITY);
  GameCFG.registerDamageSource(TemporaryClass::DAMAGE_SOURCE_CHEMICAL);
  GameCFG.registerDamageSource(TemporaryClass::DAMAGE_SOURCE_GRAVY);
  GameCFG.registerDamageSource(TemporaryClass::DAMAGE_SOURCE_PSY);
  GameCFG.registerDamageSource(TemporaryClass::DAMAGE_SOURCE_BIO);
  GameCFG.registerDamageSource(TemporaryClass::DAMAGE_SOURCE_BLOWOUT);
  */
  


  #include "GameTemplate_Effects.hpp"
  #include "GameTemplate_Radiomarks.hpp"
  #include "GameTemplate_Factions.hpp"
  #include "GameTemplate_Anomalies.hpp"
  #include "GameTemplate_Items.hpp"
  #include "GameTemplate_Suites.hpp"
  #include "GameTemplate_Quests.hpp"
  #include "GameTemplate_Artefacts.hpp"

  #include "GameTemplate_PDAMenu.hpp"
  #include "GameTemplate_InGameEvents.hpp"
  

  

  #ifdef DEBUG_BUILD

    LcdStringUpdate(1,LCD_LINE_2, (char*)"wrt Art Erase ");
    //Player.GetArtefactPorts()->M25P05_BulkErase(0);
    Player.GetArtefactPorts()->SetPortOut(0);
    Artefact00.EraseDevice();    

    LcdStringUpdate(1,LCD_LINE_2, (char*)"wrt Art Write ");
    //                                  subtype                                        param [0-3][charges,value,delay]
    //[EXCLUDED]uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_MEDICAMENTS,  0,    ItemsClass::ITEMID_FIRST_AID,      ArtefactPortsClass::DEVICE_STATUS_OK,  0b11111111, 15,  50,0};
    //[EXCLUDED]uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_MEDICAMENTS,  0,    ItemsClass::ITEMID_ANTIRAD,        ArtefactPortsClass::DEVICE_STATUS_OK,  0, 4,  0,0};
    //[EXCLUDED]uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_MEDICAMENTS,  0,    ItemsClass::ITEMID_PSY_BLOKADA,      ArtefactPortsClass::DEVICE_STATUS_OK,  0b11111111, 0,  0,0};
    //[EXCLUDED]uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_MEDICAMENTS,  0,    ItemsClass::ITEMID_RAD_PROTECOR,    ArtefactPortsClass::DEVICE_STATUS_OK,  0b11111111, 0,  0,0};
    //[EXCLUDED]uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_MEDICAMENTS,  0,    ItemsClass::ITEMID_VODKA,        ArtefactPortsClass::DEVICE_STATUS_OK,  0b11111111, 0,  0,0};
    //[EXCLUDED]uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_SUIT,      0,    PlayerSuitClass::SUIT_ID_SEVA,      ArtefactPortsClass::DEVICE_STATUS_OK,  100, 0,  0,0};
    //[EXCLUDED]uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_SUIT,      0,    PlayerSuitClass::SUIT_ID_STALKER_SUIT,  ArtefactPortsClass::DEVICE_STATUS_OK,  100, 0,  0,0};


    //uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_ARTEFACT,    0,    ArtefactClass::ARTEFACT_PLENKA, 0,0, 0, 0, 0};
    //uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_ARTEFACT,    0,    ArtefactClass::ARTEFACT_OGN_SHAR, 0,0, 0, 0, 0};
    //uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_ARTEFACT,    0,    TemporaryClass::ARTEFACTID_LUN_SVET, 0,0, 0, 0, 0};
    //uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_ARTEFACT,    0,    TemporaryClass::ARTEFACTID_VSPYSHKA, 0,0, 0, 0, 0};
    //uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_ARTEFACT,    0,    TemporaryClass::ARTEFACTID_MEDUSA, 0,0, 0, 0, 0};
    //uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_ARTEFACT,    0,    ArtefactClass::ARTEFACT_DUWA, 0,0, 0, 0, 0};
//    uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_ARTEFACT,    0,    ArtefactClass::ARTEFACT_KAM_CVETOK, 0,0, 0, 0, 0};
    //uint8_t item[8]={ArtefactPortsClass::ITEM_TYPE_ARTEFACT,    0,    TemporaryClass::ARTEFACTID_PUSTIWKA, 0,0, 0, 0, 0};
    //Player.GetArtefactPorts()->M25P05_wholeItemWrite(0, item);
    
    //Artefact00.WriteData(item, 8);
    //Player.GetArtefactPorts()->SetPortIn(0);

    LcdStringUpdate(1,LCD_LINE_1, (char*)"4.5");
    
    UsableItem.SetConnectedItem(UsableItemClass::ITEM_TYPE_MEDICAMENTS, UsableItemClass::ITEM_SUBTYPE_NONE, 1, UsableItemClass::DEVICE_STATUS_OK, 0xFF, 0, 0, 0);
    //UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_MEDICAMENTS, UsableItemClass::ITEM_SUBTYPE_NONE, TemporaryClass::ITEMID_BANDAGE, UsableItemClass::DEVICE_STATUS_OK, 10, 0, 0, 0);
    //UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_MEDICAMENTS, UsableItemClass::ITEM_SUBTYPE_NONE, TemporaryClass::ITEMID_ANTIRAD, UsableItemClass::DEVICE_STATUS_OK, 8, 0, 0, 0);
    //UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_MEDICAMENTS, UsableItemClass::ITEM_SUBTYPE_NONE, TemporaryClass::ITEMID_VODKA, UsableItemClass::DEVICE_STATUS_OK, 100, 0, 0, 0);
    //UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_MEDICAMENTS, UsableItemClass::ITEM_SUBTYPE_NONE, TemporaryClass::ITEMID_RAD_PROTECTOR, UsableItemClass::DEVICE_STATUS_OK, 100, 0, 0, 0);
    //UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_MEDICAMENTS, UsableItemClass::ITEM_SUBTYPE_NONE, ItemsClass::ITEMID_PSY_BLOKADA, UsableItemClass::DEVICE_STATUS_OK, 130, 0, 0, 0);
    //UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_ELSE, UsableItemClass::ITEM_SUBTYPE_NONE, TemporaryClass::ITEMID_REPAIR_KIT, UsableItemClass::DEVICE_STATUS_OK, 255, 0, 0, 0);
    //UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_SUIT, UsableItemClass::ITEM_SUBTYPE_NONE, GameConfig::SUIT_ID_SEVA, UsableItemClass::DEVICE_STATUS_OK, 100, 0, 0, 0);
//    UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_SUIT, UsableItemClass::ITEM_SUBTYPE_NONE, TemporaryClass::SUIT_ID_SEVA, UsableItemClass::DEVICE_STATUS_OK, 208, 7, 0, 0);
//    UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_SUIT, UsableItemClass::ITEM_SUBTYPE_NONE, TemporaryClass::SUIT_ID_SEVA, UsableItemClass::DEVICE_STATUS_OK, (uint16_t)1000, 0, 0);
//    UsableItem.SetConnectedItem(UsableItemClass::ITEM_TYPE_SUIT, UsableItemClass::ITEM_SUBTYPE_NONE, TemporaryClass::SUIT_ID_ZARYA, UsableItemClass::DEVICE_STATUS_OK, 0xFF,0xFF, 0, 0);
    //UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_SUIT, UsableItemClass::ITEM_SUBTYPE_NONE, GameConfig::SUIT_ID_NONE, UsableItemClass::DEVICE_STATUS_OK, 0, 0, 0, 0);
    //UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_INFORMATION, UsableItemClass::ITEM_SUBTYPE_NONE, ItemInformationClass::ID_FOUND_SEVA, UsableItemClass::DEVICE_STATUS_OK, 0, 0, 0, 0);
    //UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_INFORMATION, UsableItemClass::ITEM_SUBTYPE_NONE, ItemInformationClass::ID_CODE, UsableItemClass::DEVICE_STATUS_OK, 0, 0, 0, 0);
    //UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_INFORMATION, UsableItemClass::ITEM_SUBTYPE_NONE, ItemInformationClass::ID_GOOUT, UsableItemClass::DEVICE_STATUS_OK, 0, 0, 0, 0);
    //UsableItem.setConnectedItem(UsableItemClass::ITEM_TYPE_INFORMATION, UsableItemClass::ITEM_SUBTYPE_NONE, ItemInformationClass::ID_NONE, UsableItemClass::DEVICE_STATUS_OK, 8, 0, 0, 0);
    
    //UsableItem.setConnectedItem(1, 2, 3, 4, 5, 6, 7, 8);
    UsableItem.WriteConnectedItem();
    UsableItem.CleanConnectedItem();
    /*
    char tmp[9];
    sprintf(tmp, "сталкер ");//последняя отбросится
    UsableItem.hardware.writeToDevice(UsableItemClass::ITEM_INFORMATION_HEAD_PAGE, (uint8_t*)tmp);
    sprintf(tmp, "'ЗЕТ':");
    UsableItem.twi_write_page(UsableItemClass::ITEM_INFORMATION_HEAD_PAGE+1, (uint8_t*)tmp);
    */
    /*
    sprintf(tmp, "Нашел СЕ");//последняя отбросится
    UsableItem.twi_write_page(UsableItemClass::ITEM_INFORMATION_DATA_PAGE, (uint8_t*)tmp);
    sprintf(tmp, "ВУ. ЭТО ");
    UsableItem.twi_write_page(UsableItemClass::ITEM_INFORMATION_DATA_PAGE+1, (uint8_t*)tmp);
    sprintf(tmp, "оставлю ");//последняя отбросится
    UsableItem.twi_write_page(UsableItemClass::ITEM_INFORMATION_DATA_PAGE+2, (uint8_t*)tmp);
    sprintf(tmp, "тут.    ");
    UsableItem.hardware.writeToDevice .twi_write_page(UsableItemClass::ITEM_INFORMATION_DATA_PAGE+3, (uint8_t*)tmp);
    sprintf(tmp, "12345678");//последняя отбросится
    UsableItem.twi_write_page(UsableItemClass::ITEM_INFORMATION_DATA_PAGE+4, (uint8_t*)tmp);
    sprintf(tmp, "90abcdef");
    UsableItem.twi_write_page(UsableItemClass::ITEM_INFORMATION_DATA_PAGE+5, (uint8_t*)tmp);
    sprintf(tmp, "qwertyui");//последняя отбросится
    UsableItem.twi_write_page(UsableItemClass::ITEM_INFORMATION_DATA_PAGE+6, (uint8_t*)tmp);
    sprintf(tmp, "asdfghjk");
    UsableItem.twi_write_page(UsableItemClass::ITEM_INFORMATION_DATA_PAGE+7, (uint8_t*)tmp);
    */
  #endif
  #ifdef DEBUG_BUILD
    LcdStringUpdate(1,LCD_LINE_2, (char*)"Completed     ");
  #endif
  }
void RuntimeClass::Level5(void)
  {
  SetLevel(RUNLEVEL_5);
  #ifdef DEBUG_BUILD
    LcdString(1,LCD_LINE_1, (char*)"runlevel 5");
    LcdEmptyString(LCD_LINE_2);
    n3310LcdClass::RequestUpdate();
  #endif

  #ifdef DEBUG_BUILD
    LcdStringUpdate(1,LCD_LINE_2, (char*)"PlayerLoad    ");
  #endif
  Player.Load();
  //while(1);
  #ifdef DEBUG_BUILD
    LcdStringUpdate(1,LCD_LINE_2, (char*)"Btn Wait      ");
  #endif
  
  //if (HAL.IO.IsPinLow(ButtonsClass::PIN_MENU_HAL))
  if (Buttons.isButtonDown(ButtonsClass::BUTTON_CENTER_MENU))
    {
    while(1)
      {
      if (StalkerLayer2->L1.L0.isNewEnvPacketReceived())
        {
        StalkerLayer2->L1.L0.getEnvPacketAndRSSI();
        STRClass Str;
        Str.SetPos(STRPOS_STR_FORMAT_4x_03D);
        Str.WriteFormat(Lcd.lcd_buf, StalkerLayer2->L1.L0.SignalPower, StalkerLayer2->L1.L0.RSSI, StalkerLayer2->L1.L0.RSSIRaw, 0);
        StalkerUI.DisplayString(Str, StalkerUI_Class::UI_LCD_LINE_0);

        Str.SetPos(STRPOS_STR_FORMAT_4x_03D);
        Str.WriteFormat(Lcd.lcd_buf, StalkerLayer2->L1.L0.packetContainerRX[0], StalkerLayer2->L1.L0.packetContainerRX[1], StalkerLayer2->L1.L0.packetContainerRX[2], StalkerLayer2->L1.L0.packetContainerRX[3]);
        StalkerUI.DisplayString(Str, StalkerUI_Class::UI_LCD_LINE_1);

        #ifndef RFM69_HW_CRC
          Str.SetPos(STRPOS_STR_FORMAT_4x_03D);
          Str.WriteFormat(Lcd.lcd_buf, StalkerLayer2->L1.L0.checkReceivedPacketCRC());
          StalkerUI.DisplayBottom(Str);
          
        #endif // RFM69_HW_CRC

        Str.SetPos(STRPOS_STR_FORMAT_01U);
        Str.WriteFormat(Lcd.lcd_buf, StalkerLayer2->L1.L0.packetContainerRX[0], StalkerLayer2->L1.L0.packetContainerRX[1], StalkerLayer2->L1.L0.packetContainerRX[2], StalkerLayer2->L1.L0.packetContainerRX[3]);
        StalkerUI.DisplayString(Str, StalkerUI_Class::UI_LCD_LINE_1);
/*
        sprintf (Lcd.lcd_buf,"%03d%03d %03d", StalkerLayer2->L1.L0.SignalPower, StalkerLayer2->L1.L0.RSSI, StalkerLayer2->L1.L0.RSSIRaw);
        //        StalkerLayer0.i=3;
        LcdString(1,LCD_LINE_1);
        sprintf (Lcd.lcd_buf,"%03d%03d %03d%03d", StalkerLayer2->L1.L0.packetContainerRX[0], StalkerLayer2->L1.L0.packetContainerRX[1], StalkerLayer2->L1.L0.packetContainerRX[2], StalkerLayer2->L1.L0.packetContainerRX[3]);
        LcdString(1,LCD_LINE_2);
#ifndef RFM69_HW_CRC
        sprintf (Lcd.lcd_buf,"%03d%03d", StalkerLayer2->L1.L0.packetContainerRX[4], StalkerLayer2->L1.L0.packetContainerRX[5]);
        LcdString(1,LCD_LINE_3);
#endif // RFM69_HW_CRC
        //        sprintf (lcd_buf,"%03d%03d %03d%03d", StalkerLayer0.packetContainer[4], StalkerLayer0.packetContainer[5], StalkerLayer0.packetContainer[6], StalkerLayer0.packetContainer[7]);
        //        LcdString(1,LCD_LINE_3);
        //        sprintf (lcd_buf,"%03d%03d %03d%03d", StalkerLayer0.packetContainer[8], StalkerLayer0.packetContainer[9], StalkerLayer0.packetContainer[10], StalkerLayer0.packetContainer[11]);
        //        LcdString(1,LCD_LINE_4);
        //        sprintf (lcd_buf,"%33d%03d %03d%03d", radio._RXBuffer[12], radio._RXBuffer[13], radio._RXBuffer[14], radio._RXBuffer[15]);
        //        LcdString(1,LCD_LINE_5);
        sprintf (Lcd.lcd_buf,"%01d", StalkerLayer2->L1.L0.checkReceivedPacketCRC());
        LcdString(1,LCD_LINE_6);
*/
        n3310LcdClass::RequestUpdate();
        //radio.receiveBegin();
        StalkerLayer2->L1.L0.receiveBegin();
        //_delay_ms(40);
        }
      else
        {
        //LcdClearUpdate();
        }
      }
    }
//  Quest.giveQuest(TemporaryClass::QID_FIND_BAR);
//  Quest.giveQuest(TemporaryClass::QID_FIND_BARMAN);
  
//  Quest.

  //Quest.completeQuest(QuestClass::QID_FIND_BAR);
  //Quest.completeQuest(QuestClass::QID_FIND_BARMAN);
//  #ifdef DEBUG_BUILD
//    LcdStringUpdate(1,LCD_LINE_2, (char*)"Completed     ");
//  #endif
//  while (1);// {StatusLedPin::SetOutToggle(); _delay_ms(1000);}
//  Ar1010.setFrequency(877);//106.4
//  Ar1010.setFrequency(1064);//106.4
  Ar1010.setFrequency(1071);
  

//  #ifdef DEBUG_BUILD
//    #include "src/debugInMain.h"
//  #endif

  set_sleep_mode(SLEEP_MODE_IDLE);
  //  set_sleep_mode(SLEEP_MODE_EXT_STANDBY);
  

  
  
  
//  Player.Revive();
//  Player.SetHealth(50);
//  Quest.giveQuest(TemporaryClass::QID_FIND_KEY);
//  Quest.giveQuest(TemporaryClass::QID_FIND_KEY);
//  PlayerEffectsNG.apply(PlayerEffectInstanceClass::EFFECTID_INCREASE_HEALTH_1, PlayerEffectInstanceClass::EFFECT_TIMINGS_UNTILL_DIE, 2,0);

//  PlayerSkills.setSkillKnown(PlayerSkillsClass::SKILL_COMPUTER);
//  PlayerSkills.setValue(PlayerSkillsClass::SKILL_COMPUTER, 50);
  //char* memTest  = (char*)MemoryManager.allocate(10);
  //*memTest  = "aasd";
  //sprintf (memTest,"abc");
  //RFM69* zz  = new RFM69[5];
  
  
  
  /*
  uint8_t sleepTime=5;
  while(1)
    {
    LcdString(1,LCD_LINE_1);
    sprintf (lcd_buf,"%05u", rand());
    LcdUpdate();
    if (--sleepTime == 0)
      {
      break;
      }
    sleep_enable();
    sleep_cpu();
    sleep_disable();
    }*/
  
  //set_sleep_mode(SLEEP_MODE_IDLE);
  //Ar1010.deviceEnable();
  //HAL.EnvironmentRarioModule.deviceEnable();
  //LcdClearUpdate();
  //runlevel_5();
  //_delay_ms(1000);
  PowerManager.EnterNormalMode();
  #warning "[T] remove this revive"
  Player.Revive();
  #ifndef FAKE_ADC_POWER
    //PowerManager.EnterSleepMode(PowerManagerClass::SLEEP_EVENT_DEVICE_START);
  #endif
  
//  #ifdef DEBUG_BUID
//    PDAMenu.selectMenuID(PDAMenu_MainInterface::MENUID_QUESTS);
//  #endif // DEBUG_BUID
//PDAMenu.selectMenuID(250);

  USARTF0.BAUDCTRLB = 0; //Just to be sure that BSCALE is 0
  USARTF0.BAUDCTRLA = 0;//0xCF; // 207
  //unsigned char ucBaudCtrl;
  //uint8_t ucBaudCtrl = ( F_CPU / ( 2 * 460800UL ) ) - 1;
  //USARTF0_BAUDCTRLA = (32000000UL / (2^0 * 16*9600UL) -1 );
  // Baud rate selection
  // BSEL = (32000000 / (2^0 * 16*9600) -1 = 207.333 -> BSCALE = 0
  // FBAUD = ( (32000000)/(2^0*16(207+1)) = 9615.384 -> it's alright
  //Disable interrupts, just for safety
  USARTF0.CTRLA = 0;
  //8 data bits, no parity and 1 stop bit
  USARTF0.CTRLC = USART_CHSIZE_8BIT_gc;
   
  //Enable receive and transmit
  //USARTF0.CTRLB = USART_TXEN_bm;// | USART_RXEN_bm; // And enable high speed mode
  USARTF0.CTRLB = USART_TXEN_bm | USART_CLK2X_bm;
  
  PORTF.OUTSET = PIN3_bm; //Let's make PC7 as TX
  PORTF.DIRSET = PIN3_bm; //TX pin as output
  
  //PORTF_OUTCLR = PIN2_bm;
  //PORTF_DIRCLR = PIN2_bm; //PC6 as RX
  /*uint8_t usarti=0;
  while (1)
    {
    sendChar(usarti++);
    }*/
  /*while(1)
    {
    sprintf (lcd_buf, "%03u",echo_char);
    LcdString(10,LCD_LINE_1);
    //      LcdUpdate();  
    }*/
  #ifdef DEBUG_USART
    sprintf (USARTBuffer,"Start %03u:%03u:%03u %01u\r\n", TimeRTC.hour, TimeRTC.minute, TimeRTC.second, BackLight.isBacklightONInverted);
    sendString(USARTBuffer);
  #endif
  StalkerUI.ClearDisplay();
  StalkerUI.DisplayString(STRPOS_STR_TIME_SYNC_AWAITING, StalkerUI_Class::UI_LCD_LINE_0);
  
  StalkerUI.RequestUpdate();
  while(TimeUpdate.IsTimeSyncReceivedAtLastOnce() == false)
    {
    StalkerLayer2->L1.isEnvironmentActive();//wait for time sync
    StalkerLayer2->L1.L0.packetProcessed();
    if (PowerManager.isBatteryDischarged())
      {
      PowerManager.EnterSleepMode(PowerManagerClass::SLEEP_EVENT_BATT);
      break;
      }
    sleep_enable();
    sleep_cpu();
    sleep_disable();
    }
  }
void RuntimeClass::Level6(void)
  {
  SetLevel(RUNLEVEL_6);
  //PlayerEffects.ApplyEffectInstance(TemporaryClass::PLAYEREFFECT_SAFE_SHELTER);
  //PlayerEffects.RenewEffectInstance(EffectSafeShelterHack);
  //#warning "wear suit! Remove it!"
  //Player.GetSuit()->Wear(TemporaryClass::SUIT_ID_SEVA, 99);
  //Player.DealDamage({10});
  #ifdef DEBUG_BUILD
    //Player.SetRadDose(20);
    //EEPROM_Data.load();
    //USABLE_ITEM_ITEM_CONNECTED_PORT.PIN6CTRL  = PORT_OPC_PULLUP_gc;
    //USABLE_ITEM_ITEM_CONNECTED_PORT.OUTSET    = 1<<6;
    LcdStringUpdate(1,LCD_LINE_1, (char*)"starting...");

    //LcdString(1,LCD_LINE_2, Anomaly.getAnomalyName(1));
    //LcdString(1,LCD_LINE_3, Anomaly.getAnomalyName(2));
    //LcdUpdate();
    //delay_ms(5000);
    
    
    //delay_ms(500);
    //    while(1);
    
    
    Player.GetSuit()->Wear(TemporaryClass::SUIT_ID_SEVA, PlayerSuitClass::DURABILITY_FULL);
    
//    PDAMenu.selectMenu(PDAMenuClass::MENUID_EFFECTS);
    //PDAMenu.selectMenu(PDAMenuClass::MENUID_QUESTS);
    //PDAMenu.selectMenu(PDAMenuClass::MENUID_ARTEFACTS_CONNECTED);
    //PDAMenu.selectMenu(PDAMenuClass::MENUID_CONNECTED_ITEM);
    //PDAMenu.selectMenu(PDAMenuClass::MENUID_SUIT);
    //PDAMenu.selectMenu(PDAMenuClass::MENUID_SPECS);
    //PDAMenu.selectMenu(PDAMenuClass::MENUID_ACTIONS);
    //Player.SetHealth(80);


    //    PORTK.DIRCLR  = 1<<5;
    //    PORTK.PIN6CTRL  = PORT_OPC_PULLUP_gc;
    PDAMenu.SelectDefaultMenu();
  #else
    //Player.SetHealth(90);
    PDAMenu.SelectDefaultMenu();
    //PDAMenu.selectMenu(PDAMenuClass::MENUID_MAIN);
    //Quest.GiveQuest(1);
    //Quest.GiveQuest(2);
    //Quest.GiveQuest(3);
    //Quest.GiveQuest(4);
    //Quest.GiveQuest(5);
    /*
    PlayerSuitClass* PlayerSuit  = Player.GetSuit();
    //PlayerSuit->Wear(TemporaryClass::SUIT_ID_ZARYA, 99);
      PlayerSuit->Wear(TemporaryClass::SUIT_ID_ZARYA, 99);

      sprintf (Lcd.lcd_buf,"%03d%03d %03u%03u", PlayerSuit->GetCurrentSuit()->GetCharacteristics()->Get(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS),PlayerSuit->getDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_GENERIC),PlayerSuit->getDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_EXTERNAL),PlayerSuit->getDefenceFrom(TemporaryClass::DamageSource::DAMAGE_SOURCE_RADIATION_DOSE_INTERNAL));
      LcdString(1,LCD_LINE_1);
      sprintf (Lcd.lcd_buf,"%03d", GameCFG.SuitsContainer.getSuiteInstance(1)->GetCharacteristics()->Get(GameCharacteristicsClass::CHARACTERISTIC_CONTAINERS));
      LcdString(1,LCD_LINE_2);
      sprintf (Lcd.lcd_buf,"%03d   ", PlayerSuit->GetCurrentSuit()->GetID());
      LcdString(1,LCD_LINE_3);
      sprintf (Lcd.lcd_buf,"%03d   ", GameCFG.GetDamageSourceNum());
      LcdString(1,LCD_LINE_6);
      
      n3310LcdClass::RequestUpdate();
      
      while(1);
      */
      #warning "[T] suit incomplete!"

  #endif
  Vibro.activate(10);
  }
void RuntimeClass::Level7(void)
  {

  SetLevel(RUNLEVEL_PROGRAM_STARTED);

  }
#endif //LOAD_SOUNDS

void RuntimeClass::SetLevel(RUNLEVELS lvl)
  {
  CurrentLevel  = lvl;
  }
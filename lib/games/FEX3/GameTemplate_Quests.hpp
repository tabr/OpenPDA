#ifndef GAMETEMPLATE_QUESTS_H_
#define GAMETEMPLATE_QUESTS_H_
  #ifdef DEBUG_BUILD
    LcdStringUpdate(1,LCD_LINE_2, (char*)"Quests        ");
  #endif
//  Quest.setQuestsNum(TemporaryClass::QUESTS_NUM - 1);
  Quest.RegisterNew(TemporaryClass::QID_FIND_BAR,        (char*)"дойти до бара");
  //  Quest.registerNew(TemporaryClass::QID_FIND_BAR,        tmp);
    //while(1);
  Quest.RegisterNew(TemporaryClass::QID_FIND_KEY,        (char*)"найти ключ от лабы");
  //  Quest.registerNew(TemporaryClass::QID_FIND_BARMAN,      (char*)"найти пропавшего бармена");
  //  sprintf(tmp,"найти пропавшего бармена");
  //  Quest.registerNew(TemporaryClass::QID_FIND_BAR,        tmp);
#endif //GAMETEMPLATE_QUESTS_H_
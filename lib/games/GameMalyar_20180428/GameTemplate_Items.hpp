#ifndef GAMETEMPLATE_ITEMS_H_
#define GAMETEMPLATE_ITEMS_H_

  #ifdef DEBUG_BUILD
    LcdStringUpdate(1,LCD_LINE_2, (char*)"Items         ");
  #endif

//WEB generated
GameCFG.ItemTemplate.RegisterNew(1,    (char*)"��� �������",           Item_PsyBlok);
GameCFG.ItemTemplate.RegisterNew(2,    (char*)"�������",               Item_Antiradin);
GameCFG.ItemTemplate.RegisterNew(3,    (char*)"��������������",        Item_Radioprotector);
GameCFG.ItemTemplate.RegisterNew(4,    (char*)"�������",               Item_FirstAidKit);
GameCFG.ItemTemplate.RegisterNew(5,    (char*)"����",                  Item_Bandage);



#endif //GAMETEMPLATE_ITEMS_H_
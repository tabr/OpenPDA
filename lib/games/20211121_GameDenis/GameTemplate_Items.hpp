#ifndef GAMETEMPLATE_ITEMS_H_
#define GAMETEMPLATE_ITEMS_H_

  #ifdef DEBUG_BUILD
    LcdStringUpdate(1,LCD_LINE_2, (char*)"Items         ");
  #endif

//WEB generated
//GameCFG.ItemTemplate.RegisterNew((ItemID_t)1,    (ItemName_t)"��� �������",           (PlayerEffectGUID_t)TemporaryClass::PLAYEREFFECT_ITEM_PLYSBLOCK);
//GameCFG.ItemTemplate.RegisterNew(2,    (char*)"�������",               TemporaryClass::PLAYEREFFECT_ITEM_ANTIRADIN);
//GameCFG.ItemTemplate.RegisterNew(3,    (char*)"��������������",        TemporaryClass::PLAYEREFFECT_ITEM_RADIOPROTECTOR);
//GameCFG.ItemTemplate.RegisterNew(4,    (char*)"�������",               TemporaryClass::PLAYEREFFECT_ITEM_FIRSTAIDKIT);
//GameCFG.ItemTemplate.RegisterNew(5,    (char*)"����",                  TemporaryClass::PLAYEREFFECT_ITEM_BANDAGE);

#warning "[T] doesnt work upper code!"

GameCFG.ItemTemplate.RegisterNew(new ItemTemplateInstance ((ItemID_t)1,    (ItemName_t)"��� �������",     Item_PsyBlok));
GameCFG.ItemTemplate.RegisterNew(new ItemTemplateInstance ((ItemID_t)2,    (ItemName_t)"�������",         Item_Antiradin));
GameCFG.ItemTemplate.RegisterNew(new ItemTemplateInstance ((ItemID_t)3,    (ItemName_t)"��������������",  Item_Radioprotector));
GameCFG.ItemTemplate.RegisterNew(new ItemTemplateInstance ((ItemID_t)4,    (ItemName_t)"�������",         Item_FirstAidKit));
GameCFG.ItemTemplate.RegisterNew(new ItemTemplateInstance ((ItemID_t)5,    (ItemName_t)"����",            Item_Bandage));




#endif //GAMETEMPLATE_ITEMS_H_
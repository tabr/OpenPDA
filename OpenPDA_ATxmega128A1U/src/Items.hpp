#ifndef ITEMS_CLASS_H
#define ITEMS_CLASS_H

#include <string.h>
#include <stdio.h>
//#include "PlayerEffectsOld.hpp"
#include "MemoryManager.hpp"
#include "typedefs.h"
#include "PlayerEffectsInterface.hpp"
#include "Node.hpp"


class ItemTemplateInstance : public NodeExtended
  {
  public:
    PlayerEffects_Interface* GetItemEffect(void);
    ItemName_t GetName(void);
    ItemID_t GetID(void);
    void SetPropertiesNoClone(ItemTemplateInstance src);
    ItemTemplateInstance* GetNextNode(void);
    ItemTemplateInstance(ItemID_t tmpIID, ItemName_t tmpName, PlayerEffects_Interface* PlayerEffect);
    ItemTemplateInstance(void);
  protected:
  private:
    PlayerEffects_Interface* m_PlayerEffect;
    ItemName_t Name;
    ItemID_t m_IID;
  };

class ItemTemplateClass : public NodeProcessorT<ItemTemplateInstance>
  {
  public:
    const static ItemID_t ITEMID_NOITEM      = 0;

    ItemTemplateInstance *GetItem(ItemID_t IID);
    bool IsValidItemId(ItemID_t IID);
    ItemName_t GetItemName(ItemID_t IID);
    PlayerEffects_Interface* GetItemEffect(ItemID_t IID);
    bool RegisterNewItem(ItemID_t IID, ItemName_t tmpName, PlayerEffects_Interface* PlayerEffect);
//    bool RegisterNewItem(ItemID_t IID, ItemName_t tmpName, PlayerEffectGUID_t EGUID);
    bool RegisterNewItem(ItemTemplateInstance* NewItem);
    ItemsNum_t GetItemsNum(void);
    ItemTemplateClass(void);
  protected:
  private:
  };


#endif
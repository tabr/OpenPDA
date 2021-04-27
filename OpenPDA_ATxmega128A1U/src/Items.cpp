// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
ItemTemplateInstance::ItemTemplateInstance(void)
  {
  //this->ApplyEffect  =  PlayerEffectsOldClass::EFFECTID_NONE;
  this->m_PlayerEffect  =  &PlayerEffects.PlayerEffect_NullEffect;
  this->m_IID           =  0;
  this->Name            =  RAM_STR_UNDEFINED;
  }

ItemTemplateInstance::ItemTemplateInstance(ItemID_t tmpIID, ItemName_t tmpName, PlayerEffects_Interface* PlayerEffect)
  {
  //      this->ApplyEffect  =  EID;
  this->m_PlayerEffect  =  PlayerEffect;
  //this->Name           =  (char*)MemoryManager.allocate((1  +  strlen(tmpName))  *  sizeof(char));
  //sprintf(this->Name,  tmpName);
  this->m_IID           =  tmpIID;
  this->Name            =  LcdStringCopy.CopyFrom(tmpName);
  }
PlayerEffects_Interface* ItemTemplateInstance::GetItemEffect(void)
  {
  return this->m_PlayerEffect;
  }
ItemName_t ItemTemplateInstance::GetName(void)
  {
  return this->Name;
  }
ItemID_t ItemTemplateInstance::GetID(void)
  {
  return this->m_IID;
  }
void ItemTemplateInstance::SetPropertiesNoClone(ItemTemplateInstance  src)
  {
  //      this->ApplyEffect  =  src.ApplyEffect;
  this->m_PlayerEffect  =  src.m_PlayerEffect;
  this->Name            =  src.Name;
  this->m_IID           =  src.m_IID;
  }

ItemTemplateInstance* ItemTemplateInstance::GetNextNode(void)
  {
  return static_cast<ItemTemplateInstance*>(Node::GetNextNode());//call parent "GetNextNode"
  }




ItemTemplateClass::ItemTemplateClass(void)
  {
  //this->Num  =  0;
  //      this->ItemNone.setProperties((char*)"-",      PlayerEffectsOldClass::EFFECTID_NONE);
  //this->ItemNone.setProperties(0,(char*)"-",      &PlayerEffects.PlayerEffect_NullEffect);
  }
PlayerEffects_Interface* ItemTemplateClass::GetItemEffect(ItemID_t IID)
  {
  if (this->IsValidItemId(IID))
    {
    return this->GetItem(IID)->GetItemEffect();
    }
  return &PlayerEffects.PlayerEffect_NullEffect;
  }
ItemTemplateInstance* ItemTemplateClass::GetItem(ItemID_t IID)
  {
  return this->GetNode(IID);
  /*
  ItemTemplateInstance*  I  =  &this->container;
  for  (uint8_t  i=0;i<Node::MAX_NODES;i++)
    {
    if  (I->GetID()  ==  IID)
      {
      return  I;
      }
    I  =  I->GetNextNode();
    if  (I  ==  NULL)
      {
      break;
      }
    }
  return  &this->container;
  */
  }
bool ItemTemplateClass::RegisterNewItem(ItemTemplateInstance* NewItem)
  {
  return this->RegisterNew(NewItem);
  }
/*
bool ItemTemplateClass::RegisterNewItem(ItemID_t IID, ItemName_t tmpName, PlayerEffectGUID_t EGUID)
  {
  return this->RegisterNew(new ItemTemplateInstance (IID, tmpName, GameCFG.GetPlayerEffect(EGUID)));
  }
*/
bool ItemTemplateClass::RegisterNewItem(ItemID_t IID, ItemName_t tmpName, PlayerEffects_Interface* PlayerEffect)
  {
  return this->RegisterNew(new ItemTemplateInstance (IID, tmpName, PlayerEffect));
  }
ItemsNum_t ItemTemplateClass::GetItemsNum(void)
  {
  return this->GetRegisteredNodeNum();
  }
ItemName_t ItemTemplateClass::GetItemName(ItemID_t IID)
  {
  return this->GetItem(IID)->GetName();
  }
bool ItemTemplateClass::IsValidItemId(ItemID_t IID)
  {
  return  this->GetItem(IID) != (this->GetContainer());
  }

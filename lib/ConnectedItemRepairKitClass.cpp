// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
RepairKitPCS_t  ConnectedItemRepairKitClass::GetPCS(void)
  {
  //return  (RepairKitPCS)(*(this->GetConnectedItemArrayAddr()  +  UsableItemClass::FLASHDATA_ITEM_EX0));
  //return  (*((RepairKitPCS_t*)(this->GetConnectedItemArrayAddr()  +  EepromItemClass::EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_EX0)));
  return  this->GetItem()->GetEx0();
  }

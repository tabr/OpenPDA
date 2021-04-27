// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
ResourcePCS_t ConnectedItemResourceClass::GetPCS(void)
	{
	//return (*((ResourcePCS_t*)(this->GetConnectedItemArrayAddr() + EepromItemClass::EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_EX0)));
	return (ResourcePCS_t)this->GetItem()->GetEx0();
	}
void ConnectedItemResourceClass::SetPCS(ResourcePCS_t value)
  {
  this->GetItem()->SetEx0(value);
  }
void ConnectedItemResourceClass::SetID(ResourceID_t value)
  {
  this->GetItem()->SetID(value);
  }
/*
void ConnectedItemResourceClass::SetType(ResourcePCS_t value)
  {
  this->GetItem()->SetType(value);
  }
*/
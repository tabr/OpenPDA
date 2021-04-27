#pragma once
class EepromItemClass
  {
  public:
		enum EEPROM_ITEM_STRUCT
			{
			EEPROM_ITEM_STRUCT_TYPE,
			EEPROM_ITEM_STRUCT_SUBTYPE,
			EEPROM_ITEM_STRUCT_ID,
			EEPROM_ITEM_STRUCT_STATUS,
			EEPROM_ITEM_STRUCT_EX0,
			EEPROM_ITEM_STRUCT_EX1,
			EEPROM_ITEM_STRUCT_EX2,
			EEPROM_ITEM_STRUCT_EX3,
			EEPROM_ITEM_STRUCT_SIZE,
			};
    EepromDataSize_t GetType(void)
      {
      return this->Item[EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_TYPE];
      }
    EepromDataSize_t GetSubtype(void)
      {
      return this->Item[EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_SUBTYPE];
      }
    EepromDataSize_t GetID(void)
      {
      return this->Item[EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_ID];
      }
    EepromDataSize_t GetStatus(void)
      {
      return this->Item[EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_STATUS];
      }
    EepromDataSize_t GetEx0(void)
      {
      return this->Item[EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_EX0];
      }
    EepromDataSize_t GetEx1(void)
      {
      return this->Item[EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_EX1];
      }
    EepromDataSize_t GetEx2(void)
      {
      return this->Item[EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_EX2];
      }
    EepromDataSize_t GetEx3(void)
      {
      return this->Item[EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_EX3];
      }

    void SetType(EepromDataSize_t value)
      {
      this->Item[EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_TYPE]         = value;
      }
    void SetSubtype(EepromDataSize_t value)
      {
      this->Item[EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_SUBTYPE]      = value;
      }
    void SetID(EepromDataSize_t value)
      {
      this->Item[EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_ID]           = value;
      }
    void SetStatus(EepromDataSize_t value)
      {
      this->Item[EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_STATUS]       = value;
      }
    void SetEx0(EepromDataSize_t value)
      {
      this->Item[EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_EX0]          = value;
      }
    void SetEx1(EepromDataSize_t value)
      {
      this->Item[EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_EX1]          = value;
      }
    void SetEx2(EepromDataSize_t value)
      {
      this->Item[EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_EX2]          = value;
      }
    void SetEx3(EepromDataSize_t value)
      {
      this->Item[EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_EX3]          = value;
      }

    
    EepromItemArray_t* GetArray(void)
      {
      return this->Item;
      }
    void FromArray(EepromDataSize_t* array_ptr)
      {
      memcpy(this->Item, array_ptr, EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_SIZE*sizeof(EepromDataSize_t));
      }
    void Clean(void)
      {
      memset(this->Item, 0, sizeof(this->Item));
      }
    EepromItemClass(void)
      {
      this->Clean();
      }
  private:
    EepromItemArray_t Item[EEPROM_ITEM_STRUCT::EEPROM_ITEM_STRUCT_SIZE];
  
  };
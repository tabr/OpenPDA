// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * Strings.cpp
 *
 * Created: 13.05.2018 18:08:39
 *  Author: tabr
 */ 
 
void STRClass::WriteTo(char* buffer)
  {
  if (this->str_loc == STR_LOCATION_INSIDE_BUFFER)
    {
    return;
    }
  this->SetExternalBuffer(buffer);

  TFSFileClass File;
  File.SeekByPosition(24);
  File.SetInternalPointer(this->current_pos * STORAGE_DATA_WIDTH);
  File.ReadData((uint8_t*)buffer, STORAGE_DATA_WIDTH);
  this->str_loc     = STR_LOCATION_INSIDE_BUFFER;
  }
void STRClass::Clean(void)
  {
  this->current_pos=STR_POS::STRPOS_STR_None;
  this->external_buffer=NULL;
  this->str_loc=STR_LOCATION_OUTSIDE_BUFFER;
  }
#ifdef LOAD_SOUNDS
void STRClass::WritePgmTo(char* buffer)
  {
  if (this->str_loc == STR_LOCATION_INSIDE_BUFFER)
    {
    return;
    }
  this->SetExternalBuffer(buffer);
  this->str_loc     = STR_LOCATION_INSIDE_BUFFER;

  for (uint8_t i=0;i<MAX_STR_LENGTH;i++)
    {
    uint8_t byte  = pgm_read_byte(pos_array[this->current_pos] + i);
    buffer[i]     = byte;
    if (byte == 0)//mean end of string
      {
      return;
      }
    }
  }
#endif //LOAD_SOUNDS
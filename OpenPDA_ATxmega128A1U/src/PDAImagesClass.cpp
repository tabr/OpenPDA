// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * PDAImagesClass.cpp
 *
 * Created: 09.10.2017 2:26:36
 *  Author: tabr
 */ 
PDAImagesClass::PDAImagesClass(void)
  {
  //none
  }
uint32_t PDAImagesClass::GetImageAddress(IMAGES img)
  {
  if (this->images[0] == 0)
    {
    this->LoadImageAddressesFromMediaFlash();
    }
  return this->images[img];
  }
void PDAImagesClass::DrawImg(IMAGES img)
  {
  //UNION_UINT32_LITTLE_ENDIAN z;
  //z.value_int = this->GetImageAddress(img);
  //MediaMemory.ReadData(z.byte_field.mh, z.byte_field.ml, z.byte_field.l, (uint8_t*)LcdCache, (uint16_t)LCD_CACHE_SIZE);
  TFSFileClass file;
  //TFS_FAT_FilePos_t pos = TFS.GetFilePosition("img_4cols.hex");
  file.SeekByPosition(this->img_pos[img]);
  file.ReadData(LcdCache, LCD_CACHE_SIZE);

  }


void PDAImagesClass::LoadImageAddressesFromMediaFlash(void)
  {
  UNION_UINT32 z;
  for (uint8_t i=0;i<IMAGES::IMAGES_NUM;i++)
    {
    z.value_int = MediaFlashClass::MEDIAFLASH_ADDRESS::MEDIAFLASH_ADDRESS_IMAGE_POINTERS+(4*i);//address
    uint32_t addressValue = 0;
    MediaMemory.ReadData(z.byte_field.mh, z.byte_field.ml, z.byte_field.l, (uint8_t*)&addressValue, (uint16_t)4);
    this->images[i]  = addressValue;
    //StatusLedPin::SetOutHigh();
    }
  }

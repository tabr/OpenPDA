/*
 * MediaFlashClass.h
 *
 * Created: 09.10.2017 2:48:48
 *  Author: tabr
 */ 


#ifndef MEDIAFLASHCLASS_H_
#define MEDIAFLASHCLASS_H_

class MediaFlashClass
  {
  public:
    enum MEDIAFLASH_ADDRESS
      {
      MEDIAFLASH_ADDRESS_NUM_OF_SOUNDS  = 0,
      MEDIAFLASH_ADDRESS_NUM_OF_IMAGES  = 1,
      MEDIAFLASH_ADDRESS_SOUNDS_STARTS  = 8,          //4byte
      MEDIAFLASH_ADDRESS_IMAGES_STARTS  = 12,         //4byte
      MEDIAFLASH_ADDRESS_SOUND_POINTERS = 1024 + 0,   //32 4byte addressed
      MEDIAFLASH_ADDRESS_IMAGE_POINTERS = 1024 + 128, //32 4byte addressed
      MEDIAFLASH_ADDRESS_DATA_START     = 4096,
      };
  protected:
  private:
  };



#endif /* MEDIAFLASHCLASS_H_ */
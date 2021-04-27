/*
 * PDAImagesClass.h
 *
 * Created: 09.10.2017 2:25:22
 *  Author: tabr
 */ 


#ifndef PDAIMAGESCLASS_H_
#define PDAIMAGESCLASS_H_
#include "images.h"




class PDAImagesClass
  {
  public:
    enum IMAGES
      {
      IMG_PBOY,
      IMG_4_COLS,
      IMG_SKULL,
      IMG_ZOMBIE,
      IMG_LOW_BAT,
      IMG_RADIO_WAVES_3,
      IMG_RADIO_WAVES_2,
      IMG_RADIO_WAVES_1,
      IMG_RADIO_WAVES_0,
      IMAGES_NUM
      };
    PDAImagesClass(void);
    void DrawImg(IMAGES img);
    void HardwareInitialization(void);
    void LoadImageAddressesFromMediaFlash(void);
    uint32_t GetImageAddress(IMAGES img);
  protected:
  private:
    uint32_t images[IMAGES::IMAGES_NUM]={0};

    const static uint8_t img_pos[];//={1,2,3,4,5};
  };
#warning "[T] IMG hack!"
const TFS_FAT_FilePos_t PDAImagesClass::img_pos[]={14, 12, 15, 16, 13, 25, 26, 27, 28};

#endif /* PDAIMAGESCLASS_H_ */
#ifndef SOUNDS_H
#define SOUNDS_H
//Структура WAV файла:
//https://audiocoding.ru/article/2008/05/22/wav-file-structure.html
#include <stdint.h>
#include <stddef.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

//SOFTWARE MIX: result = A+B - (AB/256)
//#include "ring_buffer.h"
#include "Mcucpp/atomic.h"
#include "Mcucpp/ring_buffer.h"

#include "boards/pcb_1.h"
#include "stalker/SoundList.h"
#include "typedefs.h"
#include "TFSClass.hpp"
#include "stalker/TimerClass.hpp"

//using Mcucpp::Containers;1
/*
PAGE SIZE 256bytes
SPIFS
[0-8191]FileList:
[0-1]   PageAddr[2]
[2-5]   FileSizeInBytes[3]
[6-7]   RESERVED
[8-15]  FileName
DATA:
[8192++](32th page)


MediaFlash structure:
[0]       num of sounds
[1]       num of images
[2]       reserved
[3]       reserved
[4]       reserved
[5]       reserved
[6]       reserved
[7]       reserved
[8-11]    sounds start address
[12-15]   images start address
[16-19]   reserved
[20-23]   reserved
[24-27]   reserved
[28-31]   reserved
[32-35]   reserved
[36-39]   reserved
[40-127]  reserved
[1024+]   128-byte sections starts (4 byte pointers to data)
[1024]    sounds [1024+(i*4)]: [1024+(0*4)], [1024+(1*4)], ..
[1152]    images
[4096+]   data starts
*/
Mcucpp::Containers::RingBufferPO2<SOUND_BUFFER_SIZE, uint8_t> SoundBuffer;
class Sound : public ITimerListener
  {
  public:
    enum SIDS
      {
      SID_NONE,
      SID_RADIOATION,
      SID_RADIOATION4,
      SID_PDA_NEWS,
      SID_ANOMALY_BEEP,
      SID_HIT_1,
      SID_HIT_2,
      SID_HIT_3,
      SID_HIT_4,
      SID_HIT_5,
      SID_BLOWOUT_HIT_2,
      SID_PIK,
      SIDS_NUM
      };
    const static uint8_t QUEUE_SIZE      = 8;
    const static uint8_t WAV_HEAD_DIFF    = 44;
    
    void TimerUpdateEvent (uint8_t msPassed);
    bool IsPsyActive(void);
    bool IsHiFiActive(void);
    void IOInit(void);
    void CleanQueue(void);
    void HardwareInitialization(void);
    void MuteOn(void);
    void MuteOff(void);
    void ISR_PsyVerctor(void);
    void ISR_DeathSound(void);
    void PlaylistAdd(SIDS SID);      //добавить в очередь - "проиграть" звук
    void PlayNext(void);            //вызывается извне для прорабортки очереди звуков
//    void startSouns(void);
    void startSoundsHiFi(void);          //DAC звуки
    void startSoundsPsy(uint8_t period);          //ногодрыг
    void stopSoundsHiFi(void);
    void stopSoundsPsy(void);
    void stopAllSounds(void);
    playableSample getNextPlayableSample(void);
    volatile void PlaySampleIfNeed(void);    //вызывается из прерывания
    void FillBufer(void);                         //call from main
    
    void LoadSoundAddressesFromMediaFlash(void);
    Sound(void);
    uint16_t* deathSoundPtr  = &deathSound[0];
//      uint32_t MediaFlashSamples[Sound::SIDS::SIDS_NUM]={0};
//#warning "!!!"
//    RingBuffer<16> Buf;
//    Mcucpp::Containers::RingBufferPO2<32, uint8_t> Buf;
  protected:
  private:
    uint8_t queueTop;
    uint8_t queueBottom;
    void DAC_init(void);
    void SetCurrentSound(SIDS snd);

    //bool IsHifiSoundBusy=false;
    TFSFileClass sound_file;
    const static uint8_t snd_pos[];//={1,2,3,4,5};


    
//    uint8_t queue[Sound::QUEUE_SIZE];
    SIDS queue[Sound::QUEUE_SIZE];
  };
const TFS_FAT_FilePos_t Sound::snd_pos[]=
  {
  1,  //SID_NONE,
  2,  //SID_RADIOATION,
  3,  //SID_RADIOATION4,
  4,  //SID_PDA_NEWS,
  5,  //SID_ANOMALY_BEEP,
  6,  //SID_HIT_1,
  7,  //SID_HIT_2,
  8,  //SID_HIT_3,
  9,  //SID_HIT_4,
  10, //SID_HIT_5,
  11, //SID_BLOWOUT_HIT_2,
  29, //SID_PIK,
  };
#endif
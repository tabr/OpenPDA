// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/* 
 * This file is part of the OpenPDA distribution https://github.com/tabr/OpenPDA
 * Copyright (c) 2010-2021 Mateshko Andrei (tabr).
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 2.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
//#define fbyte uint8_t
//https://github.com/aanon4/RFM12B/blob/master/RFM12B.cpp RFM69 COMPATIBLE ???
//https://code.google.com/p/my-ihome/wiki/XMEGA_Programming - crc16 Hardware
//AES: 0,01171875 ms ~ 15us
//https://ru.wikipedia.org/wiki/Serial_Peripheral_Interface - Soft SPI example

//C:\projects\stalker\lib\StandardCplusplus-master - # Standard C++ for Arduino

/************************************************************************/
/*
2) Ќужно придумать, как выбирать нужную половину дл€ поиска. —ама€ перва€ мо€ попытка содержала и ||, и &&, после чего мне повезло заметить, что все это сводитс€ к банальнейшему XOR'у: 
descendingOrder  array[mid] > key  XOR
0  0  0
0  1  1
1  0  1
1  1  0
if ((array[mid] > key) ^ descendingOrder)


*/

//printf("%s%s", item_name[i], "........." + strlen(item_name[i]));

/*
10 (в степени) (db/10)если изменение мощности составило +20 децибел, это значит, что ЂP1 больше P0 на два пор€дкаї или ЂP1 больше P0 в 100 разї;
1 дЅ ? в ?1,26 раза,
3 дЅ ? в ?2 раза,
10 дЅ ? в 10 раз.
ƒалее, раскладыва€ Ђболее сложные значени€ї на Ђсоставныеї, получаем:

6 дЅ = 3 дЅ + 3 дЅ ? в ?2Ј2 = в 4 раза,
9 дЅ = 3 дЅ + 3 дЅ + 3 дЅ ? в ?2Ј2Ј2 = в 8 раз,
12 дЅ = 4 Ј (3 дЅ) ? в ?24 = в 16 раз
*/
/************************************************************************/
/*
HW:
pe2->pe4
*/
/*
static Singleton& instance()
{
  static Singleton s;
  return s;
}
*/
/*
#define LOG_LEVEL_NONE        0
#define LOG_LEVEL_NOTIFY      1
#define LOG_LEVEL_NORMAL      2
#define LOG_LEVEL_DEBUG        3

#define SELECTED_LOG_LEVEL      LOG_LEVEL_NORMAL
*/
//#define LOG(LEVEL, str) (#if(LEVEL <= SELECTED_LOG_LEVEL) #warning str #endif)

//#define SUPRESS_NOTES

/*
#ifdef SUPRESS_NOTES
#  define BUILD_NOTE
#else
#  define BUILD_NOTE DO_PRAGMA(message ("The blahblah hasn't been implemented " \
"yet; use foo to do so."))
#endif
*/

/*
0-NONE
1-NOTIFY
2-NORMAL
3-DEBUG

*/
#warning "[T] LCD DMA IS NOT WORKS"
#warning "[T] Game should contain at last one suit!"
#warning "[T] Add dynamic InGameEvents: make new ONLY if need to call it!"
#warning "[T] sometimes can't detect connected item"
#warning "[T] make blowout death time longer"
#include "src/boards/compiler_defines.h"

//#define LOAD_SOUNDS



#ifndef LOAD_SOUNDS
#define SOUNDS_ON_MEDIAFLASH
#endif //LOAD_SOUNDS

//#define MASTER_PDA
//#define DEBUG_BUILD
//#define TIMESYNC_BYPASS
//#define UNLIMITED_ITEMS
#define FM_DISABLED
//#define MONOLIT_PSY_SOUND_MUTE
//#define MONOLIT_PSY_IMMUNE
//#define ASWAYS_SLEEP //does not works
//#define FAKE_ADC_POWER
//#define SLOWLY_KILL
#define IDDQD  //not fully tested
#ifndef DEBUG_BUILD
	#define CRC_TABLE_RAM //512 bytes
#endif
#define BATTERY_ADC12BIT
#define RFM69_HW_CRC
#define RFM69_FREQUENCY           (446*MHZ_1)
#define ADC_BUFFER_SIZE           16
#define MEMORYMANAGER_POOL_SIZE   3200
#define SOUND_BUFFER_SIZE         64
//#define N3310_WITH_DMA
//#define DEBUG_USART



#ifdef DEBUG_USART //4mbit
//#define DEBUG_USART_FUNCTION_CALL
//#define DEBUG_USART_USABLE_ITEM
//#define DEBUG_USART_EVENT_SYSTEM
//#define DEBUG_USART_DEFENCE
//#define DEBUG_USART_ENV_PACKETS
//#define DEBUG_USART_ERRORS
//#define DEBUG_USART_MULTY_PACKETS
//#define DEBUG_ENV_PACKETS_L0
//#define DEBUG_ENV_PACKETS_L0_GOOD
//#define DEBUG_ENV_PACKETS_L0_FAIL
//#define DEBUG_USART_SUIT_DAMAGE
//#define DEBUG_USART_HEALTH_DOSE
#endif //DEBUG_USART



#ifdef MASTER_PDA
#define TIMESYNC_BYPASS
//#define IDDQD  //not fully tested

#endif //MASTER_PDA

#ifdef DEBUG_BUILD
#warning "DEBUG_BUILD"
#endif // DEBUG_BUILD
#ifdef DEBUG_USART
#warning "DEBUG_USART"
#endif // DEBUG_USART
#ifdef FAKE_ADC_POWER
#warning "FAKE_ADC_POWER"
#endif // FAKE_ADC_POWER
#ifdef IDDQD
#warning "IDDQD"
#endif // IDDQD
//volatile bool LcdStartDMA        = false;
//void Lcd_dma_init(void);
//void Lcd_dma_start(void);

#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("TODO - " #x))



//#warning "add safe zone detection"
//#warning "add blowout detection"
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <avr/eeprom.h>
#include <util/atomic.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <avr/sleep.h>
//#include <nvm.h>
//#define pgm_read_byte pgm_read_byte_far

//void my_callback_generic_set_feature(uint8_t *report_feature);
//void my_callback_generic_report_out(uint8_t *bufferData);
//uint8_t nvm_read_byte1(uint8_t nvm_cmd, uint16_t address);


#if (HARDWARE_REVISION == 1)
  #include "src/boards/pcb_1.h"
#else
  #ERROR UNKNOWN PCB REVISION
#endif

#ifndef BATTERY_ADC12BIT
  //8bit
  typedef uint8_t ADCValue_t;
  typedef uint16_t ADCValueSum_t;
  #define BATTERY_ADC_LEVEL_FULL  (256-1)
#else //12bit
  typedef uint16_t ADCValue_t;
  #if (ADC_BUFFER_SIZE > 16)
    typedef uint32_t ADCValueSum_t;
  #else
    typedef uint16_t ADCValueSum_t;
  #endif
  #define BATTERY_ADC_LEVEL_FULL  (4096U-1)
#endif // BATTERY_ADC12BIT



#include "unionsFixed.h"
//#include "ring_buffer.h"
#include "stalker/drivers/Driver_Clock_xmega128a1u.hpp"
#include "images.h"
#include <stalker/drivers/StalkerUI_Class_n3310.hpp>
#include "src/Sounds.hpp"
#include "n3310_new.h"
#include "src/TFSClass.hpp"
#include "src/TFSFileClass.hpp"
#include "src/TFS_IOWriter.hpp"

#ifndef LOAD_SOUNDS
#include "MemoryManager.hpp"
#include <strings.h>
#include "src/RandomPseudo.hpp"
//MemoryManagerClass::init();
//volatile uint8_t zzz=0;
//MemoryManagerClass MemoryManager;

#include "cpp_NEW_support.h"
#include "crc16.c"
#include "GameTemplate_TemporaryClass.hpp"
#include "src/AES_Support_XMEGA.h"
#include "SmartPointers.cpp"
#include "AES_Class.h"


#include "DeviceConfigClass.hpp"

#include "stalker/drivers/Driver_AR1010.hpp"
#include "stalker/drivers/Driver_AnoRadRarioModule_RFM69.hpp"
#include "stalker/TimerClass.hpp"
#include "src/PowerManager.hpp"//uses HAL
#include "stalker/Class_StalkerLayer0.hpp"
#include "stalker/Class_StalkerLayer1.hpp"
#include "stalker/Class_StalkerLayer2.hpp"
#include <LogClass.hpp>

//#include "M25P05_instructions.h"
#include "src/PlayerSkillsClass.hpp"
//#include "M25P05.c"
#include "tabr_RFM69.h"
#include "RFM69_HAL.hpp"
#include "radiomark.h"
#include "stalker.hpp"

#include "src/DamageClass.hpp"
#include "src/AnomalyClass.hpp"
#include "stalker/Environment.hpp"
#include "src/EEPROM_StructPlayer.hpp"
//#include "src/PlayerEffectsOld.hpp"
#include "src/PlayerEffectsClass.hpp"
#include "src/PlayerClass.hpp"

#include "src/ChangableParameters.hpp"
#include "src/Items.hpp"
//#include "PlayerInventory.h"
#include "src/Buttons.hpp"
#include "src/pdamenu.hpp"
//#include "RTC.h"
//#ifndef FM_DISABLED
//#include "fm.h"
//#endif
//#include "ds1307.h"
#include "src/PlayerSuitClass.hpp"
//TODO("Do i need PlayerEffectsNGClass");
//#include "src/PlayerEffectsNGClass.hpp"
#include "src/BackLightClass.hpp"
#include "src/ConfigClass.hpp"
#include "src/VibroClass.hpp"
#include "src/ArtefactClass.hpp"
#include "src/ArtefactPorts.hpp"
#include "src/UsableItemClass.hpp"
#include <TimeClass.hpp>
#include "src/QuestClass.hpp"
#include "src/ItemInformationClass.hpp"
//#include "ActionsClass.h"
#include "src/EventSystemClass.hpp"
//#include "src/Suits.h"
#include "src/GameConfig.hpp"
#include "src/PlayerStatistics.hpp"
#include "src/hackableComputer.hpp"
#include "src/InGameEventsClass.hpp"
#include "protocols/protocolComputerHack.h"
#include "src/InGameEvent_BlowoutClass.hpp"
#include "src/InGameEvent_RadStormClass.hpp"
#include "src/InGameEvent_SleepTimeClass.hpp"
#include "src/GameCharacteristicsClass.hpp"
#include <ErrorClass.hpp>
#include "RadiomarkClass.hpp"//lib
#include "src/SleepModeInterface.hpp"
#include "src/ExternalEEPROMClass.hpp"
#include "src/FactionsClass.hpp"
#include "Node.hpp"
#include "src/TimeUpdateClass.hpp"
#include "src/GrenadeClass.hpp"
#include "src/SkinClass.hpp"
#else //else LOAD_SOUNDS

void copySounds(void);
class Driver_AnoRadRarioModule
{
public:
void IOInit(void){};
void HardwareInitialization(void){};
};
class ArtefactHardwareInterface
{
public:
};

#include "stalker/HAL.hpp"
#endif //else LOAD_SOUNDS



#include <stalker/LcdClass.hpp>
#include <n3310LcdClass.hpp>
//#include "src/runlevels.h"
#include "src/MediaMemoryClass.hpp"
#include "src/PDAImagesClass.hpp"
#include "src/MediaFlashClass.hpp"
#include <LcdStringCopyClass.hpp>
#include "src/RuntimeClass.hpp"
#include "src/Class_SPIFS_P256.hpp"
//#include "src/USBBootClass.hpp"
#include "src\ASF\xmega\drivers\usb\usb_device.h"


#ifndef LOAD_SOUNDS
///////////GLOBAL VARS///////////
//volatile uint8_t hui              = 0;
//volatile uint8_t grenadeDelayHackTimer      = 0;
uint8_t InGameEvent_SleepTimer          = 0;
//volatile bool LCDstartDMA            = false;
//bool LCD_DMA_Activated              = false;
uint8_t BlowoutTimer              = 0;//timer to verw symbol "star"
#define BLOWOUT_SAFE_TIME_SEC          5

//#define RUNLEVEL_INTERRUPTS_ALREADY_ENABLED    4
//uint8_t hui1 = 0;
//uint16_t hui = 0;

volatile ADCValue_t ADCValueRAWArray[ADC_BUFFER_SIZE];
volatile ADCValueSum_t ADCValueSum    = 0;
volatile uint8_t ADCValueIDX      = 0;
volatile bool ADCMeasurmentsStarted    = false;
//uint8_t batteryLevel            = 0;
//#define ADCValue ADCA.CH0.RESL



TimeClass TimeRTC;
ErrorClass Errors;
RandomPseudoClass RandomPseudo;
PowerManagerClass PowerManager;
//n3310LcdClass LcdDisplay;
//TimeClass TimeRTC1;
//TimeClass TimeSystem;
ConfigClass PDASettings;
TimerMSClass TimerMS;

DeviceConfigClass DeviceConfig;
GameConfig GameCFG;
//PlayerEffects_Interface* EffectsTMP[16];


//uint8_t hui=0;
RFM69 radio;
Environment Env;
STALKER Stalker;
PlayerClass Player;
PDAMenuClass PDAMenu;
//ArtefactPortsClass ArtefactPorts;
ButtonsClass Buttons;
PlayerEffectsClass PlayerEffects;
//PlayerEffectsNGClass PlayerEffectsNG;
BackLightClass BackLight;
AnomalyClass Anomaly;
ArtefactClass Artefact;
UsableItemClass UsableItem;
VibroClass Vibro;
//PlayerSuitClass PlayerSuit;
QuestClass Quest;
ItemInformationClass ItemInformation;
ActionsClass PlayerActions;
//Class_StalkerLayer2 StalkerLayer2;
Class_StalkerLayer2* StalkerLayer2;
//uint8_t PsyBeepKeepOnHack  = 0;

EventSystemClass EventSystem;
//DamageClass PlayerDamage;
AR1010 Ar1010;
//PlayerSkillsClass PlayerSkills;
HackableComputerClass HackableComputer;
InGameEventsClass InGameEvents;
//TWI UserEEPROM=TWI(&TWIC, TWI_EEPROM_TWI_ADDRESS, TWI_EEPROM_SPEED_KHZ);
InGameEvent_BlowoutClass BlowoutEvent;
InGameEvent_BlowoutPrepareClass BlowoutPrepareEvent;
InGameEvent_RadStormClass RadStormEvent;
InGameEvent_SleepTimeClass SleepEvent;
EEPROM_DataClass EEPROM_Data;
FlashMemoryClass<ArtefactFlash00SPI> Artefact00;
FlashMemoryClass<ArtefactFlash01SPI> Artefact01;
FlashMemoryClass<ArtefactFlash02SPI> Artefact02;
FlashMemoryClass<ArtefactFlash03SPI> Artefact03;
FlashMemoryClass<ArtefactFlash04SPI> Artefact04;
//PlayerEffect_SafeShelterClass* EffectSafeShelter;//  = new PlayerEffect_SafeShelterClass(0, 1, 30);//30 sec
ExternalEEPROMClass ExternalEEPROM;
TimeUpdateClass TimeUpdate;
GrenadeClass Grenade;
//LogClass Log;
EmissionInstanceDetectorClass EmissionInstanceDetector;
PlayerEffect_SafeShelterClass* EffectSafeShelterHack  = nullptr;
#warning "Get Player Effects by GUID is doesn't work!"
#endif //LOAD_SOUNDS

StalkerUI_Class StalkerUI;
Sound PDASound;
Driver_Clock Clock;
Class_HAL HAL(&Clock);
LcdClass Lcd;
FlashMemoryClass<MediaFlashSPI> MediaMemory;
LcdStringCopyClass LcdStringCopy;
PDAImagesClass PDAImages;
//RuntimeClass Runtime;
//Class_SPIFS_P256 SPIFS_P256;
TFSClass TFS;

//PlayerEffectsInterface** ArtefaceEffectsContainer;

//DeviceConfigClass DeviceConfig;
//#ifndef LOAD_SOUNDS
#include "src/USBBoot.h"
//USBBootClass* zzz = NULL;
USBBootClass* USBBootClassInstance  = NULL;
//#endif

void LcdSPITXData(uint8_t data)
  {
  USARTE1.DATA  = data;
  while (!(USARTE1.STATUS & USART_TXCIF_bm)){};
  USARTE1.STATUS |= USART_TXCIF_bm;
  }
void LcdSPIInit(void)
  {
  //baund=(32M)/(2*(BSEL+1))
  //BSEL=BAUDCTRLB[3..0] BSEL[11:8]
  //BSEL=BAUDCTRLA BSEL[7..0]
  USARTE1.BAUDCTRLB = 0;
  USARTE1.BAUDCTRLA = 1;//1 mean 8M[Bits]??!
  //
  //USARTE1.BAUDCTRLA = 4;//max? frequency
  //USARTE1.BAUDCTRLA = 159;
  USARTE1.CTRLA = 0;//0b00101010; //All interrupts enabled, medium level
//  USARTE1.CTRLB = USART_TXEN_bm | USART_CLK2X_bm;//0b00011000; //Receiver and transmitter enabled
  USARTE1.CTRLB = USART_TXEN_bm;// | USART_CLK2X_bm;//0b00011000; //Receiver and transmitter enabled
  //2x make no sense in SPI Master mode
  //USARTE1.CTRLB = USART_TXEN_bm;//0b00011000; //Receiver and transmitter enabled
  USARTE1.CTRLC = USART_CMODE_MSPI_gc;// 0b11000000; //Master SPI mode, MSB first, leading edge
  }
#ifdef DEBUG_USART
void sendChar(char c)
  {
  while( !(USARTF0_STATUS & USART_DREIF_bm) ); //Wait until DATA buffer is empty
  USARTF0_DATA = c;
  }
void sendString(char *text)
  {
  while(*text)
    {
    sendChar(*text++);
    }
  }
char USARTBuffer[400];
#endif
#ifndef LOAD_SOUNDS


//StalkerSkinClass StalkerSkin;
SkinInterface* SelectedSkin = new StalkerSkinClass;
#warning "[T] Move to game config!"
//SkinInterface* SelectedSkin = new DetectorSkinClass;
//class userFunction1000msClass: public Runnable
//#warning "[T] MediaflsH & RM use one SPI and may stuck!"
class userFunction1000msClass: public ITimerListener
  {
  public:
  //void Task(void)
  void TimerUpdateEvent (uint8_t msPassed)
    {
    static uint16_t oneSecond_msCounter=0;
    
    oneSecond_msCounter+=msPassed;
    if (oneSecond_msCounter < 1000)
      {
      return;
      }
    //else
    oneSecond_msCounter-=1000;
    /*
    PDASound.PlaylistAdd(Sound::SIDS::SID_PDA_NEWS);
    PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
    PDASound.PlaylistAdd(Sound::SIDS::SID_PDA_NEWS);
    PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
    PDASound.PlaylistAdd(Sound::SIDS::SID_PDA_NEWS);
    PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
    PDASound.PlaylistAdd(Sound::SIDS::SID_PDA_NEWS);
    PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
    PDASound.PlaylistAdd(Sound::SIDS::SID_PDA_NEWS);
    PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
    PDASound.PlaylistAdd(Sound::SIDS::SID_PDA_NEWS);
    PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
    PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
    PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
    PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
    PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
    PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
    PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
    PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
    PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
    PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
    PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
    PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);
    PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);*/
    //Player.HealthIncrase(1);
    //TimeSystem.incrementSeconds();
    //PDASound.PlaylistAdd(Sound::SIDS::SID_PDA_NEWS);
    //Env.setPsyLevelFilter(100);
    //Env.RadLevelSetFilter(100);
    //Player.DealDamage({value:5, damageSource:TemporaryClass::DAMAGE_SOURCE_PSY, aggressorSource:DamageClass::AGGRESSOR_SOURCE_EXTERNAL});
    
    #ifdef DEBUG_USART_HEALTH_DOSE
      sprintf (USARTBuffer,"Health: %03d RAD %03d \r\n",Player.GetCurrentHealth(), Player.GetRadiationDose());
      sendString(USARTBuffer);
    #endif

    if (BlowoutTimer > 0)
      {
      --BlowoutTimer;
      }
    if (Player.IsDead())//врем€ можно обновить, но радио вырубаем
      {
      if (!Ar1010.isMuted)
        {
        Ar1010.hmuteON();
        }
      return;
      }
    if (PDASettings.isParameterSet(ConfigClass::SETTINGS_RADIO_ON))
      {
      Ar1010.getRSSIValue();
      if (Ar1010.lastRSSIFiltered > 14)
        {
        if (Ar1010.isMuted)
          {
          Ar1010.hmuteOFF();
          }
        }
      else
        {
        if (!Ar1010.isMuted)
          {
          Ar1010.hmuteON();
          }
        }
      }
    }
//  uint8_t getRepeatTime(void)
//    {
//    return TimerClass::TIME_1000MS;
//    }
  } userFunction1000msTask;
uint8_t ReadSignatureByte(uint16_t Address)
  {
  NVM_CMD = NVM_CMD_READ_CALIB_ROW_gc;
  uint8_t Result;
  __asm__ ("lpm %0, Z\n" : "=r" (Result) : "z" (Address));
  NVM_CMD = NVM_CMD_NO_OPERATION_gc;
  return Result;
  }
#endif //LOAD_SOUNDS

int main(void)
  {
//  USBBoot();
  //while(1);
  uint8_t updateCounterInSleepMode=0;

  //runlevel_0();//XTAL
  RuntimeClass::Run();
  //DeviceConfig.WriteNewDevID(31);

#ifdef LOAD_SOUNDS
  MediaMemory.IOInit();
  //MediaFlashSPI::HardwareInitialization();
  copySounds();
    while(1);
#else

  //PDASound.PlaylistAdd(Sound::SIDS::SID_PDA_NEWS);
  //PDASound.PlaylistAdd(Sound::SIDS::SID_BLOWOUT_HIT_2);
  //PlayerEffects.ApplyEffect()
  //PlayerEffects.RenewEffectInstance(TemporaryClass::PLAYEREFFECT_SAFE_SHELTER);
  //PlayerEffects.ApplyEffectInstance(TemporaryClass::PLAYEREFFECT_TMP_1);
  //PlayerEffects.ApplyEffectInstance(TemporaryClass::PLAYEREFFECT_TMP_2);
  //PlayerEffects.ApplyEffectInstance(TemporaryClass::PLAYEREFFECT_TMP_3);
  
  //Player.DealDamage(50, DamageSource_t::DAMAGE_SOURCE_GENERIC, DamageClass::AGGRESSOR_SOURCE_EXTERNAL);

  //PDAMenu.DrawImg(PDAImagesClass::IMAGES::IMG_RADIO_WAVES_3);

  PDASound.PlaylistAdd(Sound::SIDS::SID_PIK);


  //PsyBeepKeepOnHack = 1;
  //PDASound.startSoundsPsy(175);
//  PDASound.stopSoundsPsy();
  //PDASound.PlaylistAdd(Sound::SIDS::SID_BLOWOUT_HIT_2);
  /*
  RingBuffer<16> testBuffer;
  //testBuffer.Clear();
  testBuffer.Write(1);
  testBuffer.Write(2);
  testBuffer.Write(3);
  testBuffer.Write(4);
  testBuffer.Write(5);
  testBuffer.Write(6);
  */
  while(1)
    {
    PDASound.FillBufer();
    /*
    //PDAMenu.selectMenuID(PDAMenu_MainInterface::MENUID_QUESTS);
    sprintf (Lcd.lcd_buf,"%03d",SoundBuffer[0]);
    LcdString(12,LCD_LINE_2);
  sprintf (Lcd.lcd_buf,"%03d",PDASound.IsHiFiActive());
  LcdString(12,LCD_LINE_3);
//  sprintf (Lcd.lcd_buf,"%03d",PDASound.queueBottom);
//  LcdString(12,LCD_LINE_4);
//  sprintf (Lcd.lcd_buf,"%03d",PDASound.queueTop);
//  LcdString(12,LCD_LINE_5);
//  sprintf (Lcd.lcd_buf,"%03d",PDASound.Buf.GetUsedSpace());
  sprintf (Lcd.lcd_buf,"%03d%03d %03d%03d",SoundBuffer.IsNotEmpty(), SoundBuffer.GetUsedSpace(), SoundBuffer.GetFreeSpace(), hui1);
  //PDASound.FillBufer();
  //uint8_t readedD=0;
  //testBuffer.Read(readedD);
  //sprintf (Lcd.lcd_buf,"%03d%03d %03d%03d",testBuffer.IsFull(), testBuffer.GetUsedSpace(), testBuffer.GetFreeSpace(), readedD);
  LcdString(1,LCD_LINE_5);
  sprintf (Lcd.lcd_buf,"%03d%03d %03d",SoundBuffer._writeCount, SoundBuffer._readCount, hui);
  LcdString(1,LCD_LINE_6);
  */

  //PDASound.Buf.Write(1);
  /*
    uint8_t readedData  = PDASound.getNextPlayableSample();
    if (readedData != SOUND_END_OF_SOUND)
      {
      sprintf (Lcd.lcd_buf,"%03d", readedData);
      LcdString(12,LCD_LINE_6);
      }*/
    //_delay_ms(1000);
//    sprintf (Lcd.lcd_buf,"%03d",hui);
//    LcdString(12,LCD_LINE_6);
    //while ((ADCA.CTRLA & ADC_CH0START_bm) == 1);//wait for conversion ends
//      while ((ADCA.INTFLAGS & ADC_CH0IF_bm) == 0);//wait for conversion ends
//        sprintf (Lcd.lcd_buf,"%d",1);
//    sprintf (Lcd.lcd_buf,"%03u", hui);
//    LcdString(12,LCD_LINE_1);
    n3310LcdClass::RequestUpdate();
    #ifdef DEBUG_BUILD
      {
      if (PDAMenu.getSelectedMenuID() == PDAMenu_MainInterface::MENUID_MAIN)
        {
        sprintf (Lcd.lcd_buf,"%01d%01d%01d",VBUSPin::IsPinHigh(), ChargerPinCharging::IsPinLow(), ChargerPinStandby::IsPinLow());
//        sprintf (Lcd.lcd_buf,"%d",1);
        LcdString(12,LCD_LINE_1);
        //sprintf (Lcd.lcd_buf,"%03u", SID);
        //uint8_t * p_var8 = (uint8_t *) &zzz.value_int;
        //printf("%02X", *p_var8);
        //sprintf (Lcd.lcd_buf,"%02X", *p_var8);
//        sprintf (Lcd.lcd_buf,"%02X", zzz.byte_field.h);
        //LcdString(12,LCD_LINE_2);
        sprintf (Lcd.lcd_buf,"%03d",Player.GetCurrentHealth());
        LcdString(12,LCD_LINE_3);
        sprintf (Lcd.lcd_buf,"%03d",RandomPseudo.get());
        LcdString(12,LCD_LINE_4);
//        sprintf (lcd_buf,"%01d",StalkerLayer2->L1.L0.isGoodPacketReceived);
//        sprintf (lcd_buf,"%03d",ADCValue);
//        LcdString(12,LCD_LINE_5);
//        sprintf (lcd_buf,"%03d",radio.isPacketReceivedHigh());
//        LcdString(12,LCD_LINE_6);
//        sprintf (lcd_buf, "fm:%03u %01u %05u", Ar1010.lastRSSIFiltered, Ar1010.isMuted, MemoryManager.getAvailableBytes());
//        sprintf (lcd_buf, "%05u %05u %d",MemoryManager.POOL_SIZE, MemoryManager.pointerTop, MemoryManager.fail);

        //sprintf (lcd_buf,"%03u",hui);
        //LcdString(12,LCD_LINE_5);
        //LcdChr(FONT_1X, )

        sprintf (Lcd.lcd_buf, "%01u %01u", PowerManager.isInSleepMode(), PowerManager.isCanWakeup());
        //sprintf (lcd_buf, memTest);
        LcdString(12,LCD_LINE_6);

        n3310LcdClass::RequestUpdate();
        //_delay_ms(100);
/*
ADC:
121-2.555
122-2.667
124-2.820
*/
        }
      /*else if (PDAMenu.getSelectedMenuID() == PDAMenuClass::MENUID_DEBUG)
        {
        sprintf (lcd_buf, "fm:%03d", Ar1010.lastRSSIFiltered);
        LcdString(1,LCD_LINE_5);
        LcdUpdate();
        }*/
      }
    #endif //DEBUG_BUILD

    if (PowerManager.isInSleepMode())
      {
      PowerManager.StartBatteryADCMeasurments();
      //PowerManager.SleepModeOneSecTick();
      //StalkerLayer2->L1.isEnvironmentActive();
      
      InGameEvents.checkState();
      if (InGameEvent_SleepTimer > 0)
        {
        InGameEvent_SleepTimer--;
        }
      //_delay_ms(1);  //0,000000625 sec need to ADC finish
      //_delay_us(100);  //0,00008 with 512 div
      //set_sleep_mode(SLEEP_MODE_IDLE);
      //while ((ADCA.INTFLAGS & ADC_CH0IF_bm) == 0)//wait for conversion ends
      //BackLight.turnON();
      while(ADCMeasurmentsStarted)
        {
        //sleep_enable();
        //sleep_cpu();
        //sleep_disable();
        }
      //BackLight.turnOFF();
      #ifdef ASWAYS_SLEEP
        sprintf (Lcd.lcd_buf, "%04d", PowerManager.GetBatteryVoltage());
        LcdString(1,LCD_LINE_1);
      #endif
      if (++updateCounterInSleepMode > 5) //Ўќ«јѕ»«ƒ≈÷??!
        {
      /*while(1)
        {
        PowerManager.startADCMeasurments();
        set_sleep_mode(SLEEP_MODE_IDLE);
        while(ADCMeasurmentsStarted)
          {
          sleep_enable();
          sleep_cpu();
          sleep_disable();
          }
        sprintf (lcd_buf, "%05u", PowerManager.getVoltage());
        LcdString(1,LCD_LINE_1);
        */
        updateCounterInSleepMode=0;
        //sprintf (Lcd.lcd_buf, "%04d", PowerManager.GetBatteryVoltage());
        sprintf (Lcd.lcd_buf, "%03u%s", PowerManager.GetChargePercent(), "%");
        LcdString(1,LCD_LINE_1);
        //sprintf (Lcd.lcd_buf, "%03d %03d %01d %01d",(rand()%256), PowerManager.GetChargePercent(), PowerManager.isCanWakeup(), PowerManager.isCharging());
        sprintf (Lcd.lcd_buf, "%02u:%02u:%02u", TimeRTC.GetHour(), TimeRTC.GetMinute(), TimeRTC.GetSecond());
        LcdString(1,LCD_LINE_6);
        n3310LcdClass::RequestUpdate();
        }
      set_sleep_mode(SLEEP_MODE_PWR_SAVE);
      /*
      sprintf (lcd_buf, "%01u %01u", PowerManager.isInSleepMode(), PowerManager.isCanWakeup());
      LcdString(1,LCD_LINE_6);
      LcdUpdate();
      */
      //ADCA.INTFLAGS  |= ADC_CH0IF_bm;
      //while ((ADCA.INTFLAGS & ADC_CH0IF_bm) == 0);//wait for conversion ends
      //while ((ADCA.CTRLA & ADC_CH0START_bm) == 1);//wait for conversion ends
      #ifndef ASWAYS_SLEEP
      if (PowerManager.isCanWakeup())
        {
        PowerManager.EnterNormalMode();
        }
      #endif
      }
    else
      {
      if (PowerManager.isBatteryDischarged())
        {
        PowerManager.EnterSleepMode(PowerManagerClass::SLEEP_EVENT_BATT);
        }
      else if (InGameEvent_SleepTimer > 0)
        {
        PowerManager.EnterSleepMode(PowerManagerClass::SLEEP_EVENT_EVENT);
        }
      else
        {
        TimerMS.CheckPassed();
        }
      }
    sleep_enable();
    sleep_cpu();
    sleep_disable();
    }
#endif //LOAD_SOUNDS
  }
//#ifndef LOAD_SOUNDS
//Moved to PlayerClass
//void damageTaken(void* damage)
//  {
//  Player.GetSuit()->damageTaken((DamageClass*)damage);
//  }
/*
//Event disabled!
void usableItem_ConnDisconn(void* state)
  {
  #ifdef DEBUG_USART_EVENT_SYSTEM
    sprintf (USARTBuffer,"[usableItem_ConnDisconn] %03u\r\n",((uint16_t)state));
    sendString(USARTBuffer);
  #endif
  PDAMenu.PDAMenu_ConnectedItem.itemJustConnectedOrDisconnected((static_cast<UsableItemClass::CONNECTION_STATE>((uint16_t)state)));
  //PDAMenu.get
//  PDAMenu.PDAMenu_ConnectedItem.itemJustConnectedOrDisconnected(UsableItemClass::CONNECTION_STATE::CONNECTION_STATE_CONNECTED);
  //CONNECTION_STATE
  //Player.getSuit()->damageTaken((DamageClass*)damage);
  }
*/
/*
//moved to PDAMenu_MainClass
void PDAMenu_Main_ChargeStateChanged(void* state)
  {
  if ((uint16_t)state < PowerManagerClass::CHARGE_STATES::CHARGE_STATES_NUM)
    {
    #warning "HACK! change to interface call!"
    //PDAMenu.PDAMenu_Main.ChargeStateChanged((static_cast<PowerManagerClass::CHARGE_STATES>((uint16_t)state)));
    ((PDAMenu_MainClass*)(PDAMenu.GetDefaultMenu()))->ChargeStateChanged((static_cast<PowerManagerClass::CHARGE_STATES>((uint16_t)state)));
    }
  else //error
    {
    //PDAMenu.PDAMenu_Main.ChargeStateChanged((static_cast<PowerManagerClass::CHARGE_STATES>(PowerManagerClass::CHARGE_STATES::CHARGE_STATES_NUM-1)));
    }
  
  
  }
*/
/*
void EnvironmentProcessed(void* state)
  {
  Anomaly.EnvironmentProcessed();
  Env.EnvironmentProcessed();
  }
*/
//#endif //LOAD_SOUNDS
//#include "src/runlevels.c"
#include "n3310_new.c"
#ifndef LOAD_SOUNDS
#include "RFM69_HAL.cpp"
#include "stalker.cpp"
#include "src/AnomalyClass.cpp"
#include "stalker/drivers/Driver_AnoRadRarioModule_RFM69.cpp"
#include "stalker/Class_StalkerLayer0.cpp"
#include "stalker/Class_StalkerLayer1.cpp"
#include "stalker/Class_StalkerLayer2.cpp"
#include "stalker/TimerClass.cpp"
#include "stalker/Environment.cpp"

#include "src/pdamenu.cpp"
#include "src/ArtefactClass.cpp"
//#include "src/PlayerEffectsOld.cpp"
#include "src/PlayerEffectsClass.cpp"
//#include "fm.cpp"
#include "src/PlayerSuitClass.cpp"
#include "src/interrupts.c"
#include "src/PlayerStatistics.cpp"
#include "ConnectedItemClass.cpp"
//#include "src/PlayerEffectsNGClass.cpp"
#include "src/PDAMenu_MenuItems.cpp"


#include "src/PlayerSkillsClass.cpp"
#include "src/ArtefactPorts.cpp"
#include "src/ItemInformationClass.cpp"//cross
#include "src/Buttons.cpp" //cross

//можно добавить в проект
#include "src/BackLightClass.cpp"
#include "src/InGameEvent_BlowoutClass.cpp"
#include "src/InGameEvent_RadStormClass.cpp"
#include "src/InGameEvent_SleepTimeClass.cpp"
#include "src/ConfigClass.cpp"
#include "stalker/drivers/Driver_AR1010.cpp"
#include "src/hackableComputer.cpp"
#include "src/InGameEventsClass.cpp"
#include "src/PlayerClass.cpp"
#include "src/PowerManager.cpp"
#include "src/QuestClass.cpp"
#include "src/UsableItemClass.cpp"
#include "src/VibroClass.cpp"
#include "src/DamageClass.cpp"
#include "src/SuitsContainerClass.cpp"
#include "src/Suits.cpp"
#include "src/GameConfig.cpp"
#include "src/GameCharacteristicsClass.cpp"
#include "src/PDAMenu_MainInterface.cpp"
#include "src/EventSystemClass.cpp"
#include "src/DeviceConfigClass.cpp"
#include "src/Items.cpp"
#include <ErrorClass.cpp>
#include "src/FactionsClass.cpp"
#include "src/EEPROM_DataClass.cpp"
#include "MemoryManager.cpp"
#include "src/TimeUpdateClass.cpp"
#include "src/GrenadeClass.cpp"
#include "RadiomarkClass.cpp"//lib
#include <Logclass.cpp>
#include <PlayerEffectsInterface.cpp>
#else
  #include "CopySounds.hpp"
#endif //LOAD_SOUNDS



#include "stalker/drivers/StalkerUI_Class_n3310.cpp"
#include "src/Sounds.cpp"
//#include "crc16.c"
#include "stalker/drivers/Driver_Clock_xmega128a1u.cpp"
//#include "stalker/drivers/Driver_IO_xmega128a1u.c"
#include "stalker/LcdClass.cpp"
#include "n3310LcdClass.cpp"
#include "src/MediaMemoryClass.cpp"
#include "src/PDAImagesClass.cpp"
#include "stalker/HAL.cpp"
#include "src/RuntimeClass.cpp"
#include "src/USBBootClass.cpp"

//#include "src/ASF/common/services/clock/xmega/sysclk.c"
//#include "src/ASF/common/services/usb/udc/udc.c"
//#include "src\ASF\xmega\drivers\usb\usb_device.c"
////#include "src\ASF\xmega\drivers\nvm\nvm_asm.s"
//#include "src\ASF\xmega\drivers\nvm\nvm.c"
//#include "src\ASF\common\services\usb\class\hid\device\udi_hid.c"
//#include "src\ASF\common\services\usb\class\hid\device\generic\udi_hid_generic.c"
//#include "src\ASF\xmega\drivers\usb\usb_device.c"
//#include "src\ASF\common\services\usb\class\hid\device\generic\udi_hid_generic_desc.c"
//#include "src\ASF\xmega\drivers\nvm\nvm_asm.inc"
//extern "C"
//{
/*
void ccp_write_io(void *addr, uint8_t value)
  {
  void *z = (void *)&addr;

  __asm__ volatile("out %[ccp], %[ioreg]"  "\n\t"
  "st z, %[cmdex]"
  :
  : [ccp] "I" (_SFR_IO_ADDR(CCP)),
  [ioreg] "d" (CCP_IOREG_gc),
  [cmdex] "r" (value),
  [z] "z" (z)
  );
  }
void ccp_write_io_BAK(void *addr, uint8_t value)
  {
  void *z = (void *)&NVM_CTRLA;

  __asm__ volatile("out %[ccp], %[ioreg]"  "\n\t"
  "st z, %[cmdex]"
  :
  : [ccp] "I" (_SFR_IO_ADDR(CCP)),
  [ioreg] "d" (CCP_IOREG_gc),
  [cmdex] "r" (NVM_CMDEX_bm),
  [z] "z" (z)
  );
  }
uint8_t nvm_read_byte(uint8_t nvm_cmd, uint16_t address)
  {
  nvm_wait_until_ready();
  return nvm_flash_read_byte(address);

  }
void my_callback_generic_set_feature(uint8_t *report_feature)
  {
  hui=1;
  }
void my_callback_generic_report_out(uint8_t *bufferData)
  {

  }
*/
void my_callback_generic_set_feature(uint8_t *report_feature)
{
  USBBootClassInstance->my_callback_generic_set_feature(report_feature);
}
void my_callback_generic_report_out(uint8_t *bufferData)
{
  USBBootClassInstance->my_callback_generic_report_out(bufferData);
}
#ifndef LOAD_SOUNDS
#include "USBBootClass.cpp"
#include "src/SkinClass.cpp"
#endif

#include "src\ASF\common\services\usb\class\hid\device\generic\udi_hid_generic.cpp"
#include "src\ASF\common\services\usb\class\hid\device\udi_hid.cpp"
//#include "src\ASF\xmega\drivers\usb\usb_device.cpp" //if add, usb STUCKS!
#include "src/TFSClass.cpp"
#include "src/TFSFileClass.cpp"
#include "src/TFS_IOWriter_MediaMemoty.cpp"
#include "Strings.cpp"

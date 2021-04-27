/*
 * MediaMemoryClass.h
 *
 * Created: 21.02.2016 4:29:01
 *  Author: tabr
 */ 


#ifndef MEDIAMEMORYCLASS_H_
#define MEDIAMEMORYCLASS_H_

#include "SleepModeInterface.hpp"
typedef uint8_t FlashMemoryInstruction;

enum FLASH_MEMORY_CAPACITY
  {
  FLASH_MEMORY_CAPACITY_UNKNOWN,
  FLASH_MEMORY_CAPACITY_256BIT,
  FLASH_MEMORY_CAPACITY_1MBIT,
  FLASH_MEMORY_CAPACITY_2MBIT,
  FLASH_MEMORY_CAPACITY_4MBIT,
  FLASH_MEMORY_CAPACITY_8MBIT,
  FLASH_MEMORY_CAPACITY_16MBIT,
  FLASH_MEMORY_CAPACITY_32MBIT,
  };
enum AVAILABLE_DRIVERIDS
  {
  AVAILABLE_DRIVERID_UNKNOWN,
  AVAILABLE_DRIVERID_GENERIC,
  AVAILABLE_DRIVERID_W25X10_20_40_80,
  AVAILABLE_DRIVERID_W25Q80_16_32,
  AVAILABLE_DRIVERID_M25P05,
  };

class FlashMemoryDriverInterface
  {
  public:
    virtual FlashMemoryInstruction InstructionPageProgram(void)=0;
    virtual FlashMemoryInstruction InstructionWriteEnable(void)=0;
    virtual FlashMemoryInstruction InstructionGetStatusRegister1(void)=0;
    virtual FlashMemoryInstruction InstructionEraseDevice(void)=0;
    virtual FlashMemoryInstruction PowerDownInstruction(void)=0;
    virtual FlashMemoryInstruction ReleasePowerDownInstruction(void)=0;
    virtual void ReleasePowerDownDelay(void)=0;
    virtual FLASH_MEMORY_CAPACITY GetCapacity(uint16_t JEDECID)=0;
    virtual bool isContainDevice(uint16_t JEDECID)=0;
    virtual FlashMemoryInstruction GetReadInstrunction(void)=0;
    virtual AVAILABLE_DRIVERIDS GetDriverID(void)=0;
  protected:
  private:
  };

class FlashMemoryDriverFlashUnknown : public FlashMemoryDriverInterface
  {
  public:
    AVAILABLE_DRIVERIDS GetDriverID(void)
      {
      return AVAILABLE_DRIVERID_UNKNOWN;
      }
    FlashMemoryInstruction InstructionPageProgram(void)
      {
      return 0;
      }
    FlashMemoryInstruction InstructionGetStatusRegister1(void)
      {
      return 0;
      }
    FlashMemoryInstruction InstructionWriteEnable(void)
      {
      return 0;
      }
    FlashMemoryInstruction InstructionEraseDevice(void)
      {
      return 0;
      }
    FlashMemoryInstruction GetReadInstrunction(void)
      {
      return 0;
      }
    FlashMemoryInstruction PowerDownInstruction(void)
      {
      return 0;
      }
    FlashMemoryInstruction ReleasePowerDownInstruction(void)
      {
      return 0;
      }
    void ReleasePowerDownDelay(void)
      {
      
      }
    FLASH_MEMORY_CAPACITY GetCapacity(uint16_t JEDECID)
      {
      return FLASH_MEMORY_CAPACITY::FLASH_MEMORY_CAPACITY_UNKNOWN;
      }
    bool isContainDevice(uint16_t JEDECID)
      {
      return true;
      }
  protected:
  private:
  };
class FlashMemoryDriverFlashGenericClass : public FlashMemoryDriverInterface
  {
  public:
    AVAILABLE_DRIVERIDS GetDriverID(void)
      {
      return AVAILABLE_DRIVERID_GENERIC;
      }
    FlashMemoryInstruction InstructionPageProgram(void)
      {
      return 0;
      }
    FlashMemoryInstruction InstructionGetStatusRegister1(void)
      {
      return 0x02;
      }
    FlashMemoryInstruction InstructionWriteEnable(void)
      {
      return 0x06;
      }
    FlashMemoryInstruction InstructionEraseDevice(void)
      {
      return 0xc7;
      }
    FlashMemoryInstruction GetReadInstrunction(void)
      {
      return 0x03;
      }
    FlashMemoryInstruction PowerDownInstruction(void)
      {
      return 0xb9;
      }
    FlashMemoryInstruction ReleasePowerDownInstruction(void)
      {
      return 0xab;
      }
    void ReleasePowerDownDelay(void)
      {
      
      }
    FLASH_MEMORY_CAPACITY GetCapacity(uint16_t JEDECID)
      {
      return FLASH_MEMORY_CAPACITY::FLASH_MEMORY_CAPACITY_UNKNOWN;
      }
    bool isContainDevice(uint16_t JEDECID)
      {
      return true;
      }
  protected:
  private:
  };
class FlashMemoryDriverFlashW25X10_20_40_80Class : public FlashMemoryDriverInterface
  {
  public:
        

    const static uint8_t INSTRUCTION_WRITE_ENABLE      = 0x06;
    const static uint8_t INSTRUCTION_WRITE_DISABLE      = 0x04;
    const static uint8_t INSTRUCTION_READ_STATUS_REGISTER  = 0x05;
    const static uint8_t INSTRUCTION_WRITE_STATUS_REGISTER  = 0x01;
    const static uint8_t INSTRUCTION_READ_DATA        = 0x03;
    const static uint8_t INSTRUCTION_FAST_READ        = 0x0b;
    const static uint8_t INSTRUCTION_FAST_READ_DUAL_OUTPUT  = 0x3b;
    const static uint8_t INSTRUCTION_PAGE_PROGRAM      = 0x02;
    const static uint8_t INSTRUCTION_BLOCK_ERASE_64K    = 0xd8;
    const static uint8_t INSTRUCTION_SECTOR_ERASE_4k    = 0x20;
    const static uint8_t INSTRUCTION_CHIP_ERASE        = 0xc7;
    const static uint8_t INSTRUCTION_POWER_DOWN        = 0xb9;//+time
    const static uint8_t INSTRUCTION_RELEASE_PD__DEVID    = 0xab;//+time
    const static uint8_t INSTRUCTION_MANUFACTURER__DEVID  = 0x90;
    const static uint8_t INSTRUCTION_JDEC_ID        = 0x9f;

//    const static uint8_t STATUS_REGISTER_BIT00_BUSY      = 0; //ERASE or WRITE in progress
//    const static uint8_t STATUS_REGISTER_BIT01_WEL      = 1; //Write enable latch
//    const static uint8_t STATUS_REGISTER_BIT02_BP0      = 2; //Block protect bits (non-volatile)
//    const static uint8_t STATUS_REGISTER_BIT03_BP1      = 3; //Block protect bits (non-volatile)
//    const static uint8_t STATUS_REGISTER_BIT04_BP2      = 4; //Block protect bits (non-volatile)
//    const static uint8_t STATUS_REGISTER_BIT05_TB      = 5; //TOP/BOTTOM WRITE protect (non-volatile)
//    const static uint8_t STATUS_REGISTER_BIT06_R      = 6; //RESERVED
//    const static uint8_t STATUS_REGISTER_BIT07_SRP      = 7; //STATUS REGISTER PROTECT (non-volatile)

    const static uint16_t DEVICE_ID_W25X10_JEDEC      = 0x3011;
    const static uint16_t DEVICE_ID_W25X20_JEDEC      = 0x3012;
    const static uint16_t DEVICE_ID_W25X40_JEDEC      = 0x3013;
    const static uint16_t DEVICE_ID_W25X80_JEDEC      = 0x3014;
    
    const static uint8_t TRES1_DELAY_US              = 3;

    AVAILABLE_DRIVERIDS GetDriverID(void)
      {
      return AVAILABLE_DRIVERID_W25X10_20_40_80;
      }
    FlashMemoryInstruction InstructionPageProgram(void)
      {
      return INSTRUCTION_PAGE_PROGRAM;
      }
    FlashMemoryInstruction InstructionGetStatusRegister1(void)
      {
      return INSTRUCTION_READ_STATUS_REGISTER;
      }
    FlashMemoryInstruction InstructionWriteEnable(void)
      {
      return INSTRUCTION_WRITE_ENABLE;
      }
    FlashMemoryInstruction InstructionEraseDevice(void)
      {
      return INSTRUCTION_CHIP_ERASE;
      }
    FlashMemoryInstruction GetReadInstrunction(void)
      {
      return this->INSTRUCTION_READ_DATA;
      }
    FlashMemoryInstruction PowerDownInstruction(void)
      {
      return this->INSTRUCTION_POWER_DOWN;
      //TODO: delay??!
      }
    FlashMemoryInstruction ReleasePowerDownInstruction(void)
      {
      return this->INSTRUCTION_RELEASE_PD__DEVID;
      }
    void ReleasePowerDownDelay(void)
      {
      _delay_us(this->TRES1_DELAY_US);
      }
    FLASH_MEMORY_CAPACITY GetCapacity(uint16_t JEDECID)
      {
      switch (JEDECID)
        {
        case this->DEVICE_ID_W25X10_JEDEC:
          {
          return FLASH_MEMORY_CAPACITY::FLASH_MEMORY_CAPACITY_1MBIT;
          }
        break;
        case this->DEVICE_ID_W25X20_JEDEC:
          {
          return FLASH_MEMORY_CAPACITY::FLASH_MEMORY_CAPACITY_2MBIT;
          }
        break;
        case this->DEVICE_ID_W25X40_JEDEC:
          {
          return FLASH_MEMORY_CAPACITY::FLASH_MEMORY_CAPACITY_4MBIT;
          }
        break;
        case this->DEVICE_ID_W25X80_JEDEC:
          {
          return FLASH_MEMORY_CAPACITY::FLASH_MEMORY_CAPACITY_8MBIT;
          }
        break;
        }
      return FLASH_MEMORY_CAPACITY::FLASH_MEMORY_CAPACITY_UNKNOWN;
      }
    bool isContainDevice(uint16_t JEDECID)
      {
      switch (JEDECID)
        {
        case this->DEVICE_ID_W25X10_JEDEC:
        case this->DEVICE_ID_W25X20_JEDEC:
        case this->DEVICE_ID_W25X40_JEDEC:
        case this->DEVICE_ID_W25X80_JEDEC:
          {
          return true;
          }
        break;
        }
      return false;
      }
  protected:
  private:
  };

class FlashMemoryDriverFlashW25Q80_16_32Class : public FlashMemoryDriverInterface
  {
  public:
    const static uint8_t INSTRUCTION_WRITE_ENABLE      = 0x06;
    const static uint8_t INSTRUCTION_WRITE_DISABLE      = 0x04;
    const static uint8_t INSTRUCTION_READ_STATUS_REGISTER1  = 0x35;
    const static uint8_t INSTRUCTION_READ_STATUS_REGISTER2  = 0x05;
    const static uint8_t INSTRUCTION_WRITE_STATUS_REGISTER  = 0x01;
    const static uint8_t INSTRUCTION_PAGE_PROGRAM      = 0x02;
    const static uint8_t INSTRUCTION_QUAD_PAGE_PROGRAM    = 0x32;
    const static uint8_t INSTRUCTION_BLOCK_ERASE_64K    = 0xd8;
    const static uint8_t INSTRUCTION_BLOCK_ERASE_32K    = 0x52;
    const static uint8_t INSTRUCTION_SECTOR_ERASE_4k    = 0x20;
    const static uint8_t INSTRUCTION_CHIP_ERASE        = 0xc7;//+0x60
    const static uint8_t INSTRUCTION_ERASE_SUSPEND      = 0x75;
    const static uint8_t INSTRUCTION_ERASE_RESUME      = 0x7a;
    const static uint8_t INSTRUCTION_POWER_DOWN        = 0xb9;//+time
    const static uint8_t INSTRUCTION_HIGH_PERFORMANCE_MODE  = 0xa3;
    const static uint8_t INSTRUCTION_MODE_BIT_RESET      = 0xff;
    const static uint8_t INSTRUCTION_RELEASE_PD_HPM__DEVID  = 0xab;//+time
    const static uint8_t INSTRUCTION_MANUFACTURER__DEVID  = 0x90;
    const static uint8_t INSTRUCTION_READ_UNIQUE_ID      = 0x4b;
    const static uint8_t INSTRUCTION_JDEC_ID        = 0x9f;

    const static uint8_t INSTRUCTION_READ_DATA        = 0x03;
    const static uint8_t INSTRUCTION_FAST_READ        = 0x0b;
    const static uint8_t INSTRUCTION_FAST_READ_DUAL_OUTPUT  = 0x3b;
    const static uint8_t INSTRUCTION_FAST_READ_DUAL_IO    = 0xbb;
    const static uint8_t INSTRUCTION_FAST_READ_QUAD_OUTPUT  = 0x6b;
    const static uint8_t INSTRUCTION_FAST_READ_QUAD_IO    = 0xeb;

    const static uint16_t DEVICE_ID_W25Q80_JEDEC      = 0x4014;
    const static uint16_t DEVICE_ID_W25Q16_JEDEC      = 0x4015;
    const static uint16_t DEVICE_ID_W25Q32_JEDEC      = 0x4016;


    AVAILABLE_DRIVERIDS GetDriverID(void)
      {
      return AVAILABLE_DRIVERID_W25Q80_16_32;
      }
    FlashMemoryInstruction InstructionPageProgram(void)
      {
      return INSTRUCTION_PAGE_PROGRAM;
      }
    FlashMemoryInstruction InstructionGetStatusRegister1(void)
      {
      return INSTRUCTION_READ_STATUS_REGISTER1;
      }
    FlashMemoryInstruction InstructionWriteEnable(void)
      {
      return INSTRUCTION_WRITE_ENABLE;
      }
    FlashMemoryInstruction InstructionEraseDevice(void)
      {
      return INSTRUCTION_CHIP_ERASE;
      }
    FlashMemoryInstruction GetReadInstrunction(void)
      {
      return this->INSTRUCTION_READ_DATA;
      }
    FlashMemoryInstruction PowerDownInstruction(void)
      {
      //MediaFlashSPI::Communicate(this->INSTRUCTION_POWER_DOWN);
      return this->INSTRUCTION_POWER_DOWN;
      }
    FlashMemoryInstruction ReleasePowerDownInstruction(void)
      {
      //MediaFlashSPI::Communicate(this->INSTRUCTION_RELEASE_PD_HPM__DEVID);
      return this->INSTRUCTION_RELEASE_PD_HPM__DEVID;
      }
    void ReleasePowerDownDelay(void)
      {
      
      }
    FLASH_MEMORY_CAPACITY GetCapacity(uint16_t JEDECID)
      {
      switch (JEDECID)
        {
        case this->DEVICE_ID_W25Q80_JEDEC:
          {
          return FLASH_MEMORY_CAPACITY::FLASH_MEMORY_CAPACITY_8MBIT;
          }
        break;
        case this->DEVICE_ID_W25Q16_JEDEC:
          {
          return FLASH_MEMORY_CAPACITY::FLASH_MEMORY_CAPACITY_16MBIT;
          }
        break;
        case this->DEVICE_ID_W25Q32_JEDEC:
          {
          return FLASH_MEMORY_CAPACITY::FLASH_MEMORY_CAPACITY_32MBIT;
          }
        break;
        }
      return FLASH_MEMORY_CAPACITY::FLASH_MEMORY_CAPACITY_UNKNOWN;
      }
    bool isContainDevice(uint16_t JEDECID)
      {
      switch (JEDECID)
        {
        case this->DEVICE_ID_W25Q80_JEDEC:
        case this->DEVICE_ID_W25Q16_JEDEC:
        case this->DEVICE_ID_W25Q32_JEDEC:
          {
          return true;
          }
        break;
        }
      return false;
      }
  protected:
  private:
  };
class FlashMemoryDriverFlashM25P05Class : public FlashMemoryDriverInterface
  {
  public:
    const static uint8_t INSTRUCTION_WRITE_ENABLE      = 0x06;
    const static uint8_t INSTRUCTION_WRITE_DISABLE      = 0x04;
    const static uint8_t INSTRUCTION_READ_IDENTIFICATION  = 0x9F;//jedec
    const static uint8_t INSTRUCTION_JDEC_ID        = 0x9F;//does not contain, it calls "RDID"
    const static uint8_t INSTRUCTION_READ_STATUS_REGISTER  = 0x05;
    const static uint8_t INSTRUCTION_WRITE_STATUS_REGISTER  = 0x01;
    const static uint8_t INSTRUCTION_READ_DATA        = 0x03;
    const static uint8_t INSTRUCTION_FAST_READ        = 0x0B;
    const static uint8_t INSTRUCTION_PAGE_PROGRAM      = 0x02;
    const static uint8_t INSTRUCTION_SECTOR_ERASE      = 0xD8;
    const static uint8_t INSTRUCTION_BULK_ERASE        = 0xC7;
    const static uint8_t INSTRUCTION_DEEP_POWER_DOWN    = 0xB9;
    const static uint8_t INSTRUCTION_RELEASE_DPD_HPM__DEVID  = 0xAB;
    
    const static uint16_t DEVICE_ID_M25P05_JEDEC      = 0x2010;
    /*
    const static uint8_t INSTRUCTION_QUAD_PAGE_PROGRAM    = 0x32;
    const static uint8_t INSTRUCTION_BLOCK_ERASE_64K    = 0xd8;
    const static uint8_t INSTRUCTION_BLOCK_ERASE_32K    = 0x52;
    const static uint8_t INSTRUCTION_CHIP_ERASE        = 0xc7;//+0x60
    const static uint8_t INSTRUCTION_ERASE_SUSPEND      = 0x75;
    const static uint8_t INSTRUCTION_ERASE_RESUME      = 0x7a;
    const static uint8_t INSTRUCTION_POWER_DOWN        = 0xb9;//+time
    const static uint8_t INSTRUCTION_HIGH_PERFORMANCE_MODE  = 0xa3;
    const static uint8_t INSTRUCTION_MODE_BIT_RESET      = 0xff;
    const static uint8_t INSTRUCTION_RELEASE_PD_HPM__DEVID  = 0xab;//+time
    const static uint8_t INSTRUCTION_MANUFACTURER__DEVID  = 0x90;
    const static uint8_t INSTRUCTION_READ_UNIQUE_ID      = 0x4b;

    const static uint8_t INSTRUCTION_FAST_READ_DUAL_OUTPUT  = 0x3b;
    const static uint8_t INSTRUCTION_FAST_READ_DUAL_IO    = 0xbb;
    const static uint8_t INSTRUCTION_FAST_READ_QUAD_OUTPUT  = 0x6b;
    const static uint8_t INSTRUCTION_FAST_READ_QUAD_IO    = 0xeb;

    const static uint16_t DEVICE_ID_W25Q80_JEDEC      = 0x4014;
    const static uint16_t DEVICE_ID_W25Q16_JEDEC      = 0x4015;
    const static uint16_t DEVICE_ID_W25Q32_JEDEC      = 0x4016;
    */


    AVAILABLE_DRIVERIDS GetDriverID(void)
      {
      return AVAILABLE_DRIVERID_M25P05;
      }
    FlashMemoryInstruction InstructionPageProgram(void)
      {
      return INSTRUCTION_PAGE_PROGRAM;
      }
    FlashMemoryInstruction InstructionGetStatusRegister1(void)
      {
      return INSTRUCTION_READ_STATUS_REGISTER;
      }
    FlashMemoryInstruction InstructionWriteEnable(void)
      {
      return INSTRUCTION_WRITE_ENABLE;
      }
    FlashMemoryInstruction InstructionEraseDevice(void)
      {
      return INSTRUCTION_BULK_ERASE;
      }
    FlashMemoryInstruction GetReadInstrunction(void)
      {
      return this->INSTRUCTION_READ_DATA;
      }
    FlashMemoryInstruction PowerDownInstruction(void)
      {
      //MediaFlashSPI::Communicate(this->INSTRUCTION_POWER_DOWN);
      return this->INSTRUCTION_DEEP_POWER_DOWN;
      }
    FlashMemoryInstruction ReleasePowerDownInstruction(void)
      {
      //MediaFlashSPI::Communicate(this->INSTRUCTION_RELEASE_PD_HPM__DEVID);
      return this->INSTRUCTION_RELEASE_DPD_HPM__DEVID;
      }
    void ReleasePowerDownDelay(void)
      {
      
      }
    FLASH_MEMORY_CAPACITY GetCapacity(uint16_t JEDECID)
      {
      return FLASH_MEMORY_CAPACITY::FLASH_MEMORY_CAPACITY_256BIT;
      }
    bool isContainDevice(uint16_t JEDECID)
      {
      switch (JEDECID)
        {
        case this->DEVICE_ID_M25P05_JEDEC:
          {
          return true;
          }
        break;
        }
      return false;
      }
  protected:
  private:
  };

/*
template <typename template<uint16_t a> T >
class SPIFlashMemory
  {
  static void test()
    {
    T::Communicate();
    }
  };


//SPIFlashMemory<MediaFlashSPI>::test();
SPIFlashMemory<MediaFlashSPI>::test();
*/

class FlashMemoryDriverContainerClass
  {
  public:
    enum FLASH_MEMORY_MENUFACTURERS
      {
      FLASH_MEMORY_MANUFACTURER_UNKNOWN        = 0x00,
      FLASH_MEMORY_MANUFACTURER_WINBOND        = 0xEF,
      FLASH_MEMORY_MANUFACTURER_NUMONYX        = 0x20,
      };
    
    FlashMemoryDriverInterface* GetDriver(AVAILABLE_DRIVERIDS drv)
      {
      switch (drv)
        {
        case AVAILABLE_DRIVERIDS::AVAILABLE_DRIVERID_GENERIC:
          {
          return &this->FlashMemoryDriverFlashGeneric;
          }
        break;
        
        case AVAILABLE_DRIVERIDS::AVAILABLE_DRIVERID_M25P05:
          {
          return &this->FlashMemoryDriverFlashM25P05;
          }
        break;
        
        case AVAILABLE_DRIVERIDS::AVAILABLE_DRIVERID_W25Q80_16_32:
          {
          return &this->FlashMemoryDriverFlashW25Q80_16_32;
          }
        break;
        
        case AVAILABLE_DRIVERIDS::AVAILABLE_DRIVERID_W25X10_20_40_80:
          {
          return &this->FlashMemoryDriverFlashW25X10_20_40_80;
          }
        break;
        
        case AVAILABLE_DRIVERIDS::AVAILABLE_DRIVERID_UNKNOWN:
        default:
          {
          //this->SelectedDriver  = &this->FlashMemoryDriverUnknown;
          }
        break;
        }
      return &this->FlashMemoryDriverUnknown;
      }
    void SelectDriver(AVAILABLE_DRIVERIDS drv)
      {
      this->SelectedDriver  = this->GetDriver(drv);
      }
    void ResetSelectedDriver(void)
      {
      this->SelectDriver (AVAILABLE_DRIVERIDS::AVAILABLE_DRIVERID_UNKNOWN);
      }
    FlashMemoryDriverInterface* GetSelectedDriver(void)
      {
      return this->SelectedDriver;
      }
    bool SelectDriverForJEDEC(uint8_t manufacturer, uint16_t jedec_device)
      {
      switch (manufacturer)
        {
        case FLASH_MEMORY_MANUFACTURER_WINBOND:
          {
          if (this->FlashMemoryDriverFlashW25Q80_16_32.isContainDevice(jedec_device))
          //if (this->GetDriver(FlashMemoryDriverContainerClass::AVAILABLE_DRIVERS::AVAILABLE_DRIVER_W25Q80_16_32)->isContainDevice(jedec_device))
            {
            //this->FMDC->SelectedDriver  = &this->FMDC->FlashMemoryDriverFlashW25Q80_16_32;
            this->SelectDriver(AVAILABLE_DRIVERIDS::AVAILABLE_DRIVERID_W25Q80_16_32);
            //this->SelectedDriver  = &this->MediaMemoryDriverFlashW25X10_20_40_80;
            return true;
            }
          else if (this->FlashMemoryDriverFlashW25X10_20_40_80.isContainDevice(jedec_device))
          //else if (this->GetDriver(FlashMemoryDriverContainerClass::AVAILABLE_DRIVERS::AVAILABLE_DRIVER_W25X10_20_40_80)->isContainDevice(jedec_device))
            {
            //this->FMDC->SelectedDriver  = &this->FMDC->FlashMemoryDriverFlashW25X10_20_40_80;
            this->SelectDriver(AVAILABLE_DRIVERIDS::AVAILABLE_DRIVERID_W25X10_20_40_80);
            return true;
            }
          }
        break;

        case FLASH_MEMORY_MANUFACTURER_NUMONYX:
          {
          if (this->FlashMemoryDriverFlashM25P05.isContainDevice(jedec_device))
            {
            //this->SelectedDriver  = &this->FlashMemoryDriverFlashM25P05;
            this->SelectDriver(AVAILABLE_DRIVERIDS::AVAILABLE_DRIVERID_M25P05);
            return true;
            }
          }
        break;
        
        case FLASH_MEMORY_MANUFACTURER_UNKNOWN:
        default:
          {
          //TODO
          }
        break;
        }
      //nothing found BUT...
      //NUMONYX M25P05 can be WITHOUT JEDEC
      //it reports 0x05 after RES instrunction and 3dummy bytes
      return false;
      }
  protected:
  private:
    FlashMemoryDriverFlashUnknown FlashMemoryDriverUnknown;
    FlashMemoryDriverFlashW25X10_20_40_80Class FlashMemoryDriverFlashW25X10_20_40_80;
    FlashMemoryDriverFlashW25Q80_16_32Class FlashMemoryDriverFlashW25Q80_16_32;
    FlashMemoryDriverFlashGenericClass FlashMemoryDriverFlashGeneric;
    FlashMemoryDriverFlashM25P05Class FlashMemoryDriverFlashM25P05;
    FlashMemoryDriverInterface* SelectedDriver  = &FlashMemoryDriverUnknown;
  };
//extern FlashMemoryDriverContainer;
FlashMemoryDriverContainerClass FlashMemoryDriverContainer;


template <class SPIDevice>
class FlashMemoryClass : public SleepModeInterface, public ArtefactHardwareInterface
  {
  public:
    /*enum MEDIA_MEMORY_TYPE
      {
      MEDIA_MEMORY_TYPE_UNKNOWN,
      MEDIA_MEMORY_TYPE_W25X10_20_40_80,
      MEDIA_MEMORY_TYPE_W25Q80_16_32,
      MEDIA_MEMORY_TYPE_NUM
      };*/
    const static uint8_t INSTRUCTION_RELEASE_PD     = 0xab;
    const static uint8_t INSTRUCTION_JEDEC_ID       = 0x9f;
    const static uint8_t INSTRUCTION_JEDEC_LENGTH   = 3;
    const static uint8_t JEDECID_MANUFACTURER       = 0;
    const static uint8_t JEDECID_MEMORY_TYPE        = 1;
    const static uint8_t JEDECID_CAPACITY           = 2;

    void EnterSleepMode(void);
    void EnterNormalMode(void);
    void ReadJEDEC(void);//TODO: HACK!!!
    bool isJEDECReaded(void);
    uint8_t GetManufacturerID(void);
    uint8_t* GetCachedJDEC(void);
    FLASH_MEMORY_CAPACITY GetCapacity(void);
    void ReadJEDECIfNeed(void);
    FlashMemoryDriverInterface* GetDriver(void);
    FlashMemoryClass(void);


    void ReadData(uint8_t* data, uint8_t dataLength);
    void ReadData(uint8_t AddressH, uint8_t AddressM, uint8_t AddressL, uint8_t* data, uint8_t dataLength);
    void ReadData(uint8_t* data, uint16_t dataLength);
    void ReadData(uint8_t AddressH, uint8_t AddressM, uint8_t AddressL, uint8_t* data, uint16_t dataLength);
    void EraseDevice(void);
    uint8_t ReadStatusRegister1(void);
    void WriteData(uint8_t* data, uint8_t dataLength);
    void WriteData(uint8_t AddressH, uint8_t AddressM, uint8_t AddressL, uint8_t* data, uint8_t dataLength);
    void WriteData(uint8_t* data, uint16_t dataLength);
    void WriteData(uint8_t AddressH, uint8_t AddressM, uint8_t AddressL, uint8_t* data, uint16_t dataLength);
    void IOInit(void);
    /*FLASH_DEVICE GetDevice(void)
      {
      this->ReadJEDECIfNeed();
      switch (this->jedec[])
      }*/
  protected:
  private:
    uint8_t jedecArray[INSTRUCTION_JEDEC_LENGTH];
    uint16_t jedec_device=0;//use it like &jedec[1]???
    /*
    //MediaMemoryDriverInterface Drivers[MEDIA_MEMORY_TYPE_NUM];
    FlashMemoryDriverFlashUnknown FlashMemoryDriverUnknown;
    FlashMemoryDriverFlashW25X10_20_40_80Class FlashMemoryDriverFlashW25X10_20_40_80;
    FlashMemoryDriverFlashW25Q80_16_32Class FlashMemoryDriverFlashW25Q80_16_32;
    FlashMemoryDriverFlashGenericClass FlashMemoryDriverFlashGeneric;
    FlashMemoryDriverFlashM25P05Class FlashMemoryDriverFlashM25P05;
    FlashMemoryDriverInterface* SelectedDriver  = &FlashMemoryDriverUnknown;
//    MEDIA_MEMORY_TYPE selectedDriver=MEDIA_MEMORY_TYPE_UNKNOWN;
    */
    FlashMemoryDriverContainerClass* FMDC  = &FlashMemoryDriverContainer;
  };



#endif /* MEDIAMEMORYCLASS_H_ */
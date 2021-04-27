/*
 * CopySounds.h
 *
 * Created: 12.05.2018 21:48:55
 *  Author: tabr
 */ 


#ifndef COPYSOUNDS_H_
#define COPYSOUNDS_H_

#include "strings.h"
void copySounds(void)
  {


    RFM69ClkPin::SetDirOut();
    RFM69ClkPin::SetOutHigh();
    
    RFM69MisoPin::SetDirIn();

    RFM69MosiPin::SetDirOut();
    RFM69MosiPin::SetOutHigh();
    RFM69SSPin::SetDirOut();
    RFM69SSPin::SetOutHigh();
    
    RFM69Dio5Pin::SetDirIn();
    

    //PORTC.DIRSET    = 1<<4;
    RFM69SPI_SS_Pin::SetDirOut();
    //  RFM69SPI_SS_Pin::SetOutHigh();
    //            [double CLK]  [enable][DORD] [master][transfer mode][clk prescaller]
    RFM69_SPI.CTRL    = 1<<7      | 1<<6  | 0<<5 | 1<<4 | (0<<3 | 0<<2) | (0<<1 | 0<<0);
    //  RFM69_SPI.CTRL  = 0<<7      | 1<<6  | 0<<5 | 1<<4 | (0<<3 | 0<<2) | (1<<1 | 1<<0);
    RFM69_SPI.INTCTRL = SPI_INTLVL_OFF_gc ; // no interrupt


  LcdStringUpdate(1,LCD_LINE_1, (char*)"Copying data  ");
//copy SIDS to MediaFlash
//  static bool IsWritten = false;
  //UNION_UINT32_LITTLE_ENDIAN flash_num_address;
  //UNION_UINT32_LITTLE_ENDIAN flash_data_address;
  //UNION_UINT32_LITTLE_ENDIAN flash_ptr_address;
  uint32_t wrt_counter=0;
//  if (IsWritten == false)
//{
//  IsWritten = true;
  LcdStringUpdate(1,LCD_LINE_2, (char*)"Erasing...    ");
  MediaMemory.EraseDevice();
  LcdStringUpdate(1,LCD_LINE_3, (char*)"Erase Complete");

//  _delay_ms(10000);

  LcdEmptyString(LCD_LINE_3);
  LcdStringUpdate(1,LCD_LINE_2, (char*)"Checking erase");

  uint8_t cache[64];
  char buf[25];
  #warning "[T] add support 32mbit!"
  if (MediaMemory.GetCapacity() == FLASH_MEMORY_CAPACITY::FLASH_MEMORY_CAPACITY_8MBIT /* || MediaMemory.GetCapacity() == FLASH_MEMORY_CAPACITY::FLASH_MEMORY_CAPACITY_32MBIT*/)
    {
    #define CAPACITY_BYTES    (((uint32_t)1024*1024*8)/8)
    #define BLOCKS_TO_PROCESS (CAPACITY_BYTES/8)

//    MediaMemory.EraseDevice()

//    uint8_t test=0;
    for (uint32_t i=BLOCKS_TO_PROCESS;i>0;i--)
      {
      MediaMemory.ReadData((uint8_t)0,(uint8_t)0,(uint8_t)0,cache,(uint8_t)8);
      for (uint8_t z=0;z<8;z++)
        {
        if (cache[z] != 0xFF)
          {
//          UNION_UINT32_LITTLE_ENDIAN conv;
//          conv.value_int  = i;
          LcdStringUpdate(1,LCD_LINE_3, (char*)"Erase chk fail");
//          sprintf(buf, "%u",cache[z]);
          sprintf(Lcd.lcd_buf, "%05lu: %u", i, cache[z]);
//          sprintf(buf, "%03d%03d %03d%03d", conv.byte_field.h, conv.byte_field.mh, conv.byte_field.ml, conv.byte_field.l);
          LcdStringUpdate(1,LCD_LINE_4, buf);
          sprintf(buf, "%03d %03d %03d", z, cache[z], MediaMemory.GetManufacturerID());
          LcdStringUpdate(1,LCD_LINE_5, buf);
          while(1);
          }
        }
      }
    }
  else
    {
    LcdStringUpdate(1,LCD_LINE_4, (char*)"ERROR");
    LcdStringUpdate(1,LCD_LINE_5, (char*)"supp only 1MB");
    while(1);
    }
  LcdStringUpdate(1,LCD_LINE_3, (char*)"Erase chk ok  ");

  //sprintf(Lcd.lcd_buf, "%03u", MemoryManager.getAvailableBytes());;
  //LcdStringUpdate(1,LCD_LINE_4, Lcd.lcd_buf);
  _delay_ms(100);
/*
  uint8_t byte        = 0;
  //uint8_t SelecedSID  = Sound::SIDS::SID_RADIOATION4;
  uint32_t addressData          = 0;
  flash_data_address.value_int  = MediaFlashClass::MEDIAFLASH_ADDRESS_DATA_START;//first
//<= init data

  LcdStringUpdate(1,LCD_LINE_2, (char*)"wrt num of snd");
  LcdStringUpdate(1,LCD_LINE_3, (char*)"processing... ");
  flash_num_address.value_int   = MediaFlashClass::MEDIAFLASH_ADDRESS_NUM_OF_SOUNDS;//write to [num of sounds]
  byte                          = Sound::SIDS::SIDS_NUM;
  MediaMemory.WriteData(flash_num_address.byte_field.mh, flash_num_address.byte_field.ml, flash_num_address.byte_field.l, &byte, (uint16_t)1);
  _delay_ms(3);//Page Program time (max)
  LcdStringUpdate(1,LCD_LINE_3, (char*)"wrt complete  ");
  
  LcdStringUpdate(1,LCD_LINE_3, (char*)"checking...   ");
  MediaMemory.ReadData(flash_num_address.byte_field.mh, flash_num_address.byte_field.ml, flash_num_address.byte_field.l,cache,(uint16_t)1);
  if (cache[0] != byte)
    {
    LcdStringUpdate(1,LCD_LINE_3, (char*)"1check failed!");
    while(1);
    }
*/
//<= post init write
//  flash_data_address.value_int  += 4096;//first
struct wrt_struct
  {
  const uint8_t* data_ptr;
  uint16_t size;
  char* filename;
  };
wrt_struct data_to_read[]=
  {
  {SoundNone,           sizeof(SoundNone),            (char*)"none.wav"},           //1
  {Sound_geiger_1,      sizeof(Sound_geiger_1),       (char*)"radiation.wav"},      //2
  {Sound_geiger_4,      sizeof(Sound_geiger_4),       (char*)"radiation4.wav"},     //3
  {Sound_pda_news,      sizeof(Sound_pda_news),       (char*)"pda_news.wav"},       //4
  {Sound_da_2_beep1,    sizeof(Sound_da_2_beep1),     (char*)"anomaly_beep.wav"},   //5
  {Sound_pain_1,        sizeof(Sound_pain_1),         (char*)"hit_1.wav"},          //6
  {Sound_pain_7,        sizeof(Sound_pain_7),         (char*)"hit_2.wav"},          //7
  {Sound_hit_5,         sizeof(Sound_hit_5),          (char*)"hit_3.wav"},          //8
  {Sound_hit_6,         sizeof(Sound_hit_6),          (char*)"hit_4.wav"},          //9
  {Sound_hurt3,         sizeof(Sound_hurt3),          (char*)"hit_5.wav"},          //10
  {Sound_blowout_hit_2, sizeof(Sound_blowout_hit_2),  (char*)"blowout_hit.wav"},    //11
  {img_4cols,           sizeof(img_4cols),            (char*)"img_4cols.hex"},      //12
  {img_lowbat,          sizeof(img_lowbat),           (char*)"img_lowbat.hex"},     //13
  {img_pboy,            sizeof(img_pboy),             (char*)"img_pboy.hex"},       //14
  {img_skull,           sizeof(img_skull),            (char*)"img_skull.hex"},      //15
  {img_zombie,          sizeof(img_zombie),           (char*)"img_zombie.hex"},     //16
  {test1,               sizeof(test1),                (char*)"12345678901234"},     //17
  {test2,               sizeof(test2),                (char*)"123456789012345"},    //18
  {test3,               sizeof(test3),                (char*)"1234567890123456"},   //19
  {test4,               sizeof(test4),                (char*)"12345678901234567"},  //20
  {test5,               sizeof(test5),                (char*)"test5.hex"},          //21
  {test6,               sizeof(test6),                (char*)"test6.hex"},          //22
  {test1,               sizeof(test1),                (char*)"test1_1.hex"},        //23
  {(const uint8_t*)pos_array,           STRClass::STORAGE_DATA_WIDTH*array_length(pos_array),         (char*)"lang.rus"},            //24
  {radio_waves_3,       sizeof(radio_waves_3),        (char*)"radio_waves_3.hex"},  //25
  {radio_waves_2,       sizeof(radio_waves_2),        (char*)"radio_waves_2.hex"},  //26
  {radio_waves_1,       sizeof(radio_waves_1),        (char*)"radio_waves_1.hex"},  //27
  {radio_waves_0,       sizeof(radio_waves_0),        (char*)"radio_waves_0.hex"},  //28
  {sound_pik,           sizeof(sound_pik),            (char*)"sound_pik.wav"},      //29
  };





  LcdString(1,LCD_LINE_2, (char*)"wrt data      ");
  LcdStringUpdate(1,LCD_LINE_3, (char*)"processing... ");
  //const uint8_t* selected_sound_ptr         = sounds[0];
  //sprintf(Lcd.lcd_buf, "%05d %05d", sound_size[0], sizeof(SoundNone));
  //LcdStringUpdate(1,LCD_LINE_4, Lcd.lcd_buf);
  for (uint8_t FID=0;FID<array_length(data_to_read);FID++)
    {
    LcdStringUpdate(1,LCD_LINE_3, (char*)"processing1... ");
    TFS_FAT_FilePos_t pos = TFS.WriteNewFile(data_to_read[FID].filename, 0, NULL, data_to_read[FID].size);
    _delay_ms(100);
    LcdStringUpdate(1,LCD_LINE_3, (char*)"processing2... ");
    TFSFileClass file;
    LcdStringUpdate(1,LCD_LINE_3, (char*)"processing3... ");
    file.SeekByPosition(pos);
    sprintf (buf, "%03u",file.IsParameterSet(TFS_STRUCTURE_FILE_PARAMETER_FILE_NOT_EMPTY));
    LcdString(1,LCD_LINE_3, buf);
    sprintf (buf, "%03u %03u %01u",FID, pos, file.IsEmpty());
    LcdString(1,LCD_LINE_4, buf);
    sprintf (buf, "%s %03u",file.GetName(), file.GetSizeBytes());
    LcdStringUpdate(1,LCD_LINE_5, buf);
    _delay_ms(10);

    
    const uint8_t* selected_sound_ptr         = data_to_read[FID].data_ptr;
    wrt_counter=0;
    while (1)
      {
      if (selected_sound_ptr == (const uint8_t*)pos_array) //ru.lang
        {
        for (uint8_t i=0;i<STRPOS_SIZE;i++)
          {
          memset(cache, 0, STRClass::STORAGE_DATA_WIDTH);
          STRClass str(static_cast<STR_POS>(i));
          str.WritePgmTo((char*)cache);
          file.WriteData(cache, STRClass::STORAGE_DATA_WIDTH);
          _delay_ms(3);
          sprintf(buf, "%02u: %05u", FID, i);
          LcdStringUpdate(1,LCD_LINE_4, buf);
          //_delay_ms(250);
          }
        break;
        }
      else
        {
        for (uint8_t i=0;i<sizeof(cache);i++)
          {
          cache[i]=pgm_read_byte(selected_sound_ptr);
          selected_sound_ptr++;
          }
        TFS_FAT_SizeBytes_t length  = sizeof(cache);
        if (length != file.WriteData(cache, length))
          {
          break;
          }
        _delay_ms(3);
        sprintf(buf, "%02u: %05lu", FID, wrt_counter);
        LcdStringUpdate(1,LCD_LINE_4, buf);
        wrt_counter+=length;
        }
      }
  
    }
  LcdStringUpdate(1,LCD_LINE_6, (char*)"SNDcompleted");


    //uint8_t data2[32]={0,0,0,0,0,0,0,0,0,0,0};
    //  bool result = TFS.WriteNewFile(fname, 0, data, sizeof(data));
    //MediaMemory.WriteData(0,0,0,data, (uint16_t)8);
    //  _delay_ms(100);
    //uint8_t i=0;
    TFSFileClass file;
    TFS_FAT_FilePos_t numReaded = 0;
    //UNION_UINT32_LITTLE_ENDIAN file_addr;
    //file_addr.value_int = 8192;
    //file.SeekByPosition(2);

    LcdClearCache();

    file.SeekByPosition(24);//ru.lang
    numReaded = file.ReadData(cache,16);

    //sprintf (Lcd.lcd_buf, "%03u", 123);
    //LcdString(LCD_LINE_1);

//    sprintf (Lcd.lcd_buf, "%03u%03u %03u%03u", cache[0], cache[1], cache[2], cache[3]);
    sprintf (Lcd.lcd_buf, "%s", cache);
    LcdString(LCD_LINE_2);
    sprintf (Lcd.lcd_buf, "readed: %03u", numReaded);
    LcdString(LCD_LINE_3);

    file.SeekByPosition(29);//
    numReaded = file.ReadData(cache,16);
    sprintf (Lcd.lcd_buf, "%03u%03u %03u%03u", cache[0], cache[1], cache[2], cache[3]);
    LcdString(LCD_LINE_4);
    sprintf (Lcd.lcd_buf, "readed: %03u", numReaded);
    LcdString(LCD_LINE_5);

    LcdStringUpdate(1, LCD_LINE_6, (char*)"Done");

    while(1)
      {

      }
    /*
    while(1)
    {
      file.SeekByPosition(i);
      //TFS.ReadFileHeadInPosition(1, data2);
      //MediaMemory.ReadData(0,0,32, data2, (uint16_t)32);
      //MediaMemory.ReadData(file_addr.byte_field.mh, file_addr.byte_field.ml, file_addr.byte_field.l, data2, (uint16_t)32);

      //sprintf (Lcd.lcd_buf, "%03u %01u %03u",++i, result, file.ReadData(data2,2));
      sprintf (Lcd.lcd_buf, "%03u %03u",++i, file.ReadData(data2,2));
      //sprintf (Lcd.lcd_buf, "%03u %01u %03u",++i, result, file.WriteData(&data[3],2));
      LcdString(LCD_LINE_1);
      //sprintf (Lcd.lcd_buf, "%03u%03u %03u%03u",data2[0], data2[1], data2[2], data2[3]);
      //TFS.
      //sprintf (Lcd.lcd_buf, "%03u%03u %03u%03u",data2[0]);
      //    sprintf (Lcd.lcd_buf, "%s %03u",file.GetName(), file.GetStartClusterAddr());
      LcdEmptyString(LCD_LINE_2);
      sprintf (Lcd.lcd_buf, "%s ",file.GetName());
      LcdString(LCD_LINE_2);
      sprintf (Lcd.lcd_buf, "%05u bytes", file.GetSizeBytes());
      LcdString(LCD_LINE_3);

      //sprintf (buf, "%03u %03u",file.IsParameterSet(TFS_STRUCTURE_FILE_PARAMETER_FILE_NOT_EMPTY), file.GetStructValue<TFS_FAT_NotEmptyParameter_t>(TFS_STRUCTURE_FAT_EMPTY_BYTE));
//      LcdString(1,LCD_LINE_3, buf);

      sprintf (Lcd.lcd_buf, "%03u%03u %03u%03u",data2[0], data2[1], data2[2], data2[3]);
      LcdStringUpdate(1,LCD_LINE_6, Lcd.lcd_buf);
      _delay_ms(2000);
      if (i > array_length(data_to_read))
        {
        i = 0;
        }
    }
    */


}


#endif /* COPYSOUNDS_H_ */
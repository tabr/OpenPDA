// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * TFSClass.cpp
 *
 * Created: 06.05.2018 19:27:09
 *  Author: tabr
 */ 
#warning "[TODO] Add TFS_IO Class to write any HW"
#warning "[TODO] acces to TFS files by names!"











TFS_FAT_FilePos_t TFSClass::GetFilePosition(char* name, TFS_FAT_FilePos_t parent_cat)
  {
  TFSFileClass file;
  //LcdStringUpdate(1,LCD_LINE_3, (char*)"processing_4_0... ");
  for (TFS_FAT_FilePos_t i=FIRST_FILEID;i<=MAX_FILEID;i++)
    {
    //LcdStringUpdate(1,LCD_LINE_3, (char*)"processing_4_1... ");
    //this->ReadFileHeadInPosition(i, file.file);
    file.SeekByPosition(i);
    //LcdStringUpdate(1,LCD_LINE_3, (char*)"processing_4_2... ");
    /*if (file.IsEmpty())
      {
      continue;
      }
    LcdStringUpdate(1,LCD_LINE_3, (char*)"processing_4_3... ");
    */
    if (file.IsNotEmpty())
    {
    if (file.IsInsideCatalogue(parent_cat))
      {
      if (strcmp(name, file.GetName()) == 0)
        {
        return i;
        }
      }
    }
    if (i == MAX_FILEID)
      {
      break;
      }
    }
  return 0;//0 is "system" and mean error
  }
bool TFSClass::IsFileExists(char* name, TFS_FAT_FilePos_t parent_cat)
  {
  return (this->GetFilePosition(name, parent_cat) != 0);
  }
TFS_FAT_FilePos_t TFSClass::GetFirstEmptyFilePosition(void)
  {
  TFSFileClass file;
  for (TFS_FAT_FilePos_t i=FIRST_FILEID;i<=MAX_FILEID;i++)
    {
    //this->ReadFileHeadInPosition(i, file.file);
    file.SeekByPosition(i);
    if (file.IsEmpty())
      {
      return i;
      }
    if (i == MAX_FILEID)
      {
      break;
      }
    }
  return 0;
  }
TFS_FAT_FilePos_t TFSClass::WriteNewFile(char* name, TFS_FAT_FilePos_t parent_cat, uint8_t* data, TFS_FAT_SizeBytes_t size_bytes)
  {
  TFSFileClass file;
  TFS_FAT_FilePos_t foundEmptyFilePos;

  //LcdStringUpdate(1,LCD_LINE_3, (char*)"processing_2_0... ");
  if (this->IsFileExists(name, parent_cat))
    {
    return false;
    }
  //LcdStringUpdate(1,LCD_LINE_3, (char*)"processing_2_1... ");
  foundEmptyFilePos  = this->GetFirstEmptyFilePosition();
  if (foundEmptyFilePos == 0)
    {
    return false;
    }

  //LcdStringUpdate(1,LCD_LINE_3, (char*)"processing_2_2... ");
  file.SeekByPosition(foundEmptyFilePos);
  //LcdStringUpdate(1,LCD_LINE_3, (char*)"processing_2_3... ");
  if (file.IsEmpty())
    {
  //LcdStringUpdate(1,LCD_LINE_3, (char*)"processing_2_4... ");
    file.SetName(name);
  //LcdStringUpdate(1,LCD_LINE_3, (char*)"processing_2_5... ");
    file.SetParent(parent_cat);
  //LcdStringUpdate(1,LCD_LINE_3, (char*)"processing_2_6... ");
    file.SetNotEmpty();
  //LcdStringUpdate(1,LCD_LINE_3, (char*)"processing_2_7... ");
    file.SetFileSizeBytes(size_bytes);
  //LcdStringUpdate(1,LCD_LINE_3, (char*)"processing_2_8... ");
    file.SetStartClusterAddr(this->GetFirstEmptyClusterAddr());//TODO add checks
  //LcdStringUpdate(1,LCD_LINE_3, (char*)"processing_2_9... ");
    file.SetPosition(foundEmptyFilePos);

    //write head
    //file_addr.value_int = i * TFS_STRUCTURE_FAT_HEAD_SIZE_BYTES;
    //MediaMemory.WriteData(file_addr.byte_field.mh, file_addr.byte_field.ml, file_addr.byte_field.l, file.file, (uint16_t)TFS_STRUCTURE_FAT_HEAD_SIZE_BYTES);
    file.WriteHead();
    if (data != NULL)
      {
      file.WriteData(data, size_bytes);
      }
    
    //write body
    //file_addr.value_int = this->GetFirstEmptyClusterAddr()*TFS_CLUSTER_SIZE;
    //MediaMemory.WriteData(file_addr.byte_field.mh, file_addr.byte_field.ml, file_addr.byte_field.l, data, size_bytes);
    return foundEmptyFilePos;
    }
  return 0;
  }
TFS_FAT_ClusterAddr_t TFSClass::GetFirstEmptyClusterAddr(void)
  {
  TFS_FAT_ClusterAddr_t addr=(FS_STRUCTURE_ADDR_DATA_STARTS/TFS_CLUSTER_SIZE);//address of 1st file
  TFSFileClass file;
  for (TFS_FAT_FilePos_t i=FIRST_FILEID;i<=MAX_FILEID;i++)
    {
    //this->ReadFileHeadInPosition(i, file.file);
//  LcdStringUpdate(1,LCD_LINE_3, (char*)"processing_3_1... ");
    file.SeekByPosition(i);
/*
  LcdStringUpdate(1,LCD_LINE_3, (char*)"processing_3_2... ");
  char a[14];
  sprintf(a,"%03u",i);
  _delay_ms(250);
  LcdStringUpdate(1,LCD_LINE_4, a);
    if (file.IsEmpty())
      {
      continue;
      }
    _delay_ms(1000);
*/
    if (file.IsNotEmpty())
      {
//      LcdStringUpdate(1,LCD_LINE_3, (char*)"processing_3_3... ");
      TFS_FAT_ClusterAddr_t after_file_addr=file.GetLastClusterAddr();//we don't need +1 because SIZE mean +1 =)
      if (after_file_addr > addr)
        {
        addr  = after_file_addr;
        }
      }
    if (i == MAX_FILEID)
      {
      break;
      }
    }//for
//    _delay_ms(1000);
  return addr;
  }
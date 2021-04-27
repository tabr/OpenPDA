/*
 * TFSFileClass.cpp
 *
 * Created: 22.12.2019 19:49:29
 *  Author: MateshkoAV
 */ 
void TFSFileClass::WriteHead(void)
  {
  uint32_t addr	= this->GetPosition() * TFS_STRUCTURE_FAT_HEAD_SIZE_BYTES;
  TFS_IOWriter::WriteData(addr, file, (uint16_t)TFS_STRUCTURE_FAT_HEAD_SIZE_BYTES);
  /*
  UNION_UINT32 file_addr;
  //file_addr.value_int = this->GetStartClusterAddr()*TFS_CLUSTER_SIZE;
  file_addr.value_int = this->GetPosition() * TFS_STRUCTURE_FAT_HEAD_SIZE_BYTES;
  cli();
  MediaMemory.WriteData(file_addr.byte_field.mh, file_addr.byte_field.ml, file_addr.byte_field.l, this->file, (uint16_t)TFS_STRUCTURE_FAT_HEAD_SIZE_BYTES);
  sei();
  */
  }
void TFSFileClass::ResetInternalPointer(void)
  {
  this->SetInternalPointer(0);
  }
void TFSFileClass::SetInternalPointer(TFS_FAT_SizeBytes_t addr)
  {
  if (addr > this->GetSizeBytes())
    {
    this->internalDataPointer = this->GetSizeBytes();
    }
  else
    {
    this->internalDataPointer = addr;
    }
  }
TFS_FAT_SizeBytes_t TFSFileClass::WriteData(uint8_t* data, TFS_FAT_SizeBytes_t length)
  {
  if (length > this->GetSizeBytes() - this->internalDataPointer)
    {
    length  = this->GetSizeBytes() - this->internalDataPointer;
    }
  if (length > 0)
    {
	uint32_t addr	= ((uint32_t)this->GetStartClusterAddr())*TFS_CLUSTER_SIZE + this->internalDataPointer;
	TFS_IOWriter::WriteData(addr, data, length);
	/*
    UNION_UINT32 file_addr;
    file_addr.value_int = ((uint32_t)this->GetStartClusterAddr())*TFS_CLUSTER_SIZE + this->internalDataPointer;
    cli();
    MediaMemory.WriteData(file_addr.byte_field.mh, file_addr.byte_field.ml, file_addr.byte_field.l, data, length);
    sei();
	*/
    }
  this->internalDataPointer+= length;
  return length;
  }

TFS_FAT_SizeBytes_t TFSFileClass::ReadData(uint8_t* data, TFS_FAT_SizeBytes_t length)
  {
  if (length > this->GetSizeBytes() - this->internalDataPointer)
    {
    length  = this->GetSizeBytes() - this->internalDataPointer;
    }
  if (length > 0)
    {
	uint32_t addr	= ((uint32_t)this->GetStartClusterAddr())*TFS_CLUSTER_SIZE + this->internalDataPointer;
	TFS_IOWriter::ReadData(addr, data, length);
	/*
    UNION_UINT32 file_addr;
    file_addr.value_int = ((uint32_t)this->GetStartClusterAddr())*TFS_CLUSTER_SIZE + this->internalDataPointer;
    cli();
    MediaMemory.ReadData(file_addr.byte_field.mh, file_addr.byte_field.ml, file_addr.byte_field.l, data, length);
    sei();
	*/
    }
  this->internalDataPointer+= length;
  return length;
  }

void TFSFileClass::SeekByPosition(TFS_FAT_FilePos_t value)
  {
  this->ResetInternalPointer();
  uint32_t addr	= (value * TFS_STRUCTURE_FAT_HEAD_SIZE_BYTES) + TFS_STRUCTURE_FAT_STARTS;
  TFS_IOWriter::ReadData(addr, this->file, (uint16_t)TFS_STRUCTURE_FAT_HEAD_SIZE_BYTES);
  
  /*
  UNION_UINT32 file_addr;
  file_addr.value_int = (value * TFS_STRUCTURE_FAT_HEAD_SIZE_BYTES) + TFS_STRUCTURE_FAT_STARTS;
  cli();
  MediaMemory.ReadData(file_addr.byte_field.mh, file_addr.byte_field.ml, file_addr.byte_field.l, this->file, (uint16_t)TFS_STRUCTURE_FAT_HEAD_SIZE_BYTES);\
  sei();
  */
  }

TFSFileClass::TFSFileClass(void)
  {
  memset(this->file, 0, sizeof(this->file));
  }
TFS_FAT_FilePos_t TFSFileClass::GetPosition(void)
  {
  return this->GetStructValue<TFS_FAT_FilePos_t>(TFS_STRUCTURE_FAT_POSITION);
  }
void TFSFileClass::SetPosition(TFS_FAT_FilePos_t value)
  {
  this->SetStructValue<TFS_FAT_FilePos_t>(TFS_STRUCTURE_FAT_POSITION, value);
  }
void TFSFileClass::SetParameter(TFS_STRUCTURE_FILE_PARAMETERS parameter)
  {
  TFS_FAT_FileParameters_t current_parameters = this->GetStructValue<TFS_FAT_FileParameters_t>(TFS_STRUCTURE_FAT_FILE_PARAMETERS);
  sbi(current_parameters, parameter);
  this->SetStructValue<TFS_FAT_FileParameters_t>(TFS_STRUCTURE_FAT_FILE_PARAMETERS, current_parameters);
  }
void TFSFileClass::ClearParameter(TFS_STRUCTURE_FILE_PARAMETERS parameter)
  {
  TFS_FAT_FileParameters_t current_parameters = this->GetStructValue<TFS_FAT_FileParameters_t>(TFS_STRUCTURE_FAT_FILE_PARAMETERS);
  cbi(current_parameters, parameter);
  this->SetStructValue<TFS_FAT_FileParameters_t>(TFS_STRUCTURE_FAT_FILE_PARAMETERS, current_parameters);
  }
bool TFSFileClass::IsParameterSet(TFS_STRUCTURE_FILE_PARAMETERS parameter)
  {
  return isBitSet(this->GetStructValue<TFS_FAT_FileParameters_t>(TFS_STRUCTURE_FAT_FILE_PARAMETERS), parameter);
  }
char* TFSFileClass::GetName(void)
  {
  return this->GetStructAddr<char>(TFS_STRUCTURE_FAT_FILENAME);
  }
void TFSFileClass::SetName(char* name)
  {
  #define LAST_CHAR_POS   (TFS_STRUCTURE_FAT_FILENAME + TFS_FILENAME_LENGTH - 1)
  memset(this->GetStructAddr<char>(TFS_STRUCTURE_FAT_FILENAME), 0, TFS_FILENAME_LENGTH);
  if (strlen(name) > TFS_FILENAME_LENGTH)
    {
    memcpy(this->GetStructAddr<char>(TFS_STRUCTURE_FAT_FILENAME), name, TFS_FILENAME_LENGTH);
    this->SetStructValue<uint8_t>(static_cast<TFS_STRUCTURE_FAT>(LAST_CHAR_POS), 0);
    }
  else
    {
    strcpy(this->GetStructAddr<char>(TFS_STRUCTURE_FAT_FILENAME), name);
    }
  this->SetStructValue<uint8_t>(TFS_STRUCTURE_FAT_EMPTY_BYTE, 0);
  
  }
TFS_FAT_Parent_t TFSFileClass::GetParent(void)
  {
  return this->GetStructValue<TFS_FAT_Parent_t>(TFS_STRUCTURE_FAT_PARENT_CAT);
  }
TFS_FAT_ClusterAddr_t TFSFileClass::GetStartClusterAddr(void)
  {
  return this->GetStructValue<TFS_FAT_ClusterAddr_t>(TFS_STRUCTURE_FAT_CLUSTER_START);
  }
TFS_FAT_SizeBytes_t TFSFileClass::GetSizeBytes(void)
  {
  return this->GetStructValue<TFS_FAT_SizeBytes_t>(TFS_STRUCTURE_FAT_SIZE_BYTES);
  }
TFS_FAT_ClusterAddr_t TFSFileClass::GetSizeClusters(void)
  {
  TFS_FAT_SizeBytes_t sb  = this->GetSizeBytes();
  TFS_FAT_ClusterAddr_t sc  = sb/TFS_CLUSTER_SIZE;
  if (sb%TFS_CLUSTER_SIZE != 0)
    {
    sc++;
    }
  return sc;
  }
TFS_FAT_ClusterAddr_t TFSFileClass::GetLastClusterAddr(void)
  {
  return this->GetStartClusterAddr() + this->GetSizeClusters();
  }
bool TFSFileClass::IsInsideCatalogue(TFS_FAT_Parent_t value)
  {
  return this->GetStructValue<TFS_FAT_Parent_t>(TFS_STRUCTURE_FAT_PARENT_CAT) == value;
  }
void TFSFileClass::SetParent(TFS_FAT_FilePos_t value)
  {
  this->SetStructValue<TFS_FAT_FilePos_t>(TFS_STRUCTURE_FAT_PARENT_CAT, value);
  }
bool TFSFileClass::IsNotEmpty(void)
  {
  return !(this->IsEmpty());
  }
bool TFSFileClass::IsEmpty(void)
  {
  if (this->IsParameterSet(TFS_STRUCTURE_FILE_PARAMETER_FILE_NOT_EMPTY))
    {
    if (this->GetStructValue<TFS_FAT_NotEmptyParameter_t>(TFS_STRUCTURE_FAT_EMPTY_BYTE) == 0)
      {
      return false;
      }
    }
  return true;
  }
void TFSFileClass::SetNotEmpty(void)
  {
  this->SetParameter(TFS_STRUCTURE_FILE_PARAMETER_FILE_NOT_EMPTY);
  this->SetStructValue<TFS_FAT_NotEmptyParameter_t>(TFS_STRUCTURE_FAT_EMPTY_BYTE, 0);
  }
void TFSFileClass::SetStartClusterAddr(TFS_FAT_ClusterAddr_t value)
  {
  this->SetStructValue<TFS_FAT_ClusterAddr_t>(TFS_STRUCTURE_FAT_CLUSTER_START, value);
  }
void TFSFileClass::SetFileSizeBytes(TFS_FAT_SizeBytes_t value)
  {
  this->SetStructValue<TFS_FAT_SizeBytes_t>(TFS_STRUCTURE_FAT_SIZE_BYTES, value);
  }
template <typename T>
T TFSFileClass::GetStructValue(TFS_STRUCTURE_FAT var)
  {
  return ntoh(*(this->GetStructAddr<T>(var)));
  }
template <typename T>
T* TFSFileClass::GetStructAddr(TFS_STRUCTURE_FAT var)
  {
  return (T*)&this->file[var];
  }
template <typename T>
void TFSFileClass::SetStructValue(TFS_STRUCTURE_FAT var, T val)
  {
  val = hton(val);
  memcpy(this->GetStructAddr<T>(var), &val, sizeof(T));
  }

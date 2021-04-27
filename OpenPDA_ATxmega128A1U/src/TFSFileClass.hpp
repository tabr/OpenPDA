/*
 * TFSFileClass.h
 *
 * Created: 21.12.2019 22:57:15
 *  Author: MateshkoAV
 */ 


#ifndef TFSFILECLASS_H_
#define TFSFILECLASS_H_

class TFSFileClass //File
  {
  public:
    TFSFileClass(void);
    TFS_FAT_FilePos_t GetPosition(void);
    void SetPosition(TFS_FAT_FilePos_t value);
    void SetParameter(TFS_STRUCTURE_FILE_PARAMETERS parameter);
    void ClearParameter(TFS_STRUCTURE_FILE_PARAMETERS parameter);
    bool IsParameterSet(TFS_STRUCTURE_FILE_PARAMETERS parameter);
    char* GetName(void);
    void SetName(char* name);
    TFS_FAT_Parent_t GetParent(void);
    TFS_FAT_ClusterAddr_t GetStartClusterAddr(void);
    TFS_FAT_SizeBytes_t GetSizeBytes(void);
    TFS_FAT_ClusterAddr_t GetSizeClusters(void);
    TFS_FAT_ClusterAddr_t GetLastClusterAddr(void);
    bool IsInsideCatalogue(TFS_FAT_Parent_t value);
    void SetParent(TFS_FAT_FilePos_t value);
    bool IsNotEmpty(void);
    bool IsEmpty(void);
    void SetNotEmpty(void);
    void SetStartClusterAddr(TFS_FAT_ClusterAddr_t value);
    void SetFileSizeBytes(TFS_FAT_SizeBytes_t value);
    void WriteHead(void);
    TFS_FAT_SizeBytes_t WriteData(uint8_t* data, TFS_FAT_SizeBytes_t length);//return bytes written, 0 if end
    TFS_FAT_SizeBytes_t ReadData(uint8_t* data, TFS_FAT_SizeBytes_t length);//return bytes readed, 0 if end
    void SeekByPosition(TFS_FAT_FilePos_t pos);//calls ResetInternalPointer
    void SetInternalPointer(TFS_FAT_SizeBytes_t addr);
    void ResetInternalPointer(void);
  protected:
  private:
    uint8_t file[TFS_STRUCTURE_FAT_HEAD_SIZE_BYTES];
    TFS_FAT_SizeBytes_t internalDataPointer=0;

    template <typename T>
    T GetStructValue(TFS_STRUCTURE_FAT var);
    template <typename T>
    T* GetStructAddr(TFS_STRUCTURE_FAT var);
    template <typename T>
    void SetStructValue(TFS_STRUCTURE_FAT var, T val);
  };



#endif /* TFSFILECLASS_H_ */
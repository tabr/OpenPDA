/*
 * Class_SPIFS_P256.h
 *
 * Created: 03.01.2018 23:17:06
 *  Author: tabr
 */ 


#ifndef CLASS_SPIFS_P256_H_
#define CLASS_SPIFS_P256_H_
/*
PAGE SIZE 256bytes
SPIFS
[0-8191]FileList:
[0-1]   PageAddr[2]
[2-5]   FileSizeInBytes[3]
[6-13]  FileName
[14-15] RESERVED
DATA:
[8192++](32th page)


*/
typedef uint16_t SPIFS_P256_FilePtr_t;//in pages
typedef uint16_t SPIFS_P256_FilesNum_t;
typedef char* FileName_t;
/*
ONLY 256 Bytes page
ONLY one by one files, no pass
*/

struct SPIFS_P256_FileStruct
  {
  const static uint8_t FILE_NAME_MAX_LENGTH = 8;

  uint32_t FileSizeInBytes=0;//3 bytes
  uint16_t PageAddr=0;
  char FileName[FILE_NAME_MAX_LENGTH];
  uint8_t RESERVED1 = 0;
  uint8_t RESERVED2 = 0;

  SPIFS_P256_FileStruct(void)
    {
    memset(this->FileName, 0, sizeof(this->FileName));
    }
  };

class FileSimpleInterface
  {
  public:
    enum FileErrors
      {
      FileError_NoError,
      FileError_Unknown
      };
    virtual FileErrors FOpen(FileName_t fname) = 0;
  protected:
  private:
  };
//#include <Int24.hpp>
class Class_SPIFS_P256 : public FileSimpleInterface
  {
  public:
    /*enum FileListStructure
      {
      FileListStructure_PageAddr,
      FileListStructure_FileSizeInBytes,
      FileListStructure_FileName,
      FileListStructure_RESERVED1,
      FileListStructure_RESERVED2,
      };*/

    const static uint16_t PAGE_SIZE               = 256;
    const static SPIFS_P256_FilesNum_t MAX_FILES  = 512;

    const static uint8_t FILE_LIST_STARTS         = 0;
    const static uint8_t FILE_STRUCT_LENGTH       = 16;
    const static uint16_t DATA_STARTS             = (FILE_LIST_STARTS+(FILE_STRUCT_LENGTH*MAX_FILES));

    FileErrors FOpen(FileName_t fname)
      {
      for (SPIFS_P256_FilesNum_t i=0;i<MAX_FILES;i++)
        {

        }
      return FileSimpleInterface::FileError_NoError;
      }

    FileErrors GetFileByNum(SPIFS_P256_FilesNum_t fnum, SPIFS_P256_FilePtr_t ptr)
      {
      if (this->ReadFile(fnum) == FileErrors::FileError_NoError)
        {
        //ptr = &this->ptr
        }
      return FileErrors::FileError_Unknown;
      }
    Class_SPIFS_P256(void)
      {
      memset(this->cache, 0, PAGE_SIZE);
      }
  protected:
  private:

    FileErrors ReadFileHead(SPIFS_P256_FilesNum_t fnum)
      {
      //Need to finish!
      return FileErrors::FileError_NoError;
      }
    FileErrors ReadFile(SPIFS_P256_FilesNum_t fnum)
      {
      //Need to finish!
      return FileErrors::FileError_NoError;
      }
    uint8_t cache[PAGE_SIZE];
    SPIFS_P256_FileStruct fileStruct;
  };



#endif /* CLASS_SPIFS_P256_H_ */
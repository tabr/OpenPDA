/*
 * TFSClass.h
 *
 * Created: 06.05.2018 18:36:25
 *  Author: tabr
 */ 


#ifndef TFSCLASS_H_
#define TFSCLASS_H_
//#include "net/net.h" 
/*
structure: [page=128]
FILENAME[0..15]			#filename [WHAT TO DO WITH \0 at the end???]
[16] EMPTY				# \0
[17..26]				#RESERVED
PARENT_CAT[27]			#parent catalogue. 0 mean root
PAGE_START[28..29]		#???
SIZE_BYTES[30..31]		#file size in bytes, 0 mean catalogue

MAX 255 FILES
IF SIZE_BYTES == 0 mean catalogue
FILE_0 - reserved(root)
*/
typedef uint8_t TFS_FAT_NotEmptyParameter_t;
typedef uint8_t TFS_FAT_Parent_t;
typedef uint8_t TFS_FAT_FilePos_t;
typedef uint8_t TFS_FAT_FileParameters_t;
typedef uint16_t TFS_FAT_ClusterAddr_t;
typedef uint16_t TFS_FAT_SizeBytes_t;
typedef uint16_t* TFS_FAT_ClusterAddr_p;
typedef uint16_t* TFS_FAT_SizeBytes_p;

enum TFS_STRUCTURE_FILE_PARAMETERS //TODO
  {
  TFS_STRUCTURE_FILE_PARAMETER_FILE_NOT_EMPTY,
  };
TODO("Move FileName from Head to data section. Leave inside head only FileNameLegnth. So data should starts with byte FileName: [FileName 0..255][data]")
enum TFS_STRUCTURE_FAT //MAX 255 FILES        FILE[1..255]                                    FILE0
  {
  TFS_STRUCTURE_FAT_STARTS              = 0,
  TFS_STRUCTURE_FAT_FILENAME            = 0,  //[0..15] [0..16]?
  TFS_STRUCTURE_FAT_EMPTY_BYTE          = 16,
//  TFS_STRUCTURE_FAT_FILE_NOT_EMPTYVAR,
  TFS_STRUCTURE_FAT_POSITION            = 25, //[25] self position
  TFS_STRUCTURE_FAT_FILE_PARAMETERS     = 26, //[26] 0xF0 if not empty
  TFS_STRUCTURE_FAT_PARENT_CAT          = 27, //[27] parent catalogue							0 mean "/"
  TFS_STRUCTURE_FAT_CLUSTER_START       = 28, //[28..29]                                       FIRST empty cluster
  TFS_STRUCTURE_FAT_SIZE_BYTES          = 30, //[30..31] IF SIZE_BYTES == 0 mean catalogue     num of files
  TFS_STRUCTURE_FAT_HEAD_SIZE_BYTES     = 32,
  };
const static TFS_FAT_NotEmptyParameter_t TFS_FAT_FILE_NOT_EMPTY_VAL   = 0xF0;
const static uint16_t TFS_FILENAME_LENGTH                             = 16;// 16+ "\0" mean 17
const static uint8_t TFS_CLUSTER_SIZE                                 = 128;
const static TFS_FAT_FilePos_t FIRST_FILEID                           = 1;
const static TFS_FAT_FilePos_t MAX_FILEID                             = 255;


#include "TFSFileClass.hpp"


class TFSClass
  {
  public:
    enum FS_STRUCTURE_ADDR
      {
      FS_STRUCTURE_ADDR_FAT_STARTS    = 0,
      FS_STRUCTURE_ADDR_DATA_STARTS   = 8192
      };

    TFS_FAT_FilePos_t GetFilePosition(char* name, TFS_FAT_FilePos_t parent_cat=0);
    TFS_FAT_FilePos_t WriteNewFile(char* name, TFS_FAT_FilePos_t parent_cat=0, uint8_t* data=NULL, TFS_FAT_SizeBytes_t size_bytes=0);
    TFS_FAT_FilePos_t GetFirstEmptyFilePosition(void);
    bool IsFileExists(char* name, TFS_FAT_FilePos_t parent_cat=0);
    TFS_FAT_ClusterAddr_t GetFirstEmptyClusterAddr(void);
    void MkFS(void);//TODO
  protected:
  private:
  };


#endif /* TFSCLASS_H_ */
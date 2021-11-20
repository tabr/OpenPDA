#include "stdarg.h"
class STRClass
  {
  public:
    enum STR_LOCATION
      {
      STR_LOCATION_OUTSIDE_BUFFER,
      STR_LOCATION_INSIDE_BUFFER,
      };
    const static uint8_t MAX_STR_LENGTH=30;
    const static uint8_t STORAGE_DATA_WIDTH=32;
    STRClass(char* ext_str)//should not call any Write.. methods
      {
      this->Clean();
      this->SetExternalBuffer(ext_str);
      this->str_loc     = STR_LOCATION_INSIDE_BUFFER;
      }
    STRClass(STR_POS pos)
      {
      this->Clean();
      this->SetPos(pos);
      }
    STRClass(void)
      {
      this->Clean();
      }
    void SetPos(STR_POS pos)
      {
      this->current_pos = pos;
      this->str_loc     = STR_LOCATION_OUTSIDE_BUFFER;
      }
    void WriteTo(char* buffer);
    void WritePgmTo(char* buffer);
    void WriteFormat(char* buffer, ...)
      {
      if (this->str_loc == STR_LOCATION_INSIDE_BUFFER)
        {
        return;
        }
      //this->SetExternalBuffer(buffer);
      //STRClass Str(format_pos);
      char format[STORAGE_DATA_WIDTH];
      memset(format, 0, sizeof(format));
      this->WriteTo(format);
      va_list ap;

      va_start(ap, buffer);
      //это вместо fprintf
      vsprintf(buffer, format, ap);
      //vsprintf(buffer, "%03u", ap);
      va_end(ap);
      this->SetExternalBuffer(buffer);
      this->str_loc     = STR_LOCATION_INSIDE_BUFFER;
      }
    void SetExternalBuffer(char* buffer)
      {
      this->external_buffer = buffer;
      this->str_loc     = STR_LOCATION_OUTSIDE_BUFFER;
      }
    char* Get(void)
      {
      return this->external_buffer;
      }
  protected:
  private:
    void Clean(void);
    STR_POS current_pos;
    char* external_buffer;
    STR_LOCATION str_loc;
  };
typedef STRClass ItemTypeName_t;

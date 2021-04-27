/*
 * TFS_IOWriter_MediaMemoty.cpp
 *
 * Created: 22.12.2019 20:14:30
 *  Author: MateshkoAV
 */ 
void TFS_IOWriter::ReadData(uint32_t addr, uint8_t* data, uint16_t length)
	{
	UNION_UINT32 file_addr;
	file_addr.value_int = addr;
	cli();
	MediaMemory.ReadData(file_addr.byte_field.mh, file_addr.byte_field.ml, file_addr.byte_field.l, data, length);
	sei();
	}
void TFS_IOWriter::WriteData(uint32_t addr, uint8_t* data, uint16_t length)
	{
	UNION_UINT32 file_addr;
	file_addr.value_int = addr;
	cli();
	MediaMemory.WriteData(file_addr.byte_field.mh, file_addr.byte_field.ml, file_addr.byte_field.l, data, length);
	sei();
	}

/*
 * TFS_IOWriter.h
 *
 * Created: 22.12.2019 20:13:18
 *  Author: MateshkoAV
 */ 


#ifndef TFS_IOWRITER_H_
#define TFS_IOWRITER_H_


class TFS_IOWriter
	{
	public:
	static void ReadData(uint32_t addr, uint8_t* data, uint16_t length);
	static void WriteData(uint32_t addr, uint8_t* data, uint16_t length);
	protected:
	private:
	};


#endif /* TFS_IOWRITER_H_ */
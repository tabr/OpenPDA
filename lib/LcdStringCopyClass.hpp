/*
 * LcdStringCopyClass.h
 *
 * Created: 30.06.2017 23:16:18
 *  Author: tabr
 */ 


#ifndef LCDSTRINGCOPYCLASS_H_
#define LCDSTRINGCOPYCLASS_H_



class LcdStringCopyClass
	{
	public:
		char* CopyFrom(char* srcCharArray)
			{
			this->Cleanup();
			this->length	= strlen(srcCharArray);
			if (this->length > 14)
				{
				this->length	= 14;
				}
			this->length++;//+empty string;
			this->strCharCopy	= new char[this->length];
			this->byteSize		= (sizeof(char) * this->length);
			memset(this->strCharCopy, 0, this->byteSize);
			memcpy(this->strCharCopy, srcCharArray, this->byteSize);
			return this->GetCopy();
			}
		char* CopyFromUnlimited(char* srcCharArray)
			{
			this->Cleanup();
			this->length	= strlen(srcCharArray);
			this->length++;//+empty string;
			this->strCharCopy	= new char[this->length];
			this->byteSize		= (sizeof(char) * this->length);
			memset(this->strCharCopy, 0, this->byteSize);
			memcpy(this->strCharCopy, srcCharArray, this->byteSize);
			return this->GetCopy();
			}
		char* GetCopy(void)
			{
			return this->strCharCopy;
			}
		size_t GetLength(void)
			{
			return this->length;
			}
		size_t GetByteSize(void)
			{
			return this->byteSize;
			}
		void Cleanup(void)
			{
			this->length		= 0;
			this->byteSize		= 0;
			this->strCharCopy	= NULL;
			}
	protected:
	private:
		size_t length		= 0;
		size_t byteSize		= 0;
		char* strCharCopy	= NULL;
	};

#endif /* LCDSTRINGCOPYCLASS_H_ */
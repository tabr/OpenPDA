// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//http://we.easyelectronics.ru/Soft/avr-s-i-umnye-ukazateli.html
/*
 * CPPFile1.cpp
 *
 * Created: 2015-02-05 11:51:10
 *  Author: tabr
 */ 
// ���� ������ ��������� ��� ���������:
// 1 - ��� ���������� �� ������� ��������� ���������
// 2 - ����� ���������� ������� ������ �� �������� ��������� ������������
template<class T, class Accessor>
class BasePtr
{
	// ��������� ��� ������������ ����� ������ ��� ���������
	typedef BasePtr Self;
	public:
	BasePtr(T *address=0)
	:_address(address)
	{
	}
	// ����� ���������� ��� �������� �������������� ���� ����������
	// ������������
	inline Self& operator ++()
	{
		_address++;
		return *this;
	}
	// �������������
	inline Self operator ++(int)
	{
		Self tmp = *this;
		_address++;
		return tmp;
	}
	// ������������
	inline Self& operator --()
	{
		_address--;
		return *this;
	}
	// �������������
	inline Self operator --(int)
	{
		Self tmp = *this;
		_address--;
		return tmp;
	}
	
	inline Self& operator +=(int value)
	{
		_address += value;
		return *this;
	}

	inline Self& operator -=(int value)
	{
		_address -= value;
		return *this;
	}

	inline Self operator +(int value)
	{
		return Self(_address + value);
	}

	inline Self operator -(int value)
	{
		return Self(_address - value);
	}

	inline bool operator !=(const Self &other) const
	{
		return _address != other._address;
	}

	inline bool operator ==(const Self &other) const
	{
		return _address == other._address;
	}
	// �������� ���������������� ���������. ����� �������������� ������ �� ���������.
	inline const T operator *()const
	{
		union
		{
			T value;
			uint8_t bytes[sizeof(T)];
		}data;

		for(unsigned i = 0; i<sizeof(T); ++i)
		data.bytes[i] = Accessor::Read(_address + i);
		return data.value;
	}
	private:
	T * _address;
};
template<class T>
class FlashPtr :public BasePtr<T, FlashPtr<T> >
{
	public:
	FlashPtr(T *address)
	:BasePtr<T, FlashPtr<T> >(address)
	{}

	static uint8_t Read(T *addr)
	{
		return pgm_read_byte((const uint8_t*)addr);
	}
};

template<class T>
class EepromPtr :public BasePtr<T, EepromPtr<T> >
{
	public:
	EepromPtr(T *address)
	:BasePtr<T, EepromPtr<T> >(address)
	{}

	static uint8_t Read(T *addr)
	{
		return eeprom_read_byte((const uint8_t*)addr);
	}
};
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * ErrorClass.cpp
 *
 * Created: 19.12.2016 19:05:27
 *  Author: tabr
 */ 

void ErrorClass::SetError(ErrorClass::CODES code)
	{
	#ifdef DEBUG_USART_ERRORS
		sprintf (USARTBuffer,"[ErrorClass] code [%03u]\r\n", code);
		sendString(USARTBuffer);
	#endif // DEBUG_USART_MULTY_PACKETS
	this->lastCode	= code;
	}
ErrorClass::CODES ErrorClass::GetLastError(void)
	{
	return this->lastCode;
	}
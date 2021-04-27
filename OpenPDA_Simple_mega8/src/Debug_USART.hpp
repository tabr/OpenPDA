/*
 * Debug_USART.h
 *
 * Created: 20.09.2017 18:26:09
 *  Author: tabr
 */ 


#ifndef DEBUG_USART_H_
#define DEBUG_USART_H_

#ifdef DEBUG_USART
#warning "DEBUG_USART"


#ifdef DEBUG_USART
#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)
#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<UPE)
#define DATA_OVERRUN (1<<DOR)
#endif //DEBUG_USART


#ifdef DEBUG_USART_STR
#define sendString USART_startTX

// USART Transmitter buffer
#define TX_BUFFER_SIZE 128

char USARTBuffer[TX_BUFFER_SIZE];

#if TX_BUFFER_SIZE > 256
#error ERROR
#endif //X_BUFFER_SIZE > 256

volatile uint8_t tx_rd_index		= 0;
volatile uint8_t tx_counter		= 0;
//uint8_t USART_tx_size	= 0;

// USART Transmitter interrupt service routine
ISR(USART_TXC_vect)// void usart_tx_isr(void)
	{
	if (tx_counter > 0)
		{
		--tx_counter;
		UDR=USARTBuffer[tx_rd_index];
		tx_rd_index++;
		#if TX_BUFFER_SIZE != 256
		if (tx_rd_index == TX_BUFFER_SIZE)
			{
			tx_rd_index=0;
			}
		#endif
		}
	}
void USART_startTX(uint8_t length)
	{
//	if ((tx_counter == 0) && ((UCSRA & DATA_REGISTER_EMPTY)==0))
	if (length > 0)
		{
		while (tx_counter > 0);//ждем окончания передачи
		tx_rd_index		= 0+1;
//		tx_counter		= TX_BUFFER_SIZE - 1;
		tx_counter		= length - 1;//because 1 byte we will send now
//		USART_tx_size	= length - 1;

		UDR=USARTBuffer[0];
		}
	}

void USART_startTX(char* ptr)
	{
	while (tx_counter > 0);//ждем окончания передачи
	sprintf(USARTBuffer, ptr);
	USART_startTX(strlen(ptr));
	}

#endif //DEBUG_USART_STR


#include "USART_Codes.h"
#endif // DEBUG_USART

#endif /* DEBUG_USART_H_ */
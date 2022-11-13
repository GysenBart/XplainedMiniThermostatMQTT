/*
 * buffer.h
 *
 * Created: 10/11/2018 13:43:31
 *  Author: Petervg
 */ 


#ifndef BUFFER_H_
#define BUFFER_H_

#define	RXBUFFERSIZE0 100

struct _RxBuffer
{
	volatile unsigned char Buffer[RXBUFFERSIZE0];
	volatile unsigned char WriteIndex;
	volatile unsigned char IsDirty;
	volatile unsigned char BufferOverflow;
	unsigned char ReadIndex;
	volatile uint8_t Ok;
	volatile uint8_t CrLn;
};

// Locate a string (zero terminated) in the buffer and return the index of the occurence (index is the location of the first letter of the string).
// Search is performed from the current readindex to the current writeindex and only the first occurence is reported. -1 indicates string was not found.
signed int FindString(const uint8_t *l_String, struct _RxBuffer *l_UART_RxBuffer);

// Clear the buffer to all 0x0.
void ClearBuffer(struct _RxBuffer *l_UART_RxBuffer);


#endif /* BUFFER_H_ */
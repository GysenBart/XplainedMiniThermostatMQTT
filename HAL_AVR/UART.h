/*
 * UART.h
 *
 * Created: 01/11/2018 19:29:52
 *  Author: Petervg
 */ 


#ifndef UART_H_
#define UART_H_



void init_UART(uint16_t l_UBRR, uint8_t l_doublespeed);
void putc_UART(uint8_t c);
void puts_UART(const uint8_t* s);
void putvar_UART(uint8_t* s);




#endif /* UART_H_ */
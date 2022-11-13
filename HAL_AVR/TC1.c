/*
 * TC1.c
 *
 * Created: 01/11/2018 21:33:48
 *  Author: Petervg
 */ 

#include <avr/interrupt.h>
#include "TC1.h"


volatile uint8_t g_TickSensor = 0;
volatile uint8_t g_TickSetpoint = 0;
volatile uint16_t g_TickStatemachine = 0;
volatile uint8_t g_LcdUpdateTimer = 0;
volatile uint16_t g_DemoTimer = 0;
volatile uint8_t g_CheckSubRecv = 0;


void init_TC1(unsigned int l_MaxCount)
{
	TCCR1B = (0<<CS12)|(1<<CS11)|(0<<CS10);		// Select CLKIO/8
	OCR1A = l_MaxCount;							// Set max count value to trigger interrupts
	TIMSK1 = (1<<OCIE1A);						// Enable output compare A match interrupt
	sei();										// Enbale global interrupts
}


ISR(TIMER1_COMPA_vect)
{
	TCNT1=0;				// Reset TC1 to 0
	g_TickSensor++;				// General purpose tick timer
	g_TickSetpoint++;
	g_TickStatemachine++;
	g_CheckSubRecv++;
	g_LcdUpdateTimer++;		// Timer for updating LCD
	g_DemoTimer++;			// Used for display demo
}






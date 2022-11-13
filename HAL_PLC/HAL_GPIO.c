/*
 * GPIO.c
 *
 * Created: 01/11/2018 22:34:09
 *  Author: Petervg
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

#include "../global.h"
#include "HAL_GPIO.h"
#include "../HAL_LCD/SSD1306.h"
#include "../HAL_AVR/UART.h"


void init_GPIO()
{
	DDRC = 0b00001000;			// Set PC3 as output, used for I2C display
	DDRB = 0b00000111;			// Set PB0-2 as output, used for SPI display
	DDRD = 0b10000000;			// Set PD7 as output, used for the heater
}


void GPIO_OledReset(uint8_t l_Interface, uint8_t l_State)
{
	switch (l_State)
	{
		case 0:
			if (l_Interface == RESETI2C)
			{
				PORTC = PORTC &~(1 << 3);	// I2C display	
			}
			if (l_Interface == RESETSPI)
			{
				PORTB = PORTB &~(1 << 0);	// SPI display	
			}			
		break;

		case 1:
			if (l_Interface == RESETI2C)
			{
				PORTC = PORTC | (1 << 3);	// I2C display
			}
			if (l_Interface == RESETSPI)
			{
				PORTB = PORTB | (1 << 0);	// SPI display
			}			
		break;

		default:
		while(1);	// Error
	}
}


void GPIO_SetOledDC(uint8_t l_State)
{
	switch (l_State)
	{
		case 0:
		PORTB = PORTB &~(1 << 1);
		break;

		case 1:
		PORTB = PORTB | (1 << 1);
		break;

		default:
		while(1);	// Error
	}
}


void GPIO_SetOledCS(uint8_t l_State)
{
	switch (l_State)
	{
		case 0:
		PORTB = PORTB &~(1 << 2);
		break;

		case 1:
		PORTB = PORTB | (1 << 2);
		break;

		default:
		while(1);	// Error
	}
}

void setpinD(uint8_t l_pinnr, uint8_t l_status)
{
	if (l_status)
	{
		PORTD = PORTD | (1<<l_pinnr);	// turn ON output
	}
	else
	{
		PORTD = PORTD &~(1<<l_pinnr);	// Turn OFF output
	}
}

void setheater(uint8_t l_status)
{
	setpinD(7, l_status);
}
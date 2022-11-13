/*
 * FrameWork.c
 *
 * Created: 01/11/2018 19:02:40
 * Author : Petervg
 * 
 * I2C connections:
 * Connect BMP280 SCK (SCL)_to the CPU PC5
 * Connect BMP280 SDI (SDA) to the CPU PC4
 *
 * SPI connections:
 * Connect OLED D0 (CLK) to the CPU PB5
 * Connect OLED D1 (MOSI) to the CPU PCB3
 * Connect OLED RES (reset) to the CPU PB0
 * Connect OLED DC (data/command) to the CPU PB1
 * Connect OLED CS (Chip select) to the CPU PB2
 *
 * To enable sprintf function:
 * In AtmelStudio, go to Project -> Properties ->Toolchain->AVR/GNU linker->General setup dialog. Then select linker options, and then add the -Wl,-u,vfprintf
 * 
 * BMP280 library used: Bosch sensortec BMP2 sensor API
 * https://github.com/BoschSensortec/BMP2-Sensor-API/
 *
 */ 


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <avr/io.h>



#include "global.h"

#include "main.h"
#include "Buffer.h"
#include "statemachine.h"



#include "HAL_PLC/HAL_Init.h"
#include "HAL_PLC/HAL_GPIO.h"
#include "HAL_AVR/UART.h"
#include "HAL_LCD/SSD1306.h"
#include "HAL_BMP280/bmp2_defs.h"
#include "HAL_BMP280/app_BMP280.h"
#include "HAL_BMP280/HAL_BMP280.h"
#include "ESP8266_ATCOMMANDS/AT_commands_ESP8266.h"

extern struct bmp2_data comp_data;
extern struct _wifi str_AT_wifi;
extern struct _mqtt str_AT_mqtt;

signed int g_SubRecvIndex;

int main(void)
{
	HAL_Init();
	
    while (1)
    {
		if (UART_RxBuffer.CrLn == 1)			// check if there is an flag Carriage return and line feed
		{
			UART_RxBuffer.CrLn = 0;				// Sets the flag back to 0
			
			if ((FindString("+MQTTSUBRECV", &UART_RxBuffer)) >= 0)  // check if there is a match for mqtt subscribed received data
			{
				g_SubRecvIndex = FindString("SETPOINT", &UART_RxBuffer); // check if the subcribed received data is a setpoint
				if (g_SubRecvIndex >= 0)
				{					
					comp_data.setpoint = ((UART_RxBuffer.Buffer[g_SubRecvIndex+12]-48) *10) + (UART_RxBuffer.Buffer[g_SubRecvIndex+13]-48); // get the setpoint data
				}
				
			}
			else if (FindString("OK", &UART_RxBuffer))
			{
				UART_RxBuffer.Ok = 1;
			}
			else
			{
				ClearBuffer(&UART_RxBuffer);
			}
			
		}
		
		if (g_TickSensor > 100)
		{
			g_TickSensor = 0;
			if (readsensor() == BMP2_OK)
			{
				// Convert the temperature from uint16 to array of bytes 
				sprintf(str_AT_mqtt.data, "%.5f", comp_data.temperature);
				
				showtemperature(&comp_data);
				showsetpoint(&comp_data);
				if (comparetemperature(&comp_data))
				{
					setheater(ON);
				} 
				else
				{
					setheater(OFF);
				}
			} 
			else
			{
				showsensorerror();
			}		
		}
		
		
		if (g_TickStatemachine > 500)
		{
			g_TickStatemachine = 0;
			AT_statemachine();
		}
		
		
			
		// Update the OLED display
		if (g_LcdUpdateTimer > OLEDUPDATESPEED)
		{
			g_LcdUpdateTimer = 0;
			ProcessLCD(OLEDSPI);
		}
    }
}







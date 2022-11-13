/*
 * app_BMP280.c
 *
 * Created: 26/04/2022 19:08:13
 *  Author: bart-
 */ 

#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>

#include "../Buffer.h"
#include "../global.h"

#include "../HAL_PLC/HAL_Init.h"
#include "../HAL_PLC/HAL_GPIO.h"
#include "../HAL_AVR/UART.h"
#include "../HAL_LCD/SSD1306.h"

#include "bmp2_defs.h"
#include "HAL_BMP280.h"
#include "app_BMP280.h"


extern uint32_t meas_time;
extern struct bmp2_dev dev;
extern struct bmp2_config conf;
extern struct bmp2_data comp_data;


void showsetpoint(struct bmp2_data *l_setpoint)
{
	uint8_t l_setpointstring[5];
	
	sprintf(l_setpointstring, "%d", l_setpoint->setpoint);
	
	SSD1306_puts(0,3,"Setpoint:", FONTMEDIUM,&SSD1306FrameBuffer1);
	SSD1306_puts(0,4,l_setpointstring, FONTMEDIUM,&SSD1306FrameBuffer1);
}

void showtemperature(struct bmp2_data *p_temp)
{
	uint8_t l_temperaturestring[16];

	// Convert the temperature and pressure from double to array of bytes
	sprintf(l_temperaturestring, "%.5f", p_temp->temperature);
	
	SSD1306_puts(0,0,"Temperature (degC):", FONTMEDIUM,&SSD1306FrameBuffer1);
	SSD1306_puts(0,1,l_temperaturestring, FONTMEDIUM,&SSD1306FrameBuffer1);
}

void showsensorerror(void)
{
	SSD1306_clear(&SSD1306FrameBuffer1);
	SSD1306_puts(0,0,"Sensor error.     ", FONTMEDIUM,&SSD1306FrameBuffer1);
}


uint8_t comparetemperature(struct bmp2_data *p_data)
{
	uint8_t l_result;
	
	if(p_data->temperature < p_data->setpoint)
	{
		l_result = 1;
		SSD1306_puts(63,6,"                              ", FONTMEDIUM,&SSD1306FrameBuffer1);
		SSD1306_puts(63,6,"ON", FONTMEDIUM,&SSD1306FrameBuffer1);
	}
	else
	{
		l_result = 0;
		SSD1306_puts(63,6,"                              ", FONTMEDIUM,&SSD1306FrameBuffer1);
		SSD1306_puts(63,6,"OFF", FONTMEDIUM,&SSD1306FrameBuffer1);
	}
	return l_result;
}
uint8_t readsensor()
{
	uint8_t l_result;
	
	l_result = get_data(meas_time, &conf, &dev, &comp_data);
	return l_result;
}
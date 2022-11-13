/*
 * StateMachine.c
 *
 * Created: 10/05/2022 20:45:49
 *  Author: bart-
 */ 

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
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



uint8_t g_AT_State = ATCHECK;
uint8_t g_AT_NextState;
volatile uint8_t g_tickTimeOut = 0;

extern struct _wifi str_AT_wifi;
extern struct _mqtt str_AT_mqtt;
extern struct bmp2_data comp_data;

void AT_statemachine(void)
{
	switch (g_AT_State)
	{
		case ATCHECK:
		AT_check();
		g_AT_State = ATCHECKOK;
		g_AT_NextState = ATWIFICONNECT;
		break;
		
		case ATWIFICONNECT:
		strcpy(str_AT_wifi.WifiSSID, "dlink-5914");
		strcpy(str_AT_wifi.WifiPassword, "cjvgu89628");
		AT_wificonnect(&str_AT_wifi, &str_AT_wifi);
		g_AT_State = ATCHECKOK;
		g_AT_NextState = ATUSERCONF;
		break;

		case ATUSERCONF:
		strcpy(str_AT_mqtt.username, "mqtt");
		strcpy(str_AT_mqtt.password, "mqtt");
		strcpy(str_AT_mqtt.client_ID, "ESP8266");
		AT_mqtt_userconf(&str_AT_mqtt, &str_AT_mqtt, &str_AT_mqtt);
		g_AT_State = ATCHECKOK;
		g_AT_NextState = ATMQTTCONNECTION;
		break;
		
		case ATMQTTCONNECTION:
		strcpy(str_AT_mqtt.broker_IP, "192.168.0.102");
		AT_mqtt_connection(&str_AT_mqtt);
		g_AT_State = ATCHECKOK;
		g_AT_NextState = ATMQTTSUB;
		break;
		
		case ATMQTTSUB:
		strcpy(str_AT_mqtt.topic_sub , "SETPOINT");
		AT_mqtt_subscribe(&str_AT_mqtt);
		g_AT_State = ATCHECKOK;
		g_AT_NextState = ATMQTTPUB;
		break;
		
		case ATMQTTPUB:
		strcpy(str_AT_mqtt.topic_pub , "TEMPSENSOR");
		AT_mqtt_publish(&str_AT_mqtt, &str_AT_mqtt);
		ClearBuffer(UART_RxBuffer.Buffer);
		g_AT_State = ATMQTTPUB;
		break;
		
		case ATCHECKOK:
		if (UART_RxBuffer.Ok)
		{
			g_tickTimeOut = 0;
			UART_RxBuffer.Ok = 0;
			g_AT_State = g_AT_NextState;
		}
		else if (g_tickTimeOut++ > 10)
		{
			g_tickTimeOut = 0;
			g_AT_State = ATCHECK;
		}
		break;
		
		default:
		while(1);
	}
}
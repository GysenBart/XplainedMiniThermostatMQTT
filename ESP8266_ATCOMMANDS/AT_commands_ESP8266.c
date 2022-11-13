/*
 * AT_commands_ESP8266.c
 *
 * Created: 7/05/2022 22:19:01
 *  Author: bart-
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>

#include "AT_commands_ESP8266.h"
#include "../HAL_BMP280/bmp2_defs.h"
#include "../Buffer.h"
#include "../global.h"
#include "../HAL_AVR/TC1.h"
#include "../HAL_AVR/UART.h"


/*
Using AT commands to interact with the ESP8266.
The interaction takes place trough the UART peripheral.
*/

struct _wifi str_AT_wifi;
struct _mqtt str_AT_mqtt;

extern struct bmp2_data comp_data;


// Check if the interaction is OK
void AT_check(void)
{
	puts_UART("AT\r\n");
}

// Connect to a wifi network
void AT_wificonnect(struct _wifi *SSID, struct _wifi *password)
{
	puts_UART("AT+CWJAP=");
	putc_UART(34);
	puts_UART(SSID->WifiSSID);
	putc_UART(34);
	puts_UART(",");
	putc_UART(34);
	puts_UART(password->WifiPassword);
	putc_UART(34);
	puts_UART("\r\n");
}

// Set the user configuration
void AT_mqtt_userconf(struct _mqtt *user, struct _mqtt *password, struct _mqtt *id)
{
	puts_UART("AT+MQTTUSERCFG=0,1,");
	putc_UART(34); // show ASCII "
	puts_UART(id->client_ID);
	putc_UART(34);
	puts_UART(",");
	putc_UART(34);
	puts_UART(user->username);
	putc_UART(34);
	puts_UART(",");
	putc_UART(34);
	puts_UART(password->password);
	putc_UART(34);
	puts_UART(",0,0,");
	putc_UART(34);
	putc_UART(34);
	puts_UART("\r\n");
}

// Connect to mqtt broker
void AT_mqtt_connection(struct _mqtt *ip)
{
	puts_UART("AT+MQTTCONN=0,");
	putc_UART(34);
	puts_UART(ip->broker_IP);
	putc_UART(34);
	puts_UART(",1883,0\r\n");
}

// Publish to mqtt topic
void AT_mqtt_publish(struct _mqtt *topic, struct _mqtt *data)
{
	puts_UART("AT+MQTTPUB=0,");
	putc_UART(34);
	puts_UART(topic->topic_pub);
	putc_UART(34);
	puts_UART(",");
	putc_UART(34);
	puts_UART(data->data);
	putc_UART(34);
	puts_UART(",1,0\r\n");
}

// Subcribe to mqtt topic
void AT_mqtt_subscribe(struct _mqtt *topic)
{
	puts_UART("AT+MQTTSUB=0,");
	putc_UART(34);
	puts_UART(topic->topic_sub);
	putc_UART(34);
	puts_UART(",1\r\n");
}

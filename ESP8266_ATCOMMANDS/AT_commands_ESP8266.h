/*
 * AT_commands_ESP8266.h
 *
 * Created: 7/05/2022 22:56:30
 *  Author: bart-
 */ 


#ifndef AT_COMMANDS_ESP8266_H_
#define AT_COMMANDS_ESP8266_H_


//struct for the wifi data
struct _wifi
{
	unsigned char WifiSSID[12];
	unsigned char WifiPassword[11];
	
};

// struct for data to use mqtt
struct _mqtt
{
	unsigned char username[6];
	unsigned char password[6];
	unsigned char broker_IP[14];
	unsigned char client_ID[8];
	unsigned char topic_pub[11];
	unsigned char topic_sub[10];
	unsigned char data[10];
};

// prototypes
void AT_check(void);
void AT_wificonnect(struct _wifi *SSID, struct _wifi *password);
void AT_mqtt_userconf(struct _mqtt *user, struct _mqtt *password, struct _mqtt *id);
void AT_mqtt_connection(struct _mqtt *ip);
void AT_mqtt_subscribe(struct _mqtt *topic);
void AT_mqtt_publish(struct _mqtt *topic, struct _mqtt *data);


#endif /* AT_COMMANDS_ESP8266_H_ */
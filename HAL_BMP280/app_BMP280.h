/*
 * app_BMP280.h
 *
 * Created: 26/04/2022 19:08:33
 *  Author: bart-
 */ 


#ifndef APP_BMP280_H_
#define APP_BMP280_H_

#define UART 0
#define LCD 1
#define UARTLCD 2

void showsetpoint(struct bmp2_data *l_setpoint);
void showtemperature(struct bmp2_data *p_temp);
void showsensorerror(void);
uint8_t comparetemperature(struct bmp2_data *p_data);
uint8_t readsensor();



#endif /* APP_BMP280_H_ */
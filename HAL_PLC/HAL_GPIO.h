/*
 * HAL_GPIO.h
 *
 * Created: 01/11/2018 22:34:32
 *  Author: Petervg
 */ 


#ifndef HAL_GPIO_H_
#define HAL_GPIO_H_

void init_GPIO();
void GPIO_OledReset(uint8_t l_Interface, uint8_t l_State);
void GPIO_SetOledDC(uint8_t l_State);
void GPIO_SetOledCS(uint8_t l_State);
void setpinD(uint8_t l_pinnr, uint8_t l_status);
void setheater(uint8_t l_status);

#endif /* HAL_GPIO_H_ */
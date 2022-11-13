/*
 * HAL_BMP280.h
 *
 * Created: 20/02/2022 13:03:02
 *  Author: Petervg
 */ 


#ifndef HAL_BMP280_H_
#define HAL_BMP280_H_

#include "bmp2_defs.h"
#include "bmp2.h"

BMP2_INTF_RET_TYPE bmp2_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t length, void *intf_ptr);
BMP2_INTF_RET_TYPE bmp2_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t length, void *intf_ptr);
void bmp2_delay_us(uint32_t period, void *intf_ptr);
int8_t get_data(uint32_t period, struct bmp2_config *conf, struct bmp2_dev *dev, struct bmp2_data *l_comp_data);
int8_t BMP280_init();

#endif /* HAL_BMP280_H_ */
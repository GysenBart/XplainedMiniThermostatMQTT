/*
 * HAL_BMP280.c
 *
 * Created: 20/02/2022 13:02:52
 *  Author: Petervg
 */ 

#include <util/delay.h>

#include "../HAL_AVR/I2C.h"
#include "HAL_BMP280.h"


int8_t rslt;
uint32_t meas_time;
struct bmp2_dev dev;
struct bmp2_config conf;
static uint8_t dev_addr;
struct bmp2_data comp_data;


BMP2_INTF_RET_TYPE bmp2_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t length, void *intf_ptr)
{
	dev_addr = *(uint8_t*)intf_ptr;
	return i2c_readReg(dev_addr, reg_addr, reg_data, (uint16_t)length);
}


BMP2_INTF_RET_TYPE bmp2_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t length, void *intf_ptr)
{
	dev_addr = *(uint8_t*)intf_ptr;
	return i2c_writeReg(dev_addr, reg_addr, (uint8_t *)reg_data, (uint16_t)length);
}


void bmp2_delay_us(uint32_t period, void *intf_ptr)
{
	#ifndef __OPTIMIZE__
		for (uint32_t l_delay = 0 ; l_delay < period ; l_delay++);
	#else
		_delay_us(period);		
	#endif	
}


int8_t get_data(uint32_t period, struct bmp2_config *conf, struct bmp2_dev *dev, struct bmp2_data *l_comp_data)
{	
	int8_t rslt = BMP2_E_NULL_PTR;
	struct bmp2_status status;
	
	// wait for the current measurement to finish so readouts are synchronised
	rslt = bmp2_get_status(&status, dev);
	while (status.measuring == BMP2_MEAS_ONGOING)
	{
		rslt = bmp2_get_status(&status, dev);
	}
	
	/* Read compensated data */
	rslt = bmp2_get_sensor_data(l_comp_data, dev);
	
	return rslt;
}


int8_t BMP280_init()
{
	dev_addr = BMP2_I2C_ADDR_SEC;
	dev.read = bmp2_i2c_read;
	dev.write = bmp2_i2c_write;
	dev.intf = BMP2_I2C_INTF;
	dev.intf_ptr = &dev_addr;
	dev.delay_us = bmp2_delay_us;
		
	rslt = bmp2_init(&dev);

	/* Always read the current settings before writing, especially when all the configuration is not modified */
	rslt = bmp2_get_config(&conf, &dev);

	/* Configuring the over-sampling mode, filter coefficient and output data rate */
	/* Overwrite the desired settings */
	conf.filter = BMP2_FILTER_OFF;

	/* Over-sampling mode is set as high resolution i.e., os_pres = 8x and os_temp = 1x */
	conf.os_mode = BMP2_OS_MODE_HIGH_RESOLUTION;

	/* Setting the output data rate */
	conf.odr = BMP2_ODR_250_MS;
	rslt = bmp2_set_config(&conf, &dev);

	/* Set normal power mode */
	rslt = bmp2_set_power_mode(BMP2_POWERMODE_NORMAL, &conf, &dev);

	/* Calculate measurement time in microseconds */
	rslt = bmp2_compute_meas_time(&meas_time, &conf, &dev);
	
	return rslt;
}
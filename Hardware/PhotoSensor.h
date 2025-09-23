#ifndef __PHOTO_SENSOR_H
#define __PHOTO_SENSOR_H

#include "stm32f10x.h"

void PhotoSensor_Init(void);
uint8_t PhotoSensor1_Read(void);  // PD0
uint8_t PhotoSensor2_Read(void);  // PD1

#endif
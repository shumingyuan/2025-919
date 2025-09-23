#ifndef __HCSR04_H
#define __HCSR04_H

#include "stm32f10x.h"  // 添加头文件以支持int16_t类型

void HC_SR04_Init(void);
void HC_SR04_Timer_Init(void);  // 添加定时器初始化函数声明
int16_t sonar_mm(void);
float sonar(void);

#endif

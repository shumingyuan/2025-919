#include "PhotoSensor.h"
#include "Delay.h"

/**
  * @brief  初始化光电传感器GPIO
  * @note   使用PD0和PD1，低电平有效
  * @retval None
  */
void PhotoSensor_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;    // 上拉输入（因为是低电平有效）
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/**
  * @brief  读取光电传感器1状态
  * @note   低电平表示检测到障碍物
  * @retval 1-无障碍物，0-有障碍物
  */
uint8_t PhotoSensor1_Read(void)
{
    return GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0);
}

/**
  * @brief  读取光电传感器2状态
  * @note   低电平表示检测到障碍物
  * @retval 1-无障碍物，0-有障碍物
  */
uint8_t PhotoSensor2_Read(void)
{
    return GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1);
}
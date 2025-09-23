#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"  		//OLED
#include "LED.h"		//LED
#include "Key.h"       	//按键
#include "Buzzer.h"     //蜂鸣器
#include "Motor.h"     	//电机
#include "ENCODER.h"   	//编码器
#include "Serial.h"    	//串口
#include "Control.h"   //控制逻辑
#include "GY25.h"      //GY-25陀螺仪
#include "HCSR04.h"    //超声波
#include "PhotoSensor.h" //光电传感器
#include "stm32f10x_usart.h" // 显式包含USART头文件

int Base_Speed = 170; // 基础速度，可调


int main(void)
{
	OLED_Init();
	LED_Init();
	Key_Init();
	Buzzer_Init();
	Motor_Init();
	Encoder_Init();
	Serial_Init();
	GY25_Init();		//GY-25陀螺仪初始化
	
    GY25_SendQuery();
    OLED_ShowString(2, 1, "YAW:");
    
    // 初始化新增的传感器
    HC_SR04_Init();
    PhotoSensor_Init();
    Delay_ms(3000);
    while (1)
    {
        // 处理陀螺仪数据
        GY25_ProcessData();
        
        // 读取并显示超声波距离
        int16_t distance = sonar_mm();
        OLED_ShowString(1, 1, "Dist:");
        OLED_ShowNum(1, 6, distance, 4);
        OLED_ShowString(1, 10, "mm");
        
        // 读取并显示光电传感器状态
        uint8_t photo1 = PhotoSensor1_Read();
        uint8_t photo2 = PhotoSensor2_Read();
        
        OLED_ShowString(3, 1, "P1:");
        OLED_ShowNum(3, 4, !photo1, 1);  // 取反是因为低电平有效
        OLED_ShowString(4, 1, "P2:");
        OLED_ShowNum(4, 4, !photo2, 1);
        
        // // 如果任一光电传感器检测到障碍物，蜂鸣器响
        // if (!photo1 || !photo2)
        // {
        //     Buzzer_ON();
        //     LED_ON();
        // }
        // else
        // {
        //     Buzzer_OFF();
        //     LED_OFF();
        // }
        
        Delay_ms(100);  // 刷新间隔
    }
	
}

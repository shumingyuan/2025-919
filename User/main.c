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


int Base_Speed = 200; // 基础速度，可调


int main(void)
{
	OLED_Init();
	LED_Init();
	Key_Init();
	Buzzer_Init();
	Motor_Init();
	Encoder_Init();
	Serial_Init();
	Delay_ms(1000);
	
	// 显示初始信息
	OLED_ShowString(1, 1, "Encoder Test");
	OLED_ShowString(2, 1, "Basic Directions");
	Delay_ms(2000);
	OLED_Clear();
	// 测试向前移动
	OLED_ShowString(1, 1, "Forward 5cm");
	OLED_ShowString(4, 1, "Running...");
	Clear_All_Encoder_Count();
	Delay_ms(500);
	Move_Distance_Mecanum(5.0f, 200, MOVE_FORWARD);
	OLED_ShowString(4, 1, "Complete!");
	Delay_ms(1000);
	OLED_Clear();
	// 测试向后移动
	OLED_ShowString(1, 1, "Backward 5cm");
	OLED_ShowString(4, 1, "Running...");
	Clear_All_Encoder_Count();
	Delay_ms(500);
	Move_Distance_Mecanum(5.0f, 200, MOVE_BACKWARD);
	OLED_ShowString(4, 1, "Complete!");
	Delay_ms(1000);
	OLED_Clear();
	// 测试向左移动
	OLED_ShowString(1, 1, "Left 5cm");
	OLED_ShowString(4, 1, "Running...");
	Clear_All_Encoder_Count();
	Delay_ms(500);
	Move_Distance_Mecanum(5.0f, 200, MOVE_TRANSLATE_LEFT);
	OLED_ShowString(4, 1, "Complete!");
	Delay_ms(1000);
	OLED_Clear();
	// 测试向右移动
	OLED_ShowString(1, 1, "Right 5cm");
	OLED_ShowString(4, 1, "Running...");
	Clear_All_Encoder_Count();
	Delay_ms(500);
	Move_Distance_Mecanum(5.0f, 200, MOVE_TRANSLATE_RIGHT);
	Delay_ms(1000);
	OLED_Clear();
	//测试右前方
	OLED_ShowString(1, 1, "RightFront 5cm");
	OLED_ShowString(4, 1, "Running...");	
	Clear_All_Encoder_Count();
	Delay_ms(500);
	Move_Distance_Mecanum(5.0f, 200, MOVE_FORWARD_RIGHT);
	Delay_ms(1000);
	OLED_Clear();
	//测试左前方
	OLED_ShowString(1, 1, "LeftFront 5cm");
	OLED_ShowString(4, 1, "Running...");
	Clear_All_Encoder_Count();
	Delay_ms(500);
	Move_Distance_Mecanum(5.0f, 200, MOVE_FORWARD_LEFT);
	Delay_ms(1000);
	OLED_Clear();
	//测试右后方	
	OLED_ShowString(1, 1, "RightBack 5cm");
	OLED_ShowString(4, 1, "Running...");
	Clear_All_Encoder_Count();
	Delay_ms(500);
	Move_Distance_Mecanum(5.0f, 200, MOVE_BACKWARD_RIGHT);
	Delay_ms(1000);
	OLED_Clear();
	//测试左后方
	OLED_ShowString(1, 1, "LeftBack 5cm");
	OLED_ShowString(4, 1, "Running...");
	Clear_All_Encoder_Count();
	Delay_ms(500);
	Move_Distance_Mecanum(5.0f, 200, MOVE_BACKWARD_LEFT);
	Delay_ms(1000);
	OLED_Clear();
	// 显示测试完成
	OLED_ShowString(1, 1, "Basic Tests");
	OLED_ShowString(2, 1, "Complete!");
	OLED_ShowString(3, 1, "");
	OLED_ShowString(4, 1, "");
    // //单个电机测试
	// Delay_ms(2000);
	// OLED_Clear();
	// OLED_ShowString(1, 1, "Single Motor Test");				
	// Delay_ms(1000);
	// OLED_ShowString(2, 1, "Motor A+ 2s");
	// MotorA_SetSpeed(Base_Speed);	
	// Delay_ms(2000);
	// Motor_Stop();
	// OLED_ShowString(3, 1, "Motor A- 2s");
	// MotorA_SetSpeed(-Base_Speed);
	// Delay_ms(2000);
	// Motor_Stop();		
	// OLED_ShowString(2, 1, "Motor B+ 2s");
	// MotorB_SetSpeed(Base_Speed);		
	// Delay_ms(2000);
	// Motor_Stop();
	// OLED_ShowString(3, 1, "Motor B- 2s");
	// MotorB_SetSpeed(-Base_Speed);
	// Delay_ms(2000);
	// Motor_Stop();
	// OLED_ShowString(2, 1, "Motor C+ 2s");
    // MotorC_SetSpeed(Base_Speed);
    // // MotorD_SetSpeed(Base_Speed);
	// Delay_ms(2000);
	// Motor_Stop();
	// OLED_ShowString(3, 1, "Motor C- 2s");
	// MotorC_SetSpeed(-Base_Speed);
    // // MotorD_SetSpeed(-Base_Speed);
	// Delay_ms(2000);
	// Motor_Stop();
	// OLED_ShowString(2, 1, "Motor D+ 2s");
	// MotorD_SetSpeed(Base_Speed);	
	// Delay_ms(2000);
	// Motor_Stop();
	// OLED_ShowString(3, 1, "Motor D- 2s");
	// MotorD_SetSpeed(-Base_Speed);
	// Delay_ms(2000);
	// Motor_Stop();
	// OLED_ShowString(2, 1, "Single Test Done!");
	//测试旋转90度
	Delay_ms(2000);
	Rotate_Angle(90.0f, 200); // 顺时针旋转90度
	Delay_ms(1000);
	Rotate_Angle(-90.0f, 200); // 逆时针旋转90度
	Delay_ms(1000);
	OLED_ShowString(2, 1, "Rotation Test Done!");
	Delay_ms(2000);
	OLED_Clear();
	OLED_ShowString(1, 1, "All Tests Done!");
	while (1)
	{
		// 主循环可以添加其他测试代码
	}
}
#include "stm32f10x.h"
#include "Delay.h"
#include "HCSR04.h"

#define Echo GPIO_Pin_3    // HC-SR04模块的Echo脚接GPIOA1/3
#define Trig GPIO_Pin_2    // HC-SR04模块的Trig脚接GPIOA0/2

uint64_t time = 0;        // 声明变量，用来计时
uint64_t time_end = 0;    // 声明变量，存储回波信号时间

void HC_SR04_Timer_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);        // 启用TIM4时钟
    
    TIM_InternalClockConfig(TIM4);                               // 设置TIM4使用内部时钟
    
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;           // 定义结构体，配置定时器
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 设置1分频（不分频）
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 设置计数模式为向上计数
    TIM_TimeBaseInitStructure.TIM_Period = 10 - 1;              // 设置最大计数值，每10微秒触发一次
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;           // 设置时钟预分频，每1微秒+1
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;        // 重复计数器
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);         // 初始化TIM4定时器
    
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);                       // 清除更新中断标志位
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);                  // 开启更新中断
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);             // 设置中断优先级分组
    
    NVIC_InitTypeDef NVIC_InitStructure;                        // 定义结构体，配置中断优先级
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;            // 指定中断通道
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            // 中断使能
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  // 设置抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;         // 设置响应优先级
    NVIC_Init(&NVIC_InitStructure);
    
    TIM_Cmd(TIM4, ENABLE);                                      // 开启定时器
}

void HC_SR04_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);      // 启用GPIOA的外设时钟    
    GPIO_InitTypeDef GPIO_InitStructure;                        // 定义结构体
    
    // 配置Trig引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;           // 设置GPIO口为推挽输出
    GPIO_InitStructure.GPIO_Pin = Trig;                        // 设置GPIO口
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;          // 设置GPIO口速度50Mhz
    GPIO_Init(GPIOA, &GPIO_InitStructure);                     // 初始化GPIOA
    
    // 配置Echo引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;              // 设置GPIO口为下拉输入模式
    GPIO_InitStructure.GPIO_Pin = Echo;                        // 设置GPIO口
    GPIO_Init(GPIOA, &GPIO_InitStructure);                     // 初始化GPIOA
    
    GPIO_WriteBit(GPIOA, GPIO_Pin_2, 0);                      // 输出低电平
    Delay_us(15);                                             // 延时15微秒
    
    HC_SR04_Timer_Init();                                     // 初始化定时器
}

int16_t sonar_mm(void)									//测距并返回单位为毫米的距离结果
{
	uint32_t Distance,Distance_mm = 0;
	GPIO_WriteBit(GPIOA,Trig,1);						//输出高电平
	Delay_us(15);										//延时15微秒
	GPIO_WriteBit(GPIOA,Trig,0);						//输出低电平
	while(GPIO_ReadInputDataBit(GPIOA,Echo)==0);		//等待低电平结束
	time=0;												//计时清零
	while(GPIO_ReadInputDataBit(GPIOA,Echo)==1);		//等待高电平结束
	time_end=time;										//记录结束时的时间
	if(time_end/100<38)									//判断是否小于38毫秒，大于38毫秒的就是超时，直接调到下面返回0
	{
		Distance=(time_end*346)/2;						//计算距离，25°C空气中的音速为346m/s
		Distance_mm=Distance/100;						//因为上面的time_end的单位是10微秒，所以要得出单位为毫米的距离结果，还得除以100
	}
	return Distance_mm;									//返回测距结果
}

float sonar(void)										//测距并返回单位为米的距离结果
{
	uint32_t Distance,Distance_mm = 0;
	float Distance_m=0;
	GPIO_WriteBit(GPIOA,Trig,1);					//输出高电平
	Delay_us(15);
	GPIO_WriteBit(GPIOA,Trig,0);					//输出低电平
	while(GPIO_ReadInputDataBit(GPIOA,Echo)==0);
	time=0;
	while(GPIO_ReadInputDataBit(GPIOA,Echo)==1);
	time_end=time;
	if(time_end/100<38)
	{
		Distance=(time_end*346)/2;
		Distance_mm=Distance/100;
		Distance_m=Distance_mm/1000;
	}
	return Distance_m;
}

void TIM4_IRQHandler(void)			//更新中断函数，用来计时，每10微秒变量time加1
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)		//获取TIM4定时器的更新中断标志位
	{
		time++;
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);			//清除更新中断标志位
	}
}

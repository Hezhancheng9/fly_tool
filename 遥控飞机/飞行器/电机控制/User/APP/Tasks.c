#include "Motor.h"
#include "IMU.h"
#include "Tasks.h"
#include "Maths.h"
#include "Filter.h"
#include "Control.h"
#include "struct_all.h"
#include <stdio.h>
#include <math.h>
uint8_t Bsp_Int_Ok = 0;

/******************************************************************************
函数原型：	void Nvic_Init(void)
功    能：	NVIC初始化
*******************************************************************************/ 
void Nvic_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//NVIC_PriorityGroup 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//优先级分组
    //Timer3
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//先占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//从占优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	//Nrf2401中断
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//串口
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/******************************************************************************
函数原型：	void BSP_Int(void)
功    能：	硬件驱动初始化
*******************************************************************************/


void BSP_Int(void)
{
    
    Motor_Init();

	LED_Init();//LED初始化
	//LED_ON_OFF();//LED闪烁
	
	Uart1_Init(115200);	//串口初始化：波特率115200，8位数据，1位停止位，禁用奇偶校验
	Timer3_Init(1000);	//Timer3中断1KHZ
	Nvic_Init();		//中断优先级初始化	
	
	PrintString("\r\n RagingFire_Fly V2.2.2 \r\n");	//版本号
	
	ADC1_Init();//ADC及DMA初始化

	SPI1_Init();//SPI1初始化
	NRF24L01_Init(50,RX);//2401选择40通道，接收模式
 	NRF24L01_Check(); //检测2401是否正常

	I2C2_Int();//I2C初始化
	while( InitMPU6050()!=1 );//若MPU6050初始化不成功，则程序不向下运行
	Calculate_FilteringCoefficient(0.001f,2.0f);//计算IIR滤波器参数//0.001   10.0

	FLASH_Unlock();//Flash解锁
	EEPROM_INIT();//初始化模拟的EEPROM，读取参数

	Bsp_Int_Ok = 1;
}



/******************************************************************************
函数原型：	void Task_1000HZ(void)
功    能：	主循环中运行频率为1000HZ任务
*******************************************************************************/ 
void Task_1000HZ(void)
{
	static uint8_t ctrl_cnt=0;
	Debug1_H;
	ctrl_cnt++;
	if( MPU6050_SequenceRead()==0 )//若连续读取6050数据寄存器失败
	{
		I2C_Erro++;//统计I2C出错次数
		MPU6050_SingleRead();//分次读MPU6050数据寄存器
	}
	MPU6050_Compose();//6050数据合成
	ACC_IIR_Filter(&acc,&filter_acc);//对acc做IIR滤波
	Gyro_Filter(&gyro,&filter_gyro);//对gyro做窗口滤波
	Get_Radian(&filter_gyro,&SI_gyro);//角速度数据转为弧度
	out_angle.yaw  +=  filter_gyro.z * RawData_to_Angle * 0.001f;
	if(ctrl_cnt==2)
	{
	  ctrl_cnt=0;
		IMUupdate(SI_gyro.x,SI_gyro.y,SI_gyro.z,filter_acc.x,filter_acc.y,filter_acc.z);//姿态解算
	}
	Nrf_Connect();//NRF24L01连接函数
	Debug1_L;
}

/******************************************************************************
函数原型：	void Task_500HZ(void)
功    能：	主循环中运行频率为500HZ任务
*******************************************************************************/ 
void Task_500HZ(void)
{
	Debug2_H;
	Control_Gyro(&SI_gyro,&Rc,Rc_Lock);//内环控制
	Debug2_L;
}

/******************************************************************************
函数原型：	void Task_250HZ(void)
功    能：	主循环中运行频率为250HZ任务
*******************************************************************************/ 
void Task_250HZ(void)
{
	static uint32_t  time4ms_cnt=0;
	
	Debug3_H;
	Get_Eulerian_Angle(&out_angle);//四元数转欧拉角
	Control_Angle(&out_angle,&Rc);//外环控制
	Debug3_L;
	
	time4ms_cnt++;
	if(RF_ok_Flag ==1)
	{
	   //LED2_ON;
		 time4ms_cnt=0;
	}
	else if(fabs(out_angle.pitch)>45 || fabs(out_angle.roll)>45)
	{ 
		 if(time4ms_cnt>10)
			  //LED2_ON;
		 if(time4ms_cnt>20)
		 {
			  //LED2_OFF;
			  time4ms_cnt=0;
		 }
	}
	else
	{
		 
		 if(time4ms_cnt>300)
		 {
			  //LED2_OFF;
			  time4ms_cnt=0;
		 }
	}
}
			

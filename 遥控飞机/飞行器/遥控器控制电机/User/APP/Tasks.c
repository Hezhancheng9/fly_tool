
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
����ԭ�ͣ�	void Nvic_Init(void)
��    �ܣ�	NVIC��ʼ��
*******************************************************************************/ 
void Nvic_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//NVIC_PriorityGroup 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���ȼ�����
    //Timer3
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	//Nrf2401�ж�
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/******************************************************************************
����ԭ�ͣ�	void BSP_Int(void)
��    �ܣ�	Ӳ��������ʼ��
*******************************************************************************/



void BSP_Int(void)
{
	LED_Init();//LED��ʼ��
	//LED_ON_OFF();//LED��˸
	
	Uart1_Init(115200);	//���ڳ�ʼ����������115200��8λ���ݣ�1λֹͣλ��������żУ��
	Timer3_Init(1000);	//Timer3�ж�1KHZ
	Nvic_Init();		//�ж����ȼ���ʼ��	
	
	PrintString("\r\n RagingFire_Fly V2.2.2 \r\n");	//�汾��
	
	ADC1_Init();//ADC��DMA��ʼ��

	SPI1_Init();//SPI1��ʼ��
	NRF24L01_Init(40,RX);//2401ѡ��40ͨ��������ģʽ
 	NRF24L01_Check(); //���2401�Ƿ�����

	I2C2_Int();//I2C��ʼ��
	while( InitMPU6050()!=1 );//��MPU6050��ʼ�����ɹ����������������
	Calculate_FilteringCoefficient(0.001f,2.0f);//����IIR�˲�������//0.001   10.0

	FLASH_Unlock();//Flash����
	EEPROM_INIT();//��ʼ��ģ���EEPROM����ȡ����

	Bsp_Int_Ok = 1;
}



/******************************************************************************
����ԭ�ͣ�	void Task_1000HZ(void)
��    �ܣ�	��ѭ��������Ƶ��Ϊ1000HZ����
*******************************************************************************/ 
void Task_1000HZ(void)
{
	static uint8_t ctrl_cnt=0;
	Debug1_H;
	ctrl_cnt++;
	if( MPU6050_SequenceRead()==0 )//��������ȡ6050���ݼĴ���ʧ��
	{
		I2C_Erro++;//ͳ��I2C�������
		MPU6050_SingleRead();//�ִζ�MPU6050���ݼĴ���
	}
	MPU6050_Compose();//6050���ݺϳ�
	ACC_IIR_Filter(&acc,&filter_acc);//��acc��IIR�˲�
	Gyro_Filter(&gyro,&filter_gyro);//��gyro�������˲�
	Get_Radian(&filter_gyro,&SI_gyro);//���ٶ�����תΪ����
	out_angle.yaw  +=  filter_gyro.z * RawData_to_Angle * 0.001f;
	if(ctrl_cnt==2)
	{
	  ctrl_cnt=0;
		IMUupdate(SI_gyro.x,SI_gyro.y,SI_gyro.z,filter_acc.x,filter_acc.y,filter_acc.z);//��̬����
	}
	Nrf_Connect();//NRF24L01���Ӻ���
	Debug1_L;
}

/******************************************************************************
����ԭ�ͣ�	void Task_500HZ(void)
��    �ܣ�	��ѭ��������Ƶ��Ϊ500HZ����
*******************************************************************************/ 
void Task_500HZ(void)
{
	Debug2_H;
	Control_Gyro(&SI_gyro,&Rc,Rc_Lock);//�ڻ�����
	Debug2_L;
}

/******************************************************************************
����ԭ�ͣ�	void Task_250HZ(void)
��    �ܣ�	��ѭ��������Ƶ��Ϊ250HZ����
*******************************************************************************/ 
void Task_250HZ(void)
{
	static uint32_t  time4ms_cnt=0;
	
	Debug3_H;
	Get_Eulerian_Angle(&out_angle);//��Ԫ��תŷ����
	Control_Angle(&out_angle,&Rc);//�⻷����
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
			

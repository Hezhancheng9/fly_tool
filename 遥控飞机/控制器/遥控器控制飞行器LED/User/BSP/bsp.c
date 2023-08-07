#include "bsp.h"
#include "struct_all.h"
#include "Filter.h"


void LED_Config()
{
    GPIO_InitTypeDef GPIO_Structure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   //开启时钟

    GPIO_Structure.GPIO_Pin =  GPIO_Pin_11;                        //配置管脚
    GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;             //翻转速度
    GPIO_Structure.GPIO_Mode = GPIO_Mode_Out_PP;              //输出模式
    GPIO_Init(GPIOB, &GPIO_Structure); 
}

void delay(uint16_t n)
{
    uint16_t i,j;
    for(i=0;i<n;i++)
        for(j=0;j<8888;j++);
}

void BSP_Init()
{
    ADC1_Init();           //ADC初始化
    SPI2_Init();               //SPI初始化函数
    NRF24L01_Init(40,RX);    //NRF24L01初始化函数
    NRF24L01_Check();        //检测NRF24L01是否正常
} 
void LED_Ctrl()
{
      Rc_Filter(&Rc,&Filter_Rc);                        
      if(Filter_Rc.THROTTLE < 1600) 
      {
          LED2_ON();          //摇杆下摆 LED点亮
      }
        else
           LED2_OFF();                             //摇杆上摆 LED熄灭        
        
       if(Filter_Rc.YAW<1600)
       {
           LED3_ON();
       }else
       {
           LED3_OFF();
       }
}


void RC_transfer(void)             //控制左右遥感偏移量
{
    uint8_t    data[32];

    Rc_Filter(&Rc, &Filter_Rc);    //计算遥控指令+滤波
    if( Filter_Rc.THROTTLE < 1500)    //摇杆上摆 LED点亮
    {
        data[0] = RC_UP;
        NRF_Send_TX( data, 32 );
    }
    else    //摇杆下摆 LED熄灭
    {
        data[0] = RC_DOWN;
        NRF_Send_TX( data, 32 );
    }
}


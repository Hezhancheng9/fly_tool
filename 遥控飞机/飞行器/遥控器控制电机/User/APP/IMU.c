
#include "IMU.h"
#include "math.h"
#include "Maths.h"

// ==================================================================================
// 描述:
// 必须定义'halfT '为周期的一半，以及滤波器的参数Kp和Ki
// 四元数'q0', 'q1', 'q2', 'q3'定义为全局变量
// 需要在每一个采样周期调用'IMUupdate()'函数
// 陀螺仪数据单位是弧度/秒，加速度计的单位无关重要，因为会被规范化
// ==================================================================================
#define Kp 	0.8f    // 比例常数    1.0f---> 0.8f    
#define Ki 	0.002f  // 积分常数    0.001f--->0.002f
#define halfT 0.001f//半周期      0.0005f--->0.001f
#define T	0.002f  // 周期为1ms     0.001f--->0.002f
// ==================================================================================
// 变量定义
float q0 = 1, q1 = 0, q2 = 0, q3 = 0;     	// 四元数
float exInt = 0, eyInt = 0, ezInt = 0;    	// 误差积分累计值 
// ==================================================================================
// 函数原型：void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az) 
// 功        能：互补滤波进行姿态解算
// 输        入：陀螺仪数据及加速度计数据
// ==================================================================================
void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az) 
{
	float norm;
	float vx, vy, vz;
	float ex, ey, ez;
	
  //四元数积分，求得当前的姿态
	float q0_last = q0;	
	float q1_last = q1;	
	float q2_last = q2;	
	float q3_last = q3;	

	//把加速度计的三维向量转成单位向量
	norm = invSqrt(ax*ax + ay*ay + az*az);
	ax = ax * norm;
	ay = ay * norm;
	az = az * norm;

	//估计重力加速度方向在飞行器坐标系中的表示，为四元数表示的旋转矩阵的第三行
	vx = 2*(q1*q3 - q0*q2);
	vy = 2*(q0*q1 + q2*q3);
	vz = q0*q0 - q1*q1 - q2*q2 + q3*q3;

	//加速度计读取的方向与重力加速度方向的差值，用向量叉乘计算
	ex = ay*vz - az*vy;
	ey = az*vx - ax*vz;
	ez = ax*vy - ay*vx;

	//误差累积，已与积分常数相乘
	exInt = exInt + ex*Ki;
	eyInt = eyInt + ey*Ki;
	ezInt = ezInt + ez*Ki;

	//用叉积误差来做PI修正陀螺零偏，即抵消陀螺读数中的偏移量	
	gx = gx + Kp*ex + exInt;
	gy = gy + Kp*ey + eyInt;
	gz = gz + Kp*ez + ezInt;


	//一阶近似算法
	q0 = q0_last + (-q1_last*gx - q2_last*gy - q3_last*gz)*halfT;
	q1 = q1_last + ( q0_last*gx + q2_last*gz - q3_last*gy)*halfT;
	q2 = q2_last + ( q0_last*gy - q1_last*gz + q3_last*gx)*halfT;
	q3 = q3_last + ( q0_last*gz + q1_last*gy - q2_last*gx)*halfT; 

//	//二阶近似算法
//	float delta2 = (gx*gx + gy*gy + gz*gz)*T*T;
//	q0 = q0_last*(1-delta2/8) + (-q1_last*gx - q2_last*gy - q3_last*gz)*halfT;
//	q1 = q1_last*(1-delta2/8) + ( q0_last*gx + q2_last*gz - q3_last*gy)*halfT;
//	q2 = q2_last*(1-delta2/8) + ( q0_last*gy - q1_last*gz + q3_last*gx)*halfT;
//	q3 = q3_last*(1-delta2/8) + ( q0_last*gz + q1_last*gy - q2_last*gx)*halfT;

//	//三阶近似算法
//	float delta2 = (gx*gx + gy*gy + gz*gz)*T*T;
//	q0 = q0_last*(1-delta2/8) + (-q1_last*gx - q2_last*gy - q3_last*gz)*T*(0.5 - delta2/48);
//	q1 = q1_last*(1-delta2/8) + ( q0_last*gx + q2_last*gz - q3_last*gy)*T*(0.5 - delta2/48);
//	q2 = q2_last*(1-delta2/8) + ( q0_last*gy - q1_last*gz + q3_last*gx)*T*(0.5 - delta2/48);
//	q3 = q3_last*(1-delta2/8) + ( q0_last*gz + q1_last*gy - q2_last*gx)*T*(0.5 - delta2/48);

//	//四阶近似算法
//	float delta2 = (gx*gx + gy*gy + gz*gz)*T*T;
//	q0 = q0_last*(1 - delta2/8 + delta2*delta2/384) + (-q1_last*gx - q2_last*gy - q3_last*gz)*T*(0.5 - delta2/48);
//	q1 = q1_last*(1 - delta2/8 + delta2*delta2/384) + ( q0_last*gx + q2_last*gz - q3_last*gy)*T*(0.5 - delta2/48);
//	q2 = q2_last*(1 - delta2/8 + delta2*delta2/384) + ( q0_last*gy - q1_last*gz + q3_last*gx)*T*(0.5 - delta2/48);
//	q3 = q3_last*(1 - delta2/8 + delta2*delta2/384) + ( q0_last*gz + q1_last*gy - q2_last*gx)*T*(0.5 - delta2/48);
			
	//四元数规范化
	norm = invSqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
	q0 = q0 * norm;
	q1 = q1 * norm;
	q2 = q2 * norm;
	q3 = q3 * norm;
	
	//out_angle.yaw  +=  filter_gyro.z * RawData_to_Angle * 0.002f;
}


/******************************************************************************
函数原型：	void Get_Eulerian_Angle(struct _out_angle *angle)
功    能：	四元数转欧拉角
*******************************************************************************/ 
void Get_Eulerian_Angle(struct _out_angle *angle)
{	
	angle->pitch = -atan2(2.0f*(q0*q1 + q2*q3),q0*q0 - q1*q1 - q2*q2 + q3*q3)*Radian_to_Angle;
	angle->roll  =  asin (2.0f*(q0*q2 - q1*q3))*Radian_to_Angle;
}


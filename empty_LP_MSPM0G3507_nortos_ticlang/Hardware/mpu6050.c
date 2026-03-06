#include "ti_msp_dl_config.h"
#include "drv_i2c.h"
#include "mpu6050.h"

#define	SMPLRT_DIV		0x19
#define	MPU_CONFIG		0x1A
#define	GYRO_CONFIG		0x1B
#define	ACCEL_CONFIG	        0x1C
#define	ACCEL_XOUT_H	        0x3B
#define	ACCEL_XOUT_L	        0x3C
#define	ACCEL_YOUT_H	        0x3D
#define	ACCEL_YOUT_L	        0x3E
#define	ACCEL_ZOUT_H	        0x3F
#define	ACCEL_ZOUT_L	        0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B
#define	WHO_AM_I		0x75
#define USER_CTRL		0x6A
#define INT_PIN_CFG		0x37

#define PI 3.1415926535f
#define RtA 57.2957795f  // 弧度转角度
#define AtR 0.0174532925f  // 角度转弧度
 
typedef struct 
{
    float q0, q1, q2, q3;
} Quaternion;
 
Quaternion q = {1.0f, 0.0f, 0.0f, 0.0f};  // 初始化四元数


void I2C_WriteReg(uint8_t DevAddr,uint8_t reg_addr, uint8_t *reg_data, uint8_t count);
void I2C_ReadReg(uint8_t DevAddr,uint8_t reg_addr, uint8_t *reg_data, uint8_t count);


void Single_WriteI2C(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)
{
	I2C_WriteReg(SlaveAddress,REG_Address,&REG_data,1);
}


unsigned char Single_ReadI2C(unsigned char SlaveAddress,unsigned char REG_Address)
{
	uint8_t data;
	I2C_ReadReg(SlaveAddress,REG_Address,&data,1);
	return data;
}

#define imu_adress 0x68

uint8_t read_imu[5];
void mpu6050_init(void)
{
  Single_WriteI2C(imu_adress,PWR_MGMT_1  , 0x00);//�ر������ж�,��������
  Single_WriteI2C(imu_adress,SMPLRT_DIV  , 0x00); // sample rate.  Fsample= 1Khz/(<this value>+1) = 1000Hz
  Single_WriteI2C(imu_adress,MPU_CONFIG  , 0x02); //�ڲ���ͨ�˲�Ƶ�ʣ����ٶȼ�94hz,������98hz
  Single_WriteI2C(imu_adress,GYRO_CONFIG , 0x08);//500deg/s
  Single_WriteI2C(imu_adress,ACCEL_CONFIG, 0x10);// Accel scale 8g (4096 LSB/g)
	
	read_imu[0]=Single_ReadI2C(imu_adress,PWR_MGMT_1);
	read_imu[1]=Single_ReadI2C(imu_adress,SMPLRT_DIV);
	read_imu[2]=Single_ReadI2C(imu_adress,MPU_CONFIG);
	read_imu[3]=Single_ReadI2C(imu_adress,GYRO_CONFIG);
	read_imu[4]=Single_ReadI2C(imu_adress,ACCEL_CONFIG);
}


void mpu6050_read(int16_t *gyro,int16_t *accel,float *temperature)
{
	uint8_t buf[14];
	int16_t temp;
	I2C_ReadReg(imu_adress,ACCEL_XOUT_H,buf,14);
	accel[0]=(int16_t)((buf[0]<<8)|buf[1]);
	accel[1]=(int16_t)((buf[2]<<8)|buf[3]);
	accel[2]=(int16_t)((buf[4]<<8)|buf[5]);	
	temp		=(int16_t)((buf[6]<<8)|buf[7]);
	gyro[0]	=(int16_t)((buf[8]<<8)|buf[9]);
	gyro[1]	=(int16_t)((buf[10]<<8)|buf[11]);
	gyro[2]	=(int16_t)((buf[12]<<8)|buf[13]);	
	*temperature=36.53f+(float)(temp/340.0f);	
}

void NormalizeAccel(float *ax, float *ay, float *az) 
{
    float norm = sqrt(*ax * *ax + *ay * *ay + *az * *az);
    *ax /= norm;
    *ay /= norm;
    *az /= norm;
}

void ComputeError(float ax, float ay, float az, float *error_x, float *error_y, float *error_z) 
{
    float gravity_x = 2 * (q.q1 * q.q3 - q.q0 * q.q2);
    float gravity_y = 2 * (q.q0 * q.q1 + q.q2 * q.q3);
    float gravity_z = 1 - 2 * (q.q1 * q.q1 + q.q2 * q.q2);
 
    *error_x = (ay * gravity_z - az * gravity_y);
    *error_y = (az * gravity_x - ax * gravity_z);
    *error_z = (ax * gravity_y - ay * gravity_x);
}

void UpdateQuaternion(float gx, float gy, float gz, float error_x, float error_y, float error_z, float dt) 
{
    float Kp = 0.5f;  // 互补滤波系数
 
    float q0_dot = -q.q1 * gx - q.q2 * gy - q.q3 * gz;
    float q1_dot = q.q0 * gx - q.q3 * gy + q.q2 * gz;
    float q2_dot = q.q3 * gx + q.q0 * gy - q.q1 * gz;
    float q3_dot = -q.q2 * gx + q.q1 * gy + q.q0 * gz;
 
    q.q0 += (q0_dot + Kp * error_x) * dt;
    q.q1 += (q1_dot + Kp * error_y) * dt;
    q.q2 += (q2_dot + Kp * error_z) * dt;
    q.q3 += (q3_dot) * dt;
 
    // 归一化四元数，避免数值误差会越积越大
    float norm = sqrt(q.q0 * q.q0 + q.q1 * q.q1 + q.q2 * q.q2 + q.q3 * q.q3);
    q.q0 /= norm;
    q.q1 /= norm;
    q.q2 /= norm;
    q.q3 /= norm;
}

void ComputeEulerAngles(float *pitch, float *roll, float *yaw) 
{
    *roll = atan2(2 * (q.q2 * q.q3 + q.q0 * q.q1), q.q0 * q.q0 - q.q1 * q.q1 - q.q2 * q.q2 + q.q3 * q.q3);
    *pitch = asin(-2 * (q.q1 * q.q3 - q.q0 * q.q2));
    *yaw = atan2(2 * (q.q1 * q.q2 + q.q0 * q.q3), q.q0 * q.q0 + q.q1 * q.q1 - q.q2 * q.q2 - q.q3 * q.q3);
 
    *roll *= RtA;  // 弧度转角度
    *pitch *= RtA;
    *yaw *= RtA;
}
 
void GetAngles(float *pitch, float *roll, float *yaw, float dt) 
{
    int16_t accel[3],gyro[3];
	float temperature;
    float ax, ay, az, gx, gy, gz;
    mpu6050_read(gyro, accel, &temperature);
	ax=accel[0];
	ay=accel[1];
	az=accel[2];
    gx=gyro[0];
	gy=gyro[1];
	gz=gyro[2];
	NormalizeAccel(&ax, &ay, &az);
 
    float error_x, error_y, error_z;
    ComputeError(ax, ay, az, &error_x, &error_y, &error_z);
 
    UpdateQuaternion(gx, gy, gz, error_x, error_y, error_z, dt);
 
    ComputeEulerAngles(pitch, roll, yaw);
}

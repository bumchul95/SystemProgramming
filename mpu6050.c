// gcc -o mpu6050 mpu6050.c -lwringPi -lm

#include <wiringPiI2C.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>

// SDA로 아래의 주소들이 들어온다.
// SCL로 동기화를 한다.

#define Device_Address 0x68 //check MPU6050's address from i2cdetect -y -r 1

#define PWR_MGMT_1 0x6B
#define SMPLRT_DIV 0x19
#define CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define INT_ENABLE 0x38
#define ACCEL_XOUT_H 0x3B
#define ACCEL_YOUT_H 0x3D
#define ACCEL_ZOUT_H 0x3F
#define GYRO_XOUT_H 0x43
#define GYRO_YOUT_H 0x45
#define GYRO_ZOUT_H 0x47

int fd;

void MPU6050_Init(){
	wiringPiI2CWriteReg8(fd, SMPLRT_DIV, 0x07);
	wiringPiI2CWriteReg8(fd ,PWR_MGMT_1, 0x01);
	wiringPiI2CWriteReg8(fd, CONFIG, 0);
	wiringPiI2CWriteReg8(fd, GYRO_CONFIG, 24);
	wiringPiI2CWriteReg8(fd, INT_ENABLE, 0x01);
}

short read_raw_data(int addr){
	short high_byte, low_byte, value;
	high_byte = wiringPiI2CReadReg8(fd, addr);
	low_byte = wiringPiI2CReadReg8(fd, addr+1);
	value = (high_byte << 8) | low_byte;
	return value;
}

void ms_delay(int val){
	int i, j;
	for(i = 0; i <= val; i++)
		for(j = 0; j < 1200; j++);
}

int main(void){
	float Acc_x, Acc_y, Acc_z;
	float Gyro_x, Gyro_y, Gyro_z;
	float Ax=0, Ay=0, Az=0;
	float Gx=0, Gy=0, Gz=0;
	fd = wiringPiI2CSetup(Device_Address);
	MPU6050_Init();

	while(1){
		Acc_x = read_raw_data(ACCEL_XOUT_H);
		Acc_y = read_raw_data(ACCEL_YOUT_H);
		Acc_z = read_raw_data(ACCEL_ZOUT_H);

		Gyro_x = read_raw_data(GYRO_XOUT_H);
		Gyro_y = read_raw_data(GYRO_YOUT_H);
		Gyro_z = read_raw_data(GYRO_ZOUT_H);

		Ax = Acc_x / 16384.0;
		Ay = Acc_y / 16384.0;
		Az = Acc_z / 16384.0;

		Gx = Gyro_x/131;
		Gy = Gyro_y/131;
		Gz = Gyro_z/131;

		printf("\n Gx=%.3f Gy=%.3f Gz=%.3f Ax=%.3fg Ay=%.3fg Az=%.3fg\n", Gx, Gy, Gz, Ax, Ay, Az);
		delay(500);
	}

	return 0;
}

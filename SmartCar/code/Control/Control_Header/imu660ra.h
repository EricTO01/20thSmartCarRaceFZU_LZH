#ifndef _IMU660RA_H
#define _IMU660RA_H

int imu660ra_init(void);
int16 get_imu660ra_acc_x();
int16 get_imu660ra_acc_y();
int16 get_imu660ra_acc_z();
int16 get_imu660ra_gyro_x();
int16 get_imu660ra_gyro_y();
int16 get_imu660ra_gyro_z();
void imu660ra_callback();
void IMU_Update(float gx, float gy, float gz, float ax, float ay, float az);
#endif
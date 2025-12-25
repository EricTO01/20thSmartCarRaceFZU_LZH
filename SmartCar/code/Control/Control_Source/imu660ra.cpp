#include "zf_common_headfile.h"
#include "imu660ra.h"
#include <math.h>
#include <iostream>
using namespace std;
#define Kp      10.0f                        // proportional gain governs rate of convergence to accelerometer/magnetometer
#define Ki      0.008f                       // integral gain governs rate of convergence of gyroscope biases
#define halfT   0.001f                   // half the sample period,sapmple freq=500Hz
 
static float q0 = 1, q1 = 0, q2 = 0, q3 = 0;    // quaternion elements representing the estimated orientation
static float exInt = 0, eyInt = 0, ezInt = 0;    // scaled integral error
 
float yaw = 0;
float pitch = 0;
float roll = 0;
// void imu660ra_callback()
// {
//     if(DEV_IMU660RA == imu_type || DEV_IMU660RB == imu_type)
//     {
//         imu_acc_x = imu_get_raw(imu_file_path[ACC_X_RAW]);
//         imu_acc_y = imu_get_raw(imu_file_path[ACC_Y_RAW]);
//         imu_acc_z = imu_get_raw(imu_file_path[ACC_Z_RAW]);
    
//         imu_gyro_x = imu_get_raw(imu_file_path[GYRO_X_RAW]);
//         imu_gyro_y = imu_get_raw(imu_file_path[GYRO_Y_RAW]);
//         imu_gyro_z = imu_get_raw(imu_file_path[GYRO_Z_RAW]);
//     }
//     else if(DEV_IMU963RA == imu_type)
//     {
//         imu_acc_x = imu_get_raw(imu_file_path[ACC_X_RAW]);
//         imu_acc_y = imu_get_raw(imu_file_path[ACC_Y_RAW]);
//         imu_acc_z = imu_get_raw(imu_file_path[ACC_Z_RAW]);
    
//         imu_gyro_x = imu_get_raw(imu_file_path[GYRO_X_RAW]);
//         imu_gyro_y = imu_get_raw(imu_file_path[GYRO_Y_RAW]);
//         imu_gyro_z = imu_get_raw(imu_file_path[GYRO_Z_RAW]);

//         imu_mag_x = imu_get_raw(imu_file_path[MAG_X_RAW]);
//         imu_mag_y = imu_get_raw(imu_file_path[MAG_Y_RAW]);
//         imu_mag_z = imu_get_raw(imu_file_path[MAG_Z_RAW]);
//     }
// }
int imu660ra_init(void)
{
    imu_get_dev_info();
    
    if(DEV_IMU660RA == imu_type)
    {
        printf("IMU DEV IS IMU660RA\r\n");
    }
    else if(DEV_IMU660RB == imu_type)
    {
        printf("IMU DEV IS IMU660RB\r\n");
    }
    else if(DEV_IMU963RA == imu_type)
    {
        printf("IMU DEV IS IMU963RA\r\n");
    }
    else
    {
        printf("NO FIND IMU DEV\r\n");
        return -1;
    }
    
    
}
int16 get_imu660ra_acc_x()
{
    return imu660ra_acc_x;
}
int16 get_imu660ra_acc_y()
{
    return imu660ra_acc_y;
}
int16 get_imu660ra_acc_z()
{
    return imu660ra_acc_z;
}
int16 get_imu660ra_gyro_x()
{
    return imu660ra_gyro_x;
}
int16 get_imu660ra_gyro_y()
{
    return imu660ra_gyro_y;
}
int16 get_imu660ra_gyro_z()
{
    return imu660ra_gyro_z;
}

 
void IMU_Update(float gx, float gy, float gz, float ax, float ay, float az)
{
    float norm;
    float vx, vy, vz;
    float ex, ey, ez;
    float temp0, temp1, temp2, temp3; 
 
    float q0q0 = q0 * q0;
    float q0q1 = q0 * q1;
    float q0q2 = q0 * q2;
    //float q0q3 = q0 * q3;
    float q1q1 = q1 * q1;
    //float q1q2 = q1 * q2;
    float q1q3 = q1 * q3;
    float q2q2 = q2 * q2;
    float q2q3 = q2 * q3;
    float q3q3 = q3 * q3;
 
    if (ax * ay * az == 0)
    {
        return;
    }
 
    norm = sqrt(ax * ax + ay * ay + az * az);       //
    ax = ax / norm;
    ay = ay / norm;
    az = az / norm;
 
    // estimated direction of gravity and flux (v and w)
    vx = 2 * (q1q3 - q0q2);
    vy = 2 * (q0q1 + q2q3);
    vz = q0q0 - q1q1 - q2q2 + q3q3 ;
 
    // error is sum of cross product between reference direction of fields and direction measured by sensors
    ex = (ay * vz - az * vy) ;
    ey = (az * vx - ax * vz) ;
    ez = (ax * vy - ay * vx) ;
 
    exInt = exInt + ex * Ki;
    eyInt = eyInt + ey * Ki;
    ezInt = ezInt + ez * Ki;
 
    // adjusted gyroscope measurements
    gx = gx + Kp * ex + exInt;
    gy = gy + Kp * ey + eyInt;
    gz = gz + Kp * ez + ezInt;
 
    // integrate quaternion rate and normalise
    temp0 = q0;
    temp1 = q1;
    temp2 = q2;
    temp3 = q3;
    q0 += (-temp1 * gx - temp2 * gy - temp3 * gz) * halfT;
    q1 += (temp0 * gx + temp2 * gz - temp3 * gy) * halfT;
    q2 += (temp0 * gy - temp1 * gz + temp3 * gx) * halfT;
    q3 += (temp0 * gz + temp1 * gy - temp2 * gx) * halfT;
 
    // normalise quaternion
    norm = sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
    q0 = q0 / norm;
    q1 = q1 / norm;
    q2 = q2 / norm;
    q3 = q3 / norm;
 
    yaw = atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2 * q2 - 2 * q3 * q3 + 1) * 57.3; // unit:degree
    pitch = asin(-2 * q1 * q3 + 2 * q0 * q2) * 57.3; // unit:degree
    roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2 * q2 + 1) * 57.3; // unit:degree
    // printf("%f",yaw);

}
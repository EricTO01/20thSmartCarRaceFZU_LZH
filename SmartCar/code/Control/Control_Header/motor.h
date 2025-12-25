#ifndef __MOTOR_H
#define __MOTOR_H
#include "zf_common_headfile.h"
#define MOTOR1_DIR   "/dev/zf_driver_gpio_motor_1"
#define MOTOR1_PWM   "/dev/zf_device_pwm_motor_1"

#define MOTOR2_DIR   "/dev/zf_driver_gpio_motor_2"
#define MOTOR2_PWM   "/dev/zf_device_pwm_motor_2"

// void motor_Init(void);
void motor_Run_Left(int16 duty);
void motor_Run_Right(int16 duty);
#endif
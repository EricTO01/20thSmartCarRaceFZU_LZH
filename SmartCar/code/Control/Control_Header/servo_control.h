#ifndef CODE_CAMERA_H_
#define CODE_CAMERA_H_
#include "zf_common_headfile.h"


// 定义驱动路劲，该路劲由设备树生成
#define SERVO_MOTOR1_PWM "/dev/zf_device_pwm_servo"



// 定义主板上舵机活动范围 角度
#define SERVO_MOTOR_L_MAX (75)
#define SERVO_MOTOR_R_MAX (105)
void Servo_Init();
void Set_Servo_angle();
void Set_Servo_duty(uint16 set_servo_duty);
#define SERVO_MOTOR_DUTY(x) ((float)PWM_DUTY_MAX / (1000.0 / (float)SERVO_MOTOR_FREQ) * (0.5 + (float)(x) / 90.0))



#endif

#include "zf_common_headfile.h"

#include "servo_control.h"
// float servo_motor_duty = 90.0; // 舵机动作角度
// float servo_motor_dir = 1;     // 舵机动作状态
struct pwm_info servo_pwm_info;
// 定义主板上舵机频率  请务必注意范围 50-300
// 如果要修改，需要直接修改设备树。
#define SERVO_MOTOR_FREQ (servo_pwm_info.freq)

// 在设备树中，默认设置的10000。如果要修改，需要直接修改设备树。
#define PWM_DUTY_MAX (servo_pwm_info.duty_max)
uint16 servo_duty=0;

void Set_Servo_angle()
{
    // if (servo_duty >= SERVO_MOTOR_R_MAX)
    // {
    //     printf("servo pwm freq too big\r\n");
    // }
    // else if(servo_duty <= SERVO_MOTOR_L_MAX)
    // {
    //     printf("servo pwm freq too small\r\n");
    // }
    //5300 4400
    pwm_set_duty(SERVO_MOTOR1_PWM, servo_duty);
    
}
void Set_Servo_duty(uint16 set_servo_duty)
{
    servo_duty=set_servo_duty;
}
void Servo_pit_callback()
{
    Set_Servo_angle();
}
void Servo_Init()
{
    // // 注册清理函数
    // atexit(cleanup);

    // // 注册SIGINT信号的处理函数
    // signal(SIGINT, sigint_handler);
    Set_Servo_duty(4850);
    // 获取PWM设备信息
    pwm_get_dev_info(SERVO_MOTOR1_PWM, &servo_pwm_info);

    // 打印PWM频率和duty最大值
    printf("servo pwm freq = %d Hz\r\n", servo_pwm_info.freq);
    printf("servo pwm duty_max = %d\r\n", servo_pwm_info.duty_max);
    pit_ms_init(3, Servo_pit_callback);
}

#include "zf_common_headfile.h"
#include "motor.h"
struct pwm_info motor_pwm_info;



#define PWM_MOTOR_DUTY_MAX    (10000)         // 在设备树中，设置的10000。如果要修改，需要与设备树对应。

void motor_Run_Right(int16 duty)
{
    if (duty >= 0) // 正转
    {
        gpio_set_level(MOTOR1_DIR, 0);                         // DIR输出高电平
        pwm_set_duty(MOTOR1_PWM, duty ); // 计算占空比
    }
    else
    {
        gpio_set_level(MOTOR1_DIR, 1);                          // DIR输出低电平
        pwm_set_duty(MOTOR1_PWM, -duty ); // 计算占空比
    }
}
void motor_Run_Left(int16 duty)
{
    if (duty >= 0) // 正转
    {
        gpio_set_level(MOTOR2_DIR, 1);                         // DIR输出高电平
        pwm_set_duty(MOTOR2_PWM, duty ); // 计算占空比
    }
    else
    {
        gpio_set_level(MOTOR2_DIR, 0);                          // DIR输出低电平
        pwm_set_duty(MOTOR2_PWM, -duty ); // 计算占空比
    }
}
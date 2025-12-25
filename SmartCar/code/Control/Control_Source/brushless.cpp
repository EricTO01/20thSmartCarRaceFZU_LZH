#include "zf_common_headfile.h"
#include "brushless.h"
struct pwm_info pwm_brushless1_info;
struct pwm_info pwm_brushless2_info;
uint16 brushless_duty = 0 ;
void brushless_init()
{
    // 获取PWM设备信息
    pwm_get_dev_info(PWM_1, &pwm_brushless1_info);
    pwm_get_dev_info(PWM_2, &pwm_brushless2_info);

    // 打印PWM频率和duty最大值
    printf("pwm 1 freq = %d Hz\r\n", pwm_brushless1_info.freq);
    printf("pwm 1 duty_max = %d\r\n", pwm_brushless1_info.duty_max);

    printf("pwm 2 freq = %d Hz\r\n", pwm_brushless2_info.freq);
    printf("pwm 2 duty_max = %d\r\n", pwm_brushless2_info.duty_max);
}
void brushless_run(uint16 duty)
{

    // 50HZ的周期为20ms

    // 计算无刷电调转速   （1ms - 2ms）/20ms * 10000（10000是PWM的满占空比时候的值）
    // 无刷电调转速 0%   为 500
    // 无刷电调转速 20%  为 600
    // 无刷电调转速 40%  为 700
    // 无刷电调转速 60%  为 800
    // 无刷电调转速 80%  为 900
    // 无刷电调转速 100% 为 1000

    // 修改duty的值，可以修改无刷电调转速

    pwm_set_duty(PWM_1, duty);
    pwm_set_duty(PWM_2, duty);
}
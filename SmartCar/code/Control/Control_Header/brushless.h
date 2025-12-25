#ifndef _brushless_h
#define _brushless_h
#include "zf_common_headfile.h"


#define PWM_1           "/dev/zf_device_pwm_esc_1"
#define PWM_2           "/dev/zf_device_pwm_esc_2"


void brushless_init();
void brushless_run(uint16 duty);
#endif
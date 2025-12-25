#ifndef _ui_h
#define _ui_h
#include <stdint.h>
#include<iostream>
#include "zf_common_headfile.h"
#include "key.h"
#include "beep.h"
/*差和比阈值*/
extern uint16 G_cha_he_bi_threshold;

/*电机速度*/
extern uint16 G_straight_line_speed;
extern uint16 G_curve_line_speed;
extern uint16 G_circle_speed;

/*电机PID*/
extern float G_motor_Kp;
extern float G_motor_Ki;
extern float G_motor_Kd;

extern float G_cha_su_K;
void ui() ;
#endif
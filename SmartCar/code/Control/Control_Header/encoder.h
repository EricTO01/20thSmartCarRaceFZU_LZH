#ifndef __ENCODER_H_
#define __ENCODER_H_
#include "zf_common_headfile.h"


#define ENCODER_1           "/dev/zf_encoder_1"
#define ENCODER_2           "/dev/zf_encoder_2"
void encoder_Init();
int32 encoder_left_value();
int32 encoder_right_value();
#endif
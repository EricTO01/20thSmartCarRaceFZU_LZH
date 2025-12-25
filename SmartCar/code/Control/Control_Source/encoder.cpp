#include "zf_common_headfile.h"
#include "encoder.h"
int32 encoder_left;
int32 encoder_right;
uint64_t encoder_distance=0;
void pit_callback()
{
    encoder_left  = encoder_get_count(ENCODER_1);
    encoder_right = encoder_get_count(ENCODER_2);
    encoder_distance+=encoder_right;
}
void encoder_Init()
{
    pit_ms_init(5, pit_callback);
}
int32 encoder_left_value()
{
    return encoder_left;
}
int32 encoder_right_value()
{
    return encoder_right;
}


#ifndef __KEY_H
#define __KEY_H
#include "zf_common_headfile.h"
#define KEY_0       "/dev/zf_driver_gpio_key_0"
#define KEY_1       "/dev/zf_driver_gpio_key_1"
#define KEY_2       "/dev/zf_driver_gpio_key_2"
#define KEY_3       "/dev/zf_driver_gpio_key_3"
#define SWITCH_0    "/dev/zf_driver_gpio_switch_0"
#define SWITCH_1    "/dev/zf_driver_gpio_switch_1"
bool key0_Press_down();
bool key1_Press_down();
bool key2_Press_down();
bool key3_Press_down();

#endif
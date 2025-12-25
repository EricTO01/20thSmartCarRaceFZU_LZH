#ifndef __BUTTON_H_
#define __BUTTON_H_
#include "zf_common_headfile.h"
#define KEY_0       "/dev/zf_driver_gpio_key_0"
#define KEY_1       "/dev/zf_driver_gpio_key_1"
#define KEY_2       "/dev/zf_driver_gpio_key_2"
#define KEY_3       "/dev/zf_driver_gpio_key_3"
#define SWITCH_0    "/dev/zf_driver_gpio_switch_0"
#define SWITCH_1    "/dev/zf_driver_gpio_switch_1"
uint8 get_Key0_level();
uint8 get_Key1_level();
uint8 get_Key2_level();
uint8 get_Key3_level();
uint8 get_SWITCH_0_level();
uint8 get_SWITCH_1_level();
#endif
#ifndef __BEEP_H_
#define __BEEP_H_
#include "zf_common_headfile.h"
#define BEEP "/dev/zf_driver_gpio_beep"
void beep_on() ;
void beep_off();
#endif
#include "beep.h"

void beep_on()
{
    gpio_set_level(BEEP, 0x1);
}
void beep_off()
{
    gpio_set_level(BEEP, 0x0);
}
#include "button.h"
uint8 get_Key0_level()
{
    return gpio_get_level(KEY_0);
}
uint8 get_Key1_level()
{
    return gpio_get_level(KEY_1);
}
uint8 get_Key2_level()
{
    return gpio_get_level(KEY_2);
}
uint8 get_Key3_level()
{
    return gpio_get_level(KEY_3);
}
uint8 get_SWITCH_0_level()
{
    return gpio_get_level(SWITCH_0);
}
uint8 get_SWITCH_1_level()
{
    return gpio_get_level(SWITCH_1);
}
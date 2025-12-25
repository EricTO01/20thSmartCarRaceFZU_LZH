#include "key.h"
bool key0_Press_down()
{
    if (gpio_get_level(KEY_0)==0)
    {
        system_delay_ms(20);
        // printf("按键0按下");
        while (gpio_get_level(KEY_0)==0);
        system_delay_ms(20);
        return true;
    }
    return false;
}
bool key1_Press_down()
{
    if (gpio_get_level(KEY_1)==0)
    {
        system_delay_ms(20);
        while (gpio_get_level(KEY_1)==0);
        system_delay_ms(20);
        return true;
    }
    return false;
}
bool key2_Press_down()
{
    if (gpio_get_level(KEY_2)==0)
    {
        system_delay_ms(20);
        while (gpio_get_level(KEY_2)==0);
        system_delay_ms(20);
        return true;
    }
    return false;
}
bool key3_Press_down()
{
    if (gpio_get_level(KEY_3)==0)
    {
        system_delay_ms(20);
        while (gpio_get_level(KEY_3)==0);
        system_delay_ms(20);
        return true;
    }
    return false;
}
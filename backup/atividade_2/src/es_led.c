#include "es_led.h"

#include <gpio.h>


int led_init(es_led_t* led, const char* dev_name, u32_t pin)
{
    led->dev   = device_get_binding(dev_name);
    led->pin   = pin;
    led->value = 0;

    gpio_pin_configure(led->dev, pin, GPIO_DIR_OUT | GPIO_POL_INV);
    es_led_off(led);
    return 0;
}

void led_on(es_led_t* led)
{
    led->value = 1;
}

void led_off(es_led_t* led)
{
    led->value = 0;
}

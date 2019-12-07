#include "es_led.h"

#include <gpio.h>

#define es_led_update(led) gpio_pin_write(led->dev, led->pin, led->value)
#define es_led_update_ninja(led, v)                     \
    do {                                                \
        led->value = v;                                 \
        gpio_pin_write(led->dev, led->pin, led->value); \
    } while (0)

void es_led_expiry_function(struct k_timer* timer_id)
{
    printk("Triggered!\n");
    es_led_t* led = CONTAINER_OF(timer_id, struct led_s, timer);
    es_led_toggle(led);
}

int es_led_init(es_led_t* led, const char* dev_name, u32_t pin)
{
    led->dev   = device_get_binding(dev_name);
    led->pin   = pin;
    led->value = 0;

    gpio_pin_configure(led->dev, pin, GPIO_DIR_OUT | GPIO_POL_INV);
    es_led_off(led);
    return 0;
}

void es_led_on(es_led_t* led)
{
    led->value = 1;
    es_led_update(led);
}

void es_led_off(es_led_t* led)
{
    led->value = 0;
    es_led_update(led);
}

void es_led_toggle(es_led_t* led)
{
    es_led_update_ninja(led, !led->value);
}

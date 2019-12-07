#ifndef _ES_LED_H_
#define _ES_LED_H_

#include <device.h>
#include <zephyr/types.h>

typedef struct led_s es_led_t;

struct led_s {
    struct k_timer timer;
    struct device* dev;
    u32_t pin;
    u8_t value;
};

int es_led_init(es_led_t* led, const char* dev_name, u32_t pin);
void es_led_on(es_led_t* led);
void es_led_expiry_function(struct k_timer* timer_id);
void es_led_off(es_led_t* led);
void es_led_toggle(es_led_t* led);

#endif  // _ES_LED_H_
/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <device.h>
#include <gpio.h>
#include <zephyr.h>

#include "es_button.h"
#include "es_led.h"
#include "es_version.h"

#define LED_DEVICE LED0_GPIO_CONTROLLER
#define LED_PIN0 LED0_GPIO_PIN
#define LED_PIN1 LED1_GPIO_PIN
#define LED_PIN2 LED2_GPIO_PIN
#define LED_PIN3 LED3_GPIO_PIN

#define BUTTON_DEVICE SW0_GPIO_CONTROLLER
#define BUTTON_PIN0 SW0_GPIO_PIN
#define BUTTON_PIN1 SW1_GPIO_PIN
#define BUTTON_PIN2 SW2_GPIO_PIN

es_led_t led0       = {0};
es_led_t led1       = {0};
es_led_t led2       = {0};
es_led_t led3       = {0};
es_button_t button1 = {0};
es_button_t button0 = {0};

void es_led2_expiry_function(struct k_timer *timer_id)
{
    es_led_off(&led2);
    es_led_off(&led3);
    printk("LED timout\n");
}

K_TIMER_DEFINE(my_timer, es_led2_expiry_function, NULL);

void button0_callback(struct device *gpiob, struct gpio_callback *cb, u32_t pins)
{
    printk("Button 0 pressed!\n");
    es_led_on(&led2);
    k_timer_start(&my_timer, K_MSEC(500), 0);
}

void button1_callback(struct device *gpiob, struct gpio_callback *cb, u32_t pins)
{
    printk("Button 1 pressed!\n");
    es_led_on(&led3);
    k_timer_start(&my_timer, K_MSEC(500), 0);
}


void main(void)
{
    printk("Firmware version: %d.%d-%d\n", VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD);

    es_led_init(&led0, LED_DEVICE, LED_PIN0);

    es_led_init(&led1, LED_DEVICE, LED_PIN1);
    es_led_on(&led1);

    es_led_init(&led2, LED_DEVICE, LED_PIN2);
    es_led_init(&led3, LED_DEVICE, LED_PIN3);

    es_button_create(&button0, BUTTON_DEVICE, BUTTON_PIN0, button0_callback);
    es_button_create(&button1, BUTTON_DEVICE, BUTTON_PIN1, button1_callback);

    while (1) {
        es_led_toggle(&led0);
        es_led_toggle(&led1);
        k_sleep(K_SECONDS(1));
    }
}

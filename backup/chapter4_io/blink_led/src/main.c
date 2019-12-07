/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <device.h>
#include <gpio.h>
#include <zephyr.h>

#define LED_DEVICE LED0_GPIO_CONTROLLER
#define LED_PIN LED0_GPIO_PIN
#define LED_PIN1 LED1_GPIO_PIN

#define BUTTON_DEVICE SW0_GPIO_CONTROLLER
#define BUTTON_PIN SW0_GPIO_PIN
#define BUTTON_PIN1 SW1_GPIO_PIN
#define BUTTON_PIN2 SW2_GPIO_PIN

/* 1000 msec = 1 sec */
#define SLEEP_TIME 1000

static struct gpio_callback gpio_cb;

void button_pressed(struct device *gpiob, struct gpio_callback *cb, u32_t pins)
{
    u32_t data  = 0;
    u8_t button = 1;
    if (pins & BIT(BUTTON_PIN2)) {
        gpio_pin_read(gpiob, BUTTON_PIN2, &data);
        button = 2;
    } else {
        gpio_pin_read(gpiob, BUTTON_PIN1, &data);
        button = 1;
    }
    if (data) {
        printk("Button %d released\n", button);
    } else {
        printk("Button %d pressed\n", button);
    }
}

void main(void)
{
    u32_t cnt = 0;
    struct device *dev;

    dev = device_get_binding(LED_DEVICE);
    /* Set LED_PIN pin as output */
    gpio_pin_configure(dev, LED_PIN, GPIO_DIR_OUT);
    gpio_pin_configure(dev, LED_PIN1, GPIO_DIR_OUT | GPIO_POL_INV);

    gpio_pin_configure(dev, BUTTON_PIN, GPIO_DIR_IN | GPIO_PUD_PULL_UP | GPIO_POL_INV);

    gpio_pin_configure(dev, BUTTON_PIN1,
                       GPIO_DIR_IN | GPIO_PUD_PULL_UP | GPIO_INT | GPIO_INT_DEBOUNCE
                           | GPIO_INT_EDGE | GPIO_INT_DOUBLE_EDGE);
    gpio_pin_configure(dev, BUTTON_PIN2,
                       GPIO_DIR_IN | GPIO_PUD_PULL_UP | GPIO_INT | GPIO_INT_DEBOUNCE
                           | GPIO_INT_EDGE | GPIO_INT_DOUBLE_EDGE);
    gpio_init_callback(&gpio_cb, button_pressed, BIT(BUTTON_PIN1) | BIT(BUTTON_PIN2));
    gpio_add_callback(dev, &gpio_cb);
    gpio_pin_enable_callback(dev, BUTTON_PIN1);
    gpio_pin_enable_callback(dev, BUTTON_PIN2);

    u32_t data = 0;
    while (1) {
        /* Set pin to HIGH/LOW every 1 second */
        gpio_pin_write(dev, LED_PIN, cnt % 2);
        gpio_pin_write(dev, LED_PIN1, cnt % 2);
        cnt++;
        gpio_pin_read(dev, BUTTON_PIN, &data);
        printk("Button 0 value %d\n", data);
        k_sleep(K_MSEC(SLEEP_TIME));
    }
}

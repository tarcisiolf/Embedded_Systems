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

// Definindo os pinos dos LEDs
#define LED_DEVICE LED0_GPIO_CONTROLLER
#define LED_PIN0 LED0_GPIO_PIN
#define LED_PIN1 LED1_GPIO_PIN
#define LED_PIN2 LED2_GPIO_PIN
#define LED_PIN3 LED3_GPIO_PIN

// Definindo os pinos dos Botões
#define BUTTON_DEVICE SW0_GPIO_CONTROLLER
#define BUTTON_PIN0 SW0_GPIO_PIN
#define BUTTON_PIN1 SW1_GPIO_PIN
#define BUTTON_PIN2 SW2_GPIO_PIN
#define BUTTON_PIN3 SW3_GPIO_PIN

es_led_t led0       = {0};
es_led_t led1       = {0};
es_led_t led2       = {0};
es_led_t led3       = {0};

es_button_t button0 = {0};
es_button_t button2 = {0};
es_button_t button3 = {0};
es_button_t button4 = {0};

void button0_callback(struct device *gpiob, struct gpio_callback *cb, u32_t pins)
{
    printk("Button 0 pressed!\n");
    es_led_on(&led2);
    k_sleep(500);
}

void button1_callback(struct device *gpiob, struct gpio_callback *cb, u32_t pins)
{
    printk("Button 1 pressed!\n");
    es_led_on(&led3);
    k_sleep(500);
}


void button2_callback(struct device *gpiob, struct gpio_callback *cb, u32_t pins)
{
    printk("Button 2 pressed!\n");
    es_led_on(&led3);
    k_sleep(500);
}


void button1_callback(struct device *gpiob, struct gpio_callback *cb, u32_t pins)
{
    printk("Button 3 pressed!\n");
    es_led_on(&led3);
    k_sleep(500);
}

void main(void)
{
    printk("Inicializando LEDs\n");
    led_init(&led0, LED_DEVICE, LED_PIN0);
    led_init(&led1, LED_DEVICE, LED_PIN1);
    led_init(&led2, LED_DEVICE, LED_PIN2);
    led_init(&led3, LED_DEVICE, LED_PIN3);
    printk("LEDS ok\n");

    printk("Inicializando os Botões\n");
    button_create(&button0, BUTTON_DEVICE, BUTTON_PIN0, button0_callback);
    button_create(&button1, BUTTON_DEVICE, BUTTON_PIN1, button1_callback);
    button_create(&button1, BUTTON_DEVICE, BUTTON_PIN2, button2_callback);
    button_create(&button1, BUTTON_DEVICE, BUTTON_PIN3, button3_callback);
    printk("Botões OK\n");
    while (1) {
        k_sleep(500);
    }
}

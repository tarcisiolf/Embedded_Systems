/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <device.h>
#include <drivers/gpio.h>
#include <zephyr.h>

#include "es_button.h"
#include "es_led.h"

// Definindo os pinos dos LEDs
#define LED_DEVICE0 DT_ALIAS_LED0_GPIOS_CONTROLLER
#define LED_DEVICE1 DT_ALIAS_LED1_GPIOS_CONTROLLER
#define LED_DEVICE2 DT_ALIAS_LED2_GPIOS_CONTROLLER
#define LED_DEVICE3 DT_ALIAS_LED3_GPIOS_CONTROLLER
#define LED_PIN0 DT_ALIAS_LED0_GPIOS_PIN 
#define LED_PIN1 DT_ALIAS_LED1_GPIOS_PIN
#define LED_PIN2 DT_ALIAS_LED2_GPIOS_PIN
#define LED_PIN3 DT_ALIAS_LED3_GPIOS_PIN


// Definindo os pinos dos Botões
#define BUTTON_DEVICE DT_ALIAS_SW0_GPIOS_CONTROLLER
#define BUTTON_PIN0 DT_ALIAS_SW0_GPIOS_PIN
#define BUTTON_PIN1 DT_ALIAS_SW1_GPIOS_PIN
#define BUTTON_PIN2 DT_ALIAS_SW2_GPIOS_PIN
#define BUTTON_PIN3 DT_ALIAS_SW3_GPIOS_PIN

#define TIME 500

es_led_t led0       = {0};
es_led_t led1       = {0};
es_led_t led2       = {0};
es_led_t led3       = {0};
es_button_t button0 = {0};
es_button_t button1 = {0};
es_button_t button2 = {0};
es_button_t button3 = {0};

char sequence = 'a';
int activate_sequence0 = 0;
int activate_sequence1 = 0;
int activate_sequence2 = 0;
int activate_sequence3 = 0;

void button0_callback(struct device *gpiob, struct gpio_callback *cb, u32_t pins)
{
    printk("Button 0 pressed!\n");
    sequence = '0';
    activate_sequence0 = ~activate_sequence0;
}

void button1_callback(struct device *gpiob, struct gpio_callback *cb, u32_t pins)
{
    printk("Button 1 pressed!\n");
    sequence = '1';
    activate_sequence1 = ~activate_sequence1;
}

void button2_callback(struct device *gpiob, struct gpio_callback *cb, u32_t pins)
{
    printk("Button 2 pressed!\n");
    sequence = '2';
    activate_sequence2 = ~activate_sequence2;
}

void button3_callback(struct device *gpiob, struct gpio_callback *cb, u32_t pins)
{
    printk("Button 3 pressed!\n");
    sequence = '3';
    activate_sequence3 = ~activate_sequence3;
}

void main(void)
{
    printk("Inicializando LEDs\n");
    led_init(&led0, LED_DEVICE0, LED_PIN0);
    led_init(&led1, LED_DEVICE1, LED_PIN1);
    led_init(&led2, LED_DEVICE2, LED_PIN2);
    led_init(&led3, LED_DEVICE3, LED_PIN3);
    printk("LEDS ok\n");

    printk("Inicializando os Botões\n");
    button_create(&button0, BUTTON_DEVICE, BUTTON_PIN0, button0_callback);
    button_create(&button1, BUTTON_DEVICE, BUTTON_PIN1, button1_callback);
    button_create(&button2, BUTTON_DEVICE, BUTTON_PIN2, button2_callback);
    button_create(&button3, BUTTON_DEVICE, BUTTON_PIN3, button3_callback);
    printk("Botões OK\n");

    set_all_led(&led0, &led1, &led2, &led3, 1);

    while(1)
    {
        k_sleep(TIME);
        switch (sequence)
        {
        case '0':
            printk("Current Sequence [%c] | Value Sequence_0 [%d]\n", sequence, activate_sequence0);
            if(activate_sequence0 == -1)
            {
                set_all_led(&led0, &led1, &led2, &led3, 0);

                printk("Current Sequence [%c]\n", sequence);
                if (sequence == '1' || sequence == '2' || sequence == '3')
                {
                    set_all_led(&led0, &led1, &led2, &led3, 1);
                    break;    
                }
                
                k_sleep(K_MSEC(TIME));

                printk("Current Sequence [%c]\n", sequence);
                if (sequence == '1' || sequence == '2' || sequence == '3')
                {
                    set_all_led(&led0, &led1, &led2, &led3, 1);
                    break;    
                }
                
                set_all_led(&led0, &led1, &led2, &led3, 1);
            }
            
            else if (activate_sequence0 == 0)
            {
                set_all_led(&led0, &led1, &led2, &led3, 1);
            }
            
            break;
        
        case '1':
            printk("Current Sequence [%c] | Value Sequence_1 [%d]\n", sequence, activate_sequence1);
            if(activate_sequence1 == -1)
            {
                turn_leds(&led0, &led1, &led2, &led3, 0, 1, 0, 1);

                printk("Current Sequence [%c]\n", sequence);
                if (sequence == '0' || sequence == '2' || sequence == '3')
                {
                    set_all_led(&led0, &led1, &led2, &led3, 1);
                    break;    
                }

                k_sleep(K_MSEC(TIME));

                printk("Current Sequence [%c]\n", sequence);
                if (sequence == '0' || sequence == '2' || sequence == '3')
                {
                    set_all_led(&led0, &led1, &led2, &led3, 1);
                    break;    
                }

                turn_leds(&led0, &led1, &led2, &led3, 1, 0, 1, 0);
            }
            
            else if (activate_sequence1 == 0)
            {
                set_all_led(&led0, &led1, &led2, &led3, 1);
            }
            
            break;
        
        case '2':
            printk("Current Sequence [%c] | Value Sequence_2 [%d]\n", sequence, activate_sequence2);
            if (activate_sequence2 == -1)
            {
                turn_leds(&led0, &led1, &led2, &led3, 0, 1, 1, 0);

                printk("Current Sequence [%c]\n", sequence);
                if (sequence == '0' || sequence == '1' || sequence == '3')
                {
                    set_all_led(&led0, &led1, &led2, &led3, 1);
                    break;    
                }

                k_sleep(K_MSEC(TIME));

                printk("Current Sequence [%c]\n", sequence);
                if (sequence == '0' || sequence == '1' || sequence == '3')
                {
                    set_all_led(&led0, &led1, &led2, &led3, 1);
                    break;    
                }

                turn_leds(&led0, &led1, &led2, &led3, 1, 0, 0, 1);
            }
            
            else if (activate_sequence2 == 0)
            {
                set_all_led(&led0, &led1, &led2, &led3, 1);
            }
            
            break;

        case '3':
            printk("Current Sequence [%c] | Value Sequence_3 [%d]\n", sequence, activate_sequence3);
            if (activate_sequence3 == -1)
            {
                turn_leds(&led0, &led1, &led2, &led3, 0, 0, 1, 1);

                printk("Current Sequence [%c]\n", sequence);
                if (sequence == '0' || sequence == '1' || sequence == '2')
                {
                    set_all_led(&led0, &led1, &led2, &led3, 1);
                    break;    
                }

                k_sleep(K_MSEC(TIME));

                printk("Current Sequence [%c]\n", sequence);
                if (sequence == '0' || sequence == '1' || sequence == '2')
                {
                    set_all_led(&led0, &led1, &led2, &led3, 1);
                    break;    
                }

                turn_leds(&led0, &led1, &led2, &led3, 1, 1, 0, 0);
            }
          
            else if (activate_sequence3 == 0)
            {
                set_all_led(&led0, &led1, &led2, &led3, 1);
            }           
            
            break;

        default:
        
            break;
        
        }
    }
}


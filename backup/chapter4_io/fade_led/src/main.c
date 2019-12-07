/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file Sample app to demonstrate PWM.
 *
 * This app uses PWM[0].
 */

#include <device.h>
#include <misc/printk.h>
#include <pwm.h>
#include <zephyr.h>

#if defined(CONFIG_PWM_NRF5_SW)
#define PWM_DRIVER CONFIG_PWM_NRF5_SW_0_DEV_NAME
#else
#define PWM_DRIVER DT_NORDIC_NRF_PWM_PWM_0_LABEL
#endif /* CONFIG_PWM_NRF5_SW */
#define PWM_CHANNEL LED0_GPIO_PIN

#define PERIOD (USEC_PER_SEC / 50U)

void main(void)
{
    struct device *pwm_dev;

    printk("PWM demo app-fade LED\n");

    pwm_dev = device_get_binding(PWM_DRIVER);
    if (!pwm_dev) {
        printk("Cannot find %s!\n", PWM_DRIVER);
        return;
    }
    u8_t step = 1;
    while (1) {
        if (pwm_pin_set_usec(pwm_dev, PWM_CHANNEL, PERIOD, (PERIOD / 50) * step)) {
            printk("pwm pin set fails\n");
            return;
        }
        step++;
        if (step == 50) {
            step = 1;
        }
        k_sleep(K_MSEC(50));
    }
}

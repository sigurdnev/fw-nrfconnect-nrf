/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <zephyr.h>
#include <stdio.h>
#include <uart.h>
#include <string.h>

/**@brief Recoverable BSD library error. */
void bsd_recoverable_error_handler(uint32_t err)
{
	printk("bsdlib recoverable error: %u\n", err);
}

/**@brief Irrecoverable BSD library error. */
void bsd_irrecoverable_error_handler(uint32_t err)
{
	printk("bsdlib irrecoverable error: %u\n", err);

	__ASSERT_NO_MSG(false);
}
struct k_timer single_shot_timer;
struct k_timer multi_shot_timer;

static void my_expiry_function_1(struct k_timer *timer)
{
	ARG_UNUSED(timer);
	printk("single_shot_timer expired\n");

}

static void my_expiry_function_2(struct k_timer *timer)
{
	ARG_UNUSED(timer);
	printk("multi_shot_timer expired\n");

}

void main(void)
{
	printk("The kernel timer sample started\n"); // Doc: https://docs.zephyrproject.org/latest/reference/kernel/timing/timers.html

	/* start one single shot timer that expires after 5000 ms */
	/* start one multi shot timer that expires after 5000ms, and then every 5000 ms */
    k_timer_start(&single_shot_timer, K_MSEC(5000),             0);
	k_timer_start(&multi_shot_timer,  K_MSEC(5000), K_MSEC(5000) );
}

K_TIMER_DEFINE(single_shot_timer, my_expiry_function_1, NULL);
K_TIMER_DEFINE(multi_shot_timer,  my_expiry_function_2, NULL);

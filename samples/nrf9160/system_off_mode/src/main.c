/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <zephyr.h>
#include <stdio.h>
#include <uart.h>
#include <string.h>

#include <gpio.h>
#include <hal/nrf_regulators.h>
#include <hal/nrf_gpio.h>
#include <hal/nrf_power.h>
#include <lte_lc.h>
#include <bsd.h>

#define WAKEUP_PIN NRF_GPIO_PIN_MAP(0,31)

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

void main(void)
{
	printk("The AT host sample started\n");
	
	u32_t rr = nrf_power_resetreas_get(NRF_POWER_NS)
	printk("RR: 0x%08x", rr);
	
	if(rr & POWER_RESETREAS_OFF_Msk)
	{
	//Clear all RESETREAS when waking up from System OFF sleep by GPIO.
	nrf_power_resetreas_clear(NRF_POWER_NS, 0x70017);
	}
	
	
	printk("Configuring pin %d as sense input\n",WAKEUP_PIN);
	
	// Due to errata 4, Always configure PIN_CNF[n].INPUT before PIN_CNF[n].SENSE.
	nrf_gpio_cfg_input(WAKEUP_PIN,NRF_GPIO_PIN_PULLUP);
	nrf_gpio_cfg_sense_set(WAKEUP_PIN,NRF_GPIO_PIN_SENSE_LOW);
	
	// We readback the pin config, and print it.
	uint32_t cnf = NRF_P0_NS->PIN_CNF[WAKEUP_PIN];
    NRF_P0_NS->PIN_CNF[WAKEUP_PIN] = cnf | (GPIO_PIN_CNF_SENSE_Low << GPIO_PIN_CNF_SENSE_Pos);
	printk("PIN_CNF register for pin %d is %d \n",WAKEUP_PIN,NRF_P0_NS->PIN_CNF[WAKEUP_PIN]);

	printk("Going to System OFF\n");
	//  The LTE modem also needs to be stopped, 
	//  by issuing a command through the modem API, before entering System OFF mode.
	//  Once the command is issued, one should wait for the modem to respond that it actually has stopped
	//  as there may be a delay until modem is disconnected from the network.
	lte_lc_power_off();
	bsd_shutdown(); // Method to gracefully shutdown the BSD library.
	nrf_regulators_system_off(NRF_REGULATORS_NS);
	
	printk("This should not be printed \n");
}



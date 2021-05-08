/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef _SENSOR_SIM_H_
#define _SENSOR_SIM_H_

/**
 * @file sensor_sim.h
 *
 * @brief Public API for the sensor_sim driver.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <zephyr/types.h>
#include <drivers/sensor.h>
#include <wave_gen.h>

/** @brief Set simulated acceleration parameters.
 *
 * @note	This function can be used only if acceleration is generated as wave signal.
 * @warning	This function is thread-safe, but cannot be used in interrupts.
 *
 * @param[in] chan		Selected sensor channel.
 * @param[in] set_params	Parameters of wave signal.
 *
 * @retval 0 If the operation was successful.
 *           Otherwise, a (negative) error code is returned.
 */
int sensor_sim_set_wave_param(enum sensor_channel chan, const struct wave_gen_param *set_params);

#ifdef __cplusplus
}
#endif

#endif /* _SENSOR_SIM_H_ */

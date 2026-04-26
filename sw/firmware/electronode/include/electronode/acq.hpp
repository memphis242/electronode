/**
 * @file acq.hpp
 * @brief Declares EMG and IMU acquisition module controls.
 * @author Abdulla Almosalami @memphis242
 * @date 2026-04-26
 */

#pragma once

/* C++ standard header includes. */

/* Zephyr header includes. */

/* Public declarations. */

namespace electronode::acq::emg {

/** @brief Start periodic EMG acquisition. */
int start();

/** @brief Stop periodic EMG acquisition. */
int stop();

} // namespace electronode::acq::emg

namespace electronode::acq::imu {

/** @brief Start periodic IMU acquisition. */
int start();

/** @brief Stop periodic IMU acquisition. */
int stop();

} // namespace electronode::acq::imu

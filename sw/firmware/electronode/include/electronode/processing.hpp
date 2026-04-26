/**
 * @file processing.hpp
 * @brief Declares signal-processing worker startup functions.
 * @author Abdulla Almosalami @memphis242
 * @date 2026-04-26
 */

#pragma once

/* C++ standard header includes. */

/* Zephyr header includes. */

/* Local declarations. */

namespace electronode::processing::emg {

/** @brief Start EMG signal processing. */
int start();

} // namespace electronode::processing::emg

namespace electronode::processing::imu {

/** @brief Start the IMU processing worker. */
int start();

} // namespace electronode::processing::imu

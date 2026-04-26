/**
 * @file samples.hpp
 * @brief Defines typed sample records passed between acquisition, processing, and
 *        communication modules.
 * @author Abdulla Almosalami @memphis242
 * @date 2026-04-26
 */

#pragma once

/* C++ standard header includes. */
#include <cstdint>

/* Zephyr header includes. */

/* Local declarations. */

namespace electronode {

/** @brief One timestamped MyoWare envelope sample. */
struct EmgSample {
   /** @brief Device-local timestamp in microseconds. */
   std::uint32_t timestamp_us;

   /** @brief EMG envelope voltage in millivolts. */
   std::int16_t envelope_mv;
};

/** @brief One timestamped inertial sample. */
struct ImuSample {
   /** @brief Device-local timestamp in microseconds. */
   std::uint32_t timestamp_us;

   /** @brief Acceleration vector in mg gravity units (e.g., 1 g of acceleration
    *        == 1000 mg). */
   std::int16_t accel_mg[3];

   /** @brief Angular velocity vector in millidegrees per second units. */
   std::int16_t gyro_mdps[3];
};

/** @brief Compact record queued for BLE transport. */
struct BlePacket {
   /** @brief Device-local timestamp in microseconds. */
   std::uint32_t timestamp_us;

   /** @brief Processed EMG envelope voltage in millivolts. */
   std::int16_t emg_envelope_mv;

   /** @brief Acceleration vector in milligravity units. */
   std::int16_t accel_mg[3];

   /** @brief Angular velocity vector in millidegrees per second units. */
   std::int16_t gyro_mdps[3];
};

} // namespace electronode

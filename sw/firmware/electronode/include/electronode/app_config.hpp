/**
 * @file app_config.hpp
 * @brief Defines application-level sampling rates and queue sizing.
 * @author Abdulla Almosalami @memphis242
 * @date 2026-04-26
 */

#pragma once

/* C++ standard header includes. */
#include <cstddef>
#include <cstdint>

/* Zephyr header includes. */

/* Local declarations. */

namespace electronode {

/** @brief EMG envelope sampling rate in hertz. */
inline constexpr std::uint32_t EMG_SAMPLE_HZ = 1000U;

/** @brief IMU sampling rate in hertz. */
inline constexpr std::uint32_t IMU_SAMPLE_HZ = 100U;

/** @brief Number of EMG samples buffered between acquisition and processing. */
inline constexpr std::size_t EMG_QUEUE_DEPTH = 32U;

/** @brief Number of IMU samples buffered between acquisition and processing. */
inline constexpr std::size_t IMU_QUEUE_DEPTH = 16U;

/** @brief Number of processed packets buffered before BLE transmission. */
inline constexpr std::size_t PACKET_QUEUE_DEPTH = 16U;

} // namespace electronode

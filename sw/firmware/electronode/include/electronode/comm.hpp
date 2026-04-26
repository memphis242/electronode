/**
 * @file comm.hpp
 * @brief Declares BLE transport startup and packet submission.
 * @author Abdulla Almosalami @memphis242
 * @date 2026-04-26
 */

#pragma once

/* C++ standard header includes. */

/* Zephyr header includes. */

/* Local header includes. */
#include "samples.hpp"

/* Local declarations. */

namespace electronode::ble {

/** @brief Initialize BLE and begin advertising. */
int start();

/** @brief Queue a processed packet for BLE transmission. */
int submit(const BlePacket& pkt);

} // namespace electronode::ble

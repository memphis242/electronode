/**
 * @file supervisor.hpp
 * @brief Declares the top-level application supervisor entry point.
 * @author Abdulla Almosalami @memphis242
 * @date 2026-04-26
 */

#pragma once

/* C++ standard header includes. */

/* Zephyr header includes. */

/* Local declarations. */

namespace electronode::supervisor {

/** @brief Start firmware subsystems in supervisor-defined order. */
int start();

} // namespace electronode::supervisor

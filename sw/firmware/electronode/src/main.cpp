/**
 * @file main.cpp
 * @brief Provides the Zephyr application entry point and starts the supervisor.
 * @author Abdulla Almosalami @memphis242
 * @date 2026-04-26
 */

/* C++ standard header includes. */

/* Zephyr header includes. */
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

/* Local header includes. */
#include <electronode/supervisor.hpp>

/* Local declarations. */

/** @brief Logging module for the application entry point. */
LOG_MODULE_REGISTER( electronode_main );

/* Public function/class/struct implementation. */

int main(void)
{
   LOG_INF( "electronode firmware starting" );

   return electronode::supervisor::start();
}

/* Local implementations. */

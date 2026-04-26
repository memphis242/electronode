/**
 * @file supervisor.cpp
 * @brief Coordinates startup of BLE, processing, and acquisition modules.
 * @author Abdulla Almosalami @memphis242
 * @date 2026-04-26
 */

/* C++ standard header includes. */

/* Zephyr header includes. */
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

/* Local header includes. */
#include <electronode/acq.hpp>
#include <electronode/comm.hpp>
#include <electronode/processing.hpp>
#include <electronode/supervisor.hpp>

/* Local declarations. */

/** @brief Logging module for supervisor state transitions. */
LOG_MODULE_REGISTER( electronode_supervisor );

/* Public function/class/struct implementation. */

namespace electronode::supervisor {

int start()
{
   int err;

   err = ble::start();
   if (err != 0) {
      return err;
   }

   err = processing::emg::start();
   if (err != 0) {
      return err;
   }

   err = processing::imu::start();
   if (err != 0) {
      return err;
   }

   err = acq::emg::start();
   if (err != 0) {
      return err;
   }

   err = acq::imu::start();
   if (err != 0) {
      return err;
   }

   LOG_INF( "electronode supervisor running" );
   return 0;
}

} // namespace electronode::supervisor

/* Local implementations. */

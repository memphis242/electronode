/**
 * @file emg.cpp
 * @brief Consumes EMG samples and prepares processed packets for BLE transport.
 * @author Abdulla Almosalami @memphis242
 * @date 2026-04-26
 */

/* C++ standard header includes. */

/* Zephyr header includes. */
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

/* Local header includes. */
#include <electronode/app_config.hpp>
#include <electronode/comm.hpp>
#include <electronode/processing.hpp>
#include <electronode/samples.hpp>

/* Local declarations. */

/** @brief Logging module for EMG processing. */
LOG_MODULE_REGISTER( electronode_emg_proc );

/** @brief EMG sample queue owned by the EMG acquisition module. */
extern struct k_msgq s_electronode_emg_msgq;

/** @brief Consume EMG samples and submit processed packets to BLE. */
static void emg_processing_thread(void);

/** @brief Kernel thread used for EMG processing. */
K_THREAD_DEFINE( s_emg_processing_tid,
                 1024,
                 emg_processing_thread,
                 nullptr,
                 nullptr,
                 nullptr,
                 5,
                 0,
                 K_FOREVER );

/* Public function/class/struct implementation. */

namespace electronode::processing::emg {

int start()
{
   k_thread_start( s_emg_processing_tid );
   LOG_INF( "EMG processing thread started" );
   return 0;
}

} // namespace electronode::processing::emg

/* Local implementations. */

static void emg_processing_thread(void)
{
   electronode::EmgSample sample;

   while (true) {
      k_msgq_get( &s_electronode_emg_msgq,
                  &sample,
                  K_FOREVER );

      electronode::BlePacket pkt = {
         .timestamp_us = sample.timestamp_us,
         .emg_envelope_mv = sample.envelope_mv,
         .accel_mg = { 0, 0, 0 },
      };

      (void)electronode::ble::submit( pkt );
   }
}

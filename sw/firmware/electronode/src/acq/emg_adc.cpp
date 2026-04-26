/**
 * @file emg_adc.cpp
 * @brief Produces periodic MyoWare EMG envelope samples for processing.
 * @author Abdulla Almosalami @memphis242
 * @date 2026-04-26
 */

/* C++ standard header includes. */
#include <cstdint>

/* Zephyr header includes. */
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

/* Local header includes. */
#include <electronode/acq.hpp>
#include <electronode/app_config.hpp>
#include <electronode/samples.hpp>

/* Local declarations. */

/** @brief Logging module for EMG acquisition. */
LOG_MODULE_REGISTER( electronode_emg_acq );

/** @brief Queue of EMG samples produced by acquisition and consumed by
 *        processing. */
K_MSGQ_DEFINE( s_electronode_emg_msgq,
               sizeof( electronode::EmgSample ),
               electronode::EMG_QUEUE_DEPTH,
               sizeof( std::uint32_t ) );

/** @brief Delayable work item used to model periodic EMG sampling. */
static struct k_work_delayable s_emg_sample_work;

/** @brief Flag indicating whether EMG acquisition should continue scheduling
 *        itself. */
static bool s_emg_enabled;

/** @brief Capture one placeholder EMG sample and reschedule the next sample. */
static void emg_sample(struct k_work *work);

/* Public function/class/struct implementation. */

namespace electronode::acq::emg {

int start()
{
   s_emg_enabled = true;
   k_work_init_delayable( &s_emg_sample_work, emg_sample );
   k_work_schedule( &s_emg_sample_work, K_NO_WAIT );
   LOG_INF( "EMG acquisition started" );
   return 0;
}

int stop()
{
   s_emg_enabled = false;
   (void)k_work_cancel_delayable( &s_emg_sample_work );
   LOG_INF( "EMG acquisition stopped" );
   return 0;
}

} // namespace electronode::acq::emg

/* Local implementations. */

static void emg_sample(struct k_work *work)
{
   ARG_UNUSED( work );

   if (!s_emg_enabled) {
      return;
   }

   electronode::EmgSample sample = {
      .timestamp_us = k_ticks_to_us_floor32( k_uptime_ticks() ),
      .envelope_mv = 0,
   };

   (void)k_msgq_put( &s_electronode_emg_msgq,
                     &sample,
                      K_NO_WAIT );

   k_work_reschedule( &s_emg_sample_work,
                       K_USEC( 1000000 / electronode::EMG_SAMPLE_HZ ) );
}

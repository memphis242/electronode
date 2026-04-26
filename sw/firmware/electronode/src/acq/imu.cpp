/**
 * @file imu.cpp
 * @brief Produces periodic IMU samples for motion processing.
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

/** @brief Logging module for IMU acquisition. */
LOG_MODULE_REGISTER( electronode_imu_acq );

/** @brief Queue of IMU samples produced by acquisition and consumed by
 *        processing. */
K_MSGQ_DEFINE( s_electronode_imu_msgq,
               sizeof( electronode::ImuSample ),
               electronode::IMU_QUEUE_DEPTH,
               sizeof( std::uint32_t ) );

/** @brief Delayable work item used to model periodic IMU sampling. */
static struct k_work_delayable s_imu_sample_work;

/** @brief Flag indicating whether IMU acquisition should continue scheduling
 *        itself. */
static bool s_imu_enabled;

/** @brief Capture one placeholder IMU sample and reschedule the next sample. */
static void imu_sample(struct k_work *work);

/* Public function/class/struct implementation. */

namespace electronode::acq::imu {

int start()
{
   s_imu_enabled = true;
   k_work_init_delayable( &s_imu_sample_work, imu_sample );
   k_work_schedule( &s_imu_sample_work, K_NO_WAIT );
   LOG_INF( "IMU acquisition started" );
   return 0;
}

int stop()
{
   s_imu_enabled = false;
   (void)k_work_cancel_delayable( &s_imu_sample_work );
   LOG_INF( "IMU acquisition stopped" );
   return 0;
}

} // namespace electronode::acq::imu

/* Local implementations. */

static void imu_sample(struct k_work *work)
{
   ARG_UNUSED( work );

   if (!s_imu_enabled) {
      return;
   }

   electronode::ImuSample sample = {
      .timestamp_us = k_ticks_to_us_floor32( k_uptime_ticks() ),
      .accel_mg = { 0, 0, 0 },
      .gyro_mdps = { 0, 0, 0 },
   };

   (void)k_msgq_put( &s_electronode_imu_msgq,
                      &sample,
                      K_NO_WAIT );
   k_work_reschedule( &s_imu_sample_work,
                       K_USEC( 1000000 / electronode::IMU_SAMPLE_HZ ) );
}

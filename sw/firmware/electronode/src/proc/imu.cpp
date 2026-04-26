/**
 * @file imu.cpp
 * @brief Consumes IMU samples and hosts placeholder motion processing.
 * @author Abdulla Almosalami @memphis242
 * @date 2026-04-26
 */

/* C++ standard header includes. */

/* Zephyr header includes. */
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

/* Local header includes. */
#include <electronode/processing.hpp>
#include <electronode/samples.hpp>

/* Local declarations. */

/** @brief Logging module for IMU processing. */
LOG_MODULE_REGISTER( electronode_imu_proc );

/** @brief IMU sample queue owned by the IMU acquisition module. */
extern struct k_msgq s_electronode_imu_msgq;

/** @brief Consume IMU samples for future motion processing. */
static void imu_processing_thread(void);

/** @brief Kernel thread used for IMU processing. */
K_THREAD_DEFINE( s_imu_processing_tid,
                 1024,
                 imu_processing_thread,
                 nullptr,
                 nullptr,
                 nullptr,
                 5,
                 0,
                 K_FOREVER );

/* Public function/class/struct implementation. */

namespace electronode::processing::imu {

int start()
{
   k_thread_start( s_imu_processing_tid );
   return 0;
}

} // namespace electronode::processing::imu

/* Local implementations. */

static void imu_processing_thread(void)
{
   electronode::ImuSample sample;

   for (;;) {
      k_msgq_get( &s_electronode_imu_msgq,
                  &sample,
                  K_FOREVER );
      LOG_DBG( "IMU sample %u us",
               sample.timestamp_us );
   }
}

/**
 * @file ble.cpp
 * @brief Owns BLE initialization, advertising, and outgoing packet queuing.
 * @author Abdulla Almosalami @memphis242
 * @date 2026-04-26
 */

/* C++ standard header includes. */
#include <cstdint>

/* Zephyr header includes. */
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

/* Local header includes. */
#include <electronode/app_config.hpp>
#include <electronode/comm.hpp>
#include <electronode/samples.hpp>

/* Local declarations. */

/** @brief Logging module for BLE transport. */
LOG_MODULE_REGISTER( electronode_ble );

/** @brief Queue of processed packets awaiting BLE transport. */
K_MSGQ_DEFINE( s_electronode_ble_packet_msgq,
               sizeof( electronode::BlePacket ),
               electronode::PACKET_QUEUE_DEPTH,
               sizeof( std::uint32_t ) );

/** @brief Connectable advertising payload for the prototype firmware. */
static const struct bt_data s_adv_data[] = {
   BT_DATA_BYTES( BT_DATA_FLAGS, ( BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR ) ),
   BT_DATA( BT_DATA_NAME_COMPLETE,
            CONFIG_BT_DEVICE_NAME,
            sizeof( CONFIG_BT_DEVICE_NAME ) - 1 ),
};

/** @brief Consume queued packets and hand them to the BLE transport path. */
static void ble_thread(void);

/** @brief Kernel thread used for BLE packet handling. */
K_THREAD_DEFINE( s_ble_tid,
                 1536,
                 ble_thread,
                 nullptr,
                 nullptr,
                 nullptr,
                 5,
                 0,
                 K_FOREVER );

/* Public function/class/struct implementation. */

namespace electronode::ble {

int start()
{
   int err = bt_enable( nullptr );

   if (err != 0) {
      LOG_ERR( "Bluetooth init failed: %d", err );
      return err;
   }

   err = bt_le_adv_start(
      BT_LE_ADV_CONN,
      s_adv_data,
      ARRAY_SIZE( s_adv_data ),
      nullptr,
      0 );
   if (err != 0) {
      LOG_ERR( "Bluetooth advertising failed: %d", err );
      return err;
   }

   k_thread_start( s_ble_tid );
   LOG_INF( "Bluetooth advertising started" );
   return 0;
}

int submit(const BlePacket& pkt)
{
   return k_msgq_put( &s_electronode_ble_packet_msgq,
                      &pkt,
                      K_NO_WAIT );
}

} // namespace electronode::ble

/* Local implementations. */

static void ble_thread(void)
{
   electronode::BlePacket packet;

   for (;;) {
      k_msgq_get( &s_electronode_ble_packet_msgq,
                  &packet,
                  K_FOREVER );
      LOG_DBG( "BLE packet %u us EMG=%d mV",
               packet.timestamp_us,
               packet.emg_envelope_mv );
   }
}

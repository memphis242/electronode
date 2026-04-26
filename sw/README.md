# Software

This directory will hold firmware, host tools, and signal-processing code.

## Phase 1

Default target:

- Board: Silicon Labs BGM220 Explorer Kit (`BGM220-EK4314A`)
- Zephyr board target: `bgm220_ek4314a`
- MCU/module: `BGM220PC22HNA` module with EFR32BG22 SoC

Initial firmware responsibilities:

- Sample MyoWare envelope output through an ADC input
- Sample an IMU over I2C or SPI
- Timestamp samples on-device
- Advertise or stream compact sample packets over BLE
- Expose basic battery and firmware version metadata once power hardware exists

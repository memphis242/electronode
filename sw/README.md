# Software

This directory will hold firmware, host tools, tests, and more.

## Phase 1
To restate the goal of phase 1, I want to get a prototype going that demonstrates
the basic functionality that electronode will offer. To that end, I will take
advantage of pre-existing platforms and tooling.

- Zephyr will be used for the underlying OS and library ecosystem
   - aside from being an RTOS, it comes with a BLE stack along with many OS
     niceties (e.g., logging, configurable board overlays, etc.)
   - supports QEMU emulation for good "HIL"-like automated testing
   - it has a Linux system programming feel to it, which I like
   - super well documented
   - supports the production-grade bluetooth hardware options out there
- MCU/module: `BGM220PC22HNA` module with EFR32BG22 SoC
- Board: Silicon Labs BGM220 Explorer Kit (`BGM220-EK4314A`)
- Zephyr board target: `bgm220_ek4314a`

Initial firmware responsibilities:

- Sample MyoWare envelope output through an ADC input
- Sample an IMU over I2C or SPI
- Timestamp samples on-device
- Advertise or stream compact sample packets over BLE
- Expose basic battery and firmware version metadata once power hardware exists

## Firmware Directory Structure

The initial Zephyr electronode app lives in `firmware/electronode/`. Other apps
that will come will include a bootloader application under `firmware/bootloader/`
and possibly other related apps.

It is organized around a supervisor, acquisition producers, processing consumers,
and a BLE transport boundary.

Build from a Zephyr workspace with:

```sh
west build -b bgm220_ek4314a sw/firmware/electronode
```

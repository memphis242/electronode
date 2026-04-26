# Electronode Zephyr Firmware

This is the Phase 1 Zephyr application skeleton for a single wireless EMG node.

## Current Target

- Board: Silicon Labs BGM220 Explorer Kit
- Zephyr board target: `bgm220_ek4314a`
- EMG input: MyoWare 2.0 envelope output into an MCU ADC channel
- IMU input: I2C or SPI IMU breakout, likely BMI270-class
- Radio path: BLE peripheral advertising plus later GATT notifications

## Layout

- `src/main.c`: app entry point
- `src/sys/`: supervisor/state orchestration
- `src/acq/`: EMG and IMU acquisition producers
- `src/proc/`: signal-processing consumers
- `src/comm/`: BLE transport boundary
- `include/electronode/`: shared application interfaces and data records
- `boards/`: board overlays declaring specific ADC/IMU pin selections

## Build

From a Zephyr workspace with this repository available as an application:

```sh
west build -b bgm220_ek4314a sw/firmware/electronode
```

If the project is built from inside `sw/firmware/electronode`, use:

```sh
west build -b bgm220_ek4314a .
```

The skeleton is intentionally not expected to produce useful sensor output yet.
The next firmware step is assigning the ADC channel and IMU bus in a board
overlay, then replacing placeholder sample generation with real driver calls.

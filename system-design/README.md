# System Design

This directory tracks the system architecture for `electronode`.

## Phase 1 Baseline

Goal: demonstrate a small wireless node that samples muscle activity and motion,
      then broadcast usable data over BLE.

Initial signal path:

```text
surface electrodes -> MyoWare 2.0 EMG front end -> BGM220 Explorer ADC
IMU -> BGM220 Explorer I2C/SPI
BGM220 Explorer -> BLE stream -> host tools
```

Initial choices:

- EMG: MyoWare 2.0 envelope output first
- Motion: low-power IMU on I2C/SPI (probably Bosch BMI270)
- MCU/radio: Silicon Labs BGM220 Explorer Kit
- Firmware: Zephyr
- Data: timestamped EMG envelope samples plus IMU samples

## Design Principles

- Prefer well-established modules during proof-of-concept work
- Move analog complexity into later phases after data capture works

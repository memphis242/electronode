# Electronode Zephyr Firmware

This is the Phase 1 Zephyr application skeleton for a single wireless EMG node.
Application code is written in C++20 while still using Zephyr's C APIs directly.

## Current Target

- Board: Silicon Labs BGM220 Explorer Kit
- Zephyr board target: `bgm220_ek4314a`
- EMG input: MyoWare 2.0 envelope output into an MCU ADC channel
- IMU input: I2C or SPI IMU breakout, likely BMI270-class
- Radio path: BLE peripheral advertising plus later GATT notifications

## Layout

- `src/main.cpp`: app entry point
- `src/sys/`: supervisor/state orchestration
- `src/acq/`: EMG and IMU acquisition producers
- `src/proc/`: signal-processing consumers
- `src/comm/`: BLE transport boundary
- `include/electronode/`: shared application interfaces and data records
- `boards/`: board overlays declaring specific ADC/IMU pin selections

Module APIs use C++ namespaces, for example `electronode::supervisor::start()`
and `electronode::ble::submit()`. Keep a module as namespaced functions while it
has one static Zephyr-backed instance; introduce a class when there are multiple
instances or meaningful constructor-owned state.

## Build

From a Zephyr workspace with this repository available as an application:

```sh
west build -b bgm220_ek4314a sw/firmware/electronode
```

If the project is built from inside `sw/firmware/electronode`, use:

```sh
west build -b bgm220_ek4314a .
```

## Why C++20?
I enjoy the many modern language features that C++ offers, like strong
compile-time support, classes, extensive standard library, strong typing, RAII,
lambdas, generics through templates, namespaces, and more. C is in my heart forever,
but I gotta go C++ once in a while!

## C++ Notes

Zephyr supports C++ application code when `CONFIG_CPP=y` is enabled. This app
also selects `CONFIG_STD_CPP20=y`, and its implementation files use the `.cpp`
suffix so Zephyr builds them with the C++ compiler.

Keep C++ in application code rather than Zephyr kernel, driver, or system
initialization code. For now, avoid depending on the full C++ standard library;
add that deliberately later if features like `std::vector` or `std::string` are
needed.

Reference: [Zephyr C++ Language Support docs](https://docs.zephyrproject.org/latest/develop/languages/cpp/index.html)

# Hardware Survey

Just like the [system-design/README.md](../system-design/README.md) mentions, the
electronodes are made of three primary components:

1. the electrode: senses the muscle electrical activity and produces a faint
                  corresponding voltage
2. the amplifier: amplifies the faint signal from the electrode to a quality
                  signal that ADCs can sample
3. the MCU: controls the sampling and broadcasts the data wirelessly

This document records the survey of options for each of these components.

## Initial Survey for the Prototype (Phase 1)

I'll start with the [MyoWare 2.0](https://www.sparkfun.com/myoware-2-muscle-sensor.html#content-documentation)
as the EMG sensor + amplifier alongside the Silicon Labs BGM220 Explorer Kit for
MCU. This keeps the first milestone focused on BLE streaming, sampling, power
measurement, and basic usability.

## Electrodes

- Start: disposable snap surface EMG/ECG electrodes connected directly to the
         MyoWare 2.0 sensor
- Add when needed: MyoWare Cable Shield or Reference Cable for muscles where the
                   board geometry or reference placement is poor
- Later: evaluate reusable dry electrodes only after the signal chain and placement
         procedure are understood

## Amplifier / Analog Front End

- MyoWare 2.0 Muscle Sensor: good first choice because it exposes envelope, raw,
                             and rectified modes and is designed for MCU ADC use
- TI ADS1292R: candidate custom front end for one or two high-resolution
               biopotential channels over SPI
- TI ADS1299: candidate when multi-channel simultaneous biopotential sampling
              becomes important; too much complexity for Phase 1
- Analog Devices AD8232: integrated low-power biopotential front end worth studying,
                         but ECG-oriented rather than EMG
- Analog Devices AD8237: low-power instrumentation amplifier candidate for a custom
                         EMG analog design, not a complete EMG front end by itself.

## MCU / SoC / SoM

- Silicon Labs BGM220 Explorer Kit: good Phase 1 option
  - BG22-based (so low-power, solid vendor)
  - module-oriented
  - low-cost
  - supported by Zephyr as `bgm220_ek4314a`.

- Silicon Labs EFR32BG22 custom SoC design: potential future option
  - BGM220 is basically this but with all the RF integrated
  - could be an option if RF integration cost, size, or layout control outweigh
    module certification convenience

- Nordic nRF52840: strong candidate
  - mature BLE SoC with strong ecosystem and more memory
  - but I kinda wanna try Silicon Labs...

- Nordic nRF54L15:
  - strong future low-power BLE candidate
  - but newer and not needed for the first proof-of-concept

- TI CC2340R5: decent option
  - low-cost BLE MCU candidate with Zephyr support
  - useful for cost comparison later

- Espressif ESP32-C3:
  - probably the most popular wireless option, but BLE + Wi-Fi is more than necessary
  - that said, turning off Wi-Fi likely gives very comparable power consumption figures

## IMU

Keep the first IMU integration modular so another I2C/SPI breakout can replace it
without changing the EMG path.

- Bosch BMI270: practical low-power wearable IMU candidate for early evaluation

## Sources

- Silicon Labs BGM220 Explorer Kit: https://www.silabs.com/development-tools/wireless/bluetooth/bgm220-explorer-kit
- Zephyr BGM220 board docs: https://docs.zephyrproject.org/latest/boards/silabs/explorer_kits/xg22/doc/bgm220_ek4314a.html
- MyoWare 2.0 specs: https://myoware.com/products/technical-specifications/
- SparkFun MyoWare 2.0 guide: https://learn.sparkfun.com/tutorials/getting-started-with-the-myoware-20-muscle-sensor-ecosystem/all
- SparkFun MyoWare Cable Shield: https://www.sparkfun.com/products/18386
- TI ADS1292R: https://www.ti.com/product/ADS1292R
- TI ADS1299: https://www.ti.com/product/ADS1299
- Analog Devices AD8232: https://www.analog.com/en/products/ad8232.html
- Analog Devices AD8237: https://www.analog.com/en/products/ad8237.html
- Nordic nRF52840: https://www.nordicsemi.com/Products/nRF52840
- Nordic nRF54L15: https://www.nordicsemi.com/Products/nRF54L15
- TI CC2340R5: https://www.ti.com/product/CC2340R5
- Espressif ESP32-C3: https://docs.espressif.com/projects/esp-hardware-design-guidelines/en/latest/esp32c3/product-overview.html

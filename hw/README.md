# Hardware

This directory will hold hardware design notes, schematics, PCB work, and bring-up
logs.

## Phase 1

Default proof-of-concept stack:

- Electrodes: disposable surface EMG/ECG snap electrodes compatible with MyoWare
- EMG front end: MyoWare 2.0 Muscle Sensor, envelope output first
- MCU/radio: Silicon Labs BGM220 Explorer Kit
- Motion: small low-power IMU breakout, likely on I2C for first bring-up
- Power: battery-powered only for any human-contact experiment

## Future Hardware Direction

- Replace the dev board with a battery-powered custom PCB
- Evaluate whether a certified module remains preferable to a raw SoC RF design
- Replace the MyoWare module with a custom analog front end after the data path
  is working
- Design electrode placement, strain relief, enclosure, and isolation as first-class
  wearable constraints

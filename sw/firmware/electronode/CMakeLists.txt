cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(electronode LANGUAGES C CXX) # C++20 will the app code's language

# I'm avoiding set(CMAKE_CXX_STANDARD 20) and set(CMAKE_CXX_STANDARD_REQUIRED ON)
# because it seems like in Zephyr, the preferred way of setting the C++ language
# is Kconfig (i.e., prj.conf):
#   CONFIG_CPP=y
#   CONFIG_STD_CPP20=y
# That lets Zephyr’s build system select the correct compiler flags consistently
# with the toolchain, board, and SDK, and shall remain the single source-of-truth.

target_include_directories(app PRIVATE include)

target_sources(app PRIVATE
  src/main.cpp
  src/acq/emg_adc.cpp
  src/acq/imu.cpp
  src/proc/emg.cpp
  src/proc/imu.cpp
  src/comm/ble.cpp
  src/sys/supervisor.cpp
)

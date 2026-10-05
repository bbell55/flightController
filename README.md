# flightController
A flight controller for a V-tail fixed-wing RC plane, written in C++ for an STM32F411. The flight logic is written with hardware abstraction, so the same code can run against a simulator or actual sensors. This has not been tested on actual hardware or flown. 

## What's in the repo?
| File | Purpose |
| -- | -- |
| interfaces.hpp | IMU, Barometer, Actuator, I2CBus interfaces, and MPU6050 driver |
| I2CBus.hpp | STM32I2CBus:I2CBus implements the STM32 |
| sitl.hpp | SimPhysics and simulated IMU, barometer, and actuator (set value with variation) |
| hal_setup.cpp | I2C peripheral and GPIO initialization |
| main.cpp | Firmware entry point | 
| sitlMain.cpp | Simulation entry point |
| platformio.ini | PlatformIO config for STM32F411 |

## Hardware
- Board: STM32F411
- GY-87 module (Bundled IMU (MPU6050), Magnetometer (HMC5883L), and Barometer (BMP180))
- NEO-6M GPS module
- Airframe: V-tail with two "ruddervators" and one throttle channel

## Status
- Not flashed or tested on hardware yet
- SimPhysics::step() is a stub, so there is no actual flight dynamics in simulator
- Need to add:
  1. Actual hardware and gett readings
  2. Filter for roll and pitch estimation
  3. PID stabilization
  4. Barometer and airspeed integration for altitude and speed hold

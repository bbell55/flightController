#pragma once
#include <cstdint>
#include <iostream>

const float gravity = 9.81f;

const float accelScale = gravity * (1.0f / 16384.0f);   // convert to m/s^2
const float gyroScale = 1.0f / 131.0f;                  // convert to deg/s

struct Vector3f{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    Vector3f() = default;
    Vector3f(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};

class IMU {
public:
    virtual bool read(Vector3f& accel, Vector3f& gyro) = 0;
    virtual ~IMU() = default;
};

class Barometer {
public:
    virtual bool read(float& pressure, float& tempC) = 0;   // pressure in pa
    virtual ~Barometer() = default;   // add this
};

class Actuator {
public:
    virtual void setPWM(uint8_t channel, uint16_t pulse) = 0; // pulse in us
    virtual ~Actuator() = default;
};

class I2CBus{
public:
    virtual bool writeRegister(uint8_t addDev, uint8_t addReg, uint8_t value) = 0;
    virtual bool readRegister(uint8_t addDev, uint8_t addReg, uint8_t* buffer, uint8_t length) = 0;
    virtual ~I2CBus() = default;

private:

};

class MPU6050 : public IMU{
public:
    explicit MPU6050(I2CBus* bus, uint8_t address = 0x68) : bus(bus), addr(address) {}

    bool init(){
        return bus->writeRegister(addr, 0x6B, 0x00);
    }

    bool read(Vector3f& accel, Vector3f& gyro) override {
        uint8_t raw[14];

        if(!bus->readRegister(addr, 0x3B, raw, 14)){
            return false;
        }

        int16_t xAccel = ((raw[0] << 8) | raw[1]);
        int16_t yAccel = ((raw[2] << 8) | raw[3]);
        int16_t zAccel = ((raw[4] << 8) | raw[5]);

        // float tempC = (((raw[6] << 8) | raw[7]) / 340.0f) + 36.53f;     // Unused
        
        int16_t xGyro = (raw[8] << 8) | raw[9];
        int16_t yGyro = (raw[10] << 8) | raw[11];
        int16_t zGyro = (raw[12] << 8) | raw[13];

        accel = Vector3f(xAccel * accelScale, yAccel * accelScale, zAccel * accelScale);
        gyro = Vector3f(xGyro * gyroScale, yGyro * gyroScale, zGyro * gyroScale);

        return true;
    }

private:
    I2CBus* bus;
    uint8_t addr;
};
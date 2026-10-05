#pragma once
#include "interfaces.hpp"
#include <iostream>
#include <cmath>
#include <cstdlib>

const float seaLevelPressure = 101325.0f;

class SimPhysics{
public:
    // IMU
    Vector3f accel = {0.0f, 0.0f, gravity}; // m/s^2?
    Vector3f gyro = {0.0f, 0.0f, 0.0f};     // m/s?

    // GPS & Magnetometer
    Vector3f mag = {0.0f, 0.0f, 0.0f};  // in uT (microTeslas)
    float lattitude = 0.0f;    
    float longitude = 0.0f;


    // Barometer
    float pressure = 102404.4f;  // Pa
    float altitude = 44330.77 * (1.0f - pow(pressure / seaLevelPressure, 0.190263f));

    // 
    float tempC = 30.0f;

    float inputsPWM[5] = {1500.0f, 1500.0f, 1500.0f, 1500.0f, 1500.0f};  // 1500 uS PWM is centered

    // dt is in seconds
    void step(float dt){
        std::cout << "SimPhysics step not implemented\n";
    }

private:
    float tempF = ((tempC * 9.0f) / 5.0f) + 32.0f;
};

static float randFloat(float magnitude){
    return ((float)rand() / RAND_MAX - 0.5f) * 2.0f * magnitude;
}

class SitlIMU : public IMU{
public:
    explicit SitlIMU(SimPhysics* physics) : physics(physics) {}

    bool read(Vector3f& accel, Vector3f& gyro) override{
        accel = physics->accel;
        accel.x += randFloat(0.02f);
        accel.y += randFloat(0.02f);
        accel.z += randFloat(0.02f);

        gyro = physics->gyro;
        gyro.x += randFloat(0.01f);
        gyro.y += randFloat(0.01f);
        gyro.z += randFloat(0.01f);

        return true;
    }

private:
    SimPhysics* physics;
};

class SitlBarometer : public Barometer{
public:
    explicit SitlBarometer(SimPhysics* physics) : physics(physics) {}

    bool read(float& pressure, float& tempC) override{
        pressure = physics->pressure + randFloat(2.0f);
        tempC = physics->tempC + randFloat(0.1f);
        return true;
    }

private:
    SimPhysics* physics;
};

class SitlActuator : public Actuator{
public:
    explicit SitlActuator(SimPhysics* physics) : physics(physics) {}

    void setPWM(uint8_t channel, uint16_t pulse) override{
        if(channel < 5){
            physics->inputsPWM[channel] = pulse;
        }
    }

private:
    SimPhysics* physics;
};
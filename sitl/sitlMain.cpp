// Moved from main.cpp for firmware with actual hardware

#include "sitl.hpp"

const float dt = 0.01f;

int main() {
    SimPhysics physics;
    SitlIMU IMU(&physics);
    SitlActuator act(&physics);
    SitlBarometer baro(&physics);

    for(int i = 0; i < 5; i++){
        physics.step(dt);

        Vector3f accel, gyro;
        IMU.read(accel, gyro);

        float pressure, tempC;
        baro.read(pressure, tempC);

        act.setPWM(0, 1600);

        std::cout << "iter " << i
                  << " | accel: " << accel.x << ", " << accel.y << ", " << accel.z
                  << " | gyro: "  << gyro.x  << ", " << gyro.y  << ", " << gyro.z
                  << " | pressure: " << pressure << " Pa, temp: " << tempC << " C\n";
    }

    return 0;
}
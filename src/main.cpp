#include "I2CBus.hpp"

int main(){
    I2C1_Init();
    STM32I2CBus busI2C;
    MPU6050 imu(&busI2C);
    imu.init();

    Vector3f accel, gyro;
    imu.read(accel, gyro);
    
    return 0;
}


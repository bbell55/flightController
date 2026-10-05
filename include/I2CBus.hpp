#pragma once
#include "interfaces.hpp"
#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c1;

void I2C1_Init(void);

class STM32I2CBus: public I2CBus{
public:
    bool writeRegister(uint8_t addDev, uint8_t addReg, uint8_t value) override {
        HAL_StatusTypeDef status = HAL_I2C_Mem_Write(&hi2c1, addDev << 1, addReg, I2C_MEMADD_SIZE_8BIT, &value, 1, 100);
    return status == HAL_OK;
    }

    bool readRegister(uint8_t addDev, uint8_t addReg, uint8_t* buffer, uint8_t length) override {
        HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c1, addDev << 1, addReg, I2C_MEMADD_SIZE_8BIT, buffer, length, 100);
        return status == HAL_OK;
    }
};
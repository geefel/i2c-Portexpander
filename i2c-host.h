#ifndef I2S_HOST_H
#define I2S_HOST_H

#include <stdint.h>
#include "pin.h"

#define SDA_PIN PINDEF(C, 4)
#define SCL_PIN PINDEF(C, 5)

#define DLY_ADD 6  //DLY_ADD = 0: 100 kHz i2c-clock, 1: 3 F_CPU-Cyclen mehr, 2: 6 F_CPU-Cyclen mehr usw. 

void startI2c();
void stopI2c();
void sendACK();
void sendNACK();
uint8_t readACK();
void sendI2cData(uint8_t data);
uint8_t getI2cData();

void setupI2cSoftHost();

#endif	//I2S_HOST_H

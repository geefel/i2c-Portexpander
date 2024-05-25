 #ifndef I2S_HOST_H
#define I2S_HOST_H

#include <stdint.h>
#include "pin.h"

#define SDA_PIN PINDEF(D, 5)
#define SCL_PIN PINDEF(D, 6)

void startI2c();
void stopI2c();
void sendACK();
void sendNACK();
uint8_t readACK();
void sendI2cData(uint8_t data);
uint8_t getI2cData();

void setupI2cSoftHost();

#endif	//I2S_HOST_H

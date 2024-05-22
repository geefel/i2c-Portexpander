 #ifndef I2S_HOST_H
#define I2S_HOST_H

#include <stdint.h>
#include "pin.h"

#define SDA_PIN PINDEF(D, 5)
#define SCL_PIN PINDEF(D, 6)

void setupI2cSoftHost();
void sendDataToClient(uint8_t *data, uint8_t anzData);
void getDataFromClient(uint8_t *data, uint8_t anzData);

#endif	//I2S_HOST_H

#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>
#include "i2c-host.h"
#include "MCP23017.h"
#include "printS.h"

int main() {
uint8_t varA;
uint8_t regADir1, regADir2, regBDir;
    regADir1 = 0;
    regADir1 = (1 << bit_0) | (1 << bit_1) | (1 << bit_2);
    regADir2 = 0;
    regADir2 = (1 << bit_4) | (1 << bit_5);
    regBDir = 0; //alle Ausgang
    
    initUartHW(500000UL);
    setupI2cSoftHost();
    setupMCP23N17();
    
    set_I_O_DIRECTION_REGISTER(expanderAdr_0, port_B, regBDir);
    setRegData(expanderAdr_0, port_B, 15);
    while(1) {
        //printS("%d\n", get_GENERAL_PURPOSE_I_O_PORT_REGISTER(expanderAdr_0, port_B));
        for (int i = 0; i < 6; ++i) {
            _delay_ms(100);
            //setRegData(expanderAdr_0, port_B, (1 << i));
        }
    }
	return 0;
}
 
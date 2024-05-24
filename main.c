#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>
#include "i2c-host.h"
#include "MCP23017.h"
#include "printS.h"

int main() {
    initUartHW(500000UL);
    setupI2cSoftHost();
    setupMCP23N17();
    set_I_O_DIRECTION_REGISTER(expanderAdr_0, port_A, (1 << bit_0));

    while(1) {
        _delay_ms(1000);
        if (get_GENERAL_PURPOSE_I_O_PORT_REGISTER(expanderAdr_0, port_A))
            printS("GPB0: %d\n", 1);
        else
            printS("GPB0: %d\n", 0);
    }
	return 0;
}

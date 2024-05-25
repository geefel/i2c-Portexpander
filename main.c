#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>
#include "i2c-host.h"
#include "MCP23017.h"
#include "printS.h"

int main() {
uint8_t varA;
    initUartHW(500000UL);
    setupI2cSoftHost();
    setupMCP23N17();
    varA = getRegData(expanderAdr_0, IOCON) | (1 << SEQOP) | (1 << BANK);
    set_I_O_EXPANDER_CONFIGURATION_REGISTER(expanderAdr_0, port_B, varA);
    varA = getRegData(expanderAdr_0, IOCON) | (1 << bit_0);
    set_I_O_DIRECTION_REGISTER(expanderAdr_0, port_B, varA);

    while(1) {
        _delay_ms(1000);
            printS("%d\n", get_GENERAL_PURPOSE_I_O_PORT_REGISTER(expanderAdr_0, port_B));
    }
	return 0;
}

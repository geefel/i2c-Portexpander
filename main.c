#include <stdio.h>
#include <stdint.h>
#include "i2c-host.h"
#include "MCP23017.h"
#include "printS.h"

int main() {
    initUartHW(500000UL);
    setupI2cSoftHost();
	return 0;
}

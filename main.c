#include <stdio.h>
#include <stdint.h>
#include "printS.h"

int main() {
    initUartHW(500000UL);
	printS("Hallo");
	return 0;
}

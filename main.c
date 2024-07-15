#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>
#include "i2c-host.h"
#include "MCP23017.h"
#include "printS.h"

void setupTastenMatrix();
uint8_t getPortExpanderPort();
uint8_t changeTastenMatrixInOut();

void setupTastenMatrix() {
    set_I_O_DIRECTION_REGISTER(expanderAdr_0, port_A, 0xF0);
    set_GENERAL_PURPOSE_I_O_PORT_REGISTER(expanderAdr_0, port_A, 0);
    set_GPIO_PULL_UP_RESISTOR_REGISTER(expanderAdr_0, port_A, 0xF0);
    
    set_INTERRUPT_ON_CHANGE_CONTROL_REGISTER(expanderAdr_0, port_A, 0xF0);
    set_INTERRUPPT_DEFAULT_VALUE_REGISTER(expanderAdr_0, port_A, 0xF0);
    set_INTERRUPT_ON_CHANGE_PINS(expanderAdr_0, port_A, 0xF0);
}

uint8_t getPortExpanderPort() {
    return get_GENERAL_PURPOSE_I_O_PORT_REGISTER(expanderAdr_0, port_A);
}

uint8_t changeTastenMatrixInOut() {
    uint8_t erg = 0;
    set_I_O_DIRECTION_REGISTER(expanderAdr_0, port_A, 0x0F);
    
    set_INTERRUPT_ON_CHANGE_CONTROL_REGISTER(expanderAdr_0, port_A, 0x0F);
    set_INTERRUPPT_DEFAULT_VALUE_REGISTER(expanderAdr_0, port_A, 0x0F);
    set_INTERRUPT_ON_CHANGE_PINS(expanderAdr_0, port_A, 0x0F);
    
    erg = getPortExpanderPort();
    
    set_I_O_DIRECTION_REGISTER(expanderAdr_0, port_A, 0xF0);
    
    set_INTERRUPT_ON_CHANGE_CONTROL_REGISTER(expanderAdr_0, port_A, 0xF0);
    set_INTERRUPPT_DEFAULT_VALUE_REGISTER(expanderAdr_0, port_A, 0xF0);
    set_INTERRUPT_ON_CHANGE_PINS(expanderAdr_0, port_A, 0xF0);
    
    return erg;
}

int main() {
    uint8_t portA = 0xF0;
    uint8_t portAOld = 0xF0;
    uint8_t rowPin, colPin; 
    uint8_t portADir1 = (pinIn << bit_0)  | (pinIn << bit_1)  | (pinIn << bit_2)  | (0 << bit_3)      | (pinOut << bit_4) | (pinOut << bit_6) | (0 << bit_7);
    uint8_t portPin1 =  (low << bit_0)    | (low << bit_1)    | (low << bit_2)    | (0 << bit_3)      | (high << bit_4)   | (high << bit_6)   | (0 << bit_7);
    uint8_t portADir2 = (pinOut << bit_0) | (pinOut << bit_1) | (pinOut << bit_2) | (0 << bit_3)      | (pinIn << bit_4)  | (pinIn << bit_6)  | (0 << bit_7);
    uint8_t portPin2 =  (high << bit_0)   | (high << bit_1)   | (high << bit_2)   | (0 << bit_3)      | (low << bit_4)    | (low << bit_6)    | (0 << bit_7);
    uint8_t portBDir1 = (pinOut << bit_0) | (pinOut << bit_1) | (pinOut << bit_2) | (pinOut << bit_3) | (pinOut << bit_4) | (pinOut << bit_6) | (pinOut << bit_7);
    
//setup Uart Hardware
    initUartHW(500000UL);

//setup I2cSoftHost
    setupI2cSoftHost();
    
//setup MCP23017-Portexpander
    setupTastenMatrix();
    

    while(1) {
        
        _delay_ms(500);
        portA = getPortExpanderPort();
        printS("%d \n", portA);
        if (portA != portAOld) {
            portAOld = portA;
            colPin = portA & 0b11110000;
            rowPin = changeTastenMatrixInOut() & 0b00001111;
            printS("%d %d\n", colPin, rowPin);
        }
        _delay_ms(500);

    }
	return 0;
}
 
#include "MCP23017.h"
#include "i2c-host.h"

static uint8_t regData[EXPANDER_NUM][21];

void writeToMCP23N17(uint8_t adr, uint8_t reg, uint8_t pinset, uint8_t regDataIndex);
uint8_t readFromMCP23N17(uint8_t adr, uint8_t reg, uint8_t regDataIndex);

//Startkonditionen hinzufügen
void setupMCP23N17() {
    for (uint8_t i = 0; i < EXPANDER_NUM; ++i) {
        regData[i][IODIRA] = (1 << bit_0) & (1 << bit_1) & (1 << bit_2) & (1 << bit_3) 
				& (1 << bit_4) & (1 << bit_5) & (1 << bit_6)/* & (1 << bit_7)*/;    //pin7 immer Out bei MCP23017 (nicht bei MCP23S17)
        regData[i][IODIRB] = 0b01111111;                                    //pin7 immer Out bei MCP23017 (nicht bei MCP23S17)     
    }
    
}

void setRegData(uint8_t adr, uint8_t reg, uint8_t dat) {
    regData[adr][reg] = dat;
}

uint8_t getRegData(uint8_t adr, uint8_t reg) {
    return regData[adr][reg];
}

void writeToMCP23N17(uint8_t adr, uint8_t reg, uint8_t pinSet, uint8_t regDataIndex) {
    setRegData(adr, regDataIndex, pinSet);
    
    startI2c();
    sendI2cData(0b01000000 + (adr << 1) + 0);   //rw = 0: schreiben zum Client)
    readACK();
    sendI2cData(reg);
    readACK();
    sendI2cData(pinSet);
    readACK();
	stopI2c();
}

uint8_t readFromMCP23N17(uint8_t adr, uint8_t reg, uint8_t regDataIndex) {
    uint8_t erg;
    
    startI2c();
    sendI2cData(0b01000000 + (adr << 1) + 0);   //rw = 0: schreiben zum Client)
    readACK();
    sendI2cData(reg);
    readACK();
    startI2c();
    sendI2cData(0b01000000 + (adr << 1) + 1);   //rw = 1: lesen vom Client)
    readACK();
    erg = getI2cData();
    sendACK();
    stopI2c();    
    
    setRegData(adr, regDataIndex, erg);
    return erg;
}

void set_I_O_DIRECTION_REGISTER(uint8_t adr, uint8_t gpio_ab, uint8_t pinSet) {
    uint8_t reg;
    uint8_t regDataIndex;
    if (gpio_ab == 0) { 
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? IODIRA_IOCON_BANK_0 : IODIRA_IOCON_BANK_1;
        regDataIndex = IODIRA;
    }
    else {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? IODIRB_IOCON_BANK_0 : IODIRB_IOCON_BANK_1;
        regDataIndex = IODIRB;
    }
    writeToMCP23N17(adr, reg, pinSet, regDataIndex);
}

uint8_t get_I_O_DIRECTION_REGISTER(uint8_t adr, uint8_t gpio_ab) {
    uint8_t reg;
    uint8_t regDataIndex;
    if (gpio_ab == 0) {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? IODIRA_IOCON_BANK_0 : IODIRA_IOCON_BANK_1;
        regDataIndex = IODIRA;
    }
    else {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? IODIRB_IOCON_BANK_0 : IODIRB_IOCON_BANK_1;
        regDataIndex = IODIRB; 
    }    
    return readFromMCP23N17(adr, reg, regDataIndex);
}

void set_INPUT_POLARITY_REGISTER(uint8_t adr, uint8_t gpio_ab, uint8_t pinSet) {
    uint8_t reg;
    uint8_t regDataIndex;
    if (gpio_ab == 0) {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? IPOLA_IOCON_BANK_0 : IPOLA_IOCON_BANK_1;
        regDataIndex = IPOLA;
    }
    else {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? IPOLB_IOCON_BANK_0 : IPOLB_IOCON_BANK_1;
        regDataIndex = IPOLB;
    }
    writeToMCP23N17(adr, reg, pinSet, regDataIndex);
}

uint8_t get_INPUT_POLARITY_REGISTER(uint8_t adr, uint8_t gpio_ab) {
    uint8_t reg;
    uint8_t regDataIndex;
    if (gpio_ab == 0) {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? IPOLA_IOCON_BANK_0 : IPOLA_IOCON_BANK_1;
        regDataIndex = IPOLA;
    }
    else {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? IPOLB_IOCON_BANK_0 : IPOLB_IOCON_BANK_1;
        regDataIndex = IPOLB;
    }
    return readFromMCP23N17(adr, reg, regDataIndex);
}

void set_INTERRUPT_ON_CHANGE_PINS(uint8_t adr, uint8_t gpio_ab, uint8_t pinSet) {
    uint8_t reg;
    uint8_t regDataIndex;
    if (gpio_ab == 0) {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? GPINTENA_IOCON_BANK_0 : GPINTENA_IOCON_BANK_1;
        regDataIndex = GPINTENA;
    }
    else {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? GPINTENB_IOCON_BANK_0 : GPINTENB_IOCON_BANK_1; 
        regDataIndex = GPINTENB;
    }
    writeToMCP23N17(adr, reg, pinSet, regDataIndex);
}

uint8_t get_INTERRUPT_ON_CHANGE_PINS(uint8_t adr, uint8_t gpio_ab) {
    uint8_t reg;
    uint8_t regDataIndex;
    if (gpio_ab == 0) {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? GPINTENA_IOCON_BANK_0 : GPINTENA_IOCON_BANK_1;
        regDataIndex = GPINTENA;
    }
    else {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? GPINTENB_IOCON_BANK_0 : GPINTENB_IOCON_BANK_1; 
        regDataIndex = GPINTENB;
    }
    return readFromMCP23N17(adr, reg, regDataIndex);
}

void set_DEFAULT_VALUE_REGISTER(uint8_t adr, uint8_t gpio_ab, uint8_t pinSet) {
    uint8_t reg;
    uint8_t regDataIndex;
    if (gpio_ab == 0) {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? DEFVALA_IOCON_BANK_0 : DEFVALA_IOCON_BANK_1;
        regDataIndex = DEFVALA;
    }
    else {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? DEFVALB_IOCON_BANK_0 : DEFVALB_IOCON_BANK_1;
        regDataIndex = DEFVALB;
    }
    writeToMCP23N17(adr, reg, pinSet, regDataIndex);
}

uint8_t get_DEFAULT_VALUE_REGISTER(uint8_t adr, uint8_t gpio_ab) {
    uint8_t reg;
    uint8_t regDataIndex;
    if (gpio_ab == 0) {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? DEFVALA_IOCON_BANK_0 : DEFVALA_IOCON_BANK_1;
        regDataIndex = DEFVALA;
    }
    else {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? DEFVALB_IOCON_BANK_0 : DEFVALB_IOCON_BANK_1;
        regDataIndex = DEFVALB;
    }
    return readFromMCP23N17(adr, reg, regDataIndex);
}

void set_INTERRUPT_ON_CHANGE_CONTROL_REGISTER(uint8_t adr, uint8_t gpio_ab, uint8_t pinSet) {
    uint8_t reg;
    uint8_t regDataIndex;
    if (gpio_ab == 0) {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? INTCONA_IOCON_BANK_0 : INTCONA_IOCON_BANK_1;
        regDataIndex = INTCONA;
    }
    else {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? INTCONB_IOCON_BANK_0 : INTCONB_IOCON_BANK_1;
        regDataIndex = INTCONB;
    }
    writeToMCP23N17(adr, reg, pinSet, regDataIndex);
}

uint8_t get_INTERRUPT_ON_CHANGE_CONTROL_REGISTER(uint8_t adr, uint8_t gpio_ab) {
    uint8_t reg;
    uint8_t regDataIndex;
    if (gpio_ab == 0) {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? INTCONA_IOCON_BANK_0 : INTCONA_IOCON_BANK_1;
        regDataIndex = INTCONA;
    }
    else {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? INTCONB_IOCON_BANK_0 : INTCONB_IOCON_BANK_1;
        regDataIndex = INTCONB;
    }
    return readFromMCP23N17(adr, reg, regDataIndex);
}

void set_I_O_EXPANDER_CONFIGURATION_REGISTER(uint8_t adr, uint8_t gpio_ab, uint8_t configBits) {
    uint8_t reg;
    uint8_t regDataIndex;
    if (gpio_ab == 0) {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? IOCON_IOCON_BANK_0 : IOCON_IOCON_BANK_1;
        regDataIndex = IOCON;
    }
    else {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? IOCON_IOCON_BANK_0 : IOCON_IOCON_BANK_1;
        regDataIndex = IOCON;
    }
    writeToMCP23N17(adr, reg, configBits, regDataIndex);
}

uint8_t get_I_O_EXPANDER_CONFIGURATION_REGISTER(uint8_t adr, uint8_t gpio_ab) {
    uint8_t reg;
    uint8_t regDataIndex;
    if (gpio_ab == 0) {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? IOCON_IOCON_BANK_0 : IOCON_IOCON_BANK_1;
        regDataIndex = IOCON;
    }
    else {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? IOCON_IOCON_BANK_0 : IOCON_IOCON_BANK_1;
        regDataIndex = IOCON;
    }
    return readFromMCP23N17(adr, reg, regDataIndex);
}

void set_GPIO_PULL_UP_RESISTOR_REGISTER(uint8_t adr, uint8_t gpio_ab, uint8_t pinSet) {
    uint8_t reg;
    uint8_t regDataIndex;
    if (gpio_ab == 0) {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? GPPUA_IOCON_BANK_0 : GPPUA_IOCON_BANK_1;
        regDataIndex = GPPUA;
    }
    else {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? GPPUB_IOCON_BANK_0 : GPPUB_IOCON_BANK_1;
        regDataIndex = GPPUB;
    }
    writeToMCP23N17(adr, reg, pinSet, regDataIndex);
}

uint8_t get_GPIO_PULL_UP_RESISTOR_REGISTER(uint8_t adr, uint8_t gpio_ab) {
    uint8_t reg;
    uint8_t regDataIndex;
    if (gpio_ab == 0) {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? GPPUA_IOCON_BANK_0 : GPPUA_IOCON_BANK_1;
        regDataIndex = GPPUA;
    }
    else {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? GPPUB_IOCON_BANK_0 : GPPUB_IOCON_BANK_1;
        regDataIndex = GPPUB;
    }
    return readFromMCP23N17(adr, reg, regDataIndex);
}

uint8_t get_INTERRUPT_FLAG_REGISTER(uint8_t adr, uint8_t gpio_ab) {
    uint8_t reg;
    uint8_t regDataIndex;
    if (gpio_ab == 0) {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? INTFA_IOCON_BANK_0 : INTFA_IOCON_BANK_1;
        regDataIndex = INTFA;
    }
    else {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? INTFB_IOCON_BANK_0 : INTFB_IOCON_BANK_1;
        regDataIndex = INTFB;
    }
    return readFromMCP23N17(adr, reg, regDataIndex);
}

uint8_t get_INTERRUPT_CAPTURED_VALUE(uint8_t adr, uint8_t gpio_ab) {
    uint8_t reg;
    uint8_t regDataIndex;
    if (gpio_ab == 0) {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? INTCAPA_IOCON_BANK_0 : INTCAPA_IOCON_BANK_1;
        regDataIndex = INTCAPA;
    }
    else {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? INTCAPB_IOCON_BANK_0 : INTCAPB_IOCON_BANK_1;
        regDataIndex = INTCAPB;
    }
    return readFromMCP23N17(adr, reg, regDataIndex);
}

void set_GENERAL_PURPOSE_I_O_PORT_REGISTER(uint8_t adr, uint8_t gpio_ab, uint8_t pinSet) {
    uint8_t reg;
    uint8_t regDataIndex;
    if (gpio_ab == 0) {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? GPIOA_IOCON_BANK_0 : GPIOA_IOCON_BANK_1;
        regDataIndex = GPIOA;
    }
    else {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? GPIOB_IOCON_BANK_0 : GPIOB_IOCON_BANK_1;
        regDataIndex = GPIOB;
    }
    writeToMCP23N17(adr, reg, pinSet, regDataIndex);
}

uint8_t get_GENERAL_PURPOSE_I_O_PORT_REGISTER(uint8_t adr, uint8_t gpio_ab) {
    uint8_t reg;
    uint8_t regDataIndex;
    if (gpio_ab == 0) {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? GPIOA_IOCON_BANK_0 : GPIOA_IOCON_BANK_1;
        regDataIndex = GPIOA;
    }
    else {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? GPIOB_IOCON_BANK_0 : GPIOB_IOCON_BANK_1;
        regDataIndex = GPIOB;
    }
    return readFromMCP23N17(adr, reg, regDataIndex);
}

void set_OUTPUT_LATCH_REGISTER_0(uint8_t adr, uint8_t gpio_ab, uint8_t pinSet) {
    uint8_t reg;
    uint8_t regDataIndex;
    if (gpio_ab == 0) {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? OLATA_IOCON_BANK_0 : OLATA_IOCON_BANK_1;
        regDataIndex = OLATA;
    }
    else {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? OLATB_IOCON_BANK_0 : OLATB_IOCON_BANK_1;
        regDataIndex = OLATB;
    }
    writeToMCP23N17(adr, reg, pinSet, regDataIndex);
}

uint8_t get_OUTPUT_LATCH_REGISTER_0(uint8_t adr, uint8_t gpio_ab) {
    uint8_t reg;
    uint8_t regDataIndex;
    if (gpio_ab == 0) {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? OLATA_IOCON_BANK_0 : OLATA_IOCON_BANK_1;
        regDataIndex = OLATA;
    }
    else {
        reg = (regData[adr][IOCON] & (1 << BANK)) == 0 ? OLATB_IOCON_BANK_0 : OLATB_IOCON_BANK_1;
        regDataIndex = OLATB;
    }
    return readFromMCP23N17(adr, reg, regDataIndex);
}

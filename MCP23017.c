/*
 *                MCP23017
 *                +--/\--+
 *    GPB0 i/o   1|      |28    o GPA7
 *    GPB1 i/o   2|      |27  i/o GPA6
 *    GPB2 i/o   3|      |26  i/o GPA5
 *    GPB3 i/o   4|      |25  i/o GPA4
 *    GPB4 i/o   5|      |24  i/o GPA3
 *    GPB5 i/o   6|      |23  i/o GPA2
 *    GPB6 i/o   7|      |22  i/o GPA1
 *    GPB7   o   8|      |21  i/o GPA0
 *    Vdd  i     9|      |20    o INTA
 *    Vss  i    10|      |19    o INTB
 *    NC        11|      |18  i  /RESET
 *    SCK  i    12|      |17  i   A2
 *    SDA  i/o  13|      |16  i   A1
 *    NC        14|      |15  i   A0
 *                +------+
 * 
 * 
 *                MCP23S17
 *                +--/\--+
 *    GPB0 i/o   1|      |28  i/o GPA7
 *    GPB1 i/o   2|      |27  i/o GPA6
 *    GPB2 i/o   3|      |26  i/o GPA5
 *    GPB3 i/o   4|      |25  i/o GPA4
 *    GPB4 i/o   5|      |24  i/o GPA3
 *    GPB5 i/o   6|      |23  i/o GPA2
 *    GPB6 i/o   7|      |22  i/o GPA1
 *    GPB7 i/o   8|      |21  i/o GPA0
 *    Vdd  i     9|      |20    o INTA
 *    Vss  i    10|      |19    o INTB
 *    /CS  i    11|      |18  i  /RESET
 *    SCK  i    12|      |17  i   A2
 *    SI   i    13|      |16  i   A1
 *    SO     o  14|      |15  i   A0
 *                +------+
 *
 * A0..2, /RESET must be externally biased.
 * 
 * BYTE MODE AND SEQUENTIAL MODE
 * Byte Mode: keine automatische Zeigerverschiebung zum nächsten Regiester oder automatischer Wechsel zw. zwei korepondierenden A- und B-Registern.
 * Sequential Mode: automatische Zeigerverschiebung zum nächsten Regiester
 * Stichpunktartiges Ansprechen von einzelnen Registern unterbricht die Reaktion von den beiden Modis.
 * 
 * I2C
 * START
 * Device Opcode: 0 1 0 0  A2 A1 A0 r/w
 * ACK from Device
 * Register Adr: 8-bit MSF
 * ACK from Device
 * Data: 8-bit
 * STOP
 */

#include "MCP23017.h"
#include "i2c-host.h"

static uint8_t iocon_bank;


void writeToMCP23N17(uint8_t adr, uint8_t reg, uint8_t pinset);
uint8_t readFromMCP23N17(uint8_t adr, uint8_t reg);


void setupMCP23N17(uint8_t bnk) {
    iocon_bank = bnk;
}

void writeToMCP23N17(uint8_t adr, uint8_t reg, uint8_t pinSet) {
    uint8_t anz = 3;
    uint8_t dat[anz];
    dat[0] = 0b00100000 + adr;
    dat[1] = reg;
    dat[2] = pinSet;
    
    sendDataToClient(dat, anz);
}

uint8_t readFromMCP23N17(uint8_t adr, uint8_t reg) {
    uint8_t anz = 3;
    uint8_t dat[anz];
    dat[0] = 0b00100000 + adr;
    dat[1] = reg;
    dat[2] = 0;

    getDataFromClient(dat, anz);
    return dat[2];
}

/* IODIR 
 * Controls the direction of the data I/O.
 * 1 = Pin is configured as an input.
 * 0 = Pin is configured as an output.
 * For MCP23017, IO7 must be set to "0" (output).
 */
void set_I_O_DIRECTION_REGISTER_A(uint8_t adr, uint8_t pinSet) {
    uint8_t reg = iocon_bank == 0 ? IODIRA_IOCON_BANK_0 : IODIRA_IOCON_BANK_1;
    writeToMCP23N17(adr, reg, pinSet);
}

void set_I_O_DIRECTION_REGISTER_B(uint8_t adr, uint8_t pinSet) {
    uint8_t reg = iocon_bank == 0 ? IODIRB_IOCON_BANK_0 : IODIRB_IOCON_BANK_1;    
    writeToMCP23N17(adr, reg, pinSet);
}

uint8_t get_I_O_DIRECTION_REGISTER_A(uint8_t adr) {
    uint8_t reg = iocon_bank == 0 ? IODIRA_IOCON_BANK_0 : IODIRA_IOCON_BANK_1;
    return readFromMCP23N17(adr, reg);
}

uint8_t get_I_O_DIRECTION_REGISTER_B(uint8_t adr) {
    uint8_t reg = iocon_bank == 0 ? IODIRB_IOCON_BANK_0 : IODIRB_IOCON_BANK_1;
    return readFromMCP23N17(adr, reg);
}

/* IPOL
 * If a bit is set, the corresponding GPIO register bit will
 * reflect the inverted value on the pin.
 * 1 = GPIO register bit reflects the opposite logic state of the input pin.
 * 0 = GPIO register bit reflects the same logic state of the input pin.
 */
void set_INPUT_POLARITY_REGISTER_A(uint8_t adr, uint8_t pinSet) {
    uint8_t reg = iocon_bank == 0 ? IPOLA_IOCON_BANK_0 : IPOLA_IOCON_BANK_1; 
    writeToMCP23N17(adr, reg, pinSet);
}

void set_INPUT_POLARITY_REGISTER_B(uint8_t adr, uint8_t pinSet) {
    uint8_t reg = iocon_bank == 0 ? IPOLB_IOCON_BANK_0 : IPOLB_IOCON_BANK_1;
    writeToMCP23N17(adr, reg, pinSet);
}

uint8_t get_INPUT_POLARITY_REGISTER_A(uint8_t adr) {
    uint8_t reg = iocon_bank == 0 ? IPOLA_IOCON_BANK_0 : IPOLA_IOCON_BANK_1;
    return readFromMCP23N17(adr, reg);
}

uint8_t get_INPUT_POLARITY_REGISTER_B(uint8_t adr) {
    uint8_t reg = iocon_bank == 0 ? IPOLB_IOCON_BANK_0 : IPOLB_IOCON_BANK_1;
    return readFromMCP23N17(adr, reg);
}

/* GPINTEN
 * If a bit is set, the corresponding pin is enabled for
 * interrupt-on-change.
 * 1 = Enables GPIO input pin for interrupt-on-change event.
 * 0 = Disables GPIO input pin for interrupt-on-change event.
 */
void set_INTERRUPT_ON_CHANGE_PINS_A(uint8_t adr, uint8_t pinSet) {
    uint8_t reg = iocon_bank == 0 ? GPINTENA_IOCON_BANK_0 : GPINTENA_IOCON_BANK_1;
    writeToMCP23N17(adr, reg, pinSet);
}

void set_INTERRUPT_ON_CHANGE_PINS_B(uint8_t adr, uint8_t pinSet) {
    uint8_t reg = iocon_bank == 0 ? GPINTENB_IOCON_BANK_0 : GPINTENB_IOCON_BANK_1;
    writeToMCP23N17(adr, reg, pinSet);
}

uint8_t get_INTERRUPT_ON_CHANGE_PINS_A(uint8_t adr) {
    uint8_t reg = iocon_bank == 0 ? GPINTENA_IOCON_BANK_0 : GPINTENA_IOCON_BANK_1;
    return readFromMCP23N17(adr, reg);
}

uint8_t get_INTERRUPT_ON_CHANGE_PINS_B(uint8_t adr) {
    uint8_t reg = iocon_bank == 0 ? GPINTENB_IOCON_BANK_0 : GPINTENB_IOCON_BANK_1;
    return readFromMCP23N17(adr, reg);
}

/* DEFVAL
 * The default comparison value is configured in the
 * DEFVAL register. If enabled (via GPINTEN and
 * INTCON) to compare against the DEFVAL register, an
 * opposite value on the associated pin will cause an
 * interrupt to occur.
 * Sets the compare value for pins configured for interrupt-on-change from defaults. Refer to INTCON.
 * If the associated pin level is the opposite from the register bit, an interrupt occurs. Refer to INTCON and GPINTEN.
 */
void set_DEFAULT_VALUE_REGISTER_A(uint8_t adr, uint8_t pinSet) {
    uint8_t reg = iocon_bank == 0 ? DEFVALA_IOCON_BANK_0 : DEFVALA_IOCON_BANK_1;
    writeToMCP23N17(adr, reg, pinSet);
}

void set_DEFAULT_VALUE_REGISTER_B(uint8_t adr, uint8_t pinSet) {
    uint8_t reg = iocon_bank == 0 ? DEFVALB_IOCON_BANK_0 : DEFVALB_IOCON_BANK_1;
    writeToMCP23N17(adr, reg, pinSet);
}

uint8_t get_DEFAULT_VALUE_REGISTER_A(uint8_t adr) {
    uint8_t reg = iocon_bank == 0 ? DEFVALA_IOCON_BANK_0 : DEFVALA_IOCON_BANK_1;
    return readFromMCP23N17(adr, reg);
}

uint8_t get_DEFAULT_VALUE_REGISTER_B(uint8_t adr) {
    uint8_t reg = iocon_bank == 0 ? DEFVALB_IOCON_BANK_0 : DEFVALB_IOCON_BANK_1;
    return readFromMCP23N17(adr, reg);
}

/* INTCON
 * The INTCON register controls how the associated pin
 * value is compared for the interrupt-on-change feature.
 * 1 = Pin value is compared against the associated bit in the DEFVAL register.
 * 0 = Pin value is compared against the previous pin value.
 */
void set_INTERRUPT_ON_CHANGE_CONTROL_REGISTER_A(uint8_t adr, uint8_t pinSet) {
    uint8_t reg = iocon_bank == 0 ? INTCONA_IOCON_BANK_0 : INTCONA_IOCON_BANK_1;
    writeToMCP23N17(adr, reg, pinSet);
}

void set_INTERRUPT_ON_CHANGE_CONTROL_REGISTER_B(uint8_t adr, uint8_t pinSet) {
    uint8_t reg = iocon_bank == 0 ? INTCONB_IOCON_BANK_0 : INTCONB_IOCON_BANK_1;
    writeToMCP23N17(adr, reg, pinSet);
}

uint8_t get_INTERRUPT_ON_CHANGE_CONTROL_REGISTER_A(uint8_t adr) {
    uint8_t reg = iocon_bank == 0 ? INTCONA_IOCON_BANK_0 : INTCONA_IOCON_BANK_1;
    return readFromMCP23N17(adr, reg);
}

uint8_t get_INTERRUPT_ON_CHANGE_CONTROL_REGISTER_B(uint8_t adr) {
    uint8_t reg = iocon_bank == 0 ? INTCONB_IOCON_BANK_0 : INTCONB_IOCON_BANK_1;
    return readFromMCP23N17(adr, reg);
}

/* IOCON
 * The IOCON register contains several bits for configuring the device:
 * BANK: Controls how the registers are addressed
 * 1 = The registers associated with each port are separated into different banks.
 * 0 = The registers are in the same bank (addresses are sequential).
 * MIRROR: INT Pins Mirror bit
 * 1 = The INT pins are internally connected
 * 0 = The INT pins are not connected. INTA is associated with PORTA and INTB is associated with PORTB
 * SEQOP: Sequential Operation mode bit
 * 1 = Sequential operation disabled, address pointer does not increment.
 * 0 = Sequential operation enabled, address pointer increments.
 * DISSLW: Slew Rate control bit for SDA output
 * 1 = Slew rate disabled
 * 0 = Slew rate enabled
 * HAEN: Hardware Address Enable bit (MCP23S17 only) On the MCP23017 always enabled
 * 1 = Enables the MCP23S17 address pins.
 * 0 = Disables the MCP23S17 address pins.
 * ODR: Configures the INT pin as an open-drain output
 * 1 = Open-drain output (overrides the INTPOL bit.)
 * 0 = Active driver output (INTPOL bit sets the polarity.)
 * INTPOL: This bit sets the polarity of the INT output pin
 * 1 = Active-high
 * 0 = Active-low
 * bit 0 Unimplemented: Read as ‘0’
 */
void set_I_O_EXPANDER_CONFIGURATION_REGISTER(uint8_t adr, uint8_t configPins) {
    uint8_t reg = iocon_bank == 0 ? IOCON_IOCON_BANK_0 : IOCON_IOCON_BANK_1;
    writeToMCP23N17(adr, reg, configPins);
}

uint8_t get_I_O_EXPANDER_CONFIGURATION_REGISTER(uint8_t adr) {
    uint8_t reg = iocon_bank == 0 ? IOCON_IOCON_BANK_0 : IOCON_IOCON_BANK_1;
    return readFromMCP23N17(adr, reg);
}

/* GPPU
 * The GPPU register controls the pull-up resistors for the
 * port pins. If a bit is set and the corresponding pin is
 * configured as an input, the corresponding port pin is
 * internally pulled up with a 100 kOhm resistor.
 * 1 = Pull-up enabled
 * 0 = Pull-up disabled
 */
void set_GPIO_PULL_UP_RESISTOR_REGISTER_A(uint8_t adr, uint8_t pinSet) {
    uint8_t reg = iocon_bank == 0 ? GPPUA_IOCON_BANK_0 : GPPUA_IOCON_BANK_1;
    writeToMCP23N17(adr, reg, pinSet);
}

void set_GPIO_PULL_UP_RESISTOR_REGISTER_B(uint8_t adr, uint8_t pinSet) {
    uint8_t reg = iocon_bank == 0 ? GPPUB_IOCON_BANK_0 : GPPUB_IOCON_BANK_1;
    writeToMCP23N17(adr, reg, pinSet);
}

uint8_t get_GPIO_PULL_UP_RESISTOR_REGISTER_A(uint8_t adr) {
    uint8_t reg = iocon_bank == 0 ? GPPUA_IOCON_BANK_0 : GPPUA_IOCON_BANK_1;
    return readFromMCP23N17(adr, reg);
}

uint8_t get_GPIO_PULL_UP_RESISTOR_REGISTER_B(uint8_t adr) {
    uint8_t reg = iocon_bank == 0 ? GPPUB_IOCON_BANK_0 : GPPUB_IOCON_BANK_1;
    return readFromMCP23N17(adr, reg);
}

/* INTF
 * The INTF register reflects the interrupt condition on the
 * port pins of any pin that is enabled for interrupts via the
 * GPINTEN register.
 * 1 = Pin caused interrupt.
 * 0 = Interrupt not pending
 */
uint8_t get_INTERRUPT_FLAG_REGISTER_A(uint8_t adr) {
    uint8_t reg = iocon_bank == 0 ? INTFA_IOCON_BANK_0 : INTFA_IOCON_BANK_1;
    return readFromMCP23N17(adr, reg);
}

uint8_t get_INTERRUPT_FLAG_REGISTER_B(uint8_t adr) {
    uint8_t reg = iocon_bank == 0 ? INTFB_IOCON_BANK_0 : INTFB_IOCON_BANK_1;
    return readFromMCP23N17(adr, reg);
}

/* INTCAP
 * The INTCAP register captures the GPIO port value at
 * the time the interrupt occurred. The register is
 * read-only and is updated only when an interrupt
 * occurs. The register remains unchanged until the
 * interrupt is cleared via a read of INTCAP or GPIO.
 * 1 = Logic-high
 * 0 = Logic-low
 */
uint8_t get_INTERRUPT_CAPTURED_VALUE_A(uint8_t adr) {
    uint8_t reg = iocon_bank == 0 ? INTCAPA_IOCON_BANK_0 : INTCAPA_IOCON_BANK_1;
    return readFromMCP23N17(adr, reg);
}

uint8_t get_INTERRUPT_CAPTURED_VALUE_B(uint8_t adr) {
    uint8_t reg = iocon_bank == 0 ? INTCAPB_IOCON_BANK_0 : INTCAPB_IOCON_BANK_1;
    return readFromMCP23N17(adr, reg);
}

/* GPIO
 * The GPIO register reflects the value on the port.
 * Reading from this register reads the port. Writing to this
 * register modifies the Output Latch (OLAT) register.
 * 1 = Logic-high
 * 0 = Logic-low
 */
void set_GENERAL_PURPOSE_I_O_PORT_REGISTER_A(uint8_t adr, uint8_t pinSet) {
    uint8_t reg = iocon_bank == 0 ? GPIOA_IOCON_BANK_0 : GPIOA_IOCON_BANK_1;
    writeToMCP23N17(adr, reg, pinSet);
}

void set_GENERAL_PURPOSE_I_O_PORT_REGISTER_B(uint8_t adr, uint8_t pinSet) {
    uint8_t reg = iocon_bank == 0 ? GPIOB_IOCON_BANK_0 : GPIOB_IOCON_BANK_1;
    writeToMCP23N17(adr, reg, pinSet);
}

uint8_t get_GENERAL_PURPOSE_I_O_PORT_REGISTER_A(uint8_t adr) {
    uint8_t reg = iocon_bank == 0 ? GPIOA_IOCON_BANK_0 : GPIOA_IOCON_BANK_1;
    return readFromMCP23N17(adr, reg);
}

uint8_t get_GENERAL_PURPOSE_I_O_PORT_REGISTER_B(uint8_t adr) {
    uint8_t reg = iocon_bank == 0 ? GPIOB_IOCON_BANK_0 : GPIOB_IOCON_BANK_1;
    return readFromMCP23N17(adr, reg);
}

/* OLAT
 * The OLAT register provides access to the output
 * latches. A read from this register results in a read of the
 * OLAT and not the port itself. A write to this register
 * modifies the output latches that modifies the pins
 * configured as outputs.
 * 1 = Logic-high
 * 0 = Logic-low
 */
void set_OUTPUT_LATCH_REGISTER_0_A(uint8_t adr, uint8_t pinSet) {
    uint8_t reg = iocon_bank == 0 ? OLATA_IOCON_BANK_0 : OLATA_IOCON_BANK_1;
    writeToMCP23N17(adr, reg, pinSet);
}

void set_OUTPUT_LATCH_REGISTER_0_B(uint8_t adr, uint8_t pinSet) {
    uint8_t reg = iocon_bank == 0 ? OLATB_IOCON_BANK_0 : OLATB_IOCON_BANK_1;
    writeToMCP23N17(adr, reg, pinSet);
}

uint8_t get_OUTPUT_LATCH_REGISTER_0_A(uint8_t adr) {
    uint8_t reg = iocon_bank == 0 ? OLATA_IOCON_BANK_0 : OLATA_IOCON_BANK_1;
    return readFromMCP23N17(adr, reg);
}

uint8_t get_OUTPUT_LATCH_REGISTER_0_B(uint8_t adr) {
    uint8_t reg = iocon_bank == 0 ? OLATB_IOCON_BANK_0 : OLATB_IOCON_BANK_1;
    return readFromMCP23N17(adr, reg);
}

#ifndef MCP23017_H
#define MCP23017_H

#include <stdint.h>

//IOCON.BANK = 0 Adressen
#define 	IODIRA_IOCON_BANK_0      0x00
#define 	IODIRB_IOCON_BANK_0      0x01
#define 	IPOLA_IOCON_BANK_0       0x02
#define 	IPOLB_IOCON_BANK_0       0x03
#define 	GPINTENA_IOCON_BANK_0	 0x04
#define 	GPINTENB_IOCON_BANK_0	 0x05
#define 	DEFVALA_IOCON_BANK_0     0x06
#define 	DEFVALB_IOCON_BANK_0     0x07
#define 	INTCONA_IOCON_BANK_0     0x08
#define 	INTCONB_IOCON_BANK_0     0x09
#define 	IOCON_IOCON_BANK_0       0x0A
#define 	GPPUA_IOCON_BANK_0       0x0C
#define 	GPPUB_IOCON_BANK_0       0x0D
#define 	INTFA_IOCON_BANK_0       0x0E
#define 	INTFB_IOCON_BANK_0       0x0F
#define 	INTCAPA_IOCON_BANK_0     0x10
#define 	INTCAPB_IOCON_BANK_0     0x11
#define 	GPIOA_IOCON_BANK_0       0x12
#define 	GPIOB_IOCON_BANK_0       0x13
#define 	OLATA_IOCON_BANK_0       0x14
#define 	OLATB_IOCON_BANK_0       0x15

//IOCON.BANK = 1 Adressen
#define 	IODIRA_IOCON_BANK_1      0x00
#define 	IPOLA_IOCON_BANK_1       0x01
#define 	GPINTENA_IOCON_BANK_1	 0x02
#define 	DEFVALA_IOCON_BANK_1     0x03
#define 	INTCONA_IOCON_BANK_1     0x04
#define 	IOCON_IOCON_BANK_1       0x05
#define 	GPPUA_IOCON_BANK_1       0x06
#define 	INTFA_IOCON_BANK_1       0x07
#define 	INTCAPA_IOCON_BANK_1     0x08
#define 	GPIOA_IOCON_BANK_1       0x09
#define 	OLATA_IOCON_BANK_1       0x0A
#define 	IODIRB_IOCON_BANK_1      0x10
#define 	IPOLB_IOCON_BANK_1       0x11
#define 	GPINTENB_IOCON_BANK_1    0x12
#define 	DEFVALB_IOCON_BANK_1     0x13
#define 	INTCONB_IOCON_BANK_1     0x14 
#define 	GPPUB_IOCON_BANK_1       0x16
#define 	INTFB_IOCON_BANK_1       0x17
#define 	INTCAPB_IOCON_BANK_1     0x18
#define 	GPIOB_IOCON_BANK_1       0x19
#define 	OLATB_IOCON_BANK_1       0x1A

//Flags in IOCON-Register
#define		INTPOL	1
#define		ODR     2
#define		HAEN	3
#define		DISSLW	4
#define		SEQOP	5
#define		MIRROR	6
#define		BANK	7

//Expandernamen, -adressen
enum expanderAdr {
    expanderAdr_0 = 0,
    expanderAdr_1,
    expanderAdr_2,
    expanderAdr_3,
    expanderAdr_4,
    expanderAdr_5,
    expanderAdr_6,
    expanderAdr_7
};

//
enum port_AB {
    port_A = 0,
    port_B
};

//bit-Stellen
enum bitStelle {
    bit_0 = 0,
    bit_1,
    bit_2,
    bit_3,
    bit_4,
    bit_5,
    bit_6,
    bit_7,
};

//für regData[] Registeralias
enum regDataRegisterAlias {
    IODIRA = 0,
    IODIRB,
    IPOLA,
    IPOLB,
    GPINTENA,
    GPINTENB,
    DEFVALA,
    DEFVALB,
    INTCONA,
    INTCONB,
    IOCON,
    GPPUA,
    GPPUB,
    INTFA,
    INTFB,
    INTCAPA,
    INTCAPB,
    GPIOA,
    GPIOB,
    OLATA,
    OLATB
};

//Die Adressen müssen immer bei 0 anfangen und dann fortlaufend sein!
#define EXPANDER_NUM 1

void setupMCP23N17();

void setRegData(uint8_t adr, uint8_t reg, uint8_t dat);
uint8_t getRegData(uint8_t adr, uint8_t reg);

/* 
 * IODIR    POR = 0b111 1111
 * adr: eine Zahl 0 - 7 wie sie in A0..2 dargestellt wurde
 * gpio_ab: 0 = GPA[0..7], 1 = GPB[0..7]
 * pinSet: Byte das in Register geschrieben wird, beschreiben von einzelnen bits ist nicht vorgesehen
 * Controls the direction of the data I/O.
 * 1 = Pin is configured as an input.
 * 0 = Pin is configured as an output.
 * For MCP23017, IO7 must be set to "0" (output).
 */
void set_I_O_DIRECTION_REGISTER(uint8_t adr, uint8_t gpio_ab, uint8_t pinSet);
uint8_t get_I_O_DIRECTION_REGISTER(uint8_t adr, uint8_t gpio_ab);

/* IPOL POR = 0b0000 0000
 * adr: eine Zahl 0 - 7 wie sie in A0..2 dargestellt wurde
 * gpio_ab: 0 = GPA[0..7], 1 = GPB[0..7]
 * pinSet: Byte das in Register geschrieben wird, beschreiben von einzelnen bits ist nicht vorgesehen
 * If a bit is set, the corresponding GPIO register bit will
 * reflect the inverted value on the pin.
 * 1 = GPIO register bit reflects the opposite logic state of the input pin.
 * 0 = GPIO register bit reflects the same logic state of the input pin.
 */
void set_INPUT_POLARITY_REGISTER(uint8_t adr, uint8_t gpio_ab, uint8_t pinSet);
uint8_t get_INPUT_POLARITY_REGISTER(uint8_t adr, uint8_t gpio_ab);

/* GPINTEN POR = 0b0000 0000
 * #adr: eine Zahl 0 - 7 wie sie in A0..2 dargestellt wurde
 * gpio_ab: 0 = GPA[0..7], 1 = GPB[0..7]
 * pinSet: Byte das in Register geschrieben wird, beschreiben von einzelnen bits ist nicht vorgesehen
 * If a bit is set, the corresponding pin is enabled for
 * interrupt-on-change.
 * 1 = Enables GPIO input pin for interrupt-on-change event.
 * 0 = Disables GPIO input pin for interrupt-on-change event.
 */
void set_INTERRUPT_ON_CHANGE_PINS(uint8_t adr, uint8_t gpio_ab, uint8_t pinSet);
uint8_t get_INTERRUPT_ON_CHANGE_PINS(uint8_t adr, uint8_t gpio_ab);

/* DEFVAL POR = 0b0000 0000
 * adr: eine Zahl 0 - 7 wie sie in A0..2 dargestellt wurde
 * gpio_ab: 0 = GPA[0..7], 1 = GPB[0..7]
 * pinSet: Byte das in Register geschrieben wird, beschreiben von einzelnen bits ist nicht vorgesehen
 * The default comparison value is configured in the
 * DEFVAL register. If enabled (via GPINTEN and
 * INTCON) to compare against the DEFVAL register, an
 * opposite value on the associated pin will cause an
 * interrupt to occur.
 * Sets the compare value for pins configured for interrupt-on-change from defaults. Refer to INTCON.
 * If the associated pin level is the opposite from the register bit, an interrupt occurs. Refer to INTCON and GPINTEN.
 */
void set_DEFAULT_VALUE_REGISTER(uint8_t adr, uint8_t gpio_ab, uint8_t pinSet);
uint8_t get_DEFAULT_VALUE_REGISTER(uint8_t adr, uint8_t gpio_ab);

/* INTCON POR = 0b0000 0000
 * adr: eine Zahl 0 - 7 wie sie in A0..2 dargestellt wurde
 * gpio_ab: 0 = GPA[0..7], 1 = GPB[0..7]
 * pinSet: Byte das in Register geschrieben wird, beschreiben von einzelnen bits ist nicht vorgesehen
 * The INTCON register controls how the associated pin
 * value is compared for the interrupt-on-change feature.
 * 1 = Pin value is compared against the associated bit in the DEFVAL register.
 * 0 = Pin value is compared against the previous pin value.
 */
void set_INTERRUPT_ON_CHANGE_CONTROL_REGISTER(uint8_t adr, uint8_t gpio_ab, uint8_t pinSet);
uint8_t get_INTERRUPT_ON_CHANGE_CONTROL_REGISTER(uint8_t adr, uint8_t gpio_ab);

/* IOCON POR = 0b0000 0000
 * adr: eine Zahl 0 - 7 wie sie in A0..2 dargestellt wurde
 * gpio_ab: 0 = GPA[0..7], 1 = GPB[0..7]
 * pinSet: Byte das in Register geschrieben wird, beschreiben von einzelnen bits ist nicht vorgesehen
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
void set_I_O_EXPANDER_CONFIGURATION_REGISTER(uint8_t adr, uint8_t gpio_ab, uint8_t configBits);
uint8_t get_I_O_EXPANDER_CONFIGURATION_REGISTER(uint8_t adr, uint8_t gpio_ab);

/* GPPU POR = 0b0000 0000
 * adr: eine Zahl 0 - 7 wie sie in A0..2 dargestellt wurde
 * gpio_ab: 0 = GPA[0..7], 1 = GPB[0..7]
 * pinSet: Byte das in Register geschrieben wird, beschreiben von einzelnen bits ist nicht vorgesehen
 * The GPPU register controls the pull-up resistors for the
 * port pins. If a bit is set and the corresponding pin is
 * configured as an input, the corresponding port pin is
 * internally pulled up with a 100 kOhm resistor.
 * 1 = Pull-up enabled
 * 0 = Pull-up disabled
 */
void set_GPIO_PULL_UP_RESISTOR_REGISTER(uint8_t adr, uint8_t gpio_ab, uint8_t pinSet);
uint8_t get_GPIO_PULL_UP_RESISTOR_REGISTER(uint8_t adr, uint8_t gpio_ab);

/* INTF POR = 0b0000 0000
 * adr: eine Zahl 0 - 7 wie sie in A0..2 dargestellt wurde
 * gpio_ab: 0 = GPA[0..7], 1 = GPB[0..7]
 * The INTF register reflects the interrupt condition on the
 * port pins of any pin that is enabled for interrupts via the
 * GPINTEN register.
 * 1 = Pin caused interrupt.
 * 0 = Interrupt not pending
 */
uint8_t get_INTERRUPT_FLAG_REGISTER(uint8_t adr, uint8_t gpio_ab);

/* INTCAP POR = 0bxxxx xxxx
 * adr: eine Zahl 0 - 7 wie sie in A0..2 dargestellt wurde
 * gpio_ab: 0 = GPA[0..7], 1 = GPB[0..7]
 * The INTCAP register captures the GPIO port value at
 * the time the interrupt occurred. The register is
 * read-only and is updated only when an interrupt
 * occurs. The register remains unchanged until the
 * interrupt is cleared via a read of INTCAP or GPIO.
 * 1 = Logic-high
 * 0 = Logic-low
 */
uint8_t get_INTERRUPT_CAPTURED_VALUE(uint8_t adr, uint8_t gpio_ab);

/* GPIO POR = 0b0000 0000
 * adr: eine Zahl 0 - 7 wie sie in A0..2 dargestellt wurde
 * gpio_ab: 0 = GPA[0..7], 1 = GPB[0..7]
 * pinSet: Byte das in Register geschrieben wird, beschreiben von einzelnen bits ist nicht vorgesehen
 * The GPIO register reflects the value on the port.
 * Reading from this register reads the port. Writing to this
 * register modifies the Output Latch (OLAT) register.
 * 1 = Logic-high
 * 0 = Logic-low
 */
void set_GENERAL_PURPOSE_I_O_PORT_REGISTER(uint8_t adr, uint8_t gpio_ab, uint8_t pinSet);
uint8_t get_GENERAL_PURPOSE_I_O_PORT_REGISTER(uint8_t adr, uint8_t gpio_ab);

/* OLAT POR = 0b0000 0000
 * adr: eine Zahl 0 - 7 wie sie in A0..2 dargestellt wurde
 * gpio_ab: 0 = GPA[0..7], 1 = GPB[0..7]
 * pinSet: Byte das in Register geschrieben wird, beschreiben von einzelnen bits ist nicht vorgesehen
 * The OLAT register provides access to the output
 * latches. A read from this register results in a read of the
 * OLAT and not the port itself. A write to this register
 * modifies the output latches that modifies the pins
 * configured as outputs.
 * 1 = Logic-high
 * 0 = Logic-low
 */
void set_OUTPUT_LATCH_REGISTER_0(uint8_t adr, uint8_t gpio_ab, uint8_t pinSet);
uint8_t get_OUTPUT_LATCH_REGISTER_0(uint8_t adr, uint8_t gpio_ab);


#endif // MCP23017_H

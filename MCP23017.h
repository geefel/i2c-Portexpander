#ifndef MCP23017_H
#define MCP23017_H

#include <stdint.h>

#define	MCP23N17_ADR_0	0b01000000
#define	MCP23N17_ADR_1	0b01000010
#define	MCP23N17_ADR_2	0b01000100
#define	MCP23N17_ADR_3	0b01000110
#define	MCP23N17_ADR_4	0b01001000
#define	MCP23N17_ADR_5	0b01001010
#define	MCP23N17_ADR_6	0b01001100
#define	MCP23N17_ADR_7	0b01001110

#define WRITE 0
#define READ  1

#define ACK   0
#define NACK  1

//IOCON.BANK = 0
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
#define 	IOCON_IOCON_BANK_0       0x0B
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

//IOCON.BANK = 1
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
#define 	IOCON_IOCON_BANK_1       0x15
#define 	GPPUB_IOCON_BANK_1       0x16
#define 	INTFB_IOCON_BANK_1       0x17
#define 	INTCAPB_IOCON_BANK_1     0x18
#define 	GPIOB_IOCON_BANK_1       0x19
#define 	OLATB_IOCON_BANK_1       0x1A

#define 	IO0     1
#define 	IO1     2
#define 	IO2     4
#define 	IO3     8
#define 	IO4     16
#define 	IO5     32
#define 	IO6     64
#define 	IO7     128

#define		IP0     1
#define		IP1     2
#define		IP2     4
#define		IP3     8
#define		IP4     16
#define		IP5     32
#define		IP6     64
#define		IP7     128
			
#define		GPINT0	1
#define		GPINT1	2
#define		GPINT2	4
#define		GPINT3	8
#define		GPINT4	16
#define		GPINT5	32
#define		GPINT6	64
#define		GPINT7	128
			
#define		DEF0	1
#define		DEF1	2
#define		DEF2	4
#define		DEF3	8
#define		DEF4	16
#define		DEF5	32
#define		DEF6	64
#define		DEF7	128
			
#define		IOC0	1
#define		IOC1	2
#define		IOC2	4
#define		IOC3	8
#define		IOC4	16
#define		IOC5	32
#define		IOC6	64
#define		IOC7	128
			
#define		PU0     1
#define		PU1     2
#define		PU2     4
#define		PU3     8
#define		PU4     16
#define		PU5     32
#define		PU6     64
#define		PU7     128
			
#define		INT0	1
#define		INT1	2
#define		INT2	4
#define		INT3	8
#define		INT4	16
#define		INT5	32
#define		INT6	64
#define		INT7	128
			
#define		ICP0	1
#define		ICP1	2
#define		ICP2	4
#define		ICP3	8
#define		ICP4	16
#define		ICP5	32
#define		ICP6	64
#define		ICP7	128
			
#define		GP0     1
#define		GP1     2
#define		GP2     4
#define		GP3     8
#define		GP4     16
#define		GP5     32
#define		GP6     64
#define		GP7     128
			
#define		OL0     1
#define		OL1     2
#define		OL2     4
#define		OL3     8
#define		OL4     16
#define		OL5     32
#define		OL6     64
#define		OL7     128

#define     BIT0    1			
#define		INTPOL	2
#define		ODR     4
#define		HAEN	8
#define		DISSLW	16
#define		SEQOP	32
#define		MIRROR	64
#define		BANK	128



void set_I_O_DIRECTION_REGISTER_A(uint8_t IOn);
void set_I_O_DIRECTION_REGISTER_B(uint8_t IOn);
uint8_t get_I_O_DIRECTION_REGISTER_A();
uint8_t get_I_O_DIRECTION_REGISTER_B();
void set_INPUT_POLARITY_REGISTER_A(uint8_t IOn);
void set_INPUT_POLARITY_REGISTER_B(uint8_t IOn);
uint8_t get_INPUT_POLARITY_REGISTER_A();
uint8_t get_INPUT_POLARITY_REGISTER_B();
void set_INTERRUPT_ON_CHANGE_PINS_A(uint8_t GPINTn);
void set_INTERRUPT_ON_CHANGE_PINS_B(uint8_t GPINTn);
uint8_t get_INTERRUPT_ON_CHANGE_PINS_A();
uint8_t get_INTERRUPT_ON_CHANGE_PINS_B();
void set_DEFAULT_VALUE_REGISTER_A(uint8_t DEFn);
void set_DEFAULT_VALUE_REGISTER_B(uint8_t DEFn);
uint8_t get_DEFAULT_VALUE_REGISTER_A();
uint8_t get_DEFAULT_VALUE_REGISTER_B();
void set_INTERRUPT_ON_CHANGE_CONTROL_REGISTER_A(uint8_t IOCn);
void set_INTERRUPT_ON_CHANGE_CONTROL_REGISTER_B(uint8_t IOCn);
uint8_t get_INTERRUPT_ON_CHANGE_CONTROL_REGISTER_A();
uint8_t get_INTERRUPT_ON_CHANGE_CONTROL_REGISTER_B();
void set_I_O_EXPANDER_CONFIGURATION_REGISTER_A(uint8_t funk);
void set_I_O_EXPANDER_CONFIGURATION_REGISTER_B(uint8_t funk);
uint8_t get_I_O_EXPANDER_CONFIGURATION_REGISTER_A();
uint8_t get_I_O_EXPANDER_CONFIGURATION_REGISTER_B();
void set_GPIO_PULL_UP_RESISTOR_REGISTER_A(uint8_t PUn);
void set_GPIO_PULL_UP_RESISTOR_REGISTER_B(uint8_t PUn);
uint8_t get_GPIO_PULL_UP_RESISTOR_REGISTER_A();
uint8_t get_GPIO_PULL_UP_RESISTOR_REGISTER_B();
uint8_t get_INTERRUPT_FLAG_REGISTER_A();
uint8_t get_INTERRUPT_FLAG_REGISTER_B();
uint8_t get_INTERRUPT_CAPTURED_VALUE_A();
uint8_t get_INTERRUPT_CAPTURED_VALUE_B();
void set_GENERAL_PURPOSE_I_O_PORT_REGISTER_A(uint8_t GPn);
void set_GENERAL_PURPOSE_I_O_PORT_REGISTER_B(uint8_t GPn);
uint8_t get_GENERAL_PURPOSE_I_O_PORT_REGISTER_A();
uint8_t get_GENERAL_PURPOSE_I_O_PORT_REGISTER_B();
void set_OUTPUT_LATCH_REGISTER_0_A(uint8_t OLn);
void set_OUTPUT_LATCH_REGISTER_0_B(uint8_t OLn);
uint8_t get_OUTPUT_LATCH_REGISTER_0_A();
uint8_t get_OUTPUT_LATCH_REGISTER_0_B();


#endif // MCP23017_H

#ifndef MCP23017_H
#define MCP23017_H

#include <stdint.h>

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
#define 	GPPUB_IOCON_BANK_1       0x16
#define 	INTFB_IOCON_BANK_1       0x17
#define 	INTCAPB_IOCON_BANK_1     0x18
#define 	GPIOB_IOCON_BANK_1       0x19
#define 	OLATB_IOCON_BANK_1       0x1A

#define		IO0     0
#define		IO1     1
#define		IO2     2
#define		IO3     3
#define		IO4     4
#define		IO5     5
#define		IO6     6
#define		IO7     7
			
#define		IP0     0
#define		IP1     1
#define		IP2     2
#define		IP3     3
#define		IP4     4
#define		IP5     5
#define		IP6     6
#define		IP7     7
			
#define		GPINT0	0
#define		GPINT1	1
#define		GPINT2	2
#define		GPINT3	3
#define		GPINT4	4
#define		GPINT5	5
#define		GPINT6	6
#define		GPINT7	7
			
#define		DEF0	0
#define		DEF1	1
#define		DEF2	2
#define		DEF3	3
#define		DEF4	4
#define		DEF5	5
#define		DEF6	6
#define		DEF7	7
			
#define		IOC0	0
#define		IOC1	1
#define		IOC2	2
#define		IOC3	3
#define		IOC4	4
#define		IOC5	5
#define		IOC6	6
#define		IOC7	7
			
#define		PU0     0
#define		PU1     1
#define		PU2     2
#define		PU3     3
#define		PU4     4
#define		PU5     5
#define		PU6     6
#define		PU7     7
			
#define		INT0	0
#define		INT1	1
#define		INT2	2
#define		INT3	3
#define		INT4	4
#define		INT5	5
#define		INT6	6
#define		INT7	7
			
#define		ICP0	0
#define		ICP1	1
#define		ICP2	2
#define		ICP3	3
#define		ICP4	4
#define		ICP5	5
#define		ICP6	6
#define		ICP7	7
			
#define		GP0     0
#define		GP1     1
#define		GP2     2
#define		GP3     3
#define		GP4     4
#define		GP5     5
#define		GP6     6
#define		GP7     7
			
#define		OL0     0
#define		OL1     1
#define		OL2     2
#define		OL3     3
#define		OL4     4
#define		OL5     5
#define		OL6     6
#define		OL7     7

#define		INTPOL	1
#define		ODR     2
#define		HAEN	3
#define		DISSLW	4
#define		SEQOP	5
#define		MIRROR	6
#define		BANK	7

enum regData {
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

void setupMCP23N17(uint8_t bnk);

void setRegData(uint8_t reg, uint8_t dat);
uint8_t getRegData(uint8_t reg);

void set_I_O_DIRECTION_REGISTER(uint8_t adr, uint8_t gp_n, uint8_t pinSet);
uint8_t get_I_O_DIRECTION_REGISTER(uint8_t adr, uint8_t gp_n);
void set_INPUT_POLARITY_REGISTER(uint8_t adr, uint8_t gp_n, uint8_t pinSet);
uint8_t get_INPUT_POLARITY_REGISTER(uint8_t adr, uint8_t gp_n);
void set_INTERRUPT_ON_CHANGE_PINS(uint8_t adr, uint8_t gp_n, uint8_t pinSet);
uint8_t get_INTERRUPT_ON_CHANGE_PINS(uint8_t adr, uint8_t gp_n);
void set_DEFAULT_VALUE_REGISTER(uint8_t adr, uint8_t gp_n, uint8_t pinSet);
uint8_t get_DEFAULT_VALUE_REGISTER(uint8_t adr, uint8_t gp_n);
void set_INTERRUPT_ON_CHANGE_CONTROL_REGISTER(uint8_t adr, uint8_t gp_n, uint8_t pinSet);
uint8_t get_INTERRUPT_ON_CHANGE_CONTROL_REGISTER(uint8_t adr, uint8_t gp_n);
void set_I_O_EXPANDER_CONFIGURATION_REGISTER(uint8_t adr, uint8_t gp_n, uint8_t configBits);
uint8_t get_I_O_EXPANDER_CONFIGURATION_REGISTER(uint8_t adr, uint8_t gp_n);
void set_GPIO_PULL_UP_RESISTOR_REGISTER(uint8_t adr, uint8_t gp_n, uint8_t pinSet);
uint8_t get_GPIO_PULL_UP_RESISTOR_REGISTER(uint8_t adr, uint8_t gp_n);
uint8_t get_INTERRUPT_FLAG_REGISTER(uint8_t adr, uint8_t gp_n);
uint8_t get_INTERRUPT_CAPTURED_VALUE(uint8_t adr, uint8_t gp_n);
void set_GENERAL_PURPOSE_I_O_PORT_REGISTER(uint8_t adr, uint8_t gp_n, uint8_t pinSet);
uint8_t get_GENERAL_PURPOSE_I_O_PORT_REGISTER(uint8_t adr, uint8_t gp_n);
void set_OUTPUT_LATCH_REGISTER_0(uint8_t adr, uint8_t gp_n, uint8_t pinSet);
uint8_t get_OUTPUT_LATCH_REGISTER_0(uint8_t adr, uint8_t gp_n);


#endif // MCP23017_H

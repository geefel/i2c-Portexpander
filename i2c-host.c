/*
 * SDA ist Datenleitung ATMEGA328 PC4 ATTinyx5 PB0
 * SCL ist Clockleitung ATMEGA328 PC5 ATTinyx5 PB2
 * R/W=1 -> Lesen; RW=0 -> Schreiben
 * MSB: Most Significant Bit
 * alle Datenpakete sind 9 bit lang: 8 Datenbit, 1 ACK
 * alle Adresspakete sind 9 bit lang: 7 Adressbit, 1 RW-bit, 1 ACK
 * lesen: R = 1
 * schreiben: W = 0
 * ACK: Slave setzt Leitung auf Low (SCL ist gerade high)
 * Adresse 0000 000 ist reserviert, hiermit werden alle Slaves angesprochen
 * Übertragung: START, Adresspaket, Datenpaket, STOP
 * START: SCL ist high, SDA wechselt nach low
 * STOP: SCL ist nach ACK-Takt wieder(!) auf high, SDA wechselt nach high
 * 
 */
 
#include "i2c-host.h"
#include <util/delay.h>
#include "printS.h"
#include "pin.h"

uint8_t adr;

#define LED_PIN PINDEF(D, 2)

#define DLY_ADD 6 +20



void startI2c();
void stopI2c();
void sendACK();
void sendNACK();
uint8_t readACK();
void sendI2cData(uint8_t *data);
void getI2cData(uint8_t *data);

void led() {
    setPin(LED_PIN);
    clrPin(LED_PIN);
}
#define LED led();

//_delay_loop_1(count);//cy = 9 + count * 3   80cy für 100kHz

void setupI2cSoftHost() {
	setOutput(SCL_PIN);
	setPin(SCL_PIN);
	
    setOutput(SDA_PIN);
    	
	setOutput(LED_PIN);
	clrPin(LED_PIN);
}

void startI2c() {
    setOutput(SDA_PIN);
    setPin(SCL_PIN);
    _delay_loop_1(25 + DLY_ADD);
    
	clrPin(SDA_PIN);
    _delay_loop_1(25 + DLY_ADD);
    clrPin(SCL_PIN);
}

void stopI2c() {
    setOutput(SDA_PIN);
    clrPin(SDA_PIN);
    _delay_loop_1(25 + DLY_ADD);
    setPin(SCL_PIN);
    _delay_loop_1(25 + DLY_ADD);
    setPin(SDA_PIN);
    
}

void sendACK() {
    _delay_loop_1(5 + DLY_ADD / 2);
    setOutput(SDA_PIN);                 //| 14c 0,875 us
    clrPin(SDA_PIN);                    //| 
    _delay_loop_1(16 + DLY_ADD / 2);
    
    setPin(SCL_PIN);
    _delay_loop_1(25 + DLY_ADD);;
    clrPin(SCL_PIN);
}

void sendNACK() {
    _delay_loop_1(5 + DLY_ADD / 2);
    setOutput(SDA_PIN);                 //| 14c 0,875 us
    setPin(SDA_PIN);                    //| 
    _delay_loop_1(16 + DLY_ADD / 2);
    
    setPin(SCL_PIN);
    _delay_loop_1(25 + DLY_ADD);
    clrPin(SCL_PIN);
}

uint8_t readACK() {
    uint8_t ack;
    _delay_loop_1(5 + DLY_ADD / 2);
    setInput(SDA_PIN);
    _delay_loop_1(16 + DLY_ADD / 2);
    setPin(SCL_PIN);
    if (getPin(SDA_PIN))
        ack = 0;
    else
        ack = 1;
    _delay_loop_1(25 + DLY_ADD);
    clrPin(SCL_PIN);
    return ack;
}

//Clock low, Datum setzen, Clock high, Clock low, Datum setzen, ...
void sendI2cData(uint8_t* data) {
	uint8_t maske = 0b10000000;
	setOutput(SDA_PIN);
	
	for (uint8_t i = 0; i < 8; i++) {
        _delay_loop_1(5 + DLY_ADD / 2);
        
        if ((*data & maske) == maske)   //|
            setPin(SDA_PIN);            //|
        else                            //| 19c 1.25us
			clrPin(SDA_PIN);            //|
        maske /= 2;                     //|
        
        _delay_loop_1(16 + DLY_ADD / 2);
		setPin(SCL_PIN);    //HIGH      //| 12c 0.752us
        _delay_loop_1(25 + DLY_ADD);

        clrPin(SCL_PIN);    //LOW
	}
}

void sendDataToClient(uint8_t *data, uint8_t anzData) {
    uint8_t i;
	adr = (data[0] << 1) + 0;   //rw = 0: schreiben zum Client 
	startI2c();
    sendI2cData(&adr);
    readACK();
    
	for (i = 1; i < anzData - 1; ++i) {
		sendI2cData(&data[i]);
        readACK();
	}
    sendI2cData(&data[i]);
    readACK();
	stopI2c();
}

void getDataFromClient(uint8_t *data, uint8_t anzData) {
	uint8_t bitNr;
	uint8_t byteNr;
	uint8_t maske;
	adr = (data[0] << 1) + 1;   //rw = 1: lesen vom Client
	
	startI2c();
    sendI2cData(&adr);
    sendACK();                 //LOW
    
    clrPin(SDA_PIN);
    setInput(SDA_PIN);
    
	for (byteNr = 1; byteNr < anzData; ++byteNr)
	{
        data[byteNr] = 0;
        maske = 0b10000000;
       
        for (bitNr = 0; bitNr < 8; bitNr++)
        {
            _delay_loop_1(25 + DLY_ADD);
            setPin(SCL_PIN);    //HIGH
            _delay_loop_1(5 + DLY_ADD / 2);
            
            if (getPin(SDA_PIN))            //|
                data[byteNr] += maske;      //| 13c 0,875us
            maske /= 2;                     //|
            
            _delay_loop_1(16 + DLY_ADD / 2);
            clrPin(SCL_PIN);    //LOW
        }
        if (byteNr < anzData - 1)           //        |
            clrPin(SDA_PIN);                //ACK     |
        else                                //        | 18c 1.19us
            setPin(SDA_PIN);                //NACK    |
        setOutput(SDA_PIN);                 //        |
        _delay_loop_1(16);
        setPin(SCL_PIN);        //HIGH
        _delay_loop_1(25 + DLY_ADD);
        clrPin(SCL_PIN);        //LOW
        setInput(SDA_PIN);

	}
	   
	stopI2c();
}

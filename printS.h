#ifndef PRINT_H
#define PRINT_H

#include <stdarg.h>
#include "uart_hard.h"

/*
 * Funktion um Daten in einem Terminal anzuzeigen
 * *txt: Text in dem Formatzeichen eingebettet sein können
 * Formatzeichen: %c: char, %s: string, %d: int8_t als dezimal, %h: int8_t als hex, %b: int8_t als bin 
 * string (nur Ascii-Zeichen) kann beliebig lang sein, char ein Zeichen und int nur 8bit lang. 
 */
void printS(char *txt, ...);

#endif	//PRINT_H

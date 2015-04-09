//---------------------------------------------------------
// INCLUDES
//---------------------------------------------------------

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/simpio.h"
#include "lib/genlib.h"

//---------------------------------------------------------
// TYPES
//---------------------------------------------------------

typedef enum { FALSE, TRUE } Bool;

//---------------------------------------------------------
// CONSTANTS
//---------------------------------------------------------

//---------------------------------------------------------
// FUNCTION PROTOTYPES
//---------------------------------------------------------

void PrintGrayCode(int num_bits);
void GrayCode(int num_bits, char* bitString);
void ReverseGrayCode(int num_bits, char* bitString);

//---------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------

Uppgift1() {
	printf("Enter the number of bits you wish to generate Graycode for\n");
	int num_bits = 0;
	while (num_bits <= 0) num_bits = GetInteger();

	PrintGrayCode(num_bits);

}

void PrintGrayCode(int num_bits){
	char bitString[10];
	GrayCode(num_bits, bitString);
	printf("GrayCode for %d bits", num_bits);
}

void GrayCode(int num_bits, char bitString[]){
	if (num_bits == 1) bitString = ['0', '1'];
	else;
}
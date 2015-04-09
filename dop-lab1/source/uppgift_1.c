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
void GrayCode(int num_bits, char* bitList);
void ReverseGrayCode(int num_bits, char* bitList);

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
	char bitList[10];
	GrayCode(num_bits, bitList);
	printf("GrayCode for %d bits", num_bits);
}

void GrayCode(int num_bits, char bitList[]){
	//if (num_bits == 1) bitList = ['0', '1'];
	//else;
}


/* Generell tanke om struktur *

main(){
	nBits=GetInteger();  //villkora naturliga tal
	char* bits
	void PrintGrayCode(int num_bits){ 
		if(numBits == 1) { bits = ['0','1']; } 
		else { 
			if(numBits != 1) { PrintGrayCode(num_bits - 1); } 
			char* mirroredBits = reverse(bits); 
			concat(bits,mirroredBits); 
			//for the first n bits, append 0 
			//for the last n bits, append 1 
		} 
	}
}

*/
//---------------------------------------------------------
// INCLUDES
//---------------------------------------------------------

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/simpio.h"
#include "lib/genlib.h"
#include "lib/strlib.h"

//---------------------------------------------------------
// CONSTANTS
//---------------------------------------------------------

//---------------------------------------------------------
// FUNCTION PROTOTYPES
//---------------------------------------------------------

void PrintGrayCode(int num_bits);
string GrayCode(int num_bits);
//void ReverseGrayCode(int num_bits, char* bitList);

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
	string bitList;
	bitList = GrayCode(num_bits);
	printf("%s", bitList);
	system("pause");
}

string GrayCode(int num_bits){
	static string bitList;
	string reverseBitList = "";
	string zero = "0";
	string one = "1";
	int i = 0;
	if (num_bits == 1) bitList = "01";
	else{
		bitList = GrayCode(num_bits - 1);
		
		reverseBitList = CopyString(bitList);
		
		strrev(reverseBitList);

			Concat(zero, bitList); //ska eg. prependa en nolla till varje delbit, dvs var num_bit position
			bitList = CopyString(zero);
			Concat(one, reverseBitList); //ska eg. prependa en nolla till varje delbit, dvs var num_bit position
			reverseBitList = (one);

		Concat(bitList, reverseBitList);
	}
	return(bitList);

}

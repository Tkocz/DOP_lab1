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
    system("pause");
}

void PrintGrayCode(int num_bits){
	/*string bitList;
	bitList = GrayCode(num_bits);
	printf("%s", bitList);
	system("pause");*/
    GrayCode("", num_bits, FALSE);
}

string GrayCode(string s, int num_bits, bool omvand){
    if (num_bits == 1) {
        string a = Concat(s, "0");
        string b = Concat(s, "1");

        if (omvand && FALSE) {
            printf("%s\n", b);
            printf("%s\n", a);
        }
        else {
            printf("%s\n", a);
            printf("%s\n", b);
        }

        FreeBlock(a);
        FreeBlock(b);

        return;
    }

    string s1 = Concat("0", s);
    string s2 = Concat("1", s);

    if (omvand) {
        GrayCode(s2, num_bits - 1, FALSE);
        GrayCode(s1, num_bits - 1, TRUE);
    }
    else {
        GrayCode(s1, num_bits - 1, FALSE);
        GrayCode(s2, num_bits - 1, TRUE);
    }

    FreeBlock(s1);
    FreeBlock(s2);


    //1

    //2
    //string revs = CopyString(s);
    //strrev(revs);
    //FreeBlock(revs);


	/*static string bitList;
	string reverseBitList = "";
	string zero = "0";
	string one = "1";
	int i = 0;
	if (num_bits == 1) bitList = "01";
	else{
		bitList = GrayCode(num_bits - 1);
		
		reverseBitList = CopyString(bitList);
		
		strrev(reverseBitList);

			zero = Concat(zero, bitList); //ska eg. prependa en nolla till varje delbit, dvs var num_bit position
			bitList = CopyString(zero);
			one = Concat(one, reverseBitList); //ska eg. prependa en nolla till varje delbit, dvs var num_bit position
			reverseBitList = CopyString(one);

		Concat(bitList, reverseBitList);
	}
	return(bitList);*/

}

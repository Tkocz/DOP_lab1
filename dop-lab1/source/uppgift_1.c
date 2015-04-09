//---------------------------------------------------------
// INCLUDES
//---------------------------------------------------------

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void PrintReverseGrayCode(int num_bits);

//---------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------

Uppgift1() {
    printf("HEJSAN UPPGIFT 1\n");
    PrintGrayCode(3);
    system("pause");
}

void PrintGrayCode(int num_bits) {
    if (num_bits == 1) {
        printf("0");
        printf("1");
    }

    if (num_bits == 0) {
        printf("\n");
        return;
    }

    PrintGrayCode(num_bits - 1);
    PrintReverseGrayCode(num_bits - 1);
}

void PrintReverseGrayCode(int num_bits) {
    if (num_bits == 1) {
        printf("1");
        printf("0");
    }

    if (num_bits == 0) {
        printf("\n");
        return;
    }

    PrintGrayCode(num_bits - 1);
    PrintReverseGrayCode(num_bits - 1);

}

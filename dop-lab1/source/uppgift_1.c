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

main() {
    printf("HEJSAN UPPGIFT 1\n");
    PrintGrayCode(3);
    system("pause");
}

void PrintGrayCode(int num_bits) {
    PrintReverseGrayCode(num_bits - 1);
}
    PrintReverseGrayCode(num_bits - 1);

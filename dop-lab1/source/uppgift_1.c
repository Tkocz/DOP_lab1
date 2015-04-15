//---------------------------------------------------------
// INCLUDES
//---------------------------------------------------------

#include "lib/simpio.h"
#include "lib/genlib.h"
#include "lib/strlib.h"

#include <stdio.h>

//---------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------

/*--------------------------------------
 * Function: GenGrayCode()
 * Parameters: code      Ackumulator-sträng för rekursion.
 *             num_bits  Antal bitar att generera Gray-kod för.
 *             reverse   Används för att vända på koden.
 *
 * Description:
 *   Genererar Gray-kod och skriver ut den.
 *------------------------------------*/
void GenGrayCode(string code, int num_bits, bool reverse) {
    // Det algoritmiska basfallet skiljer sig något från det programmatiska, i
    // den bemärkelsen att det algoritmiska basfallet i själva verket är när
    // num_bits==1, medan det programmatiska (när vi bara har en operation kvar
    // att utföra) är när num_bits==1, och vi skriver ut koden.
    if (num_bits == 0) {
        printf("%s\n", code);
        return;
    }

    // Vi genererar lite mer kod för de två olika utfallen genom att lägga på
    // en nolla (ena fallet) och en etta (andra fallet).
    string str1 = Concat(code, "0");
    string str2 = Concat(code, "1");

    // Om reverse==TRUE så ska ordningen vändas bak-och-fram, så vi byter plats
    // på strängarna med varandra.
    if (reverse) {
        string tmp = str1;
               str1 = str2;
               str2 = tmp;
    }

    // En bit avklarad, så vi minskar num_bits med ett och upprepar alltihop
    // rekursivt nedan.
    num_bits--;

    // 1. Skriv ner Graykoden för N-1 bitar med en 0a framför.
    GenGrayCode(str1, num_bits, FALSE);

    // 2. Skriv ner Graykoden för N-1 bitar i omvänd ordning med en 1
    // framför.
    GenGrayCode(str2, num_bits, TRUE);

    // Minneshantering; vi måste avallokera strängarna från minnet.
    FreeBlock(str1);
    FreeBlock(str2);
}

/*--------------------------------------
 * Function: PrintGrayCode()
 * Parameters: num_bits  Antal bitar att generera Gray-kod för.
 *
 * Description:
 *   Genererar Gray-kod och skriver ut den.
 *------------------------------------*/
void PrintGrayCode(int num_bits){
    GenGrayCode("", num_bits, FALSE);
}

/*--------------------------------------
 * Function: Uppgift1()
 * Parameters:
 *
 * Description:
 *   Huvudfunktionen för uppgift 1.
 *------------------------------------*/
Uppgift1() {
    printf("Enter the number of bits you wish to generate Graycode for\n");

    int num_bits = 0;
    while (num_bits <= 0)
        num_bits = GetInteger();

    PrintGrayCode(num_bits);
    system("pause");
}

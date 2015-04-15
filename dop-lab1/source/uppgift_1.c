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
 * Parameters: code      Ackumulator-str�ng f�r rekursion.
 *             num_bits  Antal bitar att generera Gray-kod f�r.
 *             reverse   Anv�nds f�r att v�nda p� koden.
 *
 * Description:
 *   Genererar Gray-kod och skriver ut den.
 *------------------------------------*/
void GenGrayCode(string code, int num_bits, bool reverse) {
    // Det algoritmiska basfallet skiljer sig n�got fr�n det programmatiska, i
    // den bem�rkelsen att det algoritmiska basfallet i sj�lva verket �r n�r
    // num_bits==1, medan det programmatiska (n�r vi bara har en operation kvar
    // att utf�ra) �r n�r num_bits==1, och vi skriver ut koden.
    if (num_bits == 0) {
        printf("%s\n", code);
        return;
    }

    // Vi genererar lite mer kod f�r de tv� olika utfallen genom att l�gga p�
    // en nolla (ena fallet) och en etta (andra fallet).
    string str1 = Concat(code, "0");
    string str2 = Concat(code, "1");

    // Om reverse==TRUE s� ska ordningen v�ndas bak-och-fram, s� vi byter plats
    // p� str�ngarna med varandra.
    if (reverse) {
        string tmp = str1;
               str1 = str2;
               str2 = tmp;
    }

    // En bit avklarad, s� vi minskar num_bits med ett och upprepar alltihop
    // rekursivt nedan.
    num_bits--;

    // 1. Skriv ner Graykoden f�r N-1 bitar med en 0a framf�r.
    GenGrayCode(str1, num_bits, FALSE);

    // 2. Skriv ner Graykoden f�r N-1 bitar i omv�nd ordning med en 1
    // framf�r.
    GenGrayCode(str2, num_bits, TRUE);

    // Minneshantering; vi m�ste avallokera str�ngarna fr�n minnet.
    FreeBlock(str1);
    FreeBlock(str2);
}

/*--------------------------------------
 * Function: PrintGrayCode()
 * Parameters: num_bits  Antal bitar att generera Gray-kod f�r.
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
 *   Huvudfunktionen f�r uppgift 1.
 *------------------------------------*/
Uppgift1() {
    printf("Enter the number of bits you wish to generate Graycode for\n");

    int num_bits = 0;
    while (num_bits <= 0)
        num_bits = GetInteger();

    PrintGrayCode(num_bits);
    system("pause");
}

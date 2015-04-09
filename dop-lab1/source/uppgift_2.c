//---------------------------------------------------------
// INCLUDES
//---------------------------------------------------------

#include "lib/genlib.h"
#include "lib/simpio.h"

#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------
// CONSTANTS
//---------------------------------------------------------

/*--------------------------------------
 * Constants: MAX_WEIGHTS
 *
 * Description:
 *   Max antal tyngder.
 *------------------------------------*/
#define MAX_WEIGHTS 10

//---------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------

/*--------------------------------------
 * Function: IsMeasurable()
 * Parameters: target       M�lvikten som ska "motv�gas."
 *             weights      En vektor inneh�llandes alla tyngder.
 *             num_weights  Antalet tyngder i weights-vektorn.
 *
 * Description:
 *   L�ter anv�ndaren skriva in ett heltal.
 *------------------------------------*/
bool IsMeasurable(int target, int weights[], int num_weights) {
    // Vi har lyckats n� m�lvikten med en kombination av tyngder, vilket inneb�r
    // att den g�r att balansera ut mot de tyngder vi har.
    if (target == 0)
        return TRUE;

    // Vi har provat alla tyngder utan att n� m�lvikten, allts� kan vi inte v�ga
    // upp mot den.
    if (num_weights == 0)
        return FALSE;

    // Vi anv�nder den sista tyngden som vi har och "plockar bort" den.
    int i = num_weights - 1;

    // Vikten p� den tyngd vi ska prova med nu.
    int w = weights[i];

    // Vi kan nu g�ra tre val:
    //   1. Anv�nd inte tyngden alls.
    //   2. Anv�nd tyngden som motvikt.
    //   3. Anv�nd tyngden som medvikt.
    //
    // Vi vill testa alla m�jliga kombinationer, s� vi utf�r alla tre val
    // rekursivt nedan.

    return IsMeasurable(target    , weights, i)  // Utan tyngden.
        || IsMeasurable(target - w, weights, i)  // Motvikt.
        || IsMeasurable(target + w, weights, i); // Medvikt.
}

/*--------------------------------------
 * Function: Uppgift2()
 * Parameters:
 *
 * Description:
 *   Programmets huvudfunktion (avseende uppgift 2).
 *------------------------------------*/
void Uppgift2() {
    int weights[MAX_WEIGHTS] = { 0 };
    int num_weights = MAX_WEIGHTS;

    printf("Enter desired weightstones (Max is %d), end with 0\n", MAX_WEIGHTS);

    for (int i = 0; i < 10; i++){
        weights[i] = GetInteger();
        if (weights[i] <= 0) {
            num_weights = i;
            break;
        }
    }

    // Totalvikten s� vet vi maxvikten vi kan v�ga upp mot.
    int total_weight = 0;

    // R�kna ut totalvikt.
    for (int i = 0; i < num_weights; i++)
        total_weight += weights[i];

    // Prova alla vikter upp till och med totalvikten.
    for (int i = 0; i <= total_weight; i++) {
        if (IsMeasurable(i, weights, num_weights))
            printf("%d is measurable.\n", i);
        else
            printf("%d is NOT measurable.\n", i);
    }

    // Klart! :-)

    printf("No weights above %d are measurable.\n", total_weight);
    system("pause");
}
